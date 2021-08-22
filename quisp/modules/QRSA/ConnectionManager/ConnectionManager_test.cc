#include "ConnectionManager.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include "modules/QNIC.h"
#include "modules/QRSA/HardwareMonitor/IHardwareMonitor.h"
#include "rules/Action.h"
#include "rules/Clause.h"
#include "rules/clauses/EnoughResourceClause.h"
#include "test_utils/TestUtils.h"

namespace {
using namespace omnetpp;
using namespace quisp_test;
using namespace testing;

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy(IRoutingDaemon *_routing_daemon, IHardwareMonitor *_hardware_monitor) : routing_daemon(_routing_daemon), hardware_monitor(_hardware_monitor) {}
  Strategy() {}
  ~Strategy() {}
  IRoutingDaemon *getRoutingDaemon() override { return routing_daemon; }
  IHardwareMonitor *getHardwareMonitor() override { return hardware_monitor; }
  IRoutingDaemon *routing_daemon = nullptr;
  IHardwareMonitor *hardware_monitor = nullptr;
};

class ConnectionManagerTestTarget : public quisp::modules::ConnectionManager {
 public:
  using quisp::modules::ConnectionManager::par;
  using quisp::modules::ConnectionManager::respondToRequest;
  ConnectionManagerTestTarget(IRoutingDaemon *routing_daemon, IHardwareMonitor *hardware_monitor)
      : quisp::modules::ConnectionManager(), toRouterGate(new TestGate(this, "RouterPort$o")) {
    setParInt(this, "address", 123);
    setParInt(this, "total_number_of_qnics", 10);
    this->setName("connection_manager_test_target");
    setParBool(this, "simultaneous_es_enabled", false);
    setParBool(this, "entanglement_swapping_with_purification", true);
    setParInt(this, "num_remote_purification", 1);

    this->provider.setStrategy(std::make_unique<Strategy>(routing_daemon, hardware_monitor));
    setComponentType(new module_type::TestModuleType("test cm"));
  }
  ConnectionManagerTestTarget() : quisp::modules::ConnectionManager() {
    setParInt(this, "address", 123);
    setParInt(this, "total_number_of_qnics", 10);
    this->setName("connection_manager_test_target");
    this->provider.setStrategy(std::make_unique<Strategy>());
    setComponentType(new module_type::TestModuleType("test cm"));
  }
  cGate *gate(const char *gatename, int index = -1) override {
    if (strcmp(gatename, "RouterPort$o") != 0) {
      throw cRuntimeError("unknown gate called");
    }
    return toRouterGate;
  };
  TestGate *toRouterGate;
};

TEST(ConnectionManagerTest, Init) {
  ConnectionManagerTestTarget c;
  ASSERT_EQ(c.par("address").intValue(), 123);
}

TEST(ConnectionManagerTest, RespondToRequest) {
  auto *sim = prepareSimulation();
  auto *routing_daemon = new MockRoutingDaemon();
  auto *hardware_monitor = new MockHardwareMonitor();
  auto *connection_manager = new ConnectionManagerTestTarget(routing_daemon, hardware_monitor);
  sim->registerComponent(connection_manager);
  connection_manager->par("address") = 5;
  connection_manager->callInitialize();
  auto *req = new ConnectionSetupRequest;

  // [QNode2](qnic_addr:1) -- (2)[QNode3](3) -- (4)[QNode4](5) -- (6)[QNode5(test target)]
  req->setActual_destAddr(5);
  req->setActual_srcAddr(4);
  req->setDestAddr(5);
  req->setSrcAddr(2);
  req->setStack_of_QNICsArraySize(3);
  req->setStack_of_QNodeIndexesArraySize(3);
  req->setStack_of_QNodeIndexes(0, 2);
  req->setStack_of_QNodeIndexes(1, 3);
  req->setStack_of_QNodeIndexes(2, 4);
  req->setStack_of_QNICs(0, QNIC_id_pair{.fst = NULL_CONNECTION_SETUP_INFO.qnic, .snd = {.type = QNIC_E, .index = 0, .address = 1}});
  req->setStack_of_QNICs(1, QNIC_id_pair{.fst = {.type = QNIC_E, .index = 0, .address = 2}, .snd = {.type = QNIC_E, .index = 1, .address = 3}});
  req->setStack_of_QNICs(1, QNIC_id_pair{.fst = {.type = QNIC_E, .index = 0, .address = 4}, .snd = {.type = QNIC_E, .index = 1, .address = 5}});

  EXPECT_CALL(*routing_daemon, return_QNIC_address_to_destAddr(5)).Times(1).WillOnce(Return(-1));
  EXPECT_CALL(*routing_daemon, return_QNIC_address_to_destAddr(4)).Times(1).WillOnce(Return(5));
  auto src_info = new ConnectionSetupInfo{};
  EXPECT_CALL(*hardware_monitor, findConnectionInfoByQnicAddr(5)).Times(1).WillOnce(Return(ByMove(std::unique_ptr<ConnectionSetupInfo>(src_info))));

  sim->setContext(connection_manager);
  connection_manager->respondToRequest(req);
  auto gate = connection_manager->toRouterGate;
  EXPECT_EQ(gate->messages.size(), 4);

  unsigned long ruleset_id;
  // checking the ruleset for QNode2(initiator)
  {
    auto *packetFor2 = dynamic_cast<ConnectionSetupResponse *>(gate->messages[0]);
    ASSERT_NE(packetFor2, nullptr);
    EXPECT_EQ(packetFor2->getDestAddr(), 2);
    auto *ruleset = packetFor2->getRuleSet();
    ASSERT_NE(ruleset, nullptr);
    EXPECT_EQ(ruleset->size(), 4);
    ruleset_id = ruleset->ruleset_id;
    // EXPECT_EQ(packetFor2->getRuleSet_id(), ruleset_id);
    EXPECT_EQ(ruleset->entangled_partners.size(), 1);
    // EXPECT_EQ(ruleset->entangled_partners.at(0), 5); // always 0

    // checking the 1st rule: if EnoughResource -> Purify
    {
      auto *rule = ruleset->rules.at(0).get();
      EXPECT_EQ(rule->name, "X purification with : 3");
      EXPECT_EQ(rule->ruleset_id, ruleset_id);
      ASSERT_EQ(rule->action_partners.size(), 1);
      // action partner must be the next neighbor qnode3 (this qnode is qnode2[initiator])
      // first action is the purification with the neighbor qnode
      EXPECT_EQ(rule->action_partners.at(0), 3);
      EXPECT_EQ(rule->next_action_partners.size(), 0);

      EXPECT_EQ(rule->condition->clauses.size(), 1);
      EXPECT_NE(dynamic_cast<PurifyAction *>(rule->action.get()), nullptr);
      EXPECT_NE(dynamic_cast<EnoughResourceClause *>(rule->condition.get()->clauses.at(0)), nullptr);
    }

    // checking the 2nd rule: Wait
    {
      auto *rule = ruleset->rules.at(1).get();
      EXPECT_EQ(rule->name, "Wait rule with: 3");
      EXPECT_EQ(rule->ruleset_id, ruleset_id);
      ASSERT_EQ(rule->action_partners.size(), 1);
      EXPECT_EQ(rule->action_partners.at(0), 3);  // just wait QNode 3
      EXPECT_EQ(rule->next_action_partners.size(), 0);
      ASSERT_EQ(rule->condition->clauses.size(), 1);
      EXPECT_NE(dynamic_cast<WaitClause *>(rule->condition->clauses.at(0)), nullptr);
      EXPECT_EQ(rule->action.get(), nullptr);
    }

    // checking the 3rd rule: if EnoughResource -> Purify
    {
      auto *rule = ruleset->rules.at(2).get();
      EXPECT_EQ(rule->name, "X purification with : 5");
      EXPECT_EQ(rule->ruleset_id, ruleset_id);
      ASSERT_EQ(rule->action_partners.size(), 1);
      // action partner must be the qnode5(responder)
      // third action is the purification with the opposite end qnode
      EXPECT_EQ(rule->action_partners.at(0), 5);
      EXPECT_EQ(rule->next_action_partners.size(), 0);
      EXPECT_EQ(rule->condition->clauses.size(), 1);
      EXPECT_NE(dynamic_cast<PurifyAction *>(rule->action.get()), nullptr);
      EXPECT_NE(dynamic_cast<EnoughResourceClause *>(rule->condition.get()->clauses.at(0)), nullptr);
    }

    // checking the 4th rule
    {
      auto *rule = ruleset->rules.at(3).get();
      EXPECT_EQ(rule->name, "tomography");
      EXPECT_EQ(rule->ruleset_id, ruleset_id);
      EXPECT_EQ(rule->condition->clauses.size(), 2);
      ASSERT_EQ(rule->action_partners.size(), 1);
      // action partner must be the qnode5(responder)
      // last action is the tomography with the opposite end qnode
      EXPECT_EQ(rule->action_partners.at(0), 5);
      EXPECT_EQ(rule->next_action_partners.size(), 0);
      EXPECT_NE(dynamic_cast<RandomMeasureAction *>(rule->action.get()), nullptr);
      EXPECT_NE(dynamic_cast<MeasureCountClause *>(rule->condition.get()->clauses.at(0)), nullptr);
      EXPECT_NE(dynamic_cast<EnoughResourceClause *>(rule->condition.get()->clauses.at(1)), nullptr);
    }

    EXPECT_EQ(ruleset->rules.at(0)->next_rule_id, ruleset->rules.at(1)->rule_index);
    EXPECT_EQ(ruleset->rules.at(1)->next_rule_id, ruleset->rules.at(2)->rule_index);
    EXPECT_EQ(ruleset->rules.at(2)->next_rule_id, ruleset->rules.at(3)->rule_index);
  }

  auto *packetFor3 = dynamic_cast<ConnectionSetupResponse *>(gate->messages[1]);
  ASSERT_NE(packetFor3, nullptr);
  EXPECT_EQ(packetFor3->getDestAddr(), 3);

  auto *packetFor4 = dynamic_cast<ConnectionSetupResponse *>(gate->messages[2]);
  ASSERT_NE(packetFor4, nullptr);
  EXPECT_EQ(packetFor4->getDestAddr(), 4);

  auto *packetFor5 = dynamic_cast<ConnectionSetupResponse *>(gate->messages[3]);
  ASSERT_NE(packetFor5, nullptr);
  EXPECT_EQ(packetFor5->getDestAddr(), 5);

  delete routing_daemon;
  delete hardware_monitor;
}

TEST(ConnectionManagerTest, GetQNICInterface) {
  ConnectionManagerTestTarget c;
  ASSERT_EQ(c.par("address").intValue(), 123);
}
}  // namespace

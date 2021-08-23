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

ACCESS_PRIVATE_FIELD(quisp::modules::EnoughResourceClause, int, partner);
ACCESS_PRIVATE_FIELD(quisp::modules::EnoughResourceClause, int, num_resource_required);

ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, unsigned long, ruleset_id);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, unsigned long, rule_id);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, int, qnic_id);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, QNIC_type, qnic_type);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, int, partner);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, int, resource);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, int, trash_resource);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, int, purification_count);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, bool, X);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, bool, Z);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, int, num_purify);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, int, action_index);

ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, left_partner);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, left_qnic_id);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, self_left_qnic_id);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, left_qnic_address);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, QNIC_type, left_qnic_type);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, QNIC_type, self_left_qnic_type);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, left_resource);

ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, right_partner);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, right_qnic_id);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, self_right_qnic_id);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, right_qnic_address);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, QNIC_type, right_qnic_type);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, QNIC_type, self_right_qnic_type);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, right_resource);

ACCESS_PRIVATE_FIELD(quisp::modules::RandomMeasureAction, int, partner);
ACCESS_PRIVATE_FIELD(quisp::modules::RandomMeasureAction, int, qnic_id);
ACCESS_PRIVATE_FIELD(quisp::modules::RandomMeasureAction, QNIC_type, qnic_type);
ACCESS_PRIVATE_FIELD(quisp::modules::RandomMeasureAction, int, resource);
ACCESS_PRIVATE_FIELD(quisp::modules::RandomMeasureAction, int, src);
ACCESS_PRIVATE_FIELD(quisp::modules::RandomMeasureAction, int, dst);
ACCESS_PRIVATE_FIELD(quisp::modules::RandomMeasureAction, int, current_count);
ACCESS_PRIVATE_FIELD(quisp::modules::RandomMeasureAction, int, max_count);

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
    setParBool(this, "entanglement_swapping_with_purification", false);
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
  connection_manager->par("entanglement_swapping_with_purification") = true;

  connection_manager->callInitialize();
  auto *req = new ConnectionSetupRequest;

  // qnic_index           0       0            1        0            1        0
  // [QNode2](qnic_addr:101) -- (102)[QNode3](103) -- (104)[QNode4](105) -- (106)[QNode5(test target)]
  req->setActual_destAddr(5);
  req->setActual_srcAddr(4);
  req->setDestAddr(5);
  req->setSrcAddr(2);
  req->setStack_of_QNICsArraySize(3);
  req->setStack_of_QNodeIndexesArraySize(3);
  req->setStack_of_QNodeIndexes(0, 2);
  req->setStack_of_QNodeIndexes(1, 3);
  req->setStack_of_QNodeIndexes(2, 4);
  req->setStack_of_QNICs(0, QNIC_id_pair{.fst = NULL_CONNECTION_SETUP_INFO.qnic, .snd = {.type = QNIC_E, .index = 0, .address = 101}});
  req->setStack_of_QNICs(1, QNIC_id_pair{.fst = {.type = QNIC_E, .index = 0, .address = 102}, .snd = {.type = QNIC_E, .index = 1, .address = 103}});
  req->setStack_of_QNICs(1, QNIC_id_pair{.fst = {.type = QNIC_E, .index = 0, .address = 104}, .snd = {.type = QNIC_E, .index = 1, .address = 105}});

  EXPECT_CALL(*routing_daemon, return_QNIC_address_to_destAddr(5)).Times(1).WillOnce(Return(-1));
  EXPECT_CALL(*routing_daemon, return_QNIC_address_to_destAddr(4)).Times(1).WillOnce(Return(105));
  auto src_info = new ConnectionSetupInfo{.qnic =
                                              {
                                                  .type = QNIC_E,
                                                  .index = 0,
                                              },
                                          .neighbor_address = 3,
                                          .quantum_link_cost = 10};
  EXPECT_CALL(*hardware_monitor, findConnectionInfoByQnicAddr(105)).Times(1).WillOnce(Return(ByMove(std::unique_ptr<ConnectionSetupInfo>(src_info))));

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

    // checking the 1st rule of QNode2(initiator): if EnoughResource -> Purify
    {
      auto *rule = ruleset->rules.at(0).get();
      EXPECT_EQ(rule->name, "X purification with : 3");
      EXPECT_EQ(rule->ruleset_id, ruleset_id);
      ASSERT_EQ(rule->action_partners.size(), 1);
      // action partner must be the next neighbor qnode3 (this qnode is qnode2[initiator])
      // first action is the purification with the neighbor qnode
      EXPECT_EQ(rule->action_partners.at(0), 3);
      EXPECT_EQ(rule->next_action_partners.size(), 0);

      auto *action = dynamic_cast<PurifyAction *>(rule->action.get());
      EXPECT_NE(action, nullptr);
      EXPECT_EQ(access_private::rule_id(*action), rule->rule_index);
      EXPECT_EQ(access_private::ruleset_id(*action), ruleset_id);
      EXPECT_EQ(access_private::partner(*action), 3);
      EXPECT_EQ(access_private::X(*action), true);
      EXPECT_EQ(access_private::Z(*action), false);
      EXPECT_EQ(access_private::qnic_id(*action), 0);
      EXPECT_EQ(access_private::qnic_type(*action), QNIC_E);
      EXPECT_EQ(access_private::resource(*action), 0);
      EXPECT_EQ(access_private::trash_resource(*action), 1);
      EXPECT_EQ(access_private::action_index(*action), 0);
      EXPECT_EQ(access_private::purification_count(*action), 1);
      EXPECT_EQ(access_private::num_purify(*action), 1);

      EXPECT_EQ(rule->condition->clauses.size(), 1);
      auto *clause = dynamic_cast<Clause *>(rule->condition.get()->clauses.at(0));
      ASSERT_NE(clause, nullptr);

      auto *enough_resource_clause = dynamic_cast<EnoughResourceClause *>(clause);
      ASSERT_NE(enough_resource_clause, nullptr);
      EXPECT_EQ(access_private::partner(*enough_resource_clause), 3);
      EXPECT_EQ(access_private::num_resource_required(*enough_resource_clause), 2);
    }

    // checking the 2nd rule of QNode2(initiator): Wait
    {
      auto *rule = ruleset->rules.at(1).get();
      EXPECT_EQ(rule->name, "Wait rule with: 3");
      EXPECT_EQ(rule->ruleset_id, ruleset_id);
      ASSERT_EQ(rule->action_partners.size(), 1);
      EXPECT_EQ(rule->action_partners.at(0), 3);  // just wait QNode 3
      EXPECT_EQ(rule->next_action_partners.size(), 1);
      EXPECT_EQ(rule->next_action_partners.at(0), 5);

      ASSERT_EQ(rule->condition->clauses.size(), 1);
      auto *clause = dynamic_cast<WaitClause *>(rule->condition->clauses.at(0));
      EXPECT_NE(clause, nullptr);
      EXPECT_EQ(rule->action.get(), nullptr);
    }

    // checking the 3rd rule of QNode2(initiator): if EnoughResource -> Purify
    {
      auto *rule = ruleset->rules.at(2).get();
      EXPECT_EQ(rule->name, "X purification with : 5");
      EXPECT_EQ(rule->ruleset_id, ruleset_id);
      ASSERT_EQ(rule->action_partners.size(), 1);
      // action partner must be the qnode5(responder)
      // third action is the purification with the opposite end qnode
      EXPECT_EQ(rule->action_partners.at(0), 5);
      EXPECT_EQ(rule->next_action_partners.size(), 0);

      auto *action = dynamic_cast<PurifyAction *>(rule->action.get());
      EXPECT_NE(action, nullptr);
      EXPECT_EQ(access_private::rule_id(*action), rule->rule_index);
      EXPECT_EQ(access_private::ruleset_id(*action), ruleset_id);
      EXPECT_EQ(access_private::partner(*action), 5);
      EXPECT_EQ(access_private::X(*action), true);
      EXPECT_EQ(access_private::Z(*action), false);
      EXPECT_EQ(access_private::qnic_id(*action), 0);
      EXPECT_EQ(access_private::qnic_type(*action), QNIC_E);
      EXPECT_EQ(access_private::resource(*action), 0);
      EXPECT_EQ(access_private::trash_resource(*action), 1);
      EXPECT_EQ(access_private::action_index(*action), 0);
      EXPECT_EQ(access_private::purification_count(*action), 1);
      EXPECT_EQ(access_private::num_purify(*action), 1);

      ASSERT_EQ(rule->condition->clauses.size(), 1);
      auto *clause = dynamic_cast<EnoughResourceClause *>(rule->condition.get()->clauses.at(0));
      ASSERT_NE(clause, nullptr);
      EXPECT_EQ(access_private::partner(*clause), 5);
      EXPECT_EQ(access_private::num_resource_required(*clause), 2);
    }

    // checking the 4th rule of QNode2(initiator): EnoughResource && MeasureCount -> Tomography
    {
      auto *rule = ruleset->rules.at(3).get();
      EXPECT_EQ(rule->name, "tomography");
      EXPECT_EQ(rule->ruleset_id, ruleset_id);
      ASSERT_EQ(rule->action_partners.size(), 1);
      // action partner must be the qnode5(responder)
      // last action is the tomography with the opposite end qnode
      EXPECT_EQ(rule->action_partners.at(0), 5);
      EXPECT_EQ(rule->next_action_partners.size(), 0);

      auto *action = dynamic_cast<RandomMeasureAction *>(rule->action.get());
      EXPECT_NE(action, nullptr);
      EXPECT_EQ(access_private::partner(*action), 5);
      EXPECT_EQ(access_private::qnic_id(*action), 0);
      EXPECT_EQ(access_private::qnic_type(*action), QNIC_E);
      EXPECT_EQ(access_private::resource(*action), 0);
      EXPECT_EQ(access_private::src(*action), 2);
      EXPECT_EQ(access_private::dst(*action), 5);
      EXPECT_EQ(access_private::current_count(*action), 0);
      EXPECT_EQ(access_private::max_count(*action), 0);  // XXX: is it right?

      ASSERT_EQ(rule->condition->clauses.size(), 2);
      auto *measure_count_clause = dynamic_cast<MeasureCountClause *>(rule->condition.get()->clauses.at(0));
      ASSERT_NE(measure_count_clause, nullptr);
      EXPECT_EQ(measure_count_clause->max_count, 0);  // XXX: is it right?
      EXPECT_EQ(measure_count_clause->current_count, 0);
      auto *enough_res_clause = dynamic_cast<EnoughResourceClause *>(rule->condition.get()->clauses.at(1));
      ASSERT_NE(enough_res_clause, nullptr);
      EXPECT_EQ(access_private::partner(*enough_res_clause), 5);
      EXPECT_EQ(access_private::num_resource_required(*enough_res_clause), 1);
    }

    EXPECT_EQ(ruleset->rules.at(0)->next_rule_id, ruleset->rules.at(1)->rule_index);
    EXPECT_EQ(ruleset->rules.at(1)->next_rule_id, ruleset->rules.at(2)->rule_index);
    EXPECT_EQ(ruleset->rules.at(2)->next_rule_id, ruleset->rules.at(3)->rule_index);
    EXPECT_EQ(ruleset->rules.at(3)->next_rule_id, 0);
  }

  // checking the ruleset for QNode3
  {
    auto *packetFor3 = dynamic_cast<ConnectionSetupResponse *>(gate->messages[1]);
    ASSERT_NE(packetFor3, nullptr);
    EXPECT_EQ(packetFor3->getDestAddr(), 3);

    auto *ruleset = packetFor3->getRuleSet();
    ASSERT_NE(ruleset, nullptr);
    EXPECT_EQ(ruleset->size(), 5);
    EXPECT_EQ(ruleset->ruleset_id, ruleset_id);
    // EXPECT_EQ(packetFor3->getRuleSet_id(), ruleset_id);
    EXPECT_EQ(ruleset->entangled_partners.size(), 1);
    // EXPECT_EQ(ruleset->entangled_partners.at(0), 5); // always 0

    // checking the 1st rule of QNode3: if EnoughResource -> Purify
    {
      auto *rule = ruleset->rules.at(0).get();
      EXPECT_EQ(rule->name, "X purification with : 2");
      EXPECT_EQ(rule->ruleset_id, ruleset_id);
      ASSERT_EQ(rule->action_partners.size(), 1);
      EXPECT_EQ(rule->action_partners.at(0), 2);
      EXPECT_EQ(rule->next_action_partners.size(), 0);

      auto *action = dynamic_cast<PurifyAction *>(rule->action.get());
      EXPECT_NE(action, nullptr);
      EXPECT_EQ(access_private::rule_id(*action), rule->rule_index);
      EXPECT_EQ(access_private::ruleset_id(*action), ruleset_id);
      EXPECT_EQ(access_private::partner(*action), 2);
      EXPECT_EQ(access_private::X(*action), true);
      EXPECT_EQ(access_private::Z(*action), false);
      EXPECT_EQ(access_private::qnic_id(*action), 0);
      EXPECT_EQ(access_private::qnic_type(*action), QNIC_E);
      EXPECT_EQ(access_private::resource(*action), 0);
      EXPECT_EQ(access_private::trash_resource(*action), 1);
      EXPECT_EQ(access_private::action_index(*action), 0);
      EXPECT_EQ(access_private::purification_count(*action), 1);
      EXPECT_EQ(access_private::num_purify(*action), 1);

      ASSERT_EQ(rule->condition->clauses.size(), 1);
      auto *clause = dynamic_cast<EnoughResourceClause *>(rule->condition.get()->clauses.at(0));
      ASSERT_NE(clause, nullptr);
      EXPECT_EQ(access_private::partner(*clause), 2);
      EXPECT_EQ(access_private::num_resource_required(*clause), 2);
    }

    // checking the 2nd rule of QNode3: if EnoughResource -> Purify
    {
      auto *rule = ruleset->rules.at(1).get();
      EXPECT_EQ(rule->name, "X purification with : 4");
      EXPECT_EQ(rule->ruleset_id, ruleset_id);
      ASSERT_EQ(rule->action_partners.size(), 1);
      EXPECT_EQ(rule->action_partners.at(0), 4);
      EXPECT_EQ(rule->next_action_partners.size(), 0);

      auto *action = dynamic_cast<PurifyAction *>(rule->action.get());
      EXPECT_NE(action, nullptr);
      EXPECT_EQ(access_private::rule_id(*action), rule->rule_index);
      EXPECT_EQ(access_private::ruleset_id(*action), ruleset_id);
      EXPECT_EQ(access_private::partner(*action), 4);
      EXPECT_EQ(access_private::X(*action), true);
      EXPECT_EQ(access_private::Z(*action), false);
      EXPECT_EQ(access_private::qnic_id(*action), 1);
      EXPECT_EQ(access_private::qnic_type(*action), QNIC_E);
      EXPECT_EQ(access_private::resource(*action), 0);
      EXPECT_EQ(access_private::trash_resource(*action), 1);
      EXPECT_EQ(access_private::action_index(*action), 0);
      EXPECT_EQ(access_private::purification_count(*action), 1);
      EXPECT_EQ(access_private::num_purify(*action), 1);

      ASSERT_EQ(rule->condition->clauses.size(), 1);
      auto *clause = dynamic_cast<EnoughResourceClause *>(rule->condition.get()->clauses.at(0));
      ASSERT_NE(clause, nullptr);
      EXPECT_EQ(access_private::partner(*clause), 4);
      EXPECT_EQ(access_private::num_resource_required(*clause), 2);
    }
    // checking the 3rd rule of QNode3: Wait QNode4
    {
      auto *rule = ruleset->rules.at(2).get();
      EXPECT_EQ(rule->name, "Wait rule with: 4");
      EXPECT_EQ(rule->ruleset_id, ruleset_id);
      ASSERT_EQ(rule->action_partners.size(), 1);
      EXPECT_EQ(rule->action_partners.at(0), 4);
      EXPECT_EQ(rule->next_action_partners.size(), 1);
      EXPECT_EQ(rule->next_action_partners.at(0), 5);

      ASSERT_EQ(rule->condition->clauses.size(), 1);
      EXPECT_NE(dynamic_cast<WaitClause *>(rule->condition->clauses.at(0)), nullptr);
      EXPECT_EQ(rule->action.get(), nullptr);
    }
    // checking the 4th rule of QNode3: if EnoughResorce -> Purify
    {
      auto *rule = ruleset->rules.at(3).get();
      EXPECT_EQ(rule->name, "X purification with : 5");
      EXPECT_EQ(rule->ruleset_id, ruleset_id);
      ASSERT_EQ(rule->action_partners.size(), 1);
      EXPECT_EQ(rule->action_partners.at(0), 5);
      EXPECT_EQ(rule->next_action_partners.size(), 0);

      auto *action = dynamic_cast<PurifyAction *>(rule->action.get());
      EXPECT_NE(action, nullptr);
      EXPECT_EQ(access_private::rule_id(*action), rule->rule_index);
      EXPECT_EQ(access_private::ruleset_id(*action), ruleset_id);
      EXPECT_EQ(access_private::partner(*action), 5);
      EXPECT_EQ(access_private::X(*action), true);
      EXPECT_EQ(access_private::Z(*action), false);
      EXPECT_EQ(access_private::qnic_id(*action), 1);
      EXPECT_EQ(access_private::qnic_type(*action), QNIC_E);
      EXPECT_EQ(access_private::resource(*action), 0);
      EXPECT_EQ(access_private::trash_resource(*action), 1);
      EXPECT_EQ(access_private::action_index(*action), 0);
      EXPECT_EQ(access_private::purification_count(*action), 1);
      EXPECT_EQ(access_private::num_purify(*action), 1);

      ASSERT_EQ(rule->condition->clauses.size(), 1);
      auto *clause = dynamic_cast<EnoughResourceClause *>(rule->condition.get()->clauses.at(0));
      ASSERT_NE(clause, nullptr);
      EXPECT_EQ(access_private::partner(*clause), 5);
      EXPECT_EQ(access_private::num_resource_required(*clause), 2);
    }

    // checking the 5th rule of QNode3: if EnoughResource -> Swapping
    {
      auto *rule = ruleset->rules.at(4).get();
      EXPECT_EQ(rule->name, "Entanglement Swapping with 2 : 5");
      EXPECT_EQ(rule->ruleset_id, ruleset_id);
      ASSERT_EQ(rule->action_partners.size(), 2);
      EXPECT_EQ(rule->action_partners.at(0), 2);
      EXPECT_EQ(rule->action_partners.at(1), 5);
      EXPECT_EQ(rule->next_action_partners.size(), 0);

      auto *action = dynamic_cast<SwappingAction *>(rule->action.get());
      EXPECT_NE(action, nullptr);
      EXPECT_EQ(access_private::left_partner(*action), 2);
      EXPECT_EQ(access_private::left_qnic_id(*action), 0);
      EXPECT_EQ(access_private::left_qnic_type(*action), QNIC_E);
      EXPECT_EQ(access_private::left_qnic_address(*action), 101);
      EXPECT_EQ(access_private::left_resource(*action), 0);
      EXPECT_EQ(access_private::self_left_qnic_id(*action), 0);
      EXPECT_EQ(access_private::self_left_qnic_type(*action), QNIC_E);

      EXPECT_EQ(access_private::right_partner(*action), 5);
      EXPECT_EQ(access_private::right_qnic_id(*action), 0);
      EXPECT_EQ(access_private::right_qnic_type(*action), QNIC_E);
      EXPECT_EQ(access_private::right_qnic_address(*action), 0);
      EXPECT_EQ(access_private::right_resource(*action), 0);
      EXPECT_EQ(access_private::self_right_qnic_id(*action), 1);
      EXPECT_EQ(access_private::self_right_qnic_type(*action), QNIC_E);

      ASSERT_EQ(rule->condition->clauses.size(), 2);
      auto *clause1 = dynamic_cast<EnoughResourceClause *>(rule->condition.get()->clauses.at(0));
      ASSERT_NE(clause1, nullptr);
      EXPECT_EQ(access_private::partner(*clause1), 2);
      EXPECT_EQ(access_private::num_resource_required(*clause1), 0);  // XXX: should be 1?
      auto *clause2 = dynamic_cast<EnoughResourceClause *>(rule->condition.get()->clauses.at(1));
      ASSERT_NE(clause2, nullptr);
      EXPECT_EQ(access_private::partner(*clause2), 5);
      EXPECT_EQ(access_private::num_resource_required(*clause2), 0);  // XXX: should be 1?
    }

    EXPECT_EQ(ruleset->rules.at(0)->next_rule_id, ruleset->rules.at(4)->rule_index);
    EXPECT_EQ(ruleset->rules.at(1)->next_rule_id, ruleset->rules.at(2)->rule_index);
    EXPECT_EQ(ruleset->rules.at(3)->next_rule_id, ruleset->rules.at(4)->rule_index);
    EXPECT_EQ(ruleset->rules.at(4)->next_rule_id, 0);
  }

  // checking the ruleset for QNode4
  {
    auto *packetFor4 = dynamic_cast<ConnectionSetupResponse *>(gate->messages[2]);
    ASSERT_NE(packetFor4, nullptr);
    EXPECT_EQ(packetFor4->getDestAddr(), 4);
    auto *ruleset = packetFor4->getRuleSet();
    ASSERT_NE(ruleset, nullptr);
    EXPECT_EQ(ruleset->size(), 3);
    EXPECT_EQ(ruleset->ruleset_id, ruleset_id);
    // EXPECT_EQ(packetFor4->getRuleSet_id(), ruleset_id);
    EXPECT_EQ(ruleset->entangled_partners.size(), 1);
    // EXPECT_EQ(ruleset->entangled_partners.at(0), 5); // always 0

    // checking the 1st rule of QNode4: if EnoughResource -> Purify
    {
      auto *rule = ruleset->rules.at(0).get();
      EXPECT_EQ(rule->name, "X purification with : 3");
      EXPECT_EQ(rule->ruleset_id, ruleset_id);
      ASSERT_EQ(rule->action_partners.size(), 1);
      EXPECT_EQ(rule->action_partners.at(0), 3);
      EXPECT_EQ(rule->next_action_partners.size(), 0);

      auto *action = dynamic_cast<PurifyAction *>(rule->action.get());
      EXPECT_NE(action, nullptr);
      EXPECT_EQ(access_private::rule_id(*action), rule->rule_index);
      EXPECT_EQ(access_private::ruleset_id(*action), ruleset_id);
      EXPECT_EQ(access_private::partner(*action), 3);
      EXPECT_EQ(access_private::X(*action), true);
      EXPECT_EQ(access_private::Z(*action), false);
      EXPECT_EQ(access_private::qnic_id(*action), 0);
      EXPECT_EQ(access_private::qnic_type(*action), QNIC_E);
      EXPECT_EQ(access_private::resource(*action), 0);
      EXPECT_EQ(access_private::trash_resource(*action), 1);
      EXPECT_EQ(access_private::action_index(*action), 0);
      EXPECT_EQ(access_private::purification_count(*action), 1);
      EXPECT_EQ(access_private::num_purify(*action), 1);

      ASSERT_EQ(rule->condition->clauses.size(), 1);
      auto *clause = dynamic_cast<EnoughResourceClause *>(rule->condition.get()->clauses.at(0));
      ASSERT_NE(clause, nullptr);
      EXPECT_EQ(access_private::partner(*clause), 3);
      EXPECT_EQ(access_private::num_resource_required(*clause), 2);
    }

    // checking the 2nd rule of QNode4: if EnoughResource -> Purify
    {
      auto *rule = ruleset->rules.at(1).get();
      EXPECT_EQ(rule->name, "X purification with : 5");
      EXPECT_EQ(rule->ruleset_id, ruleset_id);
      ASSERT_EQ(rule->action_partners.size(), 1);
      EXPECT_EQ(rule->action_partners.at(0), 5);
      EXPECT_EQ(rule->next_action_partners.size(), 0);

      auto *action = dynamic_cast<PurifyAction *>(rule->action.get());
      EXPECT_NE(action, nullptr);
      EXPECT_EQ(access_private::rule_id(*action), rule->rule_index);
      EXPECT_EQ(access_private::ruleset_id(*action), ruleset_id);
      EXPECT_EQ(access_private::partner(*action), 5);
      EXPECT_EQ(access_private::X(*action), true);
      EXPECT_EQ(access_private::Z(*action), false);
      EXPECT_EQ(access_private::qnic_id(*action), 0);
      EXPECT_EQ(access_private::qnic_type(*action), QNIC_E);
      EXPECT_EQ(access_private::resource(*action), 0);
      EXPECT_EQ(access_private::trash_resource(*action), 1);
      EXPECT_EQ(access_private::action_index(*action), 0);
      EXPECT_EQ(access_private::purification_count(*action), 1);
      EXPECT_EQ(access_private::num_purify(*action), 1);

      ASSERT_EQ(rule->condition->clauses.size(), 1);
      auto *clause = dynamic_cast<EnoughResourceClause *>(rule->condition.get()->clauses.at(0));
      ASSERT_NE(clause, nullptr);
      EXPECT_EQ(access_private::partner(*clause), 5);
      EXPECT_EQ(access_private::num_resource_required(*clause), 2);
    }

    // checking the 3rd rule of QNode4: if EnoughResource -> Swapping
    {
      auto *rule = ruleset->rules.at(2).get();
      EXPECT_EQ(rule->name, "Entanglement Swapping with 3 : 5");
      EXPECT_EQ(rule->ruleset_id, ruleset_id);
      ASSERT_EQ(rule->action_partners.size(), 2);
      EXPECT_EQ(rule->action_partners.at(0), 3);
      EXPECT_EQ(rule->action_partners.at(1), 5);
      EXPECT_EQ(rule->next_action_partners.size(), 0);

      auto *action = dynamic_cast<SwappingAction *>(rule->action.get());
      EXPECT_NE(action, nullptr);
      EXPECT_EQ(access_private::left_partner(*action), 3);
      EXPECT_EQ(access_private::left_qnic_id(*action), 1);
      EXPECT_EQ(access_private::left_qnic_type(*action), QNIC_E);
      EXPECT_EQ(access_private::left_qnic_address(*action), 105);
      EXPECT_EQ(access_private::left_resource(*action), 0);
      EXPECT_EQ(access_private::self_left_qnic_id(*action), 0);
      EXPECT_EQ(access_private::self_left_qnic_type(*action), QNIC_E);

      EXPECT_EQ(access_private::right_partner(*action), 5);
      EXPECT_EQ(access_private::right_qnic_id(*action), 0);
      EXPECT_EQ(access_private::right_qnic_type(*action), QNIC_E);
      EXPECT_EQ(access_private::right_qnic_address(*action), 0);  // XXX: why not
      EXPECT_EQ(access_private::right_resource(*action), 0);
      EXPECT_EQ(access_private::self_right_qnic_id(*action), 0);
      EXPECT_EQ(access_private::self_right_qnic_type(*action), QNIC_E);

      ASSERT_EQ(rule->condition->clauses.size(), 2);
      auto *clause1 = dynamic_cast<EnoughResourceClause *>(rule->condition.get()->clauses.at(0));
      ASSERT_NE(clause1, nullptr);
      EXPECT_EQ(access_private::partner(*clause1), 3);
      EXPECT_EQ(access_private::num_resource_required(*clause1), 0);
      auto *clause2 = dynamic_cast<EnoughResourceClause *>(rule->condition.get()->clauses.at(1));
      ASSERT_NE(clause2, nullptr);
      EXPECT_EQ(access_private::partner(*clause2), 5);
      EXPECT_EQ(access_private::num_resource_required(*clause2), 0);
    }

    EXPECT_EQ(ruleset->rules.at(0)->next_rule_id, ruleset->rules.at(2)->rule_index);
    EXPECT_EQ(ruleset->rules.at(1)->next_rule_id, ruleset->rules.at(2)->rule_index);
    EXPECT_EQ(ruleset->rules.at(2)->next_rule_id, 0);
  }

  // checking the ruleset for QNode5
  {
    auto *packetFor5 = dynamic_cast<ConnectionSetupResponse *>(gate->messages[3]);
    ASSERT_NE(packetFor5, nullptr);
    EXPECT_EQ(packetFor5->getDestAddr(), 5);
    auto *ruleset = packetFor5->getRuleSet();
    ASSERT_NE(ruleset, nullptr);
    EXPECT_EQ(ruleset->size(), 6);
    EXPECT_EQ(ruleset->ruleset_id, ruleset_id);
    // EXPECT_EQ(packetFor5->getRuleSet_id(), ruleset_id);
    EXPECT_EQ(ruleset->entangled_partners.size(), 1);
    // EXPECT_EQ(ruleset->entangled_partners.at(0), 5); // always 0

    // checking the 1st rule of QNode5: if EnoughResource -> Purify
    {
      auto *rule = ruleset->rules.at(0).get();
      EXPECT_EQ(rule->name, "X purification with : 4");
      EXPECT_EQ(rule->ruleset_id, ruleset_id);
      ASSERT_EQ(rule->action_partners.size(), 1);
      EXPECT_EQ(rule->action_partners.at(0), 4);
      EXPECT_EQ(rule->next_action_partners.size(), 0);

      auto *action = dynamic_cast<PurifyAction *>(rule->action.get());
      EXPECT_NE(action, nullptr);
      EXPECT_EQ(access_private::rule_id(*action), rule->rule_index);
      EXPECT_EQ(access_private::ruleset_id(*action), ruleset_id);
      EXPECT_EQ(access_private::partner(*action), 4);
      EXPECT_EQ(access_private::X(*action), true);
      EXPECT_EQ(access_private::Z(*action), false);
      EXPECT_EQ(access_private::qnic_id(*action), 0);
      EXPECT_EQ(access_private::qnic_type(*action), QNIC_E);
      EXPECT_EQ(access_private::resource(*action), 0);
      EXPECT_EQ(access_private::trash_resource(*action), 1);
      EXPECT_EQ(access_private::action_index(*action), 0);
      EXPECT_EQ(access_private::purification_count(*action), 1);
      EXPECT_EQ(access_private::num_purify(*action), 1);

      ASSERT_EQ(rule->condition->clauses.size(), 1);
      auto *clause = dynamic_cast<EnoughResourceClause *>(rule->condition.get()->clauses.at(0));
      ASSERT_NE(clause, nullptr);
      EXPECT_EQ(access_private::partner(*clause), 4);
      EXPECT_EQ(access_private::num_resource_required(*clause), 2);
    }

    // checking the 2nd rule of QNode5: Wait QNode4
    {
      auto *rule = ruleset->rules.at(1).get();
      EXPECT_EQ(rule->name, "Wait rule with: 4");
      EXPECT_EQ(rule->ruleset_id, ruleset_id);
      ASSERT_EQ(rule->action_partners.size(), 1);
      EXPECT_EQ(rule->action_partners.at(0), 4);
      EXPECT_EQ(rule->next_action_partners.size(), 1);
      EXPECT_EQ(rule->next_action_partners.at(0), 3);

      ASSERT_EQ(rule->condition->clauses.size(), 1);
      EXPECT_NE(dynamic_cast<WaitClause *>(rule->condition->clauses.at(0)), nullptr);
      EXPECT_EQ(rule->action.get(), nullptr);
    }

    // checking the 3rd rule of QNode5: if EnoughResource -> Purify
    {
      auto *rule = ruleset->rules.at(2).get();
      EXPECT_EQ(rule->name, "X purification with : 3");
      EXPECT_EQ(rule->ruleset_id, ruleset_id);
      ASSERT_EQ(rule->action_partners.size(), 1);
      EXPECT_EQ(rule->action_partners.at(0), 3);
      EXPECT_EQ(rule->next_action_partners.size(), 0);

      auto *action = dynamic_cast<PurifyAction *>(rule->action.get());
      EXPECT_NE(action, nullptr);
      EXPECT_EQ(access_private::rule_id(*action), rule->rule_index);
      EXPECT_EQ(access_private::ruleset_id(*action), ruleset_id);
      EXPECT_EQ(access_private::partner(*action), 3);
      EXPECT_EQ(access_private::X(*action), true);
      EXPECT_EQ(access_private::Z(*action), false);
      EXPECT_EQ(access_private::qnic_id(*action), 0);
      EXPECT_EQ(access_private::qnic_type(*action), QNIC_E);
      EXPECT_EQ(access_private::resource(*action), 0);
      EXPECT_EQ(access_private::trash_resource(*action), 1);
      EXPECT_EQ(access_private::action_index(*action), 0);
      EXPECT_EQ(access_private::purification_count(*action), 1);
      EXPECT_EQ(access_private::num_purify(*action), 1);

      ASSERT_EQ(rule->condition->clauses.size(), 1);
      auto *clause = dynamic_cast<EnoughResourceClause *>(rule->condition.get()->clauses.at(0));
      ASSERT_NE(clause, nullptr);
      EXPECT_EQ(access_private::partner(*clause), 3);
      EXPECT_EQ(access_private::num_resource_required(*clause), 2);
    }
    // checking the 4th rule of QNode5: Wait QNode3
    {
      auto *rule = ruleset->rules.at(3).get();
      EXPECT_EQ(rule->name, "Wait rule with: 3");
      EXPECT_EQ(rule->ruleset_id, ruleset_id);
      ASSERT_EQ(rule->action_partners.size(), 1);
      EXPECT_EQ(rule->action_partners.at(0), 3);
      EXPECT_EQ(rule->next_action_partners.size(), 1);
      EXPECT_EQ(rule->next_action_partners.at(0), 2);

      ASSERT_EQ(rule->condition->clauses.size(), 1);
      EXPECT_NE(dynamic_cast<WaitClause *>(rule->condition->clauses.at(0)), nullptr);
      EXPECT_EQ(rule->action.get(), nullptr);
    }

    // checking the 5th rule of QNode5: if EnoughResource -> Purify
    {
      auto *rule = ruleset->rules.at(4).get();
      EXPECT_EQ(rule->name, "X purification with : 2");
      EXPECT_EQ(rule->ruleset_id, ruleset_id);
      ASSERT_EQ(rule->action_partners.size(), 1);
      EXPECT_EQ(rule->action_partners.at(0), 2);
      EXPECT_EQ(rule->next_action_partners.size(), 0);

      auto *action = dynamic_cast<PurifyAction *>(rule->action.get());
      EXPECT_NE(action, nullptr);
      EXPECT_EQ(access_private::rule_id(*action), rule->rule_index);
      EXPECT_EQ(access_private::ruleset_id(*action), ruleset_id);
      EXPECT_EQ(access_private::partner(*action), 2);
      EXPECT_EQ(access_private::X(*action), true);
      EXPECT_EQ(access_private::Z(*action), false);
      EXPECT_EQ(access_private::qnic_id(*action), 0);
      EXPECT_EQ(access_private::qnic_type(*action), QNIC_E);
      EXPECT_EQ(access_private::resource(*action), 0);
      EXPECT_EQ(access_private::trash_resource(*action), 1);
      EXPECT_EQ(access_private::action_index(*action), 0);
      EXPECT_EQ(access_private::purification_count(*action), 1);
      EXPECT_EQ(access_private::num_purify(*action), 1);

      ASSERT_EQ(rule->condition->clauses.size(), 1);
      auto *clause = dynamic_cast<EnoughResourceClause *>(rule->condition.get()->clauses.at(0));
      ASSERT_NE(clause, nullptr);
      EXPECT_EQ(access_private::partner(*clause), 2);
      EXPECT_EQ(access_private::num_resource_required(*clause), 2);
    }

    // checking the 6th rule of QNode5: if EnoughResource -> Swapping
    {
      auto *rule = ruleset->rules.at(5).get();
      EXPECT_EQ(rule->name, "tomography");
      EXPECT_EQ(rule->ruleset_id, ruleset_id);
      ASSERT_EQ(rule->action_partners.size(), 1);
      // action partner must be the qnode2(initiator)
      // last action is the tomography with the opposite end qnode
      EXPECT_EQ(rule->action_partners.at(0), 2);
      EXPECT_EQ(rule->next_action_partners.size(), 0);

      auto *action = dynamic_cast<RandomMeasureAction *>(rule->action.get());
      EXPECT_NE(action, nullptr);
      EXPECT_EQ(access_private::partner(*action), 2);
      EXPECT_EQ(access_private::qnic_id(*action), 0);
      EXPECT_EQ(access_private::qnic_type(*action), QNIC_E);
      EXPECT_EQ(access_private::resource(*action), 0);
      EXPECT_EQ(access_private::src(*action), 5);
      EXPECT_EQ(access_private::dst(*action), 2);
      EXPECT_EQ(access_private::current_count(*action), 0);
      EXPECT_EQ(access_private::max_count(*action), 0);  // XXX: is it right?

      ASSERT_EQ(rule->condition->clauses.size(), 2);
      auto *measure_count_clause = dynamic_cast<MeasureCountClause *>(rule->condition.get()->clauses.at(0));
      ASSERT_NE(measure_count_clause, nullptr);
      auto *enough_res_clause = dynamic_cast<EnoughResourceClause *>(rule->condition.get()->clauses.at(1));
      ASSERT_NE(enough_res_clause, nullptr);
      EXPECT_EQ(access_private::partner(*enough_res_clause), 2);
      EXPECT_EQ(access_private::num_resource_required(*enough_res_clause), 1);
    }

    EXPECT_EQ(ruleset->rules.at(0)->next_rule_id, ruleset->rules.at(1)->rule_index);
    EXPECT_EQ(ruleset->rules.at(1)->next_rule_id, ruleset->rules.at(2)->rule_index);
    EXPECT_EQ(ruleset->rules.at(2)->next_rule_id, ruleset->rules.at(3)->rule_index);
    EXPECT_EQ(ruleset->rules.at(3)->next_rule_id, ruleset->rules.at(4)->rule_index);
    EXPECT_EQ(ruleset->rules.at(4)->next_rule_id, ruleset->rules.at(5)->rule_index);
    EXPECT_EQ(ruleset->rules.at(5)->next_rule_id, 0);
  }
  delete routing_daemon;
  delete hardware_monitor;
}

TEST(ConnectionManagerTest, GetQNICInterface) {
  ConnectionManagerTestTarget c;
  ASSERT_EQ(c.par("address").intValue(), 123);
}
}  // namespace

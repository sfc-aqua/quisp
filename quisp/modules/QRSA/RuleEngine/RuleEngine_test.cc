#include <cstddef>
#include <memory>
#include <utility>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>

#include "BellPairStore/BellPairStore.h"
#include "IRuleEngine.h"
#include "QubitRecord/QubitRecord.h"
#include "RuleEngine.h"
#include "messages/barrier_messages_m.h"
#include "messages/link_allocation_update_messages_m.h"
#include "messages/purification_messages_m.h"
#include "modules/Logger/DisabledLogger.h"
#include "modules/QNIC.h"
#include "modules/QNIC/StationaryQubit/IStationaryQubit.h"
#include "modules/QRSA/HardwareMonitor/IHardwareMonitor.h"
#include "modules/QRSA/QRSA.h"
#include "modules/QRSA/RealTimeController/IRealTimeController.h"
#include "modules/QRSA/RoutingDaemon/RoutingDaemon.h"
#include "rules/Action.h"
#include "rules/Rule.h"
#include "rules/RuleSet.h"
#include "runtime/RuleSet.h"
#include "runtime/Runtime.h"
#include "runtime/opcode.h"
#include "runtime/test.h"
#include "runtime/types.h"
#include "test_utils/TestUtilFunctions.h"
#include "test_utils/TestUtils.h"
#include "test_utils/mock_modules/MockHardwareMonitor.h"
#include "test_utils/mock_modules/MockRealTimeController.h"
#include "test_utils/mock_modules/MockRoutingDaemon.h"

namespace {

using namespace omnetpp;
using namespace quisp::utils;
using namespace quisp::rules;
using namespace quisp::modules;
using namespace quisp::messages;
using quisp::modules::qrsa::IQubitRecord;
using quisp::modules::qubit_record::QubitRecord;
using namespace quisp_test;
using namespace testing;
using quisp::modules::Logger::DisabledLogger;
using quisp::runtime::InstructionTypes;
using quisp::runtime::Program;
using quisp::runtime::QNodeAddr;
using quisp::runtime::Runtime;

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy() : mockQubit(nullptr), routingDaemon(nullptr), hardwareMonitor(nullptr) {}
  Strategy(IStationaryQubit* _qubit, MockRoutingDaemon* routing_daemon, MockHardwareMonitor* hardware_monitor, MockRealTimeController* realtime_controller,
           std::vector<QNicSpec> qnic_specs)
      : TestComponentProviderStrategy(qnic_specs), mockQubit(_qubit), routingDaemon(routing_daemon), hardwareMonitor(hardware_monitor), realtimeController(realtime_controller) {}
  ~Strategy() {
    delete mockQubit;
    delete routingDaemon;
    delete hardwareMonitor;
    delete realtimeController;
  }
  int getNodeAddr() override { return 5; };
  IStationaryQubit* mockQubit = nullptr;
  MockRoutingDaemon* routingDaemon = nullptr;
  MockHardwareMonitor* hardwareMonitor = nullptr;
  MockRealTimeController* realtimeController = nullptr;
  IStationaryQubit* getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) override {
    if (mockQubit == nullptr) mockQubit = new MockQubit(QNIC_E, 1);
    return mockQubit;
  };
  IRoutingDaemon* getRoutingDaemon() override { return routingDaemon; };
  IHardwareMonitor* getHardwareMonitor() override { return hardwareMonitor; };
  IRealTimeController* getRealTimeController() override { return realtimeController; };
  ILogger* getLogger() override { return new DisabledLogger{}; }
};

class RuleEngineTestTarget : public quisp::modules::RuleEngine {
 public:
  using quisp::modules::RuleEngine::handlePurificationResult;
  using quisp::modules::RuleEngine::handleSwappingResult;
  using quisp::modules::RuleEngine::initialize;
  using quisp::modules::RuleEngine::par;
  using quisp::modules::RuleEngine::qnic_store;
  using quisp::modules::RuleEngine::runtimes;

  RuleEngineTestTarget(IStationaryQubit* mockQubit, MockRoutingDaemon* routingdaemon, MockHardwareMonitor* hardware_monitor, MockRealTimeController* realtime_controller,
                       std::vector<QNicSpec> qnic_specs = {})
      : quisp::modules::RuleEngine(), toRouterGate(new TestGate(this, "RouterPort$o")) {
    setParInt(this, "address", 2);
    setParInt(this, "number_of_qnics_rp", 0);
    setParInt(this, "number_of_qnics_r", 1);
    setParInt(this, "number_of_qnics", 1);
    setParInt(this, "total_number_of_qnics", 2);
    setName("rule_engine_test_target");
    provider.setStrategy(std::make_unique<Strategy>(mockQubit, routingdaemon, hardware_monitor, realtime_controller, qnic_specs));
    setComponentType(new TestModuleType("rule_engine_test"));
    qnic_store = std::make_unique<StrictMock<MockQNicStore>>();
  }
  // setter function for allResorces[qnic_type][qnic_index]
  void setAllResources(int partner_addr, IQubitRecord* qubit) { this->bell_pair_store.insertEntangledQubit(partner_addr, qubit); };
  cGate *gate(const char *gatename, int index = -1) {
    if (strcmp(gatename, "RouterPort$o") != 0) {
      throw cRuntimeError("unknown gate called");
    }
    return toRouterGate;
  }
  TestGate *toRouterGate;
  private:
    FRIEND_TEST(RuleEngineTest, ESResourceUpdate);
    FRIEND_TEST(RuleEngineTest, trackerUpdate);
    friend class MockRoutingDaemon;
    friend class MockHardwareMonitor;
};

class RuleEngineTest : public testing::Test {
 protected:
  void SetUp() {
    sim = prepareSimulation();
    routing_daemon = new MockRoutingDaemon;
    hardware_monitor = new MockHardwareMonitor;
    realtime_controller = new MockRealTimeController;
  }
  void TearDown() {
    delete routing_daemon;
    delete hardware_monitor;
    delete realtime_controller;
  }
  utils::TestSimulation* sim;
  MockRoutingDaemon* routing_daemon;
  MockHardwareMonitor* hardware_monitor;
  MockRealTimeController* realtime_controller;
}; 

// specifier for qnics in order to create qnic_record and qubit_record.
static const std::vector<QNicSpec> qnic_specs = {{QNIC_E, 0, 2}, {QNIC_R, 0, 2}};

TEST_F(RuleEngineTest, resourceAllocation) {
  auto logger = std::make_unique<DisabledLogger>();
  auto* qubit_record0 = new QubitRecord(QNIC_E, 3, 0, logger.get());
  auto* qubit_record1 = new QubitRecord(QNIC_E, 3, 1, logger.get());
  auto* qubit_record2 = new QubitRecord(QNIC_E, 3, 2, logger.get());
  auto rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, nullptr, qnic_specs};
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  rule_engine->setAllResources(0, qubit_record0);
  rule_engine->setAllResources(1, qubit_record1);
  rule_engine->setAllResources(2, qubit_record2);
  int q0 = 0;
  QNodeAddr partner_addr{1};
  // this action needs a resource qubit that is entangled with partner 1.
  Program test_action{"testAction", {quisp::runtime::INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner_addr, 0}}}};
  Program empty_condition{"emptyCondition", {}};
  auto rs = quisp::runtime::RuleSet{"test rs", {quisp::runtime::Rule{"test", -1, -1, empty_condition, test_action}}};
  auto runtime = quisp::runtime::Runtime{};
  rule_engine->runtimes.acceptRuleSet(rs);

  rule_engine->ResourceAllocation(QNIC_E, 3);
  EXPECT_TRUE(qubit_record1->isAllocated());

  // resource allocation assigns a corresponding qubit to action's resource
  auto& rt = rule_engine->runtimes.at(0);
  EXPECT_EQ(rt.ruleset.rules.size(), 1);
  EXPECT_EQ(rt.qubits.size(), 1);
}

TEST_F(RuleEngineTest, freeResourceFromRuleSet) {
  auto logger = std::make_unique<DisabledLogger>();
  auto* qubit_record0 = new QubitRecord(QNIC_E, 3, 0, logger.get());
  auto* qubit_record1 = new QubitRecord(QNIC_E, 3, 1, logger.get());
  auto* qubit_record2 = new QubitRecord(QNIC_E, 3, 2, logger.get());
  auto rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, nullptr, qnic_specs};
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  rule_engine->setAllResources(0, qubit_record0);
  rule_engine->setAllResources(1, qubit_record1);
  rule_engine->setAllResources(2, qubit_record2);
  int q0 = 0;
  QNodeAddr partner_addr{1};
  // this action needs a resource qubit that is entangled with partner 1.
  Program test_action{"testAction", {quisp::runtime::INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner_addr, 0}}}};
  Program empty_condition{"emptyCondition", {}};
  auto rs = quisp::runtime::RuleSet{"test rs", {quisp::runtime::Rule{"test", -1, -1, empty_condition, test_action}}};
  auto runtime = quisp::runtime::Runtime{};
  rule_engine->runtimes.acceptRuleSet(rs);

  rule_engine->ResourceAllocation(QNIC_E, 3);
  EXPECT_TRUE(qubit_record1->isAllocated());

  rule_engine->freeResourceFromRuleSet(QNIC_E, 3, rs.id);
  EXPECT_FALSE(qubit_record1->isAllocated());

  // A qubit allocated to a particular action is now successfully released
  auto& rt = rule_engine->runtimes.at(0);
  EXPECT_EQ(rt.ruleset.rules.size(), 1);
  EXPECT_EQ(rt.qubits.size(), 0);
}

TEST_F(RuleEngineTest, freeConsumedResource) {
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller};
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  int qnic_index = 7;
  auto logger = std::make_unique<DisabledLogger>();
  auto* qubit = new MockQubit(QNIC_E, qnic_index);
  auto* qubit_record = new QubitRecord(QNIC_E, qnic_index, 1, logger.get());
  qubit_record->setBusy(true);
  qubit->fillParams();

  EXPECT_CALL(*realtime_controller, ReInitialize_StationaryQubit(qubit_record, false)).Times(1).WillOnce(Return());
  EXPECT_CALL(*dynamic_cast<MockQNicStore*>(rule_engine->qnic_store.get()), getQubitRecord(QNIC_E, qnic_index, 1)).Times(1).WillOnce(Return(qubit_record));
  rule_engine->freeConsumedResource(qnic_index, qubit, QNIC_E);
  EXPECT_FALSE(qubit_record->isBusy());
  delete qubit;
  delete rule_engine->qnic_store.get();
}

TEST_F(RuleEngineTest, handleInternalConnectionTeardownInfoForwarding) {
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller};
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();

  auto *pkt = new InternalConnectionTeardownInfoForwarding();
  pkt->setNext_destAddr(1);
  rule_engine->handleInternalConnectionTeardownInfoForwarding(pkt);
  EXPECT_EQ(rule_engine->qnode_indices, vector<int>{1});
}

TEST_F(RuleEngineTest, getRoleFromInternalConnectionTeardownMessage) {
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller};
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();

  auto *pkt = new InternalConnectionTeardownMessage();
  pkt->setRole("SEND");
  auto role = rule_engine->getRoleFromInternalConnectionTeardownMessage(pkt);
  EXPECT_EQ(role, "SEND");
}

TEST_F(RuleEngineTest, sendLinkAllocationUpdateDecisionRequest) {
  auto *sim = prepareSimulation();
  auto *routing_daemon = new MockRoutingDaemon();
  auto *hardware_monitor = new MockHardwareMonitor();
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller};
  sim->registerComponent(rule_engine);
  sim->setContext(rule_engine);
  rule_engine->callInitialize();

  int q0 = 0;
  QNodeAddr partner_addr{1};
  Program test_action{"testAction", {quisp::runtime::INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner_addr, 0}}}};
  Program empty_condition{"emptyCondition", {}};
  auto rs = quisp::runtime::RuleSet{"test rs", {quisp::runtime::Rule{"test", -1, -1, empty_condition, test_action}}};
  rs.id = 1;
  rule_engine->runtimes.acceptRuleSet(rs);

  auto *msg = new InternalConnectionTeardownMessage();
  msg->setNext_destAddr(1);
  msg->setRuleSet_id(111);
  rule_engine->sendLinkAllocationUpdateDecisionRequest(msg);
  auto gate = rule_engine->toRouterGate;
  EXPECT_EQ(gate->messages.size(), 1);

  auto pkt = dynamic_cast<LinkAllocationUpdateDecisionRequest *>(gate->messages[0]);
  EXPECT_EQ(pkt->getSrcAddr(), 5);
  EXPECT_EQ(pkt->getDestAddr(), 1);
  EXPECT_EQ(pkt->getCurrentRuleSet_id(), 111);
  EXPECT_EQ(pkt->getOffered_ruleset_idsArraySize(), 2);
  EXPECT_EQ(pkt->getOfferedRuleSet_ids(0), 0);
  EXPECT_EQ(pkt->getOfferedRuleSet_ids(1), 1);
}

TEST_F(RuleEngineTest, sendLinkAllocationUpdateDecisionResponse) {
  auto *sim = prepareSimulation();
  auto *routing_daemon = new MockRoutingDaemon();
  auto *hardware_monitor = new MockHardwareMonitor();
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller};
  sim->registerComponent(rule_engine);
  sim->setContext(rule_engine);
  rule_engine->callInitialize();

  auto *msg = new LinkAllocationUpdateDecisionRequest();
  msg->setSrcAddr(1);
  msg->setDestAddr(2);
  msg->setCurrentRuleSet_id(111);
  msg->setOffered_ruleset_idsArraySize(1);
  msg->appendOffered_ruleset_ids(112);
  rule_engine->sendLinkAllocationUpdateDecisionResponse(msg);
  auto gate = rule_engine->toRouterGate;
  EXPECT_EQ(gate->messages.size(), 1);

  auto pkt = dynamic_cast<LinkAllocationUpdateDecisionResponse *>(gate->messages[0]);
  EXPECT_EQ(pkt->getSrcAddr(), 2);
  EXPECT_EQ(pkt->getDestAddr(), 1);
  EXPECT_EQ(pkt->getCurrentRuleSet_id(), 111);
  EXPECT_EQ(pkt->getNegotiatedRuleset_id(), 112);
}


TEST_F(RuleEngineTest, sendBarrierMessage){
  auto *sim = prepareSimulation();
  auto *routing_daemon = new MockRoutingDaemon();
  auto *hardware_monitor = new MockHardwareMonitor();
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller};
  sim->registerComponent(rule_engine);
  sim->setContext(rule_engine);
  rule_engine->callInitialize();

  auto *msg = new LinkAllocationUpdateDecisionResponse();
  msg->setSrcAddr(1);
  msg->setDestAddr(2);
  msg->setNegotiatedRuleset_id(111);

  auto logger = std::make_unique<DisabledLogger>();
  auto *qubit_record = new QubitRecord(QNIC_E, 3, 0, logger.get());;
  auto sequence_number = 0;
  auto is_last = false;

  rule_engine->sendBarrierMessage(msg, qubit_record, sequence_number, is_last);
  auto gate = rule_engine->toRouterGate;
  EXPECT_EQ(gate->messages.size(), 1);

  auto pkt = dynamic_cast<BarrierMessage *>(gate->messages[0]);
  EXPECT_EQ(pkt->getSrcAddr(), 2);
  EXPECT_EQ(pkt->getDestAddr(), 1);
  EXPECT_EQ(pkt->getNegotiatedRuleset_id(), 111);
  EXPECT_EQ(pkt->getQubitRecord(), qubit_record);
  EXPECT_EQ(pkt->getSequence_number(), 0);
  EXPECT_STREQ(pkt->getRole(), "SEND");
  EXPECT_EQ(pkt->getIs_last(), false);
}

TEST_F(RuleEngineTest, sendBarrierMessageAck){
  auto *sim = prepareSimulation();
  auto *routing_daemon = new MockRoutingDaemon();
  auto *hardware_monitor = new MockHardwareMonitor();
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller};
  sim->registerComponent(rule_engine);
  sim->setContext(rule_engine);
  rule_engine->callInitialize();

  auto *msg = new BarrierMessage();
  msg->setSrcAddr(1);
  msg->setDestAddr(2);
  msg->setNegotiatedRuleset_id(111);

  auto logger = std::make_unique<DisabledLogger>();
  auto *qubit_record = new QubitRecord(QNIC_E, 3, 0, logger.get());;
  msg->setQubitRecord(qubit_record);
  msg->setSequence_number(0);

  rule_engine->sendBarrierMessageAck(msg);
  auto gate = rule_engine->toRouterGate;
  EXPECT_EQ(gate->messages.size(), 1);

  auto pkt = dynamic_cast<BarrierMessage *>(gate->messages[0]);
  EXPECT_EQ(pkt->getSrcAddr(), 2);
  EXPECT_EQ(pkt->getDestAddr(), 1);
  EXPECT_EQ(pkt->getNegotiatedRuleset_id(), 111);
  EXPECT_EQ(pkt->getSequence_number(), 1);
  EXPECT_STREQ(pkt->getRole(), "ACK");
}

}  // namespace

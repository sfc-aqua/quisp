#include <cstddef>
#include <map>
#include <memory>
#include <utility>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>

#include "BellPairStore/BellPairStore.h"
#include "IRuleEngine.h"
#include "QubitRecord/QubitRecord.h"
#include "RuleEngine.h"
#include "gtest/gtest-death-test.h"
#include "gtest/gtest_pred_impl.h"
#include "messages/barrier_messages_m.h"
#include "messages/connection_teardown_messages_m.h"
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
#include "runtime/InstructionVisitor.h"
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
using namespace quisp::runtime;
using namespace quisp::modules;
using namespace quisp::messages;
using quisp::modules::qrsa::IQubitRecord;
using quisp::modules::qubit_record::QubitRecord;
using namespace quisp_test;
using namespace testing;
using quisp::modules::PartnerAddrQubitMapRange;
using quisp::modules::Logger::DisabledLogger;
using quisp::runtime::InstructionTypes;
using quisp::runtime::Program;
using quisp::runtime::QNodeAddr;
using quisp::runtime::Rule;
using quisp::runtime::RuleSet;
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
  cGate* gate(const char* gatename, int index = -1) {
    if (strcmp(gatename, "RouterPort$o") != 0) {
      throw cRuntimeError("unknown gate called");
    }
    return toRouterGate;
  }
  TestGate* toRouterGate;

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

TEST_F(RuleEngineTest, getAllocatedResourceToRuleSet) {
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
  rs.id = 1;
  rule_engine->runtimes.acceptRuleSet(rs);
  rule_engine->ResourceAllocation(QNIC_E, 3);

  auto qubit_record_list = rule_engine->getAllocatedResourceToRuleSet(QNIC_E, 3, 1);
  EXPECT_EQ(qubit_record_list, std::vector<IQubitRecord*>{qubit_record1});
}

TEST_F(RuleEngineTest, sendConnectionTeardownMessageForRuleSet) {
  auto* sim = prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon();
  auto* hardware_monitor = new MockHardwareMonitor();
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller};
  sim->registerComponent(rule_engine);
  sim->setContext(rule_engine);
  rule_engine->callInitialize();

  auto ruleset_id = 1;
  rule_engine->ruleset_id_node_addresses_along_path_map[ruleset_id].push_back(5);
  rule_engine->ruleset_id_node_addresses_along_path_map[ruleset_id].push_back(1);

  rule_engine->sendConnectionTeardownMessageForRuleSet(ruleset_id);
  auto gate = rule_engine->toRouterGate;
  EXPECT_EQ(gate->messages.size(), 2);

  auto pkt1 = dynamic_cast<ConnectionTeardownMessage*>(gate->messages[0]);
  EXPECT_EQ(pkt1->getSrcAddr(), 5);
  EXPECT_EQ(pkt1->getDestAddr(), 5);
  EXPECT_EQ(pkt1->getActual_srcAddr(), 5);
  EXPECT_EQ(pkt1->getActual_destAddr(), 5);
  EXPECT_EQ(pkt1->getRuleSet_id(), 1);
  EXPECT_EQ(pkt1->getLAU_req_srcAddr(), 5);
  EXPECT_EQ(pkt1->getLAU_req_destAddr(), 1);

  auto pkt2 = dynamic_cast<ConnectionTeardownMessage*>(gate->messages[1]);
  EXPECT_EQ(pkt2->getSrcAddr(), 5);
  EXPECT_EQ(pkt2->getDestAddr(), 1);
  EXPECT_EQ(pkt2->getActual_srcAddr(), 5);
  EXPECT_EQ(pkt2->getActual_destAddr(), 1);
  EXPECT_EQ(pkt2->getRuleSet_id(), 1);
  EXPECT_EQ(pkt2->getLAU_req_srcAddr(), 1);
  EXPECT_EQ(pkt2->getLAU_req_destAddr(), -1);
}

TEST_F(RuleEngineTest, sendBarrierMessageAck) {
  auto* sim = prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon();
  auto* hardware_monitor = new MockHardwareMonitor();
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller};
  sim->registerComponent(rule_engine);
  sim->setContext(rule_engine);
  rule_engine->callInitialize();

  auto* msg = new BarrierMessage();
  msg->setSrcAddr(1);
  msg->setDestAddr(2);
  msg->setNegotiatedRuleset_id(111);

  auto logger = std::make_unique<DisabledLogger>();
  auto* qubit_record = new QubitRecord(QNIC_E, 3, 0, logger.get());
  ;
  msg->setQubitRecord(qubit_record);
  msg->setSequence_number(0);

  rule_engine->sendBarrierMessageAck(msg);
  auto gate = rule_engine->toRouterGate;
  EXPECT_EQ(gate->messages.size(), 1);

  auto pkt = dynamic_cast<BarrierMessage*>(gate->messages[0]);
  EXPECT_EQ(pkt->getSrcAddr(), 2);
  EXPECT_EQ(pkt->getDestAddr(), 1);
  EXPECT_EQ(pkt->getNegotiatedRuleSet_id(), 111);
  EXPECT_EQ(pkt->getQubitRecord(), qubit_record);
  EXPECT_EQ(pkt->getSequence_number(), 1);
  EXPECT_EQ(pkt->getIs_sender(), false);
}

TEST_F(RuleEngineTest, sendLinkAllocationUpdateMessage) {
  auto* sim = prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon();
  auto* hardware_monitor = new MockHardwareMonitor();
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller};
  sim->registerComponent(rule_engine);
  sim->setContext(rule_engine);
  rule_engine->callInitialize();

  auto* msg = new BarrierMessage();
  msg->setSrcAddr(1);
  msg->setDestAddr(2);
  msg->setNegotiatedRuleset_id(111);
  msg->setIs_last(true);

  auto logger = std::make_unique<DisabledLogger>();
  auto* qubit_record = new QubitRecord(QNIC_E, 3, 0, logger.get());
  ;
  msg->setQubitRecord(qubit_record);
  msg->setSequence_number(1);

  rule_engine->sendLinkAllocationUpdateMessage(msg);
  auto gate = rule_engine->toRouterGate;
  EXPECT_EQ(gate->messages.size(), 1);

  auto pkt = dynamic_cast<LinkAllocationUpdateMessage*>(gate->messages[0]);
  EXPECT_EQ(pkt->getSrcAddr(), 2);
  EXPECT_EQ(pkt->getDestAddr(), 1);
  EXPECT_EQ(pkt->getNegotiatedRuleSet_id(), 111);
}

TEST_F(RuleEngineTest, sendLinkAllocationUpdateMessage) {
  auto* sim = prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon();
  auto* hardware_monitor = new MockHardwareMonitor();
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller};
  sim->registerComponent(rule_engine);
  sim->setContext(rule_engine);
  rule_engine->callInitialize();

  auto* msg = new LinkAllocationUpdateMessage();
  msg->setSrcAddr(1);
  msg->setDestAddr(2);
  msg->setNegotiatedRuleSet_id(111);

  rule_engine->sendLinkAllocationUpdateMessage(msg);
  auto gate = rule_engine->toRouterGate;
  EXPECT_EQ(gate->messages.size(), 1);

  auto pkt = dynamic_cast<LinkAllocationUpdateMessage*>(gate->messages[0]);
  EXPECT_EQ(pkt->getSrcAddr(), 2);
  EXPECT_EQ(pkt->getDestAddr(), 1);
  EXPECT_EQ(pkt->getNegotiatedRuleSet_id(), 111);
}

TEST_F(RuleEngineTest, reallocateResource) {
  auto* sim = prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon();
  auto* hardware_monitor = new MockHardwareMonitor();
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller};
  sim->registerComponent(rule_engine);
  sim->setContext(rule_engine);
  rule_engine->callInitialize();

  auto logger = std::make_unique<DisabledLogger>();
  auto* qubit_record0 = new QubitRecord(QNIC_E, 3, 0, logger.get());
  auto* qubit_record1 = new QubitRecord(QNIC_E, 3, 1, logger.get());
  auto* qubit_record2 = new QubitRecord(QNIC_E, 3, 2, logger.get());
  rule_engine->setAllResources(0, qubit_record0);
  rule_engine->setAllResources(1, qubit_record1);
  rule_engine->setAllResources(2, qubit_record2);
  int q0 = 0;
  QNodeAddr partner_addr{1};
  // this action needs a resource qubit that is entangled with partner 1.
  Program test_action{"testAction", {quisp::runtime::INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner_addr, 0}}}};
  Program empty_condition{"emptyCondition", {}};

  auto rs1 = quisp::runtime::RuleSet{"test rs", {quisp::runtime::Rule{"test", -1, -1, empty_condition, test_action}}};
  auto runtime1 = quisp::runtime::Runtime{};
  rs1.id = 111;
  rule_engine->runtimes.acceptRuleSet(rs1);

  auto rs2 = quisp::runtime::RuleSet{"test rs", {quisp::runtime::Rule{"test", -1, -1, empty_condition, test_action}}};
  auto runtime2 = quisp::runtime::Runtime{};
  rs2.id = 222;
  rule_engine->runtimes.acceptRuleSet(rs2);

  rule_engine->ResourceAllocation(QNIC_E, 3);
  EXPECT_TRUE(qubit_record1->isAllocated());

  rule_engine->reallocateResource(QNIC_E, 3, rs1.id, rs2.id);
  EXPECT_TRUE(qubit_record1->isAllocated());
}

TEST_F(RuleEngineTest, executeAllRuleSets) {
  auto* sim = prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon();
  auto* hardware_monitor = new MockHardwareMonitor();
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller};
  sim->registerComponent(rule_engine);
  sim->setContext(rule_engine);
  rule_engine->callInitialize();

  Program empty{"empty", {}};
  Program cond_passed_once{"passed_once",
                           {
                               INSTR_LOAD_RegId_MemoryKey_{{RegId::REG0, MemoryKey{"count"}}},
                               INSTR_BEZ_Label_RegId_{{Label{"first_time"}, RegId::REG0}},
                               INSTR_RET_ReturnCode_{{ReturnCode::COND_FAILED}},
                               INSTR_INC_RegId_{{RegId::REG0}, "first_time"},
                               INSTR_STORE_MemoryKey_RegId_{{MemoryKey{"count"}, RegId::REG0}},
                               INSTR_RET_ReturnCode_{{ReturnCode::COND_PASSED}},
                           }};
  Program checker{"cond", {INSTR_STORE_MemoryKey_int_{{MemoryKey{"test"}, 123}}}};
  Program terminator{"terminator", {INSTR_RET_ReturnCode_{{ReturnCode::RS_TERMINATED}}}};
  Rule rule{
      "", -1, -1, cond_passed_once, checker,
  };
  RuleSet rs1{"rs2", {rule}, terminator};
  rs1.id = 1;
  rs1.owner_addr = 1;
  rule_engine->runtimes.acceptRuleSet(rs1);

  rule_engine->ruleset_id_node_addresses_along_path_map[rs1.id].push_back(1);
  rule_engine->ruleset_id_node_addresses_along_path_map[rs1.id].push_back(5);

  rule_engine->executeAllRuleSets();
  auto gate = rule_engine->toRouterGate;
  EXPECT_EQ(gate->messages.size(), 2);

  auto pkt1 = dynamic_cast<ConnectionTeardownMessage*>(gate->messages[0]);
  EXPECT_EQ(pkt1->getSrcAddr(), 5);
  EXPECT_EQ(pkt1->getDestAddr(), 1);
  EXPECT_EQ(pkt1->getActual_srcAddr(), 5);
  EXPECT_EQ(pkt1->getActual_destAddr(), 1);
  EXPECT_EQ(pkt1->getLAU_req_srcAddr(), 1);
  EXPECT_EQ(pkt1->getLAU_req_destAddr(), 5);
  EXPECT_EQ(pkt1->getRuleSet_id(), 1);

  auto pkt2 = dynamic_cast<ConnectionTeardownMessage*>(gate->messages[1]);
  EXPECT_EQ(pkt2->getSrcAddr(), 5);
  EXPECT_EQ(pkt2->getDestAddr(), 5);
  EXPECT_EQ(pkt2->getActual_srcAddr(), 5);
  EXPECT_EQ(pkt2->getActual_destAddr(), 5);
  EXPECT_EQ(pkt2->getLAU_req_srcAddr(), 5);
  EXPECT_EQ(pkt2->getLAU_req_destAddr(), -1);
  EXPECT_EQ(pkt2->getRuleSet_id(), 1);
}

}  // namespace

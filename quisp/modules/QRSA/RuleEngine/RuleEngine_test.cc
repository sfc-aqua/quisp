#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include <test_utils/TestUtils.h>
#include <memory>
#include <utility>

#include "BellPairStore/BellPairStore.h"
#include "IRuleEngine.h"
#include "QubitRecord/QubitRecord.h"
#include "RuleEngine.h"
#include "rules/Rule.h"
#include "test_utils/UtilFunctions.h"
#include "test_utils/mock_modules/MockHardwareMonitor.h"
#include "test_utils/mock_modules/MockRealTimeController.h"
#include "test_utils/mock_modules/MockRoutingDaemon.h"
#include "types/QNodeAddr.h"

#include <messages/purification_messages_m.h>
#include <modules/Logger/DisabledLogger.h>
#include <modules/QNIC.h>
#include <modules/QNIC/StationaryQubit/IStationaryQubit.h>
#include <modules/QRSA/HardwareMonitor/IHardwareMonitor.h>
#include <modules/QRSA/QRSA.h>
#include <modules/QRSA/RealTimeController/IRealTimeController.h>
#include <modules/QRSA/RoutingDaemon/RoutingDaemon.h>
#include <rules/Action.h>
#include <rules/RuleSet.h>
#include <runtime/RuleSet.h>
#include <runtime/Runtime.h>
#include <runtime/opcode.h>
#include <runtime/test.h>
#include <runtime/types.h>

namespace {

using namespace omnetpp;
using namespace quisp::utils;
using namespace quisp::rules;
using namespace quisp::modules;
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
  using quisp::modules::RuleEngine::purification_result_table;
  using quisp::modules::RuleEngine::qnic_store;
  using quisp::modules::RuleEngine::runtimes;

  RuleEngineTestTarget(IStationaryQubit* mockQubit, MockRoutingDaemon* routingdaemon, MockHardwareMonitor* hardware_monitor, MockRealTimeController* realtime_controller,
                       std::vector<QNicSpec> qnic_specs = {})
      : quisp::modules::RuleEngine() {
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
  void setAllResources(QNodeAddr partner_addr, IQubitRecord* qubit) { this->bell_pair_store.insertEntangledQubit(partner_addr, qubit); };

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

TEST_F(RuleEngineTest, ESResourceUpdate) {
  // 1 (wait) -- 2(ES) -- 3(wait)
  // from wait to next rule
  auto* mockQubit1 = new MockQubit(QNIC_E, 0);
  std::unique_ptr<IQubitRecord> qubit_record = std::make_unique<QubitRecord>(QNIC_E, 0, 0);
  auto rule_engine = new RuleEngineTestTarget{mockQubit1, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};

  auto info = std::make_unique<ConnectionSetupInfo>();
  info->qnic.type = QNIC_E;
  info->qnic.index = 0;

  unsigned long mock_ruleset_id = 10;
  int shared_tag = 3;

  QNodeAddr swapper_addr{2};
  QNodeAddr new_partner{3};

  EXPECT_CALL(*routing_daemon, findQNicAddrByDestAddr(new_partner)).WillOnce(Return(1));
  EXPECT_CALL(*hardware_monitor, findConnectionInfoByQnicAddr(1)).Times(1).WillOnce(Return(ByMove(std::move(info))));
  EXPECT_CALL(*dynamic_cast<MockQNicStore*>(rule_engine->qnic_store.get()), getQubitRecord(QNIC_E, 0, 1)).Times(1).WillOnce(Return(qubit_record.get()));

  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();

  RuleSet rs{mock_ruleset_id, rule_engine->parentAddress};
  auto wait_rule = std::make_unique<Rule>(swapper_addr, shared_tag, false);
  wait_rule->setAction(std::make_unique<Wait>(swapper_addr));
  rs.addRule(std::move(wait_rule));
  auto next_rule = std::make_unique<Rule>(swapper_addr, shared_tag, false);
  next_rule->setAction(std::make_unique<Wait>(swapper_addr));
  rs.addRule(std::move(next_rule));

  rule_engine->runtimes.acceptRuleSet(rs.construct());
  auto& rt = rule_engine->runtimes.at(0);
  auto wait_rule_id = rt.ruleset.rules.at(0).id;
  auto next_rule_id = rt.ruleset.rules.at(1).id;
  rt.ruleset.partner_initial_rule_table.insert({QNodeAddr(1), wait_rule_id});
  rt.ruleset.partner_initial_rule_table.insert({QNodeAddr(new_partner), next_rule_id});
  rt.assignQubitToRuleSet(QNodeAddr{1}, qubit_record.get());

  ASSERT_EQ(getResourceSizeByRuleId(rt, wait_rule_id), 1);
  ASSERT_EQ(getResourceSizeByRuleId(rt, next_rule_id), 0);
  SwappingResultData swapr{
      .ruleset_id = mock_ruleset_id,
      .shared_tag = shared_tag,
      .new_partner_addr = QNodeAddr{3},
      .operation_type = 0,
      .qubit_index = 1,
  };
  rule_engine->handleSwappingResult(swapr);
  ASSERT_EQ(getResourceSizeByRuleId(rt, wait_rule_id), 0);
  ASSERT_EQ(getResourceSizeByRuleId(rt, next_rule_id), 1);
  delete rule_engine->qnic_store.get();
}

TEST_F(RuleEngineTest, resourceAllocation) {
  auto logger = std::make_unique<DisabledLogger>();
  auto* qubit_record0 = new QubitRecord(QNIC_E, 3, 0, logger.get());
  auto* qubit_record1 = new QubitRecord(QNIC_E, 3, 1, logger.get());
  auto* qubit_record2 = new QubitRecord(QNIC_E, 3, 2, logger.get());
  auto rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, nullptr, qnic_specs};
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  rule_engine->setAllResources(QNodeAddr{0}, qubit_record0);
  rule_engine->setAllResources(QNodeAddr{1}, qubit_record1);
  rule_engine->setAllResources(QNodeAddr{2}, qubit_record2);
  int q0 = 0;
  QNodeAddr partner_addr{1};
  // this action needs a resource qubit that is entangled with partner 1.
  Program test_action{"testAction", {quisp::runtime::INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner_addr, 0}}}};
  Program empty_condition{"emptyCondition", {}};
  auto rs = quisp::runtime::RuleSet{"test rs", {quisp::runtime::Rule{"test", 0, empty_condition, test_action}}};
  auto runtime = quisp::runtime::Runtime{};
  rule_engine->runtimes.acceptRuleSet(rs);

  rule_engine->ResourceAllocation(QNIC_E, 3);
  EXPECT_TRUE(qubit_record1->isAllocated());

  // resource allocation assigns a corresponding qubit to action's resource
  auto& rt = rule_engine->runtimes.at(0);
  EXPECT_EQ(rt.ruleset.rules.size(), 1);
  EXPECT_EQ(rt.qubits.size(), 1);
}

TEST_F(RuleEngineTest, storeCheckPurificationAgreement_running_process) {
  QNIC_type qnic_type = QNIC_E;
  int qnic_id = 0;
  int shared_tag = 1;
  int action_index = 3;
  auto* qubit = new MockQubit{qnic_type, qnic_id};
  qubit->action_index = action_index;
  auto* rule_engine = new RuleEngineTestTarget{qubit, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  unsigned long ruleset_id = 4;
  QNodeAddr partner_addr{5};
  auto* ruleset = new quisp::rules::RuleSet(ruleset_id, rule_engine->parentAddress);
  auto rule1 = new Rule(QNodeAddr{0}, shared_tag, false);  // target_rule_id, 0);
  auto rule2 = new Rule(QNodeAddr{0}, shared_tag, false);  // 11, 1);
  rule1->setAction(std::make_unique<Wait>(QNodeAddr{0}));
  rule2->setAction(std::make_unique<Wait>(QNodeAddr{0}));
  auto* qubit_record = new QubitRecord{qnic_type, qnic_id, 0};

  ruleset->addRule(std::unique_ptr<Rule>(rule1));
  ruleset->addRule(std::unique_ptr<Rule>(rule2));
  rule_engine->runtimes.acceptRuleSet(ruleset->construct());
  auto& rt = rule_engine->runtimes.at(0);
  auto rule1_id = rt.ruleset.rules.at(0).id;
  auto rule2_id = rt.ruleset.rules.at(1).id;

  rt.ruleset.partner_initial_rule_table.insert({partner_addr, rule1_id});
  // set rule1 -> rule2
  rt.ruleset.next_rule_table.insert({{partner_addr, rule1_id}, rule2_id});

  rt.assignQubitToRuleSet(partner_addr, qubit_record);
  EXPECT_EQ(getResourceSizeByRuleId(rt, rule1_id), 1);
  EXPECT_EQ(getResourceSizeByRuleId(rt, rule2_id), 0);

  EXPECT_EQ(rule_engine->purification_result_table.size(), 0);
  // got the result from the node itself
  PurificationResultKey key;
  key.rs_id = ruleset_id;
  key.rule_id = 0;
  key.action_index = action_index;
  key.shared_tag = shared_tag;
  key.type = PurType::SINGLE_X;
  PurificationResultData data;
  data.is_z_plus = true;
  rule_engine->handlePurificationResult(key, data, true);

  EXPECT_EQ(getResourceSizeByRuleId(rt, rule1_id), 1);
  EXPECT_EQ(getResourceSizeByRuleId(rt, rule2_id), 0);
  EXPECT_EQ(rule_engine->purification_result_table.size(), 1);

  EXPECT_CALL(*qubit, Unlock()).Times(1);
  // got the same result from the opposite node
  // and then the resource will be upgrade.
  // but obviously we should separate this into 2 methods.
  rule_engine->handlePurificationResult(key, data, false);
  EXPECT_EQ(getResourceSizeByRuleId(rt, rule1_id), 0);
  EXPECT_EQ(getResourceSizeByRuleId(rt, rule2_id), 1);
  delete qubit_record;
  delete qubit;
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
  qubit_record->markRuleApplied(0);
  EXPECT_FALSE(!qubit_record->isRuleApplied(0));

  EXPECT_CALL(*realtime_controller, ReInitialize_StationaryQubit(qubit_record, false)).Times(1).WillOnce(Return());
  EXPECT_CALL(*dynamic_cast<MockQNicStore*>(rule_engine->qnic_store.get()), getQubitRecord(QNIC_E, qnic_index, 1)).Times(1).WillOnce(Return(qubit_record));
  rule_engine->freeConsumedResource(qnic_index, qubit, QNIC_E);
  EXPECT_TRUE(!qubit_record->isRuleApplied(0));
  EXPECT_FALSE(qubit_record->isBusy());
  delete qubit;
  delete rule_engine->qnic_store.get();
}

TEST_F(RuleEngineTest, updateAndCheckAppliedRule) {
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();

  auto* qubit_record1 = new QubitRecord(QNIC_E, 7, 0);
  auto* qubit_record2 = new QubitRecord(QNIC_E, 11, 0);
  EXPECT_TRUE(!qubit_record1->isRuleApplied(1));
  qubit_record1->markRuleApplied(1);
  EXPECT_FALSE(!qubit_record1->isRuleApplied(1));
  EXPECT_TRUE(!qubit_record1->isRuleApplied(2));
  EXPECT_TRUE(!qubit_record2->isRuleApplied(1));
}

TEST_F(RuleEngineTest, checkAppliedRule) {
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();

  auto* qubit = new MockQubit(QNIC_E, 7);
  auto* qubit_record = new QubitRecord(QNIC_E, 7, 1);
  EXPECT_TRUE(!qubit_record->isRuleApplied(1));
  qubit_record->markRuleApplied(1);
  EXPECT_FALSE(!qubit_record->isRuleApplied(1));

  qubit_record->clearAppliedRules();
  EXPECT_TRUE(!qubit_record->isRuleApplied(1));

  delete qubit;
  delete qubit_record;
}

TEST_F(RuleEngineTest, updateResourcesEntanglementSwappingWithoutRuleSet) {
  /* setup components */
  auto* qubit = new MockQubit(QNIC_E, 7);
  auto* rule_engine = new RuleEngineTestTarget{qubit, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  std::unique_ptr<IQubitRecord> qubit_record = std::make_unique<QubitRecord>(QNIC_E, 0, 0);
  EXPECT_CALL(*dynamic_cast<MockQNicStore*>(rule_engine->qnic_store.get()), getQubitRecord(QNIC_E, 0, 0)).Times(3).WillRepeatedly(Return(qubit_record.get()));
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  quisp::runtime::RuleSet rs{""};
  rs.id = 0;
  rule_engine->runtimes.acceptRuleSet(rs);
  auto& rt = rule_engine->runtimes.at(0);
  rt.ruleset.partner_initial_rule_table.insert({QNodeAddr{2}, 0});
  rt.assignQubitToRuleSet(QNodeAddr{2}, qubit_record.get());

  {  // swap result doesn't need an action
    SwappingResultData result{.ruleset_id = 0, .new_partner_addr = QNodeAddr{2}, .operation_type = 0};
    EXPECT_CALL(*routing_daemon, findQNicAddrByDestAddr(QNodeAddr{2})).Times(1).WillOnce(Return(5));
    auto info = std::make_unique<ConnectionSetupInfo>();
    info->qnic.type = QNIC_E;
    info->qnic.index = 0;
    EXPECT_CALL(*hardware_monitor, findConnectionInfoByQnicAddr(5)).Times(1).WillOnce(Return(ByMove(std::move(info))));
    EXPECT_CALL(*realtime_controller, applyXGate(_)).Times(0);
    EXPECT_CALL(*realtime_controller, applyZGate(_)).Times(0);
    rule_engine->handleSwappingResult(result);
  }
  {  // swap result needs to apply X gate
    SwappingResultData result{.ruleset_id = 0, .new_partner_addr = QNodeAddr{2}, .operation_type = 1};
    EXPECT_CALL(*routing_daemon, findQNicAddrByDestAddr(QNodeAddr{2})).Times(1).WillOnce(Return(5));
    auto info = std::make_unique<ConnectionSetupInfo>();
    info->qnic.type = QNIC_E;
    info->qnic.index = 0;
    EXPECT_CALL(*hardware_monitor, findConnectionInfoByQnicAddr(5)).Times(1).WillOnce(Return(ByMove(std::move(info))));
    EXPECT_CALL(*realtime_controller, applyXGate(qubit_record.get())).Times(1);
    EXPECT_CALL(*realtime_controller, applyZGate(_)).Times(0);
    rule_engine->handleSwappingResult(result);
  }
  {  // swap result needs to apply Z gate
    SwappingResultData result{.ruleset_id = 0, .new_partner_addr = QNodeAddr{2}, .operation_type = 2};
    EXPECT_CALL(*routing_daemon, findQNicAddrByDestAddr(QNodeAddr{2})).Times(1).WillOnce(Return(5));
    auto info = std::make_unique<ConnectionSetupInfo>();
    info->qnic.type = QNIC_E;
    info->qnic.index = 0;
    EXPECT_CALL(*hardware_monitor, findConnectionInfoByQnicAddr(5)).Times(1).WillOnce(Return(ByMove(std::move(info))));
    EXPECT_CALL(*realtime_controller, applyZGate(qubit_record.get())).Times(1);
    EXPECT_CALL(*realtime_controller, applyXGate(_)).Times(0);
    rule_engine->handleSwappingResult(result);
  }
  delete qubit;
  delete rule_engine->qnic_store.get();
}

TEST_F(RuleEngineTest, updateResourcesEntanglementSwappingWithRuleSet) {
  QNIC_type qnic_type = QNIC_E;
  int qnic_index = 0;
  int qubit_index = 7;
  auto* qubit = new MockQubit(qnic_type, qnic_index);
  auto* rule_engine = new RuleEngineTestTarget{qubit, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  std::unique_ptr<IQubitRecord> qubit_record = std::make_unique<QubitRecord>(qnic_type, qnic_index, qubit_index);
  EXPECT_CALL(*dynamic_cast<MockQNicStore*>(rule_engine->qnic_store.get()), getQubitRecord(qnic_type, qnic_index, qubit_index)).Times(1).WillRepeatedly(Return(qubit_record.get()));
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();

  unsigned long ruleset_id = 4;
  int shared_tag = 5;
  QNodeAddr swapper_addr{3};
  QNodeAddr new_partner_addr{2};
  RuleSet rs{ruleset_id, rule_engine->parentAddress};
  {  // generate RuleSet
    auto rule = std::make_unique<Rule>(swapper_addr, shared_tag, false);
    rule->shared_tag = shared_tag;
    rule->setAction(std::make_unique<Wait>(swapper_addr));
    auto next_rule = std::make_unique<Rule>(swapper_addr, shared_tag, false);
    next_rule->setAction(std::make_unique<Wait>(swapper_addr));

    rs.addRule(std::move(rule));
    rs.addRule(std::move(next_rule));
    rule_engine->runtimes.acceptRuleSet(rs.construct());
  }
  auto& rt = rule_engine->runtimes.at(0);
  rt.assignQubitToRule(QNodeAddr{new_partner_addr}, 0, qubit_record.get());
  rt.ruleset.partner_initial_rule_table.insert({QNodeAddr{new_partner_addr}, 1});
  EXPECT_EQ(getResourceSizeByRuleId(rt, 0), 1);
  EXPECT_EQ(getResourceSizeByRuleId(rt, 1), 0);

  EXPECT_CALL(*routing_daemon, findQNicAddrByDestAddr(new_partner_addr)).Times(1).WillOnce(Return(5));
  auto info = std::make_unique<ConnectionSetupInfo>();
  info->qnic.type = qnic_type;
  info->qnic.index = qnic_index;
  EXPECT_CALL(*hardware_monitor, findConnectionInfoByQnicAddr(5)).Times(1).WillOnce(Return(ByMove(std::move(info))));
  EXPECT_CALL(*qubit, gateX()).Times(0);
  EXPECT_CALL(*qubit, gateZ()).Times(0);
  SwappingResultData result{
      .ruleset_id = ruleset_id,
      .shared_tag = shared_tag,
      .new_partner_addr = QNodeAddr{2},
      .operation_type = 0,
      .qubit_index = qubit_index,
  };
  rule_engine->handleSwappingResult(result);

  // check whether the qubit is promoted or not
  EXPECT_EQ(getResourceSizeByRuleId(rt, 0), 0);
  EXPECT_EQ(getResourceSizeByRuleId(rt, 1), 1);

  delete qubit;
  delete rule_engine->qnic_store.get();
}

}  // namespace

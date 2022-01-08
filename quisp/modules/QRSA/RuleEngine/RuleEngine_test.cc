#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include <test_utils/TestUtils.h>
#include <memory>
#include <utility>

#include "BellPairStore/BellPairStore.h"
#include "IRuleEngine.h"
#include "RuleEngine.h"

#include "modules/QNIC.h"
#include "modules/QNIC/StationaryQubit/IStationaryQubit.h"
#include "modules/QRSA/HardwareMonitor/HardwareMonitor.h"
#include "modules/QRSA/HardwareMonitor/IHardwareMonitor.h"
#include "modules/QRSA/QRSA.h"
#include "modules/QRSA/RealTimeController/IRealTimeController.h"
#include "modules/QRSA/RoutingDaemon/RoutingDaemon.h"
#include "modules/QRSA/RuleEngine/QubitRecord/QubitRecord.h"
#include "rules/Active/ActiveAction.h"
#include "rules/Active/ActiveRuleSet.h"

namespace {

using namespace omnetpp;
using namespace quisp::utils;
using namespace quisp::rules;
using namespace quisp::rules::actions;
using quisp::rules::actions::ActiveAction;
using namespace quisp::modules;
using quisp::modules::qrsa::IQubitRecord;
using quisp::modules::qubit_record::QubitRecord;
using namespace quisp_test;
using namespace testing;

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
};

class RuleEngineTestTarget : public quisp::modules::RuleEngine {
 public:
  using quisp::modules::RuleEngine::checkAppliedRule;
  using quisp::modules::RuleEngine::clearAppliedRule;
  using quisp::modules::RuleEngine::constructActiveRuleSet;
  using quisp::modules::RuleEngine::initialize;
  using quisp::modules::RuleEngine::par;
  using quisp::modules::RuleEngine::qnic_store;
  using quisp::modules::RuleEngine::storeCheck_Purification_Agreement;
  using quisp::modules::RuleEngine::Unlock_resource_and_discard;
  using quisp::modules::RuleEngine::Unlock_resource_and_upgrade_stage;
  using quisp::modules::RuleEngine::updateAppliedRule;
  using quisp::modules::RuleEngine::updateResources_EntanglementSwapping;

  RuleEngineTestTarget(IStationaryQubit* mockQubit, MockRoutingDaemon* routingdaemon, MockHardwareMonitor* hardware_monitor, MockRealTimeController* realtime_controller,
                       std::vector<QNicSpec> qnic_specs = {})
      : quisp::modules::RuleEngine() {
    setParInt(this, "address", 123);
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
  void setTracker(int qnic_address, int shot_number, QubitAddr_cons qubit_address) { this->tracker[qnic_address].insert(std::make_pair(shot_number, qubit_address)); };

 private:
  FRIEND_TEST(RuleEngineTest, ESResourceUpdate);
  FRIEND_TEST(RuleEngineTest, trackerUpdate);
  friend class MockRoutingDaemon;
  friend class MockHardwareMonitor;
};

// specifier for qnics in order to create qnic_record and qubit_record.
static const std::vector<QNicSpec> qnic_specs = {{QNIC_E, 0, 2}, {QNIC_R, 0, 2}};

TEST(RuleEngineTest, ESResourceUpdate) {
  // 1 (wait) -- 2(ES) -- 3(wait)
  // from wait to next rule
  auto* sim = prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* mockQubit1 = new MockQubit(QNIC_E, 0);
  std::unique_ptr<IQubitRecord> qubit_record = std::make_unique<QubitRecord>(QNIC_E, 0, 0);
  auto rule_engine = new RuleEngineTestTarget{mockQubit1, routingdaemon, mockHardwareMonitor, realtime_controller, qnic_specs};

  auto info = std::make_unique<ConnectionSetupInfo>();
  info->qnic.type = QNIC_E;
  info->qnic.index = 0;

  unsigned long mock_ruleset_id = 10;
  unsigned long mock_rule_id = 5193;
  unsigned long mock_next_rule_id = 3829;

  swapping_result swapr;
  swapr.id.ruleset_id = mock_ruleset_id;
  swapr.id.rule_id = mock_rule_id;
  swapr.new_partner = 3;
  swapr.operation_type = 0;
  swapr.new_partner_qnic_address = 1;
  swapr.new_partner_qnic_index = 1;
  swapr.new_partner_qnic_type = QNIC_E;
  swapr.measured_qubit_index = 1;

  EXPECT_CALL(*routingdaemon, return_QNIC_address_to_destAddr(swapr.new_partner)).WillOnce(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, findConnectionInfoByQnicAddr(1)).Times(1).WillOnce(Return(ByMove(std::move(info))));
  EXPECT_CALL(*dynamic_cast<MockQNicStore*>(rule_engine->qnic_store.get()), getQubitRecord(QNIC_E, 0, 1)).Times(1).WillOnce(Return(qubit_record.get()));
  EXPECT_CALL(*realtime_controller, assertNoEntanglement(qubit_record.get())).Times(1);
  // 0. set ruleset
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  auto* rs = new ActiveRuleSet(mock_ruleset_id, mock_rule_id);  // ruleset_id, ruleset_owner, partners
  auto wait_rule = std::make_unique<ActiveRule>(mock_ruleset_id, mock_rule_id);
  wait_rule->next_rule_id = mock_next_rule_id;
  rs->addRule(std::move(wait_rule));
  auto next_rule = std::make_unique<ActiveRule>(mock_ruleset_id, mock_next_rule_id);
  rs->addRule(std::move(next_rule));

  rule_engine->rp.insert(rs);
  rule_engine->rp[0]->getRule(0)->addResource(1, mockQubit1);
  ASSERT_EQ(rule_engine->rp[0]->getRule(0)->resources.size(), 1);
  ASSERT_EQ(rule_engine->rp[0]->getRule(1)->resources.size(), 0);
  rule_engine->updateResources_EntanglementSwapping(swapr);
  // 1. remove from previous rule
  ASSERT_EQ(rule_engine->rp[0]->getRule(0)->resources.size(), 0);
  // // 2. add to the next rule
  ASSERT_EQ(rule_engine->rp[0]->getRule(1)->resources.size(), 1);
  delete mockHardwareMonitor;
  delete routingdaemon;
  delete realtime_controller;
  delete rule_engine->qnic_store.get();
}

TEST(RuleEngineTest, resourceAllocation) {
  auto* sim = prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto* mockQubit1 = new MockQubit(QNIC_E, 3);
  auto* qubit_record0 = new QubitRecord(QNIC_E, 3, 0);
  auto* qubit_record1 = new QubitRecord(QNIC_E, 3, 1);
  auto* qubit_record2 = new QubitRecord(QNIC_E, 3, 2);
  auto rule_engine = new RuleEngineTestTarget{mockQubit1, routingdaemon, mockHardwareMonitor, nullptr, qnic_specs};
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  rule_engine->setAllResources(0, qubit_record0);
  rule_engine->setAllResources(1, qubit_record1);
  rule_engine->setAllResources(2, qubit_record2);
  auto* rs = new ActiveRuleSet(0, 0);
  auto rule = std::make_unique<ActiveRule>(0, 0);
  // owner address,
  auto* action = new RandomMeasureAction(0, 0, 0, 1, QNIC_E, 3, 1, 10);

  rule->setAction(action);
  rule->action_partners = {1};
  rs->addRule(std::move(rule));
  rule_engine->rp.insert(rs);

  rule_engine->ResourceAllocation(QNIC_E, 3);
  EXPECT_TRUE(qubit_record1->isAllocated());

  // resource allocation assigns a corresponding qubit to action's resource
  auto& _rs = rule_engine->rp[0];
  EXPECT_NE(_rs, nullptr);
  EXPECT_EQ(_rs->size(), 1);
  auto& _rule = _rs->getRule(0);
  EXPECT_FALSE(_rule == nullptr);
  EXPECT_EQ(_rule->resources.size(), 1);
  delete mockHardwareMonitor;
  delete routingdaemon;
  delete mockQubit1;
}

TEST(RuleEngineTest, trackerUpdate) {
  // 1. initialize tracker
  prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto* mockRealTimeController = new MockRealTimeController;
  auto rule_engine = new RuleEngineTestTarget{nullptr, routingdaemon, mockHardwareMonitor, mockRealTimeController, qnic_specs};
  rule_engine->initialize();
  for (int i = 0; i < rule_engine->number_of_qnics_all; i++) {
    EXPECT_EQ(rule_engine->tracker[i].size(), 0);  // tracker is properly initialized?
  }
  // set tracker accessible false at qnic 0
  rule_engine->tracker_accessible.at(0) = false;
  // 2. start emission (check records) add records
  // TODO: actual BSM notification should be introduced here
  QubitAddr_cons addr(1, 0, 0);  // parent_address, qnic_index, qubit_index
  rule_engine->setTracker(0, 0, addr);
  EXPECT_EQ(rule_engine->tracker[0].size(), 1);
  // check if the tracker is blocked properly
  EXPECT_FALSE(rule_engine->tracker_accessible[0]);
  EXPECT_TRUE(rule_engine->tracker_accessible[1]);
  // 3. clear tracker and check flag is reset
  rule_engine->clearTrackerTable(0, 0);  // source address, qnic address
  EXPECT_TRUE(rule_engine->tracker_accessible[0]);
  EXPECT_TRUE(rule_engine->tracker_accessible[1]);
  // clered table
  EXPECT_EQ(rule_engine->tracker[0].size(), 0);
  EXPECT_EQ(rule_engine->tracker[1].size(), 0);
  delete routingdaemon;
  delete mockHardwareMonitor;
  delete mockRealTimeController;
}

TEST(RuleEngineTest, storeCheckPurificationAgreement_no_process) {
  prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  rule_engine->callInitialize();
  purification_result result{
      .outcome = true,
  };
  rule_engine->storeCheck_Purification_Agreement(result);
  delete hardware_monitor;
}

TEST(RuleEngineTest, storeCheckPurificationAgreement_running_process) {
  prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  rule_engine->callInitialize();
  unsigned long ruleset_id = 4;
  int partner_addr = 5;
  int action_index = 3;
  auto* ruleset = new ActiveRuleSet(ruleset_id, rule_engine->parentAddress);
  unsigned long target_rule_id = 10;
  auto rule1 = new ActiveRule(ruleset_id, target_rule_id);
  auto rule2 = new ActiveRule(ruleset_id, 11);
  auto* qubit = new MockQubit(QNIC_E, 0);

  qubit->action_index = action_index;
  rule1->addResource(partner_addr, qubit);
  rule1->next_rule_id = rule2->rule_id;
  ruleset->addRule(std::unique_ptr<ActiveRule>(rule1));
  ruleset->addRule(std::unique_ptr<ActiveRule>(rule2));

  rule_engine->rp.insert(ruleset);
  EXPECT_CALL(*qubit, Unlock()).Times(1);

  purification_result result{
      .id = {.ruleset_id = ruleset_id, .rule_id = rule1->rule_id, .index = action_index},
      .outcome = true,
  };

  EXPECT_EQ(rule1->resources.size(), 1);
  EXPECT_EQ(rule2->resources.size(), 0);

  EXPECT_EQ(rule_engine->Purification_table.size(), 0);
  // got the result from the node itself
  rule_engine->storeCheck_Purification_Agreement(result);

  EXPECT_EQ(rule1->resources.size(), 1);
  EXPECT_EQ(rule2->resources.size(), 0);
  EXPECT_EQ(rule_engine->Purification_table.size(), 1);

  // got the same result from the opposite node
  // and then the resource will be upgrade.
  // but obviously we should separate this into 2 methods.
  rule_engine->storeCheck_Purification_Agreement(result);
  EXPECT_EQ(rule1->resources.size(), 0);
  EXPECT_EQ(rule2->resources.size(), 1);
  delete qubit;
  delete hardware_monitor;
}

TEST(RuleEngineTest, freeConsumedResource) {
  prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller};
  rule_engine->callInitialize();
  int qnic_index = 7;
  auto* qubit = new MockQubit(QNIC_E, qnic_index);
  auto* qubit_record = new QubitRecord(QNIC_E, qnic_index, 1);
  qubit_record->setBusy(true);
  qubit->fillParams();
  rule_engine->updateAppliedRule(qubit, 0);
  EXPECT_FALSE(rule_engine->checkAppliedRule(qubit, 0));

  EXPECT_CALL(*realtime_controller, ReInitialize_StationaryQubit(qubit_record, false)).Times(1).WillOnce(Return());
  EXPECT_CALL(*dynamic_cast<MockQNicStore*>(rule_engine->qnic_store.get()), getQubitRecord(QNIC_E, qnic_index, 1)).Times(1).WillOnce(Return(qubit_record));
  rule_engine->freeConsumedResource(qnic_index, qubit, QNIC_E);
  EXPECT_TRUE(rule_engine->checkAppliedRule(qubit, 0));
  EXPECT_FALSE(qubit_record->isBusy());
  delete qubit;
  delete hardware_monitor;
  delete realtime_controller;
  delete rule_engine->qnic_store.get();
}

TEST(RuleEngineTest, unlockResourceAndDiscard) {
  prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;

  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller, {}};
  rule_engine->callInitialize();

  unsigned long ruleset_id = 4;
  int partner_addr = 5;
  int action_index = 3;
  auto* ruleset = new ActiveRuleSet(ruleset_id, rule_engine->parentAddress);
  unsigned long target_rule_id = 10;
  auto rule1 = new ActiveRule(ruleset_id, target_rule_id);
  auto rule2 = new ActiveRule(ruleset_id, 11);
  int qnic_index = 17;
  auto* qubit = new MockQubit(QNIC_E, qnic_index);
  auto* qubit_record = new QubitRecord(QNIC_E, qnic_index, 1);
  qubit_record->setBusy(true);
  qubit->fillParams();
  qubit->action_index = action_index;
  rule1->addResource(partner_addr, qubit);
  rule1->next_rule_id = rule2->rule_id;
  ruleset->addRule(std::unique_ptr<ActiveRule>(rule1));
  ruleset->addRule(std::unique_ptr<ActiveRule>(rule2));

  rule_engine->rp.insert(ruleset);
  EXPECT_CALL(*qubit, Unlock()).Times(1);
  EXPECT_CALL(*dynamic_cast<MockQNicStore*>(rule_engine->qnic_store.get()), getQubitRecord(QNIC_E, qnic_index, 1)).Times(1).WillOnce(Return(qubit_record));

  rule_engine->updateAppliedRule(qubit, 0);
  EXPECT_EQ(rule1->resources.size(), 1);
  EXPECT_EQ(rule2->resources.size(), 0);
  EXPECT_CALL(*realtime_controller, ReInitialize_StationaryQubit(qubit_record, false)).Times(1).WillOnce(Return());
  rule_engine->Unlock_resource_and_discard(ruleset_id, target_rule_id, action_index);

  EXPECT_EQ(rule1->resources.size(), 0);
  EXPECT_EQ(rule2->resources.size(), 0);
  EXPECT_FALSE(qubit_record->isBusy());

  delete qubit;
  delete hardware_monitor;
  delete realtime_controller;
  delete rule_engine->qnic_store.get();
}

TEST(RuleEngineTest, unlockResourceAndUpgradeStage) {
  prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  rule_engine->callInitialize();

  unsigned long ruleset_id = 4;
  int partner_addr = 5;
  int action_index = 3;

  auto* ruleset = new ActiveRuleSet(ruleset_id, rule_engine->parentAddress);
  unsigned long target_rule_id = 10;
  auto rule1 = new ActiveRule(ruleset_id, target_rule_id);
  auto rule2 = new ActiveRule(ruleset_id, 11);
  auto* qubit = new MockQubit(QNIC_E, 0);

  qubit->action_index = action_index;
  rule1->addResource(partner_addr, qubit);
  rule1->next_rule_id = rule2->rule_id;
  ruleset->addRule(std::unique_ptr<ActiveRule>(rule1));
  ruleset->addRule(std::unique_ptr<ActiveRule>(rule2));

  rule_engine->rp.insert(ruleset);
  EXPECT_CALL(*qubit, Unlock()).Times(1);

  EXPECT_EQ(rule1->resources.size(), 1);
  EXPECT_EQ(rule2->resources.size(), 0);

  // the rule engine brings the qubit from rule1 to rule2
  rule_engine->Unlock_resource_and_upgrade_stage(ruleset_id, target_rule_id, action_index);

  EXPECT_EQ(rule1->resources.size(), 0);
  ASSERT_EQ(rule2->resources.size(), 1);
  auto it = rule2->resources.begin();
  EXPECT_EQ(it->first, partner_addr);
  EXPECT_EQ(it->second, qubit);

  delete qubit;
  delete hardware_monitor;
}

TEST(RuleEngineTest, unlockResourceAndUpgradeStage_without_next_rule) {
  prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  rule_engine->callInitialize();

  unsigned long ruleset_id = 4;
  int partner_addr = 5;
  int action_index = 3;

  auto* ruleset = new ActiveRuleSet(ruleset_id, rule_engine->parentAddress);
  unsigned long target_rule_id = 10;
  auto rule = new ActiveRule(ruleset_id, target_rule_id);
  auto* qubit = new MockQubit(QNIC_E, 0);

  qubit->action_index = action_index;
  rule->addResource(partner_addr, qubit);
  ruleset->addRule(std::unique_ptr<ActiveRule>(rule));

  rule_engine->rp.insert(ruleset);
  EXPECT_CALL(*qubit, Unlock()).Times(1);
  EXPECT_EQ(rule->resources.size(), 1);
  EXPECT_THROW({ rule_engine->Unlock_resource_and_upgrade_stage(ruleset_id, target_rule_id, action_index); }, cRuntimeError);

  delete qubit;
  delete hardware_monitor;
}

TEST(RuleEngineTest, unlockResourceAndUpgradeStage_without_process) {
  prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  rule_engine->callInitialize();

  EXPECT_NO_THROW({ rule_engine->Unlock_resource_and_upgrade_stage(101, 102, 103); });
  delete hardware_monitor;
}

TEST(RuleEngineTest, updateAndCheckAppliedRule) {
  prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  rule_engine->callInitialize();

  auto* qubit1 = new MockQubit(QNIC_E, 7);
  auto* qubit2 = new MockQubit(QNIC_E, 11);
  EXPECT_TRUE(rule_engine->checkAppliedRule(qubit1, 1));
  rule_engine->updateAppliedRule(qubit1, 1);
  EXPECT_FALSE(rule_engine->checkAppliedRule(qubit1, 1));
  EXPECT_TRUE(rule_engine->checkAppliedRule(qubit1, 2));
  EXPECT_TRUE(rule_engine->checkAppliedRule(qubit2, 1));

  delete qubit1;
  delete qubit2;
  delete hardware_monitor;
}

TEST(RuleEngineTest, checkAppliedRule) {
  prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  rule_engine->callInitialize();

  auto* qubit = new MockQubit(QNIC_E, 7);
  EXPECT_TRUE(rule_engine->checkAppliedRule(qubit, 1));
  rule_engine->updateAppliedRule(qubit, 1);
  EXPECT_FALSE(rule_engine->checkAppliedRule(qubit, 1));

  rule_engine->clearAppliedRule(qubit);
  EXPECT_TRUE(rule_engine->checkAppliedRule(qubit, 1));

  delete qubit;
  delete hardware_monitor;
}

TEST(RuleEngineTest, updateResourcesEntanglementSwappingWithoutRuleSet) {
  /* setup components */
  prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* qubit = new MockQubit(QNIC_E, 7);
  auto* rule_engine = new RuleEngineTestTarget{qubit, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  std::unique_ptr<IQubitRecord> qubit_record = std::make_unique<QubitRecord>(QNIC_E, 0, 0);
  EXPECT_CALL(*dynamic_cast<MockQNicStore*>(rule_engine->qnic_store.get()), getQubitRecord(QNIC_E, 0, 0)).Times(3).WillRepeatedly(Return(qubit_record.get()));
  EXPECT_CALL(*realtime_controller, assertNoEntanglement(qubit_record.get())).Times(3);
  rule_engine->callInitialize();

  {  // swap result doesn't need an action
    swapping_result result{.new_partner = 2, .operation_type = 0};
    EXPECT_CALL(*routing_daemon, return_QNIC_address_to_destAddr(2)).Times(1).WillOnce(Return(5));
    auto info = std::make_unique<ConnectionSetupInfo>();
    info->qnic.type = QNIC_E;
    info->qnic.index = 0;
    EXPECT_CALL(*hardware_monitor, findConnectionInfoByQnicAddr(5)).Times(1).WillOnce(Return(ByMove(std::move(info))));
    EXPECT_CALL(*realtime_controller, applyXGate(_)).Times(0);
    EXPECT_CALL(*realtime_controller, applyZGate(_)).Times(0);
    rule_engine->updateResources_EntanglementSwapping(result);
  }
  {  // swap result needs to apply X gate
    swapping_result result{.new_partner = 2, .operation_type = 1};
    EXPECT_CALL(*routing_daemon, return_QNIC_address_to_destAddr(2)).Times(1).WillOnce(Return(5));
    auto info = std::make_unique<ConnectionSetupInfo>();
    info->qnic.type = QNIC_E;
    info->qnic.index = 0;
    EXPECT_CALL(*hardware_monitor, findConnectionInfoByQnicAddr(5)).Times(1).WillOnce(Return(ByMove(std::move(info))));
    EXPECT_CALL(*realtime_controller, applyXGate(qubit_record.get())).Times(1);
    EXPECT_CALL(*realtime_controller, applyZGate(_)).Times(0);
    rule_engine->updateResources_EntanglementSwapping(result);
  }
  {  // swap result needs to apply Z gate
    swapping_result result{.new_partner = 2, .operation_type = 2};
    EXPECT_CALL(*routing_daemon, return_QNIC_address_to_destAddr(2)).Times(1).WillOnce(Return(5));
    auto info = std::make_unique<ConnectionSetupInfo>();
    info->qnic.type = QNIC_E;
    info->qnic.index = 0;
    EXPECT_CALL(*hardware_monitor, findConnectionInfoByQnicAddr(5)).Times(1).WillOnce(Return(ByMove(std::move(info))));
    EXPECT_CALL(*realtime_controller, applyZGate(qubit_record.get())).Times(1);
    EXPECT_CALL(*realtime_controller, applyXGate(_)).Times(0);
    rule_engine->updateResources_EntanglementSwapping(result);
  }
  delete qubit;
  delete hardware_monitor;
  delete routing_daemon;
  delete realtime_controller;
  delete rule_engine->qnic_store.get();
}
TEST(RuleEngineTest, updateResourcesEntanglementSwappingWithRuleSet) {
  /* setup components */
  prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* qubit = new MockQubit(QNIC_E, 7);
  auto* rule_engine = new RuleEngineTestTarget{qubit, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  std::unique_ptr<IQubitRecord> qubit_record = std::make_unique<QubitRecord>(QNIC_E, 7, 0);
  EXPECT_CALL(*dynamic_cast<MockQNicStore*>(rule_engine->qnic_store.get()), getQubitRecord(QNIC_E, 0, 0)).Times(1).WillRepeatedly(Return(qubit_record.get()));
  EXPECT_CALL(*realtime_controller, assertNoEntanglement(qubit_record.get())).Times(1);
  rule_engine->callInitialize();

  unsigned long ruleset_id = 3;
  unsigned long rule_id = 4;
  auto* ruleset = new ActiveRuleSet(ruleset_id, rule_id);
  {  // generate RuleSet
    auto rule = std::make_unique<ActiveRule>(ruleset_id, rule_id);
    rule->next_rule_id = rule_id + 1;
    rule->addResource(2, qubit);
    auto next_rule = std::make_unique<ActiveRule>(ruleset_id, rule_id + 1);

    ruleset->addRule(std::move(rule));
    ruleset->addRule(std::move(next_rule));
    rule_engine->rp.insert(ruleset);
    EXPECT_EQ(ruleset->rules.at(0)->resources.size(), 1);
    EXPECT_EQ(ruleset->rules.at(1)->resources.size(), 0);
  }

  swapping_result result{
      .id = {.ruleset_id = ruleset_id, .rule_id = rule_id, .index = 0},
      .new_partner = 2,
      .operation_type = 0,
  };
  EXPECT_CALL(*routing_daemon, return_QNIC_address_to_destAddr(2)).Times(1).WillOnce(Return(5));
  auto info = std::make_unique<ConnectionSetupInfo>();
  info->qnic.type = QNIC_E;
  info->qnic.index = 0;
  EXPECT_CALL(*hardware_monitor, findConnectionInfoByQnicAddr(5)).Times(1).WillOnce(Return(ByMove(std::move(info))));
  EXPECT_CALL(*qubit, X_gate()).Times(0);
  EXPECT_CALL(*qubit, Z_gate()).Times(0);
  rule_engine->updateResources_EntanglementSwapping(result);

  // check whether the qubit is promoted or not
  EXPECT_EQ(ruleset->rules.at(0)->resources.size(), 0);
  EXPECT_EQ(ruleset->rules.at(1)->resources.size(), 1);

  delete qubit;
  delete hardware_monitor;
  delete routing_daemon;
  delete realtime_controller;
  delete rule_engine->qnic_store.get();
}

TEST(RuleEngineTest, constructActiveRuleSet) {
  prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* qubit = new MockQubit(QNIC_E, 7);
  auto* rule_engine = new RuleEngineTestTarget{qubit, routing_daemon, hardware_monitor, realtime_controller, qnic_specs};
  std::unique_ptr<IQubitRecord> qubit_record = std::make_unique<QubitRecord>(QNIC_E, 7, 0);
  rule_engine->callInitialize();

  // prepare (static) ruleset being sent by responder
  unsigned long ruleset_id = 1234;
  int owner_address = 1;
  unsigned long rule_id0 = 5678;
  std::string rule0_name = "Purification";
  unsigned long rule_id1 = 5679;
  std::string rule1_name = "Swapping";
  RuleSet ruleset = RuleSet(ruleset_id, owner_address);  // static ruleset
  {
    // mock static ruleset
  }

  // auto* active_ruleset = rule_engine->constructActiveRuleSet(ruleset);

  // EXPECT_EQ(active_ruleset->ruleset_id, ruleset_id);
  // auto* rule0 = active_ruleset->getRule(0);
  // EXPECT_EQ(rule0->rule_id, rule_id0);
  // EXPECT_EQ(rule0->name, rule0_name);
  // auto* rule1 = active_ruleset->getRule(1);
  // EXPECT_EQ(rule1->rule_id, rule_id1);
  // EXPECT_EQ(rule1->name, rule1_name);
}

}  // namespace

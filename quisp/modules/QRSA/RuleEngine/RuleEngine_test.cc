
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include <test_utils/TestUtils.h>
#include <memory>
#include <utility>

#include "BellPairStore.h"
#include "IRuleEngine.h"
#include "RuleEngine.h"

#include "modules/QNIC.h"
#include "modules/QNIC/StationaryQubit/StationaryQubit.h"
#include "modules/QRSA/HardwareMonitor/HardwareMonitor.h"
#include "modules/QRSA/HardwareMonitor/IHardwareMonitor.h"
#include "modules/QRSA/RealTimeController/IRealTimeController.h"
#include "modules/QRSA/RoutingDaemon/RoutingDaemon.h"
#include "rules/Action.h"
#include "rules/RuleSet.h"

namespace {

using namespace omnetpp;
using namespace quisp::utils;
using namespace quisp::rules;
using namespace quisp::rules::actions;
using quisp::rules::actions::Action;
using namespace quisp::modules;
using namespace quisp_test;
using namespace testing;

class MockStationaryQubit : public StationaryQubit {
 public:
  MockStationaryQubit(QNIC_type _type, QNicIndex index) {
    qnic_type = _type;
    qnic_index = index;
  }

  MOCK_METHOD(void, emitPhoton, (int pulse), (override));
  MOCK_METHOD(void, setFree, (bool consumed), (override));
};

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy() : mockQubit(nullptr), routingDaemon(nullptr), hardwareMonitor(nullptr) {}
  Strategy(MockStationaryQubit* _qubit, MockRoutingDaemon* routing_daemon, MockHardwareMonitor* hardware_monitor, MockRealTimeController* realtime_controller)
      : mockQubit(_qubit), routingDaemon(routing_daemon), hardwareMonitor(hardware_monitor), realtimeController(realtime_controller) {}
  ~Strategy() {
    delete mockQubit;
    delete routingDaemon;
    delete hardwareMonitor;
    delete realtimeController;
  }
  MockStationaryQubit* mockQubit = nullptr;
  MockRoutingDaemon* routingDaemon = nullptr;
  MockHardwareMonitor* hardwareMonitor = nullptr;
  MockRealTimeController* realtimeController = nullptr;
  StationaryQubit* getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) override {
    if (mockQubit == nullptr) mockQubit = new MockStationaryQubit(QNIC_E, 1);
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
  using quisp::modules::RuleEngine::initialize;
  using quisp::modules::RuleEngine::par;
  using quisp::modules::RuleEngine::storeCheck_Purification_Agreement;
  using quisp::modules::RuleEngine::Unlock_resource_and_discard;
  using quisp::modules::RuleEngine::Unlock_resource_and_upgrade_stage;
  using quisp::modules::RuleEngine::updateAppliedRule;

  RuleEngineTestTarget(MockStationaryQubit* mockQubit, MockRoutingDaemon* routingdaemon, MockHardwareMonitor* hardware_monitor, MockRealTimeController* realtime_controller)
      : quisp::modules::RuleEngine() {
    setParInt(this, "address", 123);
    setParInt(this, "number_of_qnics_rp", 0);
    setParInt(this, "number_of_qnics_r", 1);
    setParInt(this, "number_of_qnics", 1);
    setParInt(this, "total_number_of_qnics", 2);
    setName("rule_engine_test_target");
    provider.setStrategy(std::make_unique<Strategy>(mockQubit, routingdaemon, hardware_monitor, realtime_controller));
    setComponentType(new TestModuleType("rule_engine_test"));
  }
  // setter function for allResorces[qnic_type][qnic_index]
  void setAllResources(int partner_addr, StationaryQubit* qubit) { this->bell_pair_store.insertEntangledQubit(partner_addr, qubit); };
  void setTracker(int qnic_address, int shot_number, QubitAddr_cons qubit_address) { this->tracker[qnic_address].insert(std::make_pair(shot_number, qubit_address)); };

 private:
  FRIEND_TEST(RuleEngineTest, ESResourceUpdate);
  FRIEND_TEST(RuleEngineTest, trackerUpdate);
  friend class MockRoutingDaemon;
  friend class MockHardwareMonitor;
};

TEST(RuleEngineTest, ESResourceUpdate) {
  // 1 (wait) -- 2(ES) -- 3(wait)
  // from wait to next rule
  auto* sim = prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto* mockQubit1 = new MockStationaryQubit(QNIC_E, 0);
  auto rule_engine = new RuleEngineTestTarget{mockQubit1, routingdaemon, mockHardwareMonitor, nullptr};

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
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_E)).Times(2).WillOnce(Return(2)).WillOnce(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_R)).Times(2).WillOnce(Return(2)).WillOnce(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, findConnectionInfoByQnicAddr(1)).Times(1).WillOnce(Return(ByMove(std::move(info))));

  // 0. set ruleset
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  auto* rs = new RuleSet(mock_ruleset_id, mock_rule_id, {});  // ruleset_id, ruleset_owner, partners
  auto wait_rule = std::make_unique<Rule>();
  wait_rule->ruleset_id = mock_ruleset_id;
  wait_rule->rule_index = mock_rule_id;
  wait_rule->next_rule_id = mock_next_rule_id;
  rs->addRule(std::move(wait_rule));
  auto next_rule = std::make_unique<Rule>();
  next_rule->ruleset_id = mock_ruleset_id;
  next_rule->rule_index = mock_next_rule_id;
  rs->addRule(std::move(next_rule));

  rule_engine->rp.insert(std::make_pair(0, rs));
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
}

TEST(RuleEngineTest, resourceAllocation) {
  auto* sim = prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_E)).WillRepeatedly(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_R)).WillRepeatedly(Return(1));
  auto mockQubit0 = new MockStationaryQubit(QNIC_E, 3);
  auto mockQubit1 = new MockStationaryQubit(QNIC_E, 3);
  auto mockQubit2 = new MockStationaryQubit(QNIC_E, 3);
  auto rule_engine = new RuleEngineTestTarget{mockQubit1, routingdaemon, mockHardwareMonitor, nullptr};
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  rule_engine->setAllResources(0, mockQubit0);
  rule_engine->setAllResources(1, mockQubit1);
  rule_engine->setAllResources(2, mockQubit2);
  auto* rs = new RuleSet(0, 0, 1);
  auto rule = std::make_unique<Rule>();
  // owner address,
  auto* action = new RandomMeasureAction(0, 1, QNIC_E, 3, 1, 10);

  rule->setAction(action);
  rule->action_partners = {1};
  rs->addRule(std::move(rule));
  rule_engine->rp.insert(std::make_pair(0, rs));

  rule_engine->ResourceAllocation(QNIC_E, 3);

  // resource allocation assigns a corresponding qubit to action's resource
  auto& _rs = rule_engine->rp.at(0);
  EXPECT_NE(_rs, nullptr);
  EXPECT_EQ(_rs->size(), 1);
  auto& _rule = _rs->getRule(0);
  EXPECT_FALSE(_rule == nullptr);
  EXPECT_EQ(_rule->resources.size(), 1);
  delete mockHardwareMonitor;
  delete routingdaemon;
}

TEST(RuleEngineTest, trackerUpdate) {
  // 1. initialize tracker
  prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto* mockRealTimeController = new MockRealTimeController;
  auto rule_engine = new RuleEngineTestTarget{nullptr, routingdaemon, mockHardwareMonitor, mockRealTimeController};
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_E)).WillRepeatedly(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_R)).WillRepeatedly(Return(1));
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
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller};
  EXPECT_CALL(*hardware_monitor, getQnicNumQubits(0, QNIC_E)).Times(3).WillRepeatedly(Return(2));
  EXPECT_CALL(*hardware_monitor, getQnicNumQubits(0, QNIC_R)).Times(3).WillRepeatedly(Return(2));
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
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller};
  EXPECT_CALL(*hardware_monitor, getQnicNumQubits(0, QNIC_E)).Times(3).WillRepeatedly(Return(2));
  EXPECT_CALL(*hardware_monitor, getQnicNumQubits(0, QNIC_R)).Times(3).WillRepeatedly(Return(2));
  rule_engine->callInitialize();
  unsigned long ruleset_id = 4;
  int partner_addr = 5;
  int action_index = 3;
  auto* ruleset = new RuleSet(ruleset_id, rule_engine->parentAddress, partner_addr);
  unsigned long target_rule_id = 10;
  auto rule1 = new Rule(ruleset_id, target_rule_id);
  auto rule2 = new Rule(ruleset_id, 11);
  auto* qubit = new MockQubit(QNIC_E, 0);

  qubit->action_index = action_index;
  rule1->addResource(partner_addr, qubit);
  rule1->next_rule_id = rule2->rule_index;
  ruleset->addRule(std::unique_ptr<Rule>(rule1));
  ruleset->addRule(std::unique_ptr<Rule>(rule2));

  rule_engine->rp.insert(std::make_pair(1, ruleset));
  EXPECT_CALL(*qubit, Unlock()).Times(1);

  purification_result result{
      .id = {.ruleset_id = ruleset_id, .rule_id = rule1->rule_index, .index = action_index},
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
  EXPECT_CALL(*hardware_monitor, getQnicNumQubits(0, QNIC_E)).Times(3).WillRepeatedly(Return(2));
  EXPECT_CALL(*hardware_monitor, getQnicNumQubits(0, QNIC_R)).Times(3).WillRepeatedly(Return(2));
  rule_engine->callInitialize();
  int qnic_index = 7;
  auto* qubit = new MockQubit(QNIC_E, qnic_index);
  qubit->fillParams();
  rule_engine->updateAppliedRule(qubit, 0);
  EXPECT_FALSE(rule_engine->checkAppliedRule(qubit, 0));

  EXPECT_CALL(*realtime_controller, ReInitialize_StationaryQubit(qnic_index, 1, QNIC_E, true)).Times(1).WillOnce(Return());
  rule_engine->freeConsumedResource(qnic_index, qubit, QNIC_E);
  EXPECT_TRUE(rule_engine->checkAppliedRule(qubit, 0));
  delete qubit;
  delete hardware_monitor;
  delete realtime_controller;
}

TEST(RuleEngineTest, unlockResourceAndDiscard) {
  prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller};
  // prevent creation of the qubits in the Busy_OR_Free_QubitState_table.
  EXPECT_CALL(*hardware_monitor, getQnicNumQubits(0, QNIC_E)).Times(1).WillRepeatedly(Return(0));
  EXPECT_CALL(*hardware_monitor, getQnicNumQubits(0, QNIC_R)).Times(1).WillRepeatedly(Return(0));
  rule_engine->callInitialize();

  unsigned long ruleset_id = 4;
  int partner_addr = 5;
  int action_index = 3;
  auto* ruleset = new RuleSet(ruleset_id, rule_engine->parentAddress, partner_addr);
  unsigned long target_rule_id = 10;
  auto rule1 = new Rule(ruleset_id, target_rule_id);
  auto rule2 = new Rule(ruleset_id, 11);
  int qnic_index = 17;
  auto* qubit = new MockQubit(QNIC_E, qnic_index);
  qubit->fillParams();
  qubit->action_index = action_index;
  rule1->addResource(partner_addr, qubit);
  rule1->next_rule_id = rule2->rule_index;
  ruleset->addRule(std::unique_ptr<Rule>(rule1));
  ruleset->addRule(std::unique_ptr<Rule>(rule2));

  rule_engine->rp.insert(std::make_pair(1, ruleset));
  EXPECT_CALL(*qubit, Unlock()).Times(1);

  rule_engine->updateAppliedRule(qubit, 0);
  EXPECT_EQ(rule1->resources.size(), 1);
  EXPECT_EQ(rule2->resources.size(), 0);
  EXPECT_CALL(*realtime_controller, ReInitialize_StationaryQubit(qnic_index, 1, QNIC_E, true)).Times(1).WillOnce(Return());
  rule_engine->Unlock_resource_and_discard(ruleset_id, target_rule_id, action_index);

  EXPECT_EQ(rule1->resources.size(), 0);
  EXPECT_EQ(rule2->resources.size(), 0);

  delete qubit;
  delete hardware_monitor;
  delete realtime_controller;
}

TEST(RuleEngineTest, unlockResourceAndUpgradeStage) {
  prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller};
  EXPECT_CALL(*hardware_monitor, getQnicNumQubits(0, QNIC_E)).Times(3).WillRepeatedly(Return(2));
  EXPECT_CALL(*hardware_monitor, getQnicNumQubits(0, QNIC_R)).Times(3).WillRepeatedly(Return(2));
  rule_engine->callInitialize();

  unsigned long ruleset_id = 4;
  int partner_addr = 5;
  int action_index = 3;

  auto* ruleset = new RuleSet(ruleset_id, rule_engine->parentAddress, partner_addr);
  unsigned long target_rule_id = 10;
  auto rule1 = new Rule(ruleset_id, target_rule_id);
  auto rule2 = new Rule(ruleset_id, 11);
  auto* qubit = new MockQubit(QNIC_E, 0);

  qubit->action_index = action_index;
  rule1->addResource(partner_addr, qubit);
  rule1->next_rule_id = rule2->rule_index;
  ruleset->addRule(std::unique_ptr<Rule>(rule1));
  ruleset->addRule(std::unique_ptr<Rule>(rule2));

  rule_engine->rp.insert(std::make_pair(1, ruleset));
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
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller};
  EXPECT_CALL(*hardware_monitor, getQnicNumQubits(0, QNIC_E)).Times(3).WillRepeatedly(Return(2));
  EXPECT_CALL(*hardware_monitor, getQnicNumQubits(0, QNIC_R)).Times(3).WillRepeatedly(Return(2));
  rule_engine->callInitialize();

  unsigned long ruleset_id = 4;
  int partner_addr = 5;
  int action_index = 3;

  auto* ruleset = new RuleSet(ruleset_id, rule_engine->parentAddress, partner_addr);
  unsigned long target_rule_id = 10;
  auto rule = new Rule(ruleset_id, target_rule_id);
  auto* qubit = new MockQubit(QNIC_E, 0);

  qubit->action_index = action_index;
  rule->addResource(partner_addr, qubit);
  ruleset->addRule(std::unique_ptr<Rule>(rule));

  rule_engine->rp.insert(std::make_pair(1, ruleset));
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
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller};
  EXPECT_CALL(*hardware_monitor, getQnicNumQubits(0, QNIC_E)).Times(3).WillRepeatedly(Return(2));
  EXPECT_CALL(*hardware_monitor, getQnicNumQubits(0, QNIC_R)).Times(3).WillRepeatedly(Return(2));
  rule_engine->callInitialize();

  EXPECT_NO_THROW({ rule_engine->Unlock_resource_and_upgrade_stage(101, 102, 103); });
  delete hardware_monitor;
}

TEST(RuleEngineTest, updateAndCheckAppliedRule) {
  prepareSimulation();
  auto* routing_daemon = new MockRoutingDaemon;
  auto* hardware_monitor = new MockHardwareMonitor;
  auto* realtime_controller = new MockRealTimeController;
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller};
  EXPECT_CALL(*hardware_monitor, getQnicNumQubits(0, QNIC_E)).Times(3).WillRepeatedly(Return(2));
  EXPECT_CALL(*hardware_monitor, getQnicNumQubits(0, QNIC_R)).Times(3).WillRepeatedly(Return(2));
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
  auto* rule_engine = new RuleEngineTestTarget{nullptr, routing_daemon, hardware_monitor, realtime_controller};
  EXPECT_CALL(*hardware_monitor, getQnicNumQubits(0, QNIC_E)).Times(3).WillRepeatedly(Return(2));
  EXPECT_CALL(*hardware_monitor, getQnicNumQubits(0, QNIC_R)).Times(3).WillRepeatedly(Return(2));
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
}  // namespace

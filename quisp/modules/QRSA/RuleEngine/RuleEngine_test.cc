
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

class MockRoutingDaemon : public RoutingDaemon {
 public:
  MOCK_METHOD(int, return_QNIC_address_to_destAddr, (int destAddr), (override));
};

class MockHardwareMonitor : public IHardwareMonitor {
 public:
  MOCK_METHOD(int, getQnicNumQubits, (int i, QNIC_type qnic_type), (override));
  MOCK_METHOD(NeighborTable, passNeighborTable, (), (override));
  MOCK_METHOD(std::unique_ptr<InterfaceInfo>, findInterfaceByNeighborAddr, (int neighbor_address), (override));
  MOCK_METHOD(std::unique_ptr<ConnectionSetupInfo>, findConnectionInfoByQnicAddr, (int qnic_address), (override));
};

class MockRealTimeController : public IRealTimeController {
 public:
  MOCK_METHOD(void, initialize, (), (override));
  MOCK_METHOD(void, handleMessage, (cMessage * msg), (override));
  MOCK_METHOD(void, EmitPhoton, (int qnic_index, int qubit_index, QNIC_type qnic_type, int pulse), (override));
  MOCK_METHOD(void, ReInitialize_StationaryQubit, (int qnic_index, int qubit_index, QNIC_type qnic_type, bool consumed), (override));
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
  using quisp::modules::RuleEngine::initialize;
  using quisp::modules::RuleEngine::par;
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

  Process proc;
  proc.owner_addr = 0;
  proc.Rs = rs;
  rule_engine->rp.insert(std::make_pair(0, proc));
  rule_engine->rp[0].Rs->getRule(0)->addResource(1, mockQubit1);
  ASSERT_EQ(rule_engine->rp[0].Rs->getRule(0)->resources.size(), 1);
  ASSERT_EQ(rule_engine->rp[0].Rs->getRule(1)->resources.size(), 0);
  rule_engine->updateResources_EntanglementSwapping(swapr);
  // 1. remove from previous rule
  ASSERT_EQ(rule_engine->rp[0].Rs->getRule(0)->resources.size(), 0);
  // // 2. add to the next rule
  ASSERT_EQ(rule_engine->rp[0].Rs->getRule(1)->resources.size(), 1);
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
  Process proc;
  proc.owner_addr = 0;
  proc.Rs = rs;
  rule_engine->rp.insert(std::make_pair(0, proc));

  rule_engine->ResourceAllocation(QNIC_E, 3);

  // resource allocation assigns a corresponding qubit to action's resource
  auto* _rs = rule_engine->rp.at(0).Rs;
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
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto* mockRealTimeController = new MockRealTimeController;
  auto rule_engine = new RuleEngineTestTarget{nullptr, routingdaemon, mockHardwareMonitor, mockRealTimeController};
}

TEST(RuleEngineTest, storeCheckPurificationAgreement_running_process) {
  prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto* mockRealTimeController = new MockRealTimeController;
  auto rule_engine = new RuleEngineTestTarget{nullptr, routingdaemon, mockHardwareMonitor, mockRealTimeController};
}

TEST(RuleEngineTest, unlockResourceAndDiscard) {
  prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto* mockRealTimeController = new MockRealTimeController;
  auto rule_engine = new RuleEngineTestTarget{nullptr, routingdaemon, mockHardwareMonitor, mockRealTimeController};
}

TEST(RuleEngineTest, unlockResourceAndUpgradeStage) {
  prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto* mockRealTimeController = new MockRealTimeController;
  auto rule_engine = new RuleEngineTestTarget{nullptr, routingdaemon, mockHardwareMonitor, mockRealTimeController};
}

TEST(RuleEngineTest, updateAppliedRule) {
  prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto* mockRealTimeController = new MockRealTimeController;
  auto rule_engine = new RuleEngineTestTarget{nullptr, routingdaemon, mockHardwareMonitor, mockRealTimeController};
}

TEST(RuleEngineTest, checkAppliedRule) {
  prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto* mockRealTimeController = new MockRealTimeController;
  auto rule_engine = new RuleEngineTestTarget{nullptr, routingdaemon, mockHardwareMonitor, mockRealTimeController};
}
}  // namespace

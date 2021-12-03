
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include <test_utils/TestUtils.h>
#include <memory>
#include <utility>

#include "BellPairStore/BellPairStore.h"
#include "IRuleEngine.h"
#include "RuleEngine.h"

#include "messages/QNode_ipc_messages_m.h"
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

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy() : mockQubit(nullptr), routingDaemon(nullptr), hardwareMonitor(nullptr) {}
  Strategy(IStationaryQubit* _qubit, MockRoutingDaemon* routing_daemon, MockHardwareMonitor* hardware_monitor, MockRealTimeController* realtime_controller)
      : mockQubit(_qubit), routingDaemon(routing_daemon), hardwareMonitor(hardware_monitor), realtimeController(realtime_controller) {}
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
  using quisp::modules::RuleEngine::initialize;
  using quisp::modules::RuleEngine::par;
  using quisp::modules::RuleEngine::scheduleNextEmissionEvent;
  using quisp::modules::RuleEngine::shootPhoton;

  RuleEngineTestTarget(IStationaryQubit* mockQubit, MockRoutingDaemon* routingdaemon, MockHardwareMonitor* hardware_monitor, MockRealTimeController* realtime_controller)
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
  void setAllResources(int partner_addr, IStationaryQubit* qubit) { this->bell_pair_store.insertEntangledQubit(partner_addr, qubit); };
  void setTracker(int qnic_address, int shot_number, QubitAddr_cons qubit_address) { this->tracker[qnic_address].insert(std::make_pair(shot_number, qubit_address)); };

 private:
  FRIEND_TEST(RuleEngineTest, ESResourceUpdate);
  FRIEND_TEST(RuleEngineTest, trackerUpdate);
  friend class MockRoutingDaemon;
  friend class MockHardwareMonitor;
};

TEST(RuleEnginePhotonShootingTest, ShootPhoton) {
  auto* sim = prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto* mockQubit1 = new MockQubit(QNIC_E, 0);
  auto rule_engine = new RuleEngineTestTarget{mockQubit1, routingdaemon, mockHardwareMonitor, nullptr};

  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_E)).Times(2).WillOnce(Return(2)).WillOnce(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_R)).Times(2).WillOnce(Return(2)).WillOnce(Return(1));

  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();

  auto* pk = new SchedulePhotonTransmissionsOnebyOne();
  rule_engine->shootPhoton(pk);

  delete mockHardwareMonitor;
  delete routingdaemon;
  delete mockQubit1;
}

TEST(RuleEnginePhotonShootingTest, ScheduleNextEmissionEvent) {
  auto* sim = prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto* mockQubit1 = new MockQubit(QNIC_E, 0);
  auto rule_engine = new RuleEngineTestTarget{mockQubit1, routingdaemon, mockHardwareMonitor, nullptr};

  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_E)).Times(2).WillOnce(Return(2)).WillOnce(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_R)).Times(2).WillOnce(Return(2)).WillOnce(Return(1));

  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();

  sim->setContext(rule_engine);
  int qnic_index = 3;
  int qnic_address = 9;
  double interval = 0.5;
  simtime_t timing = sim->getSimTime();
  int num_sent = 5;
  bool internal = true;
  int trial = 7;

  rule_engine->scheduleNextEmissionEvent(qnic_index, qnic_address, interval, timing, num_sent, internal, trial);

  auto* fes = sim->getFES();
  ASSERT_EQ(fes->getLength(), 1);
  auto* res = fes->get(0);
  auto* packet = dynamic_cast<SchedulePhotonTransmissionsOnebyOne*>(res);
  EXPECT_EQ(packet->getQnic_index(), qnic_index);
  EXPECT_EQ(packet->getQnic_address(), qnic_address);
  EXPECT_EQ(packet->getInterval(), interval);
  EXPECT_EQ(packet->getTiming(), timing);
  EXPECT_EQ(packet->getNum_sent(), num_sent + 1);
  EXPECT_EQ(packet->getTrial(), trial);
  EXPECT_EQ(packet->getInternal_hom(), 1 /* internal HoM */);
  fes->clear();

  internal = false;
  rule_engine->scheduleNextEmissionEvent(qnic_index, qnic_address, interval, timing, num_sent, internal, trial);
  ASSERT_EQ(fes->getLength(), 1);
  res = fes->get(0);
  packet = dynamic_cast<SchedulePhotonTransmissionsOnebyOne*>(res);
  EXPECT_EQ(packet->getQnic_index(), qnic_index);
  EXPECT_EQ(packet->getQnic_address(), qnic_address);
  EXPECT_EQ(packet->getInterval(), interval);
  EXPECT_EQ(packet->getTiming(), timing);
  EXPECT_EQ(packet->getNum_sent(), num_sent + 1);
  EXPECT_EQ(packet->getTrial(), trial);
  EXPECT_EQ(packet->getInternal_hom(), 0 /* not internal HoM */);
  fes->clear();

  sim->setSimTime(3.0);
  num_sent = 1;
  timing = 1.5;
  rule_engine->scheduleNextEmissionEvent(qnic_index, qnic_address, interval, timing, num_sent, internal, trial);
  ASSERT_EQ(fes->getLength(), 1);
  res = fes->get(0);
  packet = dynamic_cast<SchedulePhotonTransmissionsOnebyOne*>(res);
  EXPECT_EQ(packet->getQnic_index(), qnic_index);
  EXPECT_EQ(packet->getQnic_address(), qnic_address);
  EXPECT_EQ(packet->getInterval(), interval);
  EXPECT_EQ(packet->getTiming(), timing);
  EXPECT_EQ(packet->getNum_sent(), num_sent + 1);
  EXPECT_EQ(packet->getTrial(), trial);
  EXPECT_EQ(packet->getInternal_hom(), 0 /* not internal HoM */);
  EXPECT_EQ(packet->getArrivalTime(), sim->getSimTime() + interval);
  fes->clear();

  sim->setSimTime(7.0);
  num_sent = 0;
  timing = 1.5;
  rule_engine->scheduleNextEmissionEvent(qnic_index, qnic_address, interval, timing, num_sent, internal, trial);
  ASSERT_EQ(fes->getLength(), 1);
  res = fes->get(0);
  packet = dynamic_cast<SchedulePhotonTransmissionsOnebyOne*>(res);
  EXPECT_EQ(packet->getQnic_index(), qnic_index);
  EXPECT_EQ(packet->getQnic_address(), qnic_address);
  EXPECT_EQ(packet->getInterval(), interval);
  EXPECT_EQ(packet->getTiming(), timing);
  EXPECT_EQ(packet->getNum_sent(), num_sent + 1);
  EXPECT_EQ(packet->getTrial(), trial);
  EXPECT_EQ(packet->getInternal_hom(), 0 /* not internal HoM */);
  EXPECT_EQ(packet->getArrivalTime(), sim->getSimTime() + timing);
  fes->clear();

  delete mockHardwareMonitor;
  delete routingdaemon;
}

}  // namespace

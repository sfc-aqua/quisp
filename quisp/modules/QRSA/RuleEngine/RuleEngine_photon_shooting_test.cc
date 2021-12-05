
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
#include "omnetpp/cmodule.h"
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
  cModule* temp_qnic;

 public:
  Strategy() : mockQubit(nullptr), routingDaemon(nullptr), hardwareMonitor(nullptr) {}
  Strategy(IStationaryQubit* _qubit, MockRoutingDaemon* routing_daemon, MockHardwareMonitor* hardware_monitor, MockRealTimeController* realtime_controller)
      : mockQubit(_qubit), routingDaemon(routing_daemon), hardwareMonitor(hardware_monitor), realtimeController(realtime_controller) {
    temp_qnic = new omnetpp::cModule();
    setParInt(temp_qnic, "burst_trial_counter", 0);
  }
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
  cModule* getQNIC(int qnic_index, QNIC_type qnic_type) override { return temp_qnic; }
};

class RuleEngineTestTarget : public quisp::modules::RuleEngine {
 public:
  using quisp::modules::RuleEngine::burstTrial_outdated;
  using quisp::modules::RuleEngine::checkAppliedRule;
  using quisp::modules::RuleEngine::clearAppliedRule;
  using quisp::modules::RuleEngine::incrementBurstTrial;
  using quisp::modules::RuleEngine::initialize;
  using quisp::modules::RuleEngine::ntable;
  using quisp::modules::RuleEngine::par;
  using quisp::modules::RuleEngine::scheduleNextEmissionEvent;
  using quisp::modules::RuleEngine::shootPhoton;
  using quisp::modules::RuleEngine::shootPhoton_internal;

  RuleEngineTestTarget(IStationaryQubit* mockQubit, MockRoutingDaemon* routingdaemon, MockHardwareMonitor* hardware_monitor, MockRealTimeController* realtime_controller)
      : quisp::modules::RuleEngine() {
    setParInt(this, "address", 123);
    setParInt(this, "number_of_qnics_rp", 0);
    setParInt(this, "number_of_qnics_r", 1);
    setParInt(this, "number_of_qnics", 3);
    setParInt(this, "total_number_of_qnics", 2);
    setName("rule_engine_test_target");
    provider.setStrategy(std::make_unique<Strategy>(mockQubit, routingdaemon, hardware_monitor, realtime_controller));
    setComponentType(new TestModuleType("rule_engine_test"));
  }
  // setter function for allResorces[qnic_type][qnic_index]
  void setAllResources(int partner_addr, IStationaryQubit* qubit) { this->bell_pair_store.insertEntangledQubit(partner_addr, qubit); };
  void setTracker(int qnic_address, int shot_number, QubitAddr_cons qubit_address) { this->tracker[qnic_address].insert(std::make_pair(shot_number, qubit_address)); };
  void setQubitBusyInQnic(int qnic_type, int qnic_index, int qubit_index) {
    Busy_OR_Free_QubitState_table[qnic_type] = this->setQubitBusy_inQnic(Busy_OR_Free_QubitState_table[qnic_type], qnic_index, qubit_index);
  };
  int getNumFreeQubitsInQnic(int qnic_type, int qnic_index) { return countFreeQubits_inQnic(Busy_OR_Free_QubitState_table[qnic_type], qnic_index); }

  int getBurstCountByQnic(int qnic_address) { return this->qnic_burst_trial_counter[qnic_address]; }

 private:
  FRIEND_TEST(RuleEngineTest, ESResourceUpdate);
  FRIEND_TEST(RuleEngineTest, trackerUpdate);
  friend class MockRoutingDaemon;
  friend class MockHardwareMonitor;
};

TEST(RuleEnginePhotonShootingTest, ShootPhotonWithoutFreeQubit) {
  auto* sim = prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto* mockQubit1 = new MockQubit(QNIC_E, 0);
  auto rule_engine = new RuleEngineTestTarget{mockQubit1, routingdaemon, mockHardwareMonitor, nullptr};

  // Emitter QNIC(index:0~2) has 1 qubit, Receiver QNIC(index:0) has 1 qubit
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_E)).WillRepeatedly(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(1, QNIC_E)).WillRepeatedly(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(2, QNIC_E)).WillRepeatedly(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_R)).WillRepeatedly(Return(1));

  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  sim->setContext(rule_engine);

  int qnic_index = 1;
  // no free qubit case
  auto* pk = new SchedulePhotonTransmissionsOnebyOne();
  pk->setQnic_index(1);
  // set qubit in Emitter QNIC1 to busy, so there's no free qubit.
  rule_engine->setQubitBusyInQnic(QNIC_E, qnic_index, 0);
  rule_engine->shootPhoton(pk);
  auto* fes = sim->getFES();
  ASSERT_EQ(fes->getLength(), 0);
  fes->clear();

  delete mockHardwareMonitor;
  delete routingdaemon;
  delete mockQubit1;
}

TEST(RuleEnginePhotonShootingTest, ShootPhotonWithSingleFreeQubit) {
  auto* sim = prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  int qnic_index = 1;

  auto* mockQubit1 = new MockQubit(QNIC_E, qnic_index);
  auto rule_engine = new RuleEngineTestTarget{mockQubit1, routingdaemon, mockHardwareMonitor, nullptr};

  // Emitter QNIC(index:0~2) has 2 qubit, Receiver QNIC(index:0) has 1 qubit
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_E)).WillRepeatedly(Return(2));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(1, QNIC_E)).WillRepeatedly(Return(2));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(2, QNIC_E)).WillRepeatedly(Return(2));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_R)).WillRepeatedly(Return(1));

  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  rule_engine->setQubitBusyInQnic(QNIC_E, qnic_index, 0);
  EXPECT_EQ(rule_engine->getNumFreeQubitsInQnic(QNIC_E, qnic_index), 1);
  sim->setContext(rule_engine);
  auto* fes = sim->getFES();

  int qnic_address = 1234;
  int trial = 1;
  int num_sent = 0;
  double interval = 5.3;

  {
    auto pk = new SchedulePhotonTransmissionsOnebyOne();
    pk->setQnic_index(qnic_index);
    pk->setNum_sent(num_sent);
    pk->setTrial(trial);
    pk->setQnic_address(qnic_address);
    pk->setInterval(interval);

    rule_engine->shootPhoton(pk);
    ASSERT_EQ(fes->getLength(), 2);
    auto* res1 = fes->get(0);
    auto* res2 = fes->get(1);
    auto* emitReq = dynamic_cast<EmitPhotonRequest*>(res1);
    ASSERT_NE(emitReq, nullptr);
    auto* scheduled = dynamic_cast<SchedulePhotonTransmissionsOnebyOne*>(res2);
    ASSERT_NE(scheduled, nullptr);

    EXPECT_EQ(emitReq->getKind(), STATIONARYQUBIT_PULSE_BOUND);
    EXPECT_EQ(emitReq->getQnic_address(), qnic_address);
    EXPECT_EQ(emitReq->getQnic_index(), qnic_index);
    EXPECT_EQ(emitReq->getQubit_index(), 1);
    EXPECT_EQ(emitReq->getTrial(), trial);
    EXPECT_EQ(emitReq->getQnic_type(), QNIC_E);
    // no free qubit left
    EXPECT_EQ(rule_engine->getNumFreeQubitsInQnic(QNIC_E, qnic_index), 0);

    EXPECT_EQ(scheduled->getQnic_address(), qnic_address);
    EXPECT_EQ(scheduled->getQnic_index(), qnic_index);
    EXPECT_EQ(scheduled->getNum_sent(), num_sent + 1);
    EXPECT_EQ(scheduled->getTrial(), trial);
    EXPECT_EQ(scheduled->getInterval(), interval);
    fes->clear();
  }

  delete mockHardwareMonitor;
  delete routingdaemon;
  delete mockQubit1;
}

TEST(RuleEnginePhotonShootingTest, ShootPhotonWithThreeFreeQubits) {
  auto* sim = prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  int qnic_index = 1;

  auto* mockQubit1 = new MockQubit(QNIC_E, qnic_index);
  auto rule_engine = new RuleEngineTestTarget{mockQubit1, routingdaemon, mockHardwareMonitor, nullptr};

  // Emitter QNIC(index:0~2) has 2 qubit, Receiver QNIC(index:0) has 1 qubit
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_E)).WillRepeatedly(Return(3));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(1, QNIC_E)).WillRepeatedly(Return(3));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(2, QNIC_E)).WillRepeatedly(Return(3));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_R)).WillRepeatedly(Return(1));

  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  EXPECT_EQ(rule_engine->getNumFreeQubitsInQnic(QNIC_E, qnic_index), 3);
  sim->setContext(rule_engine);
  auto* fes = sim->getFES();

  int qnic_address = 1234;
  int trial = 1;
  int num_sent = 0;
  double interval = 5.3;

  {  // first shot
    auto pk = new SchedulePhotonTransmissionsOnebyOne();
    pk->setQnic_index(qnic_index);
    pk->setNum_sent(num_sent);
    pk->setTrial(trial);
    pk->setQnic_address(qnic_address);
    pk->setInterval(interval);

    rule_engine->shootPhoton(pk);
    ASSERT_EQ(fes->getLength(), 2);
    auto* res1 = fes->get(0);
    auto* res2 = fes->get(1);
    auto* emitReq = dynamic_cast<EmitPhotonRequest*>(res1);
    ASSERT_NE(emitReq, nullptr);
    auto* scheduled = dynamic_cast<SchedulePhotonTransmissionsOnebyOne*>(res2);
    ASSERT_NE(scheduled, nullptr);

    EXPECT_EQ(emitReq->getKind(), STATIONARYQUBIT_PULSE_BEGIN);
    EXPECT_EQ(emitReq->getQnic_address(), qnic_address);
    EXPECT_EQ(emitReq->getQnic_index(), qnic_index);
    EXPECT_EQ(emitReq->getQubit_index(), 0);
    EXPECT_EQ(emitReq->getTrial(), trial);
    EXPECT_EQ(emitReq->getQnic_type(), QNIC_E);
    EXPECT_EQ(rule_engine->getNumFreeQubitsInQnic(QNIC_E, qnic_index), 2);

    EXPECT_EQ(scheduled->getQnic_address(), qnic_address);
    EXPECT_EQ(scheduled->getQnic_index(), qnic_index);
    EXPECT_EQ(scheduled->getNum_sent(), num_sent + 1);
    EXPECT_EQ(scheduled->getTrial(), trial);
    EXPECT_EQ(scheduled->getInterval(), interval);
    fes->clear();
  }

  {  // second shot
    num_sent += 1;
    auto pk = new SchedulePhotonTransmissionsOnebyOne();
    pk->setQnic_index(qnic_index);
    pk->setNum_sent(num_sent);
    pk->setTrial(trial);
    pk->setQnic_address(qnic_address);
    pk->setInterval(interval);

    rule_engine->shootPhoton(pk);
    ASSERT_EQ(fes->getLength(), 2);
    auto* res1 = fes->get(0);
    auto* res2 = fes->get(1);
    auto* emitReq = dynamic_cast<EmitPhotonRequest*>(res1);
    ASSERT_NE(emitReq, nullptr);
    auto* scheduled = dynamic_cast<SchedulePhotonTransmissionsOnebyOne*>(res2);
    ASSERT_NE(scheduled, nullptr);

    EXPECT_EQ(emitReq->getKind(), 0);
    EXPECT_EQ(emitReq->getQnic_address(), qnic_address);
    EXPECT_EQ(emitReq->getQnic_index(), qnic_index);
    EXPECT_EQ(emitReq->getQubit_index(), 1);
    EXPECT_EQ(emitReq->getTrial(), trial);
    EXPECT_EQ(emitReq->getQnic_type(), QNIC_E);
    EXPECT_EQ(rule_engine->getNumFreeQubitsInQnic(QNIC_E, qnic_index), 1);

    EXPECT_EQ(scheduled->getQnic_address(), qnic_address);
    EXPECT_EQ(scheduled->getQnic_index(), qnic_index);
    EXPECT_EQ(scheduled->getNum_sent(), num_sent + 1);
    EXPECT_EQ(scheduled->getTrial(), trial);
    EXPECT_EQ(scheduled->getInterval(), interval);
    fes->clear();
  }

  {  // last shot
    num_sent += 1;
    auto pk = new SchedulePhotonTransmissionsOnebyOne();
    pk->setQnic_index(qnic_index);
    pk->setNum_sent(num_sent);
    pk->setTrial(trial);
    pk->setQnic_address(qnic_address);
    pk->setInterval(interval);

    rule_engine->shootPhoton(pk);
    ASSERT_EQ(fes->getLength(), 2);
    auto* res1 = fes->get(0);
    auto* res2 = fes->get(1);
    auto* emitReq = dynamic_cast<EmitPhotonRequest*>(res1);
    ASSERT_NE(emitReq, nullptr);
    auto* scheduled = dynamic_cast<SchedulePhotonTransmissionsOnebyOne*>(res2);
    ASSERT_NE(scheduled, nullptr);

    EXPECT_EQ(emitReq->getKind(), STATIONARYQUBIT_PULSE_END);
    EXPECT_EQ(emitReq->getQnic_address(), qnic_address);
    EXPECT_EQ(emitReq->getQnic_index(), qnic_index);
    EXPECT_EQ(emitReq->getQubit_index(), 2);
    EXPECT_EQ(emitReq->getTrial(), trial);
    EXPECT_EQ(emitReq->getQnic_type(), QNIC_E);
    EXPECT_EQ(rule_engine->getNumFreeQubitsInQnic(QNIC_E, qnic_index), 0);

    EXPECT_EQ(scheduled->getQnic_address(), qnic_address);
    EXPECT_EQ(scheduled->getQnic_index(), qnic_index);
    EXPECT_EQ(scheduled->getNum_sent(), num_sent + 1);
    EXPECT_EQ(scheduled->getTrial(), trial);
    EXPECT_EQ(scheduled->getInterval(), interval);
    fes->clear();
  }
  delete mockHardwareMonitor;
  delete routingdaemon;
  delete mockQubit1;
}

TEST(RuleEnginePhotonShootingTest, ShootPhotonInternalWithoutFreeQubit) {
  auto* sim = prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto* mockQubit1 = new MockQubit(QNIC_E, 0);
  auto rule_engine = new RuleEngineTestTarget{mockQubit1, routingdaemon, mockHardwareMonitor, nullptr};

  // Emitter QNIC(index:0~2) has 1 qubit, Receiver QNIC(index:0) has 1 qubit
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_E)).WillRepeatedly(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(1, QNIC_E)).WillRepeatedly(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(2, QNIC_E)).WillRepeatedly(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_R)).WillRepeatedly(Return(1));

  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  sim->setContext(rule_engine);

  int qnic_index = 1;
  // no free qubit case
  auto* pk = new SchedulePhotonTransmissionsOnebyOne();
  pk->setQnic_index(1);
  // set qubit in Emitter QNIC1 to busy, so there's no free qubit.
  rule_engine->setQubitBusyInQnic(QNIC_E, qnic_index, 0);
  rule_engine->shootPhoton_internal(pk);
  auto* fes = sim->getFES();
  ASSERT_EQ(fes->getLength(), 0);
  fes->clear();

  delete mockHardwareMonitor;
  delete routingdaemon;
  delete mockQubit1;
}

TEST(RuleEnginePhotonShootingTest, ShootPhotonInternalWithSingleFreeQubit) {
  auto* sim = prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  int qnic_index = 0;

  auto* mockQubit1 = new MockQubit(QNIC_E, qnic_index);
  auto rule_engine = new RuleEngineTestTarget{mockQubit1, routingdaemon, mockHardwareMonitor, nullptr};

  // Emitter QNIC(index:0~2) has 2 qubit, Receiver QNIC(index:0) has 1 qubit
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_E)).WillRepeatedly(Return(2));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(1, QNIC_E)).WillRepeatedly(Return(2));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(2, QNIC_E)).WillRepeatedly(Return(2));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_R)).WillRepeatedly(Return(1));

  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  EXPECT_EQ(rule_engine->getNumFreeQubitsInQnic(QNIC_R, qnic_index), 1);
  sim->setContext(rule_engine);
  auto* fes = sim->getFES();

  int qnic_address = 1234;
  int trial = 1;
  int num_sent = 0;
  double interval = 5.3;

  {
    auto pk = new SchedulePhotonTransmissionsOnebyOne();
    pk->setQnic_index(qnic_index);
    pk->setNum_sent(num_sent);
    pk->setTrial(trial);
    pk->setQnic_address(qnic_address);
    pk->setInterval(interval);

    rule_engine->shootPhoton_internal(pk);
    ASSERT_EQ(fes->getLength(), 2);
    auto* res1 = fes->get(0);
    auto* res2 = fes->get(1);
    auto* emitReq = dynamic_cast<EmitPhotonRequest*>(res1);
    ASSERT_NE(emitReq, nullptr);
    auto* scheduled = dynamic_cast<SchedulePhotonTransmissionsOnebyOne*>(res2);
    ASSERT_NE(scheduled, nullptr);

    EXPECT_EQ(emitReq->getKind(), STATIONARYQUBIT_PULSE_BOUND);
    EXPECT_EQ(emitReq->getQnic_address(), qnic_address);
    EXPECT_EQ(emitReq->getQnic_index(), qnic_index);
    EXPECT_EQ(emitReq->getQubit_index(), 0);
    EXPECT_EQ(emitReq->getTrial(), trial);
    EXPECT_EQ(emitReq->getQnic_type(), QNIC_R);
    // no free qubit left
    EXPECT_EQ(rule_engine->getNumFreeQubitsInQnic(QNIC_R, qnic_index), 0);

    EXPECT_EQ(scheduled->getQnic_address(), qnic_address);
    EXPECT_EQ(scheduled->getQnic_index(), qnic_index);
    EXPECT_EQ(scheduled->getNum_sent(), num_sent + 1);
    EXPECT_EQ(scheduled->getTrial(), trial);
    EXPECT_EQ(scheduled->getInterval(), interval);
    fes->clear();
  }

  delete mockHardwareMonitor;
  delete routingdaemon;
  delete mockQubit1;
}

TEST(RuleEnginePhotonShootingTest, ShootPhotonInternalWithThreeFreeQubits) {
  auto* sim = prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  int qnic_index = 0;

  auto* mockQubit1 = new MockQubit(QNIC_R, qnic_index);
  auto rule_engine = new RuleEngineTestTarget{mockQubit1, routingdaemon, mockHardwareMonitor, nullptr};

  // Emitter QNIC(index:0~2) has 1 qubit, Receiver QNIC(index:0) has 3 qubit
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_E)).WillRepeatedly(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(1, QNIC_E)).WillRepeatedly(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(2, QNIC_E)).WillRepeatedly(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_R)).WillRepeatedly(Return(3));

  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  EXPECT_EQ(rule_engine->getNumFreeQubitsInQnic(QNIC_R, qnic_index), 3);
  sim->setContext(rule_engine);
  auto* fes = sim->getFES();

  int qnic_address = 1234;
  int trial = 1;
  int num_sent = 0;
  double interval = 5.3;

  {  // first shot
    auto pk = new SchedulePhotonTransmissionsOnebyOne();
    pk->setQnic_index(qnic_index);
    pk->setNum_sent(num_sent);
    pk->setTrial(trial);
    pk->setQnic_address(qnic_address);
    pk->setInterval(interval);

    rule_engine->shootPhoton_internal(pk);
    ASSERT_EQ(fes->getLength(), 2);
    auto* res1 = fes->get(0);
    auto* res2 = fes->get(1);
    auto* emitReq = dynamic_cast<EmitPhotonRequest*>(res1);
    ASSERT_NE(emitReq, nullptr);
    auto* scheduled = dynamic_cast<SchedulePhotonTransmissionsOnebyOne*>(res2);
    ASSERT_NE(scheduled, nullptr);

    EXPECT_EQ(emitReq->getKind(), STATIONARYQUBIT_PULSE_BEGIN);
    EXPECT_EQ(emitReq->getQnic_address(), qnic_address);
    EXPECT_EQ(emitReq->getQnic_index(), qnic_index);
    EXPECT_EQ(emitReq->getQubit_index(), 0);
    EXPECT_EQ(emitReq->getTrial(), trial);
    EXPECT_EQ(emitReq->getQnic_type(), QNIC_R);
    EXPECT_EQ(rule_engine->getNumFreeQubitsInQnic(QNIC_R, qnic_index), 2);

    EXPECT_EQ(scheduled->getQnic_address(), qnic_address);
    EXPECT_EQ(scheduled->getQnic_index(), qnic_index);
    EXPECT_EQ(scheduled->getNum_sent(), num_sent + 1);
    EXPECT_EQ(scheduled->getTrial(), trial);
    EXPECT_EQ(scheduled->getInterval(), interval);
    fes->clear();
  }

  {  // second shot
    num_sent += 1;
    auto pk = new SchedulePhotonTransmissionsOnebyOne();
    pk->setQnic_index(qnic_index);
    pk->setNum_sent(num_sent);
    pk->setTrial(trial);
    pk->setQnic_address(qnic_address);
    pk->setInterval(interval);

    rule_engine->shootPhoton_internal(pk);
    ASSERT_EQ(fes->getLength(), 2);
    auto* res1 = fes->get(0);
    auto* res2 = fes->get(1);
    auto* emitReq = dynamic_cast<EmitPhotonRequest*>(res1);
    ASSERT_NE(emitReq, nullptr);
    auto* scheduled = dynamic_cast<SchedulePhotonTransmissionsOnebyOne*>(res2);
    ASSERT_NE(scheduled, nullptr);

    EXPECT_EQ(emitReq->getKind(), 0);
    EXPECT_EQ(emitReq->getQnic_address(), qnic_address);
    EXPECT_EQ(emitReq->getQnic_index(), qnic_index);
    EXPECT_EQ(emitReq->getQubit_index(), 1);
    EXPECT_EQ(emitReq->getTrial(), trial);
    EXPECT_EQ(emitReq->getQnic_type(), QNIC_R);
    EXPECT_EQ(rule_engine->getNumFreeQubitsInQnic(QNIC_R, qnic_index), 1);

    EXPECT_EQ(scheduled->getQnic_address(), qnic_address);
    EXPECT_EQ(scheduled->getQnic_index(), qnic_index);
    EXPECT_EQ(scheduled->getNum_sent(), num_sent + 1);
    EXPECT_EQ(scheduled->getTrial(), trial);
    EXPECT_EQ(scheduled->getInterval(), interval);
    fes->clear();
  }

  {  // last shot
    num_sent += 1;
    auto pk = new SchedulePhotonTransmissionsOnebyOne();
    pk->setQnic_index(qnic_index);
    pk->setNum_sent(num_sent);
    pk->setTrial(trial);
    pk->setQnic_address(qnic_address);
    pk->setInterval(interval);

    rule_engine->shootPhoton_internal(pk);
    ASSERT_EQ(fes->getLength(), 2);
    auto* res1 = fes->get(0);
    auto* res2 = fes->get(1);
    auto* emitReq = dynamic_cast<EmitPhotonRequest*>(res1);
    ASSERT_NE(emitReq, nullptr);
    auto* scheduled = dynamic_cast<SchedulePhotonTransmissionsOnebyOne*>(res2);
    ASSERT_NE(scheduled, nullptr);

    EXPECT_EQ(emitReq->getKind(), STATIONARYQUBIT_PULSE_END);
    EXPECT_EQ(emitReq->getQnic_address(), qnic_address);
    EXPECT_EQ(emitReq->getQnic_index(), qnic_index);
    EXPECT_EQ(emitReq->getQubit_index(), 2);
    EXPECT_EQ(emitReq->getTrial(), trial);
    EXPECT_EQ(emitReq->getQnic_type(), QNIC_R);
    EXPECT_EQ(rule_engine->getNumFreeQubitsInQnic(QNIC_R, qnic_index), 0);

    EXPECT_EQ(scheduled->getQnic_address(), qnic_address);
    EXPECT_EQ(scheduled->getQnic_index(), qnic_index);
    EXPECT_EQ(scheduled->getNum_sent(), num_sent + 1);
    EXPECT_EQ(scheduled->getTrial(), trial);
    EXPECT_EQ(scheduled->getInterval(), interval);
    fes->clear();
  }
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

  // Emitter QNIC(index:0~2) has 1 qubit, Receiver QNIC(index:0) has 1 qubit
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_E)).WillRepeatedly(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(1, QNIC_E)).WillRepeatedly(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(2, QNIC_E)).WillRepeatedly(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_R)).WillRepeatedly(Return(1));

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
  // get first scheduled event in rule_engine
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

TEST(RuleEnginePhotonShootingTest, BurstTrialOutdated) {
  auto* sim = prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto* mockQubit1 = new MockQubit(QNIC_E, 0);
  auto rule_engine = new RuleEngineTestTarget{mockQubit1, routingdaemon, mockHardwareMonitor, nullptr};
  setParInt(rule_engine, "total_number_of_qnics", 1);
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_E)).WillRepeatedly(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(1, QNIC_E)).WillRepeatedly(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(2, QNIC_E)).WillRepeatedly(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_R)).WillRepeatedly(Return(3));

  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();

  int qnic_address = 0;
  auto outdated = rule_engine->burstTrial_outdated(1, qnic_address);
  EXPECT_TRUE(outdated);

  outdated = rule_engine->burstTrial_outdated(0, qnic_address);
  EXPECT_FALSE(outdated);

  delete mockHardwareMonitor;
  delete routingdaemon;
  delete mockQubit1;
}

TEST(RuleEnginePhotonShootingTest, incrementBurstTrial) {
  auto* sim = prepareSimulation();
  auto* routingdaemon = new MockRoutingDaemon;
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto* mockQubit1 = new MockQubit(QNIC_E, 0);
  auto rule_engine = new RuleEngineTestTarget{mockQubit1, routingdaemon, mockHardwareMonitor, nullptr};
  setParInt(rule_engine, "total_number_of_qnics", 2);
  setParInt(rule_engine, "number_of_qnics", 1);
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_E)).WillRepeatedly(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(1, QNIC_E)).WillRepeatedly(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(2, QNIC_E)).WillRepeatedly(Return(1));
  EXPECT_CALL(*mockHardwareMonitor, getQnicNumQubits(0, QNIC_R)).WillRepeatedly(Return(1));

  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();

  // for QNIC_R
  int qnic_address = 0;
  EXPECT_EQ(rule_engine->getBurstCountByQnic(qnic_address), 0);
  int dest_addr = 0;
  int internal_qnic_index = 0;
  rule_engine->incrementBurstTrial(dest_addr, qnic_address, internal_qnic_index);
  EXPECT_EQ(rule_engine->getBurstCountByQnic(qnic_address), 1);

  // for QNIC_E
  qnic_address = 1;
  InterfaceInfo interface_info{
      .qnic =
          {
              .address = qnic_address,
          },
  };
  rule_engine->ntable.insert(std::make_pair(dest_addr, interface_info));
  int internal_qnic_address = -1;
  EXPECT_EQ(rule_engine->getBurstCountByQnic(qnic_address), 0);
  rule_engine->incrementBurstTrial(dest_addr, internal_qnic_address, internal_qnic_index);
  EXPECT_EQ(rule_engine->getBurstCountByQnic(qnic_address), 1);

  delete mockHardwareMonitor;
  delete routingdaemon;
  delete mockQubit1;
}
}  // namespace

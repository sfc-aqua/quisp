
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
#include "messages/link_generation_messages_m.h"
#include "modules/QNIC.h"
#include "modules/QNIC/StationaryQubit/StationaryQubit.h"
#include "modules/QRSA/HardwareMonitor/HardwareMonitor.h"
#include "modules/QRSA/HardwareMonitor/IHardwareMonitor.h"
#include "modules/QRSA/RealTimeController/IRealTimeController.h"
#include "modules/QRSA/RoutingDaemon/RoutingDaemon.h"
#include "omnetpp/cmodule.h"
#include "omnetpp/simtime_t.h"
#include "rules/Active/ActiveAction.h"
#include "rules/Active/ActiveRuleSet.h"

namespace {

using namespace omnetpp;
using namespace quisp::utils;
using namespace quisp::rules;
using namespace quisp::rules::active::actions;
using quisp::rules::active::actions::ActiveAction;
using namespace quisp::modules;
using namespace quisp_test;
using namespace testing;

class Strategy : public TestComponentProviderStrategy {
  cModule* temp_qnic;

 public:
  Strategy(MockHardwareMonitor* hardware_monitor, std::vector<QNicSpec> qnic_specs) : TestComponentProviderStrategy(qnic_specs), hardwareMonitor(hardware_monitor) {
    temp_qnic = new omnetpp::cModule();
    setParInt(temp_qnic, "burst_trial_counter", 0);
  }
  ~Strategy() {
    delete hardwareMonitor;
    delete realtimeController;
  }
  MockHardwareMonitor* hardwareMonitor = nullptr;
  MockRealTimeController* realtimeController = nullptr;
  IHardwareMonitor* getHardwareMonitor() override { return hardwareMonitor; };
  IRealTimeController* getRealTimeController() override { return realtimeController; };
  cModule* getQNIC(int qnic_index, QNIC_type qnic_type) override { return temp_qnic; };
};

class RuleEngineTestTarget : public quisp::modules::RuleEngine {
 public:
  using quisp::modules::RuleEngine::burstTrial_outdated;
  using quisp::modules::RuleEngine::incrementBurstTrial;
  using quisp::modules::RuleEngine::initialize;
  using quisp::modules::RuleEngine::ntable;
  using quisp::modules::RuleEngine::par;
  using quisp::modules::RuleEngine::scheduleFirstPhotonEmission;
  using quisp::modules::RuleEngine::scheduleNextEmissionEvent;
  using quisp::modules::RuleEngine::sendPhotonTransmissionSchedule;
  using quisp::modules::RuleEngine::shootPhoton;
  using quisp::modules::RuleEngine::shootPhoton_internal;

  RuleEngineTestTarget(MockHardwareMonitor* hardware_monitor, std::vector<QNicSpec> qnic_specs) : quisp::modules::RuleEngine() {
    setParInt(this, "address", 123);
    setParInt(this, "number_of_qnics_rp", 0);
    setParInt(this, "number_of_qnics_r", 1);
    setParInt(this, "number_of_qnics", 3);
    setParInt(this, "total_number_of_qnics", 2);
    setName("rule_engine_test_target");
    provider.setStrategy(std::make_unique<Strategy>(hardware_monitor, qnic_specs));
    setComponentType(new TestModuleType("rule_engine_test"));
  }
  // setter function for allResorces[qnic_type][qnic_index]
  void setQubitBusyInQnic(int qnic_type, int qnic_index, int qubit_index) { qnic_store->setQubitBusy(QNIC_type(qnic_type), qnic_index, qubit_index, true); };
  int getNumFreeQubitsInQnic(int qnic_type, int qnic_index) { return qnic_store->countNumFreeQubits(QNIC_type(qnic_type), qnic_index); }
  int getBurstCountByQnic(int qnic_address) { return this->qnic_burst_trial_counter[qnic_address]; }
};

TEST(RuleEnginePhotonShootingTest, ShootPhotonWithoutFreeQubit) {
  auto* sim = prepareSimulation();
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  // Emitter QNIC(index:0~2) has 1 qubit, Receiver QNIC(index:0) has 1 qubit

  std::vector<QNicSpec> qnic_specs = {
      {QNIC_E, 0, 1},
      {QNIC_E, 1, 1},
      {QNIC_E, 2, 1},
      {QNIC_R, 0, 1},
  };
  auto rule_engine = new RuleEngineTestTarget{mockHardwareMonitor, qnic_specs};

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
}

TEST(RuleEnginePhotonShootingTest, ShootPhotonWithSingleFreeQubit) {
  auto* sim = prepareSimulation();
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  int qnic_index = 1;

  // Emitter QNIC(index:0~2) has 2 qubit, Receiver QNIC(index:0) has 1 qubit
  std::vector<QNicSpec> qnic_specs = {
      {QNIC_E, 0, 2},
      {QNIC_E, 1, 2},
      {QNIC_E, 2, 2},
      {QNIC_R, 0, 1},
  };
  auto rule_engine = new RuleEngineTestTarget{mockHardwareMonitor, qnic_specs};

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
}

TEST(RuleEnginePhotonShootingTest, ShootPhotonWithThreeFreeQubits) {
  auto* sim = prepareSimulation();
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  int qnic_index = 1;

  std::vector<QNicSpec> qnic_specs = {
      {QNIC_E, 0, 3},
      {QNIC_E, 1, 3},
      {QNIC_E, 2, 3},
      {QNIC_R, 0, 1},
  };
  auto rule_engine = new RuleEngineTestTarget{mockHardwareMonitor, qnic_specs};

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
}

TEST(RuleEnginePhotonShootingTest, ShootPhotonInternalWithoutFreeQubit) {
  auto* sim = prepareSimulation();
  auto* mockHardwareMonitor = new MockHardwareMonitor;

  // Emitter QNIC(index:0~2) has 1 qubit, Receiver QNIC(index:0) has 2 qubit
  std::vector<QNicSpec> qnic_specs = {
      {QNIC_E, 0, 1}, {QNIC_E, 1, 1}, {QNIC_E, 2, 1}, {QNIC_R, 0, 1}, {QNIC_R, 1, 1},
  };
  auto rule_engine = new RuleEngineTestTarget{mockHardwareMonitor, qnic_specs};
  setParInt(rule_engine, "number_of_qnics_r", 2);

  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  sim->setContext(rule_engine);

  int qnic_index = 1;
  // no free qubit case
  auto* pk = new SchedulePhotonTransmissionsOnebyOne();
  pk->setQnic_index(1);
  // set qubit in Receiver QNIC1 to busy, so there's no free qubit.
  rule_engine->setQubitBusyInQnic(QNIC_R, qnic_index, 0);
  rule_engine->shootPhoton_internal(pk);
  auto* fes = sim->getFES();
  ASSERT_EQ(fes->getLength(), 0);
  fes->clear();

  delete mockHardwareMonitor;
}

TEST(RuleEnginePhotonShootingTest, ShootPhotonInternalWithSingleFreeQubit) {
  auto* sim = prepareSimulation();
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  int qnic_index = 0;

  // Emitter QNIC(index:0~2) has 2 qubit, Receiver QNIC(index:0) has 1 qubit
  std::vector<QNicSpec> qnic_specs = {
      {QNIC_E, 0, 2},
      {QNIC_E, 1, 2},
      {QNIC_E, 2, 2},
      {QNIC_R, 0, 1},
  };

  auto rule_engine = new RuleEngineTestTarget{mockHardwareMonitor, qnic_specs};

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
}

TEST(RuleEnginePhotonShootingTest, ShootPhotonInternalWithThreeFreeQubits) {
  auto* sim = prepareSimulation();
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  int qnic_index = 0;
  // Emitter QNIC(index:0~2) has 1 qubit, Receiver QNIC(index:0) has 3 qubit
  std::vector<QNicSpec> qnic_specs = {
      {QNIC_E, 0, 1},
      {QNIC_E, 1, 1},
      {QNIC_E, 2, 1},
      {QNIC_R, 0, 3},
  };
  auto rule_engine = new RuleEngineTestTarget{mockHardwareMonitor, qnic_specs};

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
}

TEST(RuleEnginePhotonShootingTest, ScheduleNextEmissionEvent) {
  auto* sim = prepareSimulation();
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  // Emitter QNIC(index:0~2) has 1 qubit, Receiver QNIC(index:0) has 1 qubit
  std::vector<QNicSpec> qnic_specs = {
      {QNIC_E, 0, 1},
      {QNIC_E, 1, 1},
      {QNIC_E, 2, 1},
      {QNIC_R, 0, 1},
  };
  auto rule_engine = new RuleEngineTestTarget{mockHardwareMonitor, qnic_specs};

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
  EXPECT_EQ(packet->getInternal_hom(), 1 /* internal HOM */);
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
  EXPECT_EQ(packet->getInternal_hom(), 0 /* not internal HOM */);
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
  EXPECT_EQ(packet->getInternal_hom(), 0 /* not internal HOM */);
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
  EXPECT_EQ(packet->getInternal_hom(), 0 /* not internal HOM */);
  EXPECT_EQ(packet->getArrivalTime(), sim->getSimTime() + timing);
  fes->clear();

  delete mockHardwareMonitor;
}

TEST(RuleEnginePhotonShootingTest, BurstTrialOutdated) {
  auto* sim = prepareSimulation();
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  std::vector<QNicSpec> qnic_specs = {
      {QNIC_E, 0, 1},
      {QNIC_E, 1, 1},
      {QNIC_E, 2, 1},
      {QNIC_R, 0, 3},
  };
  auto rule_engine = new RuleEngineTestTarget{mockHardwareMonitor, qnic_specs};
  setParInt(rule_engine, "total_number_of_qnics", 1);

  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();

  int qnic_address = 0;
  auto outdated = rule_engine->burstTrial_outdated(1, qnic_address);
  EXPECT_TRUE(outdated);

  outdated = rule_engine->burstTrial_outdated(0, qnic_address);
  EXPECT_FALSE(outdated);

  delete mockHardwareMonitor;
}

TEST(RuleEnginePhotonShootingTest, incrementBurstTrial) {
  auto* sim = prepareSimulation();
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  std::vector<QNicSpec> qnic_specs = {
      {QNIC_E, 0, 1},
      {QNIC_E, 1, 1},
      {QNIC_E, 2, 1},
      {QNIC_R, 0, 1},
  };
  auto rule_engine = new RuleEngineTestTarget{mockHardwareMonitor, qnic_specs};
  setParInt(rule_engine, "total_number_of_qnics", 2);
  setParInt(rule_engine, "number_of_qnics", 1);

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
  QNIC qnic;
  qnic.address = qnic_address;
  InterfaceInfo interface_info{.qnic = qnic};
  rule_engine->ntable.insert(std::make_pair(dest_addr, interface_info));
  int internal_qnic_address = -1;
  EXPECT_EQ(rule_engine->getBurstCountByQnic(qnic_address), 0);
  rule_engine->incrementBurstTrial(dest_addr, internal_qnic_address, internal_qnic_index);
  EXPECT_EQ(rule_engine->getBurstCountByQnic(qnic_address), 1);

  delete mockHardwareMonitor;
}

TEST(RuleEnginePhotonShootingTest, sendPhotonTransmissionSchedule) {
  auto* sim = prepareSimulation();
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  std::vector<QNicSpec> qnic_specs = {
      {QNIC_E, 0, 1},
      {QNIC_E, 1, 1},
      {QNIC_E, 2, 1},
      {QNIC_R, 0, 1},
  };
  auto rule_engine = new RuleEngineTestTarget{mockHardwareMonitor, qnic_specs};
  setParInt(rule_engine, "total_number_of_qnics", 2);
  setParInt(rule_engine, "number_of_qnics", 1);
  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  sim->setContext(rule_engine);
  auto* fes = sim->getFES();

  int qnic_address = 0;
  int qnic_index = 0;
  double interval = 0.5;
  simtime_t timing = 1.0;
  PhotonTransmissionConfig config = {
      .transmission_partner_address = 0,
      .qnic_index = qnic_index,
      .qnic_address = qnic_address,
      .qnic_type = QNIC_E,
      .timing = timing,
      .interval = interval,
  };
  rule_engine->sendPhotonTransmissionSchedule(config);
  ASSERT_EQ(fes->getLength(), 1);
  auto* res = fes->get(0);
  ASSERT_NE(res, nullptr);
  auto scheduled = dynamic_cast<SchedulePhotonTransmissionsOnebyOne*>(res);
  ASSERT_NE(scheduled, nullptr);
  EXPECT_EQ(scheduled->getQnic_address(), qnic_address);
  EXPECT_EQ(scheduled->getQnic_index(), qnic_index);
  EXPECT_EQ(scheduled->getInterval(), interval);
  EXPECT_EQ(scheduled->getTiming(), timing);
  EXPECT_EQ(scheduled->getInternal_hom(), 0);
  fes->clear();

  // no free qubit case
  rule_engine->setQubitBusyInQnic(QNIC_E, qnic_index, 0);
  rule_engine->sendPhotonTransmissionSchedule(config);
  ASSERT_EQ(fes->getLength(), 0);  // not sent because no more free qubits
  fes->clear();

  // internal hom case
  config.qnic_type = QNIC_R;
  rule_engine->sendPhotonTransmissionSchedule(config);
  ASSERT_EQ(fes->getLength(), 1);
  res = fes->get(0);
  ASSERT_NE(res, nullptr);
  scheduled = dynamic_cast<SchedulePhotonTransmissionsOnebyOne*>(res);
  ASSERT_NE(scheduled, nullptr);
  EXPECT_EQ(scheduled->getQnic_address(), qnic_address);
  EXPECT_EQ(scheduled->getQnic_index(), qnic_index);
  EXPECT_EQ(scheduled->getInterval(), interval);
  EXPECT_EQ(scheduled->getTiming(), timing);
  EXPECT_EQ(scheduled->getInternal_hom(), 1);
  fes->clear();

  delete mockHardwareMonitor;
}

TEST(RuleEnginePhotonShootingTest, scheduleFirstPhotonEmission) {
  auto* sim = prepareSimulation();
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  std::vector<QNicSpec> qnic_specs = {
      {QNIC_E, 0, 1},
      {QNIC_E, 1, 1},
      {QNIC_E, 2, 1},
      {QNIC_R, 0, 1},
  };
  auto rule_engine = new RuleEngineTestTarget{mockHardwareMonitor, qnic_specs};
  setParInt(rule_engine, "total_number_of_qnics", 2);
  setParInt(rule_engine, "number_of_qnics", 1);

  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  sim->setContext(rule_engine);
  auto* fes = sim->getFES();

  int src_addr = 1;
  int qnic_address = 0;
  int qnic_index = 0;
  int qnic_type = QNIC_E;
  double interval = 0.5;
  simtime_t timing = 1.0;

  // QNIC_E
  auto* pk = new BSMtimingNotifier();
  pk->setInternal_qnic_address(qnic_address);
  pk->setInternal_qnic_index(qnic_index);
  pk->setTiming_at(timing);
  pk->setInterval(interval);
  pk->setSrcAddr(src_addr);
  QNIC qnic;
  qnic.index = qnic_index;
  qnic.address = qnic_address;
  InterfaceInfo interface_info{.qnic = qnic};
  rule_engine->ntable.insert(std::make_pair(src_addr, interface_info));
  rule_engine->scheduleFirstPhotonEmission(pk, QNIC_type(qnic_type));
  ASSERT_EQ(fes->getLength(), 1);
  auto* res = fes->get(0);
  ASSERT_NE(res, nullptr);
  auto scheduled = dynamic_cast<SchedulePhotonTransmissionsOnebyOne*>(res);
  ASSERT_NE(scheduled, nullptr);
  EXPECT_EQ(scheduled->getQnic_address(), qnic_address);
  EXPECT_EQ(scheduled->getQnic_index(), qnic_index);
  EXPECT_EQ(scheduled->getInterval(), interval);
  EXPECT_EQ(scheduled->getTiming(), timing);
  EXPECT_EQ(scheduled->getInternal_hom(), 0);
  fes->clear();

  // QNIC_R
  qnic_type = QNIC_R;
  qnic_index = 0;
  pk = new BSMtimingNotifier();
  pk->setInternal_qnic_address(qnic_address);
  pk->setInternal_qnic_index(qnic_index);
  pk->setTiming_at(timing);
  pk->setInterval(interval);
  pk->setSrcAddr(src_addr);
  rule_engine->tracker_accessible[qnic_address] = true;
  rule_engine->ntable.insert(std::make_pair(src_addr, interface_info));
  rule_engine->scheduleFirstPhotonEmission(pk, QNIC_type(qnic_type));
  ASSERT_EQ(fes->getLength(), 1);
  res = fes->get(0);
  ASSERT_NE(res, nullptr);
  scheduled = dynamic_cast<SchedulePhotonTransmissionsOnebyOne*>(res);
  ASSERT_NE(scheduled, nullptr);
  EXPECT_EQ(scheduled->getQnic_address(), qnic_address);
  EXPECT_EQ(scheduled->getQnic_index(), qnic_index);
  EXPECT_EQ(scheduled->getInterval(), interval);
  EXPECT_EQ(scheduled->getTiming(), timing);
  EXPECT_EQ(scheduled->getInternal_hom(), 1);
  fes->clear();

  delete mockHardwareMonitor;
}
}  // namespace


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
#include "omnetpp/csimulation.h"

namespace {

using namespace omnetpp;
using namespace quisp::utils;
using namespace quisp::rules;
using namespace quisp::modules;
using namespace quisp_test;
using namespace quisp::messages;
using namespace testing;

class Strategy : public TestComponentProviderStrategy {
  cModule* temp_qnic;

 public:
  Strategy(MockHardwareMonitor* hardware_monitor, std::vector<QNicSpec> qnic_specs, MockRealTimeController* realtime_controller)
      : TestComponentProviderStrategy(qnic_specs), hardwareMonitor(hardware_monitor), realtimeController(realtime_controller) {
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
  using quisp::modules::RuleEngine::freeFailedEntanglementAttemptQubits;
  using quisp::modules::RuleEngine::getEmitTimeFromBSMNotification;
  using quisp::modules::RuleEngine::handleMessage;
  using quisp::modules::RuleEngine::initialize;
  using quisp::modules::RuleEngine::ntable;
  using quisp::modules::RuleEngine::par;
  using quisp::modules::RuleEngine::schedulePhotonEmission;
  using quisp::modules::RuleEngine::sendEmitPhotonSignalToQnic;
  using quisp::modules::RuleEngine::stopOnGoingPhotonEmission;

  RuleEngineTestTarget(MockHardwareMonitor* hardware_monitor, std::vector<QNicSpec> qnic_specs, MockRealTimeController* realtime_controller) : quisp::modules::RuleEngine() {
    setParInt(this, "address", 123);
    setParInt(this, "number_of_qnics_rp", 0);
    setParInt(this, "number_of_qnics_r", 1);
    setParInt(this, "number_of_qnics", 3);
    setParInt(this, "total_number_of_qnics", 2);
    setName("rule_engine_test_target");
    provider.setStrategy(std::make_unique<Strategy>(hardware_monitor, qnic_specs, realtime_controller));
    setComponentType(new TestModuleType("rule_engine_test"));
  }
  // setter function for allResorces[qnic_type][qnic_index]
  void setQubitBusyInQnic(int qnic_type, int qnic_index, int qubit_index) { qnic_store->setQubitBusy(QNIC_type(qnic_type), qnic_index, qubit_index, true); };
  int getNumFreeQubitsInQnic(int qnic_type, int qnic_index) { return qnic_store->countNumFreeQubits(QNIC_type(qnic_type), qnic_index); }
  int getBurstCountByQnic(int qnic_address) { return this->qnic_burst_trial_counter[qnic_address]; }
};

TEST(RuleEnginePhotonShootingTest, RequestEmissionWithoutFreeQubit) {
  auto* sim = prepareSimulation();
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto* mockRealtimeController = new MockRealTimeController;
  // Emitter QNIC(index:0~2) has 1 qubit, Receiver QNIC(index:0) has 1 qubit

  std::vector<QNicSpec> qnic_specs = {
      {QNIC_E, 0, 1},
      {QNIC_E, 1, 1},
      {QNIC_E, 2, 1},
      {QNIC_R, 0, 1},
  };
  auto rule_engine = new RuleEngineTestTarget{mockHardwareMonitor, qnic_specs, mockRealtimeController};

  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  sim->setContext(rule_engine);

  int qnic_index = 1;
  // no free qubit case
  auto* pk = new EmitPhotonRequest();
  pk->setQnicType(QNIC_E);
  pk->setQnicIndex(qnic_index);
  pk->setFirst(true);

  // set qubit in Emitter QNIC1 to busy, so there's no free qubit.
  rule_engine->setQubitBusyInQnic(QNIC_E, qnic_index, 0);
  rule_engine->handleMessage(pk);
  auto* fes = sim->getFES();
  EXPECT_EQ(fes->getLength(), 0);
  fes->clear();

  delete mockHardwareMonitor;
}

TEST(RuleEnginePhotonShootingTest, EmitPhotonWithSingleFreeQubit) {
  auto* sim = prepareSimulation();
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto* mockRealtimeController = new MockRealTimeController;
  int qnic_index = 1;

  // Emitter QNIC(index:0~2) has 2 qubit, Receiver QNIC(index:0) has 1 qubit
  std::vector<QNicSpec> qnic_specs = {
      {QNIC_E, 0, 2},
      {QNIC_E, 1, 2},
      {QNIC_E, 2, 2},
      {QNIC_R, 0, 1},
  };
  auto rule_engine = new RuleEngineTestTarget{mockHardwareMonitor, qnic_specs, mockRealtimeController};

  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  sim->setContext(rule_engine);
  rule_engine->setQubitBusyInQnic(QNIC_E, qnic_index, 0);

  auto* pk = new EmitPhotonRequest();
  pk->setQnicType(QNIC_E);
  pk->setQnicIndex(qnic_index);
  pk->setFirst(true);

  EXPECT_EQ(rule_engine->getNumFreeQubitsInQnic(QNIC_E, qnic_index), 1);
  EXPECT_CALL(*mockRealtimeController, EmitPhoton(qnic_index, 1, QNIC_E, STATIONARYQUBIT_PULSE_BOUND));
  // RE receives BSM Notification message
  rule_engine->handleMessage(pk);
  auto* fes = sim->getFES();
  EXPECT_EQ(fes->getLength(), 0);

  fes->clear();

  delete mockHardwareMonitor;
  delete mockRealtimeController;
}

TEST(RuleEnginePhotonShootingTest, EmitPhotonWithTwoFreeQubits) {
  auto* sim = prepareSimulation();
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto* mockRealtimeController = new MockRealTimeController;
  int qnic_index = 1;

  // Emitter QNIC(index:0~2) has 2 qubit, Receiver QNIC(index:0) has 1 qubit
  std::vector<QNicSpec> qnic_specs = {
      {QNIC_E, 0, 2},
      {QNIC_E, 1, 2},
      {QNIC_E, 2, 2},
      {QNIC_R, 0, 1},
  };
  auto rule_engine = new RuleEngineTestTarget{mockHardwareMonitor, qnic_specs, mockRealtimeController};

  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  sim->setContext(rule_engine);

  auto* pk = new EmitPhotonRequest();
  pk->setQnicType(QNIC_E);
  pk->setQnicIndex(qnic_index);
  pk->setFirst(true);
  pk->setIntervalBetweenPhotons(0.0001);

  EXPECT_EQ(rule_engine->getNumFreeQubitsInQnic(QNIC_E, qnic_index), 2);
  EXPECT_CALL(*mockRealtimeController, EmitPhoton(qnic_index, 0, QNIC_E, STATIONARYQUBIT_PULSE_BEGIN));
  // RE receives BSM Notification message
  rule_engine->handleMessage(pk);
  EXPECT_EQ(sim->getFES()->getLength(), 1);
  EXPECT_TRUE(pk->isScheduled());
  EXPECT_EQ(rule_engine->getNumFreeQubitsInQnic(QNIC_E, qnic_index), 1);

  // second photon emission
  EXPECT_CALL(*mockRealtimeController, EmitPhoton(qnic_index, 1, QNIC_E, STATIONARYQUBIT_PULSE_END));
  sim->executeNextEvent();
  EXPECT_EQ(rule_engine->getNumFreeQubitsInQnic(QNIC_E, qnic_index), 0);
  EXPECT_EQ(sim->getFES()->getLength(), 0);

  sim->getFES()->clear();
  delete mockHardwareMonitor;
  delete mockRealtimeController;
}

TEST(RuleEnginePhotonShootingTest, EmitPhotonWithThreeFreeQubits) {
  auto* sim = prepareSimulation();
  auto* mockHardwareMonitor = new MockHardwareMonitor;
  auto* mockRealtimeController = new MockRealTimeController;
  int qnic_index = 1;

  // Emitter QNIC(index:0~2) has 2 qubit, Receiver QNIC(index:0) has 1 qubit
  std::vector<QNicSpec> qnic_specs = {
      {QNIC_E, 0, 2},
      {QNIC_E, 1, 3},
      {QNIC_E, 2, 2},
      {QNIC_R, 0, 1},
  };
  auto rule_engine = new RuleEngineTestTarget{mockHardwareMonitor, qnic_specs, mockRealtimeController};

  sim->registerComponent(rule_engine);
  rule_engine->callInitialize();
  sim->setContext(rule_engine);

  auto* pk = new EmitPhotonRequest();
  pk->setQnicType(QNIC_E);
  pk->setQnicIndex(qnic_index);
  pk->setFirst(true);

  EXPECT_EQ(rule_engine->getNumFreeQubitsInQnic(QNIC_E, qnic_index), 3);
  EXPECT_CALL(*mockRealtimeController, EmitPhoton(qnic_index, 0, QNIC_E, STATIONARYQUBIT_PULSE_BEGIN));
  // RE receives BSM Notification message
  rule_engine->handleMessage(pk);
  EXPECT_EQ(sim->getFES()->getLength(), 1);
  EXPECT_TRUE(pk->isScheduled());
  EXPECT_EQ(rule_engine->getNumFreeQubitsInQnic(QNIC_E, qnic_index), 2);

  // second photon emission
  EXPECT_CALL(*mockRealtimeController, EmitPhoton(qnic_index, 1, QNIC_E, 0));
  sim->executeNextEvent();
  EXPECT_EQ(sim->getFES()->getLength(), 1);
  EXPECT_TRUE(pk->isScheduled());
  EXPECT_EQ(rule_engine->getNumFreeQubitsInQnic(QNIC_E, qnic_index), 1);

  // third photon emission
  EXPECT_CALL(*mockRealtimeController, EmitPhoton(qnic_index, 2, QNIC_E, STATIONARYQUBIT_PULSE_END));
  sim->executeNextEvent();
  EXPECT_EQ(sim->getFES()->getLength(), 0);
  EXPECT_EQ(rule_engine->getNumFreeQubitsInQnic(QNIC_E, qnic_index), 0);

  sim->getFES()->clear();
  delete mockHardwareMonitor;
  delete mockRealtimeController;
}

}  // namespace

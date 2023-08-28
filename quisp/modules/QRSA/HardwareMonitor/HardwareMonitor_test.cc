#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include <omnetpp/csimulation.h>

#include "HardwareMonitor.h"

#include "gmock/gmock-spec-builders.h"
#include "messages/tomography_messages_m.h"
#include "modules/QNIC.h"
#include "modules/QNIC/StationaryQubit/IStationaryQubit.h"
#include "modules/QRSA/HardwareMonitor/HardwareMonitor.h"
#include "modules/QRSA/RoutingDaemon/IRoutingDaemon.h"
#include "test_utils/TestUtilFunctions.h"
#include "test_utils/TestUtils.h"
#include "test_utils/mock_modules/MockRoutingDaemon.h"
#include "utils/HelperFunctions.h"
#include "utils/TomographyManager.h"

namespace {

using namespace omnetpp;
using namespace quisp::utils;
using namespace quisp::modules;
using namespace quisp_test;
using namespace testing;
using namespace quisp::messages;
using quisp::utils::HelperFunctions;

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy(TestQNode* _qnode) : routingDaemon(nullptr), parent_qnode(_qnode) {}
  // We could prepare mock for tomography manager if we need
  Strategy(MockRoutingDaemon* routing_daemon) : routingDaemon(routing_daemon) {}
  ~Strategy() { delete routingDaemon; }
  cModule* getQNode() override { return parent_qnode; }
  MockRoutingDaemon* routingDaemon = nullptr;
  TomographyManager* tomography_manager;
  IRoutingDaemon* getRoutingDaemon() override { return routingDaemon; };

 private:
  TestQNode* parent_qnode;
};

class HardwareMonitorTestTarget : public quisp::modules::HardwareMonitor {
 public:
  using quisp::modules::HardwareMonitor::handleMessage;
  using quisp::modules::HardwareMonitor::initialize;
  using quisp::modules::HardwareMonitor::par;
  using quisp::modules::HardwareMonitor::tomography_manager;
  HardwareMonitorTestTarget(MockRoutingDaemon* routing_daemon) : quisp::modules::HardwareMonitor() {
    setParInt(this, "address", 123);
    setParBool(this, "link_tomography", false);
    setParStr(this, "tomography_output_filename", "test_file");
    setParInt(this, "initial_purification", 0);
    setParBool(this, "x_purification", true);
    setParBool(this, "z_purification", true);
    setParInt(this, "purification_type", 0);
    setParInt(this, "num_measure", 0);

    this->setName("hardware_monitor_test_target");
    this->provider.setStrategy(std::make_unique<Strategy>(routing_daemon));
  }
};

class MockTomographyManager : public TomographyManager {
 public:
  MOCK_METHOD(void, addLocalResult, (int qnic_id, int partner, int tomography_round, char measurement_basis, bool is_plus, char my_GOD_clean));
  MOCK_METHOD(void, addPartnerResult, (int self_qnic_id, int partner, int tomography_round, char measurement_basis, bool is_plus, char my_GOD_clean));
  MOCK_METHOD(void, setStats, (int qnic_id, int partner, simtime_t tomography_time, double bell_pair_per_sec, int total_measurement_count));
  MOCK_METHOD(Matrix4cd, reconstructDensityMatrix, (int qnic_id, int partner));
};

class HardwareMonitorTest : public testing::Test {
 protected:
  void SetUp() {
    sim = prepareSimulation();
    routing_daemon = new MockRoutingDaemon;
    tomography_manager = new MockTomographyManager;
  }
  void TearDown() {
    delete routing_daemon;
    delete tomography_manager;
  }
  utils::TestSimulation* sim;
  MockRoutingDaemon* routing_daemon;
  MockTomographyManager* tomography_manager;
};

TEST_F(HardwareMonitorTest, acceptSelfTomographyResult) {
  // Test for accepting tomography result from my self and put it to tomography manager
  // Situation:
  // Node 0 (qnic_id: 1) <--> (qnic_id: 0)Node 1
  // EXPECT_CALL(*tomography_manager, addLocalResult).Times(1);
  // EXPECT_CALL(*routing_daemon, findQNicAddrByDestAddr).Times(1).WillOnce(Return(1));
  // auto qinter_info = std::make_unique<QuantumInterfaceInfo>();

  // EXPECT_CALL(*routing_daemon, getQuantumInterfaceInfo).Times(1).WillOnce(Return());

  // auto hardware_monitor = new HardwareMonitorTestTarget{routing_daemon};
  // sim->registerComponent(hardware_monitor);
  // hardware_monitor->callInitialize(0);

  // auto* self_link_tomography_result = new LinkTomographyResult{"LinkTomographyResult"};
  // // packet for myself 0 --> -
  // self_link_tomography_result->setDestAddr(0);
  // self_link_tomography_result->setSrcAddr(0);

  // // first tomography round
  // self_link_tomography_result->setCount_id(0);
  // self_link_tomography_result->setBasis('X');
  // self_link_tomography_result->setOutput_is_plus(true);

  // // handle tomography result
  // hardware_monitor->handleMessage(self_link_tomography_result);
}

// Should be deprecated in the future
// TEST_F(HardwareMonitorTest, sendLinkTomgraphyRuleSet) {}

// TEST_F(HardwareMonitorTest, reconstructDensityMatrix) {}

}  // namespace

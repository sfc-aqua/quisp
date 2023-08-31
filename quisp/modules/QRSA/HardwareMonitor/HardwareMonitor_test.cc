#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include <omnetpp/csimulation.h>
#include <memory>

#include "HardwareMonitor.h"

#include "gmock/gmock-nice-strict.h"
#include "gmock/gmock-spec-builders.h"
#include "messages/tomography_messages_m.h"
#include "modules/QNIC.h"
#include "modules/QNIC/StationaryQubit/IStationaryQubit.h"
#include "modules/QRSA/HardwareMonitor/HardwareMonitor.h"
#include "modules/QRSA/RoutingDaemon/IRoutingDaemon.h"
#include "test_utils/TestUtilFunctions.h"
#include "test_utils/TestUtils.h"
#include "test_utils/mock_modules/MockRoutingDaemon.h"
#include "test_utils/mock_modules/MockTomographyManager.h"
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
using quisp_test::mock_modules::tomography_manager::MockTomographyManager;

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy(TestQNode* _qnode) : routingDaemon(nullptr), parent_qnode(_qnode) {}
  // We could prepare mock for tomography manager if we need
  Strategy(MockRoutingDaemon* routing_daemon) : routingDaemon(routing_daemon) {}
  ~Strategy() { delete routingDaemon; }
  cModule* getQNode() override { return parent_qnode; }
  MockRoutingDaemon* routingDaemon = nullptr;
  IRoutingDaemon* getRoutingDaemon() override { return routingDaemon; };
  int getNodeAddr() override { return 0; }

 private:
  TestQNode* parent_qnode;
};

class HardwareMonitorTestTarget : public quisp::modules::HardwareMonitor {
 public:
  using quisp::modules::HardwareMonitor::handleMessage;
  using quisp::modules::HardwareMonitor::initialize;
  using quisp::modules::HardwareMonitor::link_cost_table;
  using quisp::modules::HardwareMonitor::par;
  using quisp::modules::HardwareMonitor::tomography_manager;
  HardwareMonitorTestTarget(MockRoutingDaemon* routing_daemon) : quisp::modules::HardwareMonitor() {
    setParBool(this, "link_tomography", false);
    setParStr(this, "tomography_output_filename", "test_file");
    setParInt(this, "initial_purification", 0);
    setParBool(this, "x_purification", true);
    setParBool(this, "z_purification", true);
    setParInt(this, "purification_type", 0);
    setParInt(this, "num_measure", 0);

    this->setName("hardware_monitor_test_target");
    this->provider.setStrategy(std::make_unique<Strategy>(routing_daemon));
    setComponentType(new TestModuleType("hardware_monitor_test"));
  }
};

class HardwareMonitorTest : public testing::Test {
 protected:
  void SetUp() {
    sim = prepareSimulation();
    routing_daemon = new MockRoutingDaemon;
    tomography_manager = std::make_unique<MockTomographyManager>();
    hardware_monitor = new HardwareMonitorTestTarget{routing_daemon};
    sim->registerComponent(hardware_monitor);
  }
  void TearDown() { delete routing_daemon; }
  utils::TestSimulation* sim;
  MockRoutingDaemon* routing_daemon;
  std::unique_ptr<MockTomographyManager> tomography_manager;
  HardwareMonitorTestTarget* hardware_monitor;
};

TEST_F(HardwareMonitorTest, initialize_stage0) {
  // Test for initialize
  hardware_monitor->callInitialize(0);
}

TEST_F(HardwareMonitorTest, initialize_stage2) {
  // Test for initialize
  EXPECT_CALL(*routing_daemon, getNeighborAddresses).Times(1).WillOnce(Return(std::vector<int>{1, 2}));
  hardware_monitor->callInitialize(1);
  EXPECT_EQ(hardware_monitor->link_cost_table.size(), 2);
}

TEST_F(HardwareMonitorTest, acceptSelfTomographyResult) {
  // Test for accepting tomography result from my self and put it to tomography manager
  // Situation:
  // Node 0 (self, qnic_id: 1, qnic_type: QNIC_E) <--> (qnic_id: 0, qnic_type: QNIC_R)Node 1
  auto qinter_info = QuantumInterfaceInfo{
      .qnic =
          {
              .type = QNIC_type::QNIC_E,
              .index = 1,
          },
      .buffer_size = 1,
      .link_cost = 1,
  };
  EXPECT_CALL(*routing_daemon, getQuantumInterfaceInfo).Times(1).WillOnce(Return(qinter_info));
  EXPECT_CALL(*dynamic_cast<MockTomographyManager*>(tomography_manager.get()), addLocalResult).Times(1);
  hardware_monitor->callInitialize(0);
  hardware_monitor->tomography_manager = std::move(tomography_manager);

  auto* self_link_tomography_result = new LinkTomographyResult{"LinkTomographyResult"};
  // packet for myself 0 --> -
  self_link_tomography_result->setPartner_address(1);
  self_link_tomography_result->setDestAddr(0);
  self_link_tomography_result->setSrcAddr(0);

  // first tomography round
  self_link_tomography_result->setCount_id(0);
  self_link_tomography_result->setBasis('X');
  self_link_tomography_result->setGOD_clean('X');
  self_link_tomography_result->setOutput_is_plus(true);

  // handle tomography result
  hardware_monitor->handleMessage(self_link_tomography_result);
  delete hardware_monitor->tomography_manager.get();
}

TEST_F(HardwareMonitorTest, acceptPartnerResult) {
  auto qinter_info = QuantumInterfaceInfo{
      .qnic =
          {
              .type = QNIC_type::QNIC_E,
              .index = 1,
          },
      .buffer_size = 1,
      .link_cost = 1,
  };
  EXPECT_CALL(*routing_daemon, getQuantumInterfaceInfo).Times(1).WillOnce(Return(qinter_info));
  EXPECT_CALL(*dynamic_cast<MockTomographyManager*>(tomography_manager.get()), addPartnerResult).Times(1);
  hardware_monitor->callInitialize(0);
  hardware_monitor->tomography_manager = std::move(tomography_manager);

  auto* partner_link_tomography_result = new LinkTomographyResult{"LinkTomographyResult"};

  partner_link_tomography_result->setPartner_address(1);
  partner_link_tomography_result->setDestAddr(0);
  partner_link_tomography_result->setSrcAddr(1);  // src addr != my_address

  // fist tomography round
  partner_link_tomography_result->setCount_id(0);
  partner_link_tomography_result->setBasis('X');
  partner_link_tomography_result->setGOD_clean('X');
  partner_link_tomography_result->setOutput_is_plus(true);

  // handle tomography result
  hardware_monitor->handleMessage(partner_link_tomography_result);
  delete hardware_monitor->tomography_manager.get();
}

// Should be deprecated in the future
TEST_F(HardwareMonitorTest, sendLinkTomgraphyRuleSet) {}

// TEST_F(HardwareMonitorTest, reconstructDensityMatrix) {}

}  // namespace

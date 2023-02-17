#include "HardwareMonitor.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include <test_utils/TestUtils.h>
#include "modules/QNIC.h"
#include "modules/QNIC/StationaryQubit/IStationaryQubit.h"
#include "modules/QRSA/HardwareMonitor/HardwareMonitor.h"
#include "modules/QRSA/RoutingDaemon/IRoutingDaemon.h"
#include "omnetpp/csimulation.h"

namespace {

using namespace omnetpp;
using namespace quisp::utils;
using namespace quisp::modules;
using namespace quisp_test;
using namespace testing;

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy(TestQNode* _qnode) : mockQubit(nullptr), routingDaemon(nullptr), parent_qnode(_qnode) {}
  Strategy(MockQubit* qubit, MockRoutingDaemon* routing_daemon) : mockQubit(qubit), routingDaemon(routing_daemon) {}
  ~Strategy() {
    delete mockQubit;
    delete routingDaemon;
  }
  cModule* getQNode() override { return parent_qnode; }
  MockQubit* mockQubit = nullptr;
  MockRoutingDaemon* routingDaemon = nullptr;
  IStationaryQubit* getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) override {
    if (mockQubit == nullptr) mockQubit = new MockQubit();
    return mockQubit;
  };
  IRoutingDaemon* getRoutingDaemon() override { return routingDaemon; };

 private:
  TestQNode* parent_qnode;
};

class HardwareMonitorTestTarget : public quisp::modules::HardwareMonitor {
 public:
  using quisp::modules::HardwareMonitor::initialize;
  using quisp::modules::HardwareMonitor::par;
  HardwareMonitorTestTarget(MockQubit* mock_qubit, MockRoutingDaemon* routing_daemon) : quisp::modules::HardwareMonitor() {
    setParInt(this, "address", 123);
    setParInt(this, "number_of_qnics_rp", 0);
    setParInt(this, "number_of_qnics_r", 0);
    setParInt(this, "number_of_qnics", 0);
    setParBool(this, "link_tomography", false);
    setParStr(this, "tomography_output_filename", "test_file");
    setParStr(this, "file_dir_name", "out/tests");
    setParInt(this, "initial_purification", 0);
    setParBool(this, "x_purification", true);
    setParBool(this, "z_purification", true);
    setParInt(this, "purification_type", 0);
    setParInt(this, "num_measure", 0);

    this->setName("hardware_monitor_test_target");
    this->provider.setStrategy(std::make_unique<Strategy>(mock_qubit, routing_daemon));
  }
};

TEST(HardwareMonitorTestTarget, Init) {
  prepareSimulation();
  auto* mock_routing_daemon = new MockRoutingDaemon;
  auto* mock_qubit = new MockQubit;
  EXPECT_CALL(*mock_routing_daemon, getNumEndNodes()).WillOnce(Return(1));
  HardwareMonitorTestTarget c{mock_qubit, mock_routing_daemon};

  c.initialize(0);
  ASSERT_EQ(c.par("address").intValue(), 123);
}
}  // namespace

#include "HardwareMonitor.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include <test_utils/TestUtils.h>
#include "modules/QNIC.h"
#include "modules/QNIC/StationaryQubit/StationaryQubit.h"
#include "modules/QRSA/HardwareMonitor/HardwareMonitor.h"
#include "modules/QRSA/RoutingDaemon/IRoutingDaemon.h"
#include "omnetpp/csimulation.h"

namespace {

using namespace omnetpp;
using namespace quisp::utils;
using namespace quisp::modules;
using namespace quisp_test;
using namespace testing;

class MockStationaryQubit : public StationaryQubit {
 public:
  MOCK_METHOD(void, emitPhoton, (int pulse), (override));
  MOCK_METHOD(void, setFree, (bool consumed), (override));
};

class MockRoutingDaemon : public IRoutingDaemon {
 public:
  MOCK_METHOD(int, returnNumEndNodes, (), (override));
  MOCK_METHOD(int, return_QNIC_address_to_destAddr, (int destAddr), (override));
};

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy() : mockQubit(nullptr), routingDaemon(nullptr) {}
  Strategy(MockStationaryQubit* qubit, MockRoutingDaemon* routing_daemon) : mockQubit(qubit), routingDaemon(routing_daemon) {}
  ~Strategy() {
    delete mockQubit;
    delete routingDaemon;
  }
  MockStationaryQubit* mockQubit = nullptr;
  MockRoutingDaemon* routingDaemon = nullptr;
  StationaryQubit* getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) override {
    if (mockQubit == nullptr) mockQubit = new MockStationaryQubit();
    return mockQubit;
  };
  IRoutingDaemon* getRoutingDaemon() override { return routingDaemon; };
};

class HardwareMonitorTestTarget : public quisp::modules::HardwareMonitor {
 public:
  using quisp::modules::HardwareMonitor::initialize;
  using quisp::modules::HardwareMonitor::par;
  HardwareMonitorTestTarget(MockStationaryQubit* mock_qubit, MockRoutingDaemon* routing_daemon) : quisp::modules::HardwareMonitor() {
    setParInt(this, "address", 123);
    setParInt(this, "number_of_qnics_rp", 0);
    setParInt(this, "number_of_qnics_r", 0);
    setParInt(this, "number_of_qnics", 0);
    setParBool(this, "link_tomography", false);
    setParStr(this, "tomography_output_filename", "test_file");
    setParStr(this, "file_dir_name", "out/tests");
    setParInt(this, "initial_purification", 0);
    setParBool(this, "X_purification", true);
    setParBool(this, "Z_purification", true);
    setParInt(this, "Purification_type", 0);
    setParInt(this, "num_measure", 0);

    this->setName("hardware_monitor_test_target");
    this->provider.setStrategy(std::make_unique<Strategy>(mock_qubit, routing_daemon));
  }
};

TEST(HardwareMonitorTestTarget, Init) {
  auto* mock_routing_daemon = new MockRoutingDaemon;
  auto* mock_qubit = new MockStationaryQubit;
  EXPECT_CALL(*mock_routing_daemon, returnNumEndNodes()).WillOnce(Return(1));
  HardwareMonitorTestTarget c{mock_qubit, mock_routing_daemon};

  c.initialize(0);
  ASSERT_EQ(c.par("address").intValue(), 123);
}

}  // namespace

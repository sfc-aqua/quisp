#include "RuleEngine.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include <test_utils/TestUtils.h>
#include <memory>
#include "modules/QNIC.h"
#include "modules/QNIC/StationaryQubit/StationaryQubit.h"
#include "modules/QRSA/HardwareMonitor/HardwareMonitor.h"
#include "modules/QRSA/HardwareMonitor/IHardwareMonitor.h"
#include "modules/QRSA/RoutingDaemon/RoutingDaemon.h"
#include "modules/QRSA/RuleEngine/RuleEngine.h"
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

class MockRoutingDaemon : public RoutingDaemon {
 public:
  MOCK_METHOD(int, return_QNIC_address_to_destAddr, (int destAddr), (override));
};

class MockHardwareMonitor : public HardwareMonitor {
 public:
  MOCK_METHOD(std::unique_ptr<ConnectionSetupInfo>, findConnectionInfoByQnicAddr, (int qnic_address), (override));
  MOCK_METHOD(int, getQnicNumQubits, (int i, QNIC_type qnic_type), (override));
};

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy() : mockQubit(nullptr), routingDaemon(nullptr), hardwareMonitor(nullptr) {}
  Strategy(MockStationaryQubit* _qubit, MockRoutingDaemon* routing_daemon, MockHardwareMonitor* hardware_monitor)
      : mockQubit(_qubit), routingDaemon(routing_daemon), hardwareMonitor(hardware_monitor) {}
  ~Strategy() {
    delete mockQubit;
    delete routingDaemon;
    delete hardwareMonitor;
  }
  MockStationaryQubit* mockQubit = nullptr;
  MockRoutingDaemon* routingDaemon = nullptr;
  MockHardwareMonitor* hardwareMonitor = nullptr;
  StationaryQubit* getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) override {
    if (mockQubit == nullptr) mockQubit = new MockStationaryQubit();
    return mockQubit;
  };
  IRoutingDaemon* getRoutingDaemon() override { return routingDaemon; };
  IHardwareMonitor* getHardwareMonitor() override { return hardwareMonitor; };
};

class RuleEngineTestTarget : public quisp::modules::RuleEngine {
 public:
  using quisp::modules::RuleEngine::initialize;
  using quisp::modules::RuleEngine::par;
  RuleEngineTestTarget(MockStationaryQubit* mockQubit, MockRoutingDaemon* routingdaemon, MockHardwareMonitor* hardware_monitor) : quisp::modules::RuleEngine() {
    setParInt(this, "address", 123);
    setParInt(this, "number_of_qnics_rp", 0);
    setParInt(this, "number_of_qnics_r", 1);
    setParInt(this, "number_of_qnics", 1);
    setParInt(this, "total_number_of_qnics", 2);
    this->setName("rule_engine_test_target");
    this->provider.setStrategy(std::make_unique<Strategy>(mockQubit, routingdaemon, hardware_monitor));
  }

 protected:
  // setter function for allResorces[qnic_type][qnic_index]
  void setAllResources(int qnic_type, int qnic_index, int partner, StationaryQubit* qubit) { this->allResources[qnic_type][qnic_index].insert(std::make_pair(partner, qubit)); };

 private:
  FRIEND_TEST(RuleEngineTest, ESResourceUpdate);
  friend class MockRoutingDaemon;
  friend class MockHardwareMonitor;
};

TEST(RuleEngineTest, ESResourceUpdate) {
  std::cout << "Start RuleEngine Test" << std::endl;
  auto routingdaemon = new MockRoutingDaemon;
  auto mockHardwareMonitor = new MockHardwareMonitor;
  auto mockQubit = new MockStationaryQubit;
  RuleEngineTestTarget c{mockQubit, routingdaemon, mockHardwareMonitor};

  auto info = std::make_unique<ConnectionSetupInfo>();
  info->qnic.type = QNIC_E;
  info->qnic.index = 0;

  swapping_result swapr;
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
  c.initialize();
  c.setAllResources(QNIC_E, 0, 0, mockQubit);
  c.setAllResources(QNIC_E, 0, 1, mockQubit);
  c.setAllResources(QNIC_E, 0, 2, mockQubit);
  auto part = c.allResources[QNIC_E][0].find(1);
  ASSERT_TRUE(part != c.allResources[QNIC_E][0].end());
  // check resource is updated?
  c.updateResources_EntanglementSwapping(swapr);
  auto part_after = c.allResources[QNIC_E][0].find(3);
  ASSERT_TRUE(part_after != c.allResources[QNIC_E][0].end());
  // old record was deleted properly
  auto part_after_old = c.allResources[QNIC_E][0].find(1);
  ASSERT_TRUE(part_after_old == c.allResources[QNIC_E][0].end());
}

}  // namespace

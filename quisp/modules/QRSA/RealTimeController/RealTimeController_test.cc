#include "RealTimeController.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include <utils/IComponentProviderStrategy.h>
#include "modules/QNIC.h"
#include "modules/QNIC/StationaryQubit/StationaryQubit.h"
#include "modules/QRSA/HardwareMonitor/HardwareMonitor.h"
#include "modules/QRSA/RoutingDaemon/RoutingDaemon.h"
#include "omnetpp/csimulation.h"

namespace {

using namespace omnetpp;
using namespace quisp::utils;
using namespace quisp::modules;

class MockStationaryQubit : public StationaryQubit {
 public:
  MOCK_METHOD(void, emitPhoton, (int pulse), (override));
  MOCK_METHOD(void, setFree, (bool consumed), (override));
};

class TestComponentProviderStrategy : public IComponentProviderStrategy {
 public:
  TestComponentProviderStrategy() : mockQubit(nullptr) {}
  TestComponentProviderStrategy(MockStationaryQubit* _qubit) : mockQubit(_qubit) {}
  ~TestComponentProviderStrategy() { delete mockQubit; }
  MockStationaryQubit* mockQubit = nullptr;
  omnetpp::cModule* getQNode() override { return nullptr; }
  RoutingDaemon* getRoutingDaemon() override { return nullptr; }
  HardwareMonitor* getHardwareMonitor() override { return nullptr; }
  StationaryQubit* getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) override {
    if (mockQubit == nullptr) mockQubit = new MockStationaryQubit();
    return mockQubit;
  };
};

class RTCTestTarget : public quisp::modules::RealTimeController {
 public:
  using quisp::modules::RealTimeController::initialize;
  using quisp::modules::RealTimeController::par;
  RTCTestTarget(MockStationaryQubit* mockQubit) : RealTimeController() {
    omnetpp::cParImpl* p = new omnetpp::cIntParImpl();
    const char* name = "address";
    p->setName(name);
    p->setIntValue(123);
    this->addPar(p);
    this->setName("rtc_test_target");
    this->provider.setStrategy(std::make_unique<TestComponentProviderStrategy>(mockQubit));
  }
};

TEST(RealTimeControllerTest, Init) {
  RTCTestTarget c{nullptr};
  c.initialize();
  ASSERT_EQ(c.par("address").intValue(), 123);
}
TEST(RealTimeControllerTest, EmitPhoton) {
  auto* qubit = new MockStationaryQubit{};
  RTCTestTarget c{qubit};
  c.initialize();

  EXPECT_CALL(*qubit, emitPhoton(7)).Times(1);
  c.EmitPhoton(1, 2, quisp::modules::QNIC_E, 7);
}

TEST(RealTimeControllerTest, ReInitializeStationaryQubit) {
  auto* qubit = new MockStationaryQubit{};
  RTCTestTarget c{qubit};
  c.initialize();

  EXPECT_CALL(*qubit, setFree(true)).Times(1);
  c.ReInitialize_StationaryQubit(1, 2, quisp::modules::QNIC_E, true);
}

}  // namespace

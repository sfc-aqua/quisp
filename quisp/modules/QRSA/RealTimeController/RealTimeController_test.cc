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
#include "test_utils/TestUtils.h"

namespace {

using namespace omnetpp;
using namespace quisp::utils;
using namespace quisp::modules;
using namespace quisp_test;

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy() : mockQubit(nullptr) {}
  Strategy(MockQubit* _qubit) : mockQubit(_qubit) {}
  ~Strategy() { delete mockQubit; }
  MockQubit* mockQubit = nullptr;
  IStationaryQubit* getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) override {
    if (mockQubit == nullptr) mockQubit = new MockQubit();
    return mockQubit;
  };
};

class RTCTestTarget : public quisp::modules::RealTimeController {
 public:
  using quisp::modules::RealTimeController::initialize;
  using quisp::modules::RealTimeController::par;
  RTCTestTarget(MockQubit* mockQubit) : RealTimeController() {
    auto* p = new omnetpp::internal::cIntParImpl();
    const char* name = "address";
    p->setName(name);
    p->setIntValue(123);
    this->addPar(p);
    this->setName("rtc_test_target");
    this->provider.setStrategy(std::make_unique<Strategy>(mockQubit));
  }
};

TEST(RealTimeControllerTest, Init) {
  RTCTestTarget c{nullptr};
  c.initialize();
  ASSERT_EQ(c.par("address").intValue(), 123);
}
TEST(RealTimeControllerTest, EmitPhoton) {
  prepareSimulation();
  auto* qubit = new MockQubit{};
  RTCTestTarget c{qubit};
  c.initialize();

  EXPECT_CALL(*qubit, emitPhoton(7)).Times(1);
  c.EmitPhoton(1, 2, quisp::modules::QNIC_E, 7);
}

TEST(RealTimeControllerTest, ReInitializeStationaryQubit) {
  prepareSimulation();
  auto* qubit = new MockQubit{};
  RTCTestTarget c{qubit};
  c.initialize();

  EXPECT_CALL(*qubit, setFree(true)).Times(1);
  c.ReInitialize_StationaryQubit(1, 2, quisp::modules::QNIC_E, true);
}

}  // namespace

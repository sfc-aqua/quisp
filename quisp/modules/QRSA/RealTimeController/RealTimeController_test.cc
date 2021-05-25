#include "RealTimeController.h"
#include <gtest/gtest.h>
#include <omnetpp.h>
#include <utils/IComponentProviderStrategy.h>

namespace {

using namespace omnetpp;
using namespace quisp::utils;
using namespace quisp::modules;

class TestComponentProviderStrategy : public IComponentProviderStrategy {
  omnetpp::cModule* getQNode() override { return nullptr; }
  StationaryQubit* getStationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type) override { return nullptr; };
};

class RTCTestTarget : public quisp::modules::RealTimeController {
 public:
  using quisp::modules::RealTimeController::initialize;
  using quisp::modules::RealTimeController::par;
  RTCTestTarget() : RealTimeController() {
    omnetpp::cParImpl* p = new omnetpp::cIntParImpl();
    const char* name = "address";
    p->setName(name);
    p->setIntValue(123);
    this->addPar(p);
    this->setName("rtc_test_target");
    this->provider.setStrategy(new TestComponentProviderStrategy{});
  }
};

TEST(RealTimeControllerTest, Init) {
  RTCTestTarget c{};
  c.initialize();
  ASSERT_EQ(c.par("address").intValue(), 123);
}
}  // namespace

#include "RealTimeController.h"
#include "gtest/gtest.h"

namespace {

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
  }
};

TEST(RealTimeControllerTest, Init) {
  RTCTestTarget c{};
  c.initialize();
  ASSERT_EQ(c.par("address").intValue(), 123);
}
}  // namespace

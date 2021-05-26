#include "RoutingDamon.h"
#include "gtest/gtest.h"

namespace {

class RoutingDaemonTestTarget : public quisp::modules::RoutingDaemon {
 public:
  using quisp::modules::RoutingDaemon::initialize;
  using quisp::modules::RoutingDaemon::par;
  RoutingDaemonTestTarget() : RealTimeController() {
    omnetpp::cParImpl* p = new omnetpp::cIntParImpl();
    const char* name = "address";
    p->setName(name);
    p->setIntValue(123);
    this->addPar(p);
    this->setName("rd_test_target");
  }
};

TEST(RoutingDaemonTest, Init) {
  RTCTestTarget c{};
  c.initialize();
  ASSERT_EQ(c.par("address").intValue(), 123);
}
}  // namespace

#include "RoutingDamon.h"
#include "gtest/gtest.h"

namespace {

class RDTestTarget : public quisp::modules::RoutingDaemon {
 public:
  using quisp::modules::RoutingDaemon::initialize;
  using quisp::modules::RoutingDaemon::par;
  RDTestTarget() : RoutingDaemon() {
    omnetpp::cParImpl* p = new omnetpp::cIntParImpl();
    const char* name = "address";
    p->setName(name);
    p->setIntValue(123);
    this->addPar(p);
    this->setName("rd_test_target");
  }
};

TEST(RoutingDaemonTest, InitTest) {
  RDTestTarget c{};
  c.initialize();
  ASSERT_EQ(c.par("address").intValue(), 123);
 }
}  // namespace

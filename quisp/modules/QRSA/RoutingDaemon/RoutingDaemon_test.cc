#include "RoutingDaemon.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include <utils/IComponentProviderStrategy.h>
#include "modules/QNIC.h"
#include "modules/QNIC/StationaryQubit/StationaryQubit.h"
#include "omnetpp/csimulation.h"

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
  int stage = 1;
  c.initialize(stage);
  ASSERT_EQ(c.par("address").intValue(), 123);
 }
}  // namespace

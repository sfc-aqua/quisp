#include "RoutingDaemon.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include <test_utils/TestUtils.h>
#include <utils/IComponentProviderStrategy.h>
#include "modules/QNIC.h"
#include "modules/QNIC/StationaryQubit/StationaryQubit.h"
#include "omnetpp/csimulation.h"

namespace {

using namespace omnetpp;
using namespace quisp::utils;
using namespace quisp::modules;
using namespace quisp_test;
using namespace testing;

class MockOmnetPrimitive : public cSimpleModule {
 public:
  MOCK_METHOD(cModule*, getParentModule, (), (override));
};

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy() : omnetPrimitive(nullptr) {}
  Strategy(MockOmnetPrimitive* primitives) : omnetPrimitive(primitives) {}
  ~Strategy() { delete omnetPrimitive; }
};

class RoutingDaemonTestTarget : public quisp::modules::RoutingDaemon {
 public:
  using quisp::modules::RoutingDaemon::initialize;
  using quisp::modules::RoutingDaemon::par;
  RoutingDaemonTestTarget(MockOmnetPrimitive* omnet_primitive) : RoutingDaemon() {
    omnetpp::cParImpl* p = new omnetpp::cIntParImpl();
    const char* name = "address";
    p->setName(name);
    p->setIntValue(123);
    this->addPar(p);
    this->setName("rd_test_target");

    this->provider.setStrategy(std::make_unique<Strategy>(omnet_primitive));
  }
};

TEST(RoutingDaemonTest, InitTest) {
  auto* mock_omnet_primitive = new MockOmnetPrimitive;
  EXPECT_CALL(*mock_omnet_primitive, getParentModule()).WillOnce(Return(omnetpp::cModule*));
  RoutingDaemonTestTarget c{mock_omnet_primitive};
  int stage = 1;
  c.initialize(stage);
  ASSERT_EQ(c.par("address").intValue(), 123);
}
}  // namespace

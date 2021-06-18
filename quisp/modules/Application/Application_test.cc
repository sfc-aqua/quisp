#include "Application.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include <utils/IComponentProviderStrategy.h>
#include "omnetpp/cexception.h"
#include "omnetpp/csimulation.h"
#include "test_utils/TestUtils.h"
#include "utils/utils.h"

namespace {

using namespace omnetpp;
using namespace quisp::utils;
using namespace quisp::modules;
using namespace quisp_test;

class MockQNode : public omnetpp::cModule {
 public:
  MockQNode() : omnetpp::cModule() {
    // setParInt(this, "address", 123);
  }
};

class StaticGate : public omnetpp::cGate {};
static StaticGate *static_gate = new StaticGate{};
static MockQNode *mock_qnode = new MockQNode{};
class TestGate : public omnetpp::cGate {
 public:
  TestGate(cModule *mod) {
    desc = new omnetpp::cGate::Desc{};
    desc->owner = mod;
    prevGate = static_gate;
  }
};

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy() {}
  cModule *getQNode() override { return mock_qnode; }
};

class AppTestTarget : public quisp::modules::Application {
 public:
  using quisp::modules::Application::initialize;
  using quisp::modules::Application::par;
  cGate *gate(const char *gatename, int index = -1) override {
    auto *g = new TestGate(this);
    return g;
  };
  AppTestTarget() : Application() { this->provider.setStrategy(std::make_unique<Strategy>()); }
};

void SetUp() {

}
TEST(AppTest, Init) {
  AppTestTarget app{};
  setParInt(mock_qnode, "address", 123);
  setParStr(mock_qnode, "nodeType", "qnode");
  setParBool(&app, "EndToEndConnection", true);
  setParInt(&app, "NumberOfResources", 5);
  setParInt(&app, "num_measure", 1);
  setParInt(&app, "TrafficPattern", 1);
  setParInt(&app, "LoneInitiatorAddress", 123);
  app.initialize();
  // ASSERT_EQ(app.par("address").intValue(), 123);
}
}  // namespace

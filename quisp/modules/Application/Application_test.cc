#include "Application.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include <omnetpp/ccomponenttype.h>
#include <omnetpp/cexception.h>
#include <omnetpp/clog.h>
#include <omnetpp/csimulation.h>
#include <test_utils/ModuleType.h>
#include <test_utils/StaticTestEnv.h>
#include <test_utils/TestUtils.h>
#include <utils/IComponentProviderStrategy.h>
#include <utils/utils.h>

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
class TestGate : public omnetpp::cGate {
 public:
  TestGate(cModule *mod) {
    desc = new omnetpp::cGate::Desc{};
    desc->owner = mod;
    prevGate = static_gate;
  }
};

MockQNode *mock_qnode;

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy() {}
  cModule *getQNode() override { return mock_qnode; }
};

class AppTestTarget : public quisp::modules::Application {
 public:
  using quisp::modules::Application::getParentModule;
  using quisp::modules::Application::initialize;
  using quisp::modules::Application::par;
  cGate *gate(const char *gatename, int index = -1) override {
    auto *g = new TestGate(this);
    return g;
  };
  AppTestTarget() : Application() { this->provider.setStrategy(std::make_unique<Strategy>()); }
  virtual ~AppTestTarget() {}
  std::vector<int> getOtherEndNodeAdresses() { return this->other_end_node_addresses; }
  int getAddress() { return this->my_address; }
};

TEST(AppTest, InitSimple) {
  mock_qnode = new MockQNode{};
  AppTestTarget app{};
  setParInt(mock_qnode, "address", 123);
  setParStr(mock_qnode, "nodeType", "qnode");
  setParBool(&app, "EndToEndConnection", true);
  setParInt(&app, "NumberOfResources", 5);
  setParInt(&app, "num_measure", 1);
  setParInt(&app, "TrafficPattern", 0);
  setParInt(&app, "LoneInitiatorAddress", 0);
  app.initialize();
  ASSERT_EQ(app.getAddress(), 123);
  ASSERT_EQ(app.getOtherEndNodeAdresses().size(), 0);
  delete mock_qnode;
}
TEST(AppTest, Init_OneConnection_NoSender) {
  mock_qnode = new MockQNode{};
  AppTestTarget app{};
  setParInt(mock_qnode, "address", 123);
  setParStr(mock_qnode, "nodeType", "qnode");
  setParBool(&app, "EndToEndConnection", true);
  setParInt(&app, "NumberOfResources", 5);
  setParInt(&app, "num_measure", 1);
  setParInt(&app, "TrafficPattern", 1);
  setParInt(&app, "LoneInitiatorAddress", 0);
  app.initialize();
  ASSERT_EQ(app.getAddress(), 123);
  ASSERT_EQ(app.getOtherEndNodeAdresses().size(), 0);
  delete mock_qnode;
}

TEST(AppTest, Init_OneConnection_Sender) {
  auto *sim = getSimulation();

  mock_qnode = new MockQNode{};
  setParInt(mock_qnode, "address", 123);
  setParStr(mock_qnode, "nodeType", "qnode");
  sim->registerComponent(mock_qnode);

  auto *mock_qnode2 = new MockQNode{};
  setParInt(mock_qnode2, "address", 456);
  setParStr(mock_qnode2, "nodeType", "qnode");
  sim->registerComponent(mock_qnode2);

  auto *app = new AppTestTarget;
  setParBool(app, "EndToEndConnection", true);
  setParInt(app, "NumberOfResources", 5);
  setParInt(app, "num_measure", 1);
  setParInt(app, "TrafficPattern", 1);
  setParInt(app, "LoneInitiatorAddress", 123);
  sim->setContext(app);
  app->setComponentType(new TestModuleType("test qnode"));
  app->setLogLevel(LogLevel::LOGLEVEL_DEBUG);
  app->callInitialize();

  // ASSERT_EQ(app.getAddress(), 123);
  // ASSERT_EQ(app.getOtherEndNodeAdresses().size(), 1);
  sim->callFinish();
  sim->deleteNetwork();
}

TEST(AppTest, Init_OneConnection_Sender2) {
  auto *env = dynamic_cast<quisp_test::StaticTestEnv *>(getEnvir());
  env->newSimulation();
  auto *sim = getSimulation();

  mock_qnode = new MockQNode{};
  setParInt(mock_qnode, "address", 123);
  setParStr(mock_qnode, "nodeType", "qnode");
  sim->registerComponent(mock_qnode);

  auto *mock_qnode2 = new MockQNode{};
  setParInt(mock_qnode2, "address", 456);
  setParStr(mock_qnode2, "nodeType", "qnode");
  sim->registerComponent(mock_qnode2);

  auto *app = new AppTestTarget;
  setParBool(app, "EndToEndConnection", true);
  setParInt(app, "NumberOfResources", 5);
  setParInt(app, "num_measure", 1);
  setParInt(app, "TrafficPattern", 1);
  setParInt(app, "LoneInitiatorAddress", 123);
  sim->registerComponent(app);
  sim->setContext(app);
  app->setComponentType(new TestModuleType("test qnode"));
  app->setLogLevel(LogLevel::LOGLEVEL_DEBUG);
  app->callInitialize();

  // ASSERT_EQ(app.getAddress(), 123);
  // ASSERT_EQ(app.getOtherEndNodeAdresses().size(), 1);
  sim->callFinish();

  env->newSimulation();
  sim = getSimulation();

  mock_qnode = new MockQNode{};
  setParInt(mock_qnode, "address", 123);
  setParStr(mock_qnode, "nodeType", "qnode");
  sim->registerComponent(mock_qnode);

  mock_qnode2 = new MockQNode{};
  setParInt(mock_qnode2, "address", 456);
  setParStr(mock_qnode2, "nodeType", "qnode");
  sim->registerComponent(mock_qnode2);

  app = new AppTestTarget;
  setParBool(app, "EndToEndConnection", true);
  setParInt(app, "NumberOfResources", 5);
  setParInt(app, "num_measure", 1);
  setParInt(app, "TrafficPattern", 1);
  setParInt(app, "LoneInitiatorAddress", 123);
  sim->registerComponent(app);
  sim->setContext(app);
  app->setComponentType(new TestModuleType("test qnode"));
  app->setLogLevel(LogLevel::LOGLEVEL_DEBUG);
  app->callInitialize();

  // ASSERT_EQ(app.getAddress(), 123);
  // ASSERT_EQ(app.getOtherEndNodeAdresses().size(), 1);
  sim->callFinish();
  sim->deleteNetwork();
}
}  // namespace

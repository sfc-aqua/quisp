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
#include "omnetpp/cobject.h"
#include "omnetpp/cownedobject.h"

namespace {

using namespace omnetpp;
using namespace quisp::utils;
using namespace quisp::modules;
using namespace quisp_test;

class MockQNode : public omnetpp::cModule {
 public:
  MockQNode(int addr) : omnetpp::cModule() {
    setParInt(this, "address", addr);
    setParStr(this, "nodeType", "qnode");
    setComponentType(new TestModuleType("test qnode"));
    finalizeParameters();
  }
  // virtual ~MockQNode() { setFlag(16, true); }
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
  Strategy(MockQNode *_qnode) : parent_qnode(_qnode) {}
  cModule *getQNode() override { return parent_qnode; }

 private:
  MockQNode *parent_qnode;
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
  AppTestTarget(MockQNode *parent_qnode) : Application() {
    this->provider.setStrategy(std::make_unique<Strategy>(parent_qnode));
    setComponentType(new TestModuleType("test qnode"));
  }
  virtual ~AppTestTarget() {}
  std::vector<int> getOtherEndNodeAdresses() { return this->other_end_node_addresses; }
  int getAddress() { return this->my_address; }
};

TEST(AppTest, InitSimple) {
  auto *sim = prepareSimulation();
  mock_qnode = new MockQNode{123};
  AppTestTarget app{mock_qnode};
  setParBool(&app, "EndToEndConnection", true);
  setParInt(&app, "NumberOfResources", 5);
  setParInt(&app, "num_measure", 1);
  setParInt(&app, "TrafficPattern", 0);
  setParInt(&app, "LoneInitiatorAddress", 0);
  app.callInitialize();
  ASSERT_EQ(app.getAddress(), 123);
  ASSERT_EQ(app.getOtherEndNodeAdresses().size(), 0);
}

TEST(AppTest, Init_OneConnection_NoSender) {
  auto *sim = prepareSimulation();
  mock_qnode = new MockQNode{123};
  AppTestTarget app{mock_qnode};
  setParBool(&app, "EndToEndConnection", true);
  setParInt(&app, "NumberOfResources", 5);
  setParInt(&app, "num_measure", 1);
  setParInt(&app, "TrafficPattern", 1);
  setParInt(&app, "LoneInitiatorAddress", 0);
  app.callInitialize();
  ASSERT_EQ(app.getAddress(), 123);
  ASSERT_EQ(app.getOtherEndNodeAdresses().size(), 0);
}

TEST(AppTest, Init_OneConnection_Sender) {
  auto *sim = prepareSimulation();

  mock_qnode = new MockQNode{123};
  sim->registerComponent(mock_qnode);

  auto *mock_qnode2 = new MockQNode{456};
  sim->registerComponent(mock_qnode2);

  auto *app = new AppTestTarget{mock_qnode};
  setParBool(app, "EndToEndConnection", true);
  setParInt(app, "NumberOfResources", 5);
  setParInt(app, "num_measure", 1);
  setParInt(app, "TrafficPattern", 1);
  setParInt(app, "LoneInitiatorAddress", 123);
  sim->setContext(app);
  // app->setLogLevel(LogLevel::LOGLEVEL_DEBUG);
  app->callInitialize();

  ASSERT_EQ(app->getAddress(), 123);
  ASSERT_EQ(app->getOtherEndNodeAdresses().size(), 1);
  sim->callInitialize();
  
  // auto *event = sim->takeNextEvent();
  // sim->executeEvent(event);
}

}  // namespace

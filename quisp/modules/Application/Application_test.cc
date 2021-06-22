#include "Application.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include <test_utils/TestUtils.h>
#include "classical_messages_m.h"

namespace {

using namespace omnetpp;
using namespace quisp::utils;
using namespace quisp::modules;
using namespace quisp_test;

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy(TestQNode *_qnode) : parent_qnode(_qnode) {}
  cModule *getQNode() override { return parent_qnode; }

 private:
  TestQNode *parent_qnode;
};

class AppTestTarget : public quisp::modules::Application {
 public:
  using quisp::modules::Application::getParentModule;
  using quisp::modules::Application::initialize;
  using quisp::modules::Application::par;
  cGate *gate(const char *gatename, int index = -1) override {
    if (strcmp(gatename, "toRouter") != 0) {
      throw cRuntimeError("unknown gate called");
    }
    return toRouterGate;
  };
  explicit AppTestTarget(TestQNode *parent_qnode) : Application(), toRouterGate(new TestGate(this)) {
    this->provider.setStrategy(std::make_unique<Strategy>(parent_qnode));
    setComponentType(new TestModuleType("test qnode"));
  }
  virtual ~AppTestTarget() { EVCB.gateDeleted(toRouterGate); }
  std::vector<int> getOtherEndNodeAdresses() { return this->other_end_node_addresses; }
  int getAddress() { return this->my_address; }

  TestGate *toRouterGate;
};

TEST(AppTest, InitSimple) {
  auto *sim = prepareSimulation();
  auto *mock_qnode = new TestQNode{123};
  auto *app = new AppTestTarget{mock_qnode};
  setParBool(app, "EndToEndConnection", true);
  setParInt(app, "NumberOfResources", 5);
  setParInt(app, "num_measure", 1);
  setParInt(app, "TrafficPattern", 0);
  setParInt(app, "LoneInitiatorAddress", 0);

  sim->registerComponent(app);
  app->callInitialize();

  ASSERT_EQ(app->getAddress(), mock_qnode->address);
  ASSERT_EQ(app->getOtherEndNodeAdresses().size(), 0);
}

TEST(AppTest, Init_OneConnection_NoSender) {
  auto *sim = prepareSimulation();
  auto *mock_qnode = new TestQNode{123};
  auto *app = new AppTestTarget{mock_qnode};
  setParBool(app, "EndToEndConnection", true);
  setParInt(app, "NumberOfResources", 5);
  setParInt(app, "num_measure", 1);
  setParInt(app, "TrafficPattern", 1);
  setParInt(app, "LoneInitiatorAddress", 0);

  sim->registerComponent(app);
  app->callInitialize();

  ASSERT_EQ(app->getAddress(), mock_qnode->address);
  ASSERT_EQ(app->getOtherEndNodeAdresses().size(), 0);
}

TEST(AppTest, Init_OneConnection_Sender) {
  auto *sim = prepareSimulation();
  auto *mock_qnode = new TestQNode{123};

  auto *app = new AppTestTarget{mock_qnode};
  setParBool(app, "EndToEndConnection", true);
  setParInt(app, "NumberOfResources", 5);
  setParInt(app, "num_measure", 1);
  setParInt(app, "TrafficPattern", 1);
  setParInt(app, "LoneInitiatorAddress", mock_qnode->address);
  sim->registerComponent(app);

  auto *mock_qnode2 = new TestQNode{456};
  app->callInitialize();

  ASSERT_EQ(app->getAddress(), mock_qnode->address);
  ASSERT_EQ(app->getOtherEndNodeAdresses().size(), 1);

  sim->run();
  // assert app sent one message to "toRouter" gate
  ASSERT_EQ(app->toRouterGate->messages.size(), 1);

  auto *msg = app->toRouterGate->messages.at(0);
  ASSERT_NE(msg, nullptr);

  auto *pkt = dynamic_cast<ConnectionSetupRequest *>(msg);
  ASSERT_EQ(pkt->getActual_srcAddr(), 123);
  ASSERT_EQ(pkt->getActual_destAddr(), mock_qnode2->address);
  ASSERT_EQ(pkt->getSrcAddr(), 123);
  ASSERT_EQ(pkt->getDestAddr(), 123);
  ASSERT_EQ(pkt->getNumber_of_required_Bellpairs(), 5);
}

TEST(AppTest, Init_OneConnection_Sender_TrafficPattern2) {
  auto *sim = prepareSimulation();
  auto *mock_qnode = new TestQNode{123};
  auto *mock_qnode2 = new TestQNode{456};
  auto *app = new AppTestTarget{mock_qnode};
  setParBool(app, "EndToEndConnection", true);
  setParInt(app, "NumberOfResources", 5);
  setParInt(app, "num_measure", 1);
  setParInt(app, "TrafficPattern", 2);
  setParInt(app, "LoneInitiatorAddress", 123);
  sim->registerComponent(app);

  app->callInitialize();
  ASSERT_EQ(app->getAddress(), 123);
  ASSERT_EQ(app->getOtherEndNodeAdresses().size(), 1);

  sim->run();
  ASSERT_EQ(app->toRouterGate->messages.size(), 1);

  auto *msg = app->toRouterGate->messages.at(0);
  ASSERT_NE(msg, nullptr);
  auto *pkt = dynamic_cast<ConnectionSetupRequest *>(msg);
  ASSERT_EQ(pkt->getActual_srcAddr(), 123);
  ASSERT_EQ(pkt->getActual_destAddr(), mock_qnode2->address);
  ASSERT_EQ(pkt->getSrcAddr(), 123);
  ASSERT_EQ(pkt->getDestAddr(), 123);
  ASSERT_EQ(pkt->getNumber_of_required_Bellpairs(), 5);
}

}  // namespace

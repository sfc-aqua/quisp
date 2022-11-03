#include "Application.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <messages/classical_messages.h>
#include <omnetpp.h>
#include <test_utils/TestUtils.h>
#include <unordered_map>

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
  explicit AppTestTarget(TestQNode *parent_qnode) : Application(), toRouterGate(new TestGate(this, "toRouter")) {
    this->provider.setStrategy(std::make_unique<Strategy>(parent_qnode));
    setComponentType(new TestModuleType("test qnode"));
  }
  virtual ~AppTestTarget() { EVCB.gateDeleted(toRouterGate); }
  std::unordered_map<int, int> getEndNodeWeightMap() { return this->end_node_weight_map; }
  int getAddress() { return this->my_address; }

  TestGate *toRouterGate;
};

TEST(AppTest, Init_IsNotInitiator) {
  auto *sim = prepareSimulation();
  auto *mock_qnode = new TestQNode{123, 100, false};
  auto *app = new AppTestTarget{mock_qnode};

  sim->registerComponent(app);
  app->callInitialize();

  ASSERT_EQ(app->getAddress(), mock_qnode->address);
  ASSERT_EQ(app->getEndNodeWeightMap().size(), 0);
}

TEST(AppTest, Init_IsInitiator) {
  auto *sim = prepareSimulation();
  auto *mock_qnode = new TestQNode{123, 100, true};
  auto *app = new AppTestTarget{mock_qnode};

  setParBool(mock_qnode, "isInitiator", true);

  sim->registerComponent(app);
  app->callInitialize();

  ASSERT_EQ(app->getAddress(), mock_qnode->address);
  ASSERT_EQ(app->getEndNodeWeightMap().size(), 1);
  ASSERT_NE(app->getEndNodeWeightMap().find(123), app->getEndNodeWeightMap().end());
  ASSERT_EQ(app->getEndNodeWeightMap()[123], 0);
}

TEST(AppTest, Init_WeightMap_Generation) {
  auto *sim = prepareSimulation();
  auto *mock_qnode = new TestQNode{123, 321, true};
  auto *mock_qnode2 = new TestQNode{456, 654, false};
  auto *mock_qnode3 = new TestQNode{789, 987, false};

  auto *app = new AppTestTarget{mock_qnode};

  sim->registerComponent(app);
  app->callInitialize();

  ASSERT_EQ(app->getAddress(), mock_qnode->address);
  ASSERT_EQ(app->getEndNodeWeightMap().size(), 3);
  ASSERT_NE(app->getEndNodeWeightMap().find(123), app->getEndNodeWeightMap().end());
  ASSERT_NE(app->getEndNodeWeightMap().find(456), app->getEndNodeWeightMap().end());
  ASSERT_NE(app->getEndNodeWeightMap().find(789), app->getEndNodeWeightMap().end());

  ASSERT_EQ(app->getEndNodeWeightMap()[123], 0);
  ASSERT_EQ(app->getEndNodeWeightMap()[456], 654);
  ASSERT_EQ(app->getEndNodeWeightMap()[789], 987);
}

}  // namespace

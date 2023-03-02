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
using namespace quisp::messages;
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
    this->id = 1;
    this->provider.setStrategy(std::make_unique<Strategy>(parent_qnode));
    setComponentType(new TestModuleType("test qnode"));
  }
  virtual ~AppTestTarget() { EVCB.gateDeleted(toRouterGate); }
  std::unordered_map<int, int> getEndNodeWeightMap() { return this->end_node_weight_map; }
  int getId() { return this->id; }
  int getAddress() { return this->my_address; }
  bool isInitiator() { return this->is_initiator; }

  TestGate *toRouterGate;
};

TEST(AppTest, Init_IsNotInitiator) {
  auto *sim = prepareSimulation();
  auto *mock_qnode = new TestQNode{123, 100, false};
  auto *app = new AppTestTarget{mock_qnode};

  sim->registerComponent(app);
  app->callInitialize();
  ASSERT_EQ(app->getId(), 1);
  ASSERT_EQ(app->getAddress(), mock_qnode->address);
  ASSERT_EQ(app->getEndNodeWeightMap().size(), 0);
}

TEST(AppTest, Init_IsInitiator) {
  auto *sim = prepareSimulation();
  auto *mock_qnode = new TestQNode{123, 100, true};
  auto *app = new AppTestTarget{mock_qnode};

  setParDouble(app, "request_generation_interval", 5);
  setParInt(app, "number_of_bellpair", 10);
  setParBool(app, "has_specific_recipients", false);

  sim->registerComponent(app);
  app->callInitialize();

  ASSERT_EQ(app->getId(), 1);
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
  setParDouble(app, "request_generation_interval", 5);
  setParInt(app, "number_of_bellpair", 10);
  setParBool(app, "has_specific_recipients", false);

  sim->registerComponent(app);
  app->callInitialize();

  ASSERT_EQ(app->getId(), 1);
  ASSERT_EQ(app->getAddress(), mock_qnode->address);
  ASSERT_EQ(app->getEndNodeWeightMap().size(), 3);
  ASSERT_NE(app->getEndNodeWeightMap().find(123), app->getEndNodeWeightMap().end());
  ASSERT_NE(app->getEndNodeWeightMap().find(456), app->getEndNodeWeightMap().end());
  ASSERT_NE(app->getEndNodeWeightMap().find(789), app->getEndNodeWeightMap().end());

  ASSERT_EQ(app->getEndNodeWeightMap()[123], 0);
  ASSERT_EQ(app->getEndNodeWeightMap()[456], 654);
  ASSERT_EQ(app->getEndNodeWeightMap()[789], 987);
}

TEST(AppTest, Init_Connection_Setup_Message_Send) {
  auto *sim = prepareSimulation();
  auto *mock_qnode = new TestQNode{123, 100, true};
  auto *mock_qnode2 = new TestQNode{456, 100, false};
  auto *app = new AppTestTarget{mock_qnode};
  sim->setConfigValue("sim-time-limit", "5.1s");

  setParDouble(app, "request_generation_interval", 5);
  setParInt(app, "number_of_bellpair", 10);
  setParBool(app, "has_specific_recipients", false);

  sim->registerComponent(app);
  app->callInitialize();

  ASSERT_EQ(app->getId(), 1);
  ASSERT_EQ(app->getAddress(), 123);
  ASSERT_EQ(app->getEndNodeWeightMap().size(), 2);

  sim->run();
  ASSERT_EQ(app->toRouterGate->messages.size(), 1);

  auto *msg = app->toRouterGate->messages.at(0);
  ASSERT_NE(msg, nullptr);
  auto *pkt = dynamic_cast<ConnectionSetupRequest *>(msg);
  ASSERT_EQ(pkt->getApplicationId(), 1);
  ASSERT_EQ(pkt->getActual_srcAddr(), 123);
  ASSERT_EQ(pkt->getActual_destAddr(), mock_qnode2->address);
  ASSERT_EQ(pkt->getSrcAddr(), 123);
  ASSERT_EQ(pkt->getDestAddr(), 123);
}

TEST(AppTest, Specifying_Empty_As_Recipients) {
  auto *sim = prepareSimulation();
  auto *mock_qnode = new TestQNode{123, 100, true};
  auto *mock_qnode2 = new TestQNode{456, 100, false};
  auto *app = new AppTestTarget{mock_qnode};

  setParDouble(app, "request_generation_interval", 5);
  setParInt(app, "number_of_bellpair", 10);
  setParBool(app, "has_specific_recipients", true);

  cValueArray *cval_arr = new cValueArray();
  quisp_test::utils::setParObject(app, "possible_recipients", cval_arr);

  sim->registerComponent(app);
  EXPECT_ANY_THROW(app->callInitialize());
}

TEST(AppTest, Specifying_Self_As_Recipients) {
  auto *sim = prepareSimulation();
  auto *mock_qnode = new TestQNode{123, 100, true};
  auto *mock_qnode2 = new TestQNode{456, 100, false};
  auto *app = new AppTestTarget{mock_qnode};

  setParDouble(app, "request_generation_interval", 5);
  setParInt(app, "number_of_bellpair", 10);
  setParBool(app, "has_specific_recipients", true);

  cValueArray *cval_arr = new cValueArray();
  cval_arr->add(123);
  cval_arr->add(456);

  quisp_test::utils::setParObject(app, "possible_recipients", cval_arr);

  sim->registerComponent(app);
  EXPECT_ANY_THROW(app->callInitialize());
}

TEST(AppTest, Specifying_Not_Existing_Address_As_Recipients) {
  auto *sim = prepareSimulation();
  auto *mock_qnode = new TestQNode{123, 100, true};
  auto *mock_qnode2 = new TestQNode{456, 100, false};
  auto *app = new AppTestTarget{mock_qnode};

  setParDouble(app, "request_generation_interval", 5);
  setParInt(app, "number_of_bellpair", 10);
  setParBool(app, "has_specific_recipients", true);

  cValueArray *cval_arr = new cValueArray();
  cval_arr->add(456);
  cval_arr->add(999);

  quisp_test::utils::setParObject(app, "possible_recipients", cval_arr);

  sim->registerComponent(app);
  EXPECT_ANY_THROW(app->callInitialize());
}

TEST(AppTest, Specifying_Valid_Addresses_As_Recipients) {
  auto *sim = prepareSimulation();
  auto *mock_qnode = new TestQNode{123, 100, true};
  auto *mock_qnode2 = new TestQNode{456, 654, false};
  auto *mock_qnode3 = new TestQNode{789, 987, false};
  auto *app = new AppTestTarget{mock_qnode};

  setParDouble(app, "request_generation_interval", 5);
  setParInt(app, "number_of_bellpair", 10);
  setParBool(app, "has_specific_recipients", true);

  cValueArray *cval_arr = new cValueArray();
  cval_arr->add(456);

  quisp_test::utils::setParObject(app, "possible_recipients", cval_arr);

  sim->registerComponent(app);
  app->callInitialize();

  ASSERT_EQ(app->getId(), 1);
  ASSERT_EQ(app->getAddress(), mock_qnode->address);
  ASSERT_EQ(app->getEndNodeWeightMap().size(), 2);  // self and 456
  ASSERT_NE(app->getEndNodeWeightMap().find(123), app->getEndNodeWeightMap().end());
  ASSERT_NE(app->getEndNodeWeightMap().find(456), app->getEndNodeWeightMap().end());
  ASSERT_EQ(app->getEndNodeWeightMap().find(789), app->getEndNodeWeightMap().end());

  ASSERT_EQ(app->getEndNodeWeightMap()[456], 654);
}

}  // namespace

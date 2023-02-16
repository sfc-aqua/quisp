#include <gtest/gtest.h>

#include <test_utils/TestUtils.h>

#include "Router.h"
#include "test_utils/QNode.h"
using namespace quisp_test;
using namespace quisp_test::utils;
using OriginalRouter = quisp::modules::Router;

namespace {

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy(TestQNode* _qnode) : parent_qnode(_qnode) {}
  cModule* getQNode() override { return parent_qnode; }

 private:
  TestQNode* parent_qnode;
};

class Router : public OriginalRouter {
 public:
  using OriginalRouter::handleMessage;
  using OriginalRouter::initialize;
  explicit Router(TestQNode* parent_qnode) : OriginalRouter() {
    this->provider.setStrategy(std::make_unique<Strategy>(parent_qnode));
    this->setComponentType(new TestModuleType("test_router"));
  }
};

class RouterTest : public ::testing::Test {
 protected:
  void SetUp() {
    sim = prepareSimulation();
    qnode = new TestQNode(10, 0, true);
    router = new Router(qnode);
    sim->registerComponent(router);
    router->callInitialize();
  }
  void TearDown() {}

  TestSimulation* sim;
  Router* router;
  TestQNode* qnode;
};
TEST_F(RouterTest, handleMessage) { sim->run(); }
}  // namespace
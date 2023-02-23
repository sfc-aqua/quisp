#include <gtest/gtest.h>

#include <messages/classical_messages.h>
#include <test_utils/TestUtils.h>

#include "Router.h"
#include "messages/connection_setup_messages_m.h"
#include "test_utils/Gate.h"
using namespace quisp_test;
using namespace quisp_test::utils;
using namespace quisp::messages;
using OriginalRouter = quisp::modules::Router;

namespace {

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy(TestQNode* _qnode) : parent_qnode(_qnode) {}
  cModule* getNode() override { return parent_qnode; }
  QNodeAddr getNodeAddr() override { return parent_qnode->address; }

 private:
  TestQNode* parent_qnode;
};

class Router : public OriginalRouter {
 public:
  using OriginalRouter::handleMessage;
  using OriginalRouter::initialize;
  using OriginalRouter::routing_table;
  explicit Router(TestQNode* parent_qnode) : OriginalRouter() {
    this->provider.setStrategy(std::make_unique<Strategy>(parent_qnode));
    this->setComponentType(new TestModuleType("test_router"));
    hmPort = new TestGate(this, "hmPort$o");
    rePort = new TestGate(this, "rePort$o");
    cmPort = new TestGate(this, "cmPort$o");
    queueGate = new TestGate(this, "toQueue");
    routing_table.insert({QNodeAddr{8}, queueGate->getId()});
  }

  TestGate* hmPort;
  TestGate* rePort;
  TestGate* cmPort;
  TestGate* queueGate;

  std::map<const char*, cGate*> ports{};
  cGate* gate(const char* gatename, int index = -1) {
    if (strcmp(gatename, "hmPort$o") == 0) return hmPort;
    if (strcmp(gatename, "cmPort$o") == 0) return cmPort;
    if (strcmp(gatename, "rePort$o") == 0) return rePort;
    if (strcmp(gatename, "toQueue") == 0) return queueGate;
    error("port: %s not found", gatename);
    return nullptr;
  }
};

class RouterTest : public ::testing::Test {
 protected:
  void SetUp() {
    sim = prepareSimulation();
    qnode = new TestQNode(10, 0, true);
    router = new Router(qnode);
    sim->registerComponent(router);
    sim->setContext(router);
    router->callInitialize();
  }
  void TearDown() {}

  TestSimulation* sim;
  Router* router;
  TestQNode* qnode;
};

TEST_F(RouterTest, handlePacketForUnknownAddr) {
  auto msg = new ConnectionSetupRequest;
  msg->setDestAddr(QNodeAddr{7});
  EXPECT_THROW({ router->handleMessage(msg); }, cRuntimeError);
}

TEST_F(RouterTest, handlePacketForOtherNode) {
  auto msg = new ConnectionSetupRequest;
  msg->setDestAddr(QNodeAddr{8});
  router->handleMessage(msg);
  ASSERT_EQ(router->queueGate->messages.size(), 1);
  {
    auto* msg = router->queueGate->messages.at(0);
    auto req = dynamic_cast<ConnectionSetupRequest*>(msg);
    EXPECT_EQ(req->getHopCount(), 1);
  }
}

TEST_F(RouterTest, handleConnSetupRequest) {
  auto msg = new ConnectionSetupRequest;
  msg->setDestAddr(QNodeAddr{10});
  router->handleMessage(msg);
  ASSERT_EQ(router->cmPort->messages.size(), 1);
}

TEST_F(RouterTest, handleConnSetupResponse) {
  auto msg = new ConnectionSetupResponse;
  msg->setDestAddr(QNodeAddr{10});
  router->handleMessage(msg);
  ASSERT_EQ(router->cmPort->messages.size(), 1);
}

TEST_F(RouterTest, handleBSMTimingNotification) {
  auto msg = new BSMTimingNotification;
  msg->setDestAddr(QNodeAddr{10});
  router->handleMessage(msg);
  ASSERT_EQ(router->rePort->messages.size(), 1);
}

TEST_F(RouterTest, handleEPPSTimingNotifier) {
  auto msg = new EPPStimingNotifier;
  msg->setDestAddr(QNodeAddr{10});
  router->handleMessage(msg);
  ASSERT_EQ(router->rePort->messages.size(), 1);
}

TEST_F(RouterTest, handleRejectConnectionSetupReq) {
  auto msg = new RejectConnectionSetupRequest;
  msg->setDestAddr(QNodeAddr{10});
  router->handleMessage(msg);
  ASSERT_EQ(router->cmPort->messages.size(), 1);
}

TEST_F(RouterTest, handleInternalRuleSetForwarding) {
  auto msg = new InternalRuleSetForwarding;
  msg->setDestAddr(QNodeAddr{10});
  router->handleMessage(msg);
  ASSERT_EQ(router->rePort->messages.size(), 1);
}

TEST_F(RouterTest, handleInternalRuleSetForwarding_Application) {
  auto msg = new InternalRuleSetForwarding_Application;
  msg->setDestAddr(QNodeAddr{10});
  router->handleMessage(msg);
  ASSERT_EQ(router->rePort->messages.size(), 1);
}

TEST_F(RouterTest, handleSwappingResult) {
  auto msg = new SwappingResult;
  msg->setDestAddr(QNodeAddr{10});
  router->handleMessage(msg);
  ASSERT_EQ(router->rePort->messages.size(), 1);
}

TEST_F(RouterTest, handleLinkTomographyAck) {
  auto msg = new LinkTomographyAck;
  msg->setDestAddr(QNodeAddr{10});
  router->handleMessage(msg);
  ASSERT_EQ(router->hmPort->messages.size(), 1);
}

TEST_F(RouterTest, handleLinkTomographyRequest) {
  auto msg = new LinkTomographyRequest;
  msg->setDestAddr(QNodeAddr{10});
  router->handleMessage(msg);
  ASSERT_EQ(router->hmPort->messages.size(), 1);
}

TEST_F(RouterTest, handleLinkTomographyRuleSet) {
  auto msg = new LinkTomographyRuleSet;
  msg->setDestAddr(QNodeAddr{10});
  router->handleMessage(msg);
  ASSERT_EQ(router->rePort->messages.size(), 1);
}

TEST_F(RouterTest, handlePurificationResult) {
  auto msg = new PurificationResult;
  msg->setDestAddr(QNodeAddr{10});
  router->handleMessage(msg);
  ASSERT_EQ(router->rePort->messages.size(), 1);
}

TEST_F(RouterTest, handleStopEmitting) {
  auto msg = new StopEmitting;
  msg->setDestAddr(QNodeAddr{10});
  router->handleMessage(msg);
  ASSERT_EQ(router->rePort->messages.size(), 1);
}
}  // namespace

#include <gtest/gtest.h>

#include <messages/classical_messages.h>
#include <test_utils/TestUtils.h>

#include "Router.h"
#include "modules/SharedResource/SharedResource.h"

using namespace quisp_test;
using namespace quisp_test::utils;
using namespace quisp::messages;
using namespace quisp::modules::SharedResource;
using OriginalRouter = quisp::modules::Router;

namespace {

class MockNode : public quisp_test::TestQNode {
 public:
  MockNode(int addr, int mass, bool is_initiator, bool i_am_qnode) : TestQNode(addr, mass, is_initiator), is_qnode(i_am_qnode) {}
  MockNode(int addr, int mass, bool is_initiator) : TestQNode(addr, mass, is_initiator), is_qnode(true) {}
  bool is_qnode;
};

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy(MockNode* _qnode) : parent_qnode(_qnode) {}
  cModule* getNode() override { return parent_qnode; }
  int getNodeAddr() override { return parent_qnode->address; }
  SharedResource* getSharedResource() override { return &shared_resource; }

 private:
  MockNode* parent_qnode;
  SharedResource shared_resource;
};

class Router : public OriginalRouter {
 public:
  using OriginalRouter::handleMessage;
  using OriginalRouter::initialize;
  using OriginalRouter::routing_table;
  explicit Router(MockNode* parent_qnode) : OriginalRouter() {
    this->provider.setStrategy(std::make_unique<Strategy>(parent_qnode));
    this->setComponentType(new TestModuleType("test_router"));
    hmPort = new TestGate(this, "hmPort$o");
    rePort = new TestGate(this, "rePort$o");
    cmPort = new TestGate(this, "cmPort$o");
    rdPort = new TestGate(this, "rdPort$o");
    queueGate = new TestGate(this, "toQueue");
    routing_table.insert({8, queueGate->getId()});
  }

  TestGate* hmPort;
  TestGate* rePort;
  TestGate* cmPort;
  TestGate* rdPort;
  TestGate* queueGate;

  std::map<const char*, cGate*> ports{};
  cGate* gate(const char* gatename, int index = -1) override {
    if (strcmp(gatename, "hmPort$o") == 0) return hmPort;
    if (strcmp(gatename, "cmPort$o") == 0) return cmPort;
    if (strcmp(gatename, "rePort$o") == 0) return rePort;
    if (strcmp(gatename, "rdPort$o") == 0) return rdPort;
    if (strcmp(gatename, "toQueue") == 0) return queueGate;
    error("port: %s not found", gatename);
    return nullptr;
  }
  bool parentModuleIsQNode() override { return dynamic_cast<MockNode*>(provider.getNode())->is_qnode; }
  void setIsQnode(bool is_qnode) { dynamic_cast<MockNode*>(provider.getNode())->is_qnode = is_qnode; }
};

class RouterTest : public ::testing::Test {
 protected:
  void SetUp() {
    sim = prepareSimulation();
    node = new MockNode(10, 0, true);
    router = new Router(node);
    sim->registerComponent(router);
    sim->setContext(router);
    router->callInitialize();
  }
  void TearDown() {}

  /**
   * This function mimics the behavior of Omnet++ internals
   * that sets up the message arrival to Router module.
   * Call this function before router->handleMessages
   * when you want to retrieve the info of the arrival gate.
   */
  void mockMessageArrival(cMessage* msg) {
    int queue_size = 1;
    int arrival_gate_index = 0;
    router->addGateVector("fromQueue", cGate::Type::INPUT, queue_size);
    msg->setArrival(router->getId(), router->findGate("fromQueue", arrival_gate_index));
  }

  TestSimulation* sim;
  Router* router;
  MockNode* node;
};

TEST_F(RouterTest, handlePacketForUnknownAddr) {
  auto msg = new ConnectionSetupRequest;
  msg->setDestAddr(7);
  EXPECT_THROW({ router->handleMessage(msg); }, cRuntimeError);
}

TEST_F(RouterTest, handlePacketForOtherNode) {
  auto msg = new ConnectionSetupRequest;
  msg->setDestAddr(8);
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
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->cmPort->messages.size(), 1);
}

TEST_F(RouterTest, handleConnSetupResponse) {
  auto msg = new ConnectionSetupResponse;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->cmPort->messages.size(), 1);
}

TEST_F(RouterTest, handleBSMTimingNotification) {
  auto msg = new BSMTimingNotification;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->rePort->messages.size(), 1);
}

TEST_F(RouterTest, handleEPPSTimingNotifier) {
  auto msg = new EPPStimingNotifier;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->rePort->messages.size(), 1);
}

TEST_F(RouterTest, handleRejectConnectionSetupReq) {
  auto msg = new RejectConnectionSetupRequest;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->cmPort->messages.size(), 1);
}

TEST_F(RouterTest, handleInternalRuleSetForwarding) {
  auto msg = new InternalRuleSetForwarding;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->rePort->messages.size(), 1);
}

TEST_F(RouterTest, handleInternalRuleSetForwarding_Application) {
  auto msg = new InternalRuleSetForwarding_Application;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->rePort->messages.size(), 1);
}

TEST_F(RouterTest, handleSwappingResult) {
  auto msg = new SwappingResult;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->rePort->messages.size(), 1);
}

TEST_F(RouterTest, handleLinkTomographyAck) {
  auto msg = new LinkTomographyAck;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->hmPort->messages.size(), 1);
}

TEST_F(RouterTest, handleLinkTomographyRequest) {
  auto msg = new LinkTomographyRequest;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->hmPort->messages.size(), 1);
}

TEST_F(RouterTest, handleLinkTomographyRuleSet) {
  auto msg = new LinkTomographyRuleSet;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->rePort->messages.size(), 1);
}

TEST_F(RouterTest, handlePurificationResult) {
  auto msg = new PurificationResult;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->rePort->messages.size(), 1);
}

TEST_F(RouterTest, handleStopEmitting) {
  auto msg = new StopEmitting;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->rePort->messages.size(), 1);
}

TEST_F(RouterTest, handleOspfPacket) {
  auto msg = new OspfPacket;
  msg->setDestAddr(10);
  router->handleMessage(msg);
  ASSERT_EQ(router->rdPort->messages.size(), 1);

  auto elo = new OspfHelloPacket;
  elo->setDestAddr(10);
  router->handleMessage(elo);
  ASSERT_EQ(router->rdPort->messages.size(), 2);

  auto dbd = new OspfDbdPacket;
  dbd->setDestAddr(10);
  router->handleMessage(dbd);
  ASSERT_EQ(router->rdPort->messages.size(), 3);

  auto lsr = new OspfLsrPacket;
  lsr->setDestAddr(10);
  router->handleMessage(lsr);
  ASSERT_EQ(router->rdPort->messages.size(), 4);

  auto lsu = new OspfLsuPacket;
  lsu->setDestAddr(10);
  router->handleMessage(lsu);
  ASSERT_EQ(router->rdPort->messages.size(), 5);

  auto ack = new OspfLsAckPacket;
  ack->setDestAddr(10);
  router->handleMessage(ack);
  ASSERT_EQ(router->rdPort->messages.size(), 6);
}

TEST_F(RouterTest, nonQNodeForwardOspfPacket) {
  auto msg = new OspfHelloPacket;
  msg->setSrcAddr(10);
  msg->setSending_gate_index(0);
  msg->setDestAddr(-1);
  router->setIsQnode(false);

  mockMessageArrival(msg);
  router->handleMessage(msg);
  ASSERT_EQ(router->queueGate->messages.size(), 1);
}

TEST_F(RouterTest, sendOspfHelloPacketToQueue) {
  auto msg = new OspfHelloPacket;
  msg->setSrcAddr(10);
  msg->setSending_gate_index(0);
  msg->setDestAddr(-1);

  router->handleMessage(msg);
  ASSERT_EQ(router->queueGate->messages.size(), 1);
}

TEST_F(RouterTest, redirectOspfHelloPacketToRoutingDaemon) {
  auto msg = new OspfHelloPacket;
  msg->setSrcAddr(8);
  msg->setDestAddr(-1);

  router->handleMessage(msg);
  ASSERT_EQ(router->rdPort->messages.size(), 1);
}
}  // namespace

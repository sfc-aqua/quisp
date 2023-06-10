#include <gtest/gtest.h>

#include <messages/classical_messages.h>
#include <test_utils/TestUtils.h>

#include "Router.h"
#include "gmock/gmock-spec-builders.h"
#include "messages/connection_setup_messages_m.h"
#include "messages/ospf_messages_m.h"
#include "modules/SharedResource/SharedResource.h"
#include "test_utils/Gate.h"
using namespace quisp_test;
using namespace quisp_test::utils;
using namespace quisp::messages;
using namespace quisp::modules::SharedResource;
using OriginalRouter = quisp::modules::Router;

namespace {

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy(TestQNode* _qnode) : parent_qnode(_qnode) {}
  cModule* getNode() override { return parent_qnode; }
  int getNodeAddr() override { return parent_qnode->address; }
  SharedResource* getSharedResource() override { return &shared_resource; }

 private:
  TestQNode* parent_qnode;
  SharedResource shared_resource;
};

class Router : public OriginalRouter {
 public:
  using OriginalRouter::handleMessage;
  using OriginalRouter::initialize;
  using OriginalRouter::my_address;
  using OriginalRouter::neighbor_table;
  using OriginalRouter::OspfNeighborInfo;
  using OriginalRouter::ospfSendNeighbor;
  using OriginalRouter::ospfSendNeighbors;
  using OriginalRouter::routing_table;
  using OriginalRouter::adj_list;
  explicit Router(TestQNode* parent_qnode) : OriginalRouter() {
    this->provider.setStrategy(std::make_unique<Strategy>(parent_qnode));
    this->setComponentType(new TestModuleType("test_router"));
    hmPort = new TestGate(this, "hmPort$o");
    rePort = new TestGate(this, "rePort$o");
    cmPort = new TestGate(this, "cmPort$o");
    queueGate = new TestGate(this, "toQueue");
    routing_table.insert({8, queueGate->getId()});
  }

  TestGate* hmPort;
  TestGate* rePort;
  TestGate* cmPort;
  TestGate* queueGate;

  std::map<const char*, cGate*> ports{};
  cGate* gate(const char* gatename, int index = -1) override {
    if (strcmp(gatename, "hmPort$o") == 0) return hmPort;
    if (strcmp(gatename, "cmPort$o") == 0) return cmPort;
    if (strcmp(gatename, "rePort$o") == 0) return rePort;
    if (strcmp(gatename, "toQueue") == 0) return queueGate;
    error("port: %s not found", gatename);
    return nullptr;
  }
  size_t getNumNeighbors() const override { return 1; }
};

class RouterTest : public ::testing::Test {
 protected:
  void SetUp() {
    sim = prepareSimulation();
    qnode = new TestQNode(10, 0, true);
    router = new Router(qnode);
    sim->registerComponent(router);
    sim->setContext(router);
    router->callInitialize();  // Router sends a message at initialization
    // pop the sent message so the tests won't be affected by the message
    router->queueGate->messages.pop_back();
  }
  void TearDown() {}

  /**
   * This function mimics the behavior of Omnet++ internals
   * that sets up the message arrival to Router module.
   * Call this function before router->handleMessages
   * when you want to retrieve the info of the arrival gate.
   */
  void mockMessageArrival(OspfHelloPacket* msg) {
    int queue_size = 1;
    int arrival_gate_index = 0;
    router->addGateVector("fromQueue", cGate::Type::INPUT, queue_size);
    msg->setArrival(router->getId(), router->findGate("fromQueue", arrival_gate_index));
  }

  TestSimulation* sim;
  Router* router;
  TestQNode* qnode;
};

TEST_F(RouterTest, ospfSendHelloPacketAtInitialization) {
  router->ospfSendNeighbors();
  auto down_state_msg = router->queueGate->messages.front();
  auto* down_state_packet = check_and_cast<OspfHelloPacket*>(down_state_msg);

  ASSERT_EQ(down_state_packet->getSrcAddr(), router->my_address);
  ASSERT_EQ(down_state_packet->getNeighborsArraySize(), 0);
}

TEST_F(RouterTest, ospfSendHelloPacketWithNeighborInfo) {
  int src = 1, send_gate_index = 0, arrival_gate_index = 0;
  router->neighbor_table[src] = Router::OspfNeighborInfo(arrival_gate_index, OspfState::INIT);

  router->ospfSendNeighbor(send_gate_index);
  auto msg = router->queueGate->messages.front();
  auto* pk = check_and_cast<OspfHelloPacket*>(msg);

  ASSERT_EQ(pk->getSrcAddr(), router->my_address);
  ASSERT_EQ(pk->getNeighborsArraySize(), 1);
  ASSERT_EQ(pk->getNeighbors(0), src);
}

TEST_F(RouterTest, ospfReceiveHelloPacketHandleImpossibleCase) {
  int src = 1;
  auto msg_from_other_node = new OspfHelloPacket;
  msg_from_other_node->setSrcAddr(src);

  int arrival_gate_index = 0;
  router->neighbor_table[src] = Router::OspfNeighborInfo(arrival_gate_index, OspfState::INIT);
  ASSERT_THROW(router->handleMessage(msg_from_other_node), cRuntimeError);
}

TEST_F(RouterTest, ospfReceiveHelloPacketFailedStateTransition) {
  int src = 1;
  auto msg_from_other_node = new OspfHelloPacket;
  msg_from_other_node->setSrcAddr(src);

  int arrival_gate_index = 0;
  router->neighbor_table[src] = Router::OspfNeighborInfo(arrival_gate_index, OspfState::DOWN);
  ASSERT_THROW(router->handleMessage(msg_from_other_node), cRuntimeError);
}

TEST_F(RouterTest, ospfReceiveHelloPacketAndEstablishInitState) {
  int src = 1;
  auto msg_from_other_node = new OspfHelloPacket;
  msg_from_other_node->setSrcAddr(src);

  mockMessageArrival(msg_from_other_node);

  router->handleMessage(msg_from_other_node);
  int arrival_gate_index = 0;
  ASSERT_EQ(router->neighbor_table[src].gate_index, arrival_gate_index);
  ASSERT_EQ(router->queueGate->messages.size(), 1);
}

TEST_F(RouterTest, ospfReceiveHelloPacketAndEstablishTwoWayState) {
  int src = 1;
  auto msg_from_other_node = new OspfHelloPacket;
  msg_from_other_node->setSrcAddr(src);
  msg_from_other_node->appendNeighbors(router->my_address);

  mockMessageArrival(msg_from_other_node);

  router->handleMessage(msg_from_other_node);
  int arrival_gate_index = 0;
  ASSERT_EQ(router->neighbor_table[src].gate_index, arrival_gate_index);
  ASSERT_EQ(router->queueGate->messages.size(), 1);
}

TEST_F(RouterTest, ospfReceiveHelloPacketAndTransitionFromInitToTwoWayState) {
  int src = 1;
  auto msg_from_other_node = new OspfHelloPacket;
  msg_from_other_node->setSrcAddr(src);
  msg_from_other_node->appendNeighbors(router->my_address);

  mockMessageArrival(msg_from_other_node);

  int arrival_gate_index = 0;
  router->neighbor_table[src] = Router::OspfNeighborInfo(arrival_gate_index, OspfState::INIT);
  router->handleMessage(msg_from_other_node);
  ASSERT_EQ(router->neighbor_table[src].gate_index, arrival_gate_index);
  ASSERT_EQ(router->queueGate->messages.size(), 0);
}

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
}  // namespace

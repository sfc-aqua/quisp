#include <gtest/gtest.h>

#include <test_utils/TestUtils.h>

#include "PointingSystem.h"
#include "modules/SharedResource/SharedResource.h"

using namespace quisp_test;
using namespace quisp_test::utils;
using namespace quisp::messages;
using namespace quisp::modules::SharedResource;
using OriginalPointingSystem = quisp::modules::Satellite::PointingSystem;

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

class PointingSystem : public OriginalPointingSystem {
 public:
  using OriginalPointingSystem::handleMessage;
  using OriginalPointingSystem::initialize;
  using OriginalPointingSystem::routing_table;
  explicit PointingSystem(MockNode* parent_qnode) : OriginalPointingSystem() {
    this->provider.setStrategy(std::make_unique<Strategy>(parent_qnode));
    this->setComponentType(new TestModuleType("test_pointing_system"));
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

class PointingSystemTest : public ::testing::Test {
 protected:
  void SetUp() {
    sim = prepareSimulation();
    node = new MockNode(10, 0, true);
    PointingSystem = new PointingSystem(node);
    sim->registerComponent(PointingSystem);
    sim->setContext(PointingSystem);
    PointingSystem->callInitialize();
  }
  void TearDown() {}

  /**
   * This function mimics the behavior of Omnet++ internals
   * that sets up the message arrival to PointingSystem module.
   * Call this function before PointingSystem->handleMessages
   * when you want to retrieve the info of the arrival gate.
   */
  void mockMessageArrival(cMessage* msg) {
    int queue_size = 1;
    int arrival_gate_index = 0;
    PointingSystem->addGateVector("fromQueue", cGate::Type::INPUT, queue_size);
    msg->setArrival(PointingSystem->getId(), PointingSystem->findGate("fromQueue", arrival_gate_index));
  }

  TestSimulation* sim;
  PointingSystem* PointingSystem;
  MockNode* node;
};

TEST_F(PointingSystemTest, handlePacketForUnknownAddr) {
  auto msg = new ConnectionSetupRequest;
  msg->setDestAddr(7);
  EXPECT_THROW({ PointingSystem->handleMessage(msg); }, cRuntimeError);
}

TEST_F(PointingSystemTest, handlePacketForOtherNode) {
  auto msg = new ConnectionSetupRequest;
  msg->setDestAddr(8);
  PointingSystem->handleMessage(msg);
  ASSERT_EQ(PointingSystem->queueGate->messages.size(), 1);
  {
    auto* msg = PointingSystem->queueGate->messages.at(0);
    auto req = dynamic_cast<ConnectionSetupRequest*>(msg);
    EXPECT_EQ(req->getHopCount(), 1);
  }
}

TEST_F(PointingSystemTest, handleConnSetupRequest) {
  auto msg = new ConnectionSetupRequest;
  msg->setDestAddr(10);
  PointingSystem->handleMessage(msg);
  ASSERT_EQ(PointingSystem->cmPort->messages.size(), 1);
}

TEST_F(PointingSystemTest, handleConnSetupResponse) {
  auto msg = new ConnectionSetupResponse;
  msg->setDestAddr(10);
  PointingSystem->handleMessage(msg);
  ASSERT_EQ(PointingSystem->cmPort->messages.size(), 1);
}

TEST_F(PointingSystemTest, handleBSMTimingNotification) {
  auto msg = new BSMTimingNotification;
  msg->setDestAddr(10);
  PointingSystem->handleMessage(msg);
  ASSERT_EQ(PointingSystem->rePort->messages.size(), 1);
}

TEST_F(PointingSystemTest, handleEPPSTimingNotifier) {
  auto msg = new EPPStimingNotifier;
  msg->setDestAddr(10);
  PointingSystem->handleMessage(msg);
  ASSERT_EQ(PointingSystem->rePort->messages.size(), 1);
}

TEST_F(PointingSystemTest, handleRejectConnectionSetupReq) {
  auto msg = new RejectConnectionSetupRequest;
  msg->setDestAddr(10);
  PointingSystem->handleMessage(msg);
  ASSERT_EQ(PointingSystem->cmPort->messages.size(), 1);
}

TEST_F(PointingSystemTest, handleInternalRuleSetForwarding) {
  auto msg = new InternalRuleSetForwarding;
  msg->setDestAddr(10);
  PointingSystem->handleMessage(msg);
  ASSERT_EQ(PointingSystem->rePort->messages.size(), 1);
}

TEST_F(PointingSystemTest, handleInternalRuleSetForwarding_Application) {
  auto msg = new InternalRuleSetForwarding_Application;
  msg->setDestAddr(10);
  PointingSystem->handleMessage(msg);
  ASSERT_EQ(PointingSystem->rePort->messages.size(), 1);
}

TEST_F(PointingSystemTest, handleSwappingResult) {
  auto msg = new SwappingResult;
  msg->setDestAddr(10);
  PointingSystem->handleMessage(msg);
  ASSERT_EQ(PointingSystem->rePort->messages.size(), 1);
}

TEST_F(PointingSystemTest, handleLinkTomographyAck) {
  auto msg = new LinkTomographyAck;
  msg->setDestAddr(10);
  PointingSystem->handleMessage(msg);
  ASSERT_EQ(PointingSystem->hmPort->messages.size(), 1);
}

TEST_F(PointingSystemTest, handleLinkTomographyRequest) {
  auto msg = new LinkTomographyRequest;
  msg->setDestAddr(10);
  PointingSystem->handleMessage(msg);
  ASSERT_EQ(PointingSystem->hmPort->messages.size(), 1);
}

TEST_F(PointingSystemTest, handleLinkTomographyRuleSet) {
  auto msg = new LinkTomographyRuleSet;
  msg->setDestAddr(10);
  PointingSystem->handleMessage(msg);
  ASSERT_EQ(PointingSystem->rePort->messages.size(), 1);
}

TEST_F(PointingSystemTest, handlePurificationResult) {
  auto msg = new PurificationResult;
  msg->setDestAddr(10);
  PointingSystem->handleMessage(msg);
  ASSERT_EQ(PointingSystem->rePort->messages.size(), 1);
}

TEST_F(PointingSystemTest, handleStopEmitting) {
  auto msg = new StopEmitting;
  msg->setDestAddr(10);
  PointingSystem->handleMessage(msg);
  ASSERT_EQ(PointingSystem->rePort->messages.size(), 1);
}

TEST_F(PointingSystemTest, handleOspfPacket) {
  auto msg = new OspfPacket;
  msg->setDestAddr(10);
  PointingSystem->handleMessage(msg);
  ASSERT_EQ(PointingSystem->rdPort->messages.size(), 1);

  auto elo = new OspfHelloPacket;
  elo->setDestAddr(10);
  PointingSystem->handleMessage(elo);
  ASSERT_EQ(PointingSystem->rdPort->messages.size(), 2);

  auto dbd = new OspfDbdPacket;
  dbd->setDestAddr(10);
  PointingSystem->handleMessage(dbd);
  ASSERT_EQ(PointingSystem->rdPort->messages.size(), 3);

  auto lsr = new OspfLsrPacket;
  lsr->setDestAddr(10);
  PointingSystem->handleMessage(lsr);
  ASSERT_EQ(PointingSystem->rdPort->messages.size(), 4);

  auto lsu = new OspfLsuPacket;
  lsu->setDestAddr(10);
  PointingSystem->handleMessage(lsu);
  ASSERT_EQ(PointingSystem->rdPort->messages.size(), 5);

  auto ack = new OspfLsAckPacket;
  ack->setDestAddr(10);
  PointingSystem->handleMessage(ack);
  ASSERT_EQ(PointingSystem->rdPort->messages.size(), 6);
}

TEST_F(PointingSystemTest, nonQNodeForwardOspfPacket) {
  auto msg = new OspfHelloPacket;
  msg->setSrcAddr(10);
  msg->setSendingGateIndex(0);
  msg->setDestAddr(-1);
  PointingSystem->setIsQnode(false);

  mockMessageArrival(msg);
  PointingSystem->handleMessage(msg);
  ASSERT_EQ(PointingSystem->queueGate->messages.size(), 1);
}

TEST_F(PointingSystemTest, sendOspfHelloPacketToQueue) {
  auto msg = new OspfHelloPacket;
  msg->setSrcAddr(10);
  msg->setSendingGateIndex(0);
  msg->setDestAddr(-1);

  PointingSystem->handleMessage(msg);
  ASSERT_EQ(PointingSystem->queueGate->messages.size(), 1);
}

TEST_F(PointingSystemTest, redirectOspfHelloPacketToRoutingDaemon) {
  auto msg = new OspfHelloPacket;
  msg->setSrcAddr(8);
  msg->setDestAddr(-1);

  PointingSystem->handleMessage(msg);
  ASSERT_EQ(PointingSystem->rdPort->messages.size(), 1);
}
}  // namespace

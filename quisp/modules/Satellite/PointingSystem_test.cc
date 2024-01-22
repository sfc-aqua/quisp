#include <gtest/gtest.h>

#include <test_utils/TestUtils.h>

#include "PointingSystem.h"
#include "modules/SharedResource/SharedResource.h"
#include "messages/visibility_messages_m.h"
#include "test_utils/MockFreeSpaceChannel.h"


using namespace quisp_test;
using namespace quisp_test::utils;
using namespace quisp::messages;
using namespace quisp::modules::SharedResource;
using OriginalPointingSystem = quisp::modules::Satellite::PointingSystem;
using quisp_test::FSChannel::MockFreeSpaceChannel;

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
  explicit PointingSystem(MockNode* parent_qnode) : OriginalPointingSystem() {
    this->provider.setStrategy(std::make_unique<Strategy>(parent_qnode));
    this->setComponentType(new TestModuleType("test_pointing_system"));
    recPort = new TestGate(this, "rec");
    ansPort = new TestGate(this, "ans");
  }

  TestGate* ansPort;
  TestGate* recPort;


  std::map<const char*, cGate*> ports{};
  TestGate* gate(const char* gatename, int index = -1) override {
    if (strcmp(gatename, "rec") == 0) return recPort;
    if (strcmp(gatename, "ans") == 0) return ansPort;
    error("port: %s not found", gatename);
    return nullptr;
  }
  bool parentModuleIsQNode() { return dynamic_cast<MockNode*>(provider.getNode())->is_qnode; }
  void setIsQnode(bool is_qnode) { dynamic_cast<MockNode*>(provider.getNode())->is_qnode = is_qnode; }
};

class PointingSystemTest : public ::testing::Test {
 protected:
  void SetUp() {
    sim = prepareSimulation();
    node = new MockNode(0, 0, false);
    pointing_system = new PointingSystem(node);
    channel = new MockFreeSpaceChannel("test_channel");
    stub = new Stub();

    sim->registerComponent(pointing_system);
    sim->setContext(pointing_system);

    sim->registerComponent(channel);
    sim->setContext(channel);

    sim->registerComponent(stub);
    sim->setContext(stub);

    outgate = node->addGate("test_out",cGate::OUTPUT);
    stub_gate = stub->addGate("stub_gate", cGate::INPUT);

    outgate->connectTo(stub_gate,channel);

    pointing_system->callInitialize();
    channel->callInitialize();
    stub->callInitialize();
  }
  void TearDown() {
    }

  /**
   * This function mimics the behavior of Omnet++ internals
   * that sets up the message arrival to PointingSystem module.
   * Call this function before PointingSystem->handleMessages
   * when you want to retrieve the info of the arrival gate.
   */
  void mockMessageArrival(cMessage* msg) {
    msg->setArrival(pointing_system->getId(), pointing_system->findGate("rec"));
  }

  TestSimulation* sim;
  PointingSystem* pointing_system;
  MockNode* node;
  MockFreeSpaceChannel* channel;
  Stub* stub;

  cGate* outgate;
  cGate* stub_gate;
};

TEST_F(PointingSystemTest, handleNonControlMessage) {
  auto msg = new cMessage;
  mockMessageArrival(msg);
  EXPECT_THROW({ pointing_system->handleMessage(msg); }, cRuntimeError);
  node->gate("test_out")->disconnect();
}

TEST_F(PointingSystemTest, handleVisRequest_VisibleChannel) {
  channel->setNext_check_time(simTime());

  auto vcr = new VisCheckRequest;
  vcr->setOut_gate("test_out");
  vcr->setIndex(-1);

  mockMessageArrival(vcr);
  pointing_system->handleMessage(vcr);
  ASSERT_EQ(pointing_system->gate("ans")->messages.size(), 1);
  {
    auto* msg = pointing_system->gate("ans")->messages.at(0);
    auto vco = dynamic_cast<VisCheckOutcome*>(msg);
    ASSERT_EQ(vco->getNext_check_time(), 0);
  }
}

TEST_F(PointingSystemTest, handleVisRequest_NonVisibleChannel) {
  channel->setNext_check_time(simTime()+1);

  auto vcr = new VisCheckRequest;
  vcr->setOut_gate("test_out");
  vcr->setIndex(-1);

  mockMessageArrival(vcr);
  pointing_system->handleMessage(vcr);
  ASSERT_EQ(pointing_system->gate("ans")->messages.size(), 1);
  {
    auto* msg = pointing_system->gate("ans")->messages.at(0);
    auto vco = dynamic_cast<VisCheckOutcome*>(msg);
    ASSERT_EQ(vco->getNext_check_time(), simTime().dbl()+1);
  }
}
}  // namespace

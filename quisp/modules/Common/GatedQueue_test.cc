#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include "GatedQueue.h"
#include "modules/SharedResource/SharedResource.h"
#include "messages/visibility_messages_m.h"
#include "test_utils/MockFreeSpaceChannel.h"


using namespace quisp_test;
using namespace quisp_test::utils;
using namespace quisp::messages;
using namespace quisp::modules::SharedResource;
using OriginalGatedQueue = quisp::modules::GatedQueue;
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

class GatedQueue : public OriginalGatedQueue {
 public:
  using OriginalGatedQueue::handleMessage;
  using OriginalGatedQueue::initialize;
  void addResultRecorders() override {};

  MockNode* parent;
  cModule* getParentModule() const override {return parent;};

  explicit GatedQueue(MockNode* parent_qnode) : OriginalGatedQueue() {
    this->provider.setStrategy(std::make_unique<Strategy>(parent_qnode));
    this->setComponentType(new TestModuleType("test_gated_queue"));
    parent = parent_qnode;
    auto *sim = getTestSimulation();
    sim->registerComponent(this);
    inPort = new TestGate(this, "in");
    outPort = new TestGate(this, "out");
    line_inPort = new TestGate(this, "line_in");
    line_outPort = new TestGate(this, "line_out");
    from_psPort = new TestGate(this, "from_ps");
    to_psPort = new TestGate (this, "to_ps");
  }

  TestGate* inPort;
  TestGate* outPort;
  TestGate* line_inPort;
  TestGate* line_outPort;
  TestGate* from_psPort;
  TestGate* to_psPort;

  std::map<const char*, cGate*> ports{};
  TestGate* gate(const char* gatename, int index = -1) override {
    if (strcmp(gatename, "in") == 0) return inPort;
    if (strcmp(gatename, "out") == 0) return outPort;
    if (strcmp(gatename, "line_in") == 0) return line_inPort;
    if (strcmp(gatename, "line_out") == 0) return line_outPort;
    if (strcmp(gatename, "from_ps") == 0) return from_psPort;
    if (strcmp(gatename, "to_ps") == 0) return to_psPort;
    error("port: %s not found", gatename);
    return nullptr;
  }
  bool parentModuleIsQNode() { return dynamic_cast<MockNode*>(provider.getNode())->is_qnode; }
  void setIsQnode(bool is_qnode) { dynamic_cast<MockNode*>(provider.getNode())->is_qnode = is_qnode; }


};

class GatedQueueTest : public ::testing::Test {
 protected:
  void SetUp() {
    node = new TestQNode("node");
    gated_queue = new GatedQueue(node);

    out_to_router = node->addGate("out_to_router", cGate::OUTPUT);

    gated_queue->callInitialize();


  }
  void TearDown() {
    }


  TestSimulation* sim;
  GatedQueue* gated_queue;
  MockNode* node;
  cGate* out_to_router;
  cGate* out_to_outside;

};

TEST_F(GatedQueueTest, handleNonVisMessage) {
  omnetpp::cMessage* msg = new cMessage;
  msg->setArrival(gated_queue->getId(), gated_queue->findGate("rec"),arrival_time);
  EXPECT_THROW({ gated_queue->handleMessage(msg); }, cRuntimeError);
}

TEST_F(GatedQueueTest, handleVisRequest_VisibleChannel) {
  chl->setNext_check_time(simTime());

  auto vcr = new VisCheckRequest;
  vcr->setOut_gate("test_out");
  vcr->setIndex(-1);

  mockMessageArrival(vcr);
  gated_queue->handleMessage(vcr);
  ASSERT_EQ(gated_queue->gate("ans")->messages.size(), 1);
  {
    auto* msg = gated_queue->gate("ans")->messages.at(0);
    auto vco = dynamic_cast<VisCheckOutcome*>(msg);
    ASSERT_EQ(vco->getNext_check_time(), 0);
  }
}

// TEST_F(GatedQueueTest, handleVisRequest_NonVisibleChannel) {
//   chl->setNext_check_time(simTime()+1);

//   auto vcr = new VisCheckRequest;
//   vcr->setOut_gate("test_out");
//   vcr->setIndex(-1);

//   mockMessageArrival(vcr);
//   gated_queue->handleMessage(vcr);
//   ASSERT_EQ(gated_queue->gate("ans")->messages.size(), 1);
//   {
//     auto* msg = gated_queue->gate("ans")->messages.at(0);
//     auto vco = dynamic_cast<VisCheckOutcome*>(msg);
//     ASSERT_EQ(vco->getNext_check_time(), simTime().dbl()+1);
//   }
// }

// TEST_F(GatedQueueTest, handleVisRequest_NonFSChannel) {
//   outgate->disconnect();
//   outgate->connectTo(stub_gate);

//   auto vcr = new VisCheckRequest;
//   vcr->setOut_gate("test_out");
//   vcr->setIndex(-1);

//   mockMessageArrival(vcr);
//   gated_queue->handleMessage(vcr);
//   ASSERT_EQ(gated_queue->gate("ans")->messages.size(), 1);
//   {
//     auto* msg = gated_queue->gate("ans")->messages.at(0);
//     auto vco = dynamic_cast<VisCheckOutcome*>(msg);
//     ASSERT_EQ(vco->getNext_check_time(), 0);
//   }
// }

}  // namespace


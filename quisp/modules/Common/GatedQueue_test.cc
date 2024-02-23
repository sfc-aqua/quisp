#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include "GatedQueue.h"
#include "modules/SharedResource/SharedResource.h"
#include "messages/visibility_messages_m.h"
#include "test_utils/MockFreeSpaceChannel.h"
#include "test_utils/Stub.h"
#include "test_utils/TestUtilFunctions.h"


using namespace quisp_test;
using namespace quisp_test::utils;
using namespace quisp::messages;
using namespace quisp::modules::SharedResource;
using quisp_test::FSChannel::MockFreeSpaceChannel;
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
  virtual void take(omnetpp::cOwnedObject *obj) override {OriginalGatedQueue::take(obj);};
  virtual void send(omnetpp::cMessage *msg, const char *gatename, int gateindex=-1) override {take(msg); OriginalGatedQueue::send(msg,gatename,gateindex);};
  virtual void scheduleAt(omnetpp::simtime_t t, omnetpp::cMessage* msg) override {take(msg); OriginalGatedQueue::scheduleAt(t,msg);};
  MockNode* parent;

  explicit GatedQueue(MockNode* parent_qnode) : OriginalGatedQueue() {
    this->provider.setStrategy(std::make_unique<Strategy>(parent_qnode));
    this->setComponentType(new TestModuleType("test_gated_queue"));
    setParBool(this,"useCutThroughSwitching",false);
    setParInt(this,"frame_capacity",0);
    parent = parent_qnode;
    auto *sim = getTestSimulation();
    sim->registerComponent(this);
    inPort = new TestGate(this, "in");
    outPort = new TestGate(this, "out");
    line_inPort = new TestGate(this, "line$i");
    line_outPort = new TestGate(this, "line$o");
    from_psPort = new TestGate(this, "from_ps");
    to_psPort = new TestGate (this, "to_ps");

    this->addGate("in",cGate::INPUT);
    this->addGate("out",cGate::OUTPUT);
    this->addGate("line",cGate::INOUT);
    this->addGate("from_ps",cGate::INPUT);
    this->addGate("to_ps",cGate::OUTPUT);
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
    if (strcmp(gatename, "line$i") == 0) return line_inPort;
    if (strcmp(gatename, "line$o") == 0) return line_outPort;
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
    sim = prepareSimulation();
    node = new MockNode(0,0,false);
    gated_queue = new GatedQueue(node);

    chl = new MockFreeSpaceChannel("test_channel");
    quisp_test::utils::setParDouble(chl,"delay",1);

    stub = new Stub();

    outgate = node->addGate("test_out",cGate::OUTPUT);
    stub_gate = stub->addGate("stub_gate", cGate::INPUT);

    outgate->connectTo(stub_gate,chl,true);
    chl->finalizeParameters(); // THIS METHOD MAY ONLY BE CALLED WHEN THE CHANNEL IS CONNECTED

    gated_queue->callInitialize();
    chl->callInitialize();
    stub->callInitialize();

    gated_queue->gate("line$o")->quiet_connectTo(outgate);

    //out_to_router = node->addGate("out_to_router", cGate::OUTPUT);

  }
  void TearDown() {
    }


  TestSimulation* sim;
  GatedQueue* gated_queue;
  MockNode* node;
  MockFreeSpaceChannel* chl;
  Stub* stub;

  cGate* outgate;
  cGate* stub_gate;
  //TestGate* node_out;
};

TEST_F(GatedQueueTest, handleNonVisMessage) {
  auto msg = new cMessage;
  msg->setArrival(gated_queue->getId(), gated_queue->findGate("from_ps"),simTime());
  EXPECT_THROW({ gated_queue->handleMessage(msg); }, cRuntimeError);
}

TEST_F(GatedQueueTest, handleIncomingMessage) {
  omnetpp::cPacket* pkt = new cPacket("TestPacket");
  gated_queue->take(pkt);
  pkt->setArrival(gated_queue->getId(), gated_queue->findGate("line$i"),simTime());
  gated_queue->handleMessage(pkt);
  ASSERT_EQ(gated_queue->gate("to_ps")->messages.size(),0); // Must not request Vis info
  ASSERT_EQ(*gated_queue->gate("out")->messages.front()->getName(),*pkt->getName()); // Must let message from outside pass always
}

TEST_F(GatedQueueTest, handleOutgoingMessage_Visible) {
  omnetpp::cPacket* pkt = new cPacket("TestPacket");
  //gated_queue->take(pkt);
  pkt->setArrival(gated_queue->getId(), gated_queue->findGate("in"),simTime());
  gated_queue->handleMessage(pkt);
  ASSERT_EQ(gated_queue->gate("to_ps")->messages.size(),1); // Must request Vis info
  ASSERT_EQ(gated_queue->gate("line$o")->messages.size(),0); // Must not send message yet
  VisCheckOutcome* vco = new VisCheckOutcome();
  vco->setNext_check_time(0);
  vco->setArrival(gated_queue->getId(), gated_queue->findGate("from_ps"),simTime());
  gated_queue->handleMessage(vco);
  ASSERT_EQ(*gated_queue->gate("line$o")->messages.front()->getName(),*pkt->getName()); // If receiver is visible, we can send the message.
}

TEST_F(GatedQueueTest, handleOutgoingMessage_NonVisible) {
  omnetpp::cPacket* pkt = new cPacket("TestPacket");
  gated_queue->take(pkt);
  pkt->setArrival(gated_queue->getId(), gated_queue->findGate("in"),simTime());
  gated_queue->handleMessage(pkt);
  ASSERT_EQ(gated_queue->gate("to_ps")->messages.size(),1); // Must request Vis info
  ASSERT_EQ(gated_queue->gate("line$o")->messages.size(),0); // Must not send message yet
  VisCheckOutcome* vco = new VisCheckOutcome();
  vco->setNext_check_time(1);
  vco->setArrival(gated_queue->getId(), gated_queue->findGate("from_ps"),simTime());
  gated_queue->handleMessage(vco);
  ASSERT_EQ(gated_queue->gate("line$o")->messages.size(),0); // Must not send message yet
  sim->executeNextEvent(); // resend vcr
  ASSERT_EQ(simTime().dbl(),1);

  ASSERT_EQ(gated_queue->gate("to_ps")->messages.size(),2); // Must request Vis info
  ASSERT_EQ(gated_queue->gate("line$o")->messages.size(),0); // Must not send message yet
  VisCheckOutcome* second_vco = new VisCheckOutcome();
  second_vco->setNext_check_time(0);
  second_vco->setArrival(gated_queue->getId(), gated_queue->findGate("from_ps"),simTime());
  gated_queue->handleMessage(second_vco);
  ASSERT_EQ(gated_queue->gate("line$o")->messages.size(),1); // Finally send the message
  }
}

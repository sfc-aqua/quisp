#include "RoutingDaemon.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include <test_utils/TestUtils.h>
#include <utils/IComponentProviderStrategy.h>
#include "gmock/gmock-function-mocker.h"
#include "modules/QNIC.h"
#include "modules/QNIC/StationaryQubit/StationaryQubit.h"
#include "omnetpp/cchannel.h"
#include "omnetpp/ccomponenttype.h"
#include "omnetpp/cexception.h"
#include "omnetpp/cgate.h"
#include "omnetpp/csimulation.h"
#include "omnetpp/ctopology.h"

namespace {

using namespace omnetpp;
using namespace quisp::utils;
using namespace quisp::modules;
using namespace quisp_test;
using namespace testing;

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy(TestQNode *_qnode) : parent_qnode(_qnode) {}
  cModule *getQNode() override { return parent_qnode; }

 private:
  TestQNode *parent_qnode;
};

// class MockOmnetPrimitive : public cModule {
//  public:
//   cModule *parent;
//   cModule *getParentModule() const override {
//     return parent;
//   };
//   MockOmnetPrimitive() {}
//   MockOmnetPrimitive(MockOmnetPrimitive* _parent) { parent = _parent; }
// };

class MockChannel {
public:
  MOCK_METHOD(double, par, (const char *parname), ());
};

class MockGate {
public:
  MOCK_METHOD(MockChannel*, getChannel, (), ());
};

class MockLink {
public:
  MOCK_METHOD(MockGate*, getLocalGate, (), ());
};

class MockNode : public cTopology::Node {
public:
  MOCK_METHOD(MockLink*, getLinkOut, (int i), ());
};

class MockQNode : public TestQNode {
 public:
  MockQNode(int addr, int mass, bool is_initiator) : TestQNode(addr, mass, is_initiator) {
    this->addGate("in", cGate::Type::INPUT);
    this->addGate("out", cGate::Type::OUTPUT);
  }
  MockNode* node;
  MOCK_METHOD(cModule*, getParentModule, (), (const, override));
  // MOCK_METHOD(cTopology::Node*, getNode, (), ());
};

class RoutingDaemonTestTarget : public quisp::modules::RoutingDaemon {
 public:
  // using quisp::modules::RoutingDaemon::getParentModule;
  using quisp::modules::RoutingDaemon::initialize;
  using quisp::modules::RoutingDaemon::par;
  
  cModule *parent;
  // MOCK_METHOD(cModule*, getParentModule, (), (const override));
  cModule *getParentModule() const override {
    return parent;
  };
  RoutingDaemonTestTarget(TestQNode* parent_qnode, int address) : RoutingDaemon() {
    // this->setName("rd_test_target");
    setParInt(this, "address", address);
    this->provider.setStrategy(std::make_unique<Strategy>(parent_qnode));
    parent = provider.getQNode();
  }
};

TEST(RoutingDaemonTest, InitTestNoTopology) {
  auto sim = prepareSimulation();
  auto *mock_qnode1 = new MockQNode{123, 100, false};
  RoutingDaemonTestTarget c1{mock_qnode1, 123};
  sim->registerComponent(&c1);

  cTopology *topo = new cTopology("topo");
  topo->extractByParameter("included_in_topology", "\"yes\"");
  ASSERT_EQ(topo->getNumNodes(), 0);

  int stage = 1;
  c1.initialize(stage);
  ASSERT_EQ(c1.par("address").intValue(), 123);
}

TEST(RoutingDaemonTest, InitTopologyTest) {
  auto sim = prepareSimulation();
  auto *mock_qnode1 = new MockQNode{123, 100, false};
  auto *mock_qnode2 = new MockQNode{456, 100, false};
  RoutingDaemonTestTarget c1{mock_qnode1, 123};
  sim->registerComponent(&c1);
  RoutingDaemonTestTarget c2{mock_qnode2, 456};
  // auto channel = new cIdealChannel;
  // channel->setDelay(10);
  // channel->setDatarate(10);
  mock_qnode1->gate("out")->connectTo(mock_qnode2->gate("in"));
  mock_qnode2->gate("out")->connectTo(mock_qnode1->gate("in"));
  MockLink* mlink = new MockLink;
  MockGate* mgate = new MockGate;
  MockChannel* mchannel = new MockChannel;

  cTopology *topo = new cTopology("topo");
  topo->extractByParameter("included_in_topology", "\"yes\"");
  mock_qnode1->node = (MockNode*)topo->getNode(0);

  printf("gmock: %p\n", mock_qnode1->node);
  printf("real: %p\n", topo->getNode(0));

  // EXPECT_CALL(c1, getParentModule()).WillRepeatedly(Return(c1.provider.getQNode()));
  EXPECT_CALL(*mock_qnode1, getParentModule()).WillRepeatedly(Return(mock_qnode1));
  EXPECT_CALL(*mock_qnode1->node, getLinkOut(0)).WillRepeatedly(Return(mlink));
  EXPECT_CALL(*mlink, getLocalGate()).WillRepeatedly(Return(mgate));
  // printf("mlink: %p\n", mock_qnode1->node->getLinkOut(0));
  EXPECT_CALL(*mgate, getChannel()).WillRepeatedly(Return(mchannel));
  EXPECT_CALL(*mchannel, par("speed_of_light_in_fiber")).WillRepeatedly(Return(10));
  EXPECT_CALL(*mchannel, par("distance")).WillRepeatedly(Return(10));
  // channel->connect(mock_qnode1->gate("out"), mock_qnode2->gate("in"));
  int stage = 1;
  c1.initialize(stage);
  ASSERT_EQ(c1.par("address").intValue(), 123);
  
  ASSERT_NE(topo->getNumNodes(), 0);
}
}  // namespace

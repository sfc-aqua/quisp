#include "RoutingDaemon.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>

#include <modules/QNIC.h>
#include <modules/QNIC/StationaryQubit/StationaryQubit.h>
#include <test_utils/TestUtils.h>
#include <utils/IComponentProviderStrategy.h>
#include "omnetpp/ctopology.h"

namespace {

using namespace omnetpp;
using namespace quisp::utils;
using namespace quisp::modules;
using namespace quisp_test;
using quisp_test::simulation::TestSimulation;
using namespace testing;
using OriginalRoutingDaemon = quisp::modules::RoutingDaemon;

class MockTopologyLink : public cTopology::Link {
 public:
  using cTopology::Link::destGateId;
  using cTopology::Link::destNode;
  using cTopology::Link::srcGateId;
  using cTopology::Link::srcNode;
  MockTopologyLink() {}
  MockTopologyLink(cTopology::Node *src_node, cTopology::Node *dest_node) {
    srcNode = src_node;
    srcGateId = 0;
    destGateId = 0;
    destNode = dest_node;
  }
};

class MockTopologyNode : public cTopology::Node {
 public:
  using cTopology::Node::moduleId;

  MockTopologyNode(cModule *module) : cTopology::Node(module->getId()) {}
};

class MockTopology : public cTopology {
 public:
  MockTopology() {}
};

class Strategy : public TestComponentProviderStrategy {
 public:
  Strategy(cModule *qnode) : qnode(qnode) {}
  cModule *qnode;
  cModule *getQNode() override { return qnode; };
};

class RoutingDaemon : public OriginalRoutingDaemon {
 public:
  using OriginalRoutingDaemon::generateRoutingTable;
  using OriginalRoutingDaemon::provider;
  RoutingDaemon() {}
  void setParentQNode(cModule *mod) { provider.setStrategy(std::make_unique<Strategy>(mod)); }
};

class RoutingDaemonTest : public testing::Test {
 protected:
  void SetUp() {
    sim = prepareSimulation();
    rd = new RoutingDaemon{};
    sim->registerComponent(rd);
  }

  TestSimulation *sim;
  RoutingDaemon *rd;
};

TEST_F(RoutingDaemonTest, threeNodes) {
  auto *qnode1 = new TestQNode{1, 0, false};
  auto *qnode2 = new TestQNode{2, 0, false};
  auto *qnode3 = new TestQNode{3, 0, false};
  qnode1->addGate("qnode1-gate-out", cGate::Type::OUTPUT);
  qnode1->addGate("qnode1-gate-in", cGate::Type::INPUT);
  qnode2->addGate("qnode2-gate-out", cGate::Type::OUTPUT);
  qnode2->addGate("qnode2-gate-in", cGate::Type::INPUT);
  qnode3->addGate("qnode3-gate-out", cGate::Type::OUTPUT);
  qnode3->addGate("qnode3-gate-in", cGate::Type::INPUT);
  qnode1->gate("qnode1-gate-out")->connectTo(qnode2->gate("qnode2-gate-in"));
  qnode2->gate("qnode2-gate-out")->connectTo(qnode3->gate("qnode3-gate-in"));
  qnode3->gate("qnode3-gate-out")->connectTo(qnode1->gate("qnode1-gate-in"));
  rd->setParentQNode(qnode1);

  // setup cTopology instance to fake the next line
  // topo->extractByParameter("included_in_topology", "\"yes\"");
  auto *mock_node1 = new MockTopologyNode{qnode1};
  auto *mock_node2 = new MockTopologyNode{qnode2};
  auto *mock_node3 = new MockTopologyNode{qnode3};
  auto *topo = new MockTopology{};
  topo->addNode(mock_node1);
  topo->addNode(mock_node2);
  topo->addNode(mock_node3);
  topo->addLink(new MockTopologyLink, qnode1->gate("qnode1-gate-out"), qnode2->gate("qnode2-gate-in"));
  topo->addLink(new MockTopologyLink, qnode2->gate("qnode2-gate-out"), qnode3->gate("qnode3-gate-in"));
  topo->addLink(new MockTopologyLink, qnode3->gate("qnode3-gate-out"), qnode1->gate("qnode1-gate-in"));

  ASSERT_EQ(topo->getNumNodes(), 3);

  auto *node = topo->getNodeFor(qnode1);
  ASSERT_NE(node, nullptr);
  ASSERT_EQ(node->getNumPaths(), 0);

  rd->generateRoutingTable(topo);
}

}  // namespace

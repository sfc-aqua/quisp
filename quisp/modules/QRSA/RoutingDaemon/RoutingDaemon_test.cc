#include "RoutingDaemon.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>

#include <modules/QNIC.h>
#include <modules/QNIC/StationaryQubit/StationaryQubit.h>
#include <test_utils/TestUtils.h>
#include <utils/IComponentProviderStrategy.h>

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

TEST_F(RoutingDaemonTest, updateChannelWeights) {
  auto *topo = new MockTopology{};
  topo->extractByParameter("included_in_topology", "\"yes\"");
  ASSERT_EQ(topo->getNumNodes(), 0);
}

TEST_F(RoutingDaemonTest, oneNode) {
  auto *qnode1 = new TestQNode{1, 0, false};
  auto *qnode2 = new TestQNode{2, 0, false};
  auto *qnode3 = new TestQNode{3, 0, false};
  rd->setParentQNode(qnode1);
  auto *mock_node1 = new MockTopologyNode{qnode1};
  auto *mock_node2 = new MockTopologyNode{qnode2};
  auto *mock_node3 = new MockTopologyNode{qnode3};
  auto *topo = new MockTopology{};
  topo->addNode(mock_node1);
  topo->addNode(mock_node2);
  topo->addNode(mock_node3);
  auto *link_12 = new MockTopologyLink{};
  topo->addLink(link_12, mock_node1, mock_node2);
  // topo->extractByParameter("included_in_topology", "\"yes\"");
  ASSERT_EQ(topo->getNumNodes(), 3);

  auto *node = topo->getNodeFor(qnode1);
  ASSERT_NE(node, nullptr);
  ASSERT_EQ(node->getNumPaths(), 0);

  rd->generateRoutingTable(topo);
}

}  // namespace

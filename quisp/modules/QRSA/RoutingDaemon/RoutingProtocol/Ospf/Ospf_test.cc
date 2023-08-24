#include <gtest/gtest.h>

#include "gmock/gmock-function-mocker.h"
#include "gmock/gmock-matchers.h"
#include "gmock/gmock-spec-builders.h"

#include "Ospf.h"

using namespace quisp::modules::ospf;

namespace {

class TestLinkStateDatabase : public LinkStateDatabase {
 public:
  using LinkStateDatabase::link_state_database;
  using LinkStateDatabase::lsdb_summary;
  using LinkStateDatabase::PriorityQueue;
  using LinkStateDatabase::Vertex;
  using LinkStateDatabase::VertexMap;

  using LinkStateDatabase::dijkstraAlgorithm;
};

class LinkStateDatabaseTest : public ::testing::Test {
 protected:
  using Vertex = TestLinkStateDatabase::Vertex;
  using VertexMap = TestLinkStateDatabase::VertexMap;
  using PriorityQueue = TestLinkStateDatabase::PriorityQueue;

  void SetUp() {
    std::map<NodeAddr, std::map<NodeAddr, double>> graph = createGraph();
    buildTopology(graph);
  }
  void TearDown() {}

  std::map<NodeAddr, std::map<NodeAddr, double>> createGraph() {
    std::map<NodeAddr, std::map<NodeAddr, double>> graph;
    graph[1][2] = 3.5;
    graph[1][3] = 1.2;
    graph[2][3] = 0.8;
    graph[2][4] = 2.1;
    graph[3][4] = 1.0;

    graph[2][1] = 3.5;
    graph[3][1] = 1.2;
    graph[3][2] = 0.8;
    graph[4][2] = 2.1;
    graph[4][3] = 1.0;
    return graph;
  }

  void buildTopology(const std::map<NodeAddr, std::map<NodeAddr, double>>& graph) {
    for (const auto& source_node : graph) {
      int source = source_node.first;
      const auto& connections = source_node.second;

      NeighborTable neighbor_table;
      for (const auto& target_node : connections) {
        int target = target_node.first;
        double cost = target_node.second;
        neighbor_table[target] = OspfNeighborInfo(target, target, cost);
      }
      link_state_database.link_state_database[source] = LinkStateAdvertisement(source, source, neighbor_table);
    }
    for (const auto& lsa_entry : link_state_database.link_state_database) {
      const LinkStateAdvertisement& lsa = lsa_entry.second;
      link_state_database.lsdb_summary.emplace_back(lsa.lsa_id, lsa.lsa_origin_id, lsa.lsa_age);
    }
  }
  TestLinkStateDatabase link_state_database;
};

class MockLinkStateDatabase : public LinkStateDatabase {
 public:
  using LinkStateDatabase::link_state_database;

  MOCK_METHOD(bool, needsFullLinkStateAdvertisementOf, (const SummaryLinkStateAdvertisement& summary_lsa), (const, override));
  MOCK_METHOD(LinkStateAdvertisement, getLinkStateAdvertisementOf, (NodeAddr router), (const, override));
  MOCK_METHOD(const VertexMap, dijkstraAlgorithm, (NodeAddr source_id), (const, override));
};

TEST_F(LinkStateDatabaseTest, addUnseenLsaToLinkStateDatabase) {
  auto lsa5 = LinkStateAdvertisement(5, 5, {});
  link_state_database.updateLinkStateDatabase(lsa5);
  ASSERT_TRUE(link_state_database.link_state_database.count(5));
  ASSERT_EQ(link_state_database.lsdb_summary.size(), 0);
}

TEST_F(LinkStateDatabaseTest, addNewerVersionLsaToLinkStateDatabase) {
  int lsa_age = 1;
  auto node4_neighbors = link_state_database.link_state_database.at(4).neighbor_nodes;
  node4_neighbors[5] = {};
  auto lsa4 = LinkStateAdvertisement(4, 4, lsa_age, node4_neighbors);
  link_state_database.updateLinkStateDatabase(lsa4);
  ASSERT_TRUE(link_state_database.link_state_database.count(4));
  ASSERT_EQ(link_state_database.link_state_database.at(4).lsa_age, lsa_age);
  ASSERT_EQ(link_state_database.lsdb_summary.size(), 0);
}

TEST_F(LinkStateDatabaseTest, NewerLsaNotSupposedToHaveLessNeighborNodes) {
  int lsa_age = 1;
  auto lsa4 = LinkStateAdvertisement(4, 4, lsa_age, {});
  ASSERT_ANY_THROW(link_state_database.updateLinkStateDatabase(lsa4));
  ASSERT_EQ(link_state_database.lsdb_summary.size(), 4);
}

TEST_F(LinkStateDatabaseTest, outdatedLsaNotAddedToLinkStateDatabase) {
  int lsa_age = 0;
  auto lsa4 = LinkStateAdvertisement(4, 4, lsa_age, {});
  ASSERT_ANY_THROW(link_state_database.updateLinkStateDatabase(lsa4));
  ASSERT_EQ(link_state_database.lsdb_summary.size(), 4);
}

TEST_F(LinkStateDatabaseTest, getCachedLinkStateDatabaseSummary) { ASSERT_EQ(link_state_database.getLinkStateDatabaseSummary().size(), 4); }

TEST_F(LinkStateDatabaseTest, generateAndGetLinkStateDatabaseSummary) {
  link_state_database.lsdb_summary.clear();
  ASSERT_EQ(link_state_database.getLinkStateDatabaseSummary().size(), 4);
}

TEST_F(LinkStateDatabaseTest, noLinkStateDatabaseSummaryForEmptyLinkStateDatabase) {
  link_state_database.link_state_database.clear();
  link_state_database.lsdb_summary.clear();
  ASSERT_EQ(link_state_database.getLinkStateDatabaseSummary().size(), 0);
}

TEST_F(LinkStateDatabaseTest, generateRoutingTableFromGraph) {
  MockLinkStateDatabase mock_link_state_database;
  const int source = 1;
  VertexMap expected_vertices;
  for (const auto& lsa : link_state_database.link_state_database) {
    expected_vertices[lsa.first] = std::shared_ptr<Vertex>(new Vertex(lsa.second));
  }
  expected_vertices.at(2)->prev_node_in_path = 3;
  expected_vertices.at(3)->prev_node_in_path = source;
  expected_vertices.at(4)->prev_node_in_path = 3;
  mock_link_state_database.link_state_database = std::move(link_state_database.link_state_database);
  EXPECT_CALL(mock_link_state_database, dijkstraAlgorithm(source)).WillOnce(testing::Return(expected_vertices));
  auto routing_table = mock_link_state_database.generateRoutingTableFromGraph(source);
  ASSERT_EQ(routing_table.at(2), 3);
  ASSERT_EQ(routing_table.at(3), 3);
  ASSERT_EQ(routing_table.at(4), 3);
}

TEST_F(LinkStateDatabaseTest, generatedPathInconsistentWithLinkStateDatabase) {
  MockLinkStateDatabase mock_link_state_database;
  const int source = 1;
  VertexMap expected_vertices;
  for (const auto& lsa : link_state_database.link_state_database) {
    expected_vertices[lsa.first] = std::shared_ptr<Vertex>(new Vertex(lsa.second));
  }
  expected_vertices.at(2)->prev_node_in_path = -1;
  EXPECT_CALL(mock_link_state_database, dijkstraAlgorithm(source)).WillOnce(testing::Return(expected_vertices));
  ASSERT_ANY_THROW(mock_link_state_database.generateRoutingTableFromGraph(source));
}

TEST_F(LinkStateDatabaseTest, dijkstraAlgorithmWorks) {
  PriorityQueue queue;
  auto v1 = std::shared_ptr<Vertex>(new Vertex);
  v1->node_id = 1;
  v1->distance_from_source = 5;
  queue.emplace(v1);
  auto v2 = std::shared_ptr<Vertex>(new Vertex);
  v2->node_id = 2;
  v2->distance_from_source = 3;
  queue.emplace(v2);
  ASSERT_EQ(queue.top()->node_id, v2->node_id);
  auto v3 = std::shared_ptr<Vertex>(new Vertex);
  v3->node_id = 3;
  v3->distance_from_source = 4;
  queue.emplace(v3);
  ASSERT_EQ(queue.top()->node_id, v2->node_id);

  auto vertices = link_state_database.dijkstraAlgorithm(1);
  ASSERT_EQ(vertices[1]->distance_from_source, 0);
  ASSERT_EQ(vertices[2]->distance_from_source, 2.0);
  ASSERT_EQ(vertices[3]->distance_from_source, 1.2);
  ASSERT_EQ(vertices[4]->distance_from_source, 2.2);
}

TEST_F(LinkStateDatabaseTest, dijkstraAlgorithmNoSourceVertex) { ASSERT_ANY_THROW(link_state_database.dijkstraAlgorithm(5)); }

TEST_F(LinkStateDatabaseTest, identifyNoMissingLinkStateAdvertisementId) {
  MockLinkStateDatabase mock_link_state_database;
  LinkStateDatabaseSummary lsdb_summary;
  for (const auto& lsa_entry : link_state_database.link_state_database) {
    const LinkStateAdvertisement& lsa = lsa_entry.second;
    lsdb_summary.emplace_back(lsa.lsa_id, lsa.lsa_origin_id, lsa.lsa_age);
  }
  EXPECT_CALL(mock_link_state_database, needsFullLinkStateAdvertisementOf).WillRepeatedly(testing::Return(false));

  RouterIds missing_lsas = mock_link_state_database.identifyMissingLinkStateAdvertisementId(lsdb_summary);
  ASSERT_EQ(missing_lsas.size(), 0);
}

TEST_F(LinkStateDatabaseTest, identify2UnseenLinkStateAdvertisementId) {
  MockLinkStateDatabase mock_link_state_database;
  LinkStateDatabaseSummary lsdb_summary;
  lsdb_summary.emplace_back(5, 5, 0);
  lsdb_summary.emplace_back(5, 6, 0);

  EXPECT_CALL(mock_link_state_database, needsFullLinkStateAdvertisementOf).WillRepeatedly(testing::Return(true));

  RouterIds missing_lsas = link_state_database.identifyMissingLinkStateAdvertisementId(lsdb_summary);
  ASSERT_EQ(missing_lsas.size(), 2);
}

TEST_F(LinkStateDatabaseTest, doesNotNeedsFullLinkStateAdvertisementOfLsa) {
  for (const auto& lsa_entry : link_state_database.link_state_database) {
    const LinkStateAdvertisement& lsa = lsa_entry.second;
    SummaryLinkStateAdvertisement summary_lsa{lsa.lsa_id, lsa.lsa_origin_id, lsa.lsa_age};
    ASSERT_FALSE(link_state_database.needsFullLinkStateAdvertisementOf(summary_lsa));
  }
}

TEST_F(LinkStateDatabaseTest, needsFullLinkStateAdvertisementOfUpdatedLsa) {
  for (const auto& lsa_entry : link_state_database.link_state_database) {
    const LinkStateAdvertisement& lsa = lsa_entry.second;
    SummaryLinkStateAdvertisement summary_lsa{lsa.lsa_id, lsa.lsa_origin_id, lsa.lsa_age + 1};
    ASSERT_TRUE(link_state_database.needsFullLinkStateAdvertisementOf(summary_lsa));
  }
}

TEST_F(LinkStateDatabaseTest, needsFullLinkStateAdvertisementOfUnseenLsa) {
  SummaryLinkStateAdvertisement summary_lsa{5, 5, 0};
  ASSERT_TRUE(link_state_database.needsFullLinkStateAdvertisementOf(summary_lsa));
}

TEST_F(LinkStateDatabaseTest, getLinkStateUpdatesForRouter1To3) {
  int my_address = 1;
  RouterIds requests{1, 2, 3};
  MockLinkStateDatabase mock_link_state_database;

  EXPECT_CALL(mock_link_state_database, getLinkStateAdvertisementOf(testing::_)).WillRepeatedly([&](NodeAddr router) {
    return link_state_database.link_state_database.at(router);
  });

  LinkStateUpdate lsu = mock_link_state_database.getLinkStateUpdatesFor(requests, my_address);
  ASSERT_EQ(lsu.size(), requests.size());
  for (int i = 0; i < requests.size(); i++) {
    ASSERT_EQ(lsu[i].lsa_id, my_address);
    ASSERT_EQ(lsu[i].lsa_origin_id, requests[i]);
    ASSERT_EQ(lsu[i].lsa_age, 0);
    ASSERT_GT(lsu[i].neighbor_nodes.size(), 0);
  }
}

TEST_F(LinkStateDatabaseTest, getLinkStateAdvertisementInDatabase) {
  NodeAddr request = 1;
  auto return_value = link_state_database.getLinkStateAdvertisementOf(request);
  auto real_lsa = link_state_database.link_state_database.at(request);
  ASSERT_EQ(return_value.lsa_origin_id, real_lsa.lsa_origin_id);
  ASSERT_EQ(return_value.neighbor_nodes.size(), real_lsa.neighbor_nodes.size());
}

TEST_F(LinkStateDatabaseTest, cannotGetLinkStateAdvertisementNotInDatabase) {
  NodeAddr request = 5;
  ASSERT_ANY_THROW(link_state_database.getLinkStateAdvertisementOf(request));
}

TEST_F(LinkStateDatabaseTest, hasLinkStateAdvertisementOf1To4) {
  for (int i = 1; i <= 4; i++) {
    ASSERT_TRUE(link_state_database.hasLinkStateAdvertisementOf(i));
  }
}

TEST_F(LinkStateDatabaseTest, noLinkStateAdvertisementOf5) { ASSERT_FALSE(link_state_database.hasLinkStateAdvertisementOf(5)); }

}  // namespace

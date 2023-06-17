#include "Ospf.h"

namespace quisp::modules::ospf {

void LinkStateDatabase::updateLinkStateDatabase(LinkStateAdvertisement& lsa) {
  const NodeAddr lsa_origin_id = lsa.lsa_origin_id;
  if (link_state_database.count(lsa_origin_id)) lsa.lsa_age++;
  link_state_database[lsa_origin_id] = lsa;
  lsdb_summary.clear();
}

LinkStateDatabaseSummary LinkStateDatabase::getLinkStateDatabaseSummary() {
  if (lsdb_summary.empty() == false) return lsdb_summary;
  for (const auto& lsa_entry : link_state_database) {
    const LinkStateAdvertisement& lsa = lsa_entry.second;
    lsdb_summary.emplace_back(lsa.lsa_id, lsa.lsa_origin_id, lsa.lsa_age);
  }
  return lsdb_summary;
}

std::map<NodeAddr, int> LinkStateDatabase::generateRoutingTableFromGraph(NodeAddr src_id) const {
  const auto vertices = dijkstraAlgorithm(src_id);
  std::map<NodeAddr, int> routing_table;
  for (const auto& vertex : vertices) {
    const NodeAddr dst_id = vertex.first;
    if (src_id == dst_id) continue;
    const NodeAddr neighbor_id = getSecondNodeInPathToDestNode(src_id, dst_id, vertices);
    routing_table[dst_id] = getGateIndexToNeighbor(src_id, neighbor_id);
  }
  return routing_table;
}

RouterIds LinkStateDatabase::identifyMissingLinkStateAdvertisementId(const LinkStateDatabaseSummary& lsdb_summary_from_neighbor) const {
  RouterIds missing_lsas;
  for (const SummaryLinkStateAdvertisement& lsa : lsdb_summary_from_neighbor) {
    if (needsFullLinkStateAdvertisementOf(lsa)) missing_lsas.push_back(lsa.lsa_origin_id);
  }
  return missing_lsas;
}

LinkStateUpdate LinkStateDatabase::getLinkStateUpdatesFor(const RouterIds& requests, int my_address) const {
  std::vector<LinkStateAdvertisement> lsu;
  for (const NodeAddr request : requests) {
    auto lsa = getLinkStateAdvertisementOf(request);
    lsa.lsa_id = my_address;
    lsu.push_back(lsa);
  }
  return lsu;
}


LinkStateAdvertisement LinkStateDatabase::getLinkStateAdvertisementOf(NodeAddr router) const {
  if (!link_state_database.count(router)) throw omnetpp::cRuntimeError("Requested LSA of router%d does not exist", router);
  return link_state_database.at(router);
}

bool LinkStateDatabase::hasLinkStateAdvertisementOf(NodeAddr router) const {return link_state_database.count(router);}

bool LinkStateDatabase::needsFullLinkStateAdvertisementOf(const SummaryLinkStateAdvertisement& summary_lsa) const {
  const NodeAddr source_of_lsa = summary_lsa.lsa_origin_id;
  if (!link_state_database.count(source_of_lsa)) return true;
  if (link_state_database.at(source_of_lsa).lsa_age < summary_lsa.lsa_age) return true;
  return false;
}

int LinkStateDatabase::getGateIndexToNeighbor(NodeAddr src_id, NodeAddr neighbor_id) const {
  if (link_state_database.count(src_id) && link_state_database.at(src_id).neighbor_nodes.count(neighbor_id)) {
    return link_state_database.at(src_id).neighbor_nodes.at(neighbor_id).gate_index;
  }
  throw omnetpp::cRuntimeError("LinkStateDatabase::getGateIndexToNeighbor neighbor node%d of source node%d", neighbor_id, src_id);
}

NodeAddr LinkStateDatabase::getSecondNodeInPathToDestNode(NodeAddr source_id, NodeAddr dst_id, const VertexMap& vertices) const {
  auto current_node_ptr = vertices.at(dst_id);
  while (current_node_ptr->prev_node_in_path != source_id) {
    NodeAddr prev_node_id = current_node_ptr->prev_node_in_path;
    current_node_ptr = vertices.at(prev_node_id);
  }
  return current_node_ptr->node_id;
}

/**
 * @brief Dijkstra's Algorithm
 *        Reference: Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford Stein. 2009. Introduction to Algorithms, Third Edition (3rd. ed.). The MIT Press.
 * @param source_id
 * @return map<int (Node ID), LinkStateDatabase::VertexSharedPtr>
 *         Each node has a pointer to the previous node in its path from source
 *         The full path from source to destination can be retrieved by following the pointer from the destination to the source
 */
const LinkStateDatabase::VertexMap LinkStateDatabase::dijkstraAlgorithm(NodeAddr source_id) const {
  auto vertices = generateVerticesFromLsdb();
  vertices[source_id]->distance_from_source = 0;
  auto Q = initializePriorityQueue(vertices);
  while (Q.size()) {
    const auto current_vertex = popMinDistanceNode(Q);
    for (const auto& neighbor_entry : link_state_database.at(current_vertex->node_id).neighbor_nodes) {
      const auto neighbor_node = neighbor_entry.second;
      // if we do not have information about this neighbor, skip to next neighbor
      if (!vertices.count(neighbor_node.router_id)) continue;

      auto neighbor_vertex = vertices[neighbor_node.router_id];
      relax(current_vertex, neighbor_vertex);
    }
  }
  return vertices;
}

LinkStateDatabase::VertexMap LinkStateDatabase::generateVerticesFromLsdb() const {
  std::map<NodeAddr, std::shared_ptr<Vertex>> vertices;
  for (const auto& lsa : link_state_database) {
    vertices[lsa.first] = std::shared_ptr<Vertex>(new Vertex(lsa.second));
  }
  return vertices;
}

double LinkStateDatabase::weight(NodeAddr node1, NodeAddr node2) const {
  if (link_state_database.count(node1) && link_state_database.at(node1).neighbor_nodes.count(node2)) {
    return link_state_database.at(node1).neighbor_nodes.at(node2).cost;
  }
  throw omnetpp::cRuntimeError("Dijkstra's algorithm couldn't find an edge between node%d and node%d", node1, node2);
}

template <typename Q>
LinkStateDatabase::VertexSharedPtr LinkStateDatabase::popMinDistanceNode(Q& q) const {
  auto u = const_cast<LinkStateDatabase::VertexSharedPtr&>(q.top());
  q.pop();
  return u;
}

void LinkStateDatabase::relax(const LinkStateDatabase::VertexSharedPtr current_node_ptr, LinkStateDatabase::VertexSharedPtr adjacent_node) const {
  if (adjacent_node->distance_from_source > current_node_ptr->distance_from_source + weight(current_node_ptr->node_id, adjacent_node->node_id)) {
    adjacent_node->distance_from_source = current_node_ptr->distance_from_source + weight(current_node_ptr->node_id, adjacent_node->node_id);
    adjacent_node->prev_node_in_path = current_node_ptr->node_id;
  }
}

/**
 * @brief Initializes a priority_queue for Dijkstra's Algorithm
 * @details This function first creates a vector of vertices from the inputted map of vertices (std::transform),
 *          and then initializes a priority queue using the vector vertices in its constructor.
 *          The reason for this workaround is because std::priority_queue does not have a constructor that takes std::map as an input.
 *
 * @param map_vertices
 * @return std::priority_queue<LinkStateDatabase::VertexSharedPtr, std::vector<LinkStateDatabase::VertexSharedPtr>, LinkStateDatabase::VertexMinPriority>
 */
std::priority_queue<LinkStateDatabase::VertexSharedPtr, std::vector<LinkStateDatabase::VertexSharedPtr>, LinkStateDatabase::VertexMinPriority>
LinkStateDatabase::initializePriorityQueue(const VertexMap& map_vertices) const {

  std::vector<LinkStateDatabase::VertexSharedPtr> vector_vertices(map_vertices.size());

  std::transform(map_vertices.begin(), map_vertices.end(), vector_vertices.begin(), [](const auto& pair) { return pair.second; });

  std::priority_queue Q(vector_vertices.begin(), vector_vertices.end(), LinkStateDatabase::VertexMinPriority());
  return Q;
}
}  // namespace quisp::modules::ospf

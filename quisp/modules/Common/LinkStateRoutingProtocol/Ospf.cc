#include "Ospf.h"

namespace quisp::modules::ospf {

/**
  * @brief Adds new lsa or updated lsa to link_state_database
  *        As a sideffect, this function clears lsdb_summary
*/
void LinkStateDatabase::updateLinkStateDatabase(LinkStateAdvertisement& lsa) {
  const NodeAddr lsa_origin_id = lsa.lsa_origin_id;
  if (link_state_database.count(lsa_origin_id)) {
    auto my_lsa = link_state_database.at(lsa_origin_id);
    if (my_lsa.lsa_age >= lsa.lsa_age) throw omnetpp::cRuntimeError("LinkStateDatabase::updateLinkStateDatabase: input lsa is outdated");
    if (my_lsa.neighbor_nodes.size() >= lsa.neighbor_nodes.size())
      throw omnetpp::cRuntimeError(
          "LinkStateDatabase::updateLinkStateDatabase: size of neighbor_nodes is assumed to monotonically increase, but the input has smaller size of neighbor_nodes");
  }
  link_state_database[lsa_origin_id] = lsa;
  lsdb_summary.clear();
}

/**
  * @brief Get the Link State Database Summary object
  * @details This function also takes care of generating lsdb_summary when needed
  *          This is to prevent unnecessary lsdb_summary update, as lsdb_summary is not needed until a router receives LsrPacket
  * @return lsdb_summary
*/
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
    routing_table[dst_id] = getHopAddressToNeighbor(src_id, neighbor_id);
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

bool LinkStateDatabase::needsFullLinkStateAdvertisementOf(const SummaryLinkStateAdvertisement& summary_lsa) const {
  const NodeAddr source_of_lsa = summary_lsa.lsa_origin_id;
  if (!link_state_database.count(source_of_lsa)) return true;
  if (link_state_database.at(source_of_lsa).lsa_age < summary_lsa.lsa_age) return true;
  return false;
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

bool LinkStateDatabase::hasLinkStateAdvertisementOf(NodeAddr router) const { return link_state_database.count(router); }

int LinkStateDatabase::getHopAddressToNeighbor(NodeAddr src_id, NodeAddr neighbor_id) const {
  if (link_state_database.count(src_id) && link_state_database.at(src_id).neighbor_nodes.count(neighbor_id)) {
    return link_state_database.at(src_id).neighbor_nodes.at(neighbor_id).hop_address;
  }
  throw omnetpp::cRuntimeError("LinkStateDatabase::getGateIndexToNeighbor: either neighbor node%d or source node%d does not exist in link_state_database", neighbor_id, src_id);
}

NodeAddr LinkStateDatabase::getSecondNodeInPathToDestNode(NodeAddr source_id, NodeAddr dst_id, const VertexMap& vertices) const {
  auto current_node_ptr = vertices.at(dst_id);
  while (current_node_ptr->prev_node_in_path != source_id) {
    NodeAddr prev_node_id = current_node_ptr->prev_node_in_path;
    current_node_ptr = vertices.at(prev_node_id);
    if (current_node_ptr->prev_node_in_path == -1)
      throw omnetpp::cRuntimeError("LinkStateDatabase::getSecondNodeInPathToDestNode: could not find path from node%d to node%d", source_id, dst_id);
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
  if (vertices.count(source_id) == false) throw omnetpp::cRuntimeError("LinkStateDatabase::dijkstraAlgorithm: link_state_database does not have vertex%d", source_id);

  vertices[source_id]->distance_from_source = 0;
  PriorityQueue queue;
  queue.emplace(vertices[source_id]);

  while (queue.size()) {
    const auto current_vertex = popMinDistanceNode(queue);
    for (const auto& neighbor_entry : link_state_database.at(current_vertex->node_id).neighbor_nodes) {
      const auto neighbor_node = neighbor_entry.second;

      if (current_vertex->node_id == neighbor_node.router_id)
        throw omnetpp::cRuntimeError("LinkStateDatabase::dijkstraAlgorithm: vertex%d has self as a neighbor, which cannot happen", current_vertex->node_id);

      // if we do not have information about this neighbor, skip to next neighbor
      if (!vertices.count(neighbor_node.router_id)) continue;

      auto neighbor_vertex = vertices[neighbor_node.router_id];
      double distance_of_new_path = current_vertex->distance_from_source + weight(current_vertex->node_id, neighbor_vertex->node_id);
      if (neighbor_vertex->distance_from_source > distance_of_new_path) {
        neighbor_vertex->distance_from_source = distance_of_new_path;
        neighbor_vertex->prev_node_in_path = current_vertex->node_id;
        queue.emplace(neighbor_vertex);
      }
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
  throw omnetpp::cRuntimeError("LinkStateDatabase::weight: couldn't find an edge between node%d and node%d", node1, node2);
}

LinkStateDatabase::VertexSharedPtr LinkStateDatabase::popMinDistanceNode(PriorityQueue& q) const {
  auto u = q.top();
  q.pop();
  return u;
}
}  // namespace quisp::modules::ospf

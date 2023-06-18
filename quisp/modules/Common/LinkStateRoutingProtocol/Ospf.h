#pragma once
#include <omnetpp.h>
#include <algorithm>
#include <limits>
#include <memory>
#include <queue>
#include <vector>
#include "omnetpp/cexception.h"

namespace quisp::modules::ospf {

enum class OspfState;
struct OspfNeighborInfo;
struct SummaryLinkStateAdvertisement;
struct LinkStateAdvertisement;
class LinkStateDatabase;

using NodeAddr = int;
using RouterIds = std::vector<int>;
using NeighborTable = std::map<NodeAddr, OspfNeighborInfo>;
using LinkStateDatabaseSummary = std::vector<SummaryLinkStateAdvertisement>;
using LinkStateUpdate = std::vector<LinkStateAdvertisement>;

enum class OspfState { DOWN = 0, INIT = 1, TWO_WAY = 2, EXSTART = 3, EXCHANGE = 4, LOADING = 5, FULL = 6 };

struct OspfNeighborInfo {
  NodeAddr router_id;
  int gate_index = -1;
  OspfState state = OspfState::DOWN;
  double cost;

  OspfNeighborInfo(int rid) : router_id(rid) {}
  OspfNeighborInfo(int idx, OspfState st) : gate_index(idx), state(st) {}
  OspfNeighborInfo(int idx, OspfState st, double c) : gate_index(idx), state(st), cost(c) {}
  OspfNeighborInfo(int rid, int idx, double c) : router_id(rid), gate_index(idx), cost(c) {}
  OspfNeighborInfo(int rid, int idx, OspfState st, double c) : router_id(rid), gate_index(idx), state(st), cost(c) {}
  OspfNeighborInfo() = default;
};

struct SummaryLinkStateAdvertisement {
  NodeAddr lsa_id;
  NodeAddr lsa_origin_id;
  int lsa_age;
  SummaryLinkStateAdvertisement(NodeAddr id, NodeAddr origin_id, int age) : lsa_id(id), lsa_origin_id(origin_id), lsa_age(age){};
  SummaryLinkStateAdvertisement() = default;
};

struct LinkStateAdvertisement : SummaryLinkStateAdvertisement {
  NeighborTable neighbor_nodes;
  LinkStateAdvertisement(NodeAddr id, NodeAddr origin_id, NeighborTable neighbor_table) : SummaryLinkStateAdvertisement(id, origin_id, 0), neighbor_nodes(neighbor_table) {}
  LinkStateAdvertisement(NodeAddr id, NodeAddr origin_id, int age, std::map<NodeAddr, OspfNeighborInfo> neighbor_table)
      : SummaryLinkStateAdvertisement(id, origin_id, age), neighbor_nodes(neighbor_table) {}
  LinkStateAdvertisement() = default;
};

class LinkStateDatabase {
 protected:
  /**
   * @brief Vertex is a representation of routers in Dijkstra's Algorithm
   */
  struct Vertex;

  /**
   * @brief VertexMinPriority is used only in InitializePriorityQueue function.
   *        It compares the distance_from_source of two nodes.
   *        This struct allows the priority queue to order the nodes by distance_from_source in increasing order
   */
  struct VertexMinPriority;

  using VertexSharedPtr = std::shared_ptr<Vertex>;
  using VertexMap = std::map<NodeAddr, VertexSharedPtr>;

 public:
  void updateLinkStateDatabase(LinkStateAdvertisement& lsa);
  LinkStateDatabaseSummary getLinkStateDatabaseSummary();

  std::map<NodeAddr, int> generateRoutingTableFromGraph(NodeAddr source) const;

  RouterIds identifyMissingLinkStateAdvertisementId(const LinkStateDatabaseSummary& lsdb_summary_from_neighbor) const;
  LinkStateUpdate getLinkStateUpdatesFor(const RouterIds& requests, int my_address) const;
  LinkStateAdvertisement getLinkStateAdvertisementOf(NodeAddr router) const;
  bool hasLinkStateAdvertisementOf(NodeAddr router) const;
  bool needsFullLinkStateAdvertisementOf(const SummaryLinkStateAdvertisement& summary_lsa) const;

 protected:
  int getGateIndexToNeighbor(NodeAddr src, NodeAddr neighbor) const;
  NodeAddr getSecondNodeInPathToDestNode(NodeAddr source_id, NodeAddr dst_id, const VertexMap& vertices) const;

  const VertexMap dijkstraAlgorithm(NodeAddr source_id) const;
  VertexMap generateVerticesFromLsdb() const;
  double weight(NodeAddr node1, NodeAddr node2) const;
  template <typename Q>
  VertexSharedPtr popMinDistanceNode(Q& q) const;
  void relax(const VertexSharedPtr current_node, VertexSharedPtr adjacent_node) const;
  std::priority_queue<VertexSharedPtr, std::vector<VertexSharedPtr>, VertexMinPriority> initializePriorityQueue(const VertexMap& map_vertices) const;

 protected:
  std::map<NodeAddr, LinkStateAdvertisement> link_state_database;
  LinkStateDatabaseSummary lsdb_summary;

  struct Vertex {
    NodeAddr node_id;
    double distance_from_source;
    NodeAddr prev_node_in_path;
    Vertex(LinkStateAdvertisement lsa) : node_id(lsa.lsa_origin_id), distance_from_source(std::numeric_limits<double>::max()), prev_node_in_path(-1) {}
    Vertex() = default;
  };

  struct VertexMinPriority {
    bool operator()(VertexSharedPtr const l, VertexSharedPtr const r) const noexcept { return l->distance_from_source > r->distance_from_source; }
  };
};
}  // namespace quisp::modules::ospf

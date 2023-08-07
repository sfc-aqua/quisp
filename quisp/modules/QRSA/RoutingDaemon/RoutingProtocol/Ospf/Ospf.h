#pragma once

/**
 * @file Ospf.h
 * @author Tatsuhiro Nakamori
 * @brief
 * This file contains the declaration of the LinkStateDatabase
 * and classes and structs which LinkStateDatabase depends on.
 * These classes are necessary in RoutingDaemon.cc in order to
 * conduct OSPF Routing Protocol.
 * Please refer to https://tech.pjin.jp/blog/2021/03/03/ospf_4/
 * for description of OSPF
 * @date 2023-07-16
 */

#include <omnetpp.h>
#include <algorithm>
#include <limits>
#include <memory>
#include <queue>
#include <vector>
#include "omnetpp/cexception.h"

namespace quisp::modules::ospf {

class LinkStateDatabase;
struct LinkStateAdvertisement;
struct SummaryLinkStateAdvertisement;
struct OspfNeighborInfo;
enum class OspfState;

using NodeAddr = int;
using RouterIds = std::vector<int>;
using NeighborTable = std::map<NodeAddr, OspfNeighborInfo>;
using LinkStateDatabaseSummary = std::vector<SummaryLinkStateAdvertisement>;
using LinkStateUpdate = std::vector<LinkStateAdvertisement>;

enum class OspfState { DOWN = 0, INIT = 1, TWO_WAY = 2, EXSTART = 3, EXCHANGE = 4, LOADING = 5, FULL = 6 };

struct OspfNeighborInfo {
  NodeAddr router_id;
  // address that router needs in order to send packet to neighbor router
  // qnic_address in case of Quantum Routing Table
  int hop_address = -1;
  OspfState state = OspfState::DOWN;
  double cost;

  OspfNeighborInfo(int _router_id) : router_id(_router_id) {}
  OspfNeighborInfo(int _hop_address, OspfState _state) : hop_address(_hop_address), state(_state) {}
  OspfNeighborInfo(int _hop_address, OspfState _state, double _cost) : hop_address(_hop_address), state(_state), cost(_cost) {}
  OspfNeighborInfo(int _router_id, int _hop_address, double _cost) : router_id(_router_id), hop_address(_hop_address), cost(_cost) {}
  OspfNeighborInfo(int _router_id, int _hop_address, OspfState _state, double _cost) : router_id(_router_id), hop_address(_hop_address), state(_state), cost(_cost) {}
  OspfNeighborInfo() = default;
};

/**
 * @brief
 * This struct is used in DBD packet exchange for two nodes to communicate
 * what link-state advertisements are missing from one or the other.
 */
struct SummaryLinkStateAdvertisement {
  NodeAddr lsa_id;
  NodeAddr lsa_origin_id;
  int lsa_age;
  SummaryLinkStateAdvertisement(NodeAddr _id, NodeAddr _origin_id, int _age) : lsa_id(_id), lsa_origin_id(_origin_id), lsa_age(_age){};
  SummaryLinkStateAdvertisement() = default;
};

/**
 * @brief
 * Full link-state advertisement that holds info of neighbor_nodes.
 * Element that makes up the LinkStateDatabase topology information.
 */
struct LinkStateAdvertisement : SummaryLinkStateAdvertisement {
  NeighborTable neighbor_nodes;
  LinkStateAdvertisement(NodeAddr _id, NodeAddr _origin_id, NeighborTable _neighbor_table) : SummaryLinkStateAdvertisement(_id, _origin_id, 0), neighbor_nodes(_neighbor_table) {}
  LinkStateAdvertisement(NodeAddr _id, NodeAddr _origin_id, int _age, NeighborTable _neighbor_table)
      : SummaryLinkStateAdvertisement(_id, _origin_id, _age), neighbor_nodes(_neighbor_table) {}
  LinkStateAdvertisement() = default;
};

/**
 * @brief
 * Represents the database that holds link-state advertisements of nodes.
 * Effectively, link_state_database is the topology information of a network.
 * This class holds several public methods that enable easy execution of OSPF.
 */
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
  using PriorityQueue = std::priority_queue<VertexSharedPtr, std::vector<VertexSharedPtr>, VertexMinPriority>;

 public:
  void updateLinkStateDatabase(LinkStateAdvertisement& lsa);

  LinkStateDatabaseSummary getLinkStateDatabaseSummary();

  std::map<NodeAddr, int> generateRoutingTableFromGraph(NodeAddr source) const;

  RouterIds identifyMissingLinkStateAdvertisementId(const LinkStateDatabaseSummary& lsdb_summary_from_neighbor) const;
  virtual bool needsFullLinkStateAdvertisementOf(const SummaryLinkStateAdvertisement& summary_lsa) const;
  LinkStateUpdate getLinkStateUpdatesFor(const RouterIds& requests, int my_address) const;
  virtual LinkStateAdvertisement getLinkStateAdvertisementOf(NodeAddr router) const;
  bool hasLinkStateAdvertisementOf(NodeAddr router) const;

 protected:
  int getHopAddressToNeighbor(NodeAddr src, NodeAddr neighbor) const;
  NodeAddr getSecondNodeInPathToDestNode(NodeAddr source_id, NodeAddr dst_id, const VertexMap& vertices) const;

  virtual const VertexMap dijkstraAlgorithm(NodeAddr source_id) const;
  VertexMap generateVerticesFromLsdb() const;
  double weight(NodeAddr node1, NodeAddr node2) const;
  VertexSharedPtr popMinDistanceNode(PriorityQueue& q) const;

 protected:
  std::map<NodeAddr, LinkStateAdvertisement> link_state_database;
  LinkStateDatabaseSummary lsdb_summary;

  struct Vertex {
    NodeAddr node_id;
    double distance_from_source;
    NodeAddr prev_node_in_path;
    static constexpr int no_prev_node = -1;
    Vertex(LinkStateAdvertisement _lsa) : node_id(_lsa.lsa_origin_id), distance_from_source(std::numeric_limits<double>::max()), prev_node_in_path(no_prev_node) {}
    Vertex() = default;
  };

  struct VertexMinPriority {
    bool operator()(VertexSharedPtr const l, VertexSharedPtr const r) const noexcept { return l->distance_from_source > r->distance_from_source; }
  };
};
}  // namespace quisp::modules::ospf

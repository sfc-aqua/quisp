#pragma once
#include <omnetpp.h>
#include <vector>

namespace quisp::modules {

enum class OspfState { DOWN = 0, INIT = 1, TWO_WAY = 2, EXSTART = 3, EXCHANGE = 4, LOADING = 5, FULL = 6 };

struct OspfNeighborInfo {
  int router_id;
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

struct LinkStateAdvertisement {
  int lsa_id;
  int lsa_origin_id;
  int lsa_age;
  std::vector<OspfNeighborInfo> neighbor_nodes;
};
}  // namespace quisp::modules

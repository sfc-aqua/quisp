/** \file RoutingDaemon.cc
 *  \authors takaakimatsuo
 *
 *  \brief RoutingDaemon
 */
#include "RoutingDaemon.h"
#include <messages/classical_messages.h>
#include <optional>
#include <stdexcept>
#include <vector>
#include "modules/QRSA/RoutingDaemon/IRoutingDaemon.h"
#include "types/QNodeAddr.h"

using namespace omnetpp;

namespace quisp::modules::routing_daemon {

RoutingDaemon::RoutingDaemon() : provider(this) {}

/**
 *
 *  \brief RoutingDaemon
 *
 * The RoutingDaemon is one of the five key modules in the
 * software for a quantum repeater/router (qrsa).  It will be responsible for
 * running dynamic routing protocols, such as qOSPF, qBGP, etc.
 *
 * It communicates with other RoutingDaemons, in other nodes on the network,
 * as in the classical Internet.  Internally, its role is to keep track of the
 * QNICs and the links by communicating with the HardwareMonitor, and to provide
 * information to the ConnectionManager when requested.  (There is also one
 * place where the RuleEngine needs access to information maintained by the RD.)
 *
 * The above is the intended design.
 *
 * TODO In fact, the RoutingDaemon as it exists today uses special, internal
 * OMNeT++ magic to directly access the network topology, as stored in the
 * simulator, rather than dynamically discovering it.  That should be corrected.
 *
 * At the moment, the RD is independent of the end-to-end reservation of resources,
 * as dictated by the multiplexing (muxing) discpline in use.  This means that
 * it always returns a single, best path to connect to the requested node.  A
 * consequence is that ConnectionSetupRequest can fail if the resource management
 * discipline is fully blocking, as in circuit switching, which is the first
 * discipline we are implementing.
 *
 * TODO Also, this code is built as a Module, via the Define_Module call;
 * the other important modules are classes.  That distinction needs to be
 * addressed.
 */
void RoutingDaemon::initialize(int stage) {
  myAddress = provider.getNodeAddr();

  // Topology creation for routing table
  cTopology *topo = new cTopology("topo");

  // Any node that has a parameter included_in_topology will be included in routing
  topo->extractByParameter("included_in_topology", "\"yes\"");

  // If no node with the parameter & value found, do nothing.
  if (topo->getNumNodes() == 0 || topo == nullptr) {
    return;
  }

  updateChannelWeightsInTopology(topo);
  generateRoutingTable(topo);

  delete topo;
}

// Initialize channel weights for all existing links.
void RoutingDaemon::updateChannelWeightsInTopology(cTopology *topo) {
  for (int i = 0; i < topo->getNumNodes(); i++) {  // Traverse through all nodes
    auto node = topo->getNode(i);
    updateChannelWeightsOfNode(node);
  }
}

void RoutingDaemon::updateChannelWeightsOfNode(cTopology::Node *node) {
  for (int i = 0; i < node->getNumOutLinks(); i++) {  // Traverse through all links from a specific node.

    // For Bidirectional channels, parameters are stored in LinkOut not LinkIn.
    auto outgoing_link = node->getLinkOut(i);

    double channel_weight = calculateSecPerBellPair(outgoing_link);

    if (strstr(outgoing_link->getLocalGate()->getFullName(), "quantum")) {
      // Otherwise, keep the quantum channels and set the weight
      outgoing_link->setWeight(channel_weight);  // Set channel weight
    } else {
      // Ignore classical link in quantum routing table
      outgoing_link->disable();
    }
  }
}

// Calculate bell pair generation rate to use it as channel cost
// The cost metric is taken from https://arxiv.org/abs/1206.5655
double RoutingDaemon::calculateSecPerBellPair(const cTopology::LinkOut *const outgoing_link) {
  double speed_of_light_in_fiber = outgoing_link->getLocalGate()->getChannel()->par("speed_of_light_in_fiber");
  double channel_length = outgoing_link->getLocalGate()->getChannel()->par("distance");

  auto *some_stationary_qubit_in_qnic = findModuleByPath("^.^.qnic[0].statQubit[0]");
  auto *some_stationary_qubit_in_qnic_r = findModuleByPath("^.^.qnic_r[0].statQubit[0]");

  double emission_prob = 1.0;
  // TODO: fix this to read the emission success probability correctly. This is a quick fix!!
  if (some_stationary_qubit_in_qnic != nullptr) {
    emission_prob = some_stationary_qubit_in_qnic->par("emission_success_probability").doubleValue();
  } else if (some_stationary_qubit_in_qnic_r != nullptr) {
    emission_prob = some_stationary_qubit_in_qnic_r->par("emission_success_probability").doubleValue();
  } else {
    error("cannot read emission_success_probability from file");
  }

  return (channel_length / speed_of_light_in_fiber) * emission_prob;
}

void RoutingDaemon::generateRoutingTable(cTopology *topo) {
  cTopology::Node *this_node = topo->getNodeFor(provider.getNode());  // The parent node with this specific router

  for (int i = 0; i < topo->getNumNodes(); i++) {  // Traverse through all the destinations from the thisNode
    const auto node = topo->getNode(i);
    if (node == this_node) continue;  // skip the node that is running this specific router app

    auto *target_module = node->getModule();

    // dest node might have multiple addresses
    std::vector<QNodeAddr> dest_node_addresses = {QNodeAddr{target_module->par("address").stringValue()}};
    if (target_module->findPar("available_addresses") != -1) {
      auto address_str_list = ((cValueArray *)target_module->par("available_addresses").objectValue())->asStringVector();
      for (auto &s : address_str_list) {
        auto addr = QNodeAddr{s.c_str()};
        dest_node_addresses.push_back(addr);
      }
    }

    // Apply dijkstra to each node to find all shortest paths.
    topo->calculateWeightedSingleShortestPathsTo(node);  // Overwrites getNumPaths() and so on.

    // Check the number of shortest paths towards the target node. This may be more than 1 if multiple paths have the same minimum cost.
    if (this_node->getNumPaths() == 0) {
      error("Path not found. This means that a node is completely separated...Probably not what you want now");
      continue;  // not connected
    }

    // Returns the next link/gate in the ith shortest paths towards the target node.
    cGate *parentModuleGate = this_node->getPath(0)->getLocalGate();

    {  // set next neighbor addr

      auto *module = this_node->getPath(0)->getRemoteNode()->getModule();
      // if the next neighbor node is a BSA, skip it and take the next module as a neighbor because we treate BSA as an link
      if (strcmp(module->par("node_type").stringValue(), "BSA") == 0) {
        if (this_node->getPath(0)->getRemoteNode()->getNumPaths() == 0) {
          module = nullptr;
        } else {
          module = this_node->getPath(0)->getRemoteNode()->getPath(0)->getRemoteNode()->getModule();
        }
      }

      if (module != nullptr) {
        QNodeAddr next_addr{module->par("address").stringValue()};
        for (auto &a : dest_node_addresses) {
          neighbor_addr_table[a] = next_addr;
          std::cout << "@" << myAddress << " neighbor_addr_table[" << a << "] = " << next_addr << std::endl;
        }
      }
    }

    auto *node_in_path = this_node;
    // collect path info
    std::vector<std::vector<QNodeAddr>> addrs_in_path{};

    while (node_in_path != topo->getTargetNode()) {
      auto node_type = node_in_path->getModule()->par("node_type").stringValue();
      if (strcmp(node_type, "BSA") != 0) {
        // std::cout << " . " << node_in_path->getModule()->par("address").stringValue() << std::endl;
        auto addresses = RoutingDaemon::getQNodeAddressList(node_in_path->getModule());
        addrs_in_path.push_back(addresses);
      }
      auto *path = node_in_path->getPath(0);
      node_in_path = path->getRemoteNode();
    }
    auto node_type = node_in_path->getModule()->par("node_type").stringValue();
    if (strcmp(node_type, "BSA") != 0) {
      // std::cout << " ... " << node_in_path->getModule()->par("address").stringValue() << std::endl;
      auto addresses = RoutingDaemon::getQNodeAddressList(node_in_path->getModule());
      addrs_in_path.push_back(addresses);
    }

    for (auto &addresses : addrs_in_path) {
      std::cout << "{";
      for (auto &a : addresses) std::cout << a << ", ";
      std::cout << "}" << std::endl;
    }
    auto it = RoutingDaemon::findNetworkBoundary(addrs_in_path, dest_node_addresses.at(0));
    auto [current_network, current_addr, neighbor_addr, lower_dest_addr] = it;
    std::cout << myAddress << "(" << current_addr << ")"
              << "->" << dest_node_addresses << ": cur_net:" << current_network << ", neighbor:" << neighbor_addr << ", lower dest:" << lower_dest_addr << std::endl;
    if (lower_dest_addr.isValid()) {
      for (auto &a : dest_node_addresses) {
        lower_layer_routing_table.insert({a, it});
      }
    }

    for (auto &addr : dest_node_addresses) {
      qrtable[addr] = getQNicAddr(parentModuleGate);
      // std::cout << "qrtable@" << myAddress << "[" << addr << "]:" << qrtable[addr] << std::endl;
    }

    if (!strstr(parentModuleGate->getFullName(), "quantum")) {
      error("Quantum routing table referring to classical gates...");
    }
  }
}

std::vector<QNodeAddr> RoutingDaemon::getQNodeAddressList(cModule *mod) {
  if (mod->findPar("address") == -1) return {};
  std::vector<QNodeAddr> address_list{QNodeAddr{mod->par("address").stringValue()}};

  if (mod->findPar("available_addresses") == -1) return address_list;

  for (auto &s : ((cValueArray *)(mod->par("available_addresses").objectValue()))->asStringVector()) {
    address_list.push_back(QNodeAddr{s.c_str()});
  }
  return address_list;
}

DestInfoTuple RoutingDaemon::findNetworkBoundary(const std::vector<std::vector<types::QNodeAddr>> &path, QNodeAddr dest_addr) {
  // current addr, neighbor addr, lower dest addr,

  int current_network = -1;
  int depth = 0;
  std::vector<std::vector<QNodeAddr>> layers = {{path[0][0]}};
  std::tuple<QNodeAddr, QNodeAddr> current_hop = {QNodeAddr{}, QNodeAddr{}};
  auto find_intersect = [&](const std::vector<QNodeAddr> &v1, const std::vector<QNodeAddr> &v2) {
    for (const auto &e1 : v1) {
      for (const auto &e2 : v2) {
        if (e1 == e2) return e1;
      }
    }
    return QNodeAddr{-1, -1};
  };

  auto find_same_layer_hop = [&](const std::vector<QNodeAddr> &v1, const std::vector<QNodeAddr> &v2) {
    std::optional<std::tuple<QNodeAddr, QNodeAddr>> result = std::nullopt;
    for (const auto &e1 : v1) {
      for (const auto &e2 : v2) {
        if (e1.network_addr == e2.network_addr) {
          result = std::make_optional(std::make_tuple(e1, e2));
          break;
        }
      }
    }
    return result;
  };

  auto get_network_by_depth = [&](int current_depth) {
    assert(layers.size() > current_depth);
    assert(layers[current_depth].size() > 0);
    return layers[current_depth][layers[current_depth].size() - 1].network_addr;
  };

  // loop hop by hop addr pair
  for (int i = 0; i < path.size() - 1; i++) {
    // find same network addr pair in hop by hop
    auto hop = find_same_layer_hop(path[i], path[i + 1]);
    if (hop.has_value()) {
      current_hop = hop.value();
      int network = get_network_by_depth(depth);
      if (network == std::get<0>(current_hop).network_addr) {
        // found same network layer
        layers[depth].push_back(std::get<0>(current_hop));
        layers[depth].push_back(std::get<1>(current_hop));
      } else {
        // different network layer hop
        if (depth > 0 && std::get<0>(current_hop).network_addr == get_network_by_depth(depth - 1)) {
          // upper layer has same network (come back from subnet path)
          depth -= 1;
          layers[depth].push_back(std::get<0>(current_hop));
          layers[depth].push_back(std::get<1>(current_hop));
        } else {
          // one more deeper layer
          depth += 1;
          if (layers.size() > depth) {
            layers[depth].push_back(std::get<0>(current_hop));
            layers[depth].push_back(std::get<1>(current_hop));
          } else {
            layers.push_back({std::get<0>(current_hop), std::get<1>(current_hop)});
          }
        }
      }
    } else {  // across different network
      current_hop = {path[i][0], path[i + 1][0]};

      if (layers.size() > depth) {
        if (depth > 0) {
          depth -= 1;
        }
        layers[depth].push_back(path[i][0]);
        layers[depth].push_back(path[i + 1][0]);
      } else {
        depth += 1;
        if (layers.size() > depth) {
          layers[depth].push_back(std::get<0>(current_hop));
          layers[depth].push_back(std::get<1>(current_hop));
        } else {
          layers.push_back({std::get<0>(current_hop), std::get<1>(current_hop)});
        }
      }
    }
  }

  QNodeAddr current_addr{-1, -1};
  QNodeAddr neighbor_addr(-1, -1);
  QNodeAddr lower_dest_addr(-1, -1);
  if (layers.size() > 1) {
    current_addr = find_intersect(path[0], layers[1]);
    if (current_addr.isValid()) {
      neighbor_addr = find_intersect(path[1], layers[1]);
      lower_dest_addr = layers[1][0];
      int first_lower_network = layers[1][0].network_addr;
      for (const auto &addr : layers[1]) {
        if (first_lower_network != addr.network_addr) {
          break;
        }
        lower_dest_addr = addr;
      }
    }
  }
  current_network = lower_dest_addr.network_addr;
  return {current_network, current_addr, neighbor_addr, lower_dest_addr};
}

std::optional<DestInfoTuple> RoutingDaemon::findLowerLayerDestInfoByDestAddr(QNodeAddr dest_addr) {
  auto it = lower_layer_routing_table.find(dest_addr);
  if (it == lower_layer_routing_table.end()) {
    return std::nullopt;
  }
  return std::make_optional(it->second);
}

int RoutingDaemon::getQNicAddr(const cGate *const module_gate) {
  const auto module = module_gate->getPreviousGate()->getOwnerModule();
  return module->par("self_qnic_address").intValue();
}

/**
 * This is the only routine, at the moment, with any outside contact.
 * Rather than exchanging a message with those who need this information (ConnectionManager, mainly,
 * and in one case RuleEngine), this is a direct call that they make.
 *
 */
int RoutingDaemon::findQNicAddrByDestAddr(QNodeAddr destAddr) {
  RoutingTable::iterator it = qrtable.find(destAddr);
  if (it == qrtable.end()) {
    EV << "Quantum: address " << destAddr << " unreachable from this node \n";
    return -1;
  }
  return it->second;
}

int RoutingDaemon::getNumEndNodes() {
  cTopology *topo = new cTopology("topo");
  topo->extractByParameter("included_in_topology", "\"yes\"");
  int num_end_nodes = 0;
  for (int i = 0; i < topo->getNumNodes(); i++) {
    cTopology::Node *node = topo->getNode(i);
    std::string node_type = node->getModule()->par("node_type");
    if (node_type == "EndNode") {  // ignore myself
      num_end_nodes++;
    }
  }
  delete topo;
  return num_end_nodes;
};

/**
 * Once we begin using dynamic routing protocols, this is where the messages
 * will be handled.  This perhaps will also be how we communicate with the
 * other important daemons in the qrsa.
 * TODO Handle dynamic routing protocol messages.
 **/
void RoutingDaemon::handleMessage(cMessage *msg) {}

Define_Module(RoutingDaemon);
}  // namespace quisp::modules::routing_daemon

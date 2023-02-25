/** \file RoutingDaemon.cc
 *  \authors takaakimatsuo
 *
 *  \brief RoutingDaemon
 */
#include "RoutingDaemon.h"
#include <messages/classical_messages.h>
#include <vector>

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
  cTopology::Node *this_node = topo->getNodeFor(getParentModule()->getParentModule());  // The parent node with this specific router

  for (int i = 0; i < topo->getNumNodes(); i++) {  // Traverse through all the destinations from the thisNode
    const auto node = topo->getNode(i);
    if (node == this_node) continue;  // skip the node that is running this specific router app

    // Apply dijkstra to each node to find all shortest paths.
    topo->calculateWeightedSingleShortestPathsTo(node);  // Overwrites getNumPaths() and so on.

    // Check the number of shortest paths towards the target node. This may be more than 1 if multiple paths have the same minimum cost.
    if (this_node->getNumPaths() == 0) {
      error("Path not found. This means that a node is completely separated...Probably not what you want now");
      continue;  // not connected
    }
    // Returns the next link/gate in the ith shortest paths towards the target node.
    cGate *parentModuleGate = this_node->getPath(0)->getLocalGate();
    int destAddr = node->getModule()->par("address");

    qrtable[destAddr] = getQNicAddr(parentModuleGate);

    if (!strstr(parentModuleGate->getFullName(), "quantum")) {
      error("Quantum routing table referring to classical gates...");
    }
  }
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
int RoutingDaemon::findQNicAddrByDestAddr(int destAddr) {
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

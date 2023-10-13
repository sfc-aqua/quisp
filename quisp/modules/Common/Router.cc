/** \file Router.cc
 *  \authors takaakimatsuo
 *
 *  \brief Router
 */
#include "Router.h"
#include "messages/QNode_ipc_messages_m.h"
#include "messages/classical_messages.h"  //Path selection: type = 1, Timing notifier for BMA: type = 4
#include "messages/connection_teardown_messages_m.h"

using namespace omnetpp;
using namespace quisp::messages;

namespace quisp::modules {

Router::Router() : provider(utils::ComponentProvider{this}) {}

void Router::initialize() {
  my_address = provider.getNodeAddr();

  // Topology creation for routing table
  auto topo = provider.getTopologyForRouter();

  // If no node with the parameter & value found, do nothing.
  if (topo->getNumNodes() == 0 || topo == nullptr) {
    return;
  }

  generateRoutingTable(topo);
}

void Router::generateRoutingTable(cTopology *topo) {
  cTopology::Node *thisNode = topo->getNodeFor(getParentModule());  // The parent node with this specific router

  // Traverse through all the destinations from the thisNode
  for (int i = 0; i < topo->getNumNodes(); i++) {
    const auto node = topo->getNode(i);
    // skip the node that is running this specific router app
    if (node == thisNode) continue;

    // Apply dijkstra to each node to find all shortest paths.
    topo->calculateWeightedSingleShortestPathsTo(topo->getNode(i));

    // Overwrites getNumPaths() and so on.
    // Check the number of shortest paths towards the target node.
    // This may be more than 1 if multiple paths have the same minimum cost.

    if (thisNode->getNumPaths() == 0) continue;

    // Returns the next link/gate in the ith shortest paths towards the target node.
    cGate *parentModuleGate = thisNode->getPath(0)->getLocalGate();
    int gateIndex = parentModuleGate->getIndex();
    int address = topo->getNode(i)->getModule()->par("address");

    // Store gate index per destination from this node
    routing_table[address] = gateIndex;

    if (strstr(parentModuleGate->getFullName(), "quantum")) {
      error("Classical routing table referring to quantum gates...");
    }
  }
}

void Router::handleMessage(cMessage *msg) {
  const int unidentified_destination = -1;
  // check the header of the received package
  Header *pk = check_and_cast<Header *>(msg);
  int dest_addr = pk->getDestAddr();
  int who_are_you = pk->getKind();

  // If destination is this node: Path selection
  if (dest_addr == my_address && who_are_you == 1) {
    send(pk, "toApp");
    return;
  } else if (dest_addr == my_address && dynamic_cast<BSMTimingNotification *>(msg)) {  // Timing for BSM
    bubble("Timing Notifier from BSA (stand-alone or internal) received");
    send(pk, "rePort$o");  // send to Application locally
    return;
  } else if (dest_addr == my_address && dynamic_cast<EPPStimingNotifier *>(msg)) {  // Timing for BSM
    bubble("Timing Notifier from EPPS received");
    send(pk, "rePort$o");  // send to Application locally
    return;
  } else if (dest_addr == my_address && dynamic_cast<ConnectionSetupRequest *>(msg)) {
    bubble("Connection setup request received");
    send(pk, "cmPort$o");
    return;
  } else if (dest_addr == my_address && dynamic_cast<ConnectionSetupResponse *>(msg)) {
    bubble("Connection setup response received");
    send(pk, "cmPort$o");
    return;
  } else if (dest_addr == my_address && dynamic_cast<RejectConnectionSetupRequest *>(msg)) {
    bubble("Reject connection setup response received");
    send(pk, "cmPort$o");
    return;
  } else if (dest_addr == my_address && dynamic_cast<InternalRuleSetForwarding *>(msg)) {
    bubble("Internal RuleSet Forwarding packet received");
    send(pk, "rePort$o");
    return;
  } else if (dest_addr == my_address && dynamic_cast<InternalRuleSetForwarding_Application *>(msg)) {
    bubble("Internal RuleSet Forwarding Application packet received");
    send(pk, "rePort$o");
    return;
  } else if (dest_addr == my_address && dynamic_cast<InternalNodeAddressesAlongPathForwarding *>(msg)) {
    bubble("Internal Node Addresses Along Path Forwarding packet received");
    send(pk, "rePort$o");
    return;
  } else if (dest_addr == my_address && dynamic_cast<ConnectionTeardownMessage *>(msg)) {
    bubble("Connection Teardown packet received");
    send(pk, "cmPort$o");
    return;
  } else if (dest_addr == my_address && dynamic_cast<InternalConnectionTeardownMessage *>(msg)) {
    bubble("Internal Connection Teardown packet received");
    send(pk, "rePort$o");
    return;
  } else if (dest_addr == my_address && dynamic_cast<BarrierMessage *>(msg)) {
    bubble("Barrier Message packet received");
    send(pk, "rePort$o");
    return;
  } else if (dest_addr == my_address && dynamic_cast<LinkAllocationUpdateMessage *>(msg)) {
    bubble("Link Allocation Update Request packet received");
    send(pk, "rePort$o");
    return;
  } else if (dest_addr == my_address && dynamic_cast<LinkAllocationUpdateMessage *>(msg)) {
    bubble("Link Allocation Update Response packet received");
    send(pk, "rePort$o");
    return;
  } else if (dest_addr == my_address && dynamic_cast<SwappingResult *>(msg)) {
    bubble("Swapping Result packet received");
    send(pk, "rePort$o");
    return;
  } else if (dest_addr == my_address && dynamic_cast<LinkTomographyRequest *>(msg)) {
    bubble("Link tomography request received");
    send(pk, "hmPort$o");
    return;
  } else if (dest_addr == my_address && dynamic_cast<LinkTomographyAck *>(msg)) {
    bubble("Link tomography ack received");
    send(pk, "hmPort$o");
    return;
  } else if (dest_addr == my_address && dynamic_cast<LinkTomographyRuleSet *>(msg)) {
    bubble("Link tomography rule set received");
    send(pk, "rePort$o");
    return;
  } else if (dest_addr == my_address && dynamic_cast<LinkTomographyResult *>(msg)) {
    bubble("Link tomography result received");
    send(pk, "hmPort$o");
    return;
  } else if (dest_addr == my_address && dynamic_cast<PurificationResult *>(msg)) {
    bubble("Purification result received");
    send(pk, "rePort$o");
    return;
  } else if (dest_addr == my_address && dynamic_cast<StopEmitting *>(msg)) {
    send(pk, "rePort$o");
    return;
  } else if (dest_addr == my_address && dynamic_cast<OspfPacket *>(msg)) {
    send(pk, "rdPort$o");
    return;
  }

  // RoutingDaemon sends hello packet without desination specified
  if (dest_addr == unidentified_destination && dynamic_cast<OspfHelloPacket *>(msg)) {
    handleOspfHelloPacket(msg);
    return;
  }

  // Check if packet is reachable
  if (!routing_table.count(dest_addr)) {
    std::cout << "In Node[" << my_address << "]Address... " << dest_addr << " unreachable, discarding packet " << pk->getName() << endl;
    delete pk;
    error("Router couldn't find the path. Shouldn't happen. Or maybe the router does not understand the packet.");
    return;
  }

  int out_gate_index = routing_table.at(dest_addr);
  pk->setHopCount(pk->getHopCount() + 1);
  send(pk, "toQueue", out_gate_index);
}

void Router::handleOspfHelloPacket(cMessage *msg) {
  auto pk = dynamic_cast<OspfHelloPacket *>(msg);
  if (!parentModuleIsQNode()) {
    nonQNodeForwardOspfPacket(pk);
    return;
  }

  const bool dst_is_this_node = (pk->getSrcAddr() != my_address);
  if (dst_is_this_node) {
    redirectOspfHelloPacketToRoutingDaemon(pk);
  } else {
    sendOspfHelloPacketToQueue(pk);
  }
}

bool Router::parentModuleIsQNode() { return provider.getNode()->getModuleType() == cModuleType::get("modules.QNode"); }

/**
 * @details Unlike QNodes, BSA nodes are connected to only two nodes (at least that is the assumption)
 *          So this function simulates BSA nodes receiving packets from one node, and sending them to the other node.
 */
void Router::nonQNodeForwardOspfPacket(OspfPacket *pk) {
  pk->setHopCount(pk->getHopCount() + 1);
  const int gate_index_to_pk_src = pk->getArrivalGate()->getIndex();
  const int gate_index_to_pk_dst = gate_index_to_pk_src == 0 ? 1 : 0;
  send(pk, "toQueue", gate_index_to_pk_dst);
}

void Router::sendOspfHelloPacketToQueue(OspfPacket *pk) {
  pk->setHopCount(pk->getHopCount() + 1);
  const int gate_index_to_pk_dst = pk->getSendingGateIndex();
  send(pk, "toQueue", gate_index_to_pk_dst);
}

void Router::redirectOspfHelloPacketToRoutingDaemon(OspfPacket *pk) { send(pk, "rdPort$o"); }

}  // namespace quisp::modules

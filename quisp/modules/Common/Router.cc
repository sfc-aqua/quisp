/** \file Router.cc
 *  \authors takaakimatsuo
 *
 *  \brief Router
 */
#include "Router.h"
#include "messages/base_messages_m.h"
#include "messages/classical_messages.h"  //Path selection: type = 1, Timing notifier for BMA: type = 4
#include "messages/ospf_messages_m.h"

using namespace omnetpp;
using namespace quisp::messages;

namespace quisp::modules {

Router::Router() : provider(utils::ComponentProvider{this}) {}

void Router::initialize() {
  my_address = provider.getNodeAddr();

  ospfSendNeighbors();

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
  if (auto pk = dynamic_cast<OspfHelloPacket *>(msg)) {
    return ospfHandleHelloPacket(pk);
  }

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
  }

  // Check if packet is reachable
  auto it = routing_table.find(dest_addr);
  if (it == routing_table.end()) {
    std::cout << "In Node[" << my_address << "]Address... " << dest_addr << " unreachable, discarding packet " << pk->getName() << endl;
    delete pk;
    error("Router couldn't find the path. Shoudn't happen. Or maybe the router does not understand the packet.");
    return;
  }

  int out_gate_index = (*it).second;
  pk->setHopCount(pk->getHopCount() + 1);
  send(pk, "toQueue", out_gate_index);
}

void Router::ospfHandleHelloPacket(OspfHelloPacket *pk) {
  auto src = pk->getSrcAddr();

  if (ospfMyAddressIsRecognizedByNeighbor(pk) == false && ospfNeighborIsRegistered(src)) {
    error(
        "OspfHelloPacket error: Router%d does not recognize Router%d, \
         but Router%d is already registered by Router %d, this should not happen",
        src, my_address, src, my_address);
  }

  if (ospfMyAddressIsRecognizedByNeighbor(pk) && ospfNeighborIsRegistered(src)) {
    if (neighbor_table[src].state != OspfState::INIT) {
      error("neighbor_table[%d].state expected to be OspfState::INIT or 1, but it's %d", src, neighbor_table[src].state);
    }

    neighbor_table[src].state = OspfState::TWO_WAY;
    return;
  }

  if (ospfMyAddressIsRecognizedByNeighbor(pk) == false && ospfNeighborIsRegistered(src) == false) {
    ospfRegisterNeighbor(pk, OspfState::INIT);
  } else if (ospfMyAddressIsRecognizedByNeighbor(pk) && ospfNeighborIsRegistered(src) == false) {
    ospfRegisterNeighbor(pk, OspfState::TWO_WAY);
  }
  auto gate_index = pk->getArrivalGate()->getIndex();
  ospfSendNeighbor(gate_index);
  return;
}

void Router::ospfRegisterNeighbor(Header *pk, OspfState state) {
  auto src = pk->getSrcAddr();
  auto gate_index = pk->getArrivalGate()->getIndex();
  neighbor_table[src] = OspfNeighborInfo(gate_index, state);
}

void Router::ospfSendNeighbors() {
  size_t num_neighbors = getNumNeighbors();

  for (size_t i = 0; i < num_neighbors; i++) {
    ospfSendNeighbor(i);
  }
}

void Router::ospfSendNeighbor(int gate_index) {
  OspfHelloPacket *msg = new OspfHelloPacket;
  msg->setSrcAddr(this->my_address);
  for (auto registered_neighbor : neighbor_table) {
    msg->appendNeighbors(registered_neighbor.first);
  }
  send(msg, "toQueue", gate_index);
}

size_t Router::getNumNeighbors() const {
  char dummy;
  auto desc = gateDesc("toQueue", dummy);
  return desc->gateSize();
}

bool Router::ospfNeighborIsRegistered(int address) { return static_cast<bool>(neighbor_table.count(address)); }

bool Router::ospfMyAddressIsRecognizedByNeighbor(OspfHelloPacket *msg) {
  for (size_t i = 0; i < msg->getNeighborsArraySize(); i++) {
    if (my_address == msg->getNeighbors(i)) return true;
  }
  return false;
}

}  // namespace quisp::modules

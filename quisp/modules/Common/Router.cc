/** \file Router.cc
 *  \authors takaakimatsuo
 *
 *  \brief Router
 */
#include "Router.h"
#include "messages/classical_messages.h"  //Path selection: type = 1, Timing notifier for BMA: type = 4

using namespace omnetpp;
using namespace quisp::messages;

namespace quisp::modules {

Router::Router() : provider(utils::ComponentProvider{this}) {}

void Router::initialize() {
  my_address = provider.getNodeAddr();

  // Topology creation for routing table
  cTopology *topo = new cTopology("topo");

  // Any node that has a parameter included_in_topology will be included in routing
  topo->extractByParameter("included_in_topology", "\"yes\"");

  // If no node with the parameter & value found, do nothing.
  if (topo->getNumNodes() == 0 || topo == nullptr) {
    return;
  }

  cTopology::Node *thisNode = topo->getNodeFor(getParentModule());  // The parent node with this specific router

  // Initialize channel weights for all existing links.
  for (int x = 0; x < topo->getNumNodes(); x++) {  // Traverse through all nodes
    // For Bidirectional channels, parameters are stored in LinkOut not LinkIn.
    for (int j = 0; j < topo->getNode(x)->getNumOutLinks(); j++) {  // Traverse through all links from a specific node.
      double channel_cost = topo->getNode(x)->getLinkOut(j)->getLocalGate()->getChannel()->par("cost");  // Get assigned cost for each channel written in .ned file

      if (strstr(topo->getNode(x)->getLinkOut(j)->getLocalGate()->getFullName(), "quantum")) {
        // Ignore quantum link in classical routing table
        topo->getNode(x)->getLinkOut(j)->disable();
      } else {
        // Otherwise, keep the classical channels and set the weight
        topo->getNode(x)->getLinkOut(j)->setWeight(channel_cost);  // Set channel weight
      }
    }
  }

  // Traverse through all the destinations from the thisNode
  for (int i = 0; i < topo->getNumNodes(); i++) {
    // skip the node that is running this specific router app
    if (topo->getNode(i) == thisNode) continue;

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

  delete topo;
}

void Router::handleMessage(cMessage *msg) {
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

}  // namespace quisp::modules

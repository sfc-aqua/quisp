/** \file Router.cc
 *  \authors takaakimatsuo
 *
 *  \brief Router
 */
#include "Router.h"
#include "messages/classical_messages.h"  //Path selection: type = 1, Timing notifier for BMA: type = 4
#include "types/QNodeAddr.h"

using namespace omnetpp;
using namespace quisp::messages;
using namespace quisp::types;

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
  // Traverse through all nodes
  for (int x = 0; x < topo->getNumNodes(); x++) {
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

  // auto *node = topo->getNodeFor(provider.getNode());
  // auto num_links = node->getNumOutLinks();
  // for (int i = 0; i < num_links; i++) {
  //   auto *link = node->getLinkOut(i);
  //   auto *mod= node->getLinkOut(i)->getRemoteGate()->getNextGate()->getOwnerModule();
  //   // auto *mod = link->getRemoteNode()->getModule();

  //   std::cout << mod ->getFullName() << std::endl;
  // }

  {
    auto *node = provider.getNode()->getSubmodule("qrsa");
    if (node != nullptr) {
      auto available_addr_list = provider.getAvailableAddresses();
      int number_of_qnics = node->par("number_of_qnics");
      int number_of_qnics_r = node->par("number_of_qnics_r");
      int number_of_qnics_rp = node->par("number_of_qnics_rp");
      for (int i = 0; i < number_of_qnics; i++) {
        auto *qnic = provider.getQNIC(i, QNIC_E);
        auto addr_str = qnic->gate("qnic_quantum_port$o")->getNextGate()->getNextGate()->getOwnerModule()->par("address").stringValue();
        auto n_addr = QNodeAddr{addr_str};
        bool in_network = false;
        if (my_address.network_addr != n_addr.network_addr) {
          for (auto &a : available_addr_list) {
            if (a.network_addr == n_addr.network_addr) {
              std::cout << my_address << ":" << a << ": " << qnic->getFullPath() << " : gate index:" << qnic->getIndex() << " addr:" << addr_str << std::endl;
              in_network = true;
              gate_network_map[qnic->getIndex()] = n_addr.network_addr;
              break;
            }
          }
        }
        if (!in_network) {
          gate_network_map[qnic->getIndex()] = my_address.network_addr;
          std::cout << my_address << ": " << qnic->getFullPath() << " : " << addr_str << std::endl;
        }
      }
      for (int i = 0; i < number_of_qnics_r; i++) {
        auto *qnic = provider.getQNIC(i, QNIC_R);
        auto addr_str = qnic->gate("qnic_quantum_port$o")->getNextGate()->getNextGate()->getOwnerModule()->par("address").stringValue();
        std::cout << my_address << ": " << qnic->getFullPath() << " : " << addr_str << std::endl;
      }
    }

    std::cout << "----" << std::endl;
    for (auto [gate_i, network_addr] : gate_network_map) {
      std::cout << my_address << ": gate_index: " << gate_i << ", network:" << network_addr << std::endl;
    }
    std::cout << "----" << std::endl;
  }
  // auto * node = provider.getNode();

  // node->gate("qnic_quantum_port$o")

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
    auto address = QNodeAddr{topo->getNode(i)->getModule()->par("address").stringValue()};

    // if available_addresses parameter set
    if (topo->getNode(i)->getModule()->findPar("available_addresses") != -1) {
      auto address_str_list = ((cValueArray *)topo->getNode(i)->getModule()->par("available_addresses").objectValue())->asStringVector();
      std::vector<QNodeAddr> addresses = {};
      for (auto &s : address_str_list) {
        auto addr = QNodeAddr{s.c_str()};
        addresses.push_back(addr);
        routing_table[addr] = gateIndex;
      }
    }

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

  auto dest_addr = pk->getDestAddr();

  // If destination is this node: Path selection
  if (dest_addr == my_address) {
    handlePacketForThisNode(msg);
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
  auto out_network = gate_network_map.find(out_gate_index);
  if (out_network != gate_network_map.end()) {
    // if the packet is going to another network
  }
  pk->setHopCount(pk->getHopCount() + 1);
  send(pk, "toQueue", out_gate_index);
}

void Router::handlePacketForThisNode(omnetpp::cMessage *msg) {
  if (msg->getKind() == 1) {
    send(msg, "toApp");
    return;
  }
  if (dynamic_cast<BSMTimingNotification *>(msg)) {  // Timing for BSM
    bubble("Timing Notifier from BSA (stand-alone or internal) received");
    send(msg, "rePort$o");  // send to Application locally
    return;
  }
  if (dynamic_cast<EPPStimingNotifier *>(msg)) {  // Timing for BSM
    bubble("Timing Notifier from EPPS received");
    send(msg, "rePort$o");  // send to Application locally
    return;
  }
  if (dynamic_cast<ConnectionSetupRequest *>(msg)) {
    bubble("Connection setup request received");
    send(msg, "cmPort$o");
    return;
  }
  if (dynamic_cast<ConnectionSetupResponse *>(msg)) {
    bubble("Connection setup response received");
    send(msg, "cmPort$o");
    return;
  }
  if (dynamic_cast<RejectConnectionSetupRequest *>(msg)) {
    bubble("Reject connection setup response received");
    send(msg, "cmPort$o");
    return;
  }
  if (dynamic_cast<InternalRuleSetForwarding *>(msg)) {
    bubble("Internal RuleSet Forwarding packet received");
    send(msg, "rePort$o");
    return;
  }
  if (dynamic_cast<InternalRuleSetForwarding_Application *>(msg)) {
    bubble("Internal RuleSet Forwarding Application packet received");
    send(msg, "rePort$o");
    return;
  }
  if (dynamic_cast<SwappingResult *>(msg)) {
    bubble("Swapping Result packet received");
    send(msg, "rePort$o");
    return;
  }
  if (dynamic_cast<LinkTomographyRequest *>(msg)) {
    bubble("Link tomography request received");
    send(msg, "hmPort$o");
    return;
  }
  if (dynamic_cast<LinkTomographyAck *>(msg)) {
    bubble("Link tomography ack received");
    send(msg, "hmPort$o");
    return;
  }
  if (dynamic_cast<LinkTomographyRuleSet *>(msg)) {
    bubble("Link tomography rule set received");
    send(msg, "rePort$o");
    return;
  }
  if (dynamic_cast<LinkTomographyResult *>(msg)) {
    bubble("Link tomography result received");
    send(msg, "hmPort$o");
    return;
  }
  if (dynamic_cast<PurificationResult *>(msg)) {
    bubble("Purification result received");
    send(msg, "rePort$o");
    return;
  }
  if (dynamic_cast<StopEmitting *>(msg)) {
    send(msg, "rePort$o");
    return;
  }
}
}  // namespace quisp::modules

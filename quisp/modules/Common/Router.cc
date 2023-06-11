/** \file Router.cc
 *  \authors takaakimatsuo
 *
 *  \brief Router
 */
#include "Router.h"
#include <vector>
#include "messages/classical_messages.h"  //Path selection: type = 1, Timing notifier for BMA: type = 4

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

  if (auto pk = dynamic_cast<OspfDbdPacket *>(msg)) {
    return ospfHandleDbdPacket(pk);
  }

  if (auto pk = dynamic_cast<OspfLsrPacket *>(msg)) {
    return ospfHandleLinkStateRequest(pk);
  }

  if (auto pk = dynamic_cast<OspfLsuPacket*>(msg)) {
    return ospfHandleLinkStateUpdate(pk);
  }

  if (auto pk = dynamic_cast<OspfLsAckPacket*>(msg)) {
    return;
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
    error("Router couldn’t find the path. Shoudn’t happen. Or maybe the router does not understand the packet.");
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
      error("neighbor_table[%d].state expected to be OspfState::INIT or 1, but it’s %d", src, neighbor_table[src].state);
    }

    neighbor_table[src].state = OspfState::TWO_WAY;
    neighbor_table[src].state = OspfState::EXSTART;

    auto i_wanna_be_master_msg = ospfCreateExstartDbdPacket(true);
    send(i_wanna_be_master_msg, "toQueue", neighbor_table[src].gate_index);
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

void Router::ospfHandleDbdPacket(OspfDbdPacket *pk) {
  if (pk->getState() == OspfState::EXSTART) {
    return ospfExStartState(pk);
  } else if (pk->getState() == OspfState::EXCHANGE) {
    auto src = pk->getSrcAddr();

    if (pk->getIs_master()) {
      ospfRespondToExchangeStateMater(src);
    }
    if (pk->getLsdbArraySize()) {
      ospfSendLinkStateRequest(pk);
    }
    return;
  }
}

void Router::ospfExStartState(OspfDbdPacket *pk) {
  auto src = pk->getSrcAddr();
  if (pk->getIs_master()) {
    return ospfDecideMaster(src);
  }
   // i am master
  bool exchange_state_is_initiated = (neighbor_table[src].state == OspfState::EXCHANGE);
  if (exchange_state_is_initiated) return;
  ospfInitiateExchangeState(src);
}

void Router::ospfInitiateExchangeState(int dest) {
  neighbor_table[dest].state = OspfState::EXCHANGE;
  ospfSendLsdbSummary(dest, true);
}

void Router::ospfRespondToExchangeStateMater(int dest) {
  neighbor_table[dest].state = OspfState::EXCHANGE;
  ospfSendLsdbSummary(dest);
}

void Router::ospfDecideMaster(int neighbor) {
  if (my_address > neighbor) {
    auto i_am_master_msg = ospfCreateExstartDbdPacket(true);
    send(i_am_master_msg, "toQueue", neighbor_table[neighbor].gate_index);
  } else {
    auto i_am_slave_msg = ospfCreateExstartDbdPacket(false);
    send(i_am_slave_msg, "toQueue", neighbor_table[neighbor].gate_index);
  }
}

void Router::ospfSendLinkStateRequest(OspfDbdPacket *pk) {
  auto src = pk->getSrcAddr();
  neighbor_table[src].state = OspfState::LOADING;

  std::vector<int> missing_lsas = identifyMissingRouterInfo(pk);

  if (missing_lsas.size() > 0) {
    OspfLsrPacket* request = new OspfLsrPacket;
    request->setSrcAddr(my_address);
    for (auto router_id : missing_lsas) {
      request->appendRequested_router_info(router_id);
    }
    send(request, "toQueue", neighbor_table[src].gate_index);
  }
}

void Router::ospfHandleLinkStateRequest(OspfLsrPacket* pk) {
  OspfLsuPacket* lsu = new OspfLsuPacket;
  lsu->setSrcAddr(my_address);

  for (size_t i = 0; i < pk->getRequested_router_infoArraySize(); i++) {
    LinkStateAdvertisement lsa = LinkStateDatabase[pk->getRequested_router_info(i)];
    lsu->appendLsas(lsa);
  }
  send(lsu, "toQueue", neighbor_table[pk->getSrcAddr()].gate_index);
}

void Router::ospfHandleLinkStateUpdate(OspfLsuPacket *pk) {
  OspfLsAckPacket *ack = new OspfLsAckPacket;
  send(ack, "toQueue", neighbor_table[pk->getSrcAddr()].gate_index);

  ospfUpdateLinkStateDatabase(pk);
  sendUpdatedLsdbToNeighboringRouters(pk->getSrcAddr());
}

void Router::ospfUpdateLinkStateDatabase(OspfLsuPacket* pk) {
  neighbor_table[pk->getSrcAddr()].state = OspfState::FULL;

  for (size_t i = 0; i < pk->getLsasArraySize(); i++) {
    LinkStateAdvertisement lsa = pk->getLsas(i);
    auto origin = lsa.lsa_origin_id;
    if (LinkStateDatabase.count(origin)) lsa.lsa_age++;
    LinkStateDatabase[origin] = lsa;
  }
}

void Router::sendUpdatedLsdbToNeighboringRouters(int source_of_updated_lsdb) {
  for (auto neighbor : neighbor_table) {
    if (neighbor.first == source_of_updated_lsdb) continue;
    ospfSendLsdbSummary(neighbor.first);
  }
}

OspfDbdPacket *Router::ospfCreateExstartDbdPacket(bool is_master) {
  OspfDbdPacket *msg = new OspfDbdPacket;
  msg->setSrcAddr(my_address);
  msg->setDd_sequence(my_dd_sequence);
  msg->setState(OspfState::EXSTART);
  msg->setIs_master(is_master);
  return msg;
}

void Router::ospfSendLsdbSummary(int dest, bool i_am_master) {
  OspfDbdPacket *msg = new OspfDbdPacket;
  msg->setSrcAddr(my_address);
  msg->setState(OspfState::EXCHANGE);
  ospfAppendLsdbSummaryToPacket(msg);
  msg->setIs_master(i_am_master);
  send(msg, "toQueue", neighbor_table[dest].gate_index);
}

std::vector<int> Router::identifyMissingRouterInfo(OspfDbdPacket *pk) {
  std::vector<int> missing_lsas;
  for (size_t i = 0; i < pk->getLsdbArraySize(); i++) {
    LinkStateAdvertisement summary_lsa = pk->getLsdb(i);
    auto lsa_origin = summary_lsa.lsa_origin_id;
    auto lsa_age = summary_lsa.lsa_age;
    if (LinkStateDatabase.count(lsa_origin) == false || LinkStateDatabase[lsa_origin].lsa_age < lsa_age) {
      missing_lsas.push_back(lsa_origin);
    }
  }
  return missing_lsas;
}

void Router::ospfAddMyAddressLsaToLsdb() {
  LinkStateDatabase[my_address].lsa_age = 0;
  LinkStateDatabase[my_address].lsa_origin_id = my_address;
  LinkStateDatabase[my_address].lsa_id = my_address;
  for (auto neighbor : neighbor_table) {
    LinkStateDatabase[my_address].neighbor_nodes.push_back(neighbor.second);
  }
}

void Router::ospfAppendLsdbSummaryToPacket(OspfDbdPacket *msg) {
  if (LinkStateDatabase.count(my_address) == 0) {
    ospfAddMyAddressLsaToLsdb();
  }

  for (auto lsa : LinkStateDatabase) {
    LinkStateAdvertisement summary_lsa = lsa.second;
    // LSDB summary only requires LSA origin and LSA age
    // clear neighbor_nodes from summary_lsa to reduce packet size
    summary_lsa.neighbor_nodes.clear();
    msg->appendLsdb(summary_lsa);
  }
}

void Router::ospfRegisterNeighbor(Header *pk, OspfState state) {
  auto src = pk->getSrcAddr();
  auto gate_index = pk->getArrivalGate()->getIndex();
  double link_cost = provider.getQNode()->gate("port$o", gate_index)->getChannel()->par("cost");
  neighbor_table[src] = OspfNeighborInfo(src, gate_index, state, link_cost);
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

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

  run_ospf = par("run_ospf");

  if (run_ospf) {
    ospfInitializeRouter();
  } else {
    // Topology creation for routing table
    auto topo = provider.getTopologyForRouter();

    // If no node with the parameter & value found, do nothing.
    if (topo->getNumNodes() == 0 || topo == nullptr) {
      return;
    }

    generateRoutingTable(topo);
  }
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

  if (auto pk = dynamic_cast<OspfLsuPacket *>(msg)) {
    ospfHandleLinkStateUpdate(pk);
    // check if pending messages can be sent now that we have new routing_table
    if (unrecognizable_destination_messages.size()) handlePendingMessages();
    return;
  }

  if (auto pk = dynamic_cast<OspfLsAckPacket *>(msg)) {
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
  if (routing_table.count(dest_addr) == false) {
    // push back to vecor and see if we can send it later when routing_table is updated
    unrecognizable_destination_messages.push_back(pk);
    return;
  }

  // unrecognizable_destination_messages must be sent when LSDB is updated.
  // If they are not sent at this point, that means there is some kind of error.
  if (unrecognizable_destination_messages.size()) {
    std::cout << "In Node[" << my_address << "]Address... " << dest_addr << " unreachable, discarding packet " << pk->getName() << endl;
    delete pk;
    error("Router couldn’t find the path. Shoudn’t happen. Or maybe the router does not understand the packet.");
    return;
  }

  sendToDestination(pk);
}

void Router::generateRoutingTable() { routing_table = link_state_database.generateRoutingTableFromGraph(my_address); }

void Router::sendToDestination(Header *pk) {
  int dest_addr = pk->getDestAddr();
  int out_gate_index = routing_table.at(dest_addr);
  pk->setHopCount(pk->getHopCount() + 1);
  send(pk, "toQueue", out_gate_index);
}

void Router::handlePendingMessages() {
  auto itr = unrecognizable_destination_messages.begin();
  while (itr != unrecognizable_destination_messages.end()) {
    auto msg = (*itr);
    Header *pk = check_and_cast<Header *>(msg);
    int dest_addr = pk->getDestAddr();
    if (routing_table.count(dest_addr)) {
      sendToDestination(pk);
      unrecognizable_destination_messages.erase(itr);
    } else
      itr++;
  }
}

size_t Router::getNumNeighbors() const {
  char dummy;
  const auto desc = gateDesc("toQueue", dummy);
  return desc->gateSize();
}

void Router::ospfHandleHelloPacket(const OspfHelloPacket *const pk) {
  const int src = pk->getSrcAddr();

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

    ospfSendExstartDbdPacket(src, true);
    return;
  }

  if (ospfMyAddressIsRecognizedByNeighbor(pk) == false && ospfNeighborIsRegistered(src) == false) {
    ospfRegisterNeighbor(pk, OspfState::INIT);
  } else if (ospfMyAddressIsRecognizedByNeighbor(pk) && ospfNeighborIsRegistered(src) == false) {
    ospfRegisterNeighbor(pk, OspfState::TWO_WAY);
  }
  const int gate_index = pk->getArrivalGate()->getIndex();
  ospfSendHelloPacketToNeighbor(gate_index);
  return;
}

void Router::ospfInitializeRouter() {
  const size_t num_neighbors = getNumNeighbors();

  for (size_t i = 0; i < num_neighbors; i++) {
    ospfSendHelloPacketToNeighbor(i);
  }
}

void Router::ospfSendHelloPacketToNeighbor(int gate_index) {
  OspfHelloPacket *msg = new OspfHelloPacket;
  msg->setSrcAddr(this->my_address);
  msg->setNeighbor_table(neighbor_table);
  send(msg, "toQueue", gate_index);
}

bool Router::ospfMyAddressIsRecognizedByNeighbor(const OspfHelloPacket *const msg) {
  for (const auto neighbor_entry : msg->getNeighbor_table()) {
    int neighbor_id = neighbor_entry.first;
    if (my_address == neighbor_id) return true;
  }
  return false;
}

void Router::ospfRegisterNeighbor(const Header *const pk, OspfState state) {
  const int src = pk->getSrcAddr();
  const int gate_index = pk->getArrivalGate()->getIndex();
  // Router module only takes the cost of non quantum channel
  const double link_cost = provider.getNode()->gate("port$o", gate_index)->getChannel()->par("cost");
  neighbor_table[src] = OspfNeighborInfo(src, gate_index, state, link_cost);
  ospfUpdateMyAddressLsaInLsdb();
}

bool Router::ospfNeighborIsRegistered(int address) const { return static_cast<bool>(neighbor_table.count(address)); }

void Router::ospfHandleDbdPacket(const OspfDbdPacket *const pk) {
  if (pk->getState() == OspfState::EXSTART) {
    return ospfExStartState(pk);
  } else if (pk->getState() == OspfState::EXCHANGE) {
    const int src = pk->getSrcAddr();

    if (bool i_am_master = (!pk->getIs_master())) {
      ospfMasterEnterExchangeState(src);
    }

    if (pk->getLsdb().empty()) error("Router::ospfHandleDbdPacket: expected LSDB to be not empty, but it is");

    const RouterIds missing_lsa_ids = link_state_database.identifyMissingLinkStateAdvertisementId(pk->getLsdb());
    if (missing_lsa_ids.size() > 0) {
      ospfSendLinkStateRequest(pk->getSrcAddr(), missing_lsa_ids);
    } else {
      neighbor_table[pk->getSrcAddr()].state = OspfState::FULL;
    }

    return;
  }
}

void Router::ospfExStartState(const OspfDbdPacket *const pk) {
  const int src = pk->getSrcAddr();
  if (my_address > src) {
    bool i_am_master = true;
    ospfSendExstartDbdPacket(src, i_am_master);
    return;
  } else if (my_address < src) {
    const bool exchange_state_is_initiated = (neighbor_table[src].state == OspfState::EXCHANGE);
    if (exchange_state_is_initiated) return;
    ospfSlaveInitiateExchangeState(src);
  } else {
    error("Cannot decide master slave relationship");
  }
}

void Router::ospfSendExstartDbdPacket(NodeAddr neighbor, bool is_master) {
  OspfDbdPacket *msg = new OspfDbdPacket;
  msg->setSrcAddr(my_address);
  msg->setState(OspfState::EXSTART);
  msg->setIs_master(is_master);
  send(msg, "toQueue", neighbor_table[neighbor].gate_index);
}

void Router::ospfSlaveInitiateExchangeState(int dest) {
  neighbor_table[dest].state = OspfState::EXCHANGE;
  ospfSendLsdbSummary(dest);
}

void Router::ospfMasterEnterExchangeState(int dest) {
  neighbor_table[dest].state = OspfState::EXCHANGE;
  ospfSendLsdbSummary(dest, true);
}

void Router::ospfSendLsdbSummary(int dest, bool i_am_master) {
  OspfDbdPacket *msg = new OspfDbdPacket;
  msg->setSrcAddr(my_address);
  msg->setState(OspfState::EXCHANGE);
  LinkStateDatabaseSummary lsdb_summary = link_state_database.getLinkStateDatabaseSummary();
  msg->setLsdb(lsdb_summary);
  msg->setIs_master(i_am_master);
  send(msg, "toQueue", neighbor_table[dest].gate_index);
}

void Router::ospfSendLinkStateRequest(int dst, const RouterIds &missing_lsa_ids) {
  neighbor_table[dst].state = OspfState::LOADING;

  OspfLsrPacket *request = new OspfLsrPacket;
  request->setSrcAddr(my_address);
  request->setIds_of_requested_lsa(missing_lsa_ids);
  send(request, "toQueue", neighbor_table[dst].gate_index);
}

void Router::ospfHandleLinkStateRequest(const OspfLsrPacket *const pk) {
  OspfLsuPacket *lsu = new OspfLsuPacket;
  lsu->setSrcAddr(my_address);

  const RouterIds ids_of_requested_lsa = pk->getIds_of_requested_lsa();
  const LinkStateUpdate lsas = link_state_database.getLinkStateUpdatesFor(ids_of_requested_lsa, my_address);
  lsu->setLsas(lsas);
  send(lsu, "toQueue", neighbor_table[pk->getSrcAddr()].gate_index);
}

void Router::ospfHandleLinkStateUpdate(const OspfLsuPacket *const pk) {
  OspfLsAckPacket *ack = new OspfLsAckPacket;
  send(ack, "toQueue", neighbor_table[pk->getSrcAddr()].gate_index);

  neighbor_table[pk->getSrcAddr()].state = OspfState::FULL;
  ospfUpdateLinkStateDatabase(pk);
  ospfSendUpdatedLsdbToNeighboringRouters(pk->getSrcAddr());
  generateRoutingTable();
}

void Router::ospfUpdateLinkStateDatabase(const OspfLsuPacket *const pk) {
  LinkStateUpdate lsu = pk->getLsas();
  for (LinkStateAdvertisement &lsa : lsu) {
    link_state_database.updateLinkStateDatabase(lsa);
  }
}

void Router::ospfSendUpdatedLsdbToNeighboringRouters(int source_of_updated_lsdb) {
  for (const auto neighbor_entry : neighbor_table) {
    const int neighbor_id = neighbor_entry.first;
    if (neighbor_id == source_of_updated_lsdb) continue;
    ospfSendLsdbSummary(neighbor_id, true);
  }
}

void Router::ospfUpdateMyAddressLsaInLsdb() {
  LinkStateAdvertisement my_lsa{my_address, my_address, neighbor_table};
  if (link_state_database.hasLinkStateAdvertisementOf(my_address)) {
    int curr_lsa_age = link_state_database.getLinkStateAdvertisementOf(my_address).lsa_age;
    my_lsa.lsa_age = curr_lsa_age + 1;
  }
  link_state_database.updateLinkStateDatabase(my_lsa);
}
}  // namespace quisp::modules

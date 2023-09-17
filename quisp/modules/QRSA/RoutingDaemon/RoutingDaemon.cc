/** \file RoutingDaemon.cc
 *  \authors takaakimatsuo
 *
 *  \brief RoutingDaemon
 */
#include "RoutingDaemon.h"

#include <vector>

#include "messages/classical_messages.h"
#include "modules/PhysicalConnection/BSA/BSAController.h"
#include "modules/QNIC.h"
#include "modules/QRSA/RoutingDaemon/IRoutingDaemon.h"
#include "omnetpp/cexception.h"
#include "test_utils/QNode.h"

using namespace omnetpp;

namespace quisp::modules::routing_daemon {

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

RoutingDaemon::RoutingDaemon() : provider(utils::ComponentProvider{this}) {}

void RoutingDaemon::initialize(int stage) {
  if (stage >= 1) return;

  my_address = provider.getNodeAddr();
  // Prepare neighbor table and resolve
  num_qnic = par("number_of_qnics");
  num_qnic_r = par("number_of_qnics_r");
  num_qnic_rp = par("number_of_qnics_rp");
  qnic_num_map.insert(std::make_pair(QNIC_E, num_qnic));
  qnic_num_map.insert(std::make_pair(QNIC_R, num_qnic_r));
  qnic_num_map.insert(std::make_pair(QNIC_RP, num_qnic_rp));
  prepareQnicAddrMap();

  run_ospf = par("run_ospf");

  if (run_ospf) {
    ospfInitializeRoutingDaemon();
  } else {
    // Topology creation for routing table
    auto topo = provider.getTopologyForRoutingDaemon(this);

    // If no node with the parameter & value found, do nothing.
    if (topo->getNumNodes() == 0 || topo == nullptr) {
      return;
    }
    generateRoutingTable(topo);
    prepareNeighborAddressTableWithTopologyInfo();
  }
}

/**
 * Once we begin using dynamic routing protocols, this is where the messages
 * will be handled.  This perhaps will also be how we communicate with the
 * other important daemons in the qrsa.
 * TODO Handle dynamic routing protocol messages.
 **/
void RoutingDaemon::handleMessage(cMessage *msg) {
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
    return ospfHandleLinkStateUpdate(pk);
  }

  if (auto pk = dynamic_cast<OspfLsAckPacket *>(msg)) {
    return;
  }
}

void RoutingDaemon::generateRoutingTable() {
  qrtable = link_state_database.generateRoutingTableFromGraph(my_address);
  resolveQuantumInterfaceInfo();
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
    int dest_addr = node->getModule()->par("address");

    qrtable[dest_addr] = getQNicAddr(parentModuleGate);

    if (!strstr(parentModuleGate->getFullName(), "quantum")) {
      error("Quantum routing table referring to classical gates...");
    }
  }
  resolveQuantumInterfaceInfo();
}

std::vector<int> RoutingDaemon::getNeighborAddresses() {
  std::vector<int> neighbors;
  if (run_ospf) {
    for (const auto &neighbor : neighbor_table) {
      neighbors.push_back(neighbor.first);
    }
  } else {
    neighbors = neighbor_addresses;
  }
  return neighbors;
}

// This function is called in finish() in HardwareMonitor to convert
// node address into module name such as EndNode1.
std::string RoutingDaemon::getModuleNameByAddress(int module_address) {
  auto *topology = provider.getTopologyForRoutingDaemon(this);
  auto num_nodes = topology->getNumNodes();
  for (int i = 0; i < num_nodes; i++) {
    auto node = topology->getNode(i);
    if (node->getModule()->par("address").intValue() == module_address) {
      return node->getModule()->getFullName();
    };
  }
  error("Module not found for address %d", module_address);
}

void RoutingDaemon::prepareQnicAddrMap() {
  // create map between address and type, index for later use
  std::vector<QNIC_type> qnic_types = {QNIC_E, QNIC_R, QNIC_RP};

  // 1. Go through all the qnics
  for (auto qnic_type : qnic_types) {
    for (int qnic_index = 0; qnic_index < qnic_num_map[qnic_type]; qnic_index++) {
      cModule *qnic = provider.getQNIC(qnic_index, qnic_type);
      // If this qnic's naighbor is the target neighbor, finish and return qnic address
      qnic_addr_map.insert(std::make_pair(qnic->par("self_qnic_address").intValue(), std::make_tuple(qnic_type, qnic_index)));
    }
  }
}

// create a map from destination address to quantum interface information
void RoutingDaemon::resolveQuantumInterfaceInfo() {
  std::cout << "resolving interface" << qrtable.size() << "\n";
  // Routing table should already be prepared
  for (const auto &dest_qnic_address : qrtable) {
    auto qnic_address = dest_qnic_address.second;
    auto dest_addr = dest_qnic_address.first;
    std::cout << "qnic_address: " << qnic_address << "\n";
    std::cout << "dest_addr: " << dest_addr << "\n";
    if (!qnic_addr_map.count(qnic_address)) {
      error("Failed to resolve quantum interface info");
    }
    auto [qnic_type, qnic_index] = qnic_addr_map[qnic_address];
    auto *qnic = provider.getQNIC(qnic_index, qnic_type);
    interface_table[dest_addr] = prepareQuantumInterfaceInfo(qnic);
  }
}

void RoutingDaemon::prepareNeighborAddressTableWithTopologyInfo() {
  for (int index = 0; index < num_qnic; index++) {
    auto *qnic = provider.getQNIC(index, QNIC_E);
    auto neighbor_address = getNeighborAddressFromQnicModule(qnic);
    neighbor_addresses.push_back(neighbor_address);
  }
  for (int index = 0; index < num_qnic_r; index++) {
    auto *qnic_r = provider.getQNIC(index, QNIC_R);
    auto neighbor_address = getNeighborAddressFromQnicModule(qnic_r);
    neighbor_addresses.push_back(neighbor_address);
  }
  for (int index = 0; index < num_qnic_rp; index++) {
    auto *qnic_rp = provider.getQNIC(index, QNIC_RP);
    auto neighbor_address = getNeighborAddressFromQnicModule(qnic_rp);
    neighbor_addresses.push_back(neighbor_address);
  }
}

QuantumInterfaceInfo RoutingDaemon::getQuantumInterfaceInfo(int dest_addr) {
  for (auto table : interface_table) {
    EV << "table: " << table.first << "\n";
  }
  if (!interface_table.count(dest_addr)) {
    error("Interface information for destination address %d not found.", dest_addr);
  }
  return interface_table[dest_addr];
}

QuantumInterfaceInfo RoutingDaemon::prepareQuantumInterfaceInfo(cModule *qnic_module) {
  auto qnic_address = qnic_module->par("self_qnic_address").intValue();
  auto qnic_type = static_cast<QNIC_type>(qnic_module->par("self_qnic_type").intValue());
  auto qnic_index = qnic_module->par("self_qnic_index").intValue();
  auto buffer_size = qnic_module->par("num_buffer").intValue();
  QuantumInterfaceInfo info;
  info.qnic.type = qnic_type;
  info.qnic.index = qnic_index;
  info.qnic.address = qnic_address;
  info.qnic.pointer = qnic_module;
  info.buffer_size = buffer_size;
  info.link_cost = 1;  // This value should be updated by link tomography in the future
  info.neighbor_address = getNeighborAddressFromQnicModule(qnic_module);
  return info;
}
/**
 * This function gets topology information from omnet module.
 * This process should be done by proper routing process in the future.
 * This function get qnic module pointer and get its neighbor address.
 */
int RoutingDaemon::getNeighborAddressFromQnicModule(const cModule *qnic_module) {
  // qnic_quantum_port$o is connected to the node's outermost quantum_port
  auto *neighbor_gate = qnic_module->gate("qnic_quantum_port$o")->getNextGate()->getNextGate();
  if (neighbor_gate == nullptr) {
    error("This qnic is not connected to any node.");
  }

  // neighbor node could be BSA, EPPS, QNode
  const cModule *neighbor_node = neighbor_gate->getOwnerModule();
  if (neighbor_node == nullptr) {
    error("neighbor node not found.");
  }

  if ((std::string)neighbor_node->getClassName() == "quisp_test::qnode::TestQNode") {
    // In the case where this node is test node, just return address
    return neighbor_node->par("address").intValue();
  }

  // Check neighbor node
  cModuleType *neighbor_node_type = neighbor_node->getModuleType();
  // Based on node type, prepare neighbor table
  if (provider.isQNodeType(neighbor_node_type)) {
    // QNode (Just take address fro neighbor_node)
    return neighbor_node->par("address").intValue();
  } else if (provider.isBSANodeType(neighbor_node_type)) {
    // BSA needs to be skipped and find one more hop further neighbor since
    // BSA is not treated as a node.
    // Get BSA controller module
    auto *bsa_controller = dynamic_cast<BSAController *>(neighbor_node->getSubmodule("bsa_controller"));
    if (bsa_controller == nullptr) {
      error("No BSA controller found");
    }

    // BSA has two ports, one for this node the other is one hop distant node.
    // This node < -- > BSA (neighbor_node) < -- > Genuine neighbor node
    int left_address = bsa_controller->getExternalAdressFromPort(0);
    int right_address = bsa_controller->getExternalAdressFromPort(1);

    // Check which port corresponds to my address
    if (left_address == my_address) {
      // port 0 corresponds to my address, means conponent on port 1 is my neighbor
      return right_address;
    } else {
      // port 1 corresponds to my address, means conponent on port 0 is my neighbor
      return left_address;
    }
  } else if (provider.isSPDCNodeType(neighbor_node_type)) {
    // SPDC
    error("To be implemented");
  } else {
    error(
        "This simulator only recognizes the following network level node "
        "types: QNode, EPPS and BSA. Not %s",
        neighbor_node->getClassName());
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

int RoutingDaemon::findQnicAddrByNeighborAddr(int neighbor_addr) {
  // This function is used when ospf is running.
  // We cannot use Quantum Interface Info at this point since qrtable is not ready.
  std::vector<QNIC_type> qnic_types = {QNIC_E, QNIC_R, QNIC_RP};
  // 1. Go through all the qnics
  for (auto qnic_type : qnic_types) {
    for (int qnic_index = 0; qnic_index < qnic_num_map[qnic_type]; qnic_index++) {
      cModule *qnic = provider.getQNIC(qnic_index, qnic_type);
      // If this qnic's naighbor is the target neighbor, finish and return qnic address
      auto neighbor = getNeighborAddressFromQnicModule(qnic);
      if (neighbor == neighbor_addr) {
        return qnic->par("self_qnic_address").intValue();
      }
    }
  }
  error("Failed to find qnic address by this neighbor address.");
}

/**
 * @brief returns the number of neighbors of this node
 * @details we are assuming
 *          two nodes are connected by quantum channel if and only if they are connected by classical channel
 * TODO: we need to change this function if above assumption no longer holds
 * @return size_t
 */
size_t RoutingDaemon::getNumNeighbors() { return provider.getNode()->gateSize("port"); }

void RoutingDaemon::ospfHandleHelloPacket(const OspfHelloPacket *const pk) {
  const NodeAddr src = pk->getSrcAddr();

  if (!ospfMyAddressIsRecognizedByNeighbor(pk) && ospfNeighborIsRegistered(src)) {
    error("OspfHelloPacket error: Router%d does not recognize Router%d, but Router%d is already registered by Router %d, this should not happen", src, my_address, src, my_address);
  } else if (ospfMyAddressIsRecognizedByNeighbor(pk) && ospfNeighborIsRegistered(src)) {
    if (neighbor_table[src].state != OspfState::INIT) error("neighbor_table[%d].state expected to be OspfState::INIT or 1, but it’s %d", src, neighbor_table[src].state);
    neighbor_table[src].state = OspfState::TWO_WAY;
    neighbor_table[src].state = OspfState::EXSTART;

    ospfSendExstartDbdPacket(src);
    return;
  } else if (!ospfMyAddressIsRecognizedByNeighbor(pk) && !ospfNeighborIsRegistered(src)) {
    ospfRegisterNeighbor(pk, OspfState::INIT);
  } else if (ospfMyAddressIsRecognizedByNeighbor(pk) && !ospfNeighborIsRegistered(src)) {
    ospfRegisterNeighbor(pk, OspfState::TWO_WAY);
  }

  ospfSendHelloPacketToNeighbor(src);
  return;
}

void RoutingDaemon::ospfInitializeRoutingDaemon() {
  const size_t num_neighbors = getNumNeighbors();
  const NodeAddr unidentified_destination = -1;

  for (size_t i = 0; i < num_neighbors; i++) {
    OspfHelloPacket *msg = new OspfHelloPacket;
    msg->setSrcAddr(this->my_address);
    msg->setNeighborTable(neighbor_table);
    msg->setSendingGateIndex(i);
    msg->setDestAddr(unidentified_destination);
    send(msg, "RouterPort$o");
  }
}

void RoutingDaemon::ospfSendHelloPacketToNeighbor(NodeAddr neighbor) {
  OspfHelloPacket *msg = new OspfHelloPacket;
  msg->setSrcAddr(this->my_address);
  msg->setNeighborTable(neighbor_table);
  msg->setDestAddr(neighbor);
  send(msg, "RouterPort$o");
}

bool RoutingDaemon::ospfMyAddressIsRecognizedByNeighbor(const OspfHelloPacket *const msg) {
  for (const auto neighbor_entry : msg->getNeighborTable()) {
    NodeAddr neighbor_id = neighbor_entry.first;
    if (my_address == neighbor_id) return true;
  }
  return false;
}

void RoutingDaemon::ospfRegisterNeighbor(const OspfPacket *const pk, OspfState state) {
  const NodeAddr src = pk->getSrcAddr();
  const int qnic_address = findQnicAddrByNeighborAddr(src);
  const double link_cost = provider.getHardwareMonitor()->getLinkCost(src);
  neighbor_table[src] = OspfNeighborInfo(src, qnic_address, state, link_cost);
  ospfUpdateMyAddressLsaInLsdb();
}

bool RoutingDaemon::ospfNeighborIsRegistered(NodeAddr address) const { return static_cast<bool>(neighbor_table.count(address)); }

void RoutingDaemon::ospfHandleDbdPacket(const OspfDbdPacket *const pk) {
  if (pk->getState() == OspfState::EXSTART) {
    return ospfExStartState(pk);
  }

  const NodeAddr src = pk->getSrcAddr();

  if (pk->getState() != OspfState::EXCHANGE) error("RoutingDaemon::ospfHandleDbdPacket: Node%d expected to be in EXCHANGE state, but it's not", src);

  if (pk->getLsdb().empty()) error("RoutingDaemon::ospfHandleDbdPacket: expected LSDB to be not empty, but it is");

  bool i_am_master = !pk->isMaster();
  if (i_am_master) {
    ospfMasterEnterExchangeState(src);
  }

  const RouterIds missing_lsa_ids = link_state_database.identifyMissingLinkStateAdvertisementId(pk->getLsdb());
  if (missing_lsa_ids.size() > 0) {
    ospfSendLinkStateRequest(src, missing_lsa_ids);
  } else {
    neighbor_table[src].state = OspfState::FULL;
  }
}

/**
 * @brief Exchange packets to decide who the master or slave is
 * @details Master/slave is decided based on the number of router address/ID.
 *          Whichever that has the bigger router address becomes the master
 *          Slave sends its Summary LSDB to Master
 *          Master send empty DBD packet until it receives Summary LSDB from Slave
 */
void RoutingDaemon::ospfExStartState(const OspfDbdPacket *const pk) {
  const NodeAddr src = pk->getSrcAddr();
  if (my_address > src) {  // i am master
    // Master send empty DBD packet until it receives Summary LSDB from Slave
    ospfSendExstartDbdPacket(src);
    return;
  } else if (my_address < src) {  // i am slave
    const bool exchange_state_is_initiated = (neighbor_table[src].state == OspfState::EXCHANGE);
    if (exchange_state_is_initiated) return;
    // Slave sends its Summary LSDB to Master
    ospfSlaveInitiateExchangeState(src);
  } else {
    error("Cannot decide master slave relationship");
  }
}

void RoutingDaemon::ospfSendExstartDbdPacket(NodeAddr neighbor) {
  OspfDbdPacket *msg = new OspfDbdPacket;
  msg->setSrcAddr(my_address);
  msg->setState(OspfState::EXSTART);
  msg->setIsMaster(true);
  msg->setDestAddr(neighbor);
  send(msg, "RouterPort$o");
}

void RoutingDaemon::ospfSlaveInitiateExchangeState(NodeAddr dest) {
  neighbor_table[dest].state = OspfState::EXCHANGE;
  ospfSendLsdbSummary(dest);
}

void RoutingDaemon::ospfMasterEnterExchangeState(NodeAddr dest) {
  neighbor_table[dest].state = OspfState::EXCHANGE;
  ospfSendLsdbSummary(dest, true);
}

void RoutingDaemon::ospfSendLsdbSummary(NodeAddr dest, bool i_am_master) {
  OspfDbdPacket *msg = new OspfDbdPacket;
  msg->setSrcAddr(my_address);
  msg->setState(OspfState::EXCHANGE);
  LinkStateDatabaseSummary lsdb_summary = link_state_database.getLinkStateDatabaseSummary();
  msg->setLsdb(lsdb_summary);
  msg->setIsMaster(i_am_master);
  msg->setDestAddr(dest);
  send(msg, "RouterPort$o");
}

void RoutingDaemon::ospfSendLinkStateRequest(NodeAddr dst, const RouterIds &missing_lsa_ids) {
  neighbor_table[dst].state = OspfState::LOADING;

  OspfLsrPacket *request = new OspfLsrPacket;
  request->setSrcAddr(my_address);
  request->setIDsOfRequestedLsa(missing_lsa_ids);
  request->setDestAddr(dst);
  send(request, "RouterPort$o");
}

void RoutingDaemon::ospfHandleLinkStateRequest(const OspfLsrPacket *const pk) {
  OspfLsuPacket *lsu = new OspfLsuPacket;
  lsu->setSrcAddr(my_address);

  const RouterIds ids_of_requested_lsa = pk->getIDsOfRequestedLsa();
  const LinkStateUpdate lsas = link_state_database.getLinkStateUpdatesFor(ids_of_requested_lsa, my_address);
  lsu->setLsas(lsas);
  lsu->setDestAddr(pk->getSrcAddr());
  send(lsu, "RouterPort$o");
}

void RoutingDaemon::ospfHandleLinkStateUpdate(const OspfLsuPacket *const pk) {
  OspfLsAckPacket *ack = new OspfLsAckPacket;
  ack->setSrcAddr(my_address);
  ack->setDestAddr(pk->getSrcAddr());
  send(ack, "RouterPort$o");

  neighbor_table[pk->getSrcAddr()].state = OspfState::FULL;
  ospfUpdateLinkStateDatabase(pk);
  ospfSendUpdatedLsdbToNeighboringRouters(pk->getSrcAddr());
  generateRoutingTable();
}

void RoutingDaemon::ospfUpdateLinkStateDatabase(const OspfLsuPacket *const pk) {
  LinkStateUpdate lsu = pk->getLsas();
  for (LinkStateAdvertisement &lsa : lsu) {
    link_state_database.updateLinkStateDatabase(lsa);
  }
}

void RoutingDaemon::ospfSendUpdatedLsdbToNeighboringRouters(NodeAddr source_of_updated_lsdb) {
  for (const auto neighbor_entry : neighbor_table) {
    const NodeAddr neighbor_id = neighbor_entry.first;
    if (neighbor_id == source_of_updated_lsdb) continue;
    ospfSendLsdbSummary(neighbor_id, true);
  }
}

void RoutingDaemon::ospfUpdateMyAddressLsaInLsdb() {
  LinkStateAdvertisement my_lsa{my_address, my_address, neighbor_table};
  if (link_state_database.hasLinkStateAdvertisementOf(my_address)) {
    int curr_lsa_age = link_state_database.getLinkStateAdvertisementOf(my_address).lsa_age;
    my_lsa.lsa_age = curr_lsa_age + 1;
  }
  link_state_database.updateLinkStateDatabase(my_lsa);
}

Define_Module(RoutingDaemon);
}  // namespace quisp::modules::routing_daemon

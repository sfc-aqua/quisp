/** \file ConnectionManager.cc
 *
 *  \brief ConnectionManager
 */

#include <string>

#include "ConnectionManager.h"
#include "RuleSetGenerator.h"

using namespace omnetpp;
using namespace quisp::messages;
using namespace quisp::rules;
using quisp::modules::ruleset_gen::RuleSetGenerator;

namespace quisp::modules {

Define_Module(ConnectionManager);
ConnectionManager::ConnectionManager() : provider(utils::ComponentProvider{this}) {}

ConnectionManager::~ConnectionManager() {
  for (auto *msg : request_send_timing) {
    cancelAndDelete(msg);
  }
  for (auto &[qnic_num, q] : connection_setup_buffer) {
    while (!q.empty()) {
      auto req = q.front();
      q.pop();
      delete req;
    }
  }
}

void ConnectionManager::initialize() {
  initializeLogger(provider);
  routing_daemon = provider.getRoutingDaemon();
  hardware_monitor = provider.getHardwareMonitor();
  my_address = provider.getNodeAddr();
  num_of_qnics = par("total_number_of_qnics");
  simultaneous_es_enabled = par("simultaneous_es_enabled");
  num_remote_purification = par("num_remote_purification");
  if (num_remote_purification > 0) {
    es_with_purify = true;
  }
  std::string pur_type = par("purification_type_cm").str();
  pur_type = pur_type.substr(1, pur_type.size() - 2);
  threshold_fidelity = par("threshold_fidelity");

  if (simultaneous_es_enabled && es_with_purify) {
    error("Currently, simultaneous entanglement swapping cannot be simulated with purification");
  }
  purification_type = parsePurType(pur_type);
  if (purification_type == PurType::INVALID) {
    error("Unknown purification type");
  }

  for (int i = 0; i < num_of_qnics; i++) {
    auto msgname = "send timing qnic address-" + std::to_string(i);
    request_send_timing.push_back(new cMessage(msgname.c_str()));
    connection_retry_count[i] = 0;
  }
}

/**
 * The catch-all handler for messages received.  Needs to confirm the packet type and call the appropriate lower-level handler.
 * \param msg pointer to the cMessage itself
 */
void ConnectionManager::handleMessage(cMessage *msg) {
  // this should only be the send notification
  if (msg->isSelfMessage()) {
    // check which qnic address the notification is for and initiate the connection
    for (int i = 0; i < request_send_timing.size(); i++) {
      if (request_send_timing[i] == msg) {
        initiateApplicationRequest(i);
        return;
      }
    }
    error("receive a send self-notification but cannot find which qnic to use");
  }
  logger->logPacket("handleMessage", msg);

  if (auto *req = dynamic_cast<ConnectionSetupRequest *>(msg)) {
    int actual_dst = req->getActual_destAddr();
    int actual_src = req->getActual_srcAddr();

    if (actual_dst == my_address) {
      // got ConnectionSetupRequest and return the response
      respondToRequest(req);
      delete msg;
    } else if (actual_src == my_address) {
      // initiator node
      queueApplicationRequest(req);
    } else {
      // intermediate node
      tryRelayRequestToNextHop(req);
    }
    return;
  }

  if (auto *resp = dynamic_cast<ConnectionSetupResponse *>(msg)) {
    int initiator_addr = resp->getActual_destAddr();
    int responder_addr = resp->getActual_srcAddr();

    if (initiator_addr == my_address || responder_addr == my_address) {
      // this node is not a swapper
      storeRuleSetForApplication(resp);
    } else {
      // this node is a swapper (intermediate node)
      // currently, destinations are separated. (Not accumulated.)
      storeRuleSet(resp);
    }
    delete msg;
    return;
  }

  if (auto *pk = dynamic_cast<RejectConnectionSetupRequest *>(msg)) {
    int actual_src = pk->getActual_srcAddr();

    if (actual_src == my_address) {
      initiator_reject_req_handler(pk);
    } else {
      intermediate_reject_req_handler(pk);
    }
    delete msg;
    return;
  }
}

PurType ConnectionManager::parsePurType(const std::string &pur_type) {
  if (pur_type == "SINGLE_X") {
    return PurType::SINGLE_X;
  }
  if (pur_type == "SINGLE_Z") {
    return PurType::SINGLE_Z;
  }
  if (pur_type == "SINGLE_Y") {
    return PurType::SINGLE_Y;
  }
  if (pur_type == "DOUBLE") {
    return PurType::DOUBLE;
  }
  if (pur_type == "DOUBLE_INV") {
    return PurType::DOUBLE_INV;
  }
  if (pur_type == "DSSA") {
    return PurType::DSSA;
  }
  if (pur_type == "DSSA_INV") {
    return PurType::DSSA_INV;
  }
  if (pur_type == "DSDA") {
    return PurType::DSDA;
  }
  if (pur_type == "DSDA_INV") {
    return PurType::DSDA_INV;
  }
  if (pur_type == "DSDA_SECOND") {
    return PurType::DSDA_SECOND;
  }
  if (pur_type == "DSDA_SECOND_INV") {
    return PurType::DSDA_SECOND_INV;
  }
  if (pur_type == "STEANE_DECODER") {
    return PurType::STEANE_DECODER;
  }
  return PurType::INVALID;
}

/**
 * This function is called to handle the ConnectionSetupResponse at the intermediate node.
 * The only job here is to unpack the RuleSets, feed them to the RuleEngine via Router, and start the connection running.
 * Probably should also let the Application know that the setup is complete and running.
 *
 * \param pk the received ConnectionSetupResponse.
 **/
void ConnectionManager::storeRuleSet(ConnectionSetupResponse *pk) {
  InternalRuleSetForwarding *pk_internal = new InternalRuleSetForwarding("InternalRuleSetForwarding");
  pk_internal->setDestAddr(pk->getDestAddr());
  pk_internal->setSrcAddr(pk->getDestAddr());
  pk_internal->setKind(4);
  pk_internal->setRuleSet_id(pk->getRuleSet_id());
  pk_internal->setRuleSet(pk->getRuleSet());
  send(pk_internal, "RouterPort$o");
}

/**
 * This method is called to handle the ConnectionSetupResponse at an end node.
 * The only job here is to unpack the RuleSets, feed them to the RuleEngine via Router, and start the connection running.
 * \param pk the received ConnectionSetupResponse.
 *
 **/
void ConnectionManager::storeRuleSetForApplication(ConnectionSetupResponse *pk) {
  InternalRuleSetForwarding_Application *pk_internal = new InternalRuleSetForwarding_Application("InternalRuleSetForwardingApplication");
  pk_internal->setDestAddr(pk->getDestAddr());
  pk_internal->setSrcAddr(pk->getDestAddr());  // Should be original Src here?
  pk_internal->setKind(4);
  pk_internal->setRuleSet_id(pk->getRuleSet_id());
  pk_internal->setRuleSet(pk->getRuleSet());
  pk_internal->setApplication_type(pk->getApplication_type());
  send(pk_internal, "RouterPort$o");
}

void ConnectionManager::rejectRequest(ConnectionSetupRequest *req) {
  int application_id = req->getApplicationId();
  int hop_count = req->getStack_of_QNodeIndexesArraySize();
  std::vector<int> path;
  for (int i = 0; i < hop_count; i++) {
    int destination_address = req->getStack_of_QNodeIndexes(i);
    RejectConnectionSetupRequest *packet = new RejectConnectionSetupRequest("RejectConnSetup");
    packet->setApplicationId(application_id);
    packet->setKind(6);
    packet->setDestAddr(destination_address);
    packet->setSrcAddr(my_address);
    packet->setActual_destAddr(req->getActual_destAddr());
    packet->setActual_srcAddr(req->getActual_srcAddr());
    send(packet, "RouterPort$o");
  }
}

/**
 * This function is called to handle the ConnectionSetupRequest at the responder.
 * This is where much of the work happens, and there is the potential for new value
 * if you have a better way to do this.
 * @param pk pointer to the ConnectionSetupRequest packet itself
 * @returns nothing
 *
 * The procedure:
 * @verbatim
 * 1. check the qnic is busy or not
 * 2. generate all the RuleSets by calling RuleSetGenerator
 * 3. reserve the qnic for the connection
 * 4. return ConnectionSetupResponse to each node in this connection.
 * @endverbatim
 */
void ConnectionManager::respondToRequest(ConnectionSetupRequest *req) {
  int application_id = req->getApplicationId();
  int prev_hop_addr = req->getSrcAddr();

  // qnic toward to the previous node
  int qnic_addr = routing_daemon->findQNicAddrByDestAddr(prev_hop_addr);
  if (qnic_addr == -1) {
    error("No qnic to source node. Something wrong with routing.");
  }

  // check if the qnics are reserved or not
  if (isQnicBusy(qnic_addr)) {
    rejectRequest(req);
    return;
  }

  ruleset_gen::RuleSetGenerator ruleset_gen{my_address};
  auto rulesets = ruleset_gen.generateRuleSets(req, createUniqueId());

  // distribute rulesets to each qnode in the path
  for (auto [owner_address, rs] : rulesets) {
    ConnectionSetupResponse *pkt = new ConnectionSetupResponse("ConnectionSetupResponse");
    pkt->setApplicationId(application_id);
    pkt->setRuleSet(rs);
    pkt->setSrcAddr(my_address);
    pkt->setDestAddr(owner_address);
    pkt->setActual_srcAddr(my_address);
    pkt->setActual_destAddr(owner_address);
    pkt->setApplication_type(0);
    pkt->setKind(2);
    send(pkt, "RouterPort$o");
  }
  reserveQnic(qnic_addr);
}

/**
 *  This method is called to handle the ConnectionSetupRequest at an intermediate.
 *  This method reserves requested qnics and then send the request to next hop.
 *  If the QNIC cannot be reserved the ConnectionSetupRequest will be rejected.
 * \param req pointer to the ConnectionSetupRequest packet itself
 * \returns nothing
 **/
void ConnectionManager::tryRelayRequestToNextHop(ConnectionSetupRequest *req) {
  int application_id = req->getApplicationId();
  int responder_addr = req->getActual_destAddr();
  int prev_hop_addr = req->getSrcAddr();
  int outbound_qnic_address = routing_daemon->findQNicAddrByDestAddr(responder_addr);
  int inbound_qnic_address = routing_daemon->findQNicAddrByDestAddr(prev_hop_addr);

  if (outbound_qnic_address == -1) {
    error("QNIC to destination not found");
  }
  if (inbound_qnic_address == -1) {
    error("QNIC from source not found");
  }

  // Use the QNIC address to find the next hop QNode, by asking the Hardware Monitor (neighbor table).
  auto outbound_info = hardware_monitor->findConnectionInfoByQnicAddr(outbound_qnic_address);
  auto inbound_info = hardware_monitor->findConnectionInfoByQnicAddr(inbound_qnic_address);

  if (isQnicBusy(outbound_qnic_address) || isQnicBusy(inbound_qnic_address)) {
    rejectRequest(req);
    return;
  }

  // Update information and send it to the next Qnode.
  int num_accumulated_nodes = req->getStack_of_QNodeIndexesArraySize();
  int num_accumulated_costs = req->getStack_of_linkCostsArraySize();
  int num_accumulated_pair_info = req->getStack_of_QNICsArraySize();

  req->setApplicationId(application_id);
  req->setDestAddr(outbound_info->neighbor_address);
  req->setSrcAddr(my_address);
  req->setStack_of_QNodeIndexesArraySize(num_accumulated_nodes + 1);
  req->setStack_of_linkCostsArraySize(num_accumulated_costs + 1);
  req->setStack_of_QNodeIndexes(num_accumulated_nodes, my_address);
  req->setStack_of_linkCosts(num_accumulated_costs, outbound_info->quantum_link_cost);
  req->setStack_of_QNICsArraySize(num_accumulated_pair_info + 1);

  QNicPairInfo pair_info{inbound_info->qnic, outbound_info->qnic};
  req->setStack_of_QNICs(num_accumulated_pair_info, pair_info);

  reserveQnic(inbound_info->qnic.address);
  reserveQnic(outbound_info->qnic.address);

  send(req, "RouterPort$o");
}

// This is not good way. This property should be held in qnic property.
void ConnectionManager::reserveQnic(int qnic_address) {
  auto it = std::find(reserved_qnics.begin(), reserved_qnics.end(), qnic_address);
  // if qnic is already registered,
  if (it != reserved_qnics.end()) {
    error("qnic(addr: %d) already reserved", qnic_address);
  }
  // else register qnic as reserved qnic
  reserved_qnics.push_back(qnic_address);
}

void ConnectionManager::releaseQnic(int qnic_address) {
  auto it = std::find(reserved_qnics.begin(), reserved_qnics.end(), qnic_address);
  // if qnic is not reserved
  if (it == reserved_qnics.end()) {
    error("qnic(addr: %d)  not reserved", qnic_address);
  }
  // else if the qnic is propery reserved, erase it from vector
  reserved_qnics.erase(it);
}

bool ConnectionManager::isQnicBusy(int qnic_address) {
  auto it = std::find(reserved_qnics.begin(), reserved_qnics.end(), qnic_address);
  // if the qnic is not registered, it's not busy
  if (it == reserved_qnics.end()) {
    return false;
  }
  return true;
}

void ConnectionManager::initiator_reject_req_handler(RejectConnectionSetupRequest *pk) {
  int actual_dest = pk->getActual_destAddr();
  int outbound_qnic_address = routing_daemon->findQNicAddrByDestAddr(actual_dest);

  releaseQnic(outbound_qnic_address);
  scheduleRequestRetry(outbound_qnic_address);
}

/**
 *  This function is called during the handling of ConnectionSetupRequest at the responder.
 * \param pk pointer to the ConnectionSetupRequest packet itself
 * \returns nothing
 * This function is called when we discover that we can't fulfill the connection request,
 * primarily due to resource reservation conflicts.
 **/
void ConnectionManager::responder_reject_req_handler(RejectConnectionSetupRequest *pk) {}

/**
 *  This function is called during the handling of ConnectionSetupRequest at an
 *  intermediate node (not the initator or responder).
 * \param pk pointer to the ConnectionSetupRequest packet itself
 * \returns nothing
 * This function is called when we discover that we can't fulfill the connection request,
 * primarily due to resource reservation conflicts.
 **/
void ConnectionManager::intermediate_reject_req_handler(RejectConnectionSetupRequest *pk) {
  int actual_dst = pk->getActual_destAddr();  // responder address
  int actual_src = pk->getActual_srcAddr();  // initiator address (to get input qnic)

  // Currently, sending path and returning path are same, but for future, this might not good way
  int outbound_qnic_address = routing_daemon->findQNicAddrByDestAddr(actual_dst);
  int inbound_qnic_address = routing_daemon->findQNicAddrByDestAddr(actual_src);

  releaseQnic(outbound_qnic_address);
  releaseQnic(inbound_qnic_address);
}

unsigned long ConnectionManager::createUniqueId() {
  std::string time = SimTime().str();
  std::string address = std::to_string(my_address);
  std::string random = std::to_string(intuniform(0, 10000000));
  std::string hash_seed = address + time + random;
  std::hash<std::string> hash_fn;
  size_t t = hash_fn(hash_seed);
  unsigned long ruleset_id = static_cast<long>(t);
  return ruleset_id;
}

void ConnectionManager::queueApplicationRequest(ConnectionSetupRequest *req) {
  int responder_address = req->getActual_destAddr();
  int outbound_qnic_address = routing_daemon->findQNicAddrByDestAddr(responder_address);

  if (outbound_qnic_address == -1) {
    error("QNIC to destination cannot be found");
  }

  // Use the QNIC address to find the next hop QNode, by asking the Hardware Monitor (neighbor table).
  auto inbound_info = std::make_unique<ConnectionSetupInfo>(NULL_CONNECTION_SETUP_INFO);
  auto outbound_info = hardware_monitor->findConnectionInfoByQnicAddr(outbound_qnic_address);

  // Update information and send it to the next Qnode.
  int num_accumulated_nodes = req->getStack_of_QNodeIndexesArraySize();
  int num_accumulated_costs = req->getStack_of_linkCostsArraySize();
  int num_accumulated_pair_info = req->getStack_of_QNICsArraySize();

  req->setDestAddr(outbound_info->neighbor_address);
  req->setSrcAddr(my_address);
  req->setStack_of_QNodeIndexesArraySize(num_accumulated_nodes + 1);
  req->setStack_of_linkCostsArraySize(num_accumulated_costs + 1);
  req->setStack_of_QNodeIndexes(num_accumulated_nodes, my_address);
  req->setStack_of_linkCosts(num_accumulated_costs, outbound_info->quantum_link_cost);
  req->setStack_of_QNICsArraySize(num_accumulated_pair_info + 1);

  QNicPairInfo pair_info{inbound_info->qnic, outbound_info->qnic};
  req->setStack_of_QNICs(num_accumulated_pair_info, pair_info);

  auto &request_queue = connection_setup_buffer[outbound_qnic_address];
  request_queue.push(req);

  // this is the only request in the queue, try to send it right away
  if (request_queue.size() == 1) {
    EV << "schedule from enqueue" << endl;
    scheduleAt(simTime(), request_send_timing[outbound_qnic_address]);
  }
}

void ConnectionManager::popApplicationRequest(int qnic_address) {
  auto &request_queue = connection_setup_buffer[qnic_address];
  auto *req = request_queue.front();

  connection_retry_count[qnic_address] = 0;
  request_queue.pop();
  delete req;
  releaseQnic(qnic_address);

  if (!request_queue.empty()) {
    EV << "schedule from pop" << endl;
    scheduleAt(simTime(), request_send_timing[qnic_address]);
  }
}

void ConnectionManager::initiateApplicationRequest(int qnic_address) {
  auto &request_queue = connection_setup_buffer[qnic_address];

  if (request_queue.empty()) {
    error("trying to initiate a request from empty queue");
  }

  if (isQnicBusy(qnic_address)) {
    EV << "qnic is busy stop trying to send for now" << endl;
    connection_retry_count[qnic_address] = 0;
    return;
  }

  reserveQnic(qnic_address);
  auto req = request_queue.front();
  send(req->dup(), "RouterPort$o");
}

void ConnectionManager::scheduleRequestRetry(int qnic_address) {
  connection_retry_count[qnic_address]++;
  int upper_bound = (1 << connection_retry_count[qnic_address]) - 1;
  int k = intuniform(0, upper_bound);
  EV << "upper bound = " << upper_bound << endl;
  simtime_t backoff = SimTime(50, SIMTIME_US) * k;
  EV << "cannot initiate the connection. Retry attempt = " << connection_retry_count[qnic_address] << " Retry again in " << backoff << " .\n";
  EV << "schedule from retry" << endl;
  scheduleAt(simTime() + backoff, request_send_timing[qnic_address]);
  return;
}

}  // namespace quisp::modules

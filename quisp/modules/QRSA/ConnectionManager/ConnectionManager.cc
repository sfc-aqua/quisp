/** \file ConnectionManager.cc
 *  \authors cldurand,takaakimatsuo,cocori,rdv
 *
 *  \brief ConnectionManager
 */

#include "ConnectionManager.h"
#include <algorithm>
#include <iterator>
#include <memory>
#include <string>
#include <utility>
#include "modules/QRSA/HardwareMonitor/HardwareMonitor.h"
#include "utils/ComponentProvider.h"

using namespace omnetpp;
using namespace quisp::messages;
using namespace quisp::rules;
using namespace quisp::rules::active;

namespace quisp {
namespace modules {

Define_Module(ConnectionManager);
ConnectionManager::ConnectionManager() : provider(utils::ComponentProvider{this}) {}

void ConnectionManager::initialize() {
  routing_daemon = provider.getRoutingDaemon();
  hardware_monitor = provider.getHardwareMonitor();
  my_address = par("address");
  num_of_qnics = par("total_number_of_qnics");
  simultaneous_es_enabled = par("simultaneous_es_enabled");
  es_with_purify = par("entanglement_swapping_with_purification");
  num_remote_purification = par("num_remote_purification");
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
    // qnode address
    qnic_res_table.insert(std::make_pair(i, false));
    char msgname[32];
    sprintf(msgname, "send timing qnic address-%d", i);
    request_send_timing.push_back(new cMessage(msgname));
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

  if (auto *req = dynamic_cast<ConnectionSetupRequest *>(msg)) {
    int actual_dst = req->getActual_destAddr();
    int actual_src = req->getActual_srcAddr();

    if (actual_dst == my_address) {
      // got ConnectionSetupRequest and return the response
      respondToRequest_deprecated(req);
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
  if (pur_type == "DOUBLE") {
    return PurType::DOUBLE;
  }
  if (pur_type == "DOUBLE_INV") {
    return PurType::DOUBLE_INV;
  }
  if (pur_type == "SSDP_X") {
    return PurType::SSDP_X;
  }
  if (pur_type == "SSDP_Z") {
    return PurType::SSDP_Z;
  }
  if (pur_type == "SSDP_X_INV") {
    return PurType::SSDP_X_INV;
  }
  if (pur_type == "SSDP_Z_INV") {
    return PurType::SSDP_Z_INV;
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
  return PurType::INVALID;
}

/**
 * \param number of links (path length, number of nodes -1
 **/
int ConnectionManager::computePathDivisionSize(int l) {
  if (l > 1) {
    int hl = (l >> 1);
    return computePathDivisionSize(hl) + computePathDivisionSize(l - hl) + 1;
  }
  return l;
}

/**
 * Treat subpath [i:...] of length l
 * \param path Nodes on the connection setup path
 * \param i Left of the subpath to consider
 * \param l Length of the subpath
 * \param link_left Left part of the list of "links"
 * \param link_right Right part
 * \param swapper Swappers to create those links (might be -1 for real links)
 * \param fill_start [0:fill_start[ is already filled
 **/
int ConnectionManager::fillPathDivision(std::vector<int> path, int i, int l, int *link_left, int *link_right, int *swapper, int fill_start) {
  if (l > 1) {
    int hl = (l >> 1);
    fill_start = fillPathDivision(path, i, hl, link_left, link_right, swapper, fill_start);
    fill_start = fillPathDivision(path, i + hl, l - hl, link_left, link_right, swapper, fill_start);
    swapper[fill_start] = path.at(i + hl);
  }
  if (l > 0) {
    link_left[fill_start] = path.at(i);
    link_right[fill_start] = path.at(i + l);
    if (l == 1) swapper[fill_start] = -1;
    fill_start++;
  }
  return fill_start;
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
  pk_internal->setActiveRuleSet(const_cast<ActiveRuleSet *>(pk->getActiveRuleSet()));
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
  pk_internal->setActiveRuleSet(const_cast<ActiveRuleSet *>(pk->getActiveRuleSet()));
  pk_internal->setApplication_type(pk->getApplication_type());
  send(pk_internal, "RouterPort$o");
}

void ConnectionManager::rejectRequest(ConnectionSetupRequest *req) {
  int hop_count = req->getStack_of_QNodeIndexesArraySize();
  std::vector<int> path;
  for (int i = 0; i < hop_count; i++) {
    int destination_address = req->getStack_of_QNodeIndexes(i);
    RejectConnectionSetupRequest *packet = new RejectConnectionSetupRequest("RejectConnSetup");
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
 * \param pk pointer to the ConnectionSetupRequest packet itself
 * \returns nothing
 *
 * The procedure:
 * \verbatim
 * 1. figure out swapping order & partners by calling EntanglementSwappingConfig
 * 2. generate all the RuleSets by calling generateEntanglementSwappingRuleSet
 * 3. return ConnectionSetupResponse to each node in this connection.
 * \endverbatim
 */
void ConnectionManager::respondToRequest(ConnectionSetupRequest *req) {
  // 0. This function is only called in the reponder node.

  // 1. get address and interface info
  // 1.1 get initiator and responder info
  int responder_addr = req->getActual_destAddr();
  int initiator_addr = req->getActual_srcAddr();
  if (responder_addr != my_address) {
    error("The only node that can repond to the request is the end node");
  }

  // 1.2 get qnic interface infomation
  int local_qnic_address_to_actual_dst = routing_daemon->return_QNIC_address_to_destAddr(responder_addr);  // This must be -1 (not found) because not interface to itself
  int local_qnic_address_to_actual_src = routing_daemon->return_QNIC_address_to_destAddr(initiator_addr);  // interface toward to the initiator node
  if (local_qnic_address_to_actual_dst != -1 || local_qnic_address_to_actual_src == -1) {
    error("Unknown interface to the end node itself found or no interface found to source node. Something wrong with routing.");
  }

  // 1.3 destination and source information
  auto dst_info = std::make_unique<ConnectionSetupInfo>(NULL_CONNECTION_SETUP_INFO);
  auto src_info = hardware_monitor->findConnectionInfoByQnicAddr(local_qnic_address_to_actual_src);
  if (src_info == nullptr) {
    error("source info not found");
  }

  // 1.4 check if the qnics are reserved or not
  if (isQnicBusy(src_info->qnic.address) || isQnicBusy(dst_info->qnic.address)) {
    rejectRequest(req);
    return;
  }

  // 1.5 get path infomation from initiator to responder
  int hop_count = req->getStack_of_QNodeIndexesArraySize();  // the number of nodes in between
  std::vector<int> path;  // vector to store node addresses
  for (int i = 0; i < hop_count; i++) {
    path.push_back(req->getStack_of_QNodeIndexes(i));
  }
  path.push_back(my_address);  // path includes responder address

  // 1.6 calculate swapping partners based on the path information
  int divisions = computePathDivisionSize(hop_count);
  int *link_left = new int[divisions], *link_right = new int[divisions], *swapper = new int[divisions];
  // fillPathDivision should yield *exactly* the anticipated number of divisions.
  if (fillPathDivision(path, 0, hop_count, link_left, link_right, swapper, 0) < divisions) {
    error("Something went wrong in path division computation.");
  }
  // table of swapping partners {swapper address: [its swapping partners]..}
  std::map<int, std::vector<int>> swapping_partner_table;
  for (int i = 0; i < divisions; i++) {
    std::vector<int> partners;
    if (swapper[i] > 0) {
      partners.push_back(link_left[i]);
      partners.push_back(link_right[i]);
      swapping_partner_table.insert(std::make_pair(swapper[i], partners));
    }
  }

  // 1.7 get qnic info one by one
  QNIC_pair_info pair_info = {.fst = src_info->qnic, .snd = dst_info->qnic};
  int qnic_array_size = req->getStack_of_QNICsArraySize();
  req->setStack_of_QNICsArraySize(qnic_array_size + 1);
  req->setStack_of_QNICs(qnic_array_size, pair_info);
  std::vector<QNIC_pair_info> qnics = {};
  QNIC_pair_info qnic_pairs;  // qnic pairs information
  for (int i = 0; i < qnic_array_size + 1; i++) {
    qnic_pairs = req->getStack_of_QNICs(i);
    qnics.push_back(qnic_pairs);
  }
  // (-1) - [initiator] --- ... --- [responder] - (-1)
  if (qnics.at(0).fst.index != -1 || qnics.at(qnics.size() - 1).snd.index != -1) {
    error("Qnic index of initiator and responder must be -1 in current scheme. ");
  }

  // 2. RuleSet generation
  // 2.0 Initialize empty RuleSet
  // store rule as a map and vector
  /* {node1_addr, {rule1, rule2, ...}}
   * {node2_addr, {rule1, rule2, ...}}
   * ...
   */
  std::map<int, std::vector<std::unique_ptr<Rule>>> rules_array;
  auto rev_path = path;
  std::reverse(rev_path.begin(), rev_path.end());  // reversed path

  // 2.1 Add rules one by one
  if (es_with_purify) {
    // 2.2.1 purification required
    for (int i = 1; i < path.size(); i++) {
      int left_node = path.at(i - 1), right_node = path.at(i);
      auto left_qnic = getQnicInterface(left_node, right_node, path, qnics);
      auto right_qnic = getQnicInterface(right_node, left_node, path, qnics);
      // arguments: int partner_address, PurType purification_type, double threshold_fidelity, QNIC_type qnic_type, int qnic_id, std::string name
      for (int i = 0; i < num_remote_purification; i++) {
        auto pur_rule_left = purifyRule(right_node, purification_type, threshold_fidelity, left_qnic.type, left_qnic.index);
        auto pur_rule_right = purifyRule(left_node, purification_type, threshold_fidelity, right_qnic.type, right_qnic.index);
        std::vector<int> left_partner = {right_node}, right_partner = {left_node};
        rules_array[left_node].push_back(std::move(pur_rule_left));  // add rule with partner info
        rules_array[right_node].push_back(std::move(pur_rule_right));  // add rule with partner info
      }
    }
    // 2.2.2 alternate EntanglementSwapping and Purification from one hop entanglement to multihop entanglement
    for (int distance = 1; distance < path.size() / 2 + 1; distance++) {
      // 2.2.3 Entanglement Swapping
      for (int i = 1; i < (path.size() + 1) / 2; i++) {
        std::vector<int> swapper_nodes;
        if (rev_path.at(i) != path.at(i)) {
          swapper_nodes = {rev_path.at(i), path.at(i)};
        } else {
          swapper_nodes = {path.at(i)};
        }
        // 2.2.4 iterate swapper nodes
        for (int swapper_node : swapper_nodes) {
          auto config = generateSwappingConfig(swapper_node, path, swapping_partner_table, qnics, 0);
          int left_partner = config.left_partner, right_partner = config.right_partner;
          // check if the distance of swapping is the same as the target distance
          auto swapper_it = std::find(path.begin(), path.end(), swapper_node);
          auto left_it = std::find(path.begin(), path.end(), left_partner);
          auto right_it = std::find(path.begin(), path.end(), right_partner);
          int index = 0, lindex = 0, rindex = 0;
          if (swapper_it != path.end() && left_it != path.end() && right_it != path.end()) {
            index = swapper_it - path.begin();
            lindex = left_it - path.begin();
            rindex = right_it - path.begin();
          } else {
            error("swapper and partner indices are not found in the path. Should not happen.");
          }
          if (std::max(std::abs(index - lindex), std::abs(index - rindex)) == distance) {
            // 2.2.5 Swapping Rules
            // waitRule: int partner_address, QNIC_type qnic_type, int qnic_id, std::string name
            auto empty_rule_left = waitRule(swapper_node, config.lqnic_type, config.lqnic_index);
            auto empty_rule_right = waitRule(swapper_node, config.rqnic_type, config.rqnic_index);
            // std::vector<int> partner_address, double threshold_fidelity, std::vector<QNIC_type> qnic_type, std::vector<int> qnic_id,std::string name
            auto swapping_rule = swapRule(swapping_partner_table[swapper_node], threshold_fidelity, {config.self_left_qnic_type, config.self_right_qnic_type},
                                          {config.self_left_qnic_index, config.self_right_qnic_index});
            rules_array[left_partner].push_back(std::move(empty_rule_left));
            rules_array[right_partner].push_back(std::move(empty_rule_right));
            rules_array[swapper_node].push_back(std::move(swapping_rule));

            // 2.2.6 Purification Rules
            for (int i = 0; i < num_remote_purification; i++) {
              auto pur_rule_left = purifyRule(right_partner, purification_type, threshold_fidelity, config.lqnic_type, config.lqnic_index);
              auto pur_rule_right = purifyRule(left_partner, purification_type, threshold_fidelity, config.rqnic_type, config.rqnic_index);
              rules_array[left_partner].push_back(std::move(pur_rule_left));
              rules_array[right_partner].push_back(std::move(pur_rule_right));
            }
          }
        }
      }
    }

  } else {
    // 2.3.1 purification not required
    for (int distance = 1; distance < path.size() / 2 + 1; distance++) {
      // 2.2.3 Entanglement Swapping
      for (int i = 1; i < (path.size() + 1) / 2; i++) {
        std::vector<int> swapper_nodes;
        if (rev_path.at(i) != path.at(i)) {
          swapper_nodes = {rev_path.at(i), path.at(i)};
        } else {
          swapper_nodes = {path.at(i)};
        }
        // 2.2.4 iterate swapper nodes
        for (int swapper_node : swapper_nodes) {
          auto config = generateSwappingConfig(swapper_node, path, swapping_partner_table, qnics, 0);
          int left_partner = config.left_partner, right_partner = config.right_partner;
          // check if the distance of swapping is the same as the target distance
          auto swapper_it = std::find(path.begin(), path.end(), swapper_node);
          auto left_it = std::find(path.begin(), path.end(), left_partner);
          auto right_it = std::find(path.begin(), path.end(), right_partner);
          int index = 0, lindex = 0, rindex = 0;
          if (swapper_it != path.end() && left_it != path.end() && right_it != path.end()) {
            index = swapper_it - path.begin();
            lindex = left_it - path.begin();
            rindex = right_it - path.begin();
          } else {
            error("swapper and partner indices are not found in the path. Should not happen.");
          }
          if (std::max(std::abs(index - lindex), std::abs(index - rindex)) == distance) {
            // 2.2.5 Swapping Rules
            // waitRule: int partner_address, QNIC_type qnic_type, int qnic_id, std::string name
            auto empty_rule_left = waitRule(swapper_node, config.lqnic_type, config.lqnic_index);
            auto empty_rule_right = waitRule(swapper_node, config.rqnic_type, config.rqnic_index);
            // std::vector<int> partner_address, double threshold_fidelity, std::vector<QNIC_type> qnic_type, std::vector<int> qnic_id,std::string name
            auto swapping_rule = swapRule(swapping_partner_table[swapper_node], threshold_fidelity, {config.self_left_qnic_type, config.self_right_qnic_type},
                                          {config.self_left_qnic_index, config.self_right_qnic_index});
            rules_array[left_partner].push_back(std::move(empty_rule_left));
            rules_array[right_partner].push_back(std::move(empty_rule_right));
            rules_array[swapper_node].push_back(std::move(swapping_rule));
          }
        }
      }
    }
  }
  // 2.4. Tomography
  int initiator_address = path.at(0);
  int responder_address = my_address;
  int num_measure = req->getNum_measure();
  auto initiator_qnic = getQnicInterface(initiator_address, responder_address, path, qnics);
  auto responder_qnic = getQnicInterface(responder_address, initiator_address, path, qnics);
  // int partner_address, int num_measure, double threshold_fidelity, QNIC_type qnic_type, int qnic_id, std::string name
  auto tomo_rule_initiator = tomographyRule(responder_address, num_measure, threshold_fidelity, initiator_qnic.type, initiator_qnic.index);
  auto tomo_rule_responder = tomographyRule(initiator_address, num_measure, threshold_fidelity, responder_qnic.type, responder_qnic.index);
  rules_array[initiator_address].push_back(std::move(tomo_rule_initiator));
  rules_array[responder_address].push_back(std::move(tomo_rule_responder));

  // 3. Wrap up rules into ruleset and send them to prpoer partners
  // 3.1 wrap up rulesets
  unsigned long ruleset_id = createUniqueId();
  for (auto it = rules_array.begin(); it != rules_array.end(); ++it) {
    int owner_address = it->first;
    auto rules = std::move(it->second);
    RuleSet ruleset(ruleset_id, owner_address);
    for (int i = 0; i < rules.size(); i++) {
      auto rule = std::move(rules.at(i));
      auto appended_rule = ruleset.addRule(std::move(rule));
      auto target_qnic_type = appended_rule->qnic_types;
      auto target_qnic_id = appended_rule->qnic_ids;
      if (appended_rule->finalize) {
        // if the rule is entanglement swapping or tomography rule, no need to specify the next rule
        break;
      }
      // 3.2 find next rule (if the qnic type and qnic id is the same, promote entanglement if the rule is not ES)
      for (int j = i + 1; j < rules.size(); j++) {  // start from the next rule
        auto next_qnic_type = rules.at(j)->qnic_types;
        auto next_qnic_id = rules.at(j)->qnic_ids;
        auto qnic_type_it = std::find(next_qnic_type.begin(), next_qnic_type.end(), target_qnic_type.at(0));
        auto qnic_id_it = std::find(next_qnic_id.begin(), next_qnic_id.end(), target_qnic_id.at(0));
        if (qnic_type_it != next_qnic_type.end() && qnic_id_it != next_qnic_id.end()) {
          appended_rule->setNextRule(j);  // rule id is sequencial
          break;
        }
      }
    }
    auto serialized_ruleset = ruleset.serialize_json();

    ConnectionSetupResponse *pkt = new ConnectionSetupResponse("Connection Setup Response");
    pkt->setDestAddr(owner_address);
    pkt->setSrcAddr(my_address);
    pkt->setKind(2);
    pkt->setRuleSet(serialized_ruleset);
    pkt->setActual_srcAddr(initiator_address);
    pkt->setActual_destAddr(responder_address);
    // this is not application but for checking swapping done properly.
    pkt->setApplication_type(0);
    send(pkt, "RouterPort$o");
  }
  reserveQnic(src_info->qnic.address);
}

/**
 * This function is called to handle the ConnectionSetupRequest at the responder.
 * This is where much of the work happens, and there is the potential for new value
 * if you have a better way to do this.
 * \param pk pointer to the ConnectionSetupRequest packet itself
 * \returns nothing
 *
 * The procedure:
 * \verbatim
 * 1. figure out swapping order & partners by calling EntanglementSwappingConfig
 * 2. generate all the RuleSets by calling generateEntanglementSwappingRuleSet
 * 3. return ConnectionSetupResponse to each node in this connection.
 * \endverbatim
 */
void ConnectionManager::respondToRequest_deprecated(ConnectionSetupRequest *req) {
  // Taking qnic information of responder node.
  int actual_dst = req->getActual_destAddr();
  int actual_src = req->getActual_srcAddr();  // initiator address (to get input qnic)

  // This must be -1
  int local_qnic_address_to_actual_dst = routing_daemon->return_QNIC_address_to_destAddr(actual_dst);
  if (local_qnic_address_to_actual_dst != -1) {
    error("something error happen!");
  }

  // TODO: premise only one connection allowed btw, two nodes.
  int local_qnic_address_to_actual_src = routing_daemon->return_QNIC_address_to_destAddr(actual_src);
  if (local_qnic_address_to_actual_src == -1) {
    error("This shouldn't happen!");
  }

  auto dst_info = std::make_unique<ConnectionSetupInfo>(NULL_CONNECTION_SETUP_INFO);
  auto src_info = hardware_monitor->findConnectionInfoByQnicAddr(local_qnic_address_to_actual_src);

  if (src_info == nullptr) {
    error("src_info not found");
  }
  QNIC_pair_info pair_info = {.fst = src_info->qnic, .snd = dst_info->qnic};

  bool is_src_qnic_reserved = isQnicBusy(src_info->qnic.address);
  bool is_dst_qnic_reserved = isQnicBusy(dst_info->qnic.address);

  // qnic already reserved, cannot respond to the request
  if (is_src_qnic_reserved || is_dst_qnic_reserved) {
    rejectRequest(req);
    return;
  }

  // the number of steps
  int hop_count = req->getStack_of_QNodeIndexesArraySize();

  // path from source to destination
  std::vector<int> path;
  for (int i = 0; i < hop_count; i++) {
    path.push_back(req->getStack_of_QNodeIndexes(i));
  }
  path.push_back(my_address);

  int divisions = computePathDivisionSize(hop_count);
  int *link_left = new int[divisions], *link_right = new int[divisions], *swapper = new int[divisions];

  // fillPathDivision should yield *exactly* the anticipated number of divisions.
  if (fillPathDivision(path, 0, hop_count, link_left, link_right, swapper, 0) < divisions) {
    error("Something went wrong in path division computation.");
  }

  std::map<int, std::vector<int>> swapping_partners;
  for (int i = 0; i < divisions; i++) {
    std::vector<int> partners;
    if (swapper[i] > 0) {
      EV_DEBUG << link_left[i] << "---------------" << swapper[i] << "----------------" << link_right[i] << "\n";
      partners.push_back(link_left[i]);
      partners.push_back(link_right[i]);
      swapping_partners.insert(std::make_pair(swapper[i], partners));
    }
  }

  /* TODO: Remember you have link costs <3
   * The link cost is just a dummy variable (constant 1 for now and how it is set in a bad way (read from the channel
    * but from only 1 channels from Src->BSA and ignoring BSA->Dest).
   * If you need to test with different costs, try changing the value.
   * But we need to implement actual link-tomography for this eventually.

   for(int i = 0; i<hop_count; i++){
       EV<<"\nThis is one of the stacked link costs....."<<pk->getStack_of_linkCosts(i)<<"\n";
   }
   */
  // getting swappers index as vector(This might be redundant FIXME)
  std::vector<int> swappers = {};
  for (int i = 0; i < divisions; i++) {
    if (swapper[i] > 0) {
      swappers.push_back(swapper[i]);
    }
  }

  int qnic_array_size = req->getStack_of_QNICsArraySize();
  req->setStack_of_QNICsArraySize(qnic_array_size + 1);
  req->setStack_of_QNICs(qnic_array_size, pair_info);

  // HACK This may be also not good way
  std::vector<QNIC_pair_info> qnics = {};
  QNIC_pair_info qnic_pairs;
  for (int i = 0; i < qnic_array_size + 1; i++) {
    qnic_pairs = req->getStack_of_QNICs(i);
    qnics.push_back(qnic_pairs);
  }

  if (qnics.at(0).fst.index != -1 || qnics.at(qnics.size() - 1).snd.index != -1) {
    error("Qnic index of initiator and responder must be -1 in current scheme. ");
  }

  // node pairs! FIXME: really bad coding
  // Umm... thinking good way
  // Here qnic processing
  // Have to add destination qnic info (destination is the same as my_address. So qnic index must be -1 because self return is not allowed.)

  // 0. prepare empty RuleSets for all nodes
  unsigned long ruleset_id = createUniqueId();
  std::map<int, ActiveRuleSet *> ruleset_map;  // <node address, RuleSet>
  for (int i = 0; i < path.size(); i++) {
    int ruleset_owner = path.at(i);
    ActiveRuleSet *ruleset = new ActiveRuleSet(ruleset_id, ruleset_owner);  // start from empty partners
    ruleset_map.insert(std::make_pair(ruleset_owner, ruleset));
  }
  // 1. add purification rules to the ruleset (policy: do purification before entanglement swapping)
  // RuleSet stack
  // Apply purification for all links
  // Entanglement Swapping -> Purification -> ES -> PUR -> ...
  // Finally Tomography at the end nodes.
  // TODO: How do we provide intereface for ruleset constructions?
  auto rev_path = path;
  std::reverse(rev_path.begin(), rev_path.end());

  if (es_with_purify) {
    // 1.1 initial purification for all links
    // 0 <-pur-> 1 <-pur-> 2 <-pur-> 3 <-pur-> 4
    for (int i = 1; i < path.size(); i++) {
      int left_node = path.at(i - 1);  // 0, 1, 2, 3
      int right_node = path.at(i);  // 1, 2, 3, 4
      auto left_qnic = getQnicInterface(left_node, right_node, path, qnics);
      auto right_qnic = getQnicInterface(right_node, left_node, path, qnics);

      unsigned long rule_id = createUniqueId();
      auto pur_rule_left = purificationRule(right_node, 0, num_remote_purification, left_qnic.type, left_qnic.index, ruleset_id, rule_id);
      auto pur_rule_right = purificationRule(left_node, 0, num_remote_purification, right_qnic.type, right_qnic.index, ruleset_id, rule_id);
      ruleset_map[left_node]->addRule(std::move(pur_rule_left));
      ruleset_map[right_node]->addRule(std::move(pur_rule_right));
    }

    // 1.2 ES -> PUR -> ES -> ...
    // Policy of Entanglement swapping
    // Start from one hop entanglement swapping
    for (int distance = 1; distance < path.size() / 2 + 1; distance++) {
      // 1.2.1 Entanglement swapping
      for (int i = 1; i < (path.size() + 1) / 2; i++) {  // repeat for all swappers
        std::vector<int> swapper_nodes;
        if (rev_path.at(i) != path.at(i)) {
          swapper_nodes = {rev_path.at(i), path.at(i)};
        } else {
          swapper_nodes = {path.at(i)};
        }
        for (int swapper_node : swapper_nodes) {
          auto config = generateSwappingConfig(swapper_node, path, swapping_partners, qnics, 0);
          int left_partner = config.left_partner;
          int right_partner = config.right_partner;
          // check if the distance of swapping is the same as the target distance
          auto swapper_it = std::find(path.begin(), path.end(), swapper_node);
          auto left_it = std::find(path.begin(), path.end(), left_partner);
          auto right_it = std::find(path.begin(), path.end(), right_partner);
          int index = 0;
          int lindex = 0;
          int rindex = 0;

          if (swapper_it != path.end() && left_it != path.end() && right_it != path.end()) {
            index = swapper_it - path.begin();
            lindex = left_it - path.begin();
            rindex = right_it - path.begin();
          } else {
            error("swapper and partner indices are not found in the path. Should not happen.");
          }
          if (std::max(std::abs(index - lindex), std::abs(index - rindex)) == distance) {
            unsigned long rule_id = createUniqueId();
            // empty rules for left and right nodes and swapping rule for swapper
            auto empty_rule_left = waitRule_deprecated(swapper_node, right_partner, ruleset_id, rule_id);
            auto empty_rule_right = waitRule_deprecated(swapper_node, left_partner, ruleset_id, rule_id);
            auto swapping_rule = swappingRule(config, ruleset_id, rule_id);
            ruleset_map[left_partner]->addRule(std::move(empty_rule_left));
            ruleset_map[right_partner]->addRule(std::move(empty_rule_right));
            ruleset_map[swapper_node]->addRule(std::move(swapping_rule));

            // 1.2.2 Purification
            // 1 --- (2, swapped) --- 3
            // 1 (lqnic) --- --- (rqnic) 3 -> pur between 1 - 3
            rule_id = createUniqueId();
            auto pur_rule_left = purificationRule(right_partner, 0, num_remote_purification, config.lqnic_type, config.lqnic_index, ruleset_id, rule_id);
            auto pur_rule_right = purificationRule(left_partner, 0, num_remote_purification, config.rqnic_type, config.rqnic_index, ruleset_id, rule_id);
            ruleset_map[left_partner]->addRule(std::move(pur_rule_left));
            ruleset_map[right_partner]->addRule(std::move(pur_rule_right));
          }
        }
      }
    }
  } else {  // no purifications
    if (!simultaneous_es_enabled) {
      for (int distance = 1; distance < path.size() / 2 + 1; distance++) {
        for (int i = 1; i < path.size() - 1; i++) {  // repeat for all swappers
          std::vector<int> swapper_nodes;
          if (rev_path.at(i) != path.at(i)) {
            swapper_nodes = {rev_path.at(i), path.at(i)};
          } else {
            swapper_nodes = {path.at(i)};
          }
          for (int swapper_node : swapper_nodes) {
            auto config = generateSwappingConfig(swapper_node, path, swapping_partners, qnics, 0);
            int left_partner = config.left_partner;
            int right_partner = config.right_partner;

            // check if the distance of swapping is the same as the target distance
            auto swapper_it = std::find(path.begin(), path.end(), swapper_node);
            auto left_it = std::find(path.begin(), path.end(), left_partner);
            auto right_it = std::find(path.begin(), path.end(), right_partner);
            int index = 0;
            int lindex = 0;
            int rindex = 0;

            if (swapper_it != path.end() && left_it != path.end() && right_it != path.end()) {
              index = swapper_it - path.begin();
              lindex = left_it - path.begin();
              rindex = right_it - path.begin();
            } else {
              error("swapper and partner indices are not found in the path. Should not happen.");
            }
            // the distance of left and right partner should be the same
            if (std::max(std::abs(index - lindex), std::abs(index - rindex)) == distance) {
              unsigned long rule_id = createUniqueId();
              // empty rules for left and right nodes and swapping rule for swapper
              auto empty_rule_left = waitRule_deprecated(swapper_node, right_partner, ruleset_id, rule_id);
              auto empty_rule_right = waitRule_deprecated(swapper_node, left_partner, ruleset_id, rule_id);
              auto swapping_rule = swappingRule(config, ruleset_id, rule_id);
              ruleset_map[left_partner]->addRule(std::move(empty_rule_left));
              ruleset_map[right_partner]->addRule(std::move(empty_rule_right));
              ruleset_map[swapper_node]->addRule(std::move(swapping_rule));
            }
          }
        }
      }
    } else {
      for (int i = 1; i < path.size() - 1; i++) {  // repeat for all swappers
        // ES
        int swapper_node = path.at(i);
        auto config = generateSwappingConfig(swapper_node, path, swapping_partners, qnics, 0);
        unsigned long rule_id = createUniqueId();
        // empty rules for left and right nodes and swapping rule for swapper
        auto swapping_rule = simultaneousSwappingRule(config, path, ruleset_id, rule_id);
        ruleset_map[swapper_node]->addRule(std::move(swapping_rule));
      }
    }
  }

  // 2. Tomography
  int initiator_address = path.at(0);
  int responder_address = my_address;
  int num_measure = req->getNum_measure();
  auto initiator_qnic = getQnicInterface(initiator_address, responder_address, path, qnics);
  auto responder_qnic = getQnicInterface(responder_address, initiator_address, path, qnics);
  unsigned long rule_id = createUniqueId();
  auto tomo_rule_initiator = tomographyRule_deprecated(initiator_address, responder_address, num_measure, initiator_qnic.type, initiator_qnic.index, ruleset_id, rule_id);
  auto tomo_rule_responder = tomographyRule_deprecated(responder_address, initiator_address, num_measure, responder_qnic.type, responder_qnic.index, ruleset_id, rule_id);
  ruleset_map[initiator_address]->addRule(std::move(tomo_rule_initiator));
  ruleset_map[responder_address]->addRule(std::move(tomo_rule_responder));

  // Set next rules
  for (auto it = ruleset_map.cbegin(); it != ruleset_map.cend(); ++it) {
    ActiveRuleSet *ruleset = it->second;
    int current_index = 0;
    for (auto rule = ruleset->cbegin(); rule != ruleset->cend(); ++rule) {
      if ((*rule)->action_partners.size() == 1) {
        // if the action partner is larger than 2, it means entanglement swapping. (no more rules following it.)
        int action_partner;
        if ((*rule)->next_action_partners.size() > 0) {  // have different action partners before and after this rule
          action_partner = (*rule)->next_action_partners.at(0);
        } else {  // the same action partners
          action_partner = (*rule)->action_partners.at(0);
        }
        int next_index = 0;
        for (auto next_rule = ruleset->cbegin(); next_rule != ruleset->cend(); ++next_rule) {
          bool is_same_partner = std::find((*next_rule)->action_partners.begin(), (*next_rule)->action_partners.end(), action_partner) != (*next_rule)->action_partners.end();
          // (*next_rule)->action_partners.find(action_partner) != (*next_rule)->action_partners.end() didn't work why?
          if (is_same_partner && next_index > current_index) {
            // EV<<"Rule: "<<(*rule)->name<<" Next rule: "<<(*next_rule)->name<<"action partner: "<<action_partner<<" same?: "<<is_same_partner<<"\n";
            (*rule)->next_rule_id = (*next_rule)->rule_id;
            break;
          }
          next_index++;
        }
      }
      current_index++;
    }
  }

  // check
  // EV<<"RuleSet id"<<ruleset_id<<"\n";
  // for (auto rs = ruleset_map.begin(); rs != ruleset_map.end(); ++rs) {
  //   int owner = rs->first;
  //   RuleSet *ruleset = rs->second;
  //   EV << "owner: " << owner << "\n";
  //   for (auto rule = ruleset->cbegin(); rule != ruleset->cend(); ++rule) {
  //     EV << "Rule: " << (*rule)->name << " Rule id: " << (*rule)->rule_id << " next rule id: " << (*rule)->next_rule_id << "\n";
  //   }
  // }
  // error("check");

  // 3. send rulesets to nodes
  for (auto it = ruleset_map.begin(); it != ruleset_map.end(); ++it) {
    int owner_address = it->first;
    auto ruleset = it->second;
    ConnectionSetupResponse *pkt = new ConnectionSetupResponse("Connection Setup Response");
    pkt->setDestAddr(owner_address);
    pkt->setSrcAddr(my_address);
    pkt->setKind(2);
    pkt->setActiveRuleSet(ruleset);
    pkt->setActual_srcAddr(initiator_address);
    pkt->setActual_destAddr(responder_address);
    // this is not application but for checking swapping done properly.
    pkt->setApplication_type(0);
    send(pkt, "RouterPort$o");
  }

  if (actual_dst != my_address) {
    reserveQnic(src_info->qnic.address);
    reserveQnic(dst_info->qnic.address);
  } else {
    reserveQnic(src_info->qnic.address);
  }
}

QNIC_id ConnectionManager::getQnicInterface(int owner_address, int partner_address, std::vector<int> path, std::vector<QNIC_pair_info> qnics) {
  // owner index in the path
  auto iter_owner = std::find(path.begin(), path.end(), owner_address);
  size_t owner_index = std::distance(path.begin(), iter_owner);
  // partner index in the path
  auto iter_partner = std::find(path.begin(), path.end(), partner_address);
  size_t partner_index = std::distance(path.begin(), iter_partner);

  if (owner_address == partner_address) {
    error("owner address and parnter address must be different");
  }
  // if the owner is closer to the reponder than the partner, then this returns left qnic interface,
  // otherwise, this returns right qnic interface
  // initiator <-- (fst) owner (snd) --> responder
  QNIC_id qnic_interface;
  if (partner_index < owner_index) {
    qnic_interface = qnics.at(owner_index).fst;
  } else if (partner_index > owner_index) {
    qnic_interface = qnics.at(owner_index).snd;
  }
  return qnic_interface;
}

/**
 *  This function is for selecting the order of entanglement swapping
 * \param swapper_address node address; could be any intermediate in the path (not an end point)
 * \param path list of node addresses in the path
 * \param qnics index and type of QNICs at each node in the path
 * \param num_resources the duration of the requested connection, in Bell pairs
 * \returns a SwappingConfig
 **/
SwappingConfig ConnectionManager::generateSwappingConfig(int swapper_address, std::vector<int> path, std::map<int, std::vector<int>> swapping_partners,
                                                         std::vector<QNIC_pair_info> qnics, int num_resources) {
  ///
  /// 1.recognize partner. (which node is left partner, right partner)
  /// Currently, we choose every other node in the path to do swapping in the first round.
  /// In the examples below, the number in parentheses is the round of swapping,
  /// and designates which nodes are swapping.
  /// If the number of hops is a power of two, we get something like
  /// \verbatim
  /// node1 --- node2(1) --- node3 --- node4(1) --- node5
  /// node1 ---------------- node3 ---------------- node5
  /// node1 ---------------- node3(2) ------------- node5
  /// node1 --------------------------------------- node5
  /// \endverbatim
  /// If the number of hops is not a power of two, at some stage
  /// the number of hops will become become odd as we proceed,
  /// forcing us to decide which to do first.  In this version
  /// of the code, we just give priority starting from the left
  /// (start of our list)
  /// \verbatim
  /// node1 --- node2(1) --- node3 --- node4(1) --- node5 --- node6
  /// node1 ---------------- node3 ---------------- node5 --- node6
  /// node1 ---------------- node3(2) ------------- node5 --- node6
  /// node1 --------------------------------------- node5 --- node6
  /// node1 ------------------------------------ node5(3) --- node6
  /// node1 ------------------------------------------------- node6
  /// \endverbatim
  /// todo hypothetically, with no purification, all of the intermediate
  /// nodes could swap asynchronously and essentially simultaneously.
  /// In fact, that's probably what we want, to minimize decoherence.
  /// But, the condition clause will have to be extended in order to support
  /// "when part of this connection" rather than "when entangled with this node"
  /// and you have to be careful of not creating the wrong result by accident.

  // If the counterparts are decided, the order will automatically be determined.

  auto iter = std::find(path.begin(), path.end(), swapper_address);
  size_t index = std::distance(path.begin(), iter);  // index of swapper in the path
  if (index == 0 || index == path.size()) {
    error("This shouldn't happen. Endnode was recognized as swapper with some reason.");
  }
  QNIC_id left_self_qnic = qnics.at(index).fst;
  QNIC_id right_self_qnic = qnics.at(index).snd;

  // FIXME more dynamically using recursive function or ...
  // auto it = std::find(swapping_partners.begin(), swapping_partners.end(), swapper_address);
  auto it = swapping_partners.find(swapper_address);
  if (it == swapping_partners.end() || it->second.size() != 2) {
    error("Swapper is not recognized as swapper, or the number of partners is wrong (must be 2)");
  }
  int left_partner = it->second.at(0);
  int right_partner = it->second.at(1);
  EV_DEBUG << "swapping" << left_partner << "<-->" << swapper_address << "<-->" << right_partner << "\n";
  auto iter_left = std::find(path.begin(), path.end(), left_partner);
  auto iter_right = std::find(path.begin(), path.end(), right_partner);
  if (iter_left == path.end()) {
    error("left nodes are not found in path");
  }
  if (iter_right == path.end()) {
    error("right nodes are not found in path");
  }

  size_t left_partner_index = std::distance(path.begin(), iter_left);
  size_t right_partner_index = std::distance(path.begin(), iter_right);

  // left partner must be second
  // right partner must be first
  // TODO: detail description of this.
  QNIC_id left_partner_qnic = qnics.at(left_partner_index).snd;
  QNIC_id right_partner_qnic = qnics.at(right_partner_index).fst;

  if (right_self_qnic.type == QNIC_RP || left_self_qnic.type == QNIC_RP || right_partner_qnic.type == QNIC_RP || left_partner_qnic.type == QNIC_RP) {
    error("MSM link not implemented");
  }
  SwappingConfig config;
  config.left_partner = left_partner;
  config.lqnic_type = left_partner_qnic.type;
  config.lqnic_index = left_partner_qnic.index;
  config.lqnic_address = left_partner_qnic.address;
  config.lres = num_resources;

  config.right_partner = right_partner;
  config.rqnic_type = right_partner_qnic.type;
  config.rqnic_index = right_partner_qnic.index;
  config.rqnic_address = right_partner_qnic.address;
  config.rres = num_resources;

  config.self_left_qnic_index = left_self_qnic.index;
  config.self_right_qnic_index = right_self_qnic.index;
  config.self_left_qnic_type = left_self_qnic.type;
  config.self_right_qnic_type = right_self_qnic.type;
  return config;
}

SwappingConfig ConnectionManager::generateSimultaneousSwappingConfig(int swapper_address, std::vector<int> path, std::vector<QNIC_pair_info> qnics, int num_resources) {
  // Set the left and right partner to be initiator and responder.

  auto iter = std::find(path.begin(), path.end(), swapper_address);
  size_t index = std::distance(path.begin(), iter);  // index of swapper in the path
  if (index == 0 || index == path.size()) {
    error("This shouldn't happen. Endnode was recognized as swapper with some reason.");
  }
  QNIC_id left_self_qnic = qnics.at(index).fst;
  QNIC_id right_self_qnic = qnics.at(index).snd;

  size_t left_partner_index = std::distance(path.begin(), iter - 1);
  size_t right_partner_index = std::distance(path.begin(), iter + 1);

  int left_partner = path.at(left_partner_index);
  int right_partner = path.at(right_partner_index);

  // left partner must be second
  // right partner must be first
  // TODO: detail description of this.
  QNIC_id left_partner_qnic = qnics.at(left_partner_index).snd;
  QNIC_id right_partner_qnic = qnics.at(right_partner_index).fst;
  EV << "left_index: " << left_partner_index << " right_index: " << right_partner_index << "path size: " << path.size() << "\n";

  size_t initiator_index = std::distance(path.begin(), path.begin());
  size_t responder_index = std::distance(path.begin(), path.end());
  EV << "ini_index: " << initiator_index << " res_index: " << responder_index << "path size: " << path.size() << "\n";

  QNIC_id initiator_qnic = qnics.at(0).snd;

  QNIC_id responder_qnic = qnics.at(responder_index - 1).fst;

  if (right_self_qnic.type == QNIC_RP || left_self_qnic.type == QNIC_RP || right_partner_qnic.type == QNIC_RP || left_partner_qnic.type == QNIC_RP) {
    error("MSM link not implemented");
  }

  SwappingConfig config;
  config.left_partner = left_partner;
  config.lqnic_type = left_partner_qnic.type;
  config.lqnic_index = left_partner_qnic.index;
  config.lqnic_address = left_partner_qnic.address;
  config.lres = num_resources;

  config.right_partner = right_partner;
  config.rqnic_type = right_partner_qnic.type;
  config.rqnic_index = right_partner_qnic.index;
  config.rqnic_address = right_partner_qnic.address;
  config.rres = num_resources;

  // For end nodes
  config.initiator = path.at(initiator_index);
  config.initiator_qnic_type = initiator_qnic.type;
  config.initiator_qnic_index = initiator_qnic.index;
  config.initiator_qnic_address = initiator_qnic.address;
  config.initiator_res = num_resources;

  config.responder = path.at(responder_index - 1);
  config.responder_qnic_type = responder_qnic.type;
  config.responder_qnic_index = responder_qnic.index;
  config.responder_qnic_address = responder_qnic.address;
  config.responder_res = num_resources;

  // Addition info
  config.index = index;

  config.self_left_qnic_index = left_self_qnic.index;
  config.self_right_qnic_index = right_self_qnic.index;
  config.self_left_qnic_type = left_self_qnic.type;
  config.self_right_qnic_type = right_self_qnic.type;
  return config;
}

/**
 *  This method is called to handle the ConnectionSetupRequest at an intermediate.
 *  This method reserves requested qnics and then send the request to next hop.
 *  If the QNIC cannot be reserved the ConnectionSetupRequest will be rejected.
 * \param req pointer to the ConnectionSetupRequest packet itself
 * \returns nothing
 **/
void ConnectionManager::tryRelayRequestToNextHop(ConnectionSetupRequest *req) {
  int responder_addr = req->getActual_destAddr();
  int initiator_addr = req->getActual_srcAddr();
  int outbound_qnic_address = routing_daemon->return_QNIC_address_to_destAddr(responder_addr);
  int inbound_qnic_address = routing_daemon->return_QNIC_address_to_destAddr(initiator_addr);

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

  req->setDestAddr(outbound_info->neighbor_address);
  req->setSrcAddr(my_address);
  req->setStack_of_QNodeIndexesArraySize(num_accumulated_nodes + 1);
  req->setStack_of_linkCostsArraySize(num_accumulated_costs + 1);
  req->setStack_of_QNodeIndexes(num_accumulated_nodes, my_address);
  req->setStack_of_linkCosts(num_accumulated_costs, outbound_info->quantum_link_cost);
  req->setStack_of_QNICsArraySize(num_accumulated_pair_info + 1);

  QNIC_pair_info pair_info = {.fst = inbound_info->qnic, .snd = outbound_info->qnic};
  req->setStack_of_QNICs(num_accumulated_pair_info, pair_info);

  reserveQnic(inbound_info->qnic.address);
  reserveQnic(outbound_info->qnic.address);

  send(req, "RouterPort$o");
}

// This is not good way. This property should be held in qnic property.
void ConnectionManager::reserveQnic(int qnic_address) {
  auto it = qnic_res_table.find(qnic_address);
  if (it == qnic_res_table.end() || it->second) {
    error("qnic(addr: %d) not found or already reserved", qnic_address);
  }
  it->second = true;
}

void ConnectionManager::releaseQnic(int qnic_address) {
  auto it = qnic_res_table.find(qnic_address);
  if (it == qnic_res_table.end() || !it->second) {
    error("qnic(addr: %d) not found or not reserved", qnic_address);
  }
  it->second = false;
}

bool ConnectionManager::isQnicBusy(int qnic_address) {
  bool isReserved = false;
  auto it = qnic_res_table.find(qnic_address);
  if (it == qnic_res_table.end()) {
    error("address: %d not found", qnic_address);
  }
  isReserved = it->second;
  return isReserved;
}

void ConnectionManager::initiator_reject_req_handler(RejectConnectionSetupRequest *pk) {
  int actual_dest = pk->getActual_destAddr();
  int outbound_qnic_address = routing_daemon->return_QNIC_address_to_destAddr(actual_dest);

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
  int outbound_qnic_address = routing_daemon->return_QNIC_address_to_destAddr(actual_dst);
  int inbound_qnic_address = routing_daemon->return_QNIC_address_to_destAddr(actual_src);

  releaseQnic(outbound_qnic_address);
  releaseQnic(inbound_qnic_address);
}

std::unique_ptr<Rule> ConnectionManager::purifyRule(int partner_address, PurType purification_type, double threshold_fidelity, QNIC_type qnic_type, int qnic_id, std::string name) {
  auto purify_rule = std::make_unique<Rule>(partner_address, qnic_type, qnic_id, false);
  purify_rule->setName(name);

  // decide how many Bell pairs are required
  int num_resource;
  if (purification_type == PurType::SINGLE_X || PurType::SINGLE_Z) {
    num_resource = 2;
  } else if (purification_type == PurType::DOUBLE || purification_type == PurType::DOUBLE_INV || purification_type == PurType::SSDP_X || purification_type == PurType::SSDP_X_INV ||
             purification_type == PurType::SSDP_Z || purification_type == PurType::SSDP_Z_INV) {
    num_resource = 3;
  } else if (purification_type == PurType::DSDA_SECOND || purification_type == PurType::DSDA_SECOND_INV) {
    num_resource = 4;
  } else if (purification_type == PurType::DSDA || purification_type == PurType::DSDA_INV) {
    num_resource = 5;
  } else {
    error("unknown purification type");
  }

  // prepare condition
  auto condition = std::make_unique<Condition>();
  auto enough_resource_clause = std::make_unique<EnoughResourceConditionClause>(num_resource, threshold_fidelity, partner_address, qnic_type, qnic_id);
  condition->addClause(std::move(enough_resource_clause));
  purify_rule->setCondition(std::move(condition));

  // prepare action
  auto purify_action = std::make_unique<Purification>(purification_type, partner_address, qnic_type, qnic_id);
  purify_rule->setAction(std::move(purify_action));

  return purify_rule;
}

std::unique_ptr<Rule> ConnectionManager::swapRule(std::vector<int> partner_address, double threshold_fidelity, std::vector<QNIC_type> qnic_type, std::vector<int> qnic_id,
                                                  std::string name) {
  auto swap_rule = std::make_unique<Rule>(partner_address, qnic_type, qnic_id, true);
  swap_rule->setName(name);

  // prepare condition and two enough resource clauses
  auto condition = std::make_unique<Condition>();
  auto enough_resource_clause_first = std::make_unique<EnoughResourceConditionClause>(1, threshold_fidelity, partner_address.at(0), qnic_type.at(0), qnic_id.at(0));
  auto enough_resource_clause_second = std::make_unique<EnoughResourceConditionClause>(1, threshold_fidelity, partner_address.at(1), qnic_type.at(1), qnic_id.at(1));
  condition->addClause(std::move(enough_resource_clause_first));
  condition->addClause(std::move(enough_resource_clause_second));
  swap_rule->setCondition(std::move(condition));

  // prepare swapping action (partners, qnic_types, qnic_ids)
  auto swap_action = std::make_unique<EntanglementSwapping>(partner_address, qnic_type, qnic_id);
  swap_rule->setAction(std::move(swap_action));

  return swap_rule;
}

std::unique_ptr<Rule> ConnectionManager::waitRule(int partner_address, QNIC_type qnic_type, int qnic_id, std::string name) {
  auto wait_rule = std::make_unique<Rule>(partner_address, qnic_type, qnic_id, false);
  wait_rule->setName(name);

  // prepare condition and two enough resource clauses
  auto condition = std::make_unique<Condition>();
  auto wait_clause = std::make_unique<WaitConditionClause>(partner_address, qnic_type, qnic_id);
  condition->addClause(std::move(wait_clause));
  wait_rule->setCondition(std::move(condition));

  // prepare swapping action (partners, qnic_types, qnic_ids)
  auto wait_action = std::make_unique<Wait>(partner_address, qnic_type, qnic_id);
  wait_rule->setAction(std::move(wait_action));

  return wait_rule;
}

std::unique_ptr<Rule> ConnectionManager::tomographyRule(int partner_address, int num_measure, double threshold_fidelity, QNIC_type qnic_type, int qnic_id, std::string name) {
  auto tomography_rule = std::make_unique<Rule>(partner_address, qnic_type, qnic_id, true);
  tomography_rule->setName(name);

  // prepare condition
  auto condition = std::make_unique<Condition>();
  auto enough_resource_clause = std::make_unique<EnoughResourceConditionClause>(1, threshold_fidelity, partner_address, qnic_type, qnic_id);
  condition->addClause(std::move(enough_resource_clause));
  tomography_rule->setCondition(std::move(condition));

  // prepare action
  auto tomography_action = std::make_unique<Tomography>(num_measure, partner_address, qnic_type, qnic_id);
  tomography_rule->setAction(std::move(tomography_action));

  return tomography_rule;
}
// Rule Generators
std::unique_ptr<ActiveRule> ConnectionManager::purificationRule(int partner_address, int purification_type, int num_purification, QNIC_type qnic_type, int qnic_index,
                                                                unsigned long ruleset_id, unsigned long rule_id) {
  // list of purification types
  std::string pur_name = "";
  if (purification_type == 0) {
    pur_name = "X purification with : " + std::to_string(partner_address);
  } else if (purification_type == 1) {
    pur_name = "Z purification with : " + std::to_string(partner_address);
  } else if (purification_type == 2) {
    pur_name = "Double purificaiton with: " + std::to_string(partner_address);
  } else if (purification_type == 3) {
    pur_name = "Double seletion purification with: " + std::to_string(partner_address);
  } else if (purification_type == 4) {
    pur_name = "Double selection dual action purification with: " + std::to_string(partner_address);
  }

  std::vector<int> partners = {partner_address};
  auto rule_purification = std::make_unique<ActiveRule>(ruleset_id, rule_id, pur_name, partners);

  for (int i = 0; i < num_purification; i++) {
    if (purification_type == 0) {
      // X purification (should prepare enum with purification)
      ActiveCondition *condition = new ActiveCondition();
      ActiveClause *resource_clause = new EnoughResourceClause(partner_address, 2);  // to prepare 1 purified entanglement, we need 2 raw entanglements
      condition->addClause(resource_clause);
      rule_purification->setCondition(condition);
      // PurifyAction(unsigned long RuleSet_id, unsigned long rule_id, bool X_purification, bool Z_purification, int num_purification, int part, QNIC_type qt, int qi, int res, int
      // tres);
      ActiveAction *purify_action = new PurifyAction(ruleset_id, rule_id, true, false, num_purification, partner_address, qnic_type, qnic_index, 0, 1);
      rule_purification->setAction(purify_action);
    } else if (purification_type == 1) {
      // Z purification (should prepare enum with purification)
      ActiveCondition *condition = new ActiveCondition();
      ActiveClause *resource_clause = new EnoughResourceClause(partner_address, 2);  // to prepare 1 purified entanglement, we need 2 raw entanglements
      condition->addClause(resource_clause);
      rule_purification->setCondition(condition);
      // PurifyAction(unsigned long RuleSet_id, unsigned long rule_id, bool X_purification, bool Z_purification, int num_purification, int part, QNIC_type qt, int qi, int res,
      // int tres);
      ActiveAction *purify_action = new PurifyAction(ruleset_id, rule_id, false, true, num_purification, partner_address, qnic_type, qnic_index, 0, 1);
      rule_purification->setAction(purify_action);
    } else if (purification_type == 2) {
      // Double purification
      ActiveCondition *condition = new ActiveCondition();
      ActiveClause *resource_clause = new EnoughResourceClause(partner_address, 3);
      condition->addClause(resource_clause);
      rule_purification->setCondition(condition);
      ActiveAction *purify_action = new DoublePurifyAction(ruleset_id, rule_id, partner_address, qnic_type, qnic_index, 0, 1, 2);
      rule_purification->setAction(purify_action);
    } else if (purification_type == 3) {
      // Double Selection purify X action
      ActiveCondition *condition = new ActiveCondition();
      ActiveClause *resource_clause = new EnoughResourceClause(partner_address, 3);
      condition->addClause(resource_clause);
      rule_purification->setCondition(condition);
      ActiveAction *purify_action = new DoublePurifyAction(ruleset_id, rule_id, partner_address, qnic_type, qnic_index, 0, 1, 2);
      rule_purification->setAction(purify_action);
    } else if (purification_type == 4) {
      // Double Selection second
      ActiveCondition *condition = new ActiveCondition();
      ActiveClause *resource_clause = new EnoughResourceClause(partner_address, 4);
      condition->addClause(resource_clause);
      rule_purification->setCondition(condition);
      ActiveAction *purify_action = new DoubleSelectionDualActionSecond(ruleset_id, rule_id, partner_address, qnic_type, qnic_index, 0, 1, 2, 3);
      rule_purification->setAction(purify_action);
    } else {
      error("Unknown purification type");
    }
  }
  if (rule_purification == nullptr) {
    error("Purification Rule is not successfully generated.");
  }
  return rule_purification;
}

std::unique_ptr<ActiveRule> ConnectionManager::swappingRule(SwappingConfig conf, unsigned long ruleset_id, unsigned long rule_id) {
  std::vector<int> partners = {conf.left_partner, conf.right_partner};
  std::string rule_name = "Entanglement Swapping with " + std::to_string(conf.left_partner) + " : " + std::to_string(conf.right_partner);
  auto rule_entanglement_swapping = std::make_unique<ActiveRule>(ruleset_id, rule_id, rule_name, partners);
  ActiveCondition *condition = new ActiveCondition();
  ActiveClause *resource_clause_left = new EnoughResourceClause(conf.left_partner, 1);
  ActiveClause *resource_clause_right = new EnoughResourceClause(conf.right_partner, 1);
  condition->addClause(resource_clause_left);
  condition->addClause(resource_clause_right);
  rule_entanglement_swapping->setCondition(condition);
  ActiveAction *action = new SwappingAction(ruleset_id, rule_id, conf.left_partner, conf.lqnic_type, conf.lqnic_index, conf.lqnic_address, conf.lres, conf.right_partner,
                                            conf.rqnic_type, conf.rqnic_index, conf.rqnic_address, conf.rres, conf.self_left_qnic_index, conf.self_left_qnic_type,
                                            conf.self_right_qnic_index, conf.self_right_qnic_type);
  rule_entanglement_swapping->setAction(action);
  return rule_entanglement_swapping;
}

std::unique_ptr<ActiveRule> ConnectionManager::simultaneousSwappingRule(SwappingConfig conf, std::vector<int> path, unsigned long ruleset_id, unsigned long rule_id) {
  // From @poramet implementations
  std::vector<int> partners = {conf.left_partner, conf.right_partner};
  std::string rule_name = "Simultaneous Entanglement Swapping with " + std::to_string(conf.left_partner) + " : " + std::to_string(conf.right_partner);
  int index_in_path = conf.index;
  int path_length_exclude_IR = path.size() - 2;

  auto rule_simultaneous_entanglement_swapping = std::make_unique<ActiveRule>(ruleset_id, rule_id, rule_name, partners);
  ActiveCondition *condition = new ActiveCondition();
  ActiveClause *resource_clause_left = new EnoughResourceClause(conf.left_partner, 1);
  ActiveClause *resource_clause_right = new EnoughResourceClause(conf.right_partner, 1);
  condition->addClause(resource_clause_left);
  condition->addClause(resource_clause_right);

  ActiveAction *action = new SimultaneousSwappingAction(ruleset_id, rule_id, conf.left_partner, conf.lqnic_type, conf.lqnic_index, conf.lqnic_address, conf.lres,
                                                        conf.right_partner, conf.rqnic_type, conf.rqnic_index, conf.rqnic_address, conf.rres, conf.self_left_qnic_index,
                                                        conf.self_left_qnic_type, conf.self_right_qnic_index, conf.self_right_qnic_type, conf.initiator, conf.initiator_qnic_type,
                                                        conf.initiator_qnic_index, conf.initiator_qnic_address, conf.initiator_res, conf.responder, conf.responder_qnic_type,
                                                        conf.responder_qnic_index, conf.responder_qnic_address, conf.responder_res, index_in_path, path_length_exclude_IR);

  rule_simultaneous_entanglement_swapping->setCondition(condition);
  rule_simultaneous_entanglement_swapping->setAction(action);
  return rule_simultaneous_entanglement_swapping;
}

std::unique_ptr<ActiveRule> ConnectionManager::waitRule_deprecated(int partner_address, int next_parter_address, unsigned long ruleset_id, unsigned long rule_id) {
  // This is used for waiting swapping result from partner
  std::vector<int> partners = {partner_address};
  std::string rule_name = "Wait rule with: " + std::to_string(partner_address);
  auto wait_rule = std::make_unique<ActiveRule>(ruleset_id, rule_id, rule_name, partners);
  ActiveCondition *condition = new ActiveCondition();
  ActiveClause *wait_clause = new WaitClause();
  condition->addClause(wait_clause);
  wait_rule->setCondition(condition);
  wait_rule->next_action_partners.push_back(next_parter_address);
  return wait_rule;
}

std::unique_ptr<ActiveRule> ConnectionManager::tomographyRule_deprecated(int owner_address, int partner_address, int num_measure, QNIC_type qnic_type, int qnic_index,
                                                                         unsigned long ruleset_id, unsigned long rule_id) {
  std::vector<int> partners = {partner_address};
  auto tomography_rule = std::make_unique<ActiveRule>(ruleset_id, rule_id, "tomography", partners);
  ActiveCondition *condition = new ActiveCondition();
  ActiveClause *count_clause = new MeasureCountClause(num_measure);
  ActiveClause *resource_clause = new EnoughResourceClause(partner_address, 1);
  // Technically, there is no condition because an available resource is guaranteed whenever the rule is ran.
  condition->addClause(count_clause);
  condition->addClause(resource_clause);
  tomography_rule->setCondition(condition);
  ActiveAction *action = new RandomMeasureAction(ruleset_id, rule_id, owner_address, partner_address, qnic_type, qnic_index, 0, num_measure);
  tomography_rule->setAction(action);
  return tomography_rule;
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
  int outbound_qnic_address = routing_daemon->return_QNIC_address_to_destAddr(responder_address);

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

  QNIC_pair_info pair_info = {.fst = inbound_info->qnic, .snd = outbound_info->qnic};
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
  // simtime_t upper_bound = SimTime(50, SIMTIME_US) * connection_retry_count[qnic_address];  // 50 microsec
  EV << "upper bound = " << upper_bound << endl;
  simtime_t backoff = SimTime(50, SIMTIME_US) * k;
  EV << "cannot initiate the connection. Retry attempt = " << connection_retry_count[qnic_address] << " Retry again in " << backoff << " .\n";
  EV << "schedule from retry" << endl;
  scheduleAt(simTime() + backoff, request_send_timing[qnic_address]);
  return;
}

void ConnectionManager::finish() {
  for (auto *msg : request_send_timing) {
    cancelAndDelete(msg);
  }
}

}  // namespace modules
}  // namespace quisp

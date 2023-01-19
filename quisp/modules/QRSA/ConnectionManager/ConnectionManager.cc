/** \file ConnectionManager.cc
 *  \authors cldurand,takaakimatsuo,cocori,rdv
 *
 *  \brief ConnectionManager
 */

#include "ConnectionManager.h"

using namespace omnetpp;
using namespace quisp::messages;
using namespace quisp::rules;

namespace quisp::modules {

Define_Module(ConnectionManager);
ConnectionManager::ConnectionManager() : provider(utils::ComponentProvider{this}) {}

void ConnectionManager::initialize() {
  initializeLogger(provider);
  routing_daemon = provider.getRoutingDaemon();
  hardware_monitor = provider.getHardwareMonitor();
  my_address = par("address");
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
  std::map<int, std::vector<std::unique_ptr<Rule>>> rules_map;
  auto rev_path = path;
  std::reverse(rev_path.begin(), rev_path.end());  // reversed path

  int shared_tag = 0;  // used for identifying the partner rule.
  // 2.1 Add rules one by one
  if (es_with_purify) {
    // 2.2.1 purification required
    for (int i = 1; i < path.size(); i++) {
      int left_node = path.at(i - 1), right_node = path.at(i);
      for (int i = 0; i < num_remote_purification; i++) {
        auto pur_rule_left = purifyRule(right_node, purification_type, threshold_fidelity, shared_tag);
        auto pur_rule_right = purifyRule(left_node, purification_type, threshold_fidelity, shared_tag);
        shared_tag++;
        rules_map[left_node].push_back(std::move(pur_rule_left));  // add rule with partner info
        rules_map[right_node].push_back(std::move(pur_rule_right));  // add rule with partner info
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
            auto wait_rule_left = waitRule(swapper_node, shared_tag);
            auto wait_rule_right = waitRule(swapper_node, shared_tag);
            auto swapping_rule = swapRule(swapping_partner_table[swapper_node], threshold_fidelity, shared_tag);
            shared_tag++;
            rules_map[left_partner].push_back(std::move(wait_rule_left));
            rules_map[right_partner].push_back(std::move(wait_rule_right));
            rules_map[swapper_node].push_back(std::move(swapping_rule));

            // 2.2.6 Purification Rules
            for (int i = 0; i < num_remote_purification; i++) {
              auto pur_rule_left = purifyRule(right_partner, purification_type, threshold_fidelity, shared_tag);
              auto pur_rule_right = purifyRule(left_partner, purification_type, threshold_fidelity, shared_tag);
              shared_tag++;
              rules_map[left_partner].push_back(std::move(pur_rule_left));
              rules_map[right_partner].push_back(std::move(pur_rule_right));
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
            auto wait_rule_left = waitRule(swapper_node, shared_tag);
            auto wait_rule_right = waitRule(swapper_node, shared_tag);
            auto swapping_rule = swapRule(swapping_partner_table[swapper_node], threshold_fidelity, shared_tag);
            shared_tag++;
            rules_map[left_partner].push_back(std::move(wait_rule_left));
            rules_map[right_partner].push_back(std::move(wait_rule_right));
            rules_map[swapper_node].push_back(std::move(swapping_rule));
          }
        }
      }
    }
  }
  // 2.4. Tomography
  int initiator_address = path.at(0);
  int responder_address = my_address;
  int num_measure = req->getNum_measure();
  auto tomo_rule_initiator = tomographyRule(responder_address, initiator_address, num_measure, threshold_fidelity, shared_tag);
  auto tomo_rule_responder = tomographyRule(initiator_address, responder_address, num_measure, threshold_fidelity, shared_tag);
  shared_tag++;
  rules_map[initiator_address].push_back(std::move(tomo_rule_initiator));
  rules_map[responder_address].push_back(std::move(tomo_rule_responder));

  // 3. Wrap up rules into ruleset and send them to prpoer partners
  // 3.1 wrap up rulesets
  unsigned long ruleset_id = createUniqueId();
  for (auto it = rules_map.begin(); it != rules_map.end(); ++it) {
    int owner_address = it->first;
    auto rules = std::move(it->second);
    RuleSet ruleset(ruleset_id, owner_address);
    for (int i = 0; i < rules.size(); i++) {
      auto rule = std::move(rules.at(i));
      auto appended_rule = ruleset.addRule(std::move(rule));
      if (appended_rule->is_finalized) {
        // if the rule is entanglement swapping or tomography rule, no need to specify the next rule
        break;
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

  // validating QNIC type
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
  QNIC_id left_partner_qnic = qnics.at(left_partner_index).snd;
  QNIC_id right_partner_qnic = qnics.at(right_partner_index).fst;

  if (right_self_qnic.type == QNIC_RP || left_self_qnic.type == QNIC_RP || right_partner_qnic.type == QNIC_RP || left_partner_qnic.type == QNIC_RP) {
    error("MSM link not implemented");
  }

  SwappingConfig config;
  config.left_partner = left_partner;
  config.lres = num_resources;
  config.right_partner = right_partner;
  config.rres = num_resources;

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

std::unique_ptr<Rule> ConnectionManager::purifyRule(int partner_address, PurType purification_type, double threshold_fidelity, int shared_tag, std::string name) {
  auto purify_rule = std::make_unique<Rule>(partner_address, shared_tag, false);
  purify_rule->setName(name);

  // decide how many Bell pairs are required
  int num_resource;
  if (purification_type == PurType::SINGLE_X || purification_type == PurType::SINGLE_Z) {
    num_resource = 2;
  } else if (purification_type == PurType::DOUBLE || purification_type == PurType::DOUBLE_INV || purification_type == PurType::DSSA || purification_type == PurType::DSSA_INV) {
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
  auto enough_resource_clause = std::make_unique<EnoughResourceConditionClause>(num_resource, threshold_fidelity, partner_address);
  condition->addClause(std::move(enough_resource_clause));
  purify_rule->setCondition(std::move(condition));

  // prepare action
  auto purify_action = std::make_unique<Purification>(purification_type, partner_address);
  purify_rule->setAction(std::move(purify_action));

  return purify_rule;
}

std::unique_ptr<Rule> ConnectionManager::swapRule(std::vector<int> partner_address, double threshold_fidelity, int shared_tag, std::string name) {
  auto swap_rule = std::make_unique<Rule>(partner_address, shared_tag, true);
  swap_rule->setName(name);

  // prepare condition and two enough resource clauses
  auto condition = std::make_unique<Condition>();
  auto enough_resource_clause_first = std::make_unique<EnoughResourceConditionClause>(1, threshold_fidelity, partner_address.at(0));
  auto enough_resource_clause_second = std::make_unique<EnoughResourceConditionClause>(1, threshold_fidelity, partner_address.at(1));
  condition->addClause(std::move(enough_resource_clause_first));
  condition->addClause(std::move(enough_resource_clause_second));
  swap_rule->setCondition(std::move(condition));

  auto swap_action = std::make_unique<EntanglementSwapping>(partner_address);
  swap_rule->setAction(std::move(swap_action));

  return swap_rule;
}

std::unique_ptr<Rule> ConnectionManager::waitRule(int partner_address, int shared_tag, std::string name) {
  auto wait_rule = std::make_unique<Rule>(partner_address, shared_tag, false);
  wait_rule->setName(name);

  auto condition = std::make_unique<Condition>();
  auto wait_clause = std::make_unique<WaitConditionClause>(partner_address);
  condition->addClause(std::move(wait_clause));
  wait_rule->setCondition(std::move(condition));

  auto wait_action = std::make_unique<Wait>(partner_address);
  wait_rule->setAction(std::move(wait_action));

  return wait_rule;
}

std::unique_ptr<Rule> ConnectionManager::tomographyRule(int partner_address, int owner_address, int num_measure, double threshold_fidelity, int shared_tag, std::string name) {
  auto tomography_rule = std::make_unique<Rule>(partner_address, shared_tag, true);
  tomography_rule->setName(name);

  // prepare condition
  auto condition = std::make_unique<Condition>();
  auto enough_resource_clause = std::make_unique<EnoughResourceConditionClause>(1, threshold_fidelity, partner_address);
  auto measure_count_clause = std::make_unique<MeasureCountConditionClause>(num_measure, partner_address);
  condition->addClause(std::move(enough_resource_clause));
  condition->addClause(std::move(measure_count_clause));
  tomography_rule->setCondition(std::move(condition));

  // prepare action
  auto tomography_action = std::make_unique<Tomography>(num_measure, owner_address, partner_address);
  tomography_rule->setAction(std::move(tomography_action));

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

}  // namespace quisp::modules

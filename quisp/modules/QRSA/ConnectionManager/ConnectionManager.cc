/** \file ConnectionManager.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo,cocori,rdv
 *
 *  \brief ConnectionManager
 */

#include "ConnectionManager.h"
#include <iterator>
#include <memory>
#include <string>
#include <utility>
#include "modules/QRSA/HardwareMonitor/HardwareMonitor.h"
#include "utils/ComponentProvider.h"

using namespace omnetpp;
using namespace quisp::messages;
using namespace quisp::rules;

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

  if (simultaneous_es_enabled && es_with_purify) {
    error("Currently, simultaneous entanglement swapping cannot be simulated with purification");
  }

  for (int i = 0; i < num_of_qnics; i++) {
    // qnode address
    qnic_res_table.insert(std::make_pair(i, false));
  }
}

/**
 * The catch-all handler for messages received.  Needs to confirm the packet type and call the appropriate lower-level handler.
 * \param msg pointer to the cMessage itself
 */
void ConnectionManager::handleMessage(cMessage *msg) {
  if (dynamic_cast<ConnectionSetupRequest *>(msg) != nullptr) {
    ConnectionSetupRequest *req = check_and_cast<ConnectionSetupRequest *>(msg);
    int actual_dst = req->getActual_destAddr();
    int actual_src = req->getActual_srcAddr();

    if (actual_dst == my_address) {
      // got ConnectionSetupRequest and return the response
      respondToRequest(req);
      delete msg;
      return;
    }

    int local_qnic_address_to_actual_dst = routing_daemon->return_QNIC_address_to_destAddr(actual_dst);
    auto dst_inf = hardware_monitor->findConnectionInfoByQnicAddr(local_qnic_address_to_actual_dst);
    bool is_qnic_available = !isQnicBusy(dst_inf->qnic.address);
    bool requested_by_myself = actual_src == my_address;

    if (requested_by_myself) {
      if (is_qnic_available) {
        // reserve the qnic and relay the request to the next node
        relayRequestToNextHop(req);
        return;
      }

      // cannot accept this request because the qnic is unavailable.
      rejectRequest(req);
      return;
    }

    // got ConnectionSetupRequest as the intermediate node
    // reserve the qnic and relay the request to the next node
    relayRequestToNextHop(req);
    return;
  }

  if (dynamic_cast<ConnectionSetupResponse *>(msg) != nullptr) {
    ConnectionSetupResponse *resp = check_and_cast<ConnectionSetupResponse *>(msg);
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

  if (dynamic_cast<RejectConnectionSetupRequest *>(msg) != nullptr) {
    RejectConnectionSetupRequest *pk = check_and_cast<RejectConnectionSetupRequest *>(msg);
    int actual_src = pk->getActual_srcAddr();
    // Umm... this might be bug.
    if (actual_src != my_address) {
      intermediate_reject_req_handler(pk);
      delete msg;
    }
    return;
  }
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
 * \todo Where should timeouts and error handling happen?
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
  RejectConnectionSetupRequest *packet = new RejectConnectionSetupRequest("RejectConnSetup");
  packet->setKind(6);
  packet->setDestAddr(req->getActual_srcAddr());
  packet->setSrcAddr(my_address);
  packet->setActual_destAddr(req->getActual_destAddr());
  packet->setActual_srcAddr(req->getActual_srcAddr());
  send(packet, "RouterPort$o");
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
 * \todo Always room to make this better.  Ideally should be
 * a _configurable choice_, or even a _policy_ implementation.
 */
void ConnectionManager::respondToRequest(ConnectionSetupRequest *req) {
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
  QNIC_id_pair pair_info = {.fst = src_info->qnic, .snd = dst_info->qnic};

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
  QNIC_id_pair qnic_pairs;
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
  std::map<int, RuleSet *> ruleset_map;  // <node address, RuleSet pointer>
  for (int i = 0; i < path.size(); i++) {
    int ruleset_owner = path.at(i);
    RuleSet *ruleset = new RuleSet(ruleset_id, ruleset_owner, {});  // start from empty partners
    ruleset_map.insert(std::make_pair(ruleset_owner, ruleset));
  }
  // 1. add purification rules to the ruleset (policy: do purification before entanglement swapping)
  // 1.1 check purification pairs
  if (es_with_purify) {
    std::map<int, std::vector<int>> purification_partners;  // <owner address, {partners}>
    for (int i = 1; i < path.size() - 1; i++) {  // from the first swapper to the last swapper.
      // we reuse the swapping config
      auto espartners = swapping_partners[path.at(i)];
      int left_partner = espartners.at(0);
      int right_partner = espartners.at(1);
      // 1.2 add them to the purification partner
      purification_partners[path.at(i)].push_back(left_partner);
      purification_partners[path.at(i)].push_back(right_partner);
      // // 1.3 from left and right partner, this node is also the partner
      // purification_partners[left_partner].push_back(path.at(i));
      // purification_partners[right_partner].push_back(path.at(i));
    }
    // 1.4 add final purification between two endnodes.
    purification_partners[path.at(0)].push_back(path.at(path.size() - 1));
    // purification_partners[path.at(path.size()-1)].push_back(path.at(0));

    // 1.5 generate purification entanglements
    for (auto purification_map = purification_partners.begin(); purification_map != purification_partners.end(); ++purification_map) {
      int rule_owner = purification_map->first;
      auto rule_partners = purification_map->second;
      // 1.5.1 loop for all partners and share the same rule ids
      for (int partner_address : rule_partners) {
        unsigned long rule_id = createUniqueId();  // not the ruleset id
        // purificationRule(int partner_address, int purification_type, int num_purification, QNIC_type qnic_type, int qnic_index, unsigned long ruleset_id, int rule_id) {
        // get the qnic interface from owner to partner
        // owner --> partner
        QNIC_id qnic_info_owner = getQnicInterface(rule_owner, partner_address, path, qnics);
        // purification rule for owner
        auto owner_purification_rule = purificationRule(partner_address, 0, num_remote_purification, qnic_info_owner.type, qnic_info_owner.index, ruleset_id, rule_id);
        ruleset_map[rule_owner]->addRule(std::move(owner_purification_rule));

        // owner <-- partner
        QNIC_id qnic_info_partner = getQnicInterface(partner_address, rule_owner, path, qnics);
        auto partner_purification_rule = purificationRule(rule_owner, 0, num_remote_purification, qnic_info_partner.type, qnic_info_partner.index, ruleset_id, rule_id);
        ruleset_map[partner_address]->addRule(std::move(partner_purification_rule));
      }
    }
  }

  // 2. Entanglement Swapping Rules
  int resource_index = 0;  // always take the first resource
  for (int i = 1; i < path.size() - 1; i++) {  // loop for intermediate nodes
    int swapper_address = path.at(i);

    if (!simultaneous_es_enabled) {
      // 2.1 generate configs for entanglement swapping
      SwappingConfig config = generateSwappingConfig(swapper_address, path, swapping_partners, qnics, resource_index);
      // 2.2 prepare entanglement swapping rule
      unsigned long rule_id = createUniqueId();
      auto rule_es = swappingRule(config, ruleset_id, rule_id);
      ruleset_map[swapper_address]->addRule(std::move(rule_es));
    } else {
      SwappingConfig config = generateSimultaneousSwappingConfig(swapper_address, path, qnics, resource_index);
      unsigned long rule_id = createUniqueId();
      auto rule_es = simultaneousSwappingRule(config, path, ruleset_id, rule_id);
      ruleset_map[swapper_address]->addRule(std::move(rule_es));
    }
  }

  // 3. Tomography Rules for endnodes (This would be replaced to transfer ownership)
  int initiator_address = path.at(0);
  int responder_address = my_address;
  int num_measure = req->getNum_measure();
  QNIC_id initiator_qnic = getQnicInterface(initiator_address, responder_address, path, qnics);
  QNIC_id responder_qnic = getQnicInterface(responder_address, initiator_address, path, qnics);
  unsigned long rule_id = createUniqueId();
  auto tomography_rule_initiator = tomographyRule(initiator_address, responder_address, num_measure, initiator_qnic.type, initiator_qnic.index, ruleset_id, rule_id);
  auto tomography_rule_responder = tomographyRule(responder_address, initiator_address, num_measure, responder_qnic.type, responder_qnic.index, ruleset_id, rule_id);
  ruleset_map[initiator_address]->addRule(std::move(tomography_rule_initiator));
  ruleset_map[responder_address]->addRule(std::move(tomography_rule_responder));

  // 4. send rulesets to nodes
  for (auto it = ruleset_map.begin(); it != ruleset_map.end(); ++it) {
    int owner_address = it->first;
    auto ruleset = it->second;
    ConnectionSetupResponse *pkt = new ConnectionSetupResponse("Connection Setup Response");
    pkt->setDestAddr(owner_address);
    pkt->setSrcAddr(my_address);
    pkt->setKind(2);
    pkt->setRuleSet(ruleset);
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
 * \todo node_address might be better using qnic index
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
  /// \todo hypothetically, with no purification, all of the intermediate
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
  EV << "swapping" << left_partner << "<-->" << swapper_address << "<-->" << right_partner << "\n";
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
 *  This method is called to handle the ConnectionSetupRequest at an intermediate or initiator node.
 *  This method reserves requested qnics and then send the request to next hop.
 * \param req pointer to the ConnectionSetupRequest packet itself
 * \returns nothing
 **/
void ConnectionManager::relayRequestToNextHop(ConnectionSetupRequest *req) {
  int responder_addr = req->getActual_destAddr();  // responder address
  int initiator_addr = req->getActual_srcAddr();  // initiator address (to get input qnic)
  int dst_qnic_addr = routing_daemon->return_QNIC_address_to_destAddr(responder_addr);
  int src_qnic_addr = routing_daemon->return_QNIC_address_to_destAddr(initiator_addr);
  if (dst_qnic_addr == -1) {
    error("QNIC to destination not found");
  }

  // Use the QNIC address to find the next hop QNode, by asking the Hardware Monitor (neighbor table).
  auto dst_info = hardware_monitor->findConnectionInfoByQnicAddr(dst_qnic_addr);
  auto src_info = hardware_monitor->findConnectionInfoByQnicAddr(src_qnic_addr);
  int num_accumulated_nodes = req->getStack_of_QNodeIndexesArraySize();
  int num_accumulated_costs = req->getStack_of_linkCostsArraySize();
  int num_accumulated_pair_info = req->getStack_of_QNICsArraySize();

  // Update information and send it to the next Qnode.
  req->setDestAddr(dst_info->neighbor_address);
  req->setSrcAddr(my_address);
  req->setStack_of_QNodeIndexesArraySize(num_accumulated_nodes + 1);
  req->setStack_of_linkCostsArraySize(num_accumulated_costs + 1);
  req->setStack_of_QNodeIndexes(num_accumulated_nodes, my_address);
  req->setStack_of_linkCosts(num_accumulated_costs, dst_info->quantum_link_cost);
  req->setStack_of_QNICsArraySize(num_accumulated_pair_info + 1);

  bool is_dst_qnic_reserved = isQnicBusy(dst_info->qnic.address);
  bool is_src_qnic_reserved = false;

  bool is_initiator = my_address == initiator_addr;

  if (is_initiator) {
    src_info = std::make_unique<ConnectionSetupInfo>(NULL_CONNECTION_SETUP_INFO);
  } else {
    if (src_info == nullptr) {
      error("source qnic not found");
    }
    is_src_qnic_reserved = isQnicBusy(src_info->qnic.address);
  }

  if (is_src_qnic_reserved || is_dst_qnic_reserved) {
    rejectRequest(req);
    return;
  }

  QNIC_id_pair pair_info = {.fst = src_info->qnic, .snd = dst_info->qnic};
  req->setStack_of_QNICs(num_accumulated_pair_info, pair_info);

  if (!is_initiator) {
    reserveQnic(src_info->qnic.address);
  }
  reserveQnic(dst_info->qnic.address);

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

/**
 *  This function is called during the handling of ConnectionSetupRequest at the responder.
 * \param pk pointer to the ConnectionSetupRequest packet itself
 * \returns nothing
 * \todo needs to be filled in!
 * This function is called when we discover that we can't fulfill the connection request,
 * primarily due to resource reservation conflicts.
 **/
void ConnectionManager::responder_reject_req_handler(RejectConnectionSetupRequest *pk) {}

/**
 *  This function is called during the handling of ConnectionSetupRequest at an
 *  intermediate node (not the initator or responder).
 * \param pk pointer to the ConnectionSetupRequest packet itself
 * \returns nothing
 * \todo needs to be filled in!
 * This function is called when we discover that we can't fulfill the connection request,
 * primarily due to resource reservation conflicts.
 **/
void ConnectionManager::intermediate_reject_req_handler(RejectConnectionSetupRequest *pk) {
  // here we have to implement when the rejection packet received.
  // free reserved qnics
  int actual_dst = pk->getActual_destAddr();  // responder address
  int actual_src = pk->getActual_srcAddr();  // initiator address (to get input qnic)
  // Currently, sending path and returning path are same, but for future, this might not good way
  int local_qnic_address_to_actual_dst = routing_daemon->return_QNIC_address_to_destAddr(actual_dst);
  int local_qnic_address_to_actual_src = routing_daemon->return_QNIC_address_to_destAddr(actual_src);
  auto dst_info = hardware_monitor->findConnectionInfoByQnicAddr(local_qnic_address_to_actual_dst);
  auto src_info = hardware_monitor->findConnectionInfoByQnicAddr(local_qnic_address_to_actual_src);
  if (my_address != actual_dst && my_address != actual_src) {
    releaseQnic(dst_info->qnic.address);
    releaseQnic(src_info->qnic.address);
    return;
  }

  if (my_address == actual_dst) {
    releaseQnic(src_info->qnic.address);
  }
  if (my_address == actual_src) {
    releaseQnic(dst_info->qnic.address);
  }
}

// Rule Generators
std::unique_ptr<Rule> ConnectionManager::purificationRule(int partner_address, int purification_type, int num_purification, QNIC_type qnic_type, int qnic_index,
                                                          unsigned long ruleset_id, unsigned long rule_id) {
  std::string pur_name = "";
  if (purification_type == 0) {
    pur_name = "X purification with : " + std::to_string(partner_address);
  } else if (purification_type == 1) {
    pur_name = "Z purification with : " + std::to_string(partner_address);
  }
  std::vector<int> partners = {partner_address};
  auto rule_purification = std::make_unique<Rule>(ruleset_id, rule_id, pur_name, partners);
  if (purification_type == 0) {
    // X purification (should prepare enum with purification)
    Condition *condition = new Condition();
    Clause *resource_clause = new EnoughResourceClause(partner_address, 2);  // to prepare 1 purified entanglement, we need 2 raw entanglements
    condition->addClause(resource_clause);
    rule_purification->setCondition(condition);
    // PurifyAction(unsigned long RuleSet_id, unsigned long rule_id, bool X_purification, bool Z_purification, int num_purification, int part, QNIC_type qt, int qi, int res, int
    // tres);
    Action *purify_action = new PurifyAction(ruleset_id, rule_id, true, false, num_purification, partner_address, qnic_type, qnic_index, 0, 1);
    rule_purification->setAction(purify_action);
  } else if (purification_type == 1) {
    // Z purification (should prepare enum with purification)
    Condition *condition = new Condition();
    Clause *resource_clause = new EnoughResourceClause(partner_address, 2);  // to prepare 1 purified entanglement, we need 2 raw entanglements
    condition->addClause(resource_clause);
    rule_purification->setCondition(condition);
    // PurifyAction(unsigned long RuleSet_id, unsigned long rule_index, bool X_purification, bool Z_purification, int num_purification, int part, QNIC_type qt, int qi, int res, int
    // tres);
    Action *purify_action = new PurifyAction(ruleset_id, rule_id, false, true, num_purification, partner_address, qnic_type, qnic_index, 0, 1);
    rule_purification->setAction(purify_action);
  } else {
    error("Unknown purification type");
  }
  return rule_purification;
}

std::unique_ptr<Rule> ConnectionManager::swappingRule(SwappingConfig conf, unsigned long ruleset_id, unsigned long rule_id) {
  std::vector<int> partners = {conf.left_partner, conf.right_partner};
  std::string rule_name = "Entanglement Swapping with " + std::to_string(conf.left_partner) + " : " + std::to_string(conf.right_partner);
  auto rule_entanglement_swapping = std::make_unique<Rule>(ruleset_id, rule_id, rule_name, partners);
  Condition *condition = new Condition();
  Clause *resource_clause_left = new EnoughResourceClause(conf.left_partner, conf.lres);
  Clause *resource_clause_right = new EnoughResourceClause(conf.right_partner, conf.rres);
  condition->addClause(resource_clause_left);
  condition->addClause(resource_clause_right);
  rule_entanglement_swapping->setCondition(condition);
  Action *action = new SwappingAction(ruleset_id, rule_id, conf.left_partner, conf.lqnic_type, conf.lqnic_index, conf.lqnic_address, conf.lres, conf.right_partner, conf.rqnic_type,
                                      conf.rqnic_index, conf.rqnic_address, conf.rres, conf.self_left_qnic_index, conf.self_left_qnic_type, conf.self_right_qnic_index,
                                      conf.self_right_qnic_type);
  rule_entanglement_swapping->setAction(action);
  return rule_entanglement_swapping;
}

std::unique_ptr<Rule> ConnectionManager::simultaneousSwappingRule(SwappingConfig conf, std::vector<int> path, unsigned long ruleset_id, unsigned long rule_id) {
  // From @poramet implementations
  std::vector<int> partners = {conf.left_partner, conf.right_partner};
  std::string rule_name = "Simultaneous Entanglement Swapping with " + std::to_string(conf.left_partner) + " : " + std::to_string(conf.right_partner);
  int index_in_path = conf.index;
  int path_length_exclude_IR = path.size() - 2;

  auto rule_simultaneous_entanglement_swapping = std::make_unique<Rule>(ruleset_id, rule_id, rule_name, partners);
  Condition *condition = new Condition();
  Clause *resource_clause_left = new EnoughResourceClause(conf.left_partner, conf.lres);
  Clause *resource_clause_right = new EnoughResourceClause(conf.right_partner, conf.rres);
  condition->addClause(resource_clause_left);
  condition->addClause(resource_clause_right);

  quisp::rules::Action *action = new SimultaneousSwappingAction(
      ruleset_id, rule_id, conf.left_partner, conf.lqnic_type, conf.lqnic_index, conf.lqnic_address, conf.lres, conf.right_partner, conf.rqnic_type, conf.rqnic_index,
      conf.rqnic_address, conf.rres, conf.self_left_qnic_index, conf.self_left_qnic_type, conf.self_right_qnic_index, conf.self_right_qnic_type, conf.initiator,
      conf.initiator_qnic_type, conf.initiator_qnic_index, conf.initiator_qnic_address, conf.initiator_res, conf.responder, conf.responder_qnic_type, conf.responder_qnic_index,
      conf.responder_qnic_address, conf.responder_res, index_in_path, path_length_exclude_IR);

  rule_simultaneous_entanglement_swapping->setCondition(condition);
  rule_simultaneous_entanglement_swapping->setAction(action);
  return rule_simultaneous_entanglement_swapping;
}

std::unique_ptr<Rule> ConnectionManager::tomographyRule(int owner_address, int partner_address, int num_measure, QNIC_type qnic_type, int qnic_index, unsigned long ruleset_id,
                                                        unsigned long rule_id) {
  std::vector<int> partners = {partner_address};
  auto tomography_rule = std::make_unique<Rule>(ruleset_id, rule_id, "tomography", partners);
  Condition *condition = new Condition();
  Clause *count_clause = new MeasureCountClause(num_measure);
  Clause *resource_clause = new EnoughResourceClause(partner_address, 1);
  // Technically, there is no condition because an available resource is guaranteed whenever the rule is ran.
  condition->addClause(count_clause);
  condition->addClause(resource_clause);
  tomography_rule->setCondition(condition);
  Action *action = new RandomMeasureAction(owner_address, partner_address, qnic_type, qnic_index, 0, num_measure);
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

}  // namespace modules
}  // namespace quisp

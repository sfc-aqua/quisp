/** \file ConnectionManager.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo,cocori,rdv
 *
 *  \brief ConnectionManager
 */

#include "ConnectionManager.h"

using namespace omnetpp;
using namespace quisp::messages;
using namespace quisp::rules;

namespace quisp {
namespace modules {

void ConnectionManager::initialize() {
  routing_daemon = check_and_cast<RoutingDaemon *>(getParentModule()->getSubmodule("rd"));
  hardware_monitor = check_and_cast<HardwareMonitor *>(getParentModule()->getSubmodule("hm"));
  my_address = par("address");
  num_of_qnics = par("total_number_of_qnics");

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
  packet->setNumber_of_required_Bellpairs(req->getNumber_of_required_Bellpairs());
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

  // create RuleSet for all nodes!
  int num_resource = req->getNumber_of_required_Bellpairs();
  int intermediate_node_size = req->getStack_of_QNodeIndexesArraySize();
  for (int i = 0; i <= intermediate_node_size; i++) {
    auto itr = std::find(swappers.begin(), swappers.end(), path.at(i));
    size_t index = std::distance(swappers.begin(), itr);
    if (index != swappers.size()) {
      EV_DEBUG << "Im swapper!" << path.at(i) << "\n";
      // generate Swapping RuleSet
      // here we have to check the order of entanglement swapping

      // swapping configurations for path[i]
      SwappingConfig config = generateSwappingConfig(path.at(i), path, swapping_partners, qnics, num_resource);
      RuleSet *rule = generateEntanglementSwappingRuleSet(path.at(i), config);

      ConnectionSetupResponse *pkr = new ConnectionSetupResponse("ConnSetupResponse(Swapping)");
      pkr->setDestAddr(path.at(i));
      pkr->setSrcAddr(my_address);
      pkr->setKind(2);
      pkr->setRuleSet(rule);
      pkr->setActual_srcAddr(path.at(0));
      pkr->setActual_destAddr(path.at(path.size() - 1));
      send(pkr, "RouterPort$o");

    } else {
      EV_DEBUG << "Im not swapper!" << path.at(i) << "\n";
      int num_measure = req->getNum_measure();

      RuleSet *ruleset;
      int owner = path.at(i);
      if (i == 0) {  // if this is initiator
        ruleset = generateTomographyRuleSet(owner, path.at(path.size() - 1), num_measure, qnics.at(qnics.size() - 1).fst.type, qnics.at(qnics.size() - 1).fst.index, num_resource);
      } else {  // if this is responder
        ruleset = generateTomographyRuleSet(owner, path.at(0), num_measure, qnics.at(0).snd.type, qnics.at(0).snd.index, num_resource);
      }

      ConnectionSetupResponse *pkr = new ConnectionSetupResponse("ConnSetupResponse(Tomography)");
      pkr->setDestAddr(path.at(i));
      pkr->setSrcAddr(my_address);
      pkr->setKind(2);
      pkr->setRuleSet(ruleset);
      pkr->setActual_srcAddr(path.at(0));
      pkr->setActual_destAddr(path.at(path.size() - 1));

      // this is not application but for checking swapping done properly.
      pkr->setApplication_type(0);
      send(pkr, "RouterPort$o");
    }
  }

  if (actual_dst != my_address) {
    reserveQnic(src_info->qnic.address);
    reserveQnic(dst_info->qnic.address);
  } else {
    reserveQnic(src_info->qnic.address);
  }
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

/**
 *  This function is called during the handling of ConnectionSetupRequest at the responder.
 * \param RuleSet_id the unique identifier for this RuleSet (== connection)
 * \param owner address of the intermediate node we are generating this RuleSet for
 * \param conf the SwappingConfig listing the order and partners
 * \returns the newly-created RuleSet for ES at the given intermediate node.
 *
 *  This is where much of the work happens, and there is the potential for new value
 *  if you have a better way to do this.
 *  Called once per intermediate node to create rules for that node, which will
 *  later be distributed to that node using a ConnectionSetupResponse.
 *  \todo
 * \todo Room for endless intelligence and improvements here.  Ideally should be
 * a _configurable choice_, or even a _policy_ implementation.
 **/
RuleSet *ConnectionManager::generateEntanglementSwappingRuleSet(int owner, SwappingConfig conf) {
  unsigned long ruleset_id = createUniqueId();
  int rule_index = 0;

  Clause *resource_clause_left = new EnoughResourceClauseLeft(conf.left_partner, conf.lres);
  Clause *resource_clause_right = new EnoughResourceClauseRight(conf.right_partner, conf.rres);

  Condition *condition = new Condition();
  condition->addClause(resource_clause_left);
  condition->addClause(resource_clause_right);

  quisp::rules::Action *action = new SwappingAction(ruleset_id, rule_index, conf.left_partner, conf.lqnic_type, conf.lqnic_index, conf.lqnic_address, conf.lres, conf.right_partner,
                                                    conf.rqnic_type, conf.rqnic_index, conf.rqnic_address, conf.rres, conf.self_left_qnic_index, conf.self_left_qnic_type,
                                                    conf.self_right_qnic_index, conf.self_right_qnic_type);

  Rule *rule = new Rule(ruleset_id, rule_index);
  rule->setCondition(condition);
  rule->setAction(action);

  std::vector<int> partners = {conf.left_partner, conf.right_partner};

  RuleSet *ruleset = new RuleSet(ruleset_id, owner, partners);
  ruleset->addRule(rule);
  ruleset->setRule_ptr(rule);

  return ruleset;
}

RuleSet *ConnectionManager::generateTomographyRuleSet(int owner, int partner, int num_of_measure, QNIC_type qnic_type, int qnic_index, int num_resources) {
  unsigned long ruleset_id = createUniqueId();

  int rule_index = 0;
  RuleSet *tomography = new RuleSet(ruleset_id, owner, partner);
  Rule *rule = new Rule(ruleset_id, rule_index);

  // 3000 measurements in total. There are 3*3 = 9 patterns of measurements. So each combination must perform 3000/9 measurements.
  Clause *count_clause = new MeasureCountClause(num_of_measure, partner, qnic_type, qnic_index, 0);
  Clause *resource_clause = new EnoughResourceClause(partner, num_resources);

  // Technically, there is no condition because an available resource is guaranteed whenever the rule is ran.
  Condition *condition = new Condition();
  condition->addClause(count_clause);
  condition->addClause(resource_clause);

  rule->setCondition(condition);

  // Measure the local resource between it->second.neighborQNode_address.
  quisp::rules::Action *action = new RandomMeasureAction(partner, qnic_type, qnic_index, 0, owner, num_of_measure);
  rule->setAction(action);

  // Add the rule to the RuleSet
  tomography->addRule(rule);
  tomography->finalize();

  return tomography;
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

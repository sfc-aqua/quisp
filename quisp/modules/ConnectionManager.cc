/** \file ConnectionManager.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo,cocori,rdv
 *
 *  \brief ConnectionManager
 */
#include <classical_messages_m.h>
#include <modules/QNIC.h>
#include <omnetpp.h>
#include <rules/RuleSet.h>
#include <vector>
#include "HardwareMonitor.h"
#include "RoutingDaemon.h"
#include "RuleEngine.h"

using namespace omnetpp;
using namespace quisp::messages;
using namespace quisp::rules;

namespace quisp {
namespace modules {

typedef struct swapping_rule_table {  // This is a little bit redundunt
  int left_partner;
  QNIC_type lqnic_type;
  int lqnic_index;
  int lqnic_address;
  int lres;
  int right_partner;
  QNIC_type rqnic_type;
  int rqnic_index;
  int rqnic_address;
  int rres;
  int self_left_qnic_index;
  QNIC_type self_left_qnic_type;
  int self_right_qnic_index;
  QNIC_type self_right_qnic_type;
} swap_table;

/** \class ConnectionManager ConnectionManager.cc
 *  \todo Documentation of the class header.
 *
 *  \brief ConnectionManager
 *
 * The ConnectionManager is one of the five key modules in the
 * software for a quantum repeater/router (qrsa).  It is responsible for
 * managing the connections: initiating ConnectionSetupRequests,
 * behaving as responder for a ConnectionSetupRequest (which involves
 * actually creating the RuleSets), and handling the requests and
 * responses as the move along the path at setup time.
 *
 * It communicates with the RuleEngine, which is responsible for
 * actually executing the Rules as it is notified of events, but
 * the ConnectionManager has _nothing_ to do with the actual
 * processing of the quantum states as they evolve.
 *
 * You will see member functions for the roles as initiator, responder,
 * and intermediate node.  The main tasks are to respond to ConnectionSetupRequest,
 * ConnectionSetupResponse, RejectConnectionSetupRequest, and ConnectionTeardown messages.
 *
 * It is also responsible for the end-to-end reservation of resources,
 * as dictated by the multiplexing (muxing) discpline in use.
 */
class ConnectionManager : public cSimpleModule {
 private:
  int myAddress;
  int num_of_qnics;
  std::map<int, bool> qnic_res_table;
  RoutingDaemon *routingdaemon;
  HardwareMonitor *hardwaremonitor;

 protected:
  virtual void initialize() override;

  virtual void handleMessage(cMessage *msg) override;
  virtual void responder_alloc_req_handler(ConnectionSetupRequest *pk);
  virtual void intermediate_alloc_req_handler(ConnectionSetupRequest *pk);

  virtual void initiator_alloc_res_handler(ConnectionSetupResponse *pk);
  virtual void intermediate_alloc_res_handler(ConnectionSetupResponse *pk);

  virtual void responder_reject_req_handler(RejectConnectionSetupRequest *pk);
  virtual void intermediate_reject_req_handler(RejectConnectionSetupRequest *pk);

  // virtual RuleSet* generateRuleSet_EntanglementSwapping(unsigned int RuleSet_id,int owner, int left_node, QNIC_type lqnic_type, int lqnic_index, int lres, int right_node,
  // QNIC_type rqnic_type, int rqnic_index, int rres);
  virtual RuleSet *generateRuleSet_Tomography(unsigned long RuleSet_id, int owner, int partner, int num_measure, QNIC_type qnic_type, int qnic_index, int num_resources);
  virtual RuleSet *generateRuleSet_EntanglementSwapping(unsigned long RuleSet_id, int owner, swap_table conf);
  virtual swap_table EntanglementSwappingConfig(int swapper_address, std::vector<int> path, std::map<int, std::vector<int>> swapping_partners, std::vector<QNIC_pair_info> qnics,
                                                int num_resources);

  virtual void reserve_qnic(int qnic_address);
  virtual void release_qnic(int qnic_address);
  virtual bool isQnic_busy(int qnic_address);

  virtual unsigned long createUniqueId();
};

Define_Module(ConnectionManager);

void ConnectionManager::initialize() {
  EV << "ConnectionManager booted\n";
  cModule *rd = getParentModule()->getSubmodule("rd");
  routingdaemon = check_and_cast<RoutingDaemon *>(rd);
  cModule *hm = getParentModule()->getSubmodule("hm");
  hardwaremonitor = check_and_cast<HardwareMonitor *>(hm);
  myAddress = par("address");
  num_of_qnics = par("total_number_of_qnics");

  for (int i = 0; i < num_of_qnics; i++) {
    // qnode address
    qnic_res_table.insert(std::make_pair(i, false));
  }
}

/**
 * The catch-all handler for messages received.  Needs to confirm the packet
 * type and call the appropriate lower-level handler.
 * \param msg pointer to the cMessage itself
 */
void ConnectionManager::handleMessage(cMessage *msg) {
  if (dynamic_cast<ConnectionSetupRequest *>(msg) != nullptr) {
    ConnectionSetupRequest *pk = check_and_cast<ConnectionSetupRequest *>(msg);
    int actual_dst = pk->getActual_destAddr();
    int actual_src = pk->getActual_srcAddr();

    if (actual_dst == myAddress) {
      // got ConnectionSetupRequest and return the response
      responder_alloc_req_handler(pk);
      delete msg;
      return;
    }

    int local_qnic_address_to_actual_dst = routingdaemon->return_QNIC_address_to_destAddr(actual_dst);
    connection_setup_inf dst_inf = hardwaremonitor->return_setupInf(local_qnic_address_to_actual_dst);
    bool is_qnic_available = isQnic_busy(dst_inf.qnic.address);
    bool requested_by_myself = actual_src == myAddress;

    if (requested_by_myself) {
      if (is_qnic_available) {
        // reserve the qnic and relay the request to the next node
        intermediate_alloc_req_handler(pk);
        return;
      }

      // cannot accept this request because the qnic is unavailable, so reject it.
      RejectConnectionSetupRequest *pkt = new RejectConnectionSetupRequest;
      pkt->setKind(6);
      pkt->setDestAddr(pk->getActual_srcAddr());
      pkt->setSrcAddr(myAddress);
      pkt->setActual_destAddr(pk->getActual_destAddr());
      pkt->setActual_srcAddr(pk->getActual_srcAddr());
      pkt->setNumber_of_required_Bellpairs(pk->getNumber_of_required_Bellpairs());
      send(pkt, "RouterPort$o");
      return;
    }

    // got ConnectionSetupRequest as the intermediate node
    // reserve the qnic and relay the request to the next node
    intermediate_alloc_req_handler(pk);
    return;
  }

  if (dynamic_cast<ConnectionSetupResponse *>(msg) != nullptr) {
    ConnectionSetupResponse *pk = check_and_cast<ConnectionSetupResponse *>(msg);
    int initiator_addr = pk->getActual_destAddr();
    int responder_addr = pk->getActual_srcAddr();

    if (initiator_addr == myAddress || responder_addr == myAddress) {
      // this node is not a swapper
      initiator_alloc_res_handler(pk);
    } else {
      // this node is a swapper (intermediate node)
      // currently, destinations are separated. (Not accumulated.)
      intermediate_alloc_res_handler(pk);
    }
    delete msg;
    return;
  }

  if (dynamic_cast<RejectConnectionSetupRequest *>(msg) != nullptr) {
    RejectConnectionSetupRequest *pk = check_and_cast<RejectConnectionSetupRequest *>(msg);
    int actual_src = pk->getActual_srcAddr();
    // Umm... this might be bug.
    if (actual_src != myAddress) {
      intermediate_reject_req_handler(pk);
      delete msg;
    }
    return;
  }
}

// might just be 2*l
static int compute_path_division_size(int l /**< number of links (path length, number of nodes -1) */) {
  if (l > 1) {
    int hl = (l >> 1);
    return compute_path_division_size(hl) + compute_path_division_size(l - hl) + 1;
  }
  return l;
}

/** Treat subpath [i:...] of length l */
static int fill_path_division(std::vector<int> path /**< Nodes on the connection setup path */, int i /**< Left of the subpath to consider */, int l /**< Length of the subpath */,
                              int *link_left /**< Left part of the list of "links" */, int *link_right /**< Right part */,
                              int *swapper /**< Swappers to create those links (might be -1 for real links) */, int fill_start /** [0:fill_start[ is already filled */) {
  if (l > 1) {
    int hl = (l >> 1);
    fill_start = fill_path_division(path, i, hl, link_left, link_right, swapper, fill_start);
    fill_start = fill_path_division(path, i + hl, l - hl, link_left, link_right, swapper, fill_start);
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
 *  This function is called to handle the ConnectionSetupResponse at the initiator.
 * \param pk pointer to the ConnectionSetupRequest packet itself
 * \returns nothing
 *
 * The only job here is to unpack the RuleSets, feed them to the RuleEngine, and
 * start the connection running.  Probably should also let the Application know
 * that the setup is complete and running.
 *
 * \todo Where should timeouts and error handling happen?
 **/
void ConnectionManager::intermediate_alloc_res_handler(ConnectionSetupResponse *pk) {
  // here return ack?
  InternalRuleSetForwarding *pk_internal = new InternalRuleSetForwarding;
  pk_internal->setDestAddr(pk->getDestAddr());
  pk_internal->setSrcAddr(pk->getDestAddr());
  pk_internal->setKind(4);  // if here is setKind(1), packet is gonna go to App automatically.

  pk_internal->setRuleSet_id(pk->getRuleSet_id());
  pk_internal->setRuleSet(pk->getRuleSet());
  send(pk_internal, "RouterPort$o");
}

/**
 *  This function is called to handle the ConnectionSetupResponse at an "intermediate"
 *  node, one that is neither the initiator nor the responder.
 * \param pk pointer to the ConnectionSetupRequest packet itself
 * \returns nothing
 *
 * The only job here is to unpack the RuleSets, feed them to the RuleEngine, and
 * start the connection running.
 **/
void ConnectionManager::initiator_alloc_res_handler(ConnectionSetupResponse *pk) {
  // forward swapping rule
  // FIXME HACK This might not be better.
  InternalRuleSetForwarding_Application *pk_internal = new InternalRuleSetForwarding_Application;
  pk_internal->setDestAddr(pk->getDestAddr());
  pk_internal->setSrcAddr(pk->getDestAddr());  // Should be original Src here?
  pk_internal->setKind(4);  // if here is setKind(1), packet is gonna go to App automatically.

  pk_internal->setRuleSet_id(pk->getRuleSet_id());
  pk_internal->setRuleSet(pk->getRuleSet());
  pk_internal->setApplication_type(pk->getApplication_type());
  send(pk_internal, "RouterPort$o");
}

/**
 * This function is called to handle the ConnectionSetupRequest at the responder.
 *  This is where much of the work happens, and there is the potential for new value
 *  if you have a better way to do this.
 *  \param pk pointer to the ConnectionSetupRequest packet itself
 *  \returns nothing
 *
 * The procedure:
 * \verbatim
 * 1. figure out swapping order & partners by calling EntanglementSwappingConfig
 * 2. generate all the RuleSets by calling generateRuleSet_EntanglementSwapping
 * 3. return ConnectionSetupResponse to each node in this connection.
 * \endverbatim
 * \todo Always room to make this better.  Ideally should be
 * a _configurable choice_, or even a _policy_ implementation.
 */
void ConnectionManager::responder_alloc_req_handler(ConnectionSetupRequest *pk) {
  // Taking qnic information of responder node.
  int actual_dst = pk->getActual_destAddr();
  int actual_src = pk->getActual_srcAddr();  // initiator address (to get input qnic)
  int local_qnic_address_to_actual_dst = routingdaemon->return_QNIC_address_to_destAddr(actual_dst);  // This must be -1
  int local_qnic_address_to_actual_src = routingdaemon->return_QNIC_address_to_destAddr(actual_src);  // TODO: premise only oneconnection allowed btw, two nodes.
  connection_setup_inf dst_inf = hardwaremonitor->return_setupInf(local_qnic_address_to_actual_dst);
  connection_setup_inf src_inf = hardwaremonitor->return_setupInf(local_qnic_address_to_actual_src);
  QNIC_id_pair pair_info = {.fst = src_inf.qnic, .snd = dst_inf.qnic};
  bool isReserved_src = isQnic_busy(src_inf.qnic.address);
  bool isReserved_dst = isQnic_busy(dst_inf.qnic.address);
  if (!isReserved_src && !isReserved_dst) {
    // the number of steps
    int hop_count = pk->getStack_of_QNodeIndexesArraySize();

    // path pointer elements?
    std::vector<int> path;

    // path from source to destination
    for (int i = 0; i < hop_count; i++) {
      path.push_back(pk->getStack_of_QNodeIndexes(i));
    }
    path.push_back(myAddress);
    int divisions = compute_path_division_size(hop_count);
    int *link_left = new int[divisions], *link_right = new int[divisions], *swapper = new int[divisions];
    // fill_path_division should yield *exactly* the anticipated number of divisions.
    if (fill_path_division(path, 0, hop_count, link_left, link_right, swapper, 0) < divisions) {
      error("Something went wrong in path division computation.");
    }
    std::map<int, std::vector<int>> swapping_partners;
    for (int i = 0; i < divisions; i++) {
      std::vector<int> partners;
      if (swapper[i] > 0) {
        EV << link_left[i] << "---------------" << swapper[i] << "----------------" << link_right[i] << "\n";
        partners.push_back(link_left[i]);
        partners.push_back(link_right[i]);
        swapping_partners.insert(std::make_pair(swapper[i], partners));
      }
    }
    /* TODO: Remember you have link costs <3
    for(int i = 0; i<hop_count; i++){
        //The link cost is just a dummy variable (constant 1 for now and how it is set in a bad way (read from the channel but from only 1 channels from Src->BSA and ignoring
    BSA->Dest).
        //If you need to test with different costs, try changing the value.
        //But we need to implement actual link-tomography for this eventually.
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

    if (local_qnic_address_to_actual_dst != -1) {
      error("something error happen!");
    } else if (local_qnic_address_to_actual_src == -1) {
      error("This shouldn't happen!");
    }
    int qnic_array_size = pk->getStack_of_QNICsArraySize();
    pk->setStack_of_QNICsArraySize(qnic_array_size + 1);
    pk->setStack_of_QNICs(qnic_array_size, pair_info);

    // HACK This may be also not good way
    std::vector<QNIC_pair_info> qnics = {};
    QNIC_id_pair qnic_pairs;
    for (int i = 0; i < qnic_array_size + 1; i++) {
      qnic_pairs = pk->getStack_of_QNICs(i);
      qnics.push_back(qnic_pairs);
      // EV<<"qnic index"<<qnic_pairs.fst.index<<":::"<<qnic_pairs.snd.index<<"\n";
    }

    if (qnics.at(0).fst.index != -1 || qnics.at(qnics.size() - 1).snd.index != -1) {
      error("Qnic index of initiator and responder must be -1 in current scheme. ");
    }
    // node pairs! FIXME: really bad coding
    // Ummm... thinking good way
    // Here qunic processing
    // Have to add destination qnic info (destination is the same as myAddress. So qnic index must be -1 because self return is not allowed.)

    // create Ruleset for all nodes!
    int num_resource = pk->getNumber_of_required_Bellpairs();
    int intermediate_node_size = pk->getStack_of_QNodeIndexesArraySize();
    for (int i = 0; i <= intermediate_node_size; i++) {
      auto itr = std::find(swappers.begin(), swappers.end(), path.at(i));
      size_t index = std::distance(swappers.begin(), itr);
      if (index != swappers.size()) {
        EV << "Im swapper!" << path.at(i) << "\n";
        // generate Swapping RuleSet
        // here we have to check the order of entanglement swapping
        swap_table swap_config;  // swapping configurations for path[i]
        swap_config = EntanglementSwappingConfig(path.at(i), path, swapping_partners, qnics, num_resource);
        RuleSet *swapping_rule = generateRuleSet_EntanglementSwapping(createUniqueId(), path.at(i), swap_config);
        ConnectionSetupResponse *pkr = new ConnectionSetupResponse;
        pkr->setDestAddr(path.at(i));
        pkr->setSrcAddr(myAddress);
        pkr->setKind(2);
        pkr->setRuleSet(swapping_rule);
        pkr->setActual_srcAddr(path.at(0));
        pkr->setActual_destAddr(path.at(path.size() - 1));
        send(pkr, "RouterPort$o");
      } else {
        EV << "Im not swapper!" << path.at(i) << "\n";
        int num_measure = pk->getNum_measure();
        RuleSet *tomography_ruleset = nullptr;
        if (i == 0) {  // if this is initiater
          tomography_ruleset = generateRuleSet_Tomography(createUniqueId(), path.at(i), path.at(path.size() - 1), num_measure, qnics.at(qnics.size() - 1).fst.type,
                                                          qnics.at(qnics.size() - 1).fst.index, num_resource);
        } else {  // if this is responder
          tomography_ruleset = generateRuleSet_Tomography(createUniqueId(), path.at(i), path.at(0), num_measure, qnics.at(0).snd.type, qnics.at(0).snd.index, num_resource);
        }
        if (tomography_ruleset != nullptr) {
          ConnectionSetupResponse *pkr = new ConnectionSetupResponse;
          pkr->setDestAddr(path.at(i));
          pkr->setSrcAddr(myAddress);
          pkr->setKind(2);
          pkr->setRuleSet(tomography_ruleset);
          pkr->setActual_srcAddr(path.at(0));
          pkr->setActual_destAddr(path.at(path.size() - 1));
          // for(int j=0; j<intermediate_node_size;j++){
          //   pkr->setStack_of_QNodeIndexes(j, pk->getStack_of_QNodeIndexes(j));
          // }
          pkr->setApplication_type(0);  // this is not application but for checking Eswapping done properly.
          send(pkr, "RouterPort$o");
        } else {
          error("Something occured when the node %d creating ruleset", myAddress);
        }
      }
    }
    if (actual_dst != myAddress) {
      reserve_qnic(src_inf.qnic.address);
      reserve_qnic(dst_inf.qnic.address);
    } else {
      reserve_qnic(src_inf.qnic.address);
    }
  } else {
    RejectConnectionSetupRequest *pkt = new RejectConnectionSetupRequest;
    pkt->setKind(6);
    pkt->setDestAddr(pk->getActual_srcAddr());
    pkt->setSrcAddr(myAddress);
    pkt->setActual_destAddr(pk->getActual_destAddr());
    pkt->setActual_srcAddr(pk->getActual_srcAddr());
    pkt->setNumber_of_required_Bellpairs(pk->getNumber_of_required_Bellpairs());
    send(pkt, "RouterPort$o");
  }
}

/**
 *  This function is for selecting the order of entanglement swapping
 * \param swapper_address node address; could be any intermediate in the path (not an end point)
 * \param path list of node addresses in the path
 * \param qnics index and type of QNICs at each node in the path
 * \param num_resources the duration of the requested connection, in Bell pairs
 * \returns a swap_table
 * \todo node_address might be better using qnic index
 **/
swap_table ConnectionManager::EntanglementSwappingConfig(int swapper_address, std::vector<int> path, std::map<int, std::vector<int>> swapping_partners,
                                                         std::vector<QNIC_pair_info> qnics, int num_resources) {
  ///
  /// 1.recognize partner. (which node is left partner, right partner)
  /// Currently, we choose every other node in the path to do swapping in the first round.
  /// in the examples below, the number in parantheses is the round
  /// of swapping, and designates which nodes are swapping.
  /// if the number of hops is a power of two, we get something like
  /// \verbatim
  /// node1 --- node2(1) --- node3 --- node4(1) --- node5
  /// node1 ---------------- node3 ---------------- node5
  /// node1 ---------------- node3(2) ------------- node5
  /// node1 --------------------------------------- node5
  /// \endverbatim
  /// if the number of hops is not a power of two, at some stage
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
  swap_table swap_setting;
  int left_partner;
  int right_partner;
  QNIC_type lqnic_type, rqnic_type;
  int lqnic_index, rqnic_index;
  int lqnic_address, rqnic_address;
  int self_lqnic_index, self_rqnic_index;
  QNIC_type self_lqnic_type, self_rqnic_type;
  // actual configurations
  // If the counterparts are decided, the order will automatically be determined.

  auto iter = std::find(path.begin(), path.end(), swapper_address);
  size_t index = std::distance(path.begin(), iter);  // index of swapper in the path
  if (index == 0 || index == path.size()) {
    error("This shouldn't happen. Endnode was recognized as swapper with some reason.");
  }
  self_lqnic_index = qnics.at(index).fst.index;
  self_lqnic_type = qnics.at(index).fst.type;
  self_rqnic_index = qnics.at(index).snd.index;
  self_rqnic_type = qnics.at(index).snd.type;
  // FIXME more dynamically using recursive function or ...
  // auto it = std::find(swapping_partners.begin(), swapping_partners.end(), swapper_address);
  auto it = swapping_partners.find(swapper_address);
  if (it != swapping_partners.end() && it->second.size() == 2) {
    left_partner = it->second.at(0);
    right_partner = it->second.at(1);
  } else {
    error("Error occured. Swapper is not recognized as swapper, or the number of partners is wrong (must be 2)");
  }

  auto iter_left = std::find(path.begin(), path.end(), left_partner);
  if (iter_left != path.end()) {
    size_t index_left = std::distance(path.begin(), iter_left);

    // left partner must be second TODO: detail description of this.
    lqnic_type = qnics.at(index_left).snd.type;
    lqnic_index = qnics.at(index_left).snd.index;
    lqnic_address = qnics.at(index_left).snd.address;
  } else {
    error("nodes are not found in path");
  }

  auto iter_right = std::find(path.begin(), path.end(), right_partner);
  if (iter_right != path.end()) {
    size_t index_right = std::distance(path.begin(), iter_right);

    // right partner must be first
    rqnic_type = qnics.at(index_right).fst.type;
    rqnic_index = qnics.at(index_right).fst.index;
    rqnic_address = qnics.at(index_right).fst.address;
  } else {
    error("nodes are not found in path");
  }

  // if(index % 2 == 1){
  //   left_partner = path.at(index-1);
  //   lqnic_type = qnics.at(index-1).snd.type; // left partner must be second TODO: detail description of this.
  //   lqnic_index = qnics.at(index-1).snd.index;
  //   lqnic_address = qnics.at(index-1).snd.address;

  //   right_partner = path.at(index+1);
  //   rqnic_type = qnics.at(index+1).fst.type; // right partner must be first
  //   rqnic_index = qnics.at(index+1).fst.index;
  //   rqnic_address = qnics.at(index+1).fst.address;

  // }else if(index % 2 == 0){
  //   left_partner = path.at(0);
  //   lqnic_type = qnics.at(0).snd.type;
  //   lqnic_index = qnics.at(0).snd.index;
  //   lqnic_address = qnics.at(0).snd.address;

  //   // QNIC_type lqnic_type =
  //   right_partner = path.at(path.size()-1);
  //   rqnic_type = qnics.at(path.size()-1).fst.type;
  //   rqnic_index = qnics.at(path.size()-1).fst.index;
  //   lqnic_address = qnics.at(path.size()-1).fst.address;

  // }else{
  //   error("this must not happen index must be positive");
  // }

  // if(swapper_address == 6&& left_partner==1&&right_partner==15){
  //   error("good!");
  // }
  if (self_rqnic_type == QNIC_RP || self_lqnic_type == QNIC_RP || rqnic_type == QNIC_RP || lqnic_type == QNIC_RP) {
    error("MSM link not implemented");
  }
  swap_setting.left_partner = left_partner;
  swap_setting.lqnic_type = lqnic_type;
  swap_setting.lqnic_index = lqnic_index;
  swap_setting.lqnic_address = lqnic_address;
  swap_setting.lres = num_resources;

  swap_setting.right_partner = right_partner;
  swap_setting.rqnic_type = rqnic_type;
  swap_setting.rqnic_index = rqnic_index;
  swap_setting.rqnic_address = rqnic_address;
  swap_setting.rres = num_resources;

  swap_setting.self_left_qnic_index = self_lqnic_index;
  swap_setting.self_right_qnic_index = self_rqnic_index;
  swap_setting.self_left_qnic_type = self_lqnic_type;
  swap_setting.self_right_qnic_type = self_rqnic_type;

  return swap_setting;
}

// RuleSet **ConnectionManager::generate_RuleSet( int *stack_of_QNodeIndexes,
//                                           int *stack_of_linkCosts,
//                                           QNIC_pair_info *stack_of_QNICs){
// }

/**
 *  This function is called to handle the ConnectionSetupRequest at an "intermediate"
 *  node, one that is neither the initiator nor the responder.
 * \param pk pointer to the ConnectionSetupRequest packet itself
 * \returns nothing
 **/
void ConnectionManager::intermediate_alloc_req_handler(ConnectionSetupRequest *pk) {
  int actual_dst = pk->getActual_destAddr();  // responder address
  int actual_src = pk->getActual_srcAddr();  // initiator address (to get input qnic)
  int local_qnic_address_to_actual_dst = routingdaemon->return_QNIC_address_to_destAddr(actual_dst);

  // TODO: premise only oneconnection allowed btw, two nodes.
  int local_qnic_address_to_actual_src = routingdaemon->return_QNIC_address_to_destAddr(actual_src);

  // TODO here need to check
  if (local_qnic_address_to_actual_dst == -1) {  // is not found
    error("QNIC to destination not found");
  } else if (myAddress != actual_src && local_qnic_address_to_actual_src == -1) {
    error("QNIC to source not found");
  } else {
    // Use the QNIC address to find the next hop QNode,
    // by asking the Hardware Monitor (neighbor table).
    EV << "Source : " << pk->getSrcAddr() << " qnic_for_actual_dst : " << local_qnic_address_to_actual_dst << "\n";
    connection_setup_inf dst_inf = hardwaremonitor->return_setupInf(local_qnic_address_to_actual_dst);
    EV << "DST_INF " << dst_inf.qnic.type << "," << dst_inf.qnic.index << "\n";
    connection_setup_inf src_inf = hardwaremonitor->return_setupInf(local_qnic_address_to_actual_src);
    EV << "SRC_INF " << src_inf.qnic.type << "," << src_inf.qnic.index << "\n";
    // if(reservation){
    //   EV<<"reserved!"<<myAddress<<":"<<local_qnic_address_to_actual_dst<<"\n";
    // }else{
    //   EV<<"not reserved!"<<myAddress<<":"<<local_qnic_address_to_actual_dst<<"\n";
    // }
    bool isReserved_src = isQnic_busy(src_inf.qnic.address);
    bool isReserved_dst = isQnic_busy(dst_inf.qnic.address);
    if (!isReserved_src && !isReserved_dst) {
      int num_accumulated_nodes = pk->getStack_of_QNodeIndexesArraySize();
      int num_accumulated_costs = pk->getStack_of_linkCostsArraySize();
      int num_accumulated_pair_info = pk->getStack_of_QNICsArraySize();

      // Update information and send it to the next Qnode.
      pk->setDestAddr(dst_inf.neighbor_address);
      pk->setSrcAddr(myAddress);
      pk->setStack_of_QNodeIndexesArraySize(num_accumulated_nodes + 1);
      pk->setStack_of_linkCostsArraySize(num_accumulated_costs + 1);
      pk->setStack_of_QNodeIndexes(num_accumulated_nodes, myAddress);
      pk->setStack_of_linkCosts(num_accumulated_costs, dst_inf.quantum_link_cost);
      pk->setStack_of_QNICsArraySize(num_accumulated_pair_info + 1);
      QNIC_id_pair pair_info = {.fst = src_inf.qnic, .snd = dst_inf.qnic};
      pk->setStack_of_QNICs(num_accumulated_pair_info, pair_info);
      pair_info = pk->getStack_of_QNICs(num_accumulated_pair_info);
      if (actual_src != myAddress) {
        reserve_qnic(src_inf.qnic.address);
        reserve_qnic(dst_inf.qnic.address);
      }
      send(pk, "RouterPort$o");
    } else {  // TODO after connection expired, this goes to false
      RejectConnectionSetupRequest *pkt = new RejectConnectionSetupRequest;
      pkt->setKind(6);
      pkt->setDestAddr(pk->getActual_srcAddr());
      pkt->setSrcAddr(myAddress);
      pkt->setActual_destAddr(pk->getActual_destAddr());
      pkt->setActual_srcAddr(pk->getActual_srcAddr());
      pkt->setNumber_of_required_Bellpairs(pk->getNumber_of_required_Bellpairs());
      send(pkt, "RouterPort$o");
    }
  }
}
// This is not good way. This property should be held in qnic property.
void ConnectionManager::reserve_qnic(int qnic_address) {
  auto it = qnic_res_table.find(qnic_address);
  if (it != qnic_res_table.end() && !it->second) {
    it->second = true;
  } else {
    EV << "qnic_address" << qnic_address << "\n";
    error("qnic not found or already reserved");
  }
}

void ConnectionManager::release_qnic(int qnic_address) {
  auto it = qnic_res_table.find(qnic_address);
  if (it != qnic_res_table.end() && it->second) {
    it->second = false;
  } else {
    error("qnic not found or not reserved");
  }
}

bool ConnectionManager::isQnic_busy(int qnic_address) {
  bool isReserved = false;
  auto it = qnic_res_table.find(qnic_address);
  if (it != qnic_res_table.end()) {
    isReserved = it->second;
  } else {
    error("address not found");
  }
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
  int local_qnic_address_to_actual_dst = routingdaemon->return_QNIC_address_to_destAddr(actual_dst);
  int local_qnic_address_to_actual_src = routingdaemon->return_QNIC_address_to_destAddr(actual_src);
  connection_setup_inf dst_inf = hardwaremonitor->return_setupInf(local_qnic_address_to_actual_dst);
  connection_setup_inf src_inf = hardwaremonitor->return_setupInf(local_qnic_address_to_actual_src);
  if (myAddress != actual_dst && myAddress != actual_src) {
    release_qnic(dst_inf.qnic.address);
    release_qnic(src_inf.qnic.address);
  } else if (myAddress == actual_dst) {
    release_qnic(src_inf.qnic.address);
  } else if (myAddress == actual_src) {
    release_qnic(dst_inf.qnic.address);
  }
}

/**
 *  This function is called during the handling of ConnectionSetupRequest at the responder.
 * \param RuleSet_id the unique identifier for this RuleSet (== connection)
 * \param owner address of the intermediate node we are generating this RuleSet for
 * \param conf the swap_table listing the order and partners
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
RuleSet *ConnectionManager::generateRuleSet_EntanglementSwapping(unsigned long RuleSet_id, int owner, swap_table conf) {
  int rule_index = 0;
  std::vector<int> partners = {conf.left_partner, conf.right_partner};
  RuleSet *EntanglementSwapping = new RuleSet(RuleSet_id, owner, partners);
  Rule *SwappingRule = new Rule(RuleSet_id, rule_index);
  EntanglementSwapping->setRule_ptr(SwappingRule);
  Condition *Swap_condition = new Condition();
  Clause *resource_clause_left = new EnoughResourceClauseLeft(conf.left_partner, conf.lres);
  Clause *resource_clause_right = new EnoughResourceClauseRight(conf.right_partner, conf.rres);
  Swap_condition->addClause(resource_clause_left);
  Swap_condition->addClause(resource_clause_right);
  SwappingRule->setCondition(Swap_condition);
  quisp::rules::Action *swap_action = new SwappingAction(RuleSet_id, rule_index, conf.left_partner, conf.lqnic_type, conf.lqnic_index, conf.lqnic_address, conf.lres,
                                                         conf.right_partner, conf.rqnic_type, conf.rqnic_index, conf.rqnic_address, conf.rres, conf.self_left_qnic_index,
                                                         conf.self_left_qnic_type, conf.self_right_qnic_index, conf.self_right_qnic_type);
  SwappingRule->setAction(swap_action);
  EntanglementSwapping->addRule(SwappingRule);
  rule_index++;

  return EntanglementSwapping;
}

RuleSet *ConnectionManager::generateRuleSet_Tomography(unsigned long RuleSet_id, int owner, int partner, int num_of_measure, QNIC_type qnic_type, int qnic_index,
                                                       int num_resources) {
  // tomography ruleset
  int rule_index = 0;
  RuleSet *tomography = new RuleSet(RuleSet_id, owner, partner);
  Rule *Random_measure_tomography = new Rule(RuleSet_id, rule_index);

  // Technically, there is no condition because an available resource is guaranteed whenever the rule is ran.
  Condition *measurement_condition = new Condition();

  // 3000 measurements in total. There are 3*3 = 9 patterns of measurements. So each combination must perform 3000/9 measurements.
  Clause *count_clause = new MeasureCountClause(num_of_measure, partner, qnic_type, qnic_index, 0);
  Clause *resource_clause = new EnoughResourceClause(partner, num_resources);

  measurement_condition->addClause(count_clause);
  measurement_condition->addClause(resource_clause);

  Random_measure_tomography->setCondition(measurement_condition);

  // Measure the local resource between it->second.neighborQNode_address.
  quisp::rules::Action *measurement_action = new RandomMeasureAction(partner, qnic_type, qnic_index, 0, owner, num_of_measure);
  Random_measure_tomography->setAction(measurement_action);

  // Add the rule to the RuleSet
  tomography->addRule(Random_measure_tomography);
  tomography->finalize();

  return tomography;
}

unsigned long ConnectionManager::createUniqueId() {
  std::string time = SimTime().str();
  std::string address = std::to_string(myAddress);
  std::string random = std::to_string(intuniform(0, 10000000));
  std::string hash_seed = address + time + random;
  std::hash<std::string> hash_fn;
  size_t t = hash_fn(hash_seed);
  unsigned long RuleSet_id = static_cast<long>(t);
  std::cout << "Hash is " << hash_seed << ", t = " << t << ", long = " << RuleSet_id << "\n";
  return RuleSet_id;
}

}  // namespace modules
}  // namespace quisp

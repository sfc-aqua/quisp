#pragma once
#include <omnetpp.h>
#include <utils/ComponentProvider.h>
#include <map>
#include "messages/base_messages_m.h"
#include "messages/ospf_messages_m.h"
#include "omnetpp/ctopology.h"

namespace quisp::modules {

using RoutingTable = std::map<int, int>;  // destaddr -> gateindex

/** \class Router
 *
 *  \brief Router routes messages to components or other qnode according to the message header
 */
class Router : public omnetpp::cSimpleModule {
 public:
  Router();

 protected:
  virtual void initialize() override;
  virtual void handleMessage(omnetpp::cMessage *msg) override;
  void generateRoutingTable(cTopology *topo);

  virtual size_t getNumNeighbors() const;

  void ospfHandleHelloPacket(messages::OspfHelloPacket *pk);
  void ospfSendNeighbors();
  void ospfSendNeighbor(int gate_index);
  bool ospfNeighborIsRegistered(int address);
  bool ospfMyAddressIsRecognizedByNeighbor(messages::OspfHelloPacket *msg);
  void ospfRegisterNeighbor(messages::Header *pk, messages::OspfState state);

  void ospfHandleDbdPacket(messages::OspfDbdPacket *pk);
  void ospfExStartState(messages::OspfDbdPacket *pk);
  void ospfDecideMaster(int src);
  messages::OspfDbdPacket *ospfCreateExstartDbdPacket(bool is_master);
  void ospfInitiateExchangeState(int dest);
  void ospfExchangeState(messages::OspfDbdPacket *pk);
  // messages::OspfDbdPacket * ospfPrepareLsdbSummary();
  void ospfAppendLsdbSummaryToPacket(messages::OspfDbdPacket *msg);
  void ospfSendLsdbSummary(int destination, bool i_am_master=false);

  std::vector<int> identifyMissingRouterInfo(messages::OspfDbdPacket *pk);
  void ospfSendLinkStateRequest(messages::OspfDbdPacket *pk);
  void ospfHandleLinkStateRequest(messages::Lsr* pk);

  void ospfHandleLinkStateUpdate(messages::LsuPacket *pk);
  void ospfUpdateAdjList(messages::LsuPacket* msg);
  void sendUpdatedLsdbToNeighboringRouters(int source_of_updated_lsdb);

  void ospfConstructMyAddressAdjacencyList();
  messages::Lsa ospfGenerateLinkStateAdvertisement(int requested_id);

  utils::ComponentProvider provider;

  int my_address;
  int my_dd_sequence = 0;
  RoutingTable routing_table;

  struct OspfNeighborInfo {
    int router_id;
    int gate_index = -1;
    messages::OspfState state = messages::OspfState::DOWN;
    int cost;
    OspfNeighborInfo(int rid) : router_id(rid) {}
    OspfNeighborInfo(int idx, messages::OspfState st) : gate_index(idx), state(st) {}
    OspfNeighborInfo(int idx, messages::OspfState st, int c) : gate_index(idx), state(st), cost(c) {}
    OspfNeighborInfo() = default;
  };


  std::map<int, OspfNeighborInfo> neighbor_table;

  struct LinkStateAdvertisement {
    int lsa_age;
    std::vector<OspfNeighborInfo> adjacent_nodes;
  };
  std::map<int, LinkStateAdvertisement> adj_list;
};

Define_Module(Router);
}  // namespace quisp::modules

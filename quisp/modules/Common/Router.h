#pragma once
#include <omnetpp.h>
#include <utils/ComponentProvider.h>
#include <modules/Common/Ospf.h>
#include <map>
#include "messages/classical_messages.h"
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
  void ospfRegisterNeighbor(messages::Header *pk, OspfState state);

  void ospfHandleDbdPacket(messages::OspfDbdPacket *pk);
  void ospfExStartState(messages::OspfDbdPacket *pk);
  void ospfDecideMaster(int src);
  messages::OspfDbdPacket *ospfCreateExstartDbdPacket(bool is_master);
  void ospfInitiateExchangeState(int dest);
  void ospfRespondToExchangeStateMater(int dest);
  void ospfAppendLsdbSummaryToPacket(messages::OspfDbdPacket *msg);
  void ospfSendLsdbSummary(int destination, bool i_am_master=false);

  std::vector<int> identifyMissingRouterInfo(messages::OspfDbdPacket *pk);
  void ospfSendLinkStateRequest(messages::OspfDbdPacket *pk);
  void ospfHandleLinkStateRequest(messages::OspfLsrPacket* pk);

  void ospfHandleLinkStateUpdate(messages::OspfLsuPacket *pk);
  void ospfUpdateLinkStateDatabase(messages::OspfLsuPacket* msg);
  void sendUpdatedLsdbToNeighboringRouters(int source_of_updated_lsdb);

  void ospfAddMyAddressLsaToLsdb();

  utils::ComponentProvider provider;

  int my_address;
  int my_dd_sequence = 0;
  RoutingTable routing_table;


  std::map<int, OspfNeighborInfo> neighbor_table;

  std::map<int, LinkStateAdvertisement> LinkStateDatabase;
};

Define_Module(Router);
}  // namespace quisp::modules

#pragma once
#include <modules/Common/Ospf.h>
#include <omnetpp.h>
#include <utils/ComponentProvider.h>
#include "messages/classical_messages.h"

namespace quisp::modules {

using namespace ospf;
using RoutingTable = std::map<NodeAddr, int>;  // destaddr -> gateindex

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
  void generateRoutingTable();

  virtual size_t getNumNeighbors() const;

  void ospfHandleHelloPacket(const messages::OspfHelloPacket *const pk);
  void ospfInitializeRouter();
  void ospfSendHelloPacketToNeighbor(int gate_index);
  bool ospfMyAddressIsRecognizedByNeighbor(const messages::OspfHelloPacket *const msg);
  void ospfRegisterNeighbor(const messages::Header *const pk, OspfState state);
  bool ospfNeighborIsRegistered(int address) const;

  void ospfHandleDbdPacket(const messages::OspfDbdPacket *const pk);
  void ospfExStartState(const messages::OspfDbdPacket *const pk);
  /**
   * @brief Exchange DBD packets to decide who the master or slave is
   * @details Master/slave is decided based on the number of router address/ID.
   *          Whichever that has the bigger router address becomes the master
   * @param neighbor
   */
  void ospfDecideMaster(int src);
  void ospfSendExstartDbdPacket(NodeAddr neighbor, bool is_master);
  void ospfInitiateExchangeState(int dest);
  void ospfRespondToExchangeStateMater(int dest);
  void ospfSendLsdbSummary(int destination, bool i_am_master = false);

  void ospfSendLinkStateRequest(const messages::OspfDbdPacket *const pk);
  void ospfHandleLinkStateRequest(const messages::OspfLsrPacket *const pk);

  void ospfHandleLinkStateUpdate(const messages::OspfLsuPacket *const pk);
  void ospfUpdateLinkStateDatabase(const messages::OspfLsuPacket *const msg);
  void ospfSendUpdatedLsdbToNeighboringRouters(int source_of_updated_lsdb);

  void ospfUpdateMyAddressLsaInLsdb();

  utils::ComponentProvider provider;

  NodeAddr my_address;
  RoutingTable routing_table;

  RoutingTable ospf_routing_table;
  ospf::NeighborTable neighbor_table;
  LinkStateDatabase link_state_database;
};

Define_Module(Router);
}  // namespace quisp::modules

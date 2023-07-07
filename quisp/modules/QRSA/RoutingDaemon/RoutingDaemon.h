/*
 * RoutingDaemon.h
 *
 *  Created on: 2018/06/12
 *      Author: takaakimatsuo
 */

#pragma once

#include "IRoutingDaemon.h"
#include "modules/Common/LinkStateRoutingProtocol/Ospf.h"
#include "modules/QNIC.h"
#include "utils/ComponentProvider.h"
#include "messages/classical_messages.h"

/** \class RoutingDaemon RoutingDaemon.cc
 *
 *  \brief RoutingDaemon
 */
namespace quisp::modules::routing_daemon {

// destaddr -> {self_qnic_address (unique)}
using RoutingTable = std::map<int, int>;

using namespace ospf;
using namespace quisp::messages;

class RoutingDaemon : public IRoutingDaemon {
 public:
  RoutingDaemon();

 protected:
  NodeAddr my_address;
  RoutingTable qrtable;
  utils::ComponentProvider provider;
  ospf::NeighborTable neighbor_table;
  LinkStateDatabase link_state_database;

  void generateRoutingTable(cTopology* topo);
  int getQNicAddr(const cGate* const parentModuleGate);

  void initialize(int stage) override;
  void handleMessage(cMessage* msg) override;
  int numInitStages() const override { return 3; };

  virtual void generateRoutingTable();
  virtual size_t getNumNeighbors();

  void ospfHandleHelloPacket(const messages::OspfHelloPacket *const pk);
  void ospfInitializeRoutingDaemon();
  void ospfSendHelloPacketToNeighbor(NodeAddr neighbor);
  bool ospfMyAddressIsRecognizedByNeighbor(const messages::OspfHelloPacket *const msg);
  void ospfRegisterNeighbor(const messages::OspfPacket *const pk, OspfState state);
  bool ospfNeighborIsRegistered(int address) const;

  void ospfHandleDbdPacket(const messages::OspfDbdPacket *const pk);
  void ospfExStartState(const messages::OspfDbdPacket *const pk);
  void ospfSendExstartDbdPacket(NodeAddr neighbor);
  void ospfSlaveInitiateExchangeState(int dest);
  void ospfMasterEnterExchangeState(int dest);
  void ospfSendLsdbSummary(int destination, bool i_am_master = false);

  void ospfSendLinkStateRequest(int dst, const RouterIds &missing_lsa_ids);
  void ospfHandleLinkStateRequest(const messages::OspfLsrPacket *const pk);

  void ospfHandleLinkStateUpdate(const messages::OspfLsuPacket *const pk);
  void ospfUpdateLinkStateDatabase(const messages::OspfLsuPacket *const msg);
  void ospfSendUpdatedLsdbToNeighboringRouters(int source_of_updated_lsdb);

  void ospfUpdateMyAddressLsaInLsdb();

 public:
  int getNumEndNodes() override;
  int findQNicAddrByDestAddr(int destAddr) override;

 private:
  bool run_ospf;
};

}  // namespace quisp::modules::routing_daemon

/*
 * RoutingDaemon.h
 *
 *  Created on: 2018/06/12
 *      Author: takaakimatsuo
 */

#pragma once

#include "IRoutingDaemon.h"
#include "messages/classical_messages.h"
#include "modules/QNIC.h"
#include "modules/QRSA/RoutingDaemon/RoutingProtocol/Ospf/Ospf.h"
#include "utils/ComponentProvider.h"

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

  void generateRoutingTable();
  void generateRoutingTable(cTopology *topo);
  int getQNicAddr(const cGate *const parentModuleGate);

  void initialize(int stage) override;
  void handleMessage(cMessage *msg) override;
  int numInitStages() const override { return 3; };

  size_t getNumNeighbors();

  void ospfHandleHelloPacket(const OspfHelloPacket *const pk);
  void ospfInitializeRoutingDaemon();
  void ospfSendHelloPacketToNeighbor(NodeAddr neighbor);
  bool ospfMyAddressIsRecognizedByNeighbor(const OspfHelloPacket *const msg);
  void ospfRegisterNeighbor(const OspfPacket *const pk, OspfState state);
  bool ospfNeighborIsRegistered(int address) const;

  void ospfHandleDbdPacket(const OspfDbdPacket *const pk);
  void ospfExStartState(const OspfDbdPacket *const pk);
  void ospfSendExstartDbdPacket(NodeAddr neighbor);
  void ospfSlaveInitiateExchangeState(int dest);
  void ospfMasterEnterExchangeState(int dest);
  void ospfSendLsdbSummary(int destination, bool i_am_master = false);

  void ospfSendLinkStateRequest(int dst, const RouterIds &missing_lsa_ids);
  void ospfHandleLinkStateRequest(const OspfLsrPacket *const pk);

  void ospfHandleLinkStateUpdate(const OspfLsuPacket *const pk);
  void ospfUpdateLinkStateDatabase(const OspfLsuPacket *const msg);
  void ospfSendUpdatedLsdbToNeighboringRouters(int source_of_updated_lsdb);

  void ospfUpdateMyAddressLsaInLsdb();

 public:
  int getNumEndNodes() override;
  int findQNicAddrByDestAddr(int destAddr) override;

 private:
  bool run_ospf;
};

}  // namespace quisp::modules::routing_daemon

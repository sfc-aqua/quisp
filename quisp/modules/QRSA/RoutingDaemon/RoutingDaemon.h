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
// destaddr -> QuantumInterfaceInfo (more information than qnic_address)
using InterfaceTable = std::map<int, std::unique_ptr<QuantumInterfaceInfo>>;

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
  InterfaceTable interface_table;

  int num_qnic;
  int num_qnic_r;
  int num_qnic_rp;
  std::map<QNIC_type, int> qnic_num_map;
  // qnic_addr -> (qnic_type, qnic_index)
  std::map<int, std::tuple<QNIC_type, int>> qnic_addr_map;

  void generateRoutingTable();
  void generateRoutingTable(cTopology *topo);
  int getQNicAddr(const cGate *const parentModuleGate);

  void initialize(int stage) override;
  void handleMessage(cMessage *msg) override;
  int numInitStages() const override { return 3; };
  std::unique_ptr<QuantumInterfaceInfo> getQuantumInterfaceInfo(int dest_addr) override;

  void prepareQnicAddrMap();
  void resolveQuantumInterfaceInfo();
  void prepareNeighborAddressTableWithTopologyInfo();
  int getNeighborAddressFromQnicModule(const cModule *qnic_module);
  int findQnicAddrByNeighborAddr(int neighbor_addr);
  std::vector<int> getNeighborAddresses() override;
  std::vector<int> neighbor_addresses;
  QuantumInterfaceInfo prepareQuantumInterfaceInfo(cModule *qnic_module);

  size_t getNumNeighbors();

  // OSPF functions
  void ospfHandleHelloPacket(const OspfHelloPacket *const pk);
  void ospfInitializeRoutingDaemon();
  void ospfSendHelloPacketToNeighbor(NodeAddr neighbor);
  bool ospfMyAddressIsRecognizedByNeighbor(const OspfHelloPacket *const msg);
  void ospfRegisterNeighbor(const OspfPacket *const pk, OspfState state);
  bool ospfNeighborIsRegistered(NodeAddr address) const;

  void ospfHandleDbdPacket(const OspfDbdPacket *const pk);
  void ospfExStartState(const OspfDbdPacket *const pk);
  void ospfSendExstartDbdPacket(NodeAddr neighbor);
  void ospfSlaveInitiateExchangeState(NodeAddr dest);
  void ospfMasterEnterExchangeState(NodeAddr dest);
  void ospfSendLsdbSummary(NodeAddr destination, bool i_am_master = false);

  void ospfSendLinkStateRequest(NodeAddr dst, const RouterIds &missing_lsa_ids);
  void ospfHandleLinkStateRequest(const OspfLsrPacket *const pk);

  void ospfHandleLinkStateUpdate(const OspfLsuPacket *const pk);
  void ospfUpdateLinkStateDatabase(const OspfLsuPacket *const msg);
  void ospfSendUpdatedLsdbToNeighboringRouters(NodeAddr source_of_updated_lsdb);

  void ospfUpdateMyAddressLsaInLsdb();

 public:
  int findQNicAddrByDestAddr(int destAddr) override;

 private:
  bool run_ospf;
};

}  // namespace quisp::modules::routing_daemon

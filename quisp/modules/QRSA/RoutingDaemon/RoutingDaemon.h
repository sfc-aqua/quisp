/*
 * RoutingDaemon.h
 *
 *  Created on: 2018/06/12
 *      Author: takaakimatsuo
 */

#pragma once

#include <modules/QNIC.h>
#include "IRoutingDaemon.h"
#include "types/QNodeAddr.h"
#include "utils/ComponentProvider.h"

/** \class RoutingDaemon RoutingDaemon.cc
 *
 *  \brief RoutingDaemon
 */
namespace quisp::modules::routing_daemon {

// destaddr -> {self_qnic_address (unique)}
using RoutingTable = std::map<types::QNodeAddr, int>;

class RoutingDaemon : public IRoutingDaemon {
 protected:
  types::QNodeAddr myAddress;
  RoutingTable qrtable;

  // dest_addr -> next_neighbor_addr
  std::map<types::QNodeAddr, types::QNodeAddr> neighbor_addr_table;

  std::map<types::QNodeAddr, std::tuple<int, types::QNodeAddr, types::QNodeAddr, types::QNodeAddr>> lower_layer_routing_table;

  void updateChannelWeightsInTopology(cTopology* topo);
  void updateChannelWeightsOfNode(cTopology::Node* node);
  double calculateSecPerBellPair(const cTopology::LinkOut* const outgoing_link);

  void generateRoutingTable(cTopology* topo);
  int getQNicAddr(const cGate* const parentModuleGate);

  void initialize(int stage) override;
  void handleMessage(cMessage* msg) override;
  int numInitStages() const override { return 3; };

  static std::vector<types::QNodeAddr> getQNodeAddressList(cModule*);
  static std::tuple<int, types::QNodeAddr, types::QNodeAddr, types::QNodeAddr> findNetworkBoundary(const std::vector<std::vector<types::QNodeAddr>>&, types::QNodeAddr dest_addr);

  utils::ComponentProvider provider;

 public:
  RoutingDaemon();
  int getNumEndNodes() override;
  int findQNicAddrByDestAddr(types::QNodeAddr destAddr) override;

  std::optional<DestInfoTuple> findLowerLayerDestInfoByDestAddr(types::QNodeAddr actual_dest_addr) override;
};

}  // namespace quisp::modules::routing_daemon

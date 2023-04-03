/*
 * RoutingDaemon.h
 *
 *  Created on: 2018/06/12
 *      Author: takaakimatsuo
 */

#pragma once

#include "IRoutingDaemon.h"

#include "modules/QNIC.h"
#include "utils/ComponentProvider.h"

/** \class RoutingDaemon RoutingDaemon.cc
 *
 *  \brief RoutingDaemon
 */
namespace quisp::modules::routing_daemon {

// destaddr -> {self_qnic_address (unique)}
using RoutingTable = std::map<int, int>;

class RoutingDaemon : public IRoutingDaemon {
 protected:
  int myAddress;
  RoutingTable qrtable;

  void updateChannelWeightsInTopology(cTopology* topo);
  void updateChannelWeightsOfNode(cTopology::Node* node);
  double calculateSecPerBellPair(const cTopology::LinkOut* const outgoing_link);

  void generateRoutingTable(cTopology* topo);
  int getQNicAddr(const cGate* const parentModuleGate);

  void initialize(int stage) override;
  void handleMessage(cMessage* msg) override;
  int numInitStages() const override { return 3; };

  utils::ComponentProvider provider;

 public:
  RoutingDaemon();
  int getNumEndNodes() override;
  int findQNicAddrByDestAddr(int destAddr) override;
};

}  // namespace quisp::modules::routing_daemon

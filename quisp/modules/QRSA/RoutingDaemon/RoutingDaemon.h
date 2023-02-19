/*
 * RoutingDaemon.h
 *
 *  Created on: 2018/06/12
 *      Author: takaakimatsuo
 */

#ifndef MODULES_ROUTINGDAEMON_H_
#define MODULES_ROUTINGDAEMON_H_

#include "IRoutingDaemon.h"

#include <modules/QNIC.h>
#include <utils/ComponentProvider.h>

/** \class RoutingDaemon RoutingDaemon.cc
 *
 *  \brief RoutingDaemon
 */

namespace quisp {
namespace modules {

class RoutingDaemon : public IRoutingDaemon {
 protected:
  int myAddress;
  typedef std::map<int, QNIC> RoutingTable;  // destaddr -> {gate_index (We need this to access qnic, but it is not unique because we have 3 types of qnics), qnic_address (unique)}
  RoutingTable qrtable;
  utils::ComponentProvider provider;

  void updateChannelWeightsInTopology(cTopology* topo);
  void updateChannelWeightsOfNode(cTopology::Node* node);
  double calculateSecPerBellPair(const cTopology::LinkOut* const outgoing_link);

  void generateRoutingTable(cTopology* topo);
  virtual QNIC getQNicInfoOf(const cGate* const parentModuleGate);

  void initialize(int stage) override;
  void handleMessage(cMessage* msg) override;
  int numInitStages() const override { return 3; };

 public:
  RoutingDaemon();
  int getNumEndNodes() override;
  int findQNicAddrByDestAddr(int destAddr) override;
};

}  // namespace modules
}  // namespace quisp

#endif /* MODULES_ROUTINGDAEMON_H_ */

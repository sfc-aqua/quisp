/*
 * RoutingDaemon.h
 *
 *  Created on: 2018/06/12
 *      Author: takaakimatsuo
 */

#ifndef MODULES_ROUTINGDAEMON_H_
#define MODULES_ROUTINGDAEMON_H_

#include <modules/QNIC.h>
#include "IRoutingDaemon.h"

/** \class RoutingDaemon RoutingDaemon.cc
 *  \todo Documentation of the class header.
 *
 *  \brief RoutingDaemon
 */

namespace quisp {
namespace modules {

class RoutingDaemon : public IRoutingDaemon {
 private:
  int myAddress;
  typedef std::map<int, QNIC> RoutingTable;  // destaddr -> {gate_index (We need this to access qnic, but it is not unique because we have 3 types of qnics), qnic_address (unique)}
  RoutingTable qrtable;

 protected:
  void initialize(int stage) override;
  void handleMessage(cMessage *msg) override;
  int numInitStages() const override { return 3; };

 public:
  int return_QNIC_address_to_destAddr(int destAddr) override;
};

}  // namespace modules
}  // namespace quisp

#endif /* MODULES_ROUTINGDAEMON_H_ */

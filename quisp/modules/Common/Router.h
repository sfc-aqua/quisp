#pragma once
#include <omnetpp.h>
#include <map>

#include "messages/classical_messages.h"
#include "types/QNodeAddr.h"
#include "utils/ComponentProvider.h"

namespace quisp::modules {

using RoutingTable = std::map<types::QNodeAddr, int>;  // destaddr -> gateindex

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
  void handlePacketForThisNode(omnetpp::cMessage *msg);
  bool shouldReceive(messages::Header *msg);

  utils::ComponentProvider provider;

  types::QNodeAddr my_address;
  RoutingTable routing_table;

  std::map<int, int> gate_network_map;
};

Define_Module(Router);
}  // namespace quisp::modules

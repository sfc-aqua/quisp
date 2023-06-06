#pragma once
#include <omnetpp.h>
#include <utils/ComponentProvider.h>
#include <map>
#include "messages/base_messages_m.h"

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
  virtual void ospfSendNeighbors();
  void ospfSendNeighbor(int gate_index);
  void ospfRegisterNeighbor(messages::Header *pk);

  utils::ComponentProvider provider;

  int my_address;
  RoutingTable routing_table;
  RoutingTable neighbor_table;
};

Define_Module(Router);
}  // namespace quisp::modules

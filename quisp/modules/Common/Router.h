#pragma once
#include <omnetpp.h>
#include <utils/ComponentProvider.h>
#include <map>
#include "messages/base_messages_m.h"
#include "messages/ospf_messages_m.h"

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
  void ospfHandleHelloPacket(messages::OspfHelloPacket *pk);
  void generateRoutingTable(cTopology *topo);
  virtual size_t getNumNeighbors() const;
  void ospfSendNeighbors();
  void ospfSendNeighbor(int gate_index);
  bool ospfNeighborIsRegistered(int address);
  bool ospfMyAddressIsRecognizedByNeighbor(messages::OspfHelloPacket *msg);
  void ospfRegisterNeighbor(messages::Header *pk, messages::OspfState state);

  utils::ComponentProvider provider;

  int my_address;
  RoutingTable routing_table;

  struct OspfNeighborInfo {
    int gate_index = -1;
    messages::OspfState state = messages::OspfState::DOWN;
    OspfNeighborInfo(int idx, messages::OspfState st) : gate_index(idx), state(st) {}
    OspfNeighborInfo() = default;
  };
  std::map<int, OspfNeighborInfo> neighbor_table;
};

Define_Module(Router);
}  // namespace quisp::modules

#pragma once
#include <omnetpp.h>
#include <types/QNodeAddr.h>
#include <utils/ComponentProvider.h>
#include <map>

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

  utils::ComponentProvider provider;

  types::QNodeAddr my_address;
  RoutingTable routing_table;
};

Define_Module(Router);
}  // namespace quisp::modules

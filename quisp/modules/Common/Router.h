#include <omnetpp.h>
#include <map>

namespace quisp::modules {

using RoutingTable = std::map<int, int>;  // destaddr -> gateindex

/** \class Router Router.cc
 *
 *  \brief Router
 */
class Router : public omnetpp::cSimpleModule {
 private:
  int my_address;

  RoutingTable routing_table;

 protected:
  virtual void initialize() override;
  virtual void handleMessage(omnetpp::cMessage *msg) override;
};

Define_Module(Router);
}  // namespace quisp::modules
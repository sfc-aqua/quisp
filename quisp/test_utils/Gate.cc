#include "Gate.h"
#include <omnetpp/cenvir.h>
#include "omnetpp/cmessage.h"

namespace quisp_test {
namespace gate {

using omnetpp::cSimulation;

TempGate::TempGate() {}
bool TempGate::deliver(cMessage *msg, simtime_t at) {
  std::cout << getName() << "deliver called " << msg << std::endl;
  return true;
}

TestGate::TestGate(cModule *mod) {
  desc = new omnetpp::cGate::Desc;
  desc->name = new omnetpp::cGate::Name{"toRouter", omnetpp::cGate::Type::OUTPUT};
  desc->owner = mod;
  nextGate = &temp_gate;
  desc->setOutputGate(this);
  EVCB.gateCreated(this);
}

bool TestGate::deliver(cMessage *msg, simtime_t at) {
  messages.push_back(msg->dup());
  return true;
}

}  // namespace gate
}  // namespace quisp_test
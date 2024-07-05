#include "Gate.h"
#include <omnetpp/cenvir.h>
#include "omnetpp/cmessage.h"

namespace quisp_test {
namespace gate {

using omnetpp::cSimulation;

TempGate::TempGate() {}

bool TempGate::deliver(cMessage *msg, const omnetpp::SendOptions &options, simtime_t at) { return true; }

TestGate::TestGate(cModule *mod, const char *name) {
  desc = new omnetpp::cGate::Desc;
  // only for output gate
  desc->name = new omnetpp::cGate::Name{name, omnetpp::cGate::Type::OUTPUT};
  desc->owner = mod;
  // output gate needs nextGate to be filled. actually temp_gate do nothing.
  temp_gate = new TempGate();
  nextGate = temp_gate;
  desc->setOutputGate(this);
}

/**
 * \brief this method called when a module sent cMessage to this gate.
 * and then store the msg into `messages`
 */
bool TestGate::deliver(cMessage *msg, const omnetpp::SendOptions &options, simtime_t at) {
  messages.push_back(msg->dup());
  return true;
}

void TestGate::quiet_connectTo(cGate *target) {
  nextGate = target;
  // target->prevGate = this;
}

}  // namespace gate
}  // namespace quisp_test

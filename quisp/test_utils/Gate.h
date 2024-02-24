#pragma once

#include <omnetpp.h>
#include "omnetpp/cmessage.h"

namespace quisp_test {
namespace gate {

using omnetpp::cMessage;
using omnetpp::cModule;
using omnetpp::simtime_t;

/**
 * \brief dumb class for TestGate.
 * cGate needs `nextGate` or `prevGate` in TestGate to check the gate is output or input.
 * this class is for filling TestGate's `nextGate` or `prevGate`
 */
class TempGate : public omnetpp::cGate {
 public:
  TempGate();

 protected:
  bool deliver(cMessage *msg, const omnetpp::SendOptions &options, simtime_t at) override;
};

/**
 * \brief this class can store received messages
 * currently this class only for output gate. we may need to adapt input gate.
 */
class TestGate : public omnetpp::cGate {
 public:
  explicit TestGate(cModule *mod, const char *name);
  std::vector<cMessage *> messages;
  void quiet_connectTo(cGate *target);  // To connect to a gate skipping all the listeners checks, which create problems if a full-fledged sim environment is not up.

 protected:
  TempGate temp_gate;
  bool deliver(cMessage *msg, const omnetpp::SendOptions &options, simtime_t at) override;
};

}  // namespace gate
}  // namespace quisp_test

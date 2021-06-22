#pragma once

#include <omnetpp.h>
#include "omnetpp/cmessage.h"

namespace quisp_test {
namespace gate {

using omnetpp::cMessage;
using omnetpp::cModule;
using omnetpp::simtime_t;

class TempGate : public omnetpp::cGate {
 public:
  TempGate();

 protected:
  bool deliver(cMessage *msg, simtime_t at) override;
};

class TestGate : public omnetpp::cGate {
 public:
  explicit TestGate(cModule *mod);
  std::vector<cMessage *> messages;

 protected:
  TempGate temp_gate;
  bool deliver(cMessage *msg, simtime_t at) override;
};

}  // namespace gate
}  // namespace quisp_test
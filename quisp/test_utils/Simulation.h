#pragma once
#include <omnetpp.h>
#include "omnetpp/ceventheap.h"

namespace quisp_test {
namespace simulation {

using omnetpp::cEnvir;
using omnetpp::cEvent;
using omnetpp::cSimulation;

class TestSimulation : public cSimulation {
 public:
  TestSimulation(const char *name, cEnvir *env);
  void finishNetworkSetup();
  void run();
  bool executeNextEvent();
};

}  // namespace simulation
}  // namespace quisp_test
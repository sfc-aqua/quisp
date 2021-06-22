#pragma once
#include <omnetpp.h>

namespace quisp_test {
namespace simulation {

using omnetpp::cEnvir;
using omnetpp::cSimulation;

class TestSimulation : public cSimulation {
 public:
  TestSimulation(const char *name, cEnvir *env);
  void finishNetworkSetup();
};
}  // namespace simulation
}  // namespace quisp_test
#include "Simulation.h"

using namespace omnetpp;

namespace quisp_test {
namespace simulation {

TestSimulation::TestSimulation(const char* name, cEnvir* env) : cSimulation(name, env) {}

void TestSimulation::finishNetworkSetup() {
  setSimulationTimeLimit(10000);
  callInitialize();
}

}  // namespace simulation
}  // namespace quisp_test
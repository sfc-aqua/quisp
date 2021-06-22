#include "Simulation.h"
#include "omnetpp/cexception.h"

using namespace omnetpp;

namespace quisp_test {
namespace simulation {

TestSimulation::TestSimulation(const char *name, cEnvir *env) : cSimulation(name, env) {}

void TestSimulation::finishNetworkSetup() {
  setSimulationTimeLimit(10000);
  callInitialize();
}

void TestSimulation::run() {
  bool finished = false;
  while (!finished) {
    finished = executeNextEvent();
  }
}

bool TestSimulation::executeNextEvent() {
  try {
    cEvent *event = takeNextEvent();
    if (event) {
      executeEvent(event);
      return true;
    };
  } catch (cTerminationException &e) {
  } catch (std::exception &e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
    throw e;
  }
  return false;
}

}  // namespace simulation
}  // namespace quisp_test
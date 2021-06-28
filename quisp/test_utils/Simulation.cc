#include "Simulation.h"
#include "omnetpp/cexception.h"

using namespace omnetpp;

namespace quisp_test {
namespace simulation {

/**
 * \brief simulation class for unit test.
 */
TestSimulation::TestSimulation(const char *name, cEnvir *env) : cSimulation(name, env) {}

void TestSimulation::finishNetworkSetup() {
  setSimulationTimeLimit(10000);
  callInitialize();
}

/**
 * \brief run current simulation until it finish
 */
void TestSimulation::run() {
  bool finished = false;
  while (!finished) {
    finished = executeNextEvent();
  }
}

/**
 * \brief execute one event.
 * \return finished or not. return true value means simulation finished and no more event.
 */
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

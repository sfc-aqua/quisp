#include "Simulation.h"
#include "omnetpp/cexception.h"
#include "test_utils/Configuration.h"

using namespace omnetpp;

namespace quisp_test::simulation {

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
      return false;
    };
  } catch (cTerminationException &e) {
  } catch (std::exception &e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
    throw e;
  }
  return true;
}

void TestSimulation::setConfigValue(const char *key, const char *value) {
  auto *envir = getActiveEnvir();
  auto *config = dynamic_cast<configuration::Configuration *>(envir->getConfig());
  for (auto &kv : config->kvs) {
    if (strcmp(kv.getKey(), key) == 0) {
      kv.value = value;
      return;
    }
  }
}
}  // namespace quisp_test::simulation

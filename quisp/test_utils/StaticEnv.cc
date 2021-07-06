#include "StaticEnv.h"
#include "Simulation.h"
#include "omnetpp/cconfiguration.h"
#include "omnetpp/cownedobject.h"
#include "omnetpp/csimulation.h"

namespace quisp_test {
namespace env {
using configuration::Configuration;

StaticEnv::StaticEnv() {}

cConfiguration *StaticEnv::getConfig() { return new Configuration(); }
std::string StaticEnv::gets(const char *prompt, const char *defaultreply) {
  unsupported();
  return "";
}
void StaticEnv::undisposedObject(cObject *obj) {}

cRNG *StaticEnv::getRNG(int k) {
  if (rng == nullptr) {
    rng = new omnetpp::cMersenneTwister();
  }
  return rng;
}

/**
 * \brief delete current simulation and then setup new simulation
 */
cSimulation *StaticEnv::newSimulation() {
  resetSimulation();
  auto *sim = new simulation::TestSimulation("test_sim", this);
  cComponent::clearSignalState();
  cSimulation::setActiveSimulation(sim);
  // see https://doc.omnetpp.org/omnetpp/manual/#sec:simple-modules:simulation-time
  // resolution is 1ns
  SimTime::setScaleExp(-9);
  sim->setGlobalContext();
  return sim;
}

/**
 *  \brief delete all cObjects in cSimulation::defaultList.
 */
void StaticEnv::resetSimulation() {
  using omnetpp::defaultList;
  cSimulation *prev_sim = cSimulation::getActiveSimulation();
  if (prev_sim != nullptr) {
    prev_sim->deleteNetwork();
    // set owner of all managed objects nullptr before deleting the object.
    for (int i = 0; i < defaultList.defaultListSize(); i++) {
      defaultList.defaultListGet(i)->removeFromOwnershipTree();
    }
    defaultList.removeFromOwnershipTree();
  }
}

}  // namespace env
}  // namespace quisp_test

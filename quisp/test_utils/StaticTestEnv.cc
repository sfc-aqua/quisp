
#include "StaticTestEnv.h"
#include "omnetpp/cconfiguration.h"
#include "omnetpp/cownedobject.h"
#include "omnetpp/csimulation.h"

namespace quisp_test {

StaticTestEnv::StaticTestEnv() {}

cConfiguration *StaticTestEnv::getConfig() { return new Configuration(); }
std::string StaticTestEnv::gets(const char *prompt, const char *defaultreply) {
  unsupported();
  return "";
}
void StaticTestEnv::undisposedObject(cObject *obj) {}

/**
 * \brief delete current simulation and then setup new simulation
 */
cSimulation *StaticTestEnv::newSimulation() {
  resetSimulation();
  auto *sim = new cSimulation("test_sim", this);
  cComponent::clearSignalState();
  cSimulation::setActiveSimulation(sim);
  SimTime::setScaleExp(-3);
  sim->setGlobalContext();
  return sim;
}

/**
 *  \brief delete all cObjects in cSimulation::defaultList.
 */
void StaticTestEnv::resetSimulation() {
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

}  // namespace quisp_test
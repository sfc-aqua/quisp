
#include "StaticTestEnv.h"
#include "omnetpp/cconfiguration.h"
#include "omnetpp/cownedobject.h"

namespace quisp_test {

StaticTestEnv::StaticTestEnv() {}

cConfiguration *StaticTestEnv::getConfig() { return new Configuration(); }
std::string StaticTestEnv::gets(const char *prompt, const char *defaultreply) {
  unsupported();
  return "";
}
void StaticTestEnv::undisposedObject(cObject *obj) {}

void StaticTestEnv::newSimulation() {
  auto *prev_sim = omnetpp::cSimulation::getActiveSimulation();
  if (prev_sim != nullptr) {
    prev_sim->deleteNetwork();
  }
  auto *sim = new omnetpp::cSimulation("test_sim", this);
  omnetpp::cComponent::clearSignalState();
  omnetpp::cSimulation::setActiveSimulation(sim);
  omnetpp::SimTime::setScaleExp(-3);
}

}  // namespace quisp_test
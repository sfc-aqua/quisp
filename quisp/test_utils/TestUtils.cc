#include "TestUtils.h"
namespace quisp_test {
void setParInt(cModule *module, const char *name, const int val) {
  omnetpp::cParImpl *p = new omnetpp::cIntParImpl();
  p->setName(name);
  p->setIntValue(val);
  module->addPar(p);
}
void setParStr(cModule *module, const char *name, const char *val) {
  omnetpp::cParImpl *p = new omnetpp::cStringParImpl();
  p->setName(name);
  p->setStringValue(val);
  module->addPar(p);
}
void setParBool(cModule *module, const char *name, const bool val) {
  omnetpp::cParImpl *p = new omnetpp::cBoolParImpl();
  p->setName(name);
  p->setBoolValue(val);
  module->addPar(p);
}

cSimulation *prepareSimulation() {
  auto *env = dynamic_cast<quisp_test::StaticTestEnv *>(cSimulation::getStaticEnvir());
  return env->newSimulation();
}
}  // namespace quisp_test

#include "UtilFunctions.h"
#include <omnetpp.h>
#include "StaticEnv.h"

using namespace omnetpp;

namespace quisp_test {
namespace utils {

void setParInt(cModule *module, const char *name, const int val) {
  cParImpl *p = new cIntParImpl();
  p->setName(name);
  p->setIntValue(val);
  module->addPar(p);
}

void setParStr(cModule *module, const char *name, const char *val) {
  cParImpl *p = new cStringParImpl();
  p->setName(name);
  p->setStringValue(val);
  module->addPar(p);
}

void setParBool(cModule *module, const char *name, const bool val) {
  cParImpl *p = new cBoolParImpl();
  p->setName(name);
  p->setBoolValue(val);
  module->addPar(p);
}

TestSimulation *prepareSimulation() {
  using quisp_test::env::StaticEnv;
  auto *env = dynamic_cast<StaticEnv *>(cSimulation::getStaticEnvir());
  return dynamic_cast<TestSimulation *>(env->newSimulation());
}

TestSimulation *getTestSimulation() {
  auto *sim = dynamic_cast<TestSimulation *>(cSimulation::getActiveSimulation());
  if (sim == nullptr) throw cRuntimeError("failed to get TestSimulation. you need to call prepareSimulation() first");
  return sim;
}

cEnvir *createStaticEnv() { return new quisp_test::env::StaticEnv; }

}  // namespace utils
}  // namespace quisp_test

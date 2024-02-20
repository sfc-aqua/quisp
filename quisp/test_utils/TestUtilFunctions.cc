#include "TestUtilFunctions.h"
#include <omnetpp.h>
#include <omnetpp/cobjectparimpl.h>
#include "RNG.h"
#include "StaticEnv.h"

using namespace omnetpp;
using namespace omnetpp::internal;

namespace quisp_test {
namespace utils {

void setParInt(cModule *module, const char *name, const int val) {
  if (module->findPar(name) != -1) {
    module->par(name) = val;
    return;
  }
  cParImpl *p = new cIntParImpl();
  p->setName(name);
  p->setIntValue(val);
  p->setIsMutable(true);
  module->addPar(p);
}

void setParDouble(cModule *module, const char *name, const double val) {
  if (module->findPar(name) != -1) {
    module->par(name) = val;
    return;
  }
  cParImpl *p = new cDoubleParImpl();
  p->setName(name);
  p->setDoubleValue(val);
  p->setIsMutable(true);
  module->addPar(p);
}

void setParStr(cModule *module, const char *name, const char *val) {
  if (module->findPar(name) != -1) {
    module->par(name) = val;
    return;
  }
  cParImpl *p = new cStringParImpl();
  p->setName(name);
  p->setStringValue(val);
  p->setIsMutable(true);
  module->addPar(p);
}

void setParBool(cModule *module, const char *name, const bool val) {
  if (module->findPar(name) != -1) {
    module->par(name) = val;
    return;
  }
  cParImpl *p = new cBoolParImpl();
  p->setName(name);
  p->setBoolValue(val);
  p->setIsMutable(true);
  module->addPar(p);
}

void setParObject(cModule *module, const char *name, cObject *val) {
  if (module->findPar(name) != -1) {
    module->par(name) = val;
    return;
  }
  cParImpl *p = new cObjectParImpl();
  p->setName(name);
  p->setObjectValue(val);
  p->setIsMutable(true);
  module->addPar(p);
}

void setParInt(cChannel *channel, const char *name, const int val) {
  if (channel->findPar(name) != -1) {
    channel->par(name) = val;
    return;
  }
  cParImpl *p = new cIntParImpl();
  p->setName(name);
  p->setIntValue(val);
  p->setIsMutable(true);
  channel->addPar(p);
}

void setParDouble(cChannel *channel, const char *name, const double val) {
  if (channel->findPar(name) != -1) {
    channel->par(name) = val;
    return;
  }
  cParImpl *p = new cDoubleParImpl();
  p->setName(name);
  p->setDoubleValue(val);
  p->setIsMutable(true);
  channel->addPar(p);
}

void setParStr(cChannel *channel, const char *name, const char *val) {
  if (channel->findPar(name) != -1) {
    channel->par(name) = val;
    return;
  }
  cParImpl *p = new cStringParImpl();
  p->setName(name);
  p->setStringValue(val);
  p->setIsMutable(true);
  channel->addPar(p);
}

void setParBool(cChannel *channel, const char *name, const bool val) {
  if (channel->findPar(name) != -1) {
    channel->par(name) = val;
    return;
  }
  cParImpl *p = new cBoolParImpl();
  p->setName(name);
  p->setBoolValue(val);
  p->setIsMutable(true);
  channel->addPar(p);
}

void setParObject(cChannel *channel, const char *name, cObject *val) {
  if (channel->findPar(name) != -1) {
    channel->par(name) = val;
    return;
  }
  cParImpl *p = new cObjectParImpl();
  p->setName(name);
  p->setObjectValue(val);
  p->setIsMutable(true);
  channel->addPar(p);
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
quisp_test::rng::TestRNG *useTestRNG() {
  using quisp_test::env::StaticEnv;
  auto *env = dynamic_cast<StaticEnv *>(cSimulation::getStaticEnvir());
  auto *rng = new quisp_test::rng::TestRNG();
  env->rng = rng;
  return rng;
}

}  // namespace utils
}  // namespace quisp_test

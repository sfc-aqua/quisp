#pragma once

#include <omnetpp.h>
#include "RNG.h"
#include "Simulation.h"

namespace quisp_test {
namespace utils {

using omnetpp::cModule;
using quisp_test::simulation::TestSimulation;

void setParInt(cModule *module, const char *name, const int val);
void setParDouble(cModule *module, const char *name, const double val);
void setParBool(cModule *module, const char *name, const bool val);
void setParStr(cModule *module, const char *name, const char *val);
void setParObject(cModule *module, const char *name, omnetpp::cObject *val);
TestSimulation *prepareSimulation();
TestSimulation *getTestSimulation();
omnetpp::cEnvir *createStaticEnv();
quisp_test::rng::TestRNG *useTestRNG();

}  // namespace utils
}  // namespace quisp_test

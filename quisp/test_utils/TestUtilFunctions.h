#pragma once

#include <omnetpp.h>
#include "RNG.h"
#include "Simulation.h"

namespace quisp_test {
namespace utils {

using omnetpp::cChannel;
using omnetpp::cModule;
using quisp_test::simulation::TestSimulation;

void setParInt(cModule *module, const char *name, const int val);
void setParDouble(cModule *module, const char *name, const double val);
void setParDouble(cModule *module, const char *name, const double val, const char *unit);
void setParBool(cModule *module, const char *name, const bool val);
void setParStr(cModule *module, const char *name, const char *val);
void setParObject(cModule *module, const char *name, omnetpp::cObject *val);
void setParInt(cChannel *channel, const char *name, const int val);
void setParDouble(cChannel *channel, const char *name, const double val);
void setParDouble(cChannel *channel, const char *name, const double val, const char *unit);
void setParBool(cChannel *channel, const char *name, const bool val);
void setParStr(cChannel *channel, const char *name, const char *val);
void setParObject(cChannel *channel, const char *name, omnetpp::cObject *val);
TestSimulation *prepareSimulation();
TestSimulation *getTestSimulation();
omnetpp::cEnvir *createStaticEnv();
quisp_test::rng::TestRNG *useTestRNG();

}  // namespace utils
}  // namespace quisp_test

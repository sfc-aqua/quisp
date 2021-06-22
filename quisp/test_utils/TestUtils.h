#pragma once

#include "ModuleType.h"
#include "Simulation.h"
#include "StaticEnv.h"
#include "TestComponentProviderStrategy.h"

namespace quisp_test {
namespace utils {

using omnetpp::cModule;
using quisp_test::simulation::TestSimulation;

void setParInt(cModule *module, const char *name, const int val);
void setParBool(cModule *module, const char *name, const bool val);
void setParStr(cModule *module, const char *name, const char *val);
TestSimulation *prepareSimulation();
omnetpp::cEnvir *createStaticEnv();

}  // namespace utils

// use these functions and classes in your unit test.
using quisp_test::module_type::TestModuleType;
using quisp_test::strategy::TestComponentProviderStrategy;
using utils::createStaticEnv;
using utils::prepareSimulation;
using utils::setParBool;
using utils::setParInt;
using utils::setParStr;
}  // namespace quisp_test

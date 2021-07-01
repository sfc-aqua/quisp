#pragma once

#include "Gate.h"
#include "ModuleType.h"
#include "QNode.h"
#include "Simulation.h"
#include "StaticEnv.h"
#include "TestComponentProviderStrategy.h"
#include "UtilFunctions.h"

namespace quisp_test {

// use these functions and classes in your unit test.
using gate::TestGate;
using module_type::TestModuleType;
using qnode::TestQNode;
using strategy::TestComponentProviderStrategy;
using utils::createStaticEnv;
using utils::getTestSimulation;
using utils::prepareSimulation;
using utils::setParBool;
using utils::setParDouble;
using utils::setParInt;
using utils::setParStr;

}  // namespace quisp_test

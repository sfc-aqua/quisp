#pragma once

#include "AccessPrivate.h"
#include "Gate.h"
#include "ModuleType.h"
#include "QNode.h"
#include "Simulation.h"
#include "StaticEnv.h"
#include "TestComponentProviderStrategy.h"
#include "UtilFunctions.h"
#include "mock_backends/MockBackendQubit.h"
#include "mock_backends/MockQuantumBackend.h"
#include "mock_modules/MockHardwareMonitor.h"
#include "mock_modules/MockQubit.h"
#include "mock_modules/MockRealTimeController.h"
#include "mock_modules/MockRoutingDaemon.h"
#include "mock_modules/MockRuleEngine.h"

#include "mock_modules/MockQNicStore.h"

namespace quisp_test {

// use these functions and classes in your unit test.
using gate::TestGate;
using mock_backends::MockBackendQubit;
using mock_backends::MockQuantumBackend;
using mock_modules::hardware_monitor::MockHardwareMonitor;
using mock_modules::qnic_store::MockQNicStore;
using mock_modules::realtime_controller::MockRealTimeController;
using mock_modules::routing_daemon::MockRoutingDaemon;
using mock_modules::rule_engine::MockRuleEngine;
using mock_modules::stationary_qubit::MockQubit;
using module_type::TestModuleType;
using qnode::TestQNode;
using strategy::QNicSpec;
using strategy::TestComponentProviderStrategy;
using utils::createStaticEnv;
using utils::getTestSimulation;
using utils::prepareSimulation;
using utils::setParBool;
using utils::setParDouble;
using utils::setParInt;
using utils::setParStr;
using utils::useTestRNG;
}  // namespace quisp_test

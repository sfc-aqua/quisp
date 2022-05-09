#include <gtest/gtest.h>
#include <omnetpp.h>
#include <omnetpp/cownedobject.h>
#include <omnetpp/csimulation.h>
#include "test_utils/TestUtils.h"

int main(int argc, char **argv) {
  /**
   * DO NOT delete this _flag variable.
   * The variable declares that we are in the main function to omnetpp runtime.
   * This ensures the initialization of the omnetpp::cDefaultList which contains
   * whole cObjects. Sometimes it causes segmentation fault without the _flag var.
   */
  omnetpp::cStaticFlag _flag;
  /**
   * execute the processes defined by omnetpp's macro like Define_Module or Register_GlobalConfigOption.
   * this defines global variables for simulation
   */
  omnetpp::CodeFragments::executeAll(CodeFragments::STARTUP);
  /**
   * setup a simulation and its environment for testing.
   * OMNeT++'s methods expect that all modules are running on a simulation,
   * so it will cause segmentation faults or exceptions if there's no simulation env.
   */
  auto *env = quisp_test::createStaticEnv();
  omnetpp::cSimulation::setStaticEnvir(env);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

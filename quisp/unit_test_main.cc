#include <gtest/gtest.h>
#include <omnetpp.h>
#include "omnetpp/ccomponent.h"
#include "omnetpp/cenvir.h"
#include "omnetpp/cownedobject.h"
#include "omnetpp/csimulation.h"
#include "omnetpp/simtime.h"
#include "test_utils/StaticEnv.h"

int main(int argc, char **argv) {
  /**
   * DO NOT delete this _flag variable.
   * The variable declares that we are in the main function to omnetpp runtime.
   * This ensures the initialization of the omnetpp::cDefaultList which contains
   * whole cObjects. Sometimes it causes segmentation fault without the _flag var.
   */
  omnetpp::cStaticFlag _flag;
  auto *env = new quisp_test::StaticEnv;
  omnetpp::cSimulation::setStaticEnvir(env);
  /**
   * setup a simulation and its environment for testing.
   * OMNeT++'s methods expect that all modules are running on a simulation,
   * so it will cause segmentation faults or exceptions if there's no simulation env.
   */
  auto *sim = new omnetpp::cSimulation("test_sim", omnetpp::cSimulation::getStaticEnvir());
  omnetpp::cComponent::clearSignalState();
  omnetpp::cSimulation::setActiveSimulation(sim);
  omnetpp::SimTime::setScaleExp(-3);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

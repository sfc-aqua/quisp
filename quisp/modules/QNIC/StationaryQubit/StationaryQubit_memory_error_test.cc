#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <unsupported/Eigen/MatrixFunctions>
#include "StationaryQubit.h"
#include "omnetpp/simtime.h"

using namespace quisp::modules;
using namespace quisp_test;
namespace {

class StatQubitTarget : public StationaryQubit {
 public:
  using StationaryQubit::initialize;
  using StationaryQubit::par;
  StatQubitTarget() : StationaryQubit() { setComponentType(new TestModuleType("test qubit")); }
  void reset() {
    setFree(true);
    updated_time = SimTime(0);
    no_density_matrix_nullptr_entangled_partner_ok = true;
  }
  void fillParams() {
    // see networks/omnetpp.ini
    setParDouble(this, "emission_success_probability", 0.5);
    setParDouble(this, "memory_X_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_Y_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_Z_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_energy_excitation_rate", 0.000198);
    setParDouble(this, "memory_energy_relaxation_rate", 0.00000198);
    setParDouble(this, "memory_completely_mixed_rate", 0);

    setParDouble(this, "Hgate_error_rate", 1 / 2000);
    setParDouble(this, "Hgate_X_error_ratio", 0);
    setParDouble(this, "Hgate_Z_error_ratio", 0);
    setParDouble(this, "Hgate_Y_error_ratio", 0);

    setParDouble(this, "Xgate_error_rate", 1 / 2000);
    setParDouble(this, "Xgate_X_error_ratio", 0);
    setParDouble(this, "Xgate_Z_error_ratio", 0);
    setParDouble(this, "Xgate_Y_error_ratio", 0);

    setParDouble(this, "Zgate_error_rate", 1 / 2000);
    setParDouble(this, "Zgate_X_error_ratio", 0);
    setParDouble(this, "Zgate_Z_error_ratio", 0);
    setParDouble(this, "Zgate_Y_error_ratio", 0);

    setParDouble(this, "Measurement_error_rate", 1 / 2000);
    setParDouble(this, "Measurement_X_error_ratio", 1);
    setParDouble(this, "Measurement_Y_error_ratio", 1);
    setParDouble(this, "Measurement_Z_error_ratio", 1);

    setParDouble(this, "CNOTgate_error_rate", 1 / 2000);
    setParDouble(this, "CNOTgate_IX_error_ratio", 1);
    setParDouble(this, "CNOTgate_XI_error_ratio", 1);
    setParDouble(this, "CNOTgate_XX_error_ratio", 1);
    setParDouble(this, "CNOTgate_IZ_error_ratio", 1);
    setParDouble(this, "CNOTgate_ZI_error_ratio", 1);
    setParDouble(this, "CNOTgate_ZZ_error_ratio", 1);
    setParDouble(this, "CNOTgate_IY_error_ratio", 1);
    setParDouble(this, "CNOTgate_YI_error_ratio", 1);
    setParDouble(this, "CNOTgate_YY_error_ratio", 1);

    setParInt(this, "stationaryQubit_address", 1);
    setParInt(this, "node_address", 1);
    setParInt(this, "qnic_address", 1);
    setParInt(this, "qnic_type", 0);
    setParInt(this, "qnic_index", 0);
    setParDouble(this, "std", 0.5);

    setParDouble(this, "photon_emitted_at", 0.0);
    setParDouble(this, "last_updated_at", 0.0);
    setParBool(this, "GOD_Xerror", false);
    setParBool(this, "GOD_Zerror", false);
    setParBool(this, "GOD_CMerror", false);
    setParBool(this, "GOD_EXerror", false);
    setParBool(this, "GOD_REerror", false);
    setParBool(this, "isBusy", false);
    setParInt(this, "GOD_entangled_stationaryQubit_address", 0);
    setParInt(this, "GOD_entangled_node_address", 0);
    setParInt(this, "GOD_entangled_qnic_address", 0);
    setParInt(this, "GOD_entangled_qnic_type", 0);
    setParDouble(this, "fidelity", -1.0);
  }
};

TEST(StatQubitMemoryErrorTest, do_nothing) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  qubit->callInitialize();
  qubit->reset();
  qubit->par("GOD_Xerror") = true;
  qubit->par("GOD_Zerror") = true;
  EXPECT_TRUE(qubit->par("GOD_Xerror"));
  EXPECT_TRUE(qubit->par("GOD_Zerror"));
  EXPECT_FALSE(qubit->par("GOD_REerror"));
  EXPECT_FALSE(qubit->par("GOD_EXerror"));
  sim->registerComponent(qubit);

  // if current time and updated_time are same, do nothing
  EXPECT_EQ(qubit->updated_time, SimTime(0));
  sim->setSimTime(SimTime(0, SIMTIME_US));
  qubit->apply_memory_error(qubit);

  EXPECT_EQ(qubit->updated_time, SimTime(0, SIMTIME_US));
  EXPECT_TRUE(qubit->par("GOD_Xerror"));
  EXPECT_TRUE(qubit->par("GOD_Zerror"));
  EXPECT_FALSE(qubit->par("GOD_REerror"));
  EXPECT_FALSE(qubit->par("GOD_EXerror"));
}
TEST(StatQubitMemoryErrorTest, update_timestamp) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  qubit->callInitialize();
  qubit->reset();
  EXPECT_EQ(qubit->updated_time, SimTime(0));
  sim->registerComponent(qubit);
  sim->setSimTime(SimTime(1, SIMTIME_US));
  qubit->apply_memory_error(qubit);
  EXPECT_EQ(qubit->updated_time, SimTime(1, SIMTIME_US));
}
TEST(StatQubitMemoryErrorTest, apply_memory_error_no_error) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();

  // Initial_condition << 1, 0, 0, 0, 0, 0, 0;
  // this means take 1st row of MemoryTransitionMatrix
  // ceiled values should be:
  // No error= 0.5, X error = 0.6, Z error = 0.7, Y error = 0.8, Excitation = 0.9, Relaxation = 1.0
  setParDouble(qubit, "memory_X_error_rate", .1);
  setParDouble(qubit, "memory_Y_error_rate", .1);
  setParDouble(qubit, "memory_Z_error_rate", .1);
  setParDouble(qubit, "memory_energy_excitation_rate", .1);
  setParDouble(qubit, "memory_energy_relaxation_rate", .1);
  setParDouble(qubit, "memory_completely_mixed_rate", 0);
  qubit->callInitialize();
  sim->registerComponent(qubit);
  sim->setSimTime(SimTime(1, SIMTIME_US));

  // X error
  qubit->reset();
  rng->doubleValue = 0.55;
  qubit->apply_memory_error(qubit);
  EXPECT_TRUE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

  // Z error
  rng->doubleValue = 0.65;
  qubit->reset();
  qubit->apply_memory_error(qubit);
  EXPECT_FALSE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

  // Y error
  rng->doubleValue = 0.75;
  qubit->reset();
  qubit->apply_memory_error(qubit);
  EXPECT_TRUE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

  // Excitation error
  rng->doubleValue = 0.85;
  qubit->reset();
  qubit->apply_memory_error(qubit);
  EXPECT_FALSE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

  // Relaxation error
  rng->doubleValue = 0.95;
  qubit->reset();
  qubit->apply_memory_error(qubit);
  EXPECT_FALSE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());
}

TEST(StatQubitMemoryErrorTest, apply_memory_error_X_error) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();

  // Initial_condition << 0, 1, 0, 0, 0, 0, 0;
  // this means take 2nd row of MemoryTransitionMatrix
  // ceiled values should be:
  // No error= 0.1, X error = 0.6, Z error = 0.7, Y error = 0.8, Excitation = 0.9, Relaxation = 1.0
  setParDouble(qubit, "memory_X_error_rate", .1);
  setParDouble(qubit, "memory_Y_error_rate", .1);
  setParDouble(qubit, "memory_Z_error_rate", .1);
  setParDouble(qubit, "memory_energy_excitation_rate", .1);
  setParDouble(qubit, "memory_energy_relaxation_rate", .1);
  setParDouble(qubit, "memory_completely_mixed_rate", 0);
  qubit->callInitialize();
  sim->registerComponent(qubit);
  sim->setSimTime(SimTime(1, SIMTIME_US));

  // X error
  qubit->reset();
  qubit->par("GOD_Xerror") = true;
  rng->doubleValue = 0.55;
  qubit->apply_memory_error(qubit);
  EXPECT_TRUE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

  // Z error
  rng->doubleValue = 0.65;
  qubit->reset();
  qubit->par("GOD_Xerror") = true;
  qubit->apply_memory_error(qubit);
  EXPECT_FALSE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

  // Y error
  rng->doubleValue = 0.75;
  qubit->reset();
  qubit->par("GOD_Xerror") = true;
  qubit->apply_memory_error(qubit);
  EXPECT_TRUE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

  // Excitation error
  rng->doubleValue = 0.85;
  qubit->reset();
  qubit->par("GOD_Xerror") = true;
  qubit->apply_memory_error(qubit);
  EXPECT_FALSE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

  // Relaxation error
  rng->doubleValue = 0.95;
  qubit->reset();
  qubit->par("GOD_Xerror") = true;
  qubit->apply_memory_error(qubit);
  EXPECT_FALSE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());
}

TEST(StatQubitMemoryErrorTest, apply_memory_error_Z_error) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();

  // Initial_condition << 0, 0, 1, 0, 0, 0, 0;
  // this means take 3rd row of MemoryTransitionMatrix
  // ceiled values should be:
  // No error= 0.1, X error = 0.6, Z error = 0.7, Y error = 0.8, Excitation = 0.9, Relaxation = 1.0
  setParDouble(qubit, "memory_X_error_rate", .1);
  setParDouble(qubit, "memory_Y_error_rate", .1);
  setParDouble(qubit, "memory_Z_error_rate", .1);
  setParDouble(qubit, "memory_energy_excitation_rate", .1);
  setParDouble(qubit, "memory_energy_relaxation_rate", .1);
  setParDouble(qubit, "memory_completely_mixed_rate", 0);
  qubit->callInitialize();
  sim->registerComponent(qubit);
  sim->setSimTime(SimTime(1, SIMTIME_US));

  // X error
  qubit->reset();
  qubit->par("GOD_Xerror") = true;
  rng->doubleValue = 0.55;
  qubit->apply_memory_error(qubit);
  EXPECT_TRUE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

  // Z error
  rng->doubleValue = 0.65;
  qubit->reset();
  qubit->par("GOD_Xerror") = true;
  qubit->apply_memory_error(qubit);
  EXPECT_FALSE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

  // Y error
  rng->doubleValue = 0.75;
  qubit->reset();
  qubit->par("GOD_Xerror") = true;
  qubit->apply_memory_error(qubit);
  EXPECT_TRUE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

  // Excitation error
  rng->doubleValue = 0.85;
  qubit->reset();
  qubit->par("GOD_Xerror") = true;
  qubit->apply_memory_error(qubit);
  EXPECT_FALSE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

  // Relaxation error
  rng->doubleValue = 0.95;
  qubit->reset();
  qubit->par("GOD_Xerror") = true;
  qubit->apply_memory_error(qubit);
  EXPECT_FALSE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());
}

TEST(StatQubitMemoryErrorTest, apply_memory_error_Y_error) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();

  // Initial_condition << 0, 0, 0, 1, 0, 0, 0;
  // this means take 4th row of MemoryTransitionMatrix
  // ceiled values should be:
  // No error= 0.1, X error = 0.2, Z error = 0.3, Y error = 0.8, Excitation = 0.9, Relaxation = 1.0
  setParDouble(qubit, "memory_X_error_rate", .1);
  setParDouble(qubit, "memory_Y_error_rate", .1);
  setParDouble(qubit, "memory_Z_error_rate", .1);
  setParDouble(qubit, "memory_energy_excitation_rate", .1);
  setParDouble(qubit, "memory_energy_relaxation_rate", .1);
  setParDouble(qubit, "memory_completely_mixed_rate", 0);
  qubit->callInitialize();
  sim->registerComponent(qubit);
  sim->setSimTime(SimTime(1, SIMTIME_US));

  // X error
  qubit->reset();
  qubit->par("GOD_Xerror") = true;
  qubit->par("GOD_Zerror") = true;
  rng->doubleValue = 0.15;
  qubit->apply_memory_error(qubit);
  EXPECT_TRUE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

  // Z error
  rng->doubleValue = 0.25;
  qubit->reset();
  qubit->par("GOD_Xerror") = true;
  qubit->par("GOD_Zerror") = true;
  qubit->apply_memory_error(qubit);
  EXPECT_FALSE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

  // Y error
  rng->doubleValue = 0.5;
  qubit->reset();
  qubit->par("GOD_Xerror") = true;
  qubit->par("GOD_Zerror") = true;
  qubit->apply_memory_error(qubit);
  EXPECT_TRUE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

  // Excitation error
  rng->doubleValue = 0.85;
  qubit->reset();
  qubit->par("GOD_Xerror") = true;
  qubit->par("GOD_Zerror") = true;
  qubit->apply_memory_error(qubit);
  EXPECT_FALSE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

  // Relaxation error
  rng->doubleValue = 0.95;
  qubit->reset();
  qubit->par("GOD_Xerror") = true;
  qubit->par("GOD_Zerror") = true;
  qubit->apply_memory_error(qubit);
  EXPECT_FALSE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());
}

TEST(StatQubitMemoryErrorTest, apply_memory_error_excitation_error) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();

  // Initial_condition << 0, 0, 0, 0, 1, 0, 0;
  // this means take 5th row of MemoryTransitionMatrix
  // ceiled values should be:
  // No error= 0.1, X error = 0.2, Z error = 0.3, Y error = 0.8, Excitation = 0.9, Relaxation = 1.0
  setParDouble(qubit, "memory_X_error_rate", .1);
  setParDouble(qubit, "memory_Y_error_rate", .1);
  setParDouble(qubit, "memory_Z_error_rate", .1);
  setParDouble(qubit, "memory_energy_excitation_rate", .1);
  setParDouble(qubit, "memory_energy_relaxation_rate", .1);
  setParDouble(qubit, "memory_completely_mixed_rate", 0);
  qubit->callInitialize();
  sim->registerComponent(qubit);
  sim->setSimTime(SimTime(1, SIMTIME_US));

  // X error
  qubit->reset();
  qubit->par("GOD_EXerror") = true;
  rng->doubleValue = 0.15;
  qubit->apply_memory_error(qubit);
  EXPECT_FALSE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

  // Z error
  rng->doubleValue = 0.25;
  qubit->reset();
  qubit->par("GOD_EXerror") = true;
  qubit->apply_memory_error(qubit);
  EXPECT_FALSE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

  // Y error
  rng->doubleValue = 0.5;
  qubit->reset();
  qubit->par("GOD_EXerror") = true;
  qubit->apply_memory_error(qubit);
  EXPECT_FALSE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

  // Excitation error
  rng->doubleValue = 0.85;
  qubit->reset();
  qubit->par("GOD_EXerror") = true;
  qubit->apply_memory_error(qubit);
  EXPECT_FALSE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

  // Relaxation error
  rng->doubleValue = 0.95;
  qubit->reset();
  qubit->par("GOD_EXerror") = true;
  qubit->apply_memory_error(qubit);
  EXPECT_FALSE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());
}

TEST(StatQubitMemoryErrorTest, apply_memory_error_relaxation_error) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();

  // Initial_condition << 0, 0, 0, 0, 0, 1, 0;
  // this means take 6th row of MemoryTransitionMatrix
  // ceiled values should be:
  // No error= 0, X error = 0, Z error = 0, Y error = 0, Excitation = 0.1, Relaxation = 1.0
  setParDouble(qubit, "memory_X_error_rate", .1);
  setParDouble(qubit, "memory_Y_error_rate", .1);
  setParDouble(qubit, "memory_Z_error_rate", .1);
  setParDouble(qubit, "memory_energy_excitation_rate", .1);
  setParDouble(qubit, "memory_energy_relaxation_rate", .1);
  setParDouble(qubit, "memory_completely_mixed_rate", 0);
  qubit->callInitialize();
  sim->registerComponent(qubit);
  sim->setSimTime(SimTime(1, SIMTIME_US));

  // Excitation error
  rng->doubleValue = 0.05;
  qubit->reset();
  qubit->par("GOD_REerror") = true;
  qubit->apply_memory_error(qubit);
  EXPECT_FALSE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

  // Relaxation error
  rng->doubleValue = 0.95;
  qubit->reset();
  qubit->par("GOD_REerror") = true;
  qubit->apply_memory_error(qubit);
  EXPECT_FALSE(qubit->par("GOD_Xerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_Zerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_EXerror").boolValue());
  EXPECT_TRUE(qubit->par("GOD_REerror").boolValue());
  EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());
}

}  // namespace

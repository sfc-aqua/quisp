#include <gtest/gtest.h>
#include <modules/common_types.h>
#include <test_utils/TestUtils.h>
#include <unsupported/Eigen/MatrixFunctions>
#include "StationaryQubit.h"
#include "omnetpp/simtime.h"

using namespace quisp::modules;
using namespace quisp::modules::common;
using namespace quisp_test;
namespace {
class Strategy : public TestComponentProviderStrategy {
 public:
  Strategy() : backend(new MockQuantumBackend()) {}
  ~Strategy() {}
  IQuantumBackend *getQuantumBackend() override { return backend; }
  MockQuantumBackend *backend;
};

class StatQubitTarget : public StationaryQubit {
 public:
  using StationaryQubit::applyMemoryError;
  using StationaryQubit::initialize;
  using StationaryQubit::par;
  StatQubitTarget() : StationaryQubit() {
    setComponentType(new TestModuleType("test qubit"));
    provider.setStrategy(std::make_unique<Strategy>());
  }
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

    setParDouble(this, "Hgate_error_rate", 1. / 2000);
    setParDouble(this, "Hgate_X_error_ratio", 0);
    setParDouble(this, "Hgate_Z_error_ratio", 0);
    setParDouble(this, "Hgate_Y_error_ratio", 0);

    setParDouble(this, "Xgate_error_rate", 1. / 2000);
    setParDouble(this, "Xgate_X_error_ratio", 0);
    setParDouble(this, "Xgate_Z_error_ratio", 0);
    setParDouble(this, "Xgate_Y_error_ratio", 0);

    setParDouble(this, "Zgate_error_rate", 1. / 2000);
    setParDouble(this, "Zgate_X_error_ratio", 0);
    setParDouble(this, "Zgate_Z_error_ratio", 0);
    setParDouble(this, "Zgate_Y_error_ratio", 0);

    setParDouble(this, "CNOTgate_error_rate", 1. / 2000);
    setParDouble(this, "CNOTgate_IX_error_ratio", 1);
    setParDouble(this, "CNOTgate_XI_error_ratio", 1);
    setParDouble(this, "CNOTgate_XX_error_ratio", 1);
    setParDouble(this, "CNOTgate_IZ_error_ratio", 1);
    setParDouble(this, "CNOTgate_ZI_error_ratio", 1);
    setParDouble(this, "CNOTgate_ZZ_error_ratio", 1);
    setParDouble(this, "CNOTgate_IY_error_ratio", 1);
    setParDouble(this, "CNOTgate_YI_error_ratio", 1);
    setParDouble(this, "CNOTgate_YY_error_ratio", 1);

    setParDouble(this, "X_measurement_error_rate", 1. / 2000);
    setParDouble(this, "Y_measurement_error_rate", 1. / 2000);
    setParDouble(this, "Z_measurement_error_rate", 1. / 2000);

    setParInt(this, "stationary_qubit_address", 1);
    setParInt(this, "node_address", 1);
    setParInt(this, "qnic_address", 1);
    setParInt(this, "qnic_type", 0);
    setParInt(this, "qnic_index", 0);
    setParDouble(this, "std", 0.5);

    setParDouble(this, "photon_emitted_at", 0.0);
    setParDouble(this, "last_updated_at", 0.0);
    setParBool(this, "god_x_error", false);
    setParBool(this, "god_z_error", false);
    setParBool(this, "god_completely_mixed_error", false);
    setParBool(this, "god_excitation_error", false);
    setParBool(this, "god_relaxation_error", false);
    setParBool(this, "is_busy", false);
    setParInt(this, "god_entangled_stationaryQubit_address", 0);
    setParInt(this, "god_entangled_node_address", 0);
    setParInt(this, "god_entangled_qnic_address", 0);
    setParInt(this, "god_entangled_qnic_type", 0);
    setParDouble(this, "fidelity", -1.0);
  }
};

TEST(StatQubitMemoryErrorTest, do_nothing) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  sim->registerComponent(qubit);

  qubit->callInitialize();
  qubit->reset();
  qubit->par("god_x_error") = true;
  qubit->par("god_z_error") = true;
  EXPECT_TRUE(qubit->par("god_x_error"));
  EXPECT_TRUE(qubit->par("god_z_error"));
  EXPECT_FALSE(qubit->par("god_relaxation_error"));
  EXPECT_FALSE(qubit->par("god_excitation_error"));

  // if current time and updated_time are same, do nothing
  EXPECT_EQ(qubit->updated_time, SimTime(0));
  sim->setSimTime(SimTime(0, SIMTIME_US));
  qubit->applyMemoryError();

  EXPECT_EQ(qubit->updated_time, SimTime(0, SIMTIME_US));
  EXPECT_TRUE(qubit->par("god_x_error"));
  EXPECT_TRUE(qubit->par("god_z_error"));
  EXPECT_FALSE(qubit->par("god_relaxation_error"));
  EXPECT_FALSE(qubit->par("god_excitation_error"));
}
TEST(StatQubitMemoryErrorTest, update_timestamp) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  sim->registerComponent(qubit);

  qubit->callInitialize();
  qubit->reset();
  EXPECT_EQ(qubit->updated_time, SimTime(0));
  sim->setSimTime(SimTime(1, SIMTIME_US));
  qubit->applyMemoryError();
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
  sim->registerComponent(qubit);

  qubit->callInitialize();
  sim->setSimTime(SimTime(1, SIMTIME_US));

  // X error
  qubit->reset();
  rng->doubleValue = 0.55;
  qubit->applyMemoryError();
  EXPECT_TRUE(qubit->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());

  // Z error
  rng->doubleValue = 0.65;
  qubit->reset();
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->par("god_x_error").boolValue());
  EXPECT_TRUE(qubit->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());

  // Y error
  rng->doubleValue = 0.75;
  qubit->reset();
  qubit->applyMemoryError();
  EXPECT_TRUE(qubit->par("god_x_error").boolValue());
  EXPECT_TRUE(qubit->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());

  // Excitation error
  rng->doubleValue = 0.85;
  qubit->reset();
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit->par("god_z_error").boolValue());
  EXPECT_TRUE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());

  // Relaxation error
  rng->doubleValue = 0.95;
  qubit->reset();
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit->par("god_excitation_error").boolValue());
  EXPECT_TRUE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());
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
  sim->registerComponent(qubit);
  qubit->callInitialize();
  sim->setSimTime(SimTime(1, SIMTIME_US));

  // X error
  qubit->reset();
  qubit->par("god_x_error") = true;
  rng->doubleValue = 0.55;
  qubit->applyMemoryError();
  EXPECT_TRUE(qubit->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());

  // Z error
  rng->doubleValue = 0.65;
  qubit->reset();
  qubit->par("god_x_error") = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->par("god_x_error").boolValue());
  EXPECT_TRUE(qubit->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());

  // Y error
  rng->doubleValue = 0.75;
  qubit->reset();
  qubit->par("god_x_error") = true;
  qubit->applyMemoryError();
  EXPECT_TRUE(qubit->par("god_x_error").boolValue());
  EXPECT_TRUE(qubit->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());

  // Excitation error
  rng->doubleValue = 0.85;
  qubit->reset();
  qubit->par("god_x_error") = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit->par("god_z_error").boolValue());
  EXPECT_TRUE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());

  // Relaxation error
  rng->doubleValue = 0.95;
  qubit->reset();
  qubit->par("god_x_error") = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit->par("god_excitation_error").boolValue());
  EXPECT_TRUE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());
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
  sim->registerComponent(qubit);
  qubit->callInitialize();
  sim->setSimTime(SimTime(1, SIMTIME_US));

  // X error
  qubit->reset();
  qubit->par("god_x_error") = true;
  rng->doubleValue = 0.55;
  qubit->applyMemoryError();
  EXPECT_TRUE(qubit->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());

  // Z error
  rng->doubleValue = 0.65;
  qubit->reset();
  qubit->par("god_x_error") = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->par("god_x_error").boolValue());
  EXPECT_TRUE(qubit->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());

  // Y error
  rng->doubleValue = 0.75;
  qubit->reset();
  qubit->par("god_x_error") = true;
  qubit->applyMemoryError();
  EXPECT_TRUE(qubit->par("god_x_error").boolValue());
  EXPECT_TRUE(qubit->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());

  // Excitation error
  rng->doubleValue = 0.85;
  qubit->reset();
  qubit->par("god_x_error") = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit->par("god_z_error").boolValue());
  EXPECT_TRUE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());

  // Relaxation error
  rng->doubleValue = 0.95;
  qubit->reset();
  qubit->par("god_x_error") = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit->par("god_excitation_error").boolValue());
  EXPECT_TRUE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());
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
  sim->registerComponent(qubit);
  qubit->callInitialize();
  sim->setSimTime(SimTime(1, SIMTIME_US));

  // X error
  qubit->reset();
  qubit->par("god_x_error") = true;
  qubit->par("god_z_error") = true;
  rng->doubleValue = 0.15;
  qubit->applyMemoryError();
  EXPECT_TRUE(qubit->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());

  // Z error
  rng->doubleValue = 0.25;
  qubit->reset();
  qubit->par("god_x_error") = true;
  qubit->par("god_z_error") = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->par("god_x_error").boolValue());
  EXPECT_TRUE(qubit->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());

  // Y error
  rng->doubleValue = 0.5;
  qubit->reset();
  qubit->par("god_x_error") = true;
  qubit->par("god_z_error") = true;
  qubit->applyMemoryError();
  EXPECT_TRUE(qubit->par("god_x_error").boolValue());
  EXPECT_TRUE(qubit->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());

  // Excitation error
  rng->doubleValue = 0.85;
  qubit->reset();
  qubit->par("god_x_error") = true;
  qubit->par("god_z_error") = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit->par("god_z_error").boolValue());
  EXPECT_TRUE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());

  // Relaxation error
  rng->doubleValue = 0.95;
  qubit->reset();
  qubit->par("god_x_error") = true;
  qubit->par("god_z_error") = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit->par("god_excitation_error").boolValue());
  EXPECT_TRUE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());
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
  sim->registerComponent(qubit);
  qubit->callInitialize();
  sim->setSimTime(SimTime(1, SIMTIME_US));

  // X error
  qubit->reset();
  qubit->par("god_excitation_error") = true;
  rng->doubleValue = 0.15;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit->par("god_z_error").boolValue());
  EXPECT_TRUE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());

  // Z error
  rng->doubleValue = 0.25;
  qubit->reset();
  qubit->par("god_excitation_error") = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit->par("god_z_error").boolValue());
  EXPECT_TRUE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());

  // Y error
  rng->doubleValue = 0.5;
  qubit->reset();
  qubit->par("god_excitation_error") = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit->par("god_z_error").boolValue());
  EXPECT_TRUE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());

  // Excitation error
  rng->doubleValue = 0.85;
  qubit->reset();
  qubit->par("god_excitation_error") = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit->par("god_z_error").boolValue());
  EXPECT_TRUE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());

  // Relaxation error
  rng->doubleValue = 0.95;
  qubit->reset();
  qubit->par("god_excitation_error") = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit->par("god_excitation_error").boolValue());
  EXPECT_TRUE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());
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
  sim->registerComponent(qubit);
  qubit->callInitialize();
  sim->setSimTime(SimTime(1, SIMTIME_US));

  // Excitation error
  rng->doubleValue = 0.05;
  qubit->reset();
  qubit->par("god_relaxation_error") = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit->par("god_z_error").boolValue());
  EXPECT_TRUE(qubit->par("god_excitation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());

  // Relaxation error
  rng->doubleValue = 0.95;
  qubit->reset();
  qubit->par("god_relaxation_error") = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->par("god_x_error").boolValue());
  EXPECT_FALSE(qubit->par("god_z_error").boolValue());
  EXPECT_FALSE(qubit->par("god_excitation_error").boolValue());
  EXPECT_TRUE(qubit->par("god_relaxation_error").boolValue());
  EXPECT_FALSE(qubit->par("god_completely_mixed_error").boolValue());
}

}  // namespace

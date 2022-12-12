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
    setParDouble(this, "memory_x_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_y_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_z_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_energy_excitation_rate", 0.000198);
    setParDouble(this, "memory_energy_relaxation_rate", 0.00000198);
    setParDouble(this, "memory_completely_mixed_rate", 0);

    setParDouble(this, "h_gate_error_rate", 1. / 2000);
    setParDouble(this, "h_gate_x_error_ratio", 0);
    setParDouble(this, "h_gate_z_error_ratio", 0);
    setParDouble(this, "h_gate_y_error_ratio", 0);

    setParDouble(this, "x_gate_error_rate", 1. / 2000);
    setParDouble(this, "x_gate_x_error_ratio", 0);
    setParDouble(this, "x_gate_z_error_ratio", 0);
    setParDouble(this, "x_gate_y_error_ratio", 0);

    setParDouble(this, "z_gate_error_rate", 1. / 2000);
    setParDouble(this, "z_gate_x_error_ratio", 0);
    setParDouble(this, "z_gate_z_error_ratio", 0);
    setParDouble(this, "z_gate_y_error_ratio", 0);

    setParDouble(this, "cnot_gate_error_rate", 1. / 2000);
    setParDouble(this, "cnot_gate_ix_error_ratio", 1);
    setParDouble(this, "cnot_gate_xi_error_ratio", 1);
    setParDouble(this, "cnot_gate_xx_error_ratio", 1);
    setParDouble(this, "cnot_gate_iz_error_ratio", 1);
    setParDouble(this, "cnot_gate_zi_error_ratio", 1);
    setParDouble(this, "cnot_gate_zz_error_ratio", 1);
    setParDouble(this, "cnot_gate_iy_error_ratio", 1);
    setParDouble(this, "cnot_gate_yi_error_ratio", 1);
    setParDouble(this, "cnot_gate_yy_error_ratio", 1);

    setParDouble(this, "x_measurement_error_rate", 1. / 2000);
    setParDouble(this, "y_measurement_error_rate", 1. / 2000);
    setParDouble(this, "z_measurement_error_rate", 1. / 2000);

    setParInt(this, "stationary_qubit_address", 1);
    setParInt(this, "node_address", 1);
    setParInt(this, "qnic_address", 1);
    setParInt(this, "qnic_type", 0);
    setParInt(this, "qnic_index", 0);
    setParDouble(this, "std", 0.5);

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
  qubit->god_err.has_x_error = true;
  qubit->god_err.has_z_error = true;
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_FALSE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_excitation_error);

  // if current time and updated_time are same, do nothing
  EXPECT_EQ(qubit->updated_time, SimTime(0));
  sim->setSimTime(SimTime(0, SIMTIME_US));
  qubit->applyMemoryError();

  EXPECT_EQ(qubit->updated_time, SimTime(0, SIMTIME_US));
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_FALSE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_excitation_error);
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
  setParDouble(qubit, "memory_x_error_rate", .1);
  setParDouble(qubit, "memory_y_error_rate", .1);
  setParDouble(qubit, "memory_z_error_rate", .1);
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
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_FALSE(qubit->god_err.has_excitation_error);
  EXPECT_FALSE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);

  // Z error
  rng->doubleValue = 0.65;
  qubit->reset();
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_FALSE(qubit->god_err.has_excitation_error);
  EXPECT_FALSE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);

  // Y error
  rng->doubleValue = 0.75;
  qubit->reset();
  qubit->applyMemoryError();
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_FALSE(qubit->god_err.has_excitation_error);
  EXPECT_FALSE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);

  // Excitation error
  rng->doubleValue = 0.85;
  qubit->reset();
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_TRUE(qubit->god_err.has_excitation_error);
  EXPECT_FALSE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);

  // Relaxation error
  rng->doubleValue = 0.95;
  qubit->reset();
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_FALSE(qubit->god_err.has_excitation_error);
  EXPECT_TRUE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);
}

TEST(StatQubitMemoryErrorTest, apply_memory_error_x_error) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();

  // Initial_condition << 0, 1, 0, 0, 0, 0, 0;
  // this means take 2nd row of MemoryTransitionMatrix
  // ceiled values should be:
  // No error= 0.1, X error = 0.6, Z error = 0.7, Y error = 0.8, Excitation = 0.9, Relaxation = 1.0
  setParDouble(qubit, "memory_x_error_rate", .1);
  setParDouble(qubit, "memory_y_error_rate", .1);
  setParDouble(qubit, "memory_z_error_rate", .1);
  setParDouble(qubit, "memory_energy_excitation_rate", .1);
  setParDouble(qubit, "memory_energy_relaxation_rate", .1);
  setParDouble(qubit, "memory_completely_mixed_rate", 0);
  sim->registerComponent(qubit);
  qubit->callInitialize();
  sim->setSimTime(SimTime(1, SIMTIME_US));

  // X error
  qubit->reset();
  qubit->god_err.has_x_error = true;
  rng->doubleValue = 0.55;
  qubit->applyMemoryError();
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_FALSE(qubit->god_err.has_excitation_error);
  EXPECT_FALSE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);

  // Z error
  rng->doubleValue = 0.65;
  qubit->reset();
  qubit->god_err.has_x_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_FALSE(qubit->god_err.has_excitation_error);
  EXPECT_FALSE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);

  // Y error
  rng->doubleValue = 0.75;
  qubit->reset();
  qubit->god_err.has_x_error = true;
  qubit->applyMemoryError();
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_FALSE(qubit->god_err.has_excitation_error);
  EXPECT_FALSE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);

  // Excitation error
  rng->doubleValue = 0.85;
  qubit->reset();
  qubit->god_err.has_x_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_TRUE(qubit->god_err.has_excitation_error);
  EXPECT_FALSE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);

  // Relaxation error
  rng->doubleValue = 0.95;
  qubit->reset();
  qubit->god_err.has_x_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_FALSE(qubit->god_err.has_excitation_error);
  EXPECT_TRUE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);
}

TEST(StatQubitMemoryErrorTest, apply_memory_error_z_error) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();

  // Initial_condition << 0, 0, 1, 0, 0, 0, 0;
  // this means take 3rd row of MemoryTransitionMatrix
  // ceiled values should be:
  // No error= 0.1, X error = 0.6, Z error = 0.7, Y error = 0.8, Excitation = 0.9, Relaxation = 1.0
  setParDouble(qubit, "memory_x_error_rate", .1);
  setParDouble(qubit, "memory_y_error_rate", .1);
  setParDouble(qubit, "memory_z_error_rate", .1);
  setParDouble(qubit, "memory_energy_excitation_rate", .1);
  setParDouble(qubit, "memory_energy_relaxation_rate", .1);
  setParDouble(qubit, "memory_completely_mixed_rate", 0);
  sim->registerComponent(qubit);
  qubit->callInitialize();
  sim->setSimTime(SimTime(1, SIMTIME_US));

  // X error
  qubit->reset();
  qubit->god_err.has_x_error = true;
  rng->doubleValue = 0.55;
  qubit->applyMemoryError();
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_FALSE(qubit->god_err.has_excitation_error);
  EXPECT_FALSE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);

  // Z error
  rng->doubleValue = 0.65;
  qubit->reset();
  qubit->god_err.has_x_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_FALSE(qubit->god_err.has_excitation_error);
  EXPECT_FALSE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);

  // Y error
  rng->doubleValue = 0.75;
  qubit->reset();
  qubit->god_err.has_x_error = true;
  qubit->applyMemoryError();
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_FALSE(qubit->god_err.has_excitation_error);
  EXPECT_FALSE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);

  // Excitation error
  rng->doubleValue = 0.85;
  qubit->reset();
  qubit->god_err.has_x_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_TRUE(qubit->god_err.has_excitation_error);
  EXPECT_FALSE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);

  // Relaxation error
  rng->doubleValue = 0.95;
  qubit->reset();
  qubit->god_err.has_x_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_FALSE(qubit->god_err.has_excitation_error);
  EXPECT_TRUE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);
}

TEST(StatQubitMemoryErrorTest, apply_memory_error_y_error) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();

  // Initial_condition << 0, 0, 0, 1, 0, 0, 0;
  // this means take 4th row of MemoryTransitionMatrix
  // ceiled values should be:
  // No error= 0.1, X error = 0.2, Z error = 0.3, Y error = 0.8, Excitation = 0.9, Relaxation = 1.0
  setParDouble(qubit, "memory_x_error_rate", .1);
  setParDouble(qubit, "memory_y_error_rate", .1);
  setParDouble(qubit, "memory_z_error_rate", .1);
  setParDouble(qubit, "memory_energy_excitation_rate", .1);
  setParDouble(qubit, "memory_energy_relaxation_rate", .1);
  setParDouble(qubit, "memory_completely_mixed_rate", 0);
  sim->registerComponent(qubit);
  qubit->callInitialize();
  sim->setSimTime(SimTime(1, SIMTIME_US));

  // X error
  qubit->reset();
  qubit->god_err.has_x_error = true;
  qubit->god_err.has_z_error = true;
  rng->doubleValue = 0.15;
  qubit->applyMemoryError();
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_FALSE(qubit->god_err.has_excitation_error);
  EXPECT_FALSE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);

  // Z error
  rng->doubleValue = 0.25;
  qubit->reset();
  qubit->god_err.has_x_error = true;
  qubit->god_err.has_z_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_FALSE(qubit->god_err.has_excitation_error);
  EXPECT_FALSE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);

  // Y error
  rng->doubleValue = 0.5;
  qubit->reset();
  qubit->god_err.has_x_error = true;
  qubit->god_err.has_z_error = true;
  qubit->applyMemoryError();
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_FALSE(qubit->god_err.has_excitation_error);
  EXPECT_FALSE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);

  // Excitation error
  rng->doubleValue = 0.85;
  qubit->reset();
  qubit->god_err.has_x_error = true;
  qubit->god_err.has_z_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_TRUE(qubit->god_err.has_excitation_error);
  EXPECT_FALSE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);

  // Relaxation error
  rng->doubleValue = 0.95;
  qubit->reset();
  qubit->god_err.has_x_error = true;
  qubit->god_err.has_z_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_FALSE(qubit->god_err.has_excitation_error);
  EXPECT_TRUE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);
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
  setParDouble(qubit, "memory_x_error_rate", .1);
  setParDouble(qubit, "memory_y_error_rate", .1);
  setParDouble(qubit, "memory_z_error_rate", .1);
  setParDouble(qubit, "memory_energy_excitation_rate", .1);
  setParDouble(qubit, "memory_energy_relaxation_rate", .1);
  setParDouble(qubit, "memory_completely_mixed_rate", 0);
  sim->registerComponent(qubit);
  qubit->callInitialize();
  sim->setSimTime(SimTime(1, SIMTIME_US));

  // X error
  qubit->reset();
  qubit->god_err.has_excitation_error = true;
  rng->doubleValue = 0.15;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_TRUE(qubit->god_err.has_excitation_error);
  EXPECT_FALSE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);

  // Z error
  rng->doubleValue = 0.25;
  qubit->reset();
  qubit->god_err.has_excitation_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_TRUE(qubit->god_err.has_excitation_error);
  EXPECT_FALSE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);

  // Y error
  rng->doubleValue = 0.5;
  qubit->reset();
  qubit->god_err.has_excitation_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_TRUE(qubit->god_err.has_excitation_error);
  EXPECT_FALSE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);

  // Excitation error
  rng->doubleValue = 0.85;
  qubit->reset();
  qubit->god_err.has_excitation_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_TRUE(qubit->god_err.has_excitation_error);
  EXPECT_FALSE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);

  // Relaxation error
  rng->doubleValue = 0.95;
  qubit->reset();
  qubit->god_err.has_excitation_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_FALSE(qubit->god_err.has_excitation_error);
  EXPECT_TRUE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);
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
  setParDouble(qubit, "memory_x_error_rate", .1);
  setParDouble(qubit, "memory_y_error_rate", .1);
  setParDouble(qubit, "memory_z_error_rate", .1);
  setParDouble(qubit, "memory_energy_excitation_rate", .1);
  setParDouble(qubit, "memory_energy_relaxation_rate", .1);
  setParDouble(qubit, "memory_completely_mixed_rate", 0);
  sim->registerComponent(qubit);
  qubit->callInitialize();
  sim->setSimTime(SimTime(1, SIMTIME_US));

  // Excitation error
  rng->doubleValue = 0.05;
  qubit->reset();
  qubit->god_err.has_relaxation_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_TRUE(qubit->god_err.has_excitation_error);
  EXPECT_FALSE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);

  // Relaxation error
  rng->doubleValue = 0.95;
  qubit->reset();
  qubit->god_err.has_relaxation_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_FALSE(qubit->god_err.has_excitation_error);
  EXPECT_TRUE(qubit->god_err.has_relaxation_error);
  EXPECT_FALSE(qubit->god_err.has_completely_mixed_error);
}

}  // namespace

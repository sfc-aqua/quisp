#include "Qubit.h"
#include <backends/Backends.h>
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <unsupported/Eigen/MatrixFunctions>

namespace {
using namespace quisp::backends;
using error_tracking::ErrorTrackingQubit;

class Qubit : public ErrorTrackingQubit {
 public:
  using ErrorTrackingQubit::applyMemoryError;
  using ErrorTrackingQubit::has_excitation_error;
  using ErrorTrackingQubit::has_relaxation_error;
  using ErrorTrackingQubit::has_x_error;
  using ErrorTrackingQubit::has_z_error;
  using ErrorTrackingQubit::updated_time;

  Qubit(QubitId id = {0, 0, 0, 0}) : ErrorTrackingQubit(id) {}
  void reset() {
    // setFree(true);
    // updated_time = SimTime(0);
    // no_density_matrix_nullptr_entangled_partner_ok = true;
  }
  void fillParams() {
    // see networks/omnetpp.ini
    // setParDouble(this, "emission_success_probability", 0.5);
    double memory_X_error_rate = 1.11111111e-7;
    double memory_Y_error_rate = 1.11111111e-7;
    double memory_Z_error_rate = 1.11111111e-7;
    double memory_energy_excitation_rate = 0.000198;
    double memory_energy_relaxation_rate = 0.00000198;
    double memory_completely_mixed_rate = 0;
    this->setMemoryErrorRates(memory_X_error_rate, memory_Y_error_rate, memory_Z_error_rate, memory_energy_excitation_rate, memory_energy_relaxation_rate,
                              memory_completely_mixed_rate);

    double Hgate_error_rate = 1. / 2000;
    double Hgate_X_error_ratio = 0;
    double Hgate_Z_error_ratio = 0;
    double Hgate_Y_error_ratio = 0;

    double Xgate_error_rate = 1. / 2000;
    double Xgate_X_error_ratio = 0;
    double Xgate_Z_error_ratio = 0;
    double Xgate_Y_error_ratio = 0;

    double Zgate_error_rate = 1. / 2000;
    double Zgate_X_error_ratio = 0;
    double Zgate_Z_error_ratio = 0;
    double Zgate_Y_error_ratio = 0;

    double CNOTgate_error_rate = 1. / 2000;
    double CNOTgate_IX_error_ratio = 1;
    double CNOTgate_XI_error_ratio = 1;
    double CNOTgate_XX_error_ratio = 1;
    double CNOTgate_IZ_error_ratio = 1;
    double CNOTgate_ZI_error_ratio = 1;
    double CNOTgate_ZZ_error_ratio = 1;
    double CNOTgate_IY_error_ratio = 1;
    double CNOTgate_YI_error_ratio = 1;
    double CNOTgate_YY_error_ratio = 1;

    double X_measurement_error_rate = 1. / 2000;
    double Y_measurement_error_rate = 1. / 2000;
    double Z_measurement_error_rate = 1. / 2000;

    int stationaryQubit_address = 1;
    int node_address = 1;
    int qnic_address = 1;
    int qnic_type = 0;
    int qnic_index = 0;
    double std = 0.5;

    double photon_emitted_at = 0.0;
    double last_updated_at = 0.0;
    int GOD_entangled_stationaryQubit_address = 0;
    int GOD_entangled_node_address = 0;
    int GOD_entangled_qnic_address = 0;
    int GOD_entangled_qnic_type = 0;
    double fidelity = -1.0;
  }
};

class ETQubitMemoryErrorTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    // to avoid the omnetpp::SimTime assertion
    SimTime::setScaleExp(-9);
    qubit = new Qubit{};
  }
  Qubit* qubit;
};

TEST_F(ETQubitMemoryErrorTest, do_nothing) {
  qubit->fillParams();
  qubit->reset();
  qubit->has_x_error = true;
  qubit->has_z_error = true;
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_excitation_error);

  // if current time and updated_time are same, do nothing
  EXPECT_EQ(qubit->updated_time, SimTime(0));
  // sim->setSimTime(SimTime(0, SIMTIME_US));
  qubit->applyMemoryError();

  EXPECT_EQ(qubit->updated_time, SimTime(0, SIMTIME_US));
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_excitation_error);
}
TEST_F(ETQubitMemoryErrorTest, update_timestamp) {
  auto* qubit = new Qubit{};
  qubit->fillParams();
  qubit->reset();
  // EXPECT_EQ(qubit->updated_time, SimTime(0));
  // sim->registerComponent(qubit);
  // sim->setSimTime(SimTime(1, SIMTIME_US));
  qubit->applyMemoryError();
  // EXPECT_EQ(qubit->updated_time, SimTime(1, SIMTIME_US));
}
// TEST(StatQubitMemoryErrorTest, apply_memory_error_no_error) {
//   auto *sim = prepareSimulation();
//   auto *rng = useTestRNG();
//   auto *qubit = new Qubit{};
//   qubit->fillParams();

//   // Initial_condition << 1, 0, 0, 0, 0, 0, 0;
//   // this means take 1st row of MemoryTransitionMatrix
//   // ceiled values should be:
//   // No error= 0.5, X error = 0.6, Z error = 0.7, Y error = 0.8, Excitation = 0.9, Relaxation = 1.0
//   setParDouble(qubit, "memory_X_error_rate", .1);
//   setParDouble(qubit, "memory_Y_error_rate", .1);
//   setParDouble(qubit, "memory_Z_error_rate", .1);
//   setParDouble(qubit, "memory_energy_excitation_rate", .1);
//   setParDouble(qubit, "memory_energy_relaxation_rate", .1);
//   setParDouble(qubit, "memory_completely_mixed_rate", 0);
//   qubit->callInitialize();
//   sim->registerComponent(qubit);
//   sim->setSimTime(SimTime(1, SIMTIME_US));

//   // X error
//   qubit->reset();
//   rng->doubleValue = 0.55;
//   qubit->applyMemoryError();
//   EXPECT_TRUE(qubit->has_x_error.boolValue());
//   EXPECT_FALSE(qubit->has_z_error.boolValue());
//   EXPECT_FALSE(qubit->has_excitation_error.boolValue());
//   EXPECT_FALSE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

//   // Z error
//   rng->doubleValue = 0.65;
//   qubit->reset();
//   qubit->applyMemoryError();
//   EXPECT_FALSE(qubit->has_x_error.boolValue());
//   EXPECT_TRUE(qubit->has_z_error.boolValue());
//   EXPECT_FALSE(qubit->has_excitation_error.boolValue());
//   EXPECT_FALSE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

//   // Y error
//   rng->doubleValue = 0.75;
//   qubit->reset();
//   qubit->applyMemoryError();
//   EXPECT_TRUE(qubit->has_x_error.boolValue());
//   EXPECT_TRUE(qubit->has_z_error.boolValue());
//   EXPECT_FALSE(qubit->has_excitation_error.boolValue());
//   EXPECT_FALSE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

//   // Excitation error
//   rng->doubleValue = 0.85;
//   qubit->reset();
//   qubit->applyMemoryError();
//   EXPECT_FALSE(qubit->has_x_error.boolValue());
//   EXPECT_FALSE(qubit->has_z_error.boolValue());
//   EXPECT_TRUE(qubit->has_excitation_error.boolValue());
//   EXPECT_FALSE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

//   // Relaxation error
//   rng->doubleValue = 0.95;
//   qubit->reset();
//   qubit->applyMemoryError();
//   EXPECT_FALSE(qubit->has_x_error.boolValue());
//   EXPECT_FALSE(qubit->has_z_error.boolValue());
//   EXPECT_FALSE(qubit->has_excitation_error.boolValue());
//   EXPECT_TRUE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());
// }

// TEST(StatQubitMemoryErrorTest, apply_memory_error_X_error) {
//   auto *sim = prepareSimulation();
//   auto *rng = useTestRNG();
//   auto *qubit = new Qubit{};
//   qubit->fillParams();

//   // Initial_condition << 0, 1, 0, 0, 0, 0, 0;
//   // this means take 2nd row of MemoryTransitionMatrix
//   // ceiled values should be:
//   // No error= 0.1, X error = 0.6, Z error = 0.7, Y error = 0.8, Excitation = 0.9, Relaxation = 1.0
//   setParDouble(qubit, "memory_X_error_rate", .1);
//   setParDouble(qubit, "memory_Y_error_rate", .1);
//   setParDouble(qubit, "memory_Z_error_rate", .1);
//   setParDouble(qubit, "memory_energy_excitation_rate", .1);
//   setParDouble(qubit, "memory_energy_relaxation_rate", .1);
//   setParDouble(qubit, "memory_completely_mixed_rate", 0);
//   qubit->callInitialize();
//   sim->registerComponent(qubit);
//   sim->setSimTime(SimTime(1, SIMTIME_US));

//   // X error
//   qubit->reset();
//   qubit->has_x_error = true;
//   rng->doubleValue = 0.55;
//   qubit->applyMemoryError();
//   EXPECT_TRUE(qubit->has_x_error.boolValue());
//   EXPECT_FALSE(qubit->has_z_error.boolValue());
//   EXPECT_FALSE(qubit->has_excitation_error.boolValue());
//   EXPECT_FALSE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

//   // Z error
//   rng->doubleValue = 0.65;
//   qubit->reset();
//   qubit->has_x_error = true;
//   qubit->applyMemoryError();
//   EXPECT_FALSE(qubit->has_x_error.boolValue());
//   EXPECT_TRUE(qubit->has_z_error.boolValue());
//   EXPECT_FALSE(qubit->has_excitation_error.boolValue());
//   EXPECT_FALSE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

//   // Y error
//   rng->doubleValue = 0.75;
//   qubit->reset();
//   qubit->has_x_error = true;
//   qubit->applyMemoryError();
//   EXPECT_TRUE(qubit->has_x_error.boolValue());
//   EXPECT_TRUE(qubit->has_z_error.boolValue());
//   EXPECT_FALSE(qubit->has_excitation_error.boolValue());
//   EXPECT_FALSE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

//   // Excitation error
//   rng->doubleValue = 0.85;
//   qubit->reset();
//   qubit->has_x_error = true;
//   qubit->applyMemoryError();
//   EXPECT_FALSE(qubit->has_x_error.boolValue());
//   EXPECT_FALSE(qubit->has_z_error.boolValue());
//   EXPECT_TRUE(qubit->has_excitation_error.boolValue());
//   EXPECT_FALSE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

//   // Relaxation error
//   rng->doubleValue = 0.95;
//   qubit->reset();
//   qubit->has_x_error = true;
//   qubit->applyMemoryError();
//   EXPECT_FALSE(qubit->has_x_error.boolValue());
//   EXPECT_FALSE(qubit->has_z_error.boolValue());
//   EXPECT_FALSE(qubit->has_excitation_error.boolValue());
//   EXPECT_TRUE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());
// }

// TEST(StatQubitMemoryErrorTest, apply_memory_error_Z_error) {
//   auto *sim = prepareSimulation();
//   auto *rng = useTestRNG();
//   auto *qubit = new Qubit{};
//   qubit->fillParams();

//   // Initial_condition << 0, 0, 1, 0, 0, 0, 0;
//   // this means take 3rd row of MemoryTransitionMatrix
//   // ceiled values should be:
//   // No error= 0.1, X error = 0.6, Z error = 0.7, Y error = 0.8, Excitation = 0.9, Relaxation = 1.0
//   setParDouble(qubit, "memory_X_error_rate", .1);
//   setParDouble(qubit, "memory_Y_error_rate", .1);
//   setParDouble(qubit, "memory_Z_error_rate", .1);
//   setParDouble(qubit, "memory_energy_excitation_rate", .1);
//   setParDouble(qubit, "memory_energy_relaxation_rate", .1);
//   setParDouble(qubit, "memory_completely_mixed_rate", 0);
//   qubit->callInitialize();
//   sim->registerComponent(qubit);
//   sim->setSimTime(SimTime(1, SIMTIME_US));

//   // X error
//   qubit->reset();
//   qubit->has_x_error = true;
//   rng->doubleValue = 0.55;
//   qubit->applyMemoryError();
//   EXPECT_TRUE(qubit->has_x_error.boolValue());
//   EXPECT_FALSE(qubit->has_z_error.boolValue());
//   EXPECT_FALSE(qubit->has_excitation_error.boolValue());
//   EXPECT_FALSE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

//   // Z error
//   rng->doubleValue = 0.65;
//   qubit->reset();
//   qubit->has_x_error = true;
//   qubit->applyMemoryError();
//   EXPECT_FALSE(qubit->has_x_error.boolValue());
//   EXPECT_TRUE(qubit->has_z_error.boolValue());
//   EXPECT_FALSE(qubit->has_excitation_error.boolValue());
//   EXPECT_FALSE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

//   // Y error
//   rng->doubleValue = 0.75;
//   qubit->reset();
//   qubit->has_x_error = true;
//   qubit->applyMemoryError();
//   EXPECT_TRUE(qubit->has_x_error.boolValue());
//   EXPECT_TRUE(qubit->has_z_error.boolValue());
//   EXPECT_FALSE(qubit->has_excitation_error.boolValue());
//   EXPECT_FALSE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

//   // Excitation error
//   rng->doubleValue = 0.85;
//   qubit->reset();
//   qubit->has_x_error = true;
//   qubit->applyMemoryError();
//   EXPECT_FALSE(qubit->has_x_error.boolValue());
//   EXPECT_FALSE(qubit->has_z_error.boolValue());
//   EXPECT_TRUE(qubit->has_excitation_error.boolValue());
//   EXPECT_FALSE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

//   // Relaxation error
//   rng->doubleValue = 0.95;
//   qubit->reset();
//   qubit->has_x_error = true;
//   qubit->applyMemoryError();
//   EXPECT_FALSE(qubit->has_x_error.boolValue());
//   EXPECT_FALSE(qubit->has_z_error.boolValue());
//   EXPECT_FALSE(qubit->has_excitation_error.boolValue());
//   EXPECT_TRUE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());
// }

// TEST(StatQubitMemoryErrorTest, apply_memory_error_Y_error) {
//   auto *sim = prepareSimulation();
//   auto *rng = useTestRNG();
//   auto *qubit = new Qubit{};
//   qubit->fillParams();

//   // Initial_condition << 0, 0, 0, 1, 0, 0, 0;
//   // this means take 4th row of MemoryTransitionMatrix
//   // ceiled values should be:
//   // No error= 0.1, X error = 0.2, Z error = 0.3, Y error = 0.8, Excitation = 0.9, Relaxation = 1.0
//   setParDouble(qubit, "memory_X_error_rate", .1);
//   setParDouble(qubit, "memory_Y_error_rate", .1);
//   setParDouble(qubit, "memory_Z_error_rate", .1);
//   setParDouble(qubit, "memory_energy_excitation_rate", .1);
//   setParDouble(qubit, "memory_energy_relaxation_rate", .1);
//   setParDouble(qubit, "memory_completely_mixed_rate", 0);
//   qubit->callInitialize();
//   sim->registerComponent(qubit);
//   sim->setSimTime(SimTime(1, SIMTIME_US));

//   // X error
//   qubit->reset();
//   qubit->has_x_error = true;
//   qubit->has_z_error = true;
//   rng->doubleValue = 0.15;
//   qubit->applyMemoryError();
//   EXPECT_TRUE(qubit->has_x_error.boolValue());
//   EXPECT_FALSE(qubit->has_z_error.boolValue());
//   EXPECT_FALSE(qubit->has_excitation_error.boolValue());
//   EXPECT_FALSE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

//   // Z error
//   rng->doubleValue = 0.25;
//   qubit->reset();
//   qubit->has_x_error = true;
//   qubit->has_z_error = true;
//   qubit->applyMemoryError();
//   EXPECT_FALSE(qubit->has_x_error.boolValue());
//   EXPECT_TRUE(qubit->has_z_error.boolValue());
//   EXPECT_FALSE(qubit->has_excitation_error.boolValue());
//   EXPECT_FALSE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

//   // Y error
//   rng->doubleValue = 0.5;
//   qubit->reset();
//   qubit->has_x_error = true;
//   qubit->has_z_error = true;
//   qubit->applyMemoryError();
//   EXPECT_TRUE(qubit->has_x_error.boolValue());
//   EXPECT_TRUE(qubit->has_z_error.boolValue());
//   EXPECT_FALSE(qubit->has_excitation_error.boolValue());
//   EXPECT_FALSE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

//   // Excitation error
//   rng->doubleValue = 0.85;
//   qubit->reset();
//   qubit->has_x_error = true;
//   qubit->has_z_error = true;
//   qubit->applyMemoryError();
//   EXPECT_FALSE(qubit->has_x_error.boolValue());
//   EXPECT_FALSE(qubit->has_z_error.boolValue());
//   EXPECT_TRUE(qubit->has_excitation_error.boolValue());
//   EXPECT_FALSE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

//   // Relaxation error
//   rng->doubleValue = 0.95;
//   qubit->reset();
//   qubit->has_x_error = true;
//   qubit->has_z_error = true;
//   qubit->applyMemoryError();
//   EXPECT_FALSE(qubit->has_x_error.boolValue());
//   EXPECT_FALSE(qubit->has_z_error.boolValue());
//   EXPECT_FALSE(qubit->has_excitation_error.boolValue());
//   EXPECT_TRUE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());
// }

// TEST(StatQubitMemoryErrorTest, apply_memory_error_excitation_error) {
//   auto *sim = prepareSimulation();
//   auto *rng = useTestRNG();
//   auto *qubit = new Qubit{};
//   qubit->fillParams();

//   // Initial_condition << 0, 0, 0, 0, 1, 0, 0;
//   // this means take 5th row of MemoryTransitionMatrix
//   // ceiled values should be:
//   // No error= 0.1, X error = 0.2, Z error = 0.3, Y error = 0.8, Excitation = 0.9, Relaxation = 1.0
//   setParDouble(qubit, "memory_X_error_rate", .1);
//   setParDouble(qubit, "memory_Y_error_rate", .1);
//   setParDouble(qubit, "memory_Z_error_rate", .1);
//   setParDouble(qubit, "memory_energy_excitation_rate", .1);
//   setParDouble(qubit, "memory_energy_relaxation_rate", .1);
//   setParDouble(qubit, "memory_completely_mixed_rate", 0);
//   qubit->callInitialize();
//   sim->registerComponent(qubit);
//   sim->setSimTime(SimTime(1, SIMTIME_US));

//   // X error
//   qubit->reset();
//   qubit->has_excitation_error = true;
//   rng->doubleValue = 0.15;
//   qubit->applyMemoryError();
//   EXPECT_FALSE(qubit->has_x_error.boolValue());
//   EXPECT_FALSE(qubit->has_z_error.boolValue());
//   EXPECT_TRUE(qubit->has_excitation_error.boolValue());
//   EXPECT_FALSE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

//   // Z error
//   rng->doubleValue = 0.25;
//   qubit->reset();
//   qubit->has_excitation_error = true;
//   qubit->applyMemoryError();
//   EXPECT_FALSE(qubit->has_x_error.boolValue());
//   EXPECT_FALSE(qubit->has_z_error.boolValue());
//   EXPECT_TRUE(qubit->has_excitation_error.boolValue());
//   EXPECT_FALSE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

//   // Y error
//   rng->doubleValue = 0.5;
//   qubit->reset();
//   qubit->has_excitation_error = true;
//   qubit->applyMemoryError();
//   EXPECT_FALSE(qubit->has_x_error.boolValue());
//   EXPECT_FALSE(qubit->has_z_error.boolValue());
//   EXPECT_TRUE(qubit->has_excitation_error.boolValue());
//   EXPECT_FALSE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

//   // Excitation error
//   rng->doubleValue = 0.85;
//   qubit->reset();
//   qubit->has_excitation_error = true;
//   qubit->applyMemoryError();
//   EXPECT_FALSE(qubit->has_x_error.boolValue());
//   EXPECT_FALSE(qubit->has_z_error.boolValue());
//   EXPECT_TRUE(qubit->has_excitation_error.boolValue());
//   EXPECT_FALSE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

//   // Relaxation error
//   rng->doubleValue = 0.95;
//   qubit->reset();
//   qubit->has_excitation_error = true;
//   qubit->applyMemoryError();
//   EXPECT_FALSE(qubit->has_x_error.boolValue());
//   EXPECT_FALSE(qubit->has_z_error.boolValue());
//   EXPECT_FALSE(qubit->has_excitation_error.boolValue());
//   EXPECT_TRUE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());
// }

// TEST(StatQubitMemoryErrorTest, apply_memory_error_relaxation_error) {
//   auto *sim = prepareSimulation();
//   auto *rng = useTestRNG();
//   auto *qubit = new Qubit{};
//   qubit->fillParams();

//   // Initial_condition << 0, 0, 0, 0, 0, 1, 0;
//   // this means take 6th row of MemoryTransitionMatrix
//   // ceiled values should be:
//   // No error= 0, X error = 0, Z error = 0, Y error = 0, Excitation = 0.1, Relaxation = 1.0
//   setParDouble(qubit, "memory_X_error_rate", .1);
//   setParDouble(qubit, "memory_Y_error_rate", .1);
//   setParDouble(qubit, "memory_Z_error_rate", .1);
//   setParDouble(qubit, "memory_energy_excitation_rate", .1);
//   setParDouble(qubit, "memory_energy_relaxation_rate", .1);
//   setParDouble(qubit, "memory_completely_mixed_rate", 0);
//   qubit->callInitialize();
//   sim->registerComponent(qubit);
//   sim->setSimTime(SimTime(1, SIMTIME_US));

//   // Excitation error
//   rng->doubleValue = 0.05;
//   qubit->reset();
//   qubit->has_relaxation_error = true;
//   qubit->applyMemoryError();
//   EXPECT_FALSE(qubit->has_x_error.boolValue());
//   EXPECT_FALSE(qubit->has_z_error.boolValue());
//   EXPECT_TRUE(qubit->has_excitation_error.boolValue());
//   EXPECT_FALSE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());

//   // Relaxation error
//   rng->doubleValue = 0.95;
//   qubit->reset();
//   qubit->has_relaxation_error = true;
//   qubit->applyMemoryError();
//   EXPECT_FALSE(qubit->has_x_error.boolValue());
//   EXPECT_FALSE(qubit->has_z_error.boolValue());
//   EXPECT_FALSE(qubit->has_excitation_error.boolValue());
//   EXPECT_TRUE(qubit->has_relaxation_error.boolValue());
//   EXPECT_FALSE(qubit->par("GOD_CMerror").boolValue());
// }

}  // namespace

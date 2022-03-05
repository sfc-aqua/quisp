#include <backends/Backends.h>
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <unsupported/Eigen/MatrixFunctions>
#include "test.h"

namespace {
using namespace quisp_test::backends;

class ETQubitMemoryErrorTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    // to avoid the omnetpp::SimTime assertion
    SimTime::setScaleExp(-9);
    rng = std::make_unique<TestRNG>();
    rng->doubleValue = .0;
    backend = std::make_unique<Backend>(rng.get());
    qubit = dynamic_cast<Qubit*>(backend->getQubit(0));
    if (qubit == nullptr) throw std::runtime_error("Qubit is nullptr");
    backend->setSimTime(SimTime(1, SIMTIME_US));
    fillParams(qubit);
  }

  void fillParams(Qubit* qubit) {
    // ceiled values should be:
    // No error= 0.1, X error = 0.6, Z error = 0.7, Y error = 0.8, Excitation = 0.9, Relaxation = 1.0
    double x_error_rate = .1;
    double y_error_rate = .1;
    double z_error_rate = .1;
    double energy_excitation_rate = .1;
    double energy_relaxation_rate = .1;
    double completely_mixed_rate = 0;
    qubit->setMemoryErrorRates(x_error_rate, y_error_rate, z_error_rate, energy_excitation_rate, energy_relaxation_rate, completely_mixed_rate);
  }

  Qubit* qubit;
  std::unique_ptr<Backend> backend;
  std::unique_ptr<TestRNG> rng;
};

TEST_F(ETQubitMemoryErrorTest, do_nothing) {
  qubit->reset();
  qubit->has_x_error = true;
  qubit->has_z_error = true;
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_excitation_error);

  // if current time and updated_time are same, do nothing
  EXPECT_EQ(qubit->updated_time, SimTime(0));
  backend->setSimTime(SimTime(0, SIMTIME_US));
  qubit->applyMemoryError();

  EXPECT_EQ(qubit->updated_time, SimTime(0, SIMTIME_US));
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_excitation_error);
}

TEST_F(ETQubitMemoryErrorTest, update_timestamp) {
  qubit->reset();
  EXPECT_EQ(qubit->updated_time, SimTime(0));
  backend->setSimTime(SimTime(1, SIMTIME_US));
  qubit->applyMemoryError();
  EXPECT_EQ(qubit->updated_time, SimTime(1, SIMTIME_US));
}

TEST_F(ETQubitMemoryErrorTest, apply_memory_error_no_error) {
  // Initial_condition << 1, 0, 0, 0, 0, 0, 0;

  // X error
  qubit->reset();
  rng->doubleValue = 0.55;
  qubit->applyMemoryError();
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Z error
  rng->doubleValue = 0.65;
  qubit->reset();
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Y error
  rng->doubleValue = 0.75;
  qubit->reset();
  qubit->applyMemoryError();
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Excitation error
  rng->doubleValue = 0.85;
  qubit->reset();
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_TRUE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Relaxation error
  rng->doubleValue = 0.95;
  qubit->reset();
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_TRUE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);
}

TEST_F(ETQubitMemoryErrorTest, apply_memory_error_X_error) {
  // Initial_condition << 0, 1, 0, 0, 0, 0, 0;

  // X error
  qubit->reset();
  qubit->has_x_error = true;
  rng->doubleValue = 0.55;
  qubit->applyMemoryError();
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Z error
  rng->doubleValue = 0.65;
  qubit->reset();
  qubit->has_x_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Y error
  rng->doubleValue = 0.75;
  qubit->reset();
  qubit->has_x_error = true;
  qubit->applyMemoryError();
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Excitation error
  rng->doubleValue = 0.85;
  qubit->reset();
  qubit->has_x_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_TRUE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Relaxation error
  rng->doubleValue = 0.95;
  qubit->reset();
  qubit->has_x_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_TRUE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);
}

TEST_F(ETQubitMemoryErrorTest, apply_memory_error_Z_error) {
  // Initial_condition << 0, 0, 1, 0, 0, 0, 0;
  // this means take 3rd row of MemoryTransitionMatrix

  // X error
  qubit->reset();
  qubit->has_x_error = true;
  rng->doubleValue = 0.55;
  qubit->applyMemoryError();
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Z error
  rng->doubleValue = 0.65;
  qubit->reset();
  qubit->has_x_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Y error
  rng->doubleValue = 0.75;
  qubit->reset();
  qubit->has_x_error = true;
  qubit->applyMemoryError();
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Excitation error
  rng->doubleValue = 0.85;
  qubit->reset();
  qubit->has_x_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_TRUE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Relaxation error
  rng->doubleValue = 0.95;
  qubit->reset();
  qubit->has_x_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_TRUE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);
}

TEST_F(ETQubitMemoryErrorTest, apply_memory_error_Y_error) {
  // Initial_condition << 0, 0, 0, 1, 0, 0, 0;
  // this means take 4th row of MemoryTransitionMatrix

  // X error
  qubit->reset();
  qubit->has_x_error = true;
  qubit->has_z_error = true;
  rng->doubleValue = 0.15;
  qubit->applyMemoryError();
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Z error
  rng->doubleValue = 0.25;
  qubit->reset();
  qubit->has_x_error = true;
  qubit->has_z_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Y error
  rng->doubleValue = 0.5;
  qubit->reset();
  qubit->has_x_error = true;
  qubit->has_z_error = true;
  qubit->applyMemoryError();
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Excitation error
  rng->doubleValue = 0.85;
  qubit->reset();
  qubit->has_x_error = true;
  qubit->has_z_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_TRUE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Relaxation error
  rng->doubleValue = 0.95;
  qubit->reset();
  qubit->has_x_error = true;
  qubit->has_z_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_TRUE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);
}

TEST_F(ETQubitMemoryErrorTest, apply_memory_error_excitation_error) {
  // Initial_condition << 0, 0, 0, 0, 1, 0, 0;
  // this means take 5th row of MemoryTransitionMatrix

  // X error
  qubit->reset();
  qubit->has_excitation_error = true;
  rng->doubleValue = 0.15;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_TRUE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Z error
  rng->doubleValue = 0.25;
  qubit->reset();
  qubit->has_excitation_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_TRUE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Y error
  rng->doubleValue = 0.5;
  qubit->reset();
  qubit->has_excitation_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_TRUE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Excitation error
  rng->doubleValue = 0.85;
  qubit->reset();
  qubit->has_excitation_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_TRUE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Relaxation error
  rng->doubleValue = 0.95;
  qubit->reset();
  qubit->has_excitation_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_TRUE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);
}

TEST_F(ETQubitMemoryErrorTest, apply_memory_error_relaxation_error) {
  // Initial_condition << 0, 0, 0, 0, 0, 1, 0;
  // this means take 6th row of MemoryTransitionMatrix

  // Excitation error
  rng->doubleValue = 0.05;
  qubit->reset();
  qubit->has_relaxation_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_TRUE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Relaxation error
  rng->doubleValue = 0.95;
  qubit->reset();
  qubit->has_relaxation_error = true;
  qubit->applyMemoryError();
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_TRUE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);
}

}  // namespace

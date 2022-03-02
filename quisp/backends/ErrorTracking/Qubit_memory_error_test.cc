#include <backends/Backends.h>
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <stdexcept>
#include <unsupported/Eigen/MatrixFunctions>
#include "Backend.h"
#include "Qubit.h"

using QubitId = int;

template class ::quisp::backends::error_tracking::ErrorTrackingQubit<QubitId>;
template class ::quisp::backends::error_tracking::ErrorTrackingBackend<QubitId>;

namespace {
using ErrorTrackingQubit = ::quisp::backends::ErrorTrackingQubit<QubitId>;
using ErrorTrackingBackend = ::quisp::backends::ErrorTrackingBackend<QubitId>;

class TestRNG : public quisp::backends::abstract::IRandomNumberGenerator {
 public:
  TestRNG() {}
  double doubleRandom() override { return doubleValue; }
  double doubleValue = 0.0;
};

class Qubit : public ErrorTrackingQubit {
 public:
  using ErrorTrackingQubit::applyMemoryError;
  using ErrorTrackingQubit::has_completely_mixed_error;
  using ErrorTrackingQubit::has_excitation_error;
  using ErrorTrackingQubit::has_relaxation_error;
  using ErrorTrackingQubit::has_x_error;
  using ErrorTrackingQubit::has_z_error;
  using ErrorTrackingQubit::setMemoryErrorRates;
  using ErrorTrackingQubit::updated_time;

  Qubit(QubitId id, ErrorTrackingBackend* const backend) : ErrorTrackingQubit(id, backend) {}
  void reset() {
    setFree();
    updated_time = SimTime(0);
    no_density_matrix_nullptr_entangled_partner_ok = true;
  }
  void fillParams() {
    // see networks/omnetpp.ini
    // setParDouble(this, "emission_success_probability", 0.5);

    // ceiled values should be:
    // No error= 0.1, X error = 0.6, Z error = 0.7, Y error = 0.8, Excitation = 0.9, Relaxation = 1.0
    double x_error_rate = .1;
    double y_error_rate = .1;
    double z_error_rate = .1;
    double energy_excitation_rate = .1;
    double energy_relaxation_rate = .1;
    double completely_mixed_rate = 0;
    setMemoryErrorRates(x_error_rate, y_error_rate, z_error_rate, energy_excitation_rate, energy_relaxation_rate, completely_mixed_rate);
    backend->setSimTime(SimTime(1, SIMTIME_US));

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

class Backend : public ErrorTrackingBackend {
 public:
  Backend(TestRNG* const rng) : ErrorTrackingBackend(rng) {}
  quisp::backends::IQubit<QubitId>* getQubit(QubitId id) override {
    auto qubit = qubits.find(id);

    if (qubit != qubits.cend()) {
      return qubit->second.get();
    }
    auto original_qubit = std::make_unique<Qubit>(id, this);
    auto* qubit_ptr = original_qubit.get();
    qubits.insert({id, std::move(original_qubit)});
    return qubit_ptr;
  }
};

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
    qubit->fillParams();
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

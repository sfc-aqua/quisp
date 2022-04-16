#include <backends/Backends.h>
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <Eigen/Eigen>
#include <memory>
#include <unsupported/Eigen/MatrixFunctions>
#include "backends/ErrorTracking/types.h"
#include "test.h"

namespace {
using namespace quisp_test::backends;
using Eigen::Matrix2cd;
using Eigen::Matrix4cd;
using Eigen::Vector4cd;
using quisp::backends::error_tracking::QuantumState;

class EtQubitTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    // to avoid the omnetpp::SimTime assertion
    SimTime::setScaleExp(-9);
    rng = new TestRNG();
    rng->double_value = .0;
    backend = std::make_unique<Backend>(std::unique_ptr<IRandomNumberGenerator>(rng), std::make_unique<ErrorTrackingConfiguration>());
    qubit = dynamic_cast<Qubit*>(backend->getQubit(0));
    partner_qubit = dynamic_cast<Qubit*>(backend->getQubit(1));
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
  Qubit* partner_qubit;
  std::unique_ptr<Backend> backend;
  TestRNG* rng;
};

TEST_F(EtQubitTest, getErrorMatrixTest) {
  Matrix2cd err;

  err = qubit->getErrorMatrix();
  EXPECT_EQ(Matrix2cd::Identity(), err);

  Matrix2cd Z(2, 2);
  Z << 1, 0, 0, -1;
  qubit->addErrorZ();
  err = qubit->getErrorMatrix();
  EXPECT_EQ(Z, err);
  qubit->setFree();

  Matrix2cd X(2, 2);
  X << 0, 1, 1, 0;
  qubit->addErrorX();
  err = qubit->getErrorMatrix();
  EXPECT_EQ(X, err);
  qubit->setFree();

  Matrix2cd Y(2, 2);
  Y << 0, Complex(0, -1), Complex(0, 1), 0;
  qubit->addErrorX();
  qubit->addErrorZ();
  err = qubit->getErrorMatrix();
  EXPECT_EQ(Y, err);
  qubit->setFree();
}

TEST_F(EtQubitTest, getQuantumState) {
  qubit->setEntangledPartner(partner_qubit);

  QuantumState state;

  state = qubit->getQuantumState();
  Vector4cd state_vector(4);
  state_vector << 1 / sqrt(2), 0, 0, 1 / sqrt(2);
  Matrix4cd dm(4, 4);
  dm = state_vector * state_vector.adjoint();
  EXPECT_EQ(dm, state.state_in_density_matrix);
  EXPECT_EQ(state_vector, state.state_in_ket);

  qubit->addErrorX();
  state = qubit->getQuantumState();
  state_vector << 0, 1 / sqrt(2), 1 / sqrt(2), 0;
  dm = state_vector * state_vector.adjoint();
  EXPECT_EQ(dm, state.state_in_density_matrix);
  EXPECT_EQ(state_vector, state.state_in_ket);
  qubit->addErrorX();

  partner_qubit->addErrorX();
  state = qubit->getQuantumState();
  state_vector << 0, 1 / sqrt(2), 1 / sqrt(2), 0;
  dm = state_vector * state_vector.adjoint();
  EXPECT_EQ(dm, state.state_in_density_matrix);
  EXPECT_EQ(state_vector, state.state_in_ket);
  partner_qubit->addErrorX();

  qubit->addErrorZ();
  state = qubit->getQuantumState();
  state_vector << 1 / sqrt(2), 0, 0, -1 / sqrt(2);
  dm = state_vector * state_vector.adjoint();
  EXPECT_EQ(dm, state.state_in_density_matrix);
  EXPECT_EQ(state_vector, state.state_in_ket);
}

TEST_F(EtQubitTest, setFreeUpdatesTime) {
  qubit->setFree();
  EXPECT_EQ(qubit->updated_time, backend->getSimTime());
  auto last_updated_at = qubit->updated_time;
  backend->setSimTime(10);
  EXPECT_EQ(qubit->updated_time, last_updated_at);
  qubit->setFree();
  EXPECT_EQ(qubit->updated_time, backend->getSimTime());
}

}  // namespace

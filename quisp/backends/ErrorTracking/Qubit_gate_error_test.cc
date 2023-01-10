#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <stdexcept>
#include <unsupported/Eigen/MatrixFunctions>
#include "test.h"

namespace {

using namespace quisp_test::backends::error_tracking;

class EtQubitGateErrorTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    // to avoid the omnetpp::SimTime assertion
    SimTime::setScaleExp(-9);
    rng = new TestRNG();
    rng->double_value = .0;
    backend = std::make_unique<Backend>(std::unique_ptr<IRandomNumberGenerator>(rng), std::make_unique<ErrorTrackingConfiguration>());
    qubit = dynamic_cast<Qubit*>(backend->getQubit(0));
    if (qubit == nullptr) throw std::runtime_error("Qubit is nullptr");
    qubit2 = dynamic_cast<Qubit*>(backend->getQubit(1));
    if (qubit2 == nullptr) throw std::runtime_error("Qubit is nullptr");
    backend->setSimTime(SimTime(1, SIMTIME_US));
    fillParams(qubit);
    fillParams(qubit2);
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

    // // No error= 0.4, X error = 0.6, Z error = 0.8, Y error = 1.0
    double h_gate_error_rate = 0.6;
    double h_gate_x_error_ratio = 1.0;
    double h_gate_z_error_ratio = 1.0;
    double h_gate_y_error_ratio = 1.0;
    qubit->gate_err_h.setParams(h_gate_x_error_ratio, h_gate_y_error_ratio, h_gate_z_error_ratio, h_gate_error_rate);

    double x_gate_error_rate = 0.6;
    double x_gate_x_error_ratio = 1.0;
    double x_gate_z_error_ratio = 1.0;
    double x_gate_y_error_ratio = 1.0;
    qubit->gate_err_x.setParams(x_gate_x_error_ratio, x_gate_y_error_ratio, x_gate_z_error_ratio, x_gate_error_rate);

    double z_gate_error_rate = 0.6;
    double z_gate_x_error_ratio = 1.0;
    double z_gate_z_error_ratio = 1.0;
    double z_gate_y_error_ratio = 1.0;
    qubit->gate_err_z.setParams(z_gate_x_error_ratio, z_gate_y_error_ratio, z_gate_z_error_ratio, z_gate_error_rate);

    // clean = 0.1,
    // IX = 0.2, XI = 0.3, XX = 0.4,
    // IZ = 0.5, ZI = 0.6, ZZ = 0.7,
    // IY = 0.8, IY = 0.9, YY = 1.0

    double cnot_gate_error_rate = 0.9;
    double cnot_gate_ix_error_ratio = 1;
    double cnot_gate_xi_error_ratio = 1;
    double cnot_gate_xx_error_ratio = 1;
    double cnot_gate_iz_error_ratio = 1;
    double cnot_gate_zi_error_ratio = 1;
    double cnot_gate_zz_error_ratio = 1;
    double cnot_gate_iy_error_ratio = 1;
    double cnot_gate_yi_error_ratio = 1;
    double cnot_gate_yy_error_ratio = 1;
    qubit->gate_err_cnot.setParams(cnot_gate_error_rate, cnot_gate_ix_error_ratio, cnot_gate_xi_error_ratio, cnot_gate_xx_error_ratio, cnot_gate_iz_error_ratio,
                                   cnot_gate_iz_error_ratio, cnot_gate_zz_error_ratio, cnot_gate_iy_error_ratio, cnot_gate_yi_error_ratio, cnot_gate_yy_error_ratio);
  }
  Qubit* qubit;
  Qubit* qubit2;
  std::unique_ptr<Backend> backend;
  TestRNG* rng;
};

TEST_F(EtQubitGateErrorTest, SetSingleQubitGateErrorCeilings) {
  double x_gate_error_rate = 0.1;
  double x_gate_x_error_ratio = 1;
  double x_gate_z_error_ratio = 2;
  double x_gate_y_error_ratio = 3;
  qubit->gate_err_x.setParams(x_gate_x_error_ratio, x_gate_y_error_ratio, x_gate_z_error_ratio, x_gate_error_rate);
  auto& error_model = qubit->gate_err_x;
  EXPECT_FALSE(std::isnan(error_model.x_error_rate));
  EXPECT_FALSE(std::isnan(error_model.y_error_rate));
  EXPECT_FALSE(std::isnan(error_model.z_error_rate));
  EXPECT_FALSE(std::isnan(error_model.pauli_error_rate));
  EXPECT_FALSE(std::isnan(error_model.no_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.x_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.z_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.y_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.x_error_rate));
  EXPECT_FALSE(std::isinf(error_model.y_error_rate));
  EXPECT_FALSE(std::isinf(error_model.z_error_rate));
  EXPECT_FALSE(std::isinf(error_model.pauli_error_rate));
  EXPECT_FALSE(std::isinf(error_model.no_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.x_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.z_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.y_error_ceil));
  EXPECT_DOUBLE_EQ(error_model.pauli_error_rate, 0.1);
  EXPECT_DOUBLE_EQ(error_model.x_error_rate, 0.1 * 1 / 6);
  EXPECT_DOUBLE_EQ(error_model.z_error_rate, 0.2 * 1 / 6);
  EXPECT_DOUBLE_EQ(error_model.y_error_rate, 0.3 * 1 / 6);
}

TEST_F(EtQubitGateErrorTest, SetSingleQubitGateErrorCeilings_div_by_zero) {
  double x_gate_error_rate = 0.1;
  double x_gate_x_error_ratio = 0;
  double x_gate_z_error_ratio = 0;
  double x_gate_y_error_ratio = 0;
  qubit->gate_err_x.setParams(x_gate_x_error_ratio, x_gate_y_error_ratio, x_gate_z_error_ratio, x_gate_error_rate);
  auto& error_model = qubit->gate_err_x;
  EXPECT_FALSE(std::isnan(error_model.x_error_rate));
  EXPECT_FALSE(std::isnan(error_model.y_error_rate));
  EXPECT_FALSE(std::isnan(error_model.z_error_rate));
  EXPECT_FALSE(std::isnan(error_model.pauli_error_rate));
  EXPECT_FALSE(std::isnan(error_model.no_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.x_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.z_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.y_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.x_error_rate));
  EXPECT_FALSE(std::isinf(error_model.y_error_rate));
  EXPECT_FALSE(std::isinf(error_model.z_error_rate));
  EXPECT_FALSE(std::isinf(error_model.pauli_error_rate));
  EXPECT_FALSE(std::isinf(error_model.no_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.x_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.z_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.y_error_ceil));
  EXPECT_DOUBLE_EQ(error_model.pauli_error_rate, 0.1);
  EXPECT_DOUBLE_EQ(error_model.x_error_rate, 0.1 * 1 / 3);
  EXPECT_DOUBLE_EQ(error_model.z_error_rate, 0.1 * 1 / 3);
  EXPECT_DOUBLE_EQ(error_model.y_error_rate, 0.1 * 1 / 3);
}

TEST_F(EtQubitGateErrorTest, SetTwoQubitGateErrorCeilings) {
  double cnot_gate_error_rate = 0.1;
  double cnot_gate_ix_error_ratio = 1;
  double cnot_gate_xi_error_ratio = 1;
  double cnot_gate_xx_error_ratio = 1;
  double cnot_gate_iz_error_ratio = 1;
  double cnot_gate_zi_error_ratio = 1;
  double cnot_gate_zz_error_ratio = 1;
  double cnot_gate_iy_error_ratio = 1;
  double cnot_gate_yi_error_ratio = 1;
  double cnot_gate_yy_error_ratio = 1;
  qubit->gate_err_cnot.setParams(cnot_gate_error_rate, cnot_gate_ix_error_ratio, cnot_gate_xi_error_ratio, cnot_gate_xx_error_ratio, cnot_gate_iz_error_ratio,
                                 cnot_gate_iz_error_ratio, cnot_gate_zz_error_ratio, cnot_gate_iy_error_ratio, cnot_gate_yi_error_ratio, cnot_gate_yy_error_ratio);
  auto const& error_model = qubit->gate_err_cnot;
  EXPECT_FALSE(std::isnan(error_model.ix_error_rate));
  EXPECT_FALSE(std::isnan(error_model.xi_error_rate));
  EXPECT_FALSE(std::isnan(error_model.xx_error_rate));
  EXPECT_FALSE(std::isnan(error_model.iz_error_rate));
  EXPECT_FALSE(std::isnan(error_model.zi_error_rate));
  EXPECT_FALSE(std::isnan(error_model.zz_error_rate));
  EXPECT_FALSE(std::isnan(error_model.iy_error_rate));
  EXPECT_FALSE(std::isnan(error_model.yi_error_rate));
  EXPECT_FALSE(std::isnan(error_model.yy_error_rate));
  EXPECT_FALSE(std::isnan(error_model.pauli_error_rate));
  EXPECT_FALSE(std::isnan(error_model.no_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.xi_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.ix_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.xx_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.zi_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.iz_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.zz_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.yi_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.iy_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.yy_error_ceil));

  EXPECT_FALSE(std::isinf(error_model.xi_error_rate));
  EXPECT_FALSE(std::isinf(error_model.ix_error_rate));
  EXPECT_FALSE(std::isinf(error_model.xx_error_rate));
  EXPECT_FALSE(std::isinf(error_model.zi_error_rate));
  EXPECT_FALSE(std::isinf(error_model.iz_error_rate));
  EXPECT_FALSE(std::isinf(error_model.zz_error_rate));
  EXPECT_FALSE(std::isinf(error_model.yi_error_rate));
  EXPECT_FALSE(std::isinf(error_model.iy_error_rate));
  EXPECT_FALSE(std::isinf(error_model.yy_error_rate));
  EXPECT_FALSE(std::isinf(error_model.pauli_error_rate));
  EXPECT_FALSE(std::isinf(error_model.no_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.xi_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.ix_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.xx_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.zi_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.iz_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.zz_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.yi_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.iy_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.yy_error_ceil));
  EXPECT_DOUBLE_EQ(error_model.pauli_error_rate, 0.1);
  EXPECT_DOUBLE_EQ(error_model.xi_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.ix_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.xx_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.zi_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.iz_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.zz_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.yi_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.iy_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.yy_error_rate, 0.1 * 1 / 9);
}

TEST_F(EtQubitGateErrorTest, SetTwoQubitGateErrorCeilings_div_by_zero) {
  double cnot_gate_error_rate = 0.1;
  double cnot_gate_ix_error_ratio = 0;
  double cnot_gate_xi_error_ratio = 0;
  double cnot_gate_xx_error_ratio = 0;
  double cnot_gate_iz_error_ratio = 0;
  double cnot_gate_zi_error_ratio = 0;
  double cnot_gate_zz_error_ratio = 0;
  double cnot_gate_iy_error_ratio = 0;
  double cnot_gate_yi_error_ratio = 0;
  double cnot_gate_yy_error_ratio = 0;
  qubit->gate_err_cnot.setParams(cnot_gate_error_rate, cnot_gate_ix_error_ratio, cnot_gate_xi_error_ratio, cnot_gate_xx_error_ratio, cnot_gate_iz_error_ratio,
                                 cnot_gate_iz_error_ratio, cnot_gate_zz_error_ratio, cnot_gate_iy_error_ratio, cnot_gate_yi_error_ratio, cnot_gate_yy_error_ratio);
  auto const& error_model = qubit->gate_err_cnot;
  EXPECT_FALSE(std::isnan(error_model.ix_error_rate));
  EXPECT_FALSE(std::isnan(error_model.xi_error_rate));
  EXPECT_FALSE(std::isnan(error_model.xx_error_rate));
  EXPECT_FALSE(std::isnan(error_model.iz_error_rate));
  EXPECT_FALSE(std::isnan(error_model.zi_error_rate));
  EXPECT_FALSE(std::isnan(error_model.zz_error_rate));
  EXPECT_FALSE(std::isnan(error_model.iy_error_rate));
  EXPECT_FALSE(std::isnan(error_model.yi_error_rate));
  EXPECT_FALSE(std::isnan(error_model.yy_error_rate));
  EXPECT_FALSE(std::isnan(error_model.pauli_error_rate));
  EXPECT_FALSE(std::isnan(error_model.no_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.xi_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.ix_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.xx_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.zi_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.iz_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.zz_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.yi_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.iy_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.yy_error_ceil));

  EXPECT_FALSE(std::isinf(error_model.xi_error_rate));
  EXPECT_FALSE(std::isinf(error_model.ix_error_rate));
  EXPECT_FALSE(std::isinf(error_model.xx_error_rate));
  EXPECT_FALSE(std::isinf(error_model.zi_error_rate));
  EXPECT_FALSE(std::isinf(error_model.iz_error_rate));
  EXPECT_FALSE(std::isinf(error_model.zz_error_rate));
  EXPECT_FALSE(std::isinf(error_model.yi_error_rate));
  EXPECT_FALSE(std::isinf(error_model.iy_error_rate));
  EXPECT_FALSE(std::isinf(error_model.yy_error_rate));
  EXPECT_FALSE(std::isinf(error_model.pauli_error_rate));
  EXPECT_FALSE(std::isinf(error_model.no_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.xi_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.ix_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.xx_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.zi_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.iz_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.zz_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.yi_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.iy_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.yy_error_ceil));
  EXPECT_DOUBLE_EQ(error_model.pauli_error_rate, 0.1);
  EXPECT_DOUBLE_EQ(error_model.xi_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.ix_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.xx_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.zi_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.iz_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.zz_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.yi_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.iy_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.yy_error_rate, 0.1 * 1 / 9);
}

TEST_F(EtQubitGateErrorTest, do_nothing_single_qubit_gate) {
  double x_gate_error_rate = 0.0;
  qubit->reset();
  qubit->has_x_error = true;
  qubit->has_z_error = true;
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);

  qubit->applySingleQubitGateError(qubit->gate_err_x);

  EXPECT_EQ(qubit->updated_time, SimTime(0, SIMTIME_US));
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_excitation_error);
}

TEST_F(EtQubitGateErrorTest, do_nothing_two_qubit_gate) {
  double cnot_gate_error_rate = 0.0;
  qubit->reset();
  qubit2->reset();
  qubit->has_x_error = true;
  qubit->has_z_error = true;
  qubit2->has_x_error = true;
  qubit2->has_z_error = true;
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_TRUE(qubit2->has_x_error);
  EXPECT_TRUE(qubit2->has_z_error);
  EXPECT_FALSE(qubit2->has_relaxation_error);
  EXPECT_FALSE(qubit2->has_excitation_error);

  qubit->applyTwoQubitGateError(qubit->gate_err_cnot, qubit2);

  EXPECT_EQ(qubit->updated_time, SimTime(0, SIMTIME_US));
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_TRUE(qubit2->has_x_error);
  EXPECT_TRUE(qubit2->has_z_error);
  EXPECT_FALSE(qubit2->has_relaxation_error);
  EXPECT_FALSE(qubit2->has_excitation_error);
}

TEST_F(EtQubitGateErrorTest, apply_single_qubit_gate_error) {
  backend->setSimTime(SimTime(1, SIMTIME_US));
  // No error
  qubit->reset();
  rng->double_value = 0.35;
  qubit->applySingleQubitGateError(qubit->gate_err_x);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // X error
  qubit->reset();
  rng->double_value = 0.45;
  qubit->applySingleQubitGateError(qubit->gate_err_x);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Z error
  qubit->reset();
  rng->double_value = 0.65;
  qubit->applySingleQubitGateError(qubit->gate_err_x);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Y error
  qubit->reset();
  rng->double_value = 0.85;
  qubit->applySingleQubitGateError(qubit->gate_err_x);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);
}

TEST_F(EtQubitGateErrorTest, apply_two_qubit_gate_error) {
  backend->setSimTime(SimTime(1, SIMTIME_US));

  // No error
  qubit->reset();
  qubit2->reset();
  rng->double_value = 0.05;
  qubit->applyTwoQubitGateError(qubit->gate_err_cnot, qubit2);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);
  EXPECT_FALSE(qubit2->has_x_error);
  EXPECT_FALSE(qubit2->has_z_error);
  EXPECT_FALSE(qubit2->has_excitation_error);
  EXPECT_FALSE(qubit2->has_relaxation_error);
  EXPECT_FALSE(qubit2->has_completely_mixed_error);

  // IX error
  qubit->reset();
  qubit2->reset();
  rng->double_value = 0.15;
  qubit->applyTwoQubitGateError(qubit->gate_err_cnot, qubit2);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);
  EXPECT_FALSE(qubit2->has_x_error);
  EXPECT_FALSE(qubit2->has_z_error);
  EXPECT_FALSE(qubit2->has_excitation_error);
  EXPECT_FALSE(qubit2->has_relaxation_error);
  EXPECT_FALSE(qubit2->has_completely_mixed_error);

  // XI error
  qubit->reset();
  qubit2->reset();
  rng->double_value = 0.25;
  qubit->applyTwoQubitGateError(qubit->gate_err_cnot, qubit2);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);
  EXPECT_TRUE(qubit2->has_x_error);
  EXPECT_FALSE(qubit2->has_z_error);
  EXPECT_FALSE(qubit2->has_excitation_error);
  EXPECT_FALSE(qubit2->has_relaxation_error);
  EXPECT_FALSE(qubit2->has_completely_mixed_error);

  // XX error
  qubit->reset();
  qubit2->reset();
  rng->double_value = 0.35;
  qubit->applyTwoQubitGateError(qubit->gate_err_cnot, qubit2);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);
  EXPECT_TRUE(qubit2->has_x_error);
  EXPECT_FALSE(qubit2->has_z_error);
  EXPECT_FALSE(qubit2->has_excitation_error);
  EXPECT_FALSE(qubit2->has_relaxation_error);
  EXPECT_FALSE(qubit2->has_completely_mixed_error);

  // IZ error
  qubit->reset();
  qubit2->reset();
  rng->double_value = 0.45;
  qubit->applyTwoQubitGateError(qubit->gate_err_cnot, qubit2);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);
  EXPECT_FALSE(qubit2->has_x_error);
  EXPECT_FALSE(qubit2->has_z_error);
  EXPECT_FALSE(qubit2->has_excitation_error);
  EXPECT_FALSE(qubit2->has_relaxation_error);
  EXPECT_FALSE(qubit2->has_completely_mixed_error);

  // ZI error
  qubit->reset();
  qubit2->reset();
  rng->double_value = 0.55;
  qubit->applyTwoQubitGateError(qubit->gate_err_cnot, qubit2);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);
  EXPECT_FALSE(qubit2->has_x_error);
  EXPECT_TRUE(qubit2->has_z_error);
  EXPECT_FALSE(qubit2->has_excitation_error);
  EXPECT_FALSE(qubit2->has_relaxation_error);
  EXPECT_FALSE(qubit2->has_completely_mixed_error);

  // ZZ error
  qubit->reset();
  qubit2->reset();
  rng->double_value = 0.65;
  qubit->applyTwoQubitGateError(qubit->gate_err_cnot, qubit2);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);
  EXPECT_FALSE(qubit2->has_x_error);
  EXPECT_TRUE(qubit2->has_z_error);
  EXPECT_FALSE(qubit2->has_excitation_error);
  EXPECT_FALSE(qubit2->has_relaxation_error);
  EXPECT_FALSE(qubit2->has_completely_mixed_error);

  // IY error
  qubit->reset();
  qubit2->reset();
  rng->double_value = 0.75;
  qubit->applyTwoQubitGateError(qubit->gate_err_cnot, qubit2);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);
  EXPECT_FALSE(qubit2->has_x_error);
  EXPECT_FALSE(qubit2->has_z_error);
  EXPECT_FALSE(qubit2->has_excitation_error);
  EXPECT_FALSE(qubit2->has_relaxation_error);
  EXPECT_FALSE(qubit2->has_completely_mixed_error);

  // YI error
  qubit->reset();
  qubit2->reset();
  rng->double_value = 0.85;
  qubit->applyTwoQubitGateError(qubit->gate_err_cnot, qubit2);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);
  EXPECT_TRUE(qubit2->has_x_error);
  EXPECT_TRUE(qubit2->has_z_error);
  EXPECT_FALSE(qubit2->has_excitation_error);
  EXPECT_FALSE(qubit2->has_relaxation_error);
  EXPECT_FALSE(qubit2->has_completely_mixed_error);

  // YY error
  qubit->reset();
  qubit2->reset();
  rng->double_value = 0.95;
  qubit->applyTwoQubitGateError(qubit->gate_err_cnot, qubit2);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);
  EXPECT_TRUE(qubit2->has_x_error);
  EXPECT_TRUE(qubit2->has_z_error);
  EXPECT_FALSE(qubit2->has_excitation_error);
  EXPECT_FALSE(qubit2->has_relaxation_error);
  EXPECT_FALSE(qubit2->has_completely_mixed_error);
}
}  // namespace

#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <stdexcept>
#include <unsupported/Eigen/MatrixFunctions>
#include "test.h"

namespace {

using namespace quisp_test::backends;

class EtQubitGateErrorTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    // to avoid the omnetpp::SimTime assertion
    SimTime::setScaleExp(-9);
    rng = std::make_unique<TestRNG>();
    rng->doubleValue = .0;
    backend = std::make_unique<Backend>(rng.get());
    qubit = dynamic_cast<Qubit*>(backend->getQubit(new QubitId(0)));
    if (qubit == nullptr) throw std::runtime_error("Qubit is nullptr");
    qubit2 = dynamic_cast<Qubit*>(backend->getQubit(new QubitId(1)));
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
    double Hgate_error_rate = 0.6;
    double Hgate_X_error_ratio = 1.0;
    double Hgate_Z_error_ratio = 1.0;
    double Hgate_Y_error_ratio = 1.0;
    qubit->Hgate_error.setParams(Hgate_X_error_ratio, Hgate_Y_error_ratio, Hgate_Z_error_ratio, Hgate_error_rate);

    double Xgate_error_rate = 0.6;
    double Xgate_X_error_ratio = 1.0;
    double Xgate_Z_error_ratio = 1.0;
    double Xgate_Y_error_ratio = 1.0;
    qubit->Xgate_error.setParams(Xgate_X_error_ratio, Xgate_Y_error_ratio, Xgate_Z_error_ratio, Xgate_error_rate);

    double Zgate_error_rate = 0.6;
    double Zgate_X_error_ratio = 1.0;
    double Zgate_Z_error_ratio = 1.0;
    double Zgate_Y_error_ratio = 1.0;
    qubit->Zgate_error.setParams(Zgate_X_error_ratio, Zgate_Y_error_ratio, Zgate_Z_error_ratio, Zgate_error_rate);

    // clean = 0.1,
    // IX = 0.2, XI = 0.3, XX = 0.4,
    // IZ = 0.5, ZI = 0.6, ZZ = 0.7,
    // IY = 0.8, IY = 0.9, YY = 1.0

    double CNOTgate_error_rate = 0.9;
    double CNOTgate_IX_error_ratio = 1;
    double CNOTgate_XI_error_ratio = 1;
    double CNOTgate_XX_error_ratio = 1;
    double CNOTgate_IZ_error_ratio = 1;
    double CNOTgate_ZI_error_ratio = 1;
    double CNOTgate_ZZ_error_ratio = 1;
    double CNOTgate_IY_error_ratio = 1;
    double CNOTgate_YI_error_ratio = 1;
    double CNOTgate_YY_error_ratio = 1;
    qubit->CNOTgate_error.setParams(CNOTgate_error_rate, CNOTgate_IX_error_ratio, CNOTgate_XI_error_ratio, CNOTgate_XX_error_ratio, CNOTgate_IZ_error_ratio,
                                    CNOTgate_IZ_error_ratio, CNOTgate_ZZ_error_ratio, CNOTgate_IY_error_ratio, CNOTgate_YI_error_ratio, CNOTgate_YY_error_ratio);
  }
  Qubit* qubit;
  Qubit* qubit2;
  std::unique_ptr<Backend> backend;
  std::unique_ptr<TestRNG> rng;
};

TEST_F(EtQubitGateErrorTest, SetSingleQubitGateErrorCeilings) {
  double Xgate_error_rate = 0.1;
  double Xgate_X_error_ratio = 1;
  double Xgate_Z_error_ratio = 2;
  double Xgate_Y_error_ratio = 3;
  qubit->Xgate_error.setParams(Xgate_X_error_ratio, Xgate_Y_error_ratio, Xgate_Z_error_ratio, Xgate_error_rate);
  auto& error_model = qubit->Xgate_error;
  EXPECT_FALSE(std::isnan(error_model.X_error_rate));
  EXPECT_FALSE(std::isnan(error_model.Y_error_rate));
  EXPECT_FALSE(std::isnan(error_model.Z_error_rate));
  EXPECT_FALSE(std::isnan(error_model.pauli_error_rate));
  EXPECT_FALSE(std::isnan(error_model.No_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.X_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.Z_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.Y_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.X_error_rate));
  EXPECT_FALSE(std::isinf(error_model.Y_error_rate));
  EXPECT_FALSE(std::isinf(error_model.Z_error_rate));
  EXPECT_FALSE(std::isinf(error_model.pauli_error_rate));
  EXPECT_FALSE(std::isinf(error_model.No_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.X_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.Z_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.Y_error_ceil));
  EXPECT_DOUBLE_EQ(error_model.pauli_error_rate, 0.1);
  EXPECT_DOUBLE_EQ(error_model.X_error_rate, 0.1 * 1 / 6);
  EXPECT_DOUBLE_EQ(error_model.Z_error_rate, 0.2 * 1 / 6);
  EXPECT_DOUBLE_EQ(error_model.Y_error_rate, 0.3 * 1 / 6);
}

TEST_F(EtQubitGateErrorTest, SetSingleQubitGateErrorCeilings_div_by_zero) {
  double Xgate_error_rate = 0.1;
  double Xgate_X_error_ratio = 0;
  double Xgate_Z_error_ratio = 0;
  double Xgate_Y_error_ratio = 0;
  qubit->Xgate_error.setParams(Xgate_X_error_ratio, Xgate_Y_error_ratio, Xgate_Z_error_ratio, Xgate_error_rate);
  auto& error_model = qubit->Xgate_error;
  EXPECT_FALSE(std::isnan(error_model.X_error_rate));
  EXPECT_FALSE(std::isnan(error_model.Y_error_rate));
  EXPECT_FALSE(std::isnan(error_model.Z_error_rate));
  EXPECT_FALSE(std::isnan(error_model.pauli_error_rate));
  EXPECT_FALSE(std::isnan(error_model.No_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.X_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.Z_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.Y_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.X_error_rate));
  EXPECT_FALSE(std::isinf(error_model.Y_error_rate));
  EXPECT_FALSE(std::isinf(error_model.Z_error_rate));
  EXPECT_FALSE(std::isinf(error_model.pauli_error_rate));
  EXPECT_FALSE(std::isinf(error_model.No_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.X_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.Z_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.Y_error_ceil));
  EXPECT_DOUBLE_EQ(error_model.pauli_error_rate, 0.1);
  EXPECT_DOUBLE_EQ(error_model.X_error_rate, 0.1 * 1 / 3);
  EXPECT_DOUBLE_EQ(error_model.Z_error_rate, 0.1 * 1 / 3);
  EXPECT_DOUBLE_EQ(error_model.Y_error_rate, 0.1 * 1 / 3);
}

TEST_F(EtQubitGateErrorTest, SetTwoQubitGateErrorCeilings) {
  double CNOTgate_error_rate = 0.1;
  double CNOTgate_IX_error_ratio = 1;
  double CNOTgate_XI_error_ratio = 1;
  double CNOTgate_XX_error_ratio = 1;
  double CNOTgate_IZ_error_ratio = 1;
  double CNOTgate_ZI_error_ratio = 1;
  double CNOTgate_ZZ_error_ratio = 1;
  double CNOTgate_IY_error_ratio = 1;
  double CNOTgate_YI_error_ratio = 1;
  double CNOTgate_YY_error_ratio = 1;
  qubit->CNOTgate_error.setParams(CNOTgate_error_rate, CNOTgate_IX_error_ratio, CNOTgate_XI_error_ratio, CNOTgate_XX_error_ratio, CNOTgate_IZ_error_ratio, CNOTgate_IZ_error_ratio,
                                  CNOTgate_ZZ_error_ratio, CNOTgate_IY_error_ratio, CNOTgate_YI_error_ratio, CNOTgate_YY_error_ratio);
  auto const& error_model = qubit->CNOTgate_error;
  EXPECT_FALSE(std::isnan(error_model.IX_error_rate));
  EXPECT_FALSE(std::isnan(error_model.XI_error_rate));
  EXPECT_FALSE(std::isnan(error_model.XX_error_rate));
  EXPECT_FALSE(std::isnan(error_model.IZ_error_rate));
  EXPECT_FALSE(std::isnan(error_model.ZI_error_rate));
  EXPECT_FALSE(std::isnan(error_model.ZZ_error_rate));
  EXPECT_FALSE(std::isnan(error_model.IY_error_rate));
  EXPECT_FALSE(std::isnan(error_model.YI_error_rate));
  EXPECT_FALSE(std::isnan(error_model.YY_error_rate));
  EXPECT_FALSE(std::isnan(error_model.pauli_error_rate));
  EXPECT_FALSE(std::isnan(error_model.No_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.XI_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.IX_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.XX_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.ZI_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.IZ_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.ZZ_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.YI_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.IY_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.YY_error_ceil));

  EXPECT_FALSE(std::isinf(error_model.XI_error_rate));
  EXPECT_FALSE(std::isinf(error_model.IX_error_rate));
  EXPECT_FALSE(std::isinf(error_model.XX_error_rate));
  EXPECT_FALSE(std::isinf(error_model.ZI_error_rate));
  EXPECT_FALSE(std::isinf(error_model.IZ_error_rate));
  EXPECT_FALSE(std::isinf(error_model.ZZ_error_rate));
  EXPECT_FALSE(std::isinf(error_model.YI_error_rate));
  EXPECT_FALSE(std::isinf(error_model.IY_error_rate));
  EXPECT_FALSE(std::isinf(error_model.YY_error_rate));
  EXPECT_FALSE(std::isinf(error_model.pauli_error_rate));
  EXPECT_FALSE(std::isinf(error_model.No_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.XI_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.IX_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.XX_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.ZI_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.IZ_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.ZZ_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.YI_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.IY_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.YY_error_ceil));
  EXPECT_DOUBLE_EQ(error_model.pauli_error_rate, 0.1);
  EXPECT_DOUBLE_EQ(error_model.XI_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.IX_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.XX_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.ZI_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.IZ_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.ZZ_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.YI_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.IY_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.YY_error_rate, 0.1 * 1 / 9);
}

TEST_F(EtQubitGateErrorTest, SetTwoQubitGateErrorCeilings_div_by_zero) {
  double CNOTgate_error_rate = 0.1;
  double CNOTgate_IX_error_ratio = 0;
  double CNOTgate_XI_error_ratio = 0;
  double CNOTgate_XX_error_ratio = 0;
  double CNOTgate_IZ_error_ratio = 0;
  double CNOTgate_ZI_error_ratio = 0;
  double CNOTgate_ZZ_error_ratio = 0;
  double CNOTgate_IY_error_ratio = 0;
  double CNOTgate_YI_error_ratio = 0;
  double CNOTgate_YY_error_ratio = 0;
  qubit->CNOTgate_error.setParams(CNOTgate_error_rate, CNOTgate_IX_error_ratio, CNOTgate_XI_error_ratio, CNOTgate_XX_error_ratio, CNOTgate_IZ_error_ratio, CNOTgate_IZ_error_ratio,
                                  CNOTgate_ZZ_error_ratio, CNOTgate_IY_error_ratio, CNOTgate_YI_error_ratio, CNOTgate_YY_error_ratio);
  auto const& error_model = qubit->CNOTgate_error;
  EXPECT_FALSE(std::isnan(error_model.IX_error_rate));
  EXPECT_FALSE(std::isnan(error_model.XI_error_rate));
  EXPECT_FALSE(std::isnan(error_model.XX_error_rate));
  EXPECT_FALSE(std::isnan(error_model.IZ_error_rate));
  EXPECT_FALSE(std::isnan(error_model.ZI_error_rate));
  EXPECT_FALSE(std::isnan(error_model.ZZ_error_rate));
  EXPECT_FALSE(std::isnan(error_model.IY_error_rate));
  EXPECT_FALSE(std::isnan(error_model.YI_error_rate));
  EXPECT_FALSE(std::isnan(error_model.YY_error_rate));
  EXPECT_FALSE(std::isnan(error_model.pauli_error_rate));
  EXPECT_FALSE(std::isnan(error_model.No_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.XI_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.IX_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.XX_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.ZI_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.IZ_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.ZZ_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.YI_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.IY_error_ceil));
  EXPECT_FALSE(std::isnan(error_model.YY_error_ceil));

  EXPECT_FALSE(std::isinf(error_model.XI_error_rate));
  EXPECT_FALSE(std::isinf(error_model.IX_error_rate));
  EXPECT_FALSE(std::isinf(error_model.XX_error_rate));
  EXPECT_FALSE(std::isinf(error_model.ZI_error_rate));
  EXPECT_FALSE(std::isinf(error_model.IZ_error_rate));
  EXPECT_FALSE(std::isinf(error_model.ZZ_error_rate));
  EXPECT_FALSE(std::isinf(error_model.YI_error_rate));
  EXPECT_FALSE(std::isinf(error_model.IY_error_rate));
  EXPECT_FALSE(std::isinf(error_model.YY_error_rate));
  EXPECT_FALSE(std::isinf(error_model.pauli_error_rate));
  EXPECT_FALSE(std::isinf(error_model.No_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.XI_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.IX_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.XX_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.ZI_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.IZ_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.ZZ_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.YI_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.IY_error_ceil));
  EXPECT_FALSE(std::isinf(error_model.YY_error_ceil));
  EXPECT_DOUBLE_EQ(error_model.pauli_error_rate, 0.1);
  EXPECT_DOUBLE_EQ(error_model.XI_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.IX_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.XX_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.ZI_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.IZ_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.ZZ_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.YI_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.IY_error_rate, 0.1 * 1 / 9);
  EXPECT_DOUBLE_EQ(error_model.YY_error_rate, 0.1 * 1 / 9);
}

TEST_F(EtQubitGateErrorTest, do_nothing_single_qubit_gate) {
  double Xgate_error_rate = 0.0;
  qubit->reset();
  qubit->has_x_error = true;
  qubit->has_z_error = true;
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);

  qubit->applySingleQubitGateError(qubit->Xgate_error);

  EXPECT_EQ(qubit->updated_time, SimTime(0, SIMTIME_US));
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_excitation_error);
}

TEST_F(EtQubitGateErrorTest, do_nothing_two_qubit_gate) {
  double CNOTgate_error_rate = 0.0;
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

  qubit->applyTwoQubitGateError(qubit->CNOTgate_error, qubit2);

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
  rng->doubleValue = 0.35;
  qubit->applySingleQubitGateError(qubit->Xgate_error);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // X error
  qubit->reset();
  rng->doubleValue = 0.45;
  qubit->applySingleQubitGateError(qubit->Xgate_error);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Z error
  qubit->reset();
  rng->doubleValue = 0.65;
  qubit->applySingleQubitGateError(qubit->Xgate_error);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(qubit->has_excitation_error);
  EXPECT_FALSE(qubit->has_relaxation_error);
  EXPECT_FALSE(qubit->has_completely_mixed_error);

  // Y error
  qubit->reset();
  rng->doubleValue = 0.85;
  qubit->applySingleQubitGateError(qubit->Xgate_error);
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
  rng->doubleValue = 0.05;
  qubit->applyTwoQubitGateError(qubit->CNOTgate_error, qubit2);
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
  rng->doubleValue = 0.15;
  qubit->applyTwoQubitGateError(qubit->CNOTgate_error, qubit2);
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
  rng->doubleValue = 0.25;
  qubit->applyTwoQubitGateError(qubit->CNOTgate_error, qubit2);
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
  rng->doubleValue = 0.35;
  qubit->applyTwoQubitGateError(qubit->CNOTgate_error, qubit2);
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
  rng->doubleValue = 0.45;
  qubit->applyTwoQubitGateError(qubit->CNOTgate_error, qubit2);
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
  rng->doubleValue = 0.55;
  qubit->applyTwoQubitGateError(qubit->CNOTgate_error, qubit2);
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
  rng->doubleValue = 0.65;
  qubit->applyTwoQubitGateError(qubit->CNOTgate_error, qubit2);
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
  rng->doubleValue = 0.75;
  qubit->applyTwoQubitGateError(qubit->CNOTgate_error, qubit2);
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
  rng->doubleValue = 0.85;
  qubit->applyTwoQubitGateError(qubit->CNOTgate_error, qubit2);
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
  rng->doubleValue = 0.95;
  qubit->applyTwoQubitGateError(qubit->CNOTgate_error, qubit2);
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

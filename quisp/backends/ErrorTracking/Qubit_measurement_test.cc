#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <stdexcept>
#include <unsupported/Eigen/MatrixFunctions>
#include "test.h"

namespace {
using namespace quisp_test::backends::error_tracking;

class EtQubitMeasurementTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    // to avoid the omnetpp::SimTime assertion
    SimTime::setScaleExp(-9);
    rng = new TestRNG();
    rng->double_value = .0;

    backend = std::make_unique<Backend>(std::unique_ptr<IRandomNumberGenerator>(rng), std::make_unique<ErrorTrackingConfiguration>());
    qubit = dynamic_cast<Qubit*>(backend->getQubit(0));
    another_qubit = dynamic_cast<Qubit*>(backend->getQubit(2));

    backend->setSimTime(SimTime(1, SIMTIME_US));
    fillParams(qubit);
    fillParams(another_qubit);
  }
  void reset() {
    qubit->reset();
    another_qubit->reset();
    qubit->entangled_partner = another_qubit;
    another_qubit->entangled_partner = qubit;
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
    backend->setSimTime(SimTime(1, SIMTIME_US));

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
                                   cnot_gate_zi_error_ratio, cnot_gate_zz_error_ratio, cnot_gate_iy_error_ratio, cnot_gate_yi_error_ratio, cnot_gate_yy_error_ratio);

    double x_measurement_error_rate = 1. / 2000;
    double y_measurement_error_rate = 1. / 2000;
    double z_measurement_error_rate = 1. / 2000;
    qubit->measurement_err.setParams(x_measurement_error_rate, y_measurement_error_rate, z_measurement_error_rate);
  }
  Qubit* qubit;
  Qubit* another_qubit;
  std::unique_ptr<Backend> backend;
  TestRNG* rng;
};

TEST_F(EtQubitMeasurementTest, SetMeasurementErrorRate) {
  double x_measurement_error_rate = 0.1;
  double y_measurement_error_rate = 0.2;
  double z_measurement_error_rate = 0.4;
  qubit->measurement_err.setParams(x_measurement_error_rate, y_measurement_error_rate, z_measurement_error_rate);
  auto& error_model = qubit->measurement_err;
  EXPECT_FALSE(std::isnan(error_model.x_error_rate));
  EXPECT_FALSE(std::isnan(error_model.y_error_rate));
  EXPECT_FALSE(std::isnan(error_model.z_error_rate));
  EXPECT_DOUBLE_EQ(error_model.x_error_rate, 0.1);
  EXPECT_DOUBLE_EQ(error_model.y_error_rate, 0.2);
  EXPECT_DOUBLE_EQ(error_model.z_error_rate, 0.4);
}

TEST_F(EtQubitMeasurementTest, CorrelationMeasureXwithoutError) {
  rng->double_value = 0.5;
  EXPECT_EQ(qubit->correlationMeasureX(), MeasureXResult::NO_Z_ERROR);
  rng->double_value = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureX(), MeasureXResult::HAS_Z_ERROR);
}

TEST_F(EtQubitMeasurementTest, CorrelationMeasureXwithError) {
  // X error
  qubit->addErrorX();
  rng->double_value = 0.5;
  EXPECT_EQ(qubit->correlationMeasureX(), MeasureXResult::NO_Z_ERROR);
  rng->double_value = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureX(), MeasureXResult::HAS_Z_ERROR);

  // Y error
  qubit->addErrorZ();
  rng->double_value = 0.5;
  EXPECT_EQ(qubit->correlationMeasureX(), MeasureXResult::HAS_Z_ERROR);
  rng->double_value = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureX(), MeasureXResult::NO_Z_ERROR);

  // Z error
  qubit->addErrorX();
  rng->double_value = 0.5;
  EXPECT_EQ(qubit->correlationMeasureX(), MeasureXResult::HAS_Z_ERROR);
  rng->double_value = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureX(), MeasureXResult::NO_Z_ERROR);
}

TEST_F(EtQubitMeasurementTest, CorrelationMeasureYwithoutError) {
  rng->double_value = 0.5;
  EXPECT_EQ(qubit->correlationMeasureY(), MeasureYResult::NO_XZ_ERROR);
  rng->double_value = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureY(), MeasureYResult::HAS_XZ_ERROR);
}

TEST_F(EtQubitMeasurementTest, CorrelationMeasureYwithError) {
  // X error
  qubit->addErrorX();
  rng->double_value = 0.5;
  EXPECT_EQ(qubit->correlationMeasureY(), MeasureYResult::HAS_XZ_ERROR);
  rng->double_value = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureY(), MeasureYResult::NO_XZ_ERROR);

  // Y error
  qubit->addErrorZ();
  rng->double_value = 0.5;
  EXPECT_EQ(qubit->correlationMeasureY(), MeasureYResult::NO_XZ_ERROR);
  rng->double_value = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureY(), MeasureYResult::HAS_XZ_ERROR);

  // Z error
  qubit->addErrorX();
  rng->double_value = 0.5;
  EXPECT_EQ(qubit->correlationMeasureY(), MeasureYResult::HAS_XZ_ERROR);
  rng->double_value = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureY(), MeasureYResult::NO_XZ_ERROR);
}

TEST_F(EtQubitMeasurementTest, CorrelationMeasureZwithoutError) {
  rng->double_value = 0.5;
  EXPECT_EQ(qubit->correlationMeasureZ(), MeasureZResult::NO_X_ERROR);
  rng->double_value = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureZ(), MeasureZResult::HAS_X_ERROR);
}

TEST_F(EtQubitMeasurementTest, CorrelationMeasureZwithError) {
  // X error
  qubit->addErrorX();
  rng->double_value = 0.5;
  EXPECT_EQ(qubit->correlationMeasureZ(), MeasureZResult::HAS_X_ERROR);
  rng->double_value = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureZ(), MeasureZResult::NO_X_ERROR);

  // Y error
  qubit->addErrorZ();
  rng->double_value = 0.5;
  EXPECT_EQ(qubit->correlationMeasureZ(), MeasureZResult::HAS_X_ERROR);
  rng->double_value = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureZ(), MeasureZResult::NO_X_ERROR);

  // Z error
  qubit->addErrorX();
  rng->double_value = 0.5;
  EXPECT_EQ(qubit->correlationMeasureZ(), MeasureZResult::NO_X_ERROR);
  rng->double_value = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureZ(), MeasureZResult::HAS_X_ERROR);
}

TEST_F(EtQubitMeasurementTest, localXMeasurementWithoutError) {
  qubit->entangled_partner = another_qubit;
  another_qubit->entangled_partner = qubit;
  ASSERT_NE(qubit->entangled_partner, nullptr);
  ASSERT_NE(another_qubit->entangled_partner, nullptr);

  reset();
  rng->double_value = 0.7;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::PLUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  reset();
  rng->double_value = 0.3;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::MINUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_TRUE(another_qubit->has_z_error);

  reset();
  qubit->addErrorZ();
  rng->double_value = 0.7;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::PLUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_TRUE(another_qubit->has_z_error);

  reset();
  qubit->addErrorZ();
  rng->double_value = 0.3;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::MINUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  reset();
  qubit->addErrorX();
  rng->double_value = 0.7;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::PLUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  reset();
  qubit->addErrorX();
  rng->double_value = 0.3;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::MINUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_TRUE(another_qubit->has_z_error);

  reset();
  qubit->addErrorZ();
  qubit->addErrorX();
  rng->double_value = 0.7;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::PLUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_TRUE(another_qubit->has_z_error);

  reset();
  qubit->addErrorZ();
  qubit->addErrorX();
  rng->double_value = 0.3;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::MINUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);
}

TEST_F(EtQubitMeasurementTest, localXMeasurementWithError) {
  qubit->measurement_err.x_error_rate = 0.99;
  reset();
  rng->double_value = 0.7;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::MINUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  reset();
  rng->double_value = 0.3;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::PLUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_TRUE(another_qubit->has_z_error);

  reset();
  qubit->addErrorZ();
  rng->double_value = 0.7;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::MINUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_TRUE(another_qubit->has_z_error);

  reset();
  qubit->addErrorZ();
  rng->double_value = 0.3;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::PLUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  reset();
  qubit->addErrorX();
  rng->double_value = 0.7;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::MINUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  reset();
  qubit->addErrorX();
  rng->double_value = 0.3;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::PLUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_TRUE(another_qubit->has_z_error);

  reset();
  qubit->addErrorZ();
  qubit->addErrorX();
  rng->double_value = 0.7;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::MINUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_TRUE(another_qubit->has_z_error);

  reset();
  qubit->addErrorZ();
  qubit->addErrorX();
  rng->double_value = 0.3;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::PLUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);
}

TEST_F(EtQubitMeasurementTest, localZMeasurementWithoutError) {
  reset();
  rng->double_value = 0.7;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::PLUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  reset();
  rng->double_value = 0.3;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::MINUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_TRUE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  reset();
  qubit->addErrorZ();
  rng->double_value = 0.7;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::PLUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  reset();
  qubit->addErrorZ();
  rng->double_value = 0.3;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::MINUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_TRUE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  reset();
  qubit->addErrorX();
  rng->double_value = 0.7;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::PLUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_TRUE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  reset();
  qubit->addErrorX();
  rng->double_value = 0.3;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::MINUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  reset();
  qubit->addErrorZ();
  qubit->addErrorX();
  rng->double_value = 0.7;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::PLUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_TRUE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  reset();
  qubit->addErrorZ();
  qubit->addErrorX();
  rng->double_value = 0.3;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::MINUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);
}

TEST_F(EtQubitMeasurementTest, localZMeasurementWithError) {
  qubit->measurement_err.z_error_rate = 0.99;

  reset();
  rng->double_value = 0.7;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::MINUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  reset();
  rng->double_value = 0.3;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::PLUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_TRUE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  reset();
  qubit->addErrorZ();
  rng->double_value = 0.7;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::MINUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  reset();
  qubit->addErrorZ();
  rng->double_value = 0.3;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::PLUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_TRUE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  reset();
  qubit->addErrorX();
  rng->double_value = 0.7;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::MINUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_TRUE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  reset();
  qubit->addErrorX();
  rng->double_value = 0.3;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::PLUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  reset();
  qubit->addErrorZ();
  qubit->addErrorX();
  rng->double_value = 0.7;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::MINUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_TRUE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  reset();
  qubit->addErrorZ();
  qubit->addErrorX();
  rng->double_value = 0.3;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::PLUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);
}

}  // end namespace

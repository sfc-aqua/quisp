#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <stdexcept>
#include <unsupported/Eigen/MatrixFunctions>
#include "backends/IRandomNumberGenerator.h"
#include "test.h"

namespace {
using namespace quisp_test::backends;

class EtQubitMeasurementTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    // to avoid the omnetpp::SimTime assertion
    SimTime::setScaleExp(-9);
    rng = new TestRNG();
    rng->doubleValue = .0;

    backend = std::make_unique<Backend>(std::unique_ptr<IRandomNumberGenerator>(rng));
    qubit = dynamic_cast<Qubit*>(backend->getQubit(0));
    qubit2 = dynamic_cast<Qubit*>(backend->getQubit(1));
    another_qubit = dynamic_cast<Qubit*>(backend->getQubit(2));

    backend->setSimTime(SimTime(1, SIMTIME_US));
    fillParams(qubit);
    fillParams(qubit2);
    fillParams(another_qubit);
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

    double X_measurement_error_rate = 1. / 2000;
    double Y_measurement_error_rate = 1. / 2000;
    double Z_measurement_error_rate = 1. / 2000;
    qubit->Measurement_error.setParams(X_measurement_error_rate, Y_measurement_error_rate, Z_measurement_error_rate);
  }
  Qubit* qubit;
  Qubit* qubit2;
  Qubit* another_qubit;
  std::unique_ptr<Backend> backend;
  TestRNG* rng;
};

TEST_F(EtQubitMeasurementTest, SetMeasurementErrorRate) {
  double X_measurement_error_rate = 0.1;
  double Y_measurement_error_rate = 0.2;
  double Z_measurement_error_rate = 0.4;
  qubit->Measurement_error.setParams(X_measurement_error_rate, Y_measurement_error_rate, Z_measurement_error_rate);
  auto& error_model = qubit->Measurement_error;
  EXPECT_FALSE(std::isnan(error_model.x_error_rate));
  EXPECT_FALSE(std::isnan(error_model.y_error_rate));
  EXPECT_FALSE(std::isnan(error_model.z_error_rate));
  EXPECT_DOUBLE_EQ(error_model.x_error_rate, 0.1);
  EXPECT_DOUBLE_EQ(error_model.y_error_rate, 0.2);
  EXPECT_DOUBLE_EQ(error_model.z_error_rate, 0.4);
}

TEST_F(EtQubitMeasurementTest, CorrelationMeasureXwithoutError) {
  rng->doubleValue = 0.5;
  EXPECT_EQ(qubit->correlationMeasureX(), MeasureXResult::NO_Z_ERROR);
  rng->doubleValue = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureX(), MeasureXResult::HAS_Z_ERROR);
}

TEST_F(EtQubitMeasurementTest, CorrelationMeasureXwithError) {
  // X error
  qubit->addXerror();
  rng->doubleValue = 0.5;
  EXPECT_EQ(qubit->correlationMeasureX(), MeasureXResult::NO_Z_ERROR);
  rng->doubleValue = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureX(), MeasureXResult::HAS_Z_ERROR);

  // Y error
  qubit->addZerror();
  rng->doubleValue = 0.5;
  EXPECT_EQ(qubit->correlationMeasureX(), MeasureXResult::HAS_Z_ERROR);
  rng->doubleValue = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureX(), MeasureXResult::NO_Z_ERROR);

  // Z error
  qubit->addXerror();
  rng->doubleValue = 0.5;
  EXPECT_EQ(qubit->correlationMeasureX(), MeasureXResult::HAS_Z_ERROR);
  rng->doubleValue = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureX(), MeasureXResult::NO_Z_ERROR);
}

TEST_F(EtQubitMeasurementTest, CorrelationMeasureYwithoutError) {
  rng->doubleValue = 0.5;
  EXPECT_EQ(qubit->correlationMeasureY(), MeasureYResult::NO_XZ_ERROR);
  rng->doubleValue = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureY(), MeasureYResult::HAS_XZ_ERROR);
}

TEST_F(EtQubitMeasurementTest, CorrelationMeasureYwithError) {
  // X error
  qubit->addXerror();
  rng->doubleValue = 0.5;
  EXPECT_EQ(qubit->correlationMeasureY(), MeasureYResult::HAS_XZ_ERROR);
  rng->doubleValue = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureY(), MeasureYResult::NO_XZ_ERROR);

  // Y error
  qubit->addZerror();
  rng->doubleValue = 0.5;
  EXPECT_EQ(qubit->correlationMeasureY(), MeasureYResult::NO_XZ_ERROR);
  rng->doubleValue = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureY(), MeasureYResult::HAS_XZ_ERROR);

  // Z error
  qubit->addXerror();
  rng->doubleValue = 0.5;
  EXPECT_EQ(qubit->correlationMeasureY(), MeasureYResult::HAS_XZ_ERROR);
  rng->doubleValue = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureY(), MeasureYResult::NO_XZ_ERROR);
}

TEST_F(EtQubitMeasurementTest, CorrelationMeasureZwithoutError) {
  rng->doubleValue = 0.5;
  EXPECT_EQ(qubit->correlationMeasureZ(), MeasureZResult::NO_X_ERROR);
  rng->doubleValue = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureZ(), MeasureZResult::HAS_X_ERROR);
}

TEST_F(EtQubitMeasurementTest, CorrelationMeasureZwithError) {
  // X error
  qubit->addXerror();
  rng->doubleValue = 0.5;
  EXPECT_EQ(qubit->correlationMeasureZ(), MeasureZResult::HAS_X_ERROR);
  rng->doubleValue = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureZ(), MeasureZResult::NO_X_ERROR);

  // Y error
  qubit->addZerror();
  rng->doubleValue = 0.5;
  EXPECT_EQ(qubit->correlationMeasureZ(), MeasureZResult::HAS_X_ERROR);
  rng->doubleValue = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureZ(), MeasureZResult::NO_X_ERROR);

  // Z error
  qubit->addXerror();
  rng->doubleValue = 0.5;
  EXPECT_EQ(qubit->correlationMeasureZ(), MeasureZResult::NO_X_ERROR);
  rng->doubleValue = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureZ(), MeasureZResult::HAS_X_ERROR);
}

TEST_F(EtQubitMeasurementTest, localXMeasurementWithoutError) {
  qubit->entangled_partner = another_qubit;
  another_qubit->entangled_partner = qubit;
  ASSERT_NE(qubit->entangled_partner, nullptr);
  ASSERT_NE(another_qubit->entangled_partner, nullptr);

  qubit->reset();
  another_qubit->reset();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::PLUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::MINUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_TRUE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::PLUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_TRUE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::MINUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addXerror();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::PLUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addXerror();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::MINUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_TRUE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  qubit->addXerror();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::PLUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_TRUE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  qubit->addXerror();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::MINUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);
}

TEST_F(EtQubitMeasurementTest, localXMeasurementWithError) {
  double X_measurement_error_rate = 0.99;
  qubit->Measurement_error.x_error_rate = X_measurement_error_rate;
  qubit->entangled_partner = another_qubit;
  another_qubit->entangled_partner = qubit;

  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::MINUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::PLUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_TRUE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::MINUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_TRUE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::PLUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addXerror();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::MINUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addXerror();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::PLUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_TRUE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  qubit->addXerror();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::MINUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_TRUE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  qubit->addXerror();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureX(), EigenvalueResult::PLUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);
}

TEST_F(EtQubitMeasurementTest, localZMeasurementWithoutError) {
  qubit->entangled_partner = another_qubit;
  another_qubit->entangled_partner = qubit;
  // qubit->setMeasurementErrorModel(qubit->Measurement_error);

  qubit->reset();
  another_qubit->reset();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::PLUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::MINUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_TRUE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::PLUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::MINUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_TRUE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addXerror();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::PLUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_TRUE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addXerror();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::MINUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  qubit->addXerror();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::PLUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_TRUE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  qubit->addXerror();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::MINUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);
}

TEST_F(EtQubitMeasurementTest, localZMeasurementWithError) {
  double Z_measurement_error_rate = 0.99;
  qubit->Measurement_error.z_error_rate = Z_measurement_error_rate;
  qubit->entangled_partner = another_qubit;
  another_qubit->entangled_partner = qubit;

  qubit->reset();
  another_qubit->reset();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::MINUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::PLUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_TRUE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::MINUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::PLUS_ONE);
  EXPECT_FALSE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_TRUE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addXerror();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::MINUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_TRUE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addXerror();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::PLUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_FALSE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  qubit->addXerror();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::MINUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_TRUE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  qubit->addXerror();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureZ(), EigenvalueResult::PLUS_ONE);
  EXPECT_TRUE(qubit->has_x_error);
  EXPECT_TRUE(qubit->has_z_error);
  EXPECT_FALSE(another_qubit->has_x_error);
  EXPECT_FALSE(another_qubit->has_z_error);
}

}  // end namespace

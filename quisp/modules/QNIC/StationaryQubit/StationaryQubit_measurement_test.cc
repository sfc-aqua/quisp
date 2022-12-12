#include <gtest/gtest.h>
#include <modules/common_types.h>
#include <test_utils/TestUtils.h>
#include <unsupported/Eigen/MatrixFunctions>
#include "StationaryQubit.h"
#include "modules/QNIC/StationaryQubit/IStationaryQubit.h"
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
  using StationaryQubit::addXerror;
  using StationaryQubit::addZerror;
  using StationaryQubit::correlationMeasureX;
  using StationaryQubit::correlationMeasureY;
  using StationaryQubit::correlationMeasureZ;
  using StationaryQubit::initialize;
  using StationaryQubit::localMeasureX;
  using StationaryQubit::localMeasureY;
  using StationaryQubit::localMeasureZ;
  using StationaryQubit::par;
  using StationaryQubit::setMeasurementErrorModel;
  StatQubitTarget() : StationaryQubit() {
    setComponentType(new TestModuleType("test qubit"));
    provider.setStrategy(std::make_unique<Strategy>());
  }
  void reset() {
    this->god_err.has_x_error = false;
    this->god_err.has_z_error = false;
    // this->god_err.has_Y_error = false; not implemeted yet
  }
  void fillParams() {
    setParDouble(this, "emission_success_probability", 0.5);
    setParDouble(this, "memory_x_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_y_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_z_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_energy_excitation_rate", 0.000198);
    setParDouble(this, "memory_energy_relaxation_rate", 0.00000198);
    setParDouble(this, "memory_completely_mixed_rate", 0);

    // No error= 0.4, X error = 0.6, Z error = 0.8, Y error = 1.0
    setParDouble(this, "h_gate_error_rate", 0.6);
    setParDouble(this, "h_gate_x_error_ratio", 1);
    setParDouble(this, "h_gate_z_error_ratio", 1);
    setParDouble(this, "h_gate_y_error_ratio", 1);

    setParDouble(this, "x_gate_error_rate", 0.6);
    setParDouble(this, "x_gate_x_error_ratio", 1);
    setParDouble(this, "x_gate_z_error_ratio", 1);
    setParDouble(this, "x_gate_y_error_ratio", 1);

    setParDouble(this, "z_gate_error_rate", 0.6);
    setParDouble(this, "z_gate_x_error_ratio", 1);
    setParDouble(this, "z_gate_z_error_ratio", 1);
    setParDouble(this, "z_gate_y_error_ratio", 1);

    // clean = 0.1,
    // IX = 0.2, XI = 0.3, XX = 0.4,
    // IZ = 0.5, ZI = 0.6, ZZ = 0.7,
    // IY = 0.8, IY = 0.9, YY = 1.0
    setParDouble(this, "cnot_gate_error_rate", 0.9);
    setParDouble(this, "cnot_gate_ix_error_ratio", 1);
    setParDouble(this, "cnot_gate_xi_error_ratio", 1);
    setParDouble(this, "cnot_gate_xx_error_ratio", 1);
    setParDouble(this, "cnot_gate_iz_error_ratio", 1);
    setParDouble(this, "cnot_gate_zi_error_ratio", 1);
    setParDouble(this, "cnot_gate_zz_error_ratio", 1);
    setParDouble(this, "cnot_gate_iy_error_ratio", 1);
    setParDouble(this, "cnot_gate_yi_error_ratio", 1);
    setParDouble(this, "cnot_gate_yy_error_ratio", 1);

    setParDouble(this, "x_measurement_error_rate", 1.0 / 2000);
    setParDouble(this, "y_measurement_error_rate", 1.0 / 2000);
    setParDouble(this, "z_measurement_error_rate", 1.0 / 2000);

    setParInt(this, "stationary_qubit_address", 1);
    setParInt(this, "node_address", 1);
    setParInt(this, "qnic_address", 1);
    setParInt(this, "qnic_type", 0);
    setParInt(this, "qnic_index", 0);
    setParDouble(this, "std", 0.5);

    setParDouble(this, "fidelity", -1.0);
  }
};

TEST(StatQubitMeasurementTest, SetMeasurementErrorRate) {
  auto *sim = prepareSimulation();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  setParDouble(qubit, "x_measurement_error_rate", 0.1);
  setParDouble(qubit, "y_measurement_error_rate", 0.2);
  setParDouble(qubit, "z_measurement_error_rate", 0.4);
  sim->registerComponent(qubit);
  qubit->setMeasurementErrorModel(qubit->Measurement_error);
  auto &error_model = qubit->Measurement_error;
  EXPECT_FALSE(std::isnan(error_model.x_error_rate));
  EXPECT_FALSE(std::isnan(error_model.y_error_rate));
  EXPECT_FALSE(std::isnan(error_model.z_error_rate));
  EXPECT_DOUBLE_EQ(error_model.x_error_rate, 0.1);
  EXPECT_DOUBLE_EQ(error_model.y_error_rate, 0.2);
  EXPECT_DOUBLE_EQ(error_model.z_error_rate, 0.4);
}

TEST(StatQubitMeasurementTest, CorrelationMeasureXwithoutError) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  qubit->setMeasurementErrorModel(qubit->Measurement_error);
  sim->registerComponent(qubit);
  rng->doubleValue = 0.5;
  EXPECT_EQ(qubit->correlationMeasureX(), quisp::types::MeasureXResult::NO_Z_ERROR);
  rng->doubleValue = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureX(), quisp::types::MeasureXResult::HAS_Z_ERROR);
}

TEST(StatQubitMeasurementTest, CorrelationMeasureXwithError) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  qubit->setMeasurementErrorModel(qubit->Measurement_error);
  sim->registerComponent(qubit);

  // X error
  qubit->addXerror();
  rng->doubleValue = 0.5;
  EXPECT_EQ(qubit->correlationMeasureX(), quisp::types::MeasureXResult::NO_Z_ERROR);
  rng->doubleValue = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureX(), quisp::types::MeasureXResult::HAS_Z_ERROR);

  // Y error
  qubit->addZerror();
  rng->doubleValue = 0.5;
  EXPECT_EQ(qubit->correlationMeasureX(), quisp::types::MeasureXResult::HAS_Z_ERROR);
  rng->doubleValue = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureX(), quisp::types::MeasureXResult::NO_Z_ERROR);

  // Z error
  qubit->addXerror();
  rng->doubleValue = 0.5;
  EXPECT_EQ(qubit->correlationMeasureX(), quisp::types::MeasureXResult::HAS_Z_ERROR);
  rng->doubleValue = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureX(), quisp::types::MeasureXResult::NO_Z_ERROR);
}

TEST(StatQubitMeasurementTest, CorrelationMeasureYwithoutError) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  qubit->setMeasurementErrorModel(qubit->Measurement_error);
  sim->registerComponent(qubit);
  rng->doubleValue = 0.5;
  EXPECT_EQ(qubit->correlationMeasureY(), quisp::types::MeasureYResult::NO_XZ_ERROR);
  rng->doubleValue = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureY(), quisp::types::MeasureYResult::HAS_XZ_ERROR);
}

TEST(StatQubitMeasurementTest, CorrelationMeasureYwithError) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  qubit->setMeasurementErrorModel(qubit->Measurement_error);
  sim->registerComponent(qubit);

  // X error
  qubit->addXerror();
  rng->doubleValue = 0.5;
  EXPECT_EQ(qubit->correlationMeasureY(), quisp::types::MeasureYResult::HAS_XZ_ERROR);
  rng->doubleValue = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureY(), quisp::types::MeasureYResult::NO_XZ_ERROR);

  // Y error
  qubit->addZerror();
  rng->doubleValue = 0.5;
  EXPECT_EQ(qubit->correlationMeasureY(), quisp::types::MeasureYResult::NO_XZ_ERROR);
  rng->doubleValue = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureY(), quisp::types::MeasureYResult::HAS_XZ_ERROR);

  // Z error
  qubit->addXerror();
  rng->doubleValue = 0.5;
  EXPECT_EQ(qubit->correlationMeasureY(), quisp::types::MeasureYResult::HAS_XZ_ERROR);
  rng->doubleValue = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureY(), quisp::types::MeasureYResult::NO_XZ_ERROR);
}

TEST(StatQubitMeasurementTest, CorrelationMeasureZwithoutError) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  qubit->setMeasurementErrorModel(qubit->Measurement_error);
  sim->registerComponent(qubit);
  rng->doubleValue = 0.5;
  EXPECT_EQ(qubit->correlationMeasureZ(), quisp::types::MeasureZResult::NO_X_ERROR);
  rng->doubleValue = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureZ(), quisp::types::MeasureZResult::HAS_X_ERROR);
}

TEST(StatQubitMeasurementTest, CorrelationMeasureZwithError) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit = new StatQubitTarget{};
  qubit->fillParams();
  qubit->setMeasurementErrorModel(qubit->Measurement_error);
  sim->registerComponent(qubit);

  // X error
  qubit->addXerror();
  rng->doubleValue = 0.5;
  EXPECT_EQ(qubit->correlationMeasureZ(), quisp::types::MeasureZResult::HAS_X_ERROR);
  rng->doubleValue = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureZ(), quisp::types::MeasureZResult::NO_X_ERROR);

  // Y error
  qubit->addZerror();
  rng->doubleValue = 0.5;
  EXPECT_EQ(qubit->correlationMeasureZ(), quisp::types::MeasureZResult::HAS_X_ERROR);
  rng->doubleValue = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureZ(), quisp::types::MeasureZResult::NO_X_ERROR);

  // Z error
  qubit->addXerror();
  rng->doubleValue = 0.5;
  EXPECT_EQ(qubit->correlationMeasureZ(), quisp::types::MeasureZResult::NO_X_ERROR);
  rng->doubleValue = 1.0 / 3000;
  EXPECT_EQ(qubit->correlationMeasureZ(), quisp::types::MeasureZResult::HAS_X_ERROR);
}

TEST(StatQubitMeasurementTest, localXMeasurementWithoutError) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit = new StatQubitTarget{};
  auto *another_qubit = new StatQubitTarget{};
  qubit->fillParams();
  another_qubit->fillParams();
  qubit->entangled_partner = another_qubit;
  another_qubit->entangled_partner = qubit;
  qubit->setMeasurementErrorModel(qubit->Measurement_error);
  sim->registerComponent(qubit);

  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::PLUS_ONE);
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_FALSE(another_qubit->god_err.has_x_error);
  EXPECT_FALSE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::MINUS_ONE);
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_FALSE(another_qubit->god_err.has_x_error);
  EXPECT_TRUE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::PLUS_ONE);
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_FALSE(another_qubit->god_err.has_x_error);
  EXPECT_TRUE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::MINUS_ONE);
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_FALSE(another_qubit->god_err.has_x_error);
  EXPECT_FALSE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addXerror();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::PLUS_ONE);
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_FALSE(another_qubit->god_err.has_x_error);
  EXPECT_FALSE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addXerror();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::MINUS_ONE);
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_FALSE(another_qubit->god_err.has_x_error);
  EXPECT_TRUE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  qubit->addXerror();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::PLUS_ONE);
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_FALSE(another_qubit->god_err.has_x_error);
  EXPECT_TRUE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  qubit->addXerror();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::MINUS_ONE);
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_FALSE(another_qubit->god_err.has_x_error);
  EXPECT_FALSE(another_qubit->god_err.has_z_error);
}

TEST(StatQubitMeasurementTest, localXMeasurementWithError) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit = new StatQubitTarget{};
  auto *another_qubit = new StatQubitTarget{};
  qubit->fillParams();
  another_qubit->fillParams();
  setParDouble(qubit, "x_measurement_error_rate", 0.99);
  qubit->entangled_partner = another_qubit;
  another_qubit->entangled_partner = qubit;
  qubit->setMeasurementErrorModel(qubit->Measurement_error);
  sim->registerComponent(qubit);

  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::MINUS_ONE);
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_FALSE(another_qubit->god_err.has_x_error);
  EXPECT_FALSE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::PLUS_ONE);
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_FALSE(another_qubit->god_err.has_x_error);
  EXPECT_TRUE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::MINUS_ONE);
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_FALSE(another_qubit->god_err.has_x_error);
  EXPECT_TRUE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::PLUS_ONE);
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_FALSE(another_qubit->god_err.has_x_error);
  EXPECT_FALSE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addXerror();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::MINUS_ONE);
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_FALSE(another_qubit->god_err.has_x_error);
  EXPECT_FALSE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addXerror();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::PLUS_ONE);
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_FALSE(another_qubit->god_err.has_x_error);
  EXPECT_TRUE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  qubit->addXerror();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::MINUS_ONE);
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_FALSE(another_qubit->god_err.has_x_error);
  EXPECT_TRUE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  qubit->addXerror();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::PLUS_ONE);
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_FALSE(another_qubit->god_err.has_x_error);
  EXPECT_FALSE(another_qubit->god_err.has_z_error);
}

TEST(StatQubitMeasurementTest, localZMeasurementWithoutError) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit = new StatQubitTarget{};
  auto *another_qubit = new StatQubitTarget{};
  qubit->fillParams();
  another_qubit->fillParams();
  qubit->entangled_partner = another_qubit;
  another_qubit->entangled_partner = qubit;
  qubit->setMeasurementErrorModel(qubit->Measurement_error);
  sim->registerComponent(qubit);

  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::PLUS_ONE);
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_FALSE(another_qubit->god_err.has_x_error);
  EXPECT_FALSE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::MINUS_ONE);
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_TRUE(another_qubit->god_err.has_x_error);
  EXPECT_FALSE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::PLUS_ONE);
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_FALSE(another_qubit->god_err.has_x_error);
  EXPECT_FALSE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::MINUS_ONE);
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_TRUE(another_qubit->god_err.has_x_error);
  EXPECT_FALSE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addXerror();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::PLUS_ONE);
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_TRUE(another_qubit->god_err.has_x_error);
  EXPECT_FALSE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addXerror();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::MINUS_ONE);
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_FALSE(another_qubit->god_err.has_x_error);
  EXPECT_FALSE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  qubit->addXerror();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::PLUS_ONE);
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_TRUE(another_qubit->god_err.has_x_error);
  EXPECT_FALSE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  qubit->addXerror();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::MINUS_ONE);
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_FALSE(another_qubit->god_err.has_x_error);
  EXPECT_FALSE(another_qubit->god_err.has_z_error);
}

TEST(StatQubitMeasurementTest, localZMeasurementWithError) {
  auto *sim = prepareSimulation();
  auto *rng = useTestRNG();
  auto *qubit = new StatQubitTarget{};
  auto *another_qubit = new StatQubitTarget{};
  qubit->fillParams();
  another_qubit->fillParams();
  setParDouble(qubit, "z_measurement_error_rate", 0.99);
  qubit->entangled_partner = another_qubit;
  another_qubit->entangled_partner = qubit;
  qubit->setMeasurementErrorModel(qubit->Measurement_error);
  sim->registerComponent(qubit);

  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::MINUS_ONE);
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_FALSE(another_qubit->god_err.has_x_error);
  EXPECT_FALSE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::PLUS_ONE);
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_TRUE(another_qubit->god_err.has_x_error);
  EXPECT_FALSE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::MINUS_ONE);
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_FALSE(another_qubit->god_err.has_x_error);
  EXPECT_FALSE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::PLUS_ONE);
  EXPECT_FALSE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_TRUE(another_qubit->god_err.has_x_error);
  EXPECT_FALSE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addXerror();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::MINUS_ONE);
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_TRUE(another_qubit->god_err.has_x_error);
  EXPECT_FALSE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addXerror();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::PLUS_ONE);
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_FALSE(qubit->god_err.has_z_error);
  EXPECT_FALSE(another_qubit->god_err.has_x_error);
  EXPECT_FALSE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  qubit->addXerror();
  rng->doubleValue = 0.7;
  EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::MINUS_ONE);
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_TRUE(another_qubit->god_err.has_x_error);
  EXPECT_FALSE(another_qubit->god_err.has_z_error);

  qubit->reset();
  another_qubit->reset();
  qubit->addZerror();
  qubit->addXerror();
  rng->doubleValue = 0.3;
  EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::PLUS_ONE);
  EXPECT_TRUE(qubit->god_err.has_x_error);
  EXPECT_TRUE(qubit->god_err.has_z_error);
  EXPECT_FALSE(another_qubit->god_err.has_x_error);
  EXPECT_FALSE(another_qubit->god_err.has_z_error);
}

}  // end namespace

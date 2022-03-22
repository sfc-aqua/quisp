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
    setParBool(this, "GOD_Xerror", false);
    setParBool(this, "GOD_Yerror", false);
    setParBool(this, "GOD_Zerror", false);
  }
  void fillParams() {
    setParDouble(this, "emission_success_probability", 0.5);
    setParDouble(this, "memory_X_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_Y_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_Z_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_energy_excitation_rate", 0.000198);
    setParDouble(this, "memory_energy_relaxation_rate", 0.00000198);
    setParDouble(this, "memory_completely_mixed_rate", 0);

    // No error= 0.4, X error = 0.6, Z error = 0.8, Y error = 1.0
    setParDouble(this, "Hgate_error_rate", 0.6);
    setParDouble(this, "Hgate_X_error_ratio", 1);
    setParDouble(this, "Hgate_Z_error_ratio", 1);
    setParDouble(this, "Hgate_Y_error_ratio", 1);

    setParDouble(this, "Xgate_error_rate", 0.6);
    setParDouble(this, "Xgate_X_error_ratio", 1);
    setParDouble(this, "Xgate_Z_error_ratio", 1);
    setParDouble(this, "Xgate_Y_error_ratio", 1);

    setParDouble(this, "Zgate_error_rate", 0.6);
    setParDouble(this, "Zgate_X_error_ratio", 1);
    setParDouble(this, "Zgate_Z_error_ratio", 1);
    setParDouble(this, "Zgate_Y_error_ratio", 1);

    // clean = 0.1,
    // IX = 0.2, XI = 0.3, XX = 0.4,
    // IZ = 0.5, ZI = 0.6, ZZ = 0.7,
    // IY = 0.8, IY = 0.9, YY = 1.0
    setParDouble(this, "CNOTgate_error_rate", 0.9);
    setParDouble(this, "CNOTgate_IX_error_ratio", 1);
    setParDouble(this, "CNOTgate_XI_error_ratio", 1);
    setParDouble(this, "CNOTgate_XX_error_ratio", 1);
    setParDouble(this, "CNOTgate_IZ_error_ratio", 1);
    setParDouble(this, "CNOTgate_ZI_error_ratio", 1);
    setParDouble(this, "CNOTgate_ZZ_error_ratio", 1);
    setParDouble(this, "CNOTgate_IY_error_ratio", 1);
    setParDouble(this, "CNOTgate_YI_error_ratio", 1);
    setParDouble(this, "CNOTgate_YY_error_ratio", 1);

    setParDouble(this, "X_measurement_error_rate", 1.0 / 2000);
    setParDouble(this, "Y_measurement_error_rate", 1.0 / 2000);
    setParDouble(this, "Z_measurement_error_rate", 1.0 / 2000);

    setParInt(this, "stationaryQubit_address", 1);
    setParInt(this, "node_address", 1);
    setParInt(this, "qnic_address", 1);
    setParInt(this, "qnic_type", 0);
    setParInt(this, "qnic_index", 0);
    setParDouble(this, "std", 0.5);

    setParDouble(this, "photon_emitted_at", 0.0);
    setParDouble(this, "last_updated_at", 0.0);
    setParBool(this, "GOD_Xerror", false);
    setParBool(this, "GOD_Zerror", false);
    setParBool(this, "GOD_CMerror", false);
    setParBool(this, "GOD_EXerror", false);
    setParBool(this, "GOD_REerror", false);
    setParBool(this, "isBusy", false);
    setParInt(this, "GOD_entangled_stationaryQubit_address", 0);
    setParInt(this, "GOD_entangled_node_address", 0);
    setParInt(this, "GOD_entangled_qnic_address", 0);
    setParInt(this, "GOD_entangled_qnic_type", 0);
    setParDouble(this, "fidelity", -1.0);
  }
};

// TEST(StatQubitMeasurementTest, SetMeasurementErrorRate) {
//   auto *sim = prepareSimulation();
//   auto *qubit = new StatQubitTarget{};
//   qubit->fillParams();
//   setParDouble(qubit, "X_measurement_error_rate", 0.1);
//   setParDouble(qubit, "Y_measurement_error_rate", 0.2);
//   setParDouble(qubit, "Z_measurement_error_rate", 0.4);
//   sim->registerComponent(qubit);
//   qubit->setMeasurementErrorModel(qubit->Measurement_error);
//   auto &error_model = qubit->Measurement_error;
//   EXPECT_FALSE(std::isnan(error_model.x_error_rate));
//   EXPECT_FALSE(std::isnan(error_model.y_error_rate));
//   EXPECT_FALSE(std::isnan(error_model.z_error_rate));
//   EXPECT_DOUBLE_EQ(error_model.x_error_rate, 0.1);
//   EXPECT_DOUBLE_EQ(error_model.y_error_rate, 0.2);
//   EXPECT_DOUBLE_EQ(error_model.z_error_rate, 0.4);
// }

// TEST(StatQubitMeasurementTest, CorrelationMeasureXwithoutError) {
//   auto *sim = prepareSimulation();
//   auto *rng = useTestRNG();
//   auto *qubit = new StatQubitTarget{};
//   qubit->fillParams();
//   qubit->setMeasurementErrorModel(qubit->Measurement_error);
//   sim->registerComponent(qubit);
//   rng->doubleValue = 0.5;
//   EXPECT_EQ(qubit->correlationMeasureX(), quisp::types::MeasureXResult::NO_Z_ERROR);
//   rng->doubleValue = 1.0 / 3000;
//   EXPECT_EQ(qubit->correlationMeasureX(), quisp::types::MeasureXResult::HAS_Z_ERROR);
// }

// TEST(StatQubitMeasurementTest, CorrelationMeasureXwithError) {
//   auto *sim = prepareSimulation();
//   auto *rng = useTestRNG();
//   auto *qubit = new StatQubitTarget{};
//   qubit->fillParams();
//   qubit->setMeasurementErrorModel(qubit->Measurement_error);
//   sim->registerComponent(qubit);

//   // X error
//   qubit->addXerror();
//   rng->doubleValue = 0.5;
//   EXPECT_EQ(qubit->correlationMeasureX(), quisp::types::MeasureXResult::NO_Z_ERROR);
//   rng->doubleValue = 1.0 / 3000;
//   EXPECT_EQ(qubit->correlationMeasureX(), quisp::types::MeasureXResult::HAS_Z_ERROR);

//   // Y error
//   qubit->addZerror();
//   rng->doubleValue = 0.5;
//   EXPECT_EQ(qubit->correlationMeasureX(), quisp::types::MeasureXResult::HAS_Z_ERROR);
//   rng->doubleValue = 1.0 / 3000;
//   EXPECT_EQ(qubit->correlationMeasureX(), quisp::types::MeasureXResult::NO_Z_ERROR);

//   // Z error
//   qubit->addXerror();
//   rng->doubleValue = 0.5;
//   EXPECT_EQ(qubit->correlationMeasureX(), quisp::types::MeasureXResult::HAS_Z_ERROR);
//   rng->doubleValue = 1.0 / 3000;
//   EXPECT_EQ(qubit->correlationMeasureX(), quisp::types::MeasureXResult::NO_Z_ERROR);
// }

// TEST(StatQubitMeasurementTest, CorrelationMeasureYwithoutError) {
//   auto *sim = prepareSimulation();
//   auto *rng = useTestRNG();
//   auto *qubit = new StatQubitTarget{};
//   qubit->fillParams();
//   qubit->setMeasurementErrorModel(qubit->Measurement_error);
//   sim->registerComponent(qubit);
//   rng->doubleValue = 0.5;
//   EXPECT_EQ(qubit->correlationMeasureY(), quisp::types::MeasureYResult::NO_XZ_ERROR);
//   rng->doubleValue = 1.0 / 3000;
//   EXPECT_EQ(qubit->correlationMeasureY(), quisp::types::MeasureYResult::HAS_XZ_ERROR);
// }

// TEST(StatQubitMeasurementTest, CorrelationMeasureYwithError) {
//   auto *sim = prepareSimulation();
//   auto *rng = useTestRNG();
//   auto *qubit = new StatQubitTarget{};
//   qubit->fillParams();
//   qubit->setMeasurementErrorModel(qubit->Measurement_error);
//   sim->registerComponent(qubit);

//   // X error
//   qubit->addXerror();
//   rng->doubleValue = 0.5;
//   EXPECT_EQ(qubit->correlationMeasureY(), quisp::types::MeasureYResult::HAS_XZ_ERROR);
//   rng->doubleValue = 1.0 / 3000;
//   EXPECT_EQ(qubit->correlationMeasureY(), quisp::types::MeasureYResult::NO_XZ_ERROR);

//   // Y error
//   qubit->addZerror();
//   rng->doubleValue = 0.5;
//   EXPECT_EQ(qubit->correlationMeasureY(), quisp::types::MeasureYResult::NO_XZ_ERROR);
//   rng->doubleValue = 1.0 / 3000;
//   EXPECT_EQ(qubit->correlationMeasureY(), quisp::types::MeasureYResult::HAS_XZ_ERROR);

//   // Z error
//   qubit->addXerror();
//   rng->doubleValue = 0.5;
//   EXPECT_EQ(qubit->correlationMeasureY(), quisp::types::MeasureYResult::HAS_XZ_ERROR);
//   rng->doubleValue = 1.0 / 3000;
//   EXPECT_EQ(qubit->correlationMeasureY(), quisp::types::MeasureYResult::NO_XZ_ERROR);
// }

// TEST(StatQubitMeasurementTest, CorrelationMeasureZwithoutError) {
//   auto *sim = prepareSimulation();
//   auto *rng = useTestRNG();
//   auto *qubit = new StatQubitTarget{};
//   qubit->fillParams();
//   qubit->setMeasurementErrorModel(qubit->Measurement_error);
//   sim->registerComponent(qubit);
//   rng->doubleValue = 0.5;
//   EXPECT_EQ(qubit->correlationMeasureZ(), quisp::types::MeasureZResult::NO_X_ERROR);
//   rng->doubleValue = 1.0 / 3000;
//   EXPECT_EQ(qubit->correlationMeasureZ(), quisp::types::MeasureZResult::HAS_X_ERROR);
// }

// TEST(StatQubitMeasurementTest, CorrelationMeasureZwithError) {
//   auto *sim = prepareSimulation();
//   auto *rng = useTestRNG();
//   auto *qubit = new StatQubitTarget{};
//   qubit->fillParams();
//   qubit->setMeasurementErrorModel(qubit->Measurement_error);
//   sim->registerComponent(qubit);

//   // X error
//   qubit->addXerror();
//   rng->doubleValue = 0.5;
//   EXPECT_EQ(qubit->correlationMeasureZ(), quisp::types::MeasureZResult::HAS_X_ERROR);
//   rng->doubleValue = 1.0 / 3000;
//   EXPECT_EQ(qubit->correlationMeasureZ(), quisp::types::MeasureZResult::NO_X_ERROR);

//   // Y error
//   qubit->addZerror();
//   rng->doubleValue = 0.5;
//   EXPECT_EQ(qubit->correlationMeasureZ(), quisp::types::MeasureZResult::HAS_X_ERROR);
//   rng->doubleValue = 1.0 / 3000;
//   EXPECT_EQ(qubit->correlationMeasureZ(), quisp::types::MeasureZResult::NO_X_ERROR);

//   // Z error
//   qubit->addXerror();
//   rng->doubleValue = 0.5;
//   EXPECT_EQ(qubit->correlationMeasureZ(), quisp::types::MeasureZResult::NO_X_ERROR);
//   rng->doubleValue = 1.0 / 3000;
//   EXPECT_EQ(qubit->correlationMeasureZ(), quisp::types::MeasureZResult::HAS_X_ERROR);
// }

// TEST(StatQubitMeasurementTest, localXMeasurementWithoutError) {
//   auto *sim = prepareSimulation();
//   auto *rng = useTestRNG();
//   auto *qubit = new StatQubitTarget{};
//   auto *another_qubit = new StatQubitTarget{};
//   qubit->fillParams();
//   another_qubit->fillParams();
//   qubit->entangled_partner = another_qubit;
//   another_qubit->entangled_partner = qubit;
//   qubit->setMeasurementErrorModel(qubit->Measurement_error);
//   sim->registerComponent(qubit);

//   rng->doubleValue = 0.7;
//   EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::PLUS_ONE);
//   EXPECT_FALSE(qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(qubit->par("GOD_Zerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   rng->doubleValue = 0.3;
//   EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::MINUS_ONE);
//   EXPECT_FALSE(qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(qubit->par("GOD_Zerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Xerror"));
//   EXPECT_TRUE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   qubit->addZerror();
//   rng->doubleValue = 0.7;
//   EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::PLUS_ONE);
//   EXPECT_FALSE(qubit->par("GOD_Xerror"));
//   EXPECT_TRUE(qubit->par("GOD_Zerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Xerror"));
//   EXPECT_TRUE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   qubit->addZerror();
//   rng->doubleValue = 0.3;
//   EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::MINUS_ONE);
//   EXPECT_FALSE(qubit->par("GOD_Xerror"));
//   EXPECT_TRUE(qubit->par("GOD_Zerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   qubit->addXerror();
//   rng->doubleValue = 0.7;
//   EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::PLUS_ONE);
//   EXPECT_TRUE(qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(qubit->par("GOD_Zerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   qubit->addXerror();
//   rng->doubleValue = 0.3;
//   EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::MINUS_ONE);
//   EXPECT_TRUE(qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(qubit->par("GOD_Zerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Xerror"));
//   EXPECT_TRUE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   qubit->addZerror();
//   qubit->addXerror();
//   rng->doubleValue = 0.7;
//   EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::PLUS_ONE);
//   EXPECT_TRUE(qubit->par("GOD_Xerror"));
//   EXPECT_TRUE(qubit->par("GOD_Zerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Xerror"));
//   EXPECT_TRUE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   qubit->addZerror();
//   qubit->addXerror();
//   rng->doubleValue = 0.3;
//   EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::MINUS_ONE);
//   EXPECT_TRUE(qubit->par("GOD_Xerror"));
//   EXPECT_TRUE(qubit->par("GOD_Zerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Zerror"));
// }

// TEST(StatQubitMeasurementTest, localXMeasurementWithError) {
//   auto *sim = prepareSimulation();
//   auto *rng = useTestRNG();
//   auto *qubit = new StatQubitTarget{};
//   auto *another_qubit = new StatQubitTarget{};
//   qubit->fillParams();
//   another_qubit->fillParams();
//   setParDouble(qubit, "X_measurement_error_rate", 0.99);
//   qubit->entangled_partner = another_qubit;
//   another_qubit->entangled_partner = qubit;
//   qubit->setMeasurementErrorModel(qubit->Measurement_error);
//   sim->registerComponent(qubit);

//   rng->doubleValue = 0.7;
//   EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::MINUS_ONE);
//   EXPECT_FALSE(qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(qubit->par("GOD_Zerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   rng->doubleValue = 0.3;
//   EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::PLUS_ONE);
//   EXPECT_FALSE(qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(qubit->par("GOD_Zerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Xerror"));
//   EXPECT_TRUE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   qubit->addZerror();
//   rng->doubleValue = 0.7;
//   EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::MINUS_ONE);
//   EXPECT_FALSE(qubit->par("GOD_Xerror"));
//   EXPECT_TRUE(qubit->par("GOD_Zerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Xerror"));
//   EXPECT_TRUE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   qubit->addZerror();
//   rng->doubleValue = 0.3;
//   EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::PLUS_ONE);
//   EXPECT_FALSE(qubit->par("GOD_Xerror"));
//   EXPECT_TRUE(qubit->par("GOD_Zerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   qubit->addXerror();
//   rng->doubleValue = 0.7;
//   EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::MINUS_ONE);
//   EXPECT_TRUE(qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(qubit->par("GOD_Zerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   qubit->addXerror();
//   rng->doubleValue = 0.3;
//   EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::PLUS_ONE);
//   EXPECT_TRUE(qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(qubit->par("GOD_Zerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Xerror"));
//   EXPECT_TRUE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   qubit->addZerror();
//   qubit->addXerror();
//   rng->doubleValue = 0.7;
//   EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::MINUS_ONE);
//   EXPECT_TRUE(qubit->par("GOD_Xerror"));
//   EXPECT_TRUE(qubit->par("GOD_Zerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Xerror"));
//   EXPECT_TRUE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   qubit->addZerror();
//   qubit->addXerror();
//   rng->doubleValue = 0.3;
//   EXPECT_EQ(qubit->localMeasureX(), quisp::types::EigenvalueResult::PLUS_ONE);
//   EXPECT_TRUE(qubit->par("GOD_Xerror"));
//   EXPECT_TRUE(qubit->par("GOD_Zerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Zerror"));
// }

// TEST(StatQubitMeasurementTest, localZMeasurementWithoutError) {
//   auto *sim = prepareSimulation();
//   auto *rng = useTestRNG();
//   auto *qubit = new StatQubitTarget{};
//   auto *another_qubit = new StatQubitTarget{};
//   qubit->fillParams();
//   another_qubit->fillParams();
//   qubit->entangled_partner = another_qubit;
//   another_qubit->entangled_partner = qubit;
//   qubit->setMeasurementErrorModel(qubit->Measurement_error);
//   sim->registerComponent(qubit);

//   rng->doubleValue = 0.7;
//   EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::PLUS_ONE);
//   EXPECT_FALSE(qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(qubit->par("GOD_Zerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   rng->doubleValue = 0.3;
//   EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::MINUS_ONE);
//   EXPECT_FALSE(qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(qubit->par("GOD_Zerror"));
//   EXPECT_TRUE(another_qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   qubit->addZerror();
//   rng->doubleValue = 0.7;
//   EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::PLUS_ONE);
//   EXPECT_FALSE(qubit->par("GOD_Xerror"));
//   EXPECT_TRUE(qubit->par("GOD_Zerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   qubit->addZerror();
//   rng->doubleValue = 0.3;
//   EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::MINUS_ONE);
//   EXPECT_FALSE(qubit->par("GOD_Xerror"));
//   EXPECT_TRUE(qubit->par("GOD_Zerror"));
//   EXPECT_TRUE(another_qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   qubit->addXerror();
//   rng->doubleValue = 0.7;
//   EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::PLUS_ONE);
//   EXPECT_TRUE(qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(qubit->par("GOD_Zerror"));
//   EXPECT_TRUE(another_qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   qubit->addXerror();
//   rng->doubleValue = 0.3;
//   EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::MINUS_ONE);
//   EXPECT_TRUE(qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(qubit->par("GOD_Zerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   qubit->addZerror();
//   qubit->addXerror();
//   rng->doubleValue = 0.7;
//   EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::PLUS_ONE);
//   EXPECT_TRUE(qubit->par("GOD_Xerror"));
//   EXPECT_TRUE(qubit->par("GOD_Zerror"));
//   EXPECT_TRUE(another_qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   qubit->addZerror();
//   qubit->addXerror();
//   rng->doubleValue = 0.3;
//   EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::MINUS_ONE);
//   EXPECT_TRUE(qubit->par("GOD_Xerror"));
//   EXPECT_TRUE(qubit->par("GOD_Zerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Zerror"));
// }

// TEST(StatQubitMeasurementTest, localZMeasurementWithError) {
//   auto *sim = prepareSimulation();
//   auto *rng = useTestRNG();
//   auto *qubit = new StatQubitTarget{};
//   auto *another_qubit = new StatQubitTarget{};
//   qubit->fillParams();
//   another_qubit->fillParams();
//   setParDouble(qubit, "Z_measurement_error_rate", 0.99);
//   qubit->entangled_partner = another_qubit;
//   another_qubit->entangled_partner = qubit;
//   qubit->setMeasurementErrorModel(qubit->Measurement_error);
//   sim->registerComponent(qubit);

//   rng->doubleValue = 0.7;
//   EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::MINUS_ONE);
//   EXPECT_FALSE(qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(qubit->par("GOD_Zerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   rng->doubleValue = 0.3;
//   EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::PLUS_ONE);
//   EXPECT_FALSE(qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(qubit->par("GOD_Zerror"));
//   EXPECT_TRUE(another_qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   qubit->addZerror();
//   rng->doubleValue = 0.7;
//   EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::MINUS_ONE);
//   EXPECT_FALSE(qubit->par("GOD_Xerror"));
//   EXPECT_TRUE(qubit->par("GOD_Zerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   qubit->addZerror();
//   rng->doubleValue = 0.3;
//   EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::PLUS_ONE);
//   EXPECT_FALSE(qubit->par("GOD_Xerror"));
//   EXPECT_TRUE(qubit->par("GOD_Zerror"));
//   EXPECT_TRUE(another_qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   qubit->addXerror();
//   rng->doubleValue = 0.7;
//   EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::MINUS_ONE);
//   EXPECT_TRUE(qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(qubit->par("GOD_Zerror"));
//   EXPECT_TRUE(another_qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   qubit->addXerror();
//   rng->doubleValue = 0.3;
//   EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::PLUS_ONE);
//   EXPECT_TRUE(qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(qubit->par("GOD_Zerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   qubit->addZerror();
//   qubit->addXerror();
//   rng->doubleValue = 0.7;
//   EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::MINUS_ONE);
//   EXPECT_TRUE(qubit->par("GOD_Xerror"));
//   EXPECT_TRUE(qubit->par("GOD_Zerror"));
//   EXPECT_TRUE(another_qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Zerror"));

//   qubit->reset();
//   another_qubit->reset();
//   qubit->addZerror();
//   qubit->addXerror();
//   rng->doubleValue = 0.3;
//   EXPECT_EQ(qubit->localMeasureZ(), quisp::types::EigenvalueResult::PLUS_ONE);
//   EXPECT_TRUE(qubit->par("GOD_Xerror"));
//   EXPECT_TRUE(qubit->par("GOD_Zerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Xerror"));
//   EXPECT_FALSE(another_qubit->par("GOD_Zerror"));
// }

}  // end namespace

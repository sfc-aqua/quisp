#include "StationaryQubit.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <modules/common_types.h>
#include <test_utils/TestUtils.h>
#include <cmath>
#include <unsupported/Eigen/MatrixFunctions>
#include "backends/interfaces/IConfiguration.h"
#include "backends/interfaces/IQuantumBackend.h"
#include "test_utils/UtilFunctions.h"
#include "test_utils/mock_backends/MockQuantumBackend.h"

using namespace testing;
using namespace quisp::modules;
using namespace quisp::modules::common;
using namespace quisp_test;
using namespace Eigen;

namespace {

class Strategy : public TestComponentProviderStrategy {
 public:
  Strategy(IQuantumBackend *backend) : backend(backend) {}
  ~Strategy() {}
  IQuantumBackend *getQuantumBackend() override { return backend; }
  IQuantumBackend *backend;
};

class StatQubitTarget : public StationaryQubit {
 public:
  using StationaryQubit::initialize;
  using StationaryQubit::par;
  StatQubitTarget(IQuantumBackend *backend) : StationaryQubit() {
    setComponentType(new TestModuleType("test qubit"));
    provider.setStrategy(std::make_unique<Strategy>(backend));
  }
  void reset() { setFree(true); }
  void fillParams() {
    // see networks/omnetpp.ini
    setParDouble(this, "emission_success_probability", 0.5);
    setParDouble(this, "memory_x_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_y_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_z_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_energy_excitation_rate", 0.000198);
    setParDouble(this, "memory_energy_relaxation_rate", 0.00000198);
    setParDouble(this, "memory_completely_mixed_rate", 0);

    setParDouble(this, "h_gate_error_rate", 1. / 2000);
    setParDouble(this, "h_gate_x_error_ratio", 0);
    setParDouble(this, "h_gate_z_error_ratio", 0);
    setParDouble(this, "h_gate_y_error_ratio", 0);

    setParDouble(this, "x_gate_error_rate", 1. / 2000);
    setParDouble(this, "x_gate_x_error_ratio", 0);
    setParDouble(this, "x_gate_z_error_ratio", 0);
    setParDouble(this, "x_gate_y_error_ratio", 0);

    setParDouble(this, "z_gate_error_rate", 1. / 2000);
    setParDouble(this, "z_gate_x_error_ratio", 0);
    setParDouble(this, "z_gate_z_error_ratio", 0);
    setParDouble(this, "z_gate_y_error_ratio", 0);

    setParDouble(this, "cnot_gate_error_rate", 1. / 2000);
    setParDouble(this, "cnot_gate_ix_error_ratio", 1);
    setParDouble(this, "cnot_gate_xi_error_ratio", 1);
    setParDouble(this, "cnot_gate_xx_error_ratio", 1);
    setParDouble(this, "cnot_gate_iz_error_ratio", 1);
    setParDouble(this, "cnot_gate_zi_error_ratio", 1);
    setParDouble(this, "cnot_gate_zz_error_ratio", 1);
    setParDouble(this, "cnot_gate_iy_error_ratio", 1);
    setParDouble(this, "cnot_gate_yi_error_ratio", 1);
    setParDouble(this, "cnot_gate_yy_error_ratio", 1);

    setParDouble(this, "x_measurement_error_rate", 1. / 2000);
    setParDouble(this, "y_measurement_error_rate", 1. / 2000);
    setParDouble(this, "z_measurement_error_rate", 1. / 2000);

    setParInt(this, "stationary_qubit_address", 1);
    setParInt(this, "node_address", 1);
    setParInt(this, "qnic_address", 1);
    setParInt(this, "qnic_type", 0);
    setParInt(this, "qnic_index", 0);
    setParDouble(this, "emission_jittering_standard_deviation", 0.5);
    setParBool(this, "overwrite_backend_qubit_config", false);
  }
};

class StatQubitTest : public ::testing::Test {
 protected:
  void SetUp() {
    prepareSimulation();
    backend = new MockQuantumBackend();
    qubit = new StatQubitTarget(backend);
    qubit->fillParams();
  }
  void TearDown() { delete backend; }

  StatQubitTarget *qubit;
  MockQuantumBackend *backend;
};

TEST_F(StatQubitTest, init) {
  auto *sim = utils::prepareSimulation();
  auto *backend_qubit = new MockBackendQubit();
  auto *config = new IConfiguration();
  EXPECT_CALL(*backend, getDefaultConfiguration()).WillOnce(Return(ByMove(std::unique_ptr<IConfiguration>(config))));
  EXPECT_CALL(*backend, getQubit(NotNull(), NotNull())).WillOnce(Return(backend_qubit));
  EXPECT_CALL(*backend_qubit, setFree()).WillOnce(Return());
  sim->registerComponent(qubit);
  qubit->callInitialize();
  delete backend_qubit;
}

}  // namespace

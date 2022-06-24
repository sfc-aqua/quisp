#include "StationaryQubit.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <modules/common_types.h>
#include <test_utils/TestUtils.h>
#include <cmath>
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <unsupported/Eigen/MatrixFunctions>
#include "backends/Backends.h"
#include "backends/ErrorTracking/Configuration.h"
#include "backends/interfaces/IConfiguration.h"
#include "backends/interfaces/IQuantumBackend.h"
#include "omnetpp/cmessage.h"
#include "test_utils/Simulation.h"
#include "test_utils/UtilFunctions.h"
#include "test_utils/mock_backends/MockQuantumBackend.h"

using namespace testing;
using namespace quisp::modules;
using namespace quisp::modules::common;
using namespace quisp_test;
using namespace Eigen;
using namespace omnetpp;
using quisp::backends::ErrorTrackingConfiguration;

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
  using StationaryQubit::backend;
  using StationaryQubit::finish;
  using StationaryQubit::handleMessage;
  using StationaryQubit::initialize;
  using StationaryQubit::par;
  using StationaryQubit::prepareBackendQubitConfiguration;
  StatQubitTarget(IQuantumBackend *backend) : StationaryQubit() {
    setComponentType(new TestModuleType("test qubit"));
    provider.setStrategy(std::make_unique<Strategy>(backend));
    toLensGate = new TestGate(this, "tolens_quantum_port$o");
  }
  void reset() { setFree(true); }
  void fillParams() {
    // see networks/omnetpp.ini
    setParDouble(this, "emission_success_probability", 0.5);
    setParDouble(this, "memory_X_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_Y_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_Z_error_rate", 1.11111111e-7);
    setParDouble(this, "memory_energy_excitation_rate", 0.000198);
    setParDouble(this, "memory_energy_relaxation_rate", 0.00000198);
    setParDouble(this, "memory_completely_mixed_rate", 0);

    setParDouble(this, "Hgate_error_rate", 1. / 2000);
    setParDouble(this, "Hgate_X_error_ratio", 0);
    setParDouble(this, "Hgate_Z_error_ratio", 0);
    setParDouble(this, "Hgate_Y_error_ratio", 0);

    setParDouble(this, "Xgate_error_rate", 1. / 2000);
    setParDouble(this, "Xgate_X_error_ratio", 0);
    setParDouble(this, "Xgate_Z_error_ratio", 0);
    setParDouble(this, "Xgate_Y_error_ratio", 0);

    setParDouble(this, "Zgate_error_rate", 1. / 2000);
    setParDouble(this, "Zgate_X_error_ratio", 0);
    setParDouble(this, "Zgate_Z_error_ratio", 0);
    setParDouble(this, "Zgate_Y_error_ratio", 0);

    setParDouble(this, "CNOTgate_error_rate", 1. / 2000);
    setParDouble(this, "CNOTgate_IX_error_ratio", 1);
    setParDouble(this, "CNOTgate_XI_error_ratio", 1);
    setParDouble(this, "CNOTgate_XX_error_ratio", 1);
    setParDouble(this, "CNOTgate_IZ_error_ratio", 1);
    setParDouble(this, "CNOTgate_ZI_error_ratio", 1);
    setParDouble(this, "CNOTgate_ZZ_error_ratio", 1);
    setParDouble(this, "CNOTgate_IY_error_ratio", 1);
    setParDouble(this, "CNOTgate_YI_error_ratio", 1);
    setParDouble(this, "CNOTgate_YY_error_ratio", 1);

    setParDouble(this, "X_measurement_error_rate", 1. / 2000);
    setParDouble(this, "Y_measurement_error_rate", 1. / 2000);
    setParDouble(this, "Z_measurement_error_rate", 1. / 2000);

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
    setParBool(this, "overwrite_backend_qubit_config", false);
  }

  TestGate *toLensGate;
  cGate *gate(const char *gatename, int index = -1) override {
    if (strcmp("tolens_quantum_port$o", gatename) != 0) {
      throw std::runtime_error("unexpected gate name");
    }
    return toLensGate;
  }
};

class StatQubitTest : public ::testing::Test {
 protected:
  void SetUp() {
    sim = prepareSimulation();
    backend = new MockQuantumBackend();
    qubit = new StatQubitTarget(backend);
    qubit->fillParams();
    sim->registerComponent(qubit);
  }
  void TearDown() { delete backend; }

  StatQubitTarget *qubit;
  MockQuantumBackend *backend;
  simulation::TestSimulation *sim;
};

TEST_F(StatQubitTest, init) {
  auto *backend_qubit = new MockBackendQubit();
  auto *config = new IConfiguration();
  EXPECT_CALL(*backend, getDefaultConfiguration()).WillOnce(Return(ByMove(std::unique_ptr<IConfiguration>(config))));
  EXPECT_CALL(*backend, getQubit(NotNull(), NotNull())).WillOnce(Return(backend_qubit));
  EXPECT_CALL(*backend_qubit, setFree()).WillOnce(Return());
  qubit->callInitialize();
  delete backend_qubit;
}

TEST_F(StatQubitTest, errorTrackingQubitConfigurationOverwrite) {
  auto *config = new ErrorTrackingConfiguration();
  setParDouble(qubit, "CNOTgate_error_rate", 0.01);
  setParDouble(qubit, "CNOTgate_IX_error_ratio", 0.02);
  setParDouble(qubit, "CNOTgate_XI_error_ratio", 0.03);
  setParDouble(qubit, "CNOTgate_XX_error_ratio", 0.04);
  setParDouble(qubit, "CNOTgate_IZ_error_ratio", 0.05);
  setParDouble(qubit, "CNOTgate_ZI_error_ratio", 0.06);
  setParDouble(qubit, "CNOTgate_ZZ_error_ratio", 0.07);
  setParDouble(qubit, "CNOTgate_IY_error_ratio", 0.08);
  setParDouble(qubit, "CNOTgate_YI_error_ratio", 0.09);
  setParDouble(qubit, "CNOTgate_YY_error_ratio", 0.10);

  setParDouble(qubit, "Hgate_error_rate", 0.11);
  setParDouble(qubit, "Hgate_X_error_ratio", 0.12);
  setParDouble(qubit, "Hgate_Y_error_ratio", 0.13);
  setParDouble(qubit, "Hgate_Z_error_ratio", 0.14);

  setParDouble(qubit, "Xgate_error_rate", 0.15);
  setParDouble(qubit, "Xgate_X_error_ratio", 0.16);
  setParDouble(qubit, "Xgate_Y_error_ratio", 0.17);
  setParDouble(qubit, "Xgate_Z_error_ratio", 0.18);

  setParDouble(qubit, "Zgate_error_rate", 0.19);
  setParDouble(qubit, "Zgate_X_error_ratio", 0.20);
  setParDouble(qubit, "Zgate_Y_error_ratio", 0.21);
  setParDouble(qubit, "Zgate_Z_error_ratio", 0.22);

  setParDouble(qubit, "X_measurement_error_rate", 0.23);
  setParDouble(qubit, "Y_measurement_error_rate", 0.24);
  setParDouble(qubit, "Z_measurement_error_rate", 0.25);

  setParDouble(qubit, "memory_X_error_rate", 0.26);
  setParDouble(qubit, "memory_Y_error_rate", 0.27);
  setParDouble(qubit, "memory_Z_error_rate", 0.28);
  setParDouble(qubit, "memory_energy_excitation_rate", 0.29);
  setParDouble(qubit, "memory_energy_relaxation_rate", 0.30);
  setParDouble(qubit, "memory_completely_mixed_rate", 0.31);

  EXPECT_NE(config->cnot_gate_err_rate, qubit->par("CNOTgate_error_rate").doubleValue());
  EXPECT_NE(config->cnot_gate_ix_err_ratio, qubit->par("CNOTgate_IX_error_ratio").doubleValue());
  EXPECT_NE(config->cnot_gate_xi_err_ratio, qubit->par("CNOTgate_XI_error_ratio").doubleValue());
  EXPECT_NE(config->cnot_gate_xx_err_ratio, qubit->par("CNOTgate_XX_error_ratio").doubleValue());
  EXPECT_NE(config->cnot_gate_iz_err_ratio, qubit->par("CNOTgate_IZ_error_ratio").doubleValue());
  EXPECT_NE(config->cnot_gate_zi_err_ratio, qubit->par("CNOTgate_ZI_error_ratio").doubleValue());
  EXPECT_NE(config->cnot_gate_zz_err_ratio, qubit->par("CNOTgate_ZZ_error_ratio").doubleValue());
  EXPECT_NE(config->cnot_gate_iy_err_ratio, qubit->par("CNOTgate_IY_error_ratio").doubleValue());
  EXPECT_NE(config->cnot_gate_yi_err_ratio, qubit->par("CNOTgate_YI_error_ratio").doubleValue());
  EXPECT_NE(config->cnot_gate_yy_err_ratio, qubit->par("CNOTgate_YY_error_ratio").doubleValue());

  EXPECT_NE(config->h_gate_err_rate, qubit->par("Hgate_error_rate").doubleValue());
  EXPECT_NE(config->h_gate_x_err_ratio, qubit->par("Hgate_X_error_ratio").doubleValue());
  EXPECT_NE(config->h_gate_y_err_ratio, qubit->par("Hgate_Y_error_ratio").doubleValue());
  EXPECT_NE(config->h_gate_z_err_ratio, qubit->par("Hgate_Z_error_ratio").doubleValue());

  EXPECT_NE(config->x_gate_err_rate, qubit->par("Xgate_error_rate").doubleValue());
  EXPECT_NE(config->x_gate_x_err_ratio, qubit->par("Xgate_X_error_ratio").doubleValue());
  EXPECT_NE(config->x_gate_y_err_ratio, qubit->par("Xgate_Y_error_ratio").doubleValue());
  EXPECT_NE(config->x_gate_z_err_ratio, qubit->par("Xgate_Z_error_ratio").doubleValue());

  EXPECT_NE(config->z_gate_err_rate, qubit->par("Zgate_error_rate").doubleValue());
  EXPECT_NE(config->z_gate_x_err_ratio, qubit->par("Zgate_X_error_ratio").doubleValue());
  EXPECT_NE(config->z_gate_y_err_ratio, qubit->par("Zgate_Y_error_ratio").doubleValue());
  EXPECT_NE(config->z_gate_z_err_ratio, qubit->par("Zgate_Z_error_ratio").doubleValue());

  EXPECT_NE(config->measurement_x_err_rate, qubit->par("X_measurement_error_rate").doubleValue());
  EXPECT_NE(config->measurement_y_err_rate, qubit->par("Y_measurement_error_rate").doubleValue());
  EXPECT_NE(config->measurement_z_err_rate, qubit->par("Z_measurement_error_rate").doubleValue());

  EXPECT_NE(config->memory_x_err_rate, qubit->par("memory_X_error_rate").doubleValue());
  EXPECT_NE(config->memory_y_err_rate, qubit->par("memory_Y_error_rate").doubleValue());
  EXPECT_NE(config->memory_z_err_rate, qubit->par("memory_Z_error_rate").doubleValue());
  EXPECT_NE(config->memory_excitation_rate, qubit->par("memory_energy_excitation_rate").doubleValue());
  EXPECT_NE(config->memory_relaxation_rate, qubit->par("memory_energy_relaxation_rate").doubleValue());
  EXPECT_NE(config->memory_completely_mixed_rate, qubit->par("memory_completely_mixed_rate").doubleValue());

  // usually qubit->backend is assigned during initialize()
  qubit->backend = backend;

  EXPECT_CALL(*backend, getDefaultConfiguration()).WillOnce(Return(ByMove(std::unique_ptr<IConfiguration>(config))));
  auto new_conf = qubit->prepareBackendQubitConfiguration(true);

  EXPECT_EQ(config->cnot_gate_err_rate, qubit->par("CNOTgate_error_rate").doubleValue());
  EXPECT_EQ(config->cnot_gate_ix_err_ratio, qubit->par("CNOTgate_IX_error_ratio").doubleValue());
  EXPECT_EQ(config->cnot_gate_xi_err_ratio, qubit->par("CNOTgate_XI_error_ratio").doubleValue());
  EXPECT_EQ(config->cnot_gate_xx_err_ratio, qubit->par("CNOTgate_XX_error_ratio").doubleValue());
  EXPECT_EQ(config->cnot_gate_iz_err_ratio, qubit->par("CNOTgate_IZ_error_ratio").doubleValue());
  EXPECT_EQ(config->cnot_gate_zi_err_ratio, qubit->par("CNOTgate_ZI_error_ratio").doubleValue());
  EXPECT_EQ(config->cnot_gate_zz_err_ratio, qubit->par("CNOTgate_ZZ_error_ratio").doubleValue());
  EXPECT_EQ(config->cnot_gate_iy_err_ratio, qubit->par("CNOTgate_IY_error_ratio").doubleValue());
  EXPECT_EQ(config->cnot_gate_yi_err_ratio, qubit->par("CNOTgate_YI_error_ratio").doubleValue());
  EXPECT_EQ(config->cnot_gate_yy_err_ratio, qubit->par("CNOTgate_YY_error_ratio").doubleValue());

  EXPECT_EQ(config->h_gate_err_rate, qubit->par("Hgate_error_rate").doubleValue());
  EXPECT_EQ(config->h_gate_x_err_ratio, qubit->par("Hgate_X_error_ratio").doubleValue());
  EXPECT_EQ(config->h_gate_y_err_ratio, qubit->par("Hgate_Y_error_ratio").doubleValue());
  EXPECT_EQ(config->h_gate_z_err_ratio, qubit->par("Hgate_Z_error_ratio").doubleValue());

  EXPECT_EQ(config->x_gate_err_rate, qubit->par("Xgate_error_rate").doubleValue());
  EXPECT_EQ(config->x_gate_x_err_ratio, qubit->par("Xgate_X_error_ratio").doubleValue());
  EXPECT_EQ(config->x_gate_y_err_ratio, qubit->par("Xgate_Y_error_ratio").doubleValue());
  EXPECT_EQ(config->x_gate_z_err_ratio, qubit->par("Xgate_Z_error_ratio").doubleValue());

  EXPECT_EQ(config->z_gate_err_rate, qubit->par("Zgate_error_rate").doubleValue());
  EXPECT_EQ(config->z_gate_x_err_ratio, qubit->par("Zgate_X_error_ratio").doubleValue());
  EXPECT_EQ(config->z_gate_y_err_ratio, qubit->par("Zgate_Y_error_ratio").doubleValue());
  EXPECT_EQ(config->z_gate_z_err_ratio, qubit->par("Zgate_Z_error_ratio").doubleValue());

  EXPECT_EQ(config->measurement_x_err_rate, qubit->par("X_measurement_error_rate").doubleValue());
  EXPECT_EQ(config->measurement_y_err_rate, qubit->par("Y_measurement_error_rate").doubleValue());
  EXPECT_EQ(config->measurement_z_err_rate, qubit->par("Z_measurement_error_rate").doubleValue());

  EXPECT_EQ(config->memory_x_err_rate, qubit->par("memory_X_error_rate").doubleValue());
  EXPECT_EQ(config->memory_y_err_rate, qubit->par("memory_Y_error_rate").doubleValue());
  EXPECT_EQ(config->memory_z_err_rate, qubit->par("memory_Z_error_rate").doubleValue());
  EXPECT_EQ(config->memory_excitation_rate, qubit->par("memory_energy_excitation_rate").doubleValue());
  EXPECT_EQ(config->memory_relaxation_rate, qubit->par("memory_energy_relaxation_rate").doubleValue());
  EXPECT_EQ(config->memory_completely_mixed_rate, qubit->par("memory_completely_mixed_rate").doubleValue());
}

TEST_F(StatQubitTest, emissionFailedPhotonLost) {
  sim->setContext(qubit);
  auto *msg = new PhotonicQubit();
  qubit->emission_success_probability = 0;
  EXPECT_EQ(qubit->toLensGate->messages.size(), 0);
  qubit->handleMessage(msg);
  EXPECT_EQ(qubit->toLensGate->messages.size(), 1);
  auto *new_msg = qubit->toLensGate->messages.at(0);
  ASSERT_NE(new_msg, nullptr);
  EXPECT_NE(new_msg, msg);

  auto *photon = dynamic_cast<PhotonicQubit *>(new_msg);
  ASSERT_NE(photon, nullptr);
  EXPECT_TRUE(photon->getPhotonLost());
}

TEST_F(StatQubitTest, emissionSuccess) {
  sim->setContext(qubit);
  auto *msg = new PhotonicQubit();
  qubit->emission_success_probability = 1;
  EXPECT_EQ(qubit->toLensGate->messages.size(), 0);
  qubit->handleMessage(msg);
  EXPECT_EQ(qubit->toLensGate->messages.size(), 1);
  auto *new_msg = qubit->toLensGate->messages.at(0);
  ASSERT_NE(new_msg, nullptr);

  auto *photon = dynamic_cast<PhotonicQubit *>(new_msg);
  ASSERT_NE(photon, nullptr);
  EXPECT_FALSE(photon->getPhotonLost());
}

TEST_F(StatQubitTest, finish) {
  ASSERT_NO_THROW({ qubit->finish(); });
}

}  // namespace

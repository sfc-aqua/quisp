#include "StationaryQubit.h"
#include <backends/interfaces/IQubit.h>
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
#include "backends/interfaces/IConfiguration.h"
#include "backends/interfaces/IQuantumBackend.h"
#include "omnetpp/cmessage.h"
#include "test_utils/Simulation.h"
#include "test_utils/TestUtilFunctions.h"
#include "test_utils/mock_backends/MockQuantumBackend.h"

using quisp::backends::abstract::IQubit;

using namespace testing;
using namespace quisp::modules;
using namespace quisp::modules::common;
using namespace quisp_test;
using namespace Eigen;
using namespace omnetpp;
using quisp::backends::StationaryQubitConfiguration;
using quisp::messages::PhotonicQubit;

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
    toLensGate = new TestGate(this, "tolens_quantum_port");
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
    setParDouble(this, "cnot_gate_iy_error_ratio", 1);
    setParDouble(this, "cnot_gate_iz_error_ratio", 1);
    setParDouble(this, "cnot_gate_xi_error_ratio", 1);
    setParDouble(this, "cnot_gate_xx_error_ratio", 1);
    setParDouble(this, "cnot_gate_xy_error_ratio", 1);
    setParDouble(this, "cnot_gate_xz_error_ratio", 1);
    setParDouble(this, "cnot_gate_yi_error_ratio", 1);
    setParDouble(this, "cnot_gate_yx_error_ratio", 1);
    setParDouble(this, "cnot_gate_yy_error_ratio", 1);
    setParDouble(this, "cnot_gate_yz_error_ratio", 1);
    setParDouble(this, "cnot_gate_zi_error_ratio", 1);
    setParDouble(this, "cnot_gate_zx_error_ratio", 1);
    setParDouble(this, "cnot_gate_zy_error_ratio", 1);
    setParDouble(this, "cnot_gate_zz_error_ratio", 1);

    setParDouble(this, "x_measurement_error_rate", 1. / 2000);
    setParDouble(this, "y_measurement_error_rate", 1. / 2000);
    setParDouble(this, "z_measurement_error_rate", 1. / 2000);

    setParInt(this, "stationary_qubit_address", 1);
    setParInt(this, "node_address", 1);
    setParInt(this, "qnic_address", 1);
    setParInt(this, "qnic_type", 0);
    setParInt(this, "qnic_index", 0);
    setParDouble(this, "emission_jittering_standard_deviation", 0.5);
  }

  TestGate *toLensGate;
  cGate *gate(const char *gatename, int index = -1) override {
    if (strcmp("tolens_quantum_port", gatename) != 0) {
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
  EXPECT_CALL(*backend, createQubit(NotNull(), NotNull())).WillOnce(Return(backend_qubit));
  EXPECT_CALL(*backend_qubit, setFree()).WillOnce(Return());
  qubit->callInitialize();
  delete backend_qubit;
}

TEST_F(StatQubitTest, StationaryQubitConfigurationOverwrite) {
  auto *config = new StationaryQubitConfiguration();
  setParDouble(qubit, "cnot_gate_error_rate", 0.01);
  setParDouble(qubit, "cnot_gate_ix_error_ratio", 0.02);
  setParDouble(qubit, "cnot_gate_iy_error_ratio", 0.03);
  setParDouble(qubit, "cnot_gate_iz_error_ratio", 0.04);
  setParDouble(qubit, "cnot_gate_xi_error_ratio", 0.05);
  setParDouble(qubit, "cnot_gate_xx_error_ratio", 0.06);
  setParDouble(qubit, "cnot_gate_xy_error_ratio", 0.07);
  setParDouble(qubit, "cnot_gate_xz_error_ratio", 0.08);
  setParDouble(qubit, "cnot_gate_yi_error_ratio", 0.09);
  setParDouble(qubit, "cnot_gate_yx_error_ratio", 0.10);
  setParDouble(qubit, "cnot_gate_yy_error_ratio", 0.11);
  setParDouble(qubit, "cnot_gate_yz_error_ratio", 0.12);
  setParDouble(qubit, "cnot_gate_zi_error_ratio", 0.13);
  setParDouble(qubit, "cnot_gate_zx_error_ratio", 0.14);
  setParDouble(qubit, "cnot_gate_zy_error_ratio", 0.15);
  setParDouble(qubit, "cnot_gate_zz_error_ratio", 0.16);

  setParDouble(qubit, "h_gate_error_rate", 0.11);
  setParDouble(qubit, "h_gate_x_error_ratio", 0.12);
  setParDouble(qubit, "h_gate_y_error_ratio", 0.13);
  setParDouble(qubit, "h_gate_z_error_ratio", 0.14);

  setParDouble(qubit, "x_gate_error_rate", 0.15);
  setParDouble(qubit, "x_gate_x_error_ratio", 0.16);
  setParDouble(qubit, "x_gate_y_error_ratio", 0.17);
  setParDouble(qubit, "x_gate_z_error_ratio", 0.18);

  setParDouble(qubit, "z_gate_error_rate", 0.19);
  setParDouble(qubit, "z_gate_x_error_ratio", 0.20);
  setParDouble(qubit, "z_gate_y_error_ratio", 0.21);
  setParDouble(qubit, "z_gate_z_error_ratio", 0.22);

  setParDouble(qubit, "x_measurement_error_rate", 0.23);
  setParDouble(qubit, "y_measurement_error_rate", 0.24);
  setParDouble(qubit, "z_measurement_error_rate", 0.25);

  setParDouble(qubit, "memory_x_error_rate", 0.26);
  setParDouble(qubit, "memory_y_error_rate", 0.27);
  setParDouble(qubit, "memory_z_error_rate", 0.28);
  setParDouble(qubit, "memory_energy_excitation_rate", 0.29);
  setParDouble(qubit, "memory_energy_relaxation_rate", 0.30);
  setParDouble(qubit, "memory_completely_mixed_rate", 0.31);

  EXPECT_NE(config->cnot_gate_err_rate, qubit->par("cnot_gate_error_rate").doubleValue());
  EXPECT_NE(config->cnot_gate_ix_err_ratio, qubit->par("cnot_gate_ix_error_ratio").doubleValue());
  EXPECT_NE(config->cnot_gate_xi_err_ratio, qubit->par("cnot_gate_xi_error_ratio").doubleValue());
  EXPECT_NE(config->cnot_gate_xx_err_ratio, qubit->par("cnot_gate_xx_error_ratio").doubleValue());
  EXPECT_NE(config->cnot_gate_iz_err_ratio, qubit->par("cnot_gate_iz_error_ratio").doubleValue());
  EXPECT_NE(config->cnot_gate_zi_err_ratio, qubit->par("cnot_gate_zi_error_ratio").doubleValue());
  EXPECT_NE(config->cnot_gate_zz_err_ratio, qubit->par("cnot_gate_zz_error_ratio").doubleValue());
  EXPECT_NE(config->cnot_gate_iy_err_ratio, qubit->par("cnot_gate_iy_error_ratio").doubleValue());
  EXPECT_NE(config->cnot_gate_yi_err_ratio, qubit->par("cnot_gate_yi_error_ratio").doubleValue());
  EXPECT_NE(config->cnot_gate_yy_err_ratio, qubit->par("cnot_gate_yy_error_ratio").doubleValue());

  EXPECT_NE(config->h_gate_err_rate, qubit->par("h_gate_error_rate").doubleValue());
  EXPECT_NE(config->h_gate_x_err_ratio, qubit->par("h_gate_x_error_ratio").doubleValue());
  EXPECT_NE(config->h_gate_y_err_ratio, qubit->par("h_gate_y_error_ratio").doubleValue());
  EXPECT_NE(config->h_gate_z_err_ratio, qubit->par("h_gate_z_error_ratio").doubleValue());

  EXPECT_NE(config->x_gate_err_rate, qubit->par("x_gate_error_rate").doubleValue());
  EXPECT_NE(config->x_gate_x_err_ratio, qubit->par("x_gate_x_error_ratio").doubleValue());
  EXPECT_NE(config->x_gate_y_err_ratio, qubit->par("x_gate_y_error_ratio").doubleValue());
  EXPECT_NE(config->x_gate_z_err_ratio, qubit->par("x_gate_z_error_ratio").doubleValue());

  EXPECT_NE(config->z_gate_err_rate, qubit->par("z_gate_error_rate").doubleValue());
  EXPECT_NE(config->z_gate_x_err_ratio, qubit->par("z_gate_x_error_ratio").doubleValue());
  EXPECT_NE(config->z_gate_y_err_ratio, qubit->par("z_gate_y_error_ratio").doubleValue());
  EXPECT_NE(config->z_gate_z_err_ratio, qubit->par("z_gate_z_error_ratio").doubleValue());

  EXPECT_NE(config->measurement_x_err_rate, qubit->par("x_measurement_error_rate").doubleValue());
  EXPECT_NE(config->measurement_y_err_rate, qubit->par("y_measurement_error_rate").doubleValue());
  EXPECT_NE(config->measurement_z_err_rate, qubit->par("z_measurement_error_rate").doubleValue());

  EXPECT_NE(config->memory_x_err_rate, qubit->par("memory_x_error_rate").doubleValue());
  EXPECT_NE(config->memory_y_err_rate, qubit->par("memory_y_error_rate").doubleValue());
  EXPECT_NE(config->memory_z_err_rate, qubit->par("memory_z_error_rate").doubleValue());
  EXPECT_NE(config->memory_excitation_rate, qubit->par("memory_energy_excitation_rate").doubleValue());
  EXPECT_NE(config->memory_relaxation_rate, qubit->par("memory_energy_relaxation_rate").doubleValue());
  EXPECT_NE(config->memory_completely_mixed_rate, qubit->par("memory_completely_mixed_rate").doubleValue());

  // usually qubit->backend is assigned during initialize()
  qubit->backend = backend;

  EXPECT_CALL(*backend, getDefaultConfiguration()).WillOnce(Return(ByMove(std::unique_ptr<IConfiguration>(config))));
  auto new_conf = qubit->prepareBackendQubitConfiguration(true);

  EXPECT_EQ(config->cnot_gate_err_rate, qubit->par("cnot_gate_error_rate").doubleValue());
  EXPECT_EQ(config->cnot_gate_ix_err_ratio, qubit->par("cnot_gate_ix_error_ratio").doubleValue());
  EXPECT_EQ(config->cnot_gate_xi_err_ratio, qubit->par("cnot_gate_xi_error_ratio").doubleValue());
  EXPECT_EQ(config->cnot_gate_xx_err_ratio, qubit->par("cnot_gate_xx_error_ratio").doubleValue());
  EXPECT_EQ(config->cnot_gate_iz_err_ratio, qubit->par("cnot_gate_iz_error_ratio").doubleValue());
  EXPECT_EQ(config->cnot_gate_zi_err_ratio, qubit->par("cnot_gate_zi_error_ratio").doubleValue());
  EXPECT_EQ(config->cnot_gate_zz_err_ratio, qubit->par("cnot_gate_zz_error_ratio").doubleValue());
  EXPECT_EQ(config->cnot_gate_iy_err_ratio, qubit->par("cnot_gate_iy_error_ratio").doubleValue());
  EXPECT_EQ(config->cnot_gate_yi_err_ratio, qubit->par("cnot_gate_yi_error_ratio").doubleValue());
  EXPECT_EQ(config->cnot_gate_yy_err_ratio, qubit->par("cnot_gate_yy_error_ratio").doubleValue());

  EXPECT_EQ(config->h_gate_err_rate, qubit->par("h_gate_error_rate").doubleValue());
  EXPECT_EQ(config->h_gate_x_err_ratio, qubit->par("h_gate_x_error_ratio").doubleValue());
  EXPECT_EQ(config->h_gate_y_err_ratio, qubit->par("h_gate_y_error_ratio").doubleValue());
  EXPECT_EQ(config->h_gate_z_err_ratio, qubit->par("h_gate_z_error_ratio").doubleValue());

  EXPECT_EQ(config->x_gate_err_rate, qubit->par("x_gate_error_rate").doubleValue());
  EXPECT_EQ(config->x_gate_x_err_ratio, qubit->par("x_gate_x_error_ratio").doubleValue());
  EXPECT_EQ(config->x_gate_y_err_ratio, qubit->par("x_gate_y_error_ratio").doubleValue());
  EXPECT_EQ(config->x_gate_z_err_ratio, qubit->par("x_gate_z_error_ratio").doubleValue());

  EXPECT_EQ(config->z_gate_err_rate, qubit->par("z_gate_error_rate").doubleValue());
  EXPECT_EQ(config->z_gate_x_err_ratio, qubit->par("z_gate_x_error_ratio").doubleValue());
  EXPECT_EQ(config->z_gate_y_err_ratio, qubit->par("z_gate_y_error_ratio").doubleValue());
  EXPECT_EQ(config->z_gate_z_err_ratio, qubit->par("z_gate_z_error_ratio").doubleValue());

  EXPECT_EQ(config->measurement_x_err_rate, qubit->par("x_measurement_error_rate").doubleValue());
  EXPECT_EQ(config->measurement_y_err_rate, qubit->par("y_measurement_error_rate").doubleValue());
  EXPECT_EQ(config->measurement_z_err_rate, qubit->par("z_measurement_error_rate").doubleValue());

  EXPECT_EQ(config->memory_x_err_rate, qubit->par("memory_x_error_rate").doubleValue());
  EXPECT_EQ(config->memory_y_err_rate, qubit->par("memory_y_error_rate").doubleValue());
  EXPECT_EQ(config->memory_z_err_rate, qubit->par("memory_z_error_rate").doubleValue());
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
  EXPECT_TRUE(photon->isLost());
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
  EXPECT_FALSE(photon->isLost());
}

TEST_F(StatQubitTest, finish) {
  ASSERT_NO_THROW({ qubit->finish(); });
}

}  // namespace

#include "Backend.h"
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include "modules/common_types.h"

namespace {
using namespace quisp_test;
using OriginalBackendContainer = quisp::modules::backend::BackendContainer;
using quisp::modules::backend::ErrorTrackingBackend;
using quisp::modules::backend::ErrorTrackingConfiguration;

class BackendContainer : public OriginalBackendContainer {
 public:
  using OriginalBackendContainer::backend;

  BackendContainer() : OriginalBackendContainer() { setComponentType(new TestModuleType("test qnode")); }
  ~BackendContainer() override {}
};

class BackendContainerTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    auto *sim = utils::prepareSimulation();
    backend = new BackendContainer();
    setParDouble(backend, "x_measurement_error_rate", .02);
    setParDouble(backend, "y_measurement_error_rate", .03);
    setParDouble(backend, "z_measurement_error_rate", .04);
    setParDouble(backend, "h_gate_error_rate", .05);
    setParDouble(backend, "h_gate_x_error_ratio", .06);
    setParDouble(backend, "h_gate_y_error_ratio", .07);
    setParDouble(backend, "h_gate_z_error_ratio", .08);
    setParDouble(backend, "x_gate_error_rate", .06);
    setParDouble(backend, "x_gate_x_error_ratio", .07);
    setParDouble(backend, "x_gate_y_error_ratio", .08);
    setParDouble(backend, "x_gate_z_error_ratio", .09);
    setParDouble(backend, "z_gate_error_rate", .10);
    setParDouble(backend, "z_gate_x_error_ratio", .11);
    setParDouble(backend, "z_gate_y_error_ratio", .12);
    setParDouble(backend, "z_gate_z_error_ratio", .13);
    setParDouble(backend, "cnot_gate_error_rate", .14);
    setParDouble(backend, "cnot_gate_ix_error_ratio", .15);
    setParDouble(backend, "cnot_gate_xi_error_ratio", .16);
    setParDouble(backend, "cnot_gate_xx_error_ratio", .17);
    setParDouble(backend, "cnot_gate_iy_error_ratio", .18);
    setParDouble(backend, "cnot_gate_yi_error_ratio", .19);
    setParDouble(backend, "cnot_gate_yy_error_ratio", .20);
    setParDouble(backend, "cnot_gate_iz_error_ratio", .21);
    setParDouble(backend, "cnot_gate_zi_error_ratio", .22);
    setParDouble(backend, "cnot_gate_zz_error_ratio", .23);
    setParDouble(backend, "memory_x_error_rate", .24);
    setParDouble(backend, "memory_y_error_rate", .25);
    setParDouble(backend, "memory_z_error_rate", .26);
    setParDouble(backend, "memory_energy_excitation_rate", .27);
    setParDouble(backend, "memory_energy_relaxation_rate", .28);
    setParDouble(backend, "memory_completely_mixed_rate", .29);
    sim->registerComponent(backend);
  }
  virtual void TearDown() {}

  // managed by cSimulation, so we don't need to use unique_ptr nor delete manually.
  BackendContainer *backend;
};

TEST_F(BackendContainerTest, constructor) { BackendContainer backend; }

TEST_F(BackendContainerTest, callInitialize) {
  setParStr(backend, "backendType", "ErrorTrackingBackend");
  EXPECT_EQ(backend->backend, nullptr);
  backend->callInitialize();
  EXPECT_NE(backend->backend, nullptr);
}

TEST_F(BackendContainerTest, callInitializeWithInvalidBackend) {
  setParStr(backend, "backendType", "SomeInvalidBackend");
  EXPECT_EQ(backend->backend, nullptr);
  EXPECT_THROW(backend->callInitialize(), omnetpp::cRuntimeError);
}

TEST_F(BackendContainerTest, getQuantumBackend) {
  setParStr(backend, "backendType", "ErrorTrackingBackend");
  backend->callInitialize();
  ASSERT_NE(backend->backend, nullptr);
  auto *b = backend->getQuantumBackend();
  ASSERT_NE(b, nullptr);
  auto *et_backend = dynamic_cast<ErrorTrackingBackend *>(b);
  EXPECT_NE(et_backend, nullptr);
}

TEST_F(BackendContainerTest, getBackendConfiguration) {
  setParStr(backend, "backendType", "ErrorTrackingBackend");
  backend->callInitialize();
  ASSERT_NE(backend->backend, nullptr);
  auto *b = backend->getQuantumBackend();
  ASSERT_NE(b, nullptr);
  auto *et_backend = dynamic_cast<ErrorTrackingBackend *>(b);

  auto conf = et_backend->getDefaultConfiguration();
  ASSERT_NE(conf, nullptr);
  auto et_conf = dynamic_cast<ErrorTrackingConfiguration *>(conf.get());
  ASSERT_NE(et_conf, nullptr);
}

TEST_F(BackendContainerTest, getCopyOfBackendConfiguration) {
  setParStr(backend, "backendType", "ErrorTrackingBackend");
  backend->callInitialize();
  ASSERT_NE(backend->backend, nullptr);
  auto *b = backend->getQuantumBackend();
  ASSERT_NE(b, nullptr);
  auto *et_backend = dynamic_cast<ErrorTrackingBackend *>(b);

  auto conf = et_backend->getDefaultConfiguration();
  auto et_conf = dynamic_cast<ErrorTrackingConfiguration *>(conf.get());

  auto conf2 = et_backend->getDefaultConfiguration();
  auto et_conf2 = dynamic_cast<ErrorTrackingConfiguration *>(conf2.get());

  // confirm et_conf and et_conf2 are different intstances
  et_conf->cnot_gate_err_rate = 10;
  EXPECT_NE(et_conf->cnot_gate_err_rate, et_conf2->cnot_gate_err_rate);
  EXPECT_NE(et_conf, et_conf2);
}
}  // namespace

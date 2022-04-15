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
    setParDouble(backend, "X_measurement_error_rate", .02);
    setParDouble(backend, "Y_measurement_error_rate", .03);
    setParDouble(backend, "Z_measurement_error_rate", .04);
    setParDouble(backend, "Hgate_error_rate", .05);
    setParDouble(backend, "Hgate_X_error_ratio", .06);
    setParDouble(backend, "Hgate_Y_error_ratio", .07);
    setParDouble(backend, "Hgate_Z_error_ratio", .08);
    setParDouble(backend, "Xgate_error_rate", .06);
    setParDouble(backend, "Xgate_X_error_ratio", .07);
    setParDouble(backend, "Xgate_Y_error_ratio", .08);
    setParDouble(backend, "Xgate_Z_error_ratio", .09);
    setParDouble(backend, "Zgate_error_rate", .10);
    setParDouble(backend, "Zgate_X_error_ratio", .11);
    setParDouble(backend, "Zgate_Y_error_ratio", .12);
    setParDouble(backend, "Zgate_Z_error_ratio", .13);
    setParDouble(backend, "CNOTgate_error_rate", .14);
    setParDouble(backend, "CNOTgate_IX_error_ratio", .15);
    setParDouble(backend, "CNOTgate_XI_error_ratio", .16);
    setParDouble(backend, "CNOTgate_XX_error_ratio", .17);
    setParDouble(backend, "CNOTgate_IY_error_ratio", .18);
    setParDouble(backend, "CNOTgate_YI_error_ratio", .19);
    setParDouble(backend, "CNOTgate_YY_error_ratio", .20);
    setParDouble(backend, "CNOTgate_IZ_error_ratio", .21);
    setParDouble(backend, "CNOTgate_ZI_error_ratio", .22);
    setParDouble(backend, "CNOTgate_ZZ_error_ratio", .23);
    setParDouble(backend, "memory_X_error_rate", .24);
    setParDouble(backend, "memory_Y_error_rate", .25);
    setParDouble(backend, "memory_Z_error_rate", .26);
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

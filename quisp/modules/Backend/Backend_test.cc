#include "Backend.h"
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include "modules/common_types.h"

namespace {
using namespace quisp_test;
using OriginalBackendContainer = quisp::modules::backend::BackendContainer;
using quisp::modules::backend::ErrorTrackingBackend;

class BackendContainer : public OriginalBackendContainer {
 public:
  using OriginalBackendContainer::backend;

  BackendContainer() : OriginalBackendContainer() { setComponentType(new TestModuleType("test qnode")); }
  ~BackendContainer() override {}
};

TEST(BackendContainer, constructor) { BackendContainer backend; }

TEST(BackendContainer, callInitialize) {
  auto *sim = utils::prepareSimulation();
  BackendContainer *backend = new BackendContainer();
  sim->registerComponent(backend);
  setParStr(backend, "backendType", "ErrorTrackingBackend");
  EXPECT_EQ(backend->backend, nullptr);
  backend->callInitialize();
  EXPECT_NE(backend->backend, nullptr);
}

TEST(BackendContainer, callInitializeWithInvalidBackend) {
  auto *sim = utils::prepareSimulation();
  BackendContainer *backend = new BackendContainer();
  sim->registerComponent(backend);
  setParStr(backend, "backendType", "SomeInvalidBackend");
  EXPECT_EQ(backend->backend, nullptr);
  EXPECT_THROW(backend->callInitialize(), omnetpp::cRuntimeError);
}

TEST(BackendContainer, getQuantumBackend) {
  auto *sim = utils::prepareSimulation();
  BackendContainer *backend = new BackendContainer();
  sim->registerComponent(backend);
  setParStr(backend, "backendType", "ErrorTrackingBackend");
  backend->callInitialize();
  ASSERT_NE(backend->backend, nullptr);
  auto *b = backend->getQuantumBackend();
  ASSERT_NE(b, nullptr);
  auto *et_backend = dynamic_cast<ErrorTrackingBackend *>(b);
  EXPECT_NE(et_backend, nullptr);
}
}  // namespace

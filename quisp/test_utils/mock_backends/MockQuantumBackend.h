#pragma once

#include <gmock/gmock.h>
#include <test_utils/ModuleType.h>
#include <test_utils/UtilFunctions.h>
#include <modules/common_types.h>

namespace quisp_test::mock_backends {
using quisp::modules::common::IQuantumBackend;
using quisp::modules::common::IQubitId;
using quisp::modules::common::IBackendQubit;
class MockQuantumBackend : public IQuantumBackend {
 public:
  MOCK_METHOD(IBackendQubit*, getQubit, (const IQubitId *), (override));
  MOCK_METHOD(const SimTime&, getSimTime, (), (override));
  MOCK_METHOD(void, setSimTime, (SimTime time), (override));
};
}  // namespace quisp_test::mock_backends

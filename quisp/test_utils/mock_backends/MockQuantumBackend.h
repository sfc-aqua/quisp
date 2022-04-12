#pragma once

#include <gmock/gmock.h>
#include <modules/common_types.h>
#include <test_utils/ModuleType.h>
#include <test_utils/UtilFunctions.h>

namespace quisp_test::mock_backends {
using quisp::modules::common::IBackendQubit;
using quisp::modules::common::IConfiguration;
using quisp::modules::common::IQuantumBackend;
using quisp::modules::common::IQubitId;
class MockQuantumBackend : public IQuantumBackend {
 public:
  MOCK_METHOD(IBackendQubit *, getQubit, (const IQubitId *), (override));
  MOCK_METHOD(IBackendQubit *, getQubit, (const IQubitId *, std::unique_ptr<IConfiguration> configuration), (override));
  MOCK_METHOD(const SimTime &, getSimTime, (), (override));
  MOCK_METHOD(void, setSimTime, (SimTime time), (override));
};
}  // namespace quisp_test::mock_backends

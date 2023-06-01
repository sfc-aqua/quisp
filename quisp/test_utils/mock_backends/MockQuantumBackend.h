#pragma once

#include <gmock/gmock.h>
#include <modules/common_types.h>
#include <omnetpp.h>
#include <test_utils/ModuleType.h>
#include <test_utils/TestUtilFunctions.h>
#include "omnetpp/simtime_t.h"

namespace quisp_test::mock_backends {
using quisp::modules::common::IBackendQubit;
using quisp::modules::common::IConfiguration;
using quisp::modules::common::IQuantumBackend;
using quisp::modules::common::IQubitId;
class MockQuantumBackend : public IQuantumBackend {
 public:
  MOCK_METHOD(IBackendQubit *, getQubit, (const IQubitId *), (override));
  MOCK_METHOD(IBackendQubit *, createQubit, (const IQubitId *, std::unique_ptr<IConfiguration> configuration), (override));
  MOCK_METHOD(IBackendQubit *, createQubit, (const IQubitId *), (override));
  MOCK_METHOD(IBackendQubit *, createShortLiveQubit, (), (override));
  MOCK_METHOD(IBackendQubit *, getShortLiveQubit, (), (override));
  MOCK_METHOD(void, returnToPool, (IQubit *), (override));
  MOCK_METHOD(void, deleteQubit, (const IQubitId *), (override));
  MOCK_METHOD(const omnetpp::simtime_t &, getSimTime, (), (override));
  MOCK_METHOD(void, setSimTime, (omnetpp::simtime_t time), (override));
  MOCK_METHOD(std::unique_ptr<IConfiguration>, getDefaultConfiguration, (), (const, override));
};
}  // namespace quisp_test::mock_backends

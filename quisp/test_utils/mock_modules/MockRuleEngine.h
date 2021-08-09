#pragma once

#include <gmock/gmock.h>
#include <modules/QRSA/RuleEngine/IRuleEngine.h>

using quisp::modules::IRuleEngine;

namespace quisp_test {
namespace mock_modules {
namespace rule_engine {
class MockRuleEngine : public IRuleEngine {
 public:
  MOCK_METHOD(void, freeResource, (int, int, QNIC_type), (override));
  MOCK_METHOD(void, freeConsumedResource, (int, StationaryQubit*, QNIC_type), (override));
  MOCK_METHOD(void, ResourceAllocation, (int, int), (override));
};
}  // namespace rule_engine
}  // namespace mock_modules
}  // namespace quisp_test

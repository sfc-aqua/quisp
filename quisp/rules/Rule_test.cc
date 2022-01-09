#include "Rule.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <memory>

namespace {
using namespace quisp_test;
using namespace quisp::rules;
using quisp::rules::PurType;
using quisp::rules::SwapType;

TEST(RuleTest, InitPurificationRule) {
  prepareSimulation();
  PurificationRule pur_rule(PurType::SSDP_X);  // parent ruleset id, rule_id, partner address
}

TEST(RuleTest, InitSwappingRule) { prepareSimulation(); }

TEST(RuleTest, InitWaitRule) { prepareSimulation(); }
TEST(RuleTest, InitRandomMeasurementRule) { prepareSimulation(); }

TEST(RuleTest, setNextRule) { prepareSimulation(); }

TEST(RuleTest, addCondition) { prepareSimulation(); }

TEST(RuleTest, addAction) { prepareSimulation(); }

}  // namespace
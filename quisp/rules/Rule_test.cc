#include "Rule.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <memory>

namespace {
using namespace quisp_test;
using namespace quisp::rules;

TEST(RuleTest, InitPurificationRule) {
  prepareSimulation();
  // PurificationRule pur_rule(SSDP_X, 1);  // parent ruleset id, rule_id, partner address
  // EXPECT_EQ(pur_rule.purtype, SSDP_X);
  // EXPECT_EQ(pur_rule.num_purification, 1);
}

TEST(RuleTest, InitSwappingRule) { prepareSimulation(); }
}  // namespace
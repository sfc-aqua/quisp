#include "ActiveRuleSet.h"
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>

namespace {
using namespace quisp::rules;
using namespace quisp_test;

TEST(ActiveRuleSetTest, Init) {
  // test for initialization
  prepareSimulation();
  ActiveRuleSet active_ruleset(1, 2);
  EXPECT_EQ(1, active_ruleset.ruleset_id);
  EXPECT_EQ(2, active_ruleset.owner_addr);

  ActiveRuleSet active_ruleset2(1, 2);
  EXPECT_EQ(1, active_ruleset2.ruleset_id);
  EXPECT_EQ(2, active_ruleset2.owner_addr);
}

TEST(ActiveRuleSetTest, AddRule) {
  // test for a function to add a Rule
  prepareSimulation();
  ActiveRuleSet active_ruleset(1, 2);
  auto rule = std::make_unique<Rule>(0, 0);
  active_ruleset.addRule(std::move(rule));
  EXPECT_EQ(1, active_ruleset.size());
}

TEST(ActiveRuleSetTest, getRule) {
  // test for a function to get a pointer to the Rule
  prepareSimulation();
  ActiveRuleSet active_ruleset(1, 2);
  auto rule = std::make_unique<Rule>(0, 0);
  active_ruleset.addRule(std::move(rule));
  EXPECT_EQ(1, active_ruleset.size());
  auto target_rule = active_ruleset.getRule(0);
  EXPECT_EQ(rule, target_rule);
}

}  // namespace
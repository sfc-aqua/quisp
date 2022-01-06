#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include "RuleSet.h"

namespace {
using namespace quisp::rules;
using namespace quisp_test;

TEST(RuleSetTest, Init) {
  prepareSimulation();
  RuleSet ruleset(1, 2);
  EXPECT_EQ(1, ruleset.ruleset_id);
  EXPECT_EQ(2, ruleset.owner_addr);

  RuleSet ruleset2(1, 2);
  EXPECT_EQ(1, ruleset2.ruleset_id);
  EXPECT_EQ(2, ruleset2.owner_addr);
}

TEST(RuleSetTest, addRule) {
  prepareSimulation();
  RuleSet ruleset(1, 2);
  PurificationRule purification(SSDP_X, 1);  // (purification type, num purification)
  /*
  BaseRuleConfig{
          .to
		  .conditions = {}
		  .actions = {}
          setNextRule()
  }
  PurificationConfig: BaseRuleConfig{
          .type
          .number
          .name
		  .conditions = {clause1, clause2, ...}
		  .actions = {action1, action2, ...}
          .to // next rule id
  }
  */
  auto &rule1 = ruleset.addRule(purification, {1});  // return address to rule
  EXPECT_EQ(ruleset.rules(0).rule_id, rule1.rule_id);
  auto &rule2 = ruleset.addRule(purification, {3});  // return address to rule
  EXPECT_EQ(ruleset.rules(1).rule_id, rule2.rule_id);
  SwappingRule swapping(1);
  auto &rule3 = ruleset.addRule(swapping, {1, 3});
  EXPECT_EQ(ruleset.rules(2).rule_id, rule3.rule_id);
  rule1.setNextRule(rule3.rule_id);
  rule2.setNextRule(rule3.rule_id);
}

TEST(RuleSetTest, serialize) { prepareSimulation(); }

TEST(RuleSetTest, deserialize) { prepareSimulation(); }

}  // namespace
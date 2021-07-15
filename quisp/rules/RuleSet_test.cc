#include "RuleSet.h"
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>

namespace {
using namespace quisp::rules;
using namespace quisp_test;
TEST(RuleSetTest, Init) {
  prepareSimulation();
  RuleSet rule_set(1, 2, std::vector<int>{3, 4, 5});
  EXPECT_EQ(1, rule_set.ruleset_id);
  EXPECT_EQ(2, rule_set.owner_addr);
  EXPECT_EQ(3, rule_set.entangled_partners.size());

  RuleSet rule_set2(1, 2, 3);
  EXPECT_EQ(1, rule_set2.ruleset_id);
  EXPECT_EQ(2, rule_set2.owner_addr);
  EXPECT_EQ(1, rule_set2.entangled_partners.size());
  EXPECT_EQ(3, rule_set2.entangled_partners.at(0));
}

TEST(RuleSetTest, AddRule) {
  prepareSimulation();
  RuleSet rule_set(1, 2, 3);
  Rule* rule = new Rule();
  rule_set.addRule(rule);
  EXPECT_EQ(1, rule_set.size());
}
}  // namespace

#include "Rule.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <memory>
#include "RuleSet.h"
namespace {
using namespace quisp_test;
using namespace quisp::rules;
using quisp::rules::PurType;
using quisp::rules::SwapType;

TEST(RuleTest, setNextRule) {
  prepareSimulation();
  RuleSet ruleset(1, 2);

  auto purification = std::make_unique<Rule>();  // (purification type)
  auto rule1 = ruleset.addRule(std::move(purification), {1});  // rule type, partners
  auto purification2 = std::make_unique<Rule>();  // (purification type)
  auto rule2 = ruleset.addRule(std::move(purification2), {3});  // return address to rule
  auto swapping = std::make_unique<Rule>();
  auto rule3 = ruleset.addRule(std::move(swapping), {1, 3});

  rule1->setNextRule(rule3->rule_id);
  rule2->setNextRule(rule3->rule_id);

  EXPECT_EQ(rule1->to, rule3->rule_id);
  EXPECT_EQ(rule2->to, rule3->rule_id);
  EXPECT_EQ(rule3->to, 0);
}

TEST(RuleTest, serialize) { prepareSimulation(); }

}  // namespace
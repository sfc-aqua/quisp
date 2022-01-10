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

TEST(RuleTest, InitPurificationRule) {
  prepareSimulation();
  auto pur_rule = std::make_unique<PurificationRule>(PurType::SSDP_X);
  EXPECT_EQ(pur_rule->purification_type, PurType::SSDP_X);
}

TEST(RuleTest, InitSwappingRule) {
  prepareSimulation();
  auto swap_rule = std::make_unique<SwappingRule>(SwapType::BINARY_TREE);
  EXPECT_EQ(swap_rule->swapping_type, SwapType::BINARY_TREE);
}

TEST(RuleTest, InitRandomMeasurementRule) {
  prepareSimulation();
  auto random_measure_rule = std::make_unique<RandomMeasurementRule>(1000);
  EXPECT_EQ(random_measure_rule->total_measurement, 1000);
}

TEST(RuleTest, setNextRule) { 
  prepareSimulation(); 
  RuleSet ruleset(1, 2);
  auto purification = std::make_unique<PurificationRule>(PurType::SSDP_X);  // (purification type)
  auto swapping = std::make_unique<SwappingRule>(SwapType::BINARY_TREE);
  auto &rule1 = ruleset.addRule(std::move(purification), {1});  // rule type, partners
  
  auto purification2 = std::make_unique<PurificationRule>(PurType::SSDP_X);  // (purification type)
  auto &rule2 = ruleset.addRule(std::move(purification2), {3});  // return address to rule

  auto &rule3 = ruleset.addRule(std::move(swapping), {1, 3});

  rule1.setNextRule(rule3.rule_id);
  rule2.setNextRule(rule3.rule_id);

  EXPECT_EQ(rule1.to, rule3.rule_id);
  EXPECT_EQ(rule2.to, rule3.rule_id);
  EXPECT_EQ(rule3.to, 0);
}

TEST(RuleTest, addCondition) { prepareSimulation(); }

TEST(RuleTest, addAction) { prepareSimulation(); }

}  // namespace
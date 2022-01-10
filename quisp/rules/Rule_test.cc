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

TEST(RuleTest, setNextRule) { prepareSimulation(); }

TEST(RuleTest, addCondition) { prepareSimulation(); }

TEST(RuleTest, addAction) { prepareSimulation(); }

}  // namespace
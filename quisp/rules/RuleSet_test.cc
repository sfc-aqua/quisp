#include "RuleSet.h"
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <memory>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace {
using namespace quisp::rules;
using namespace quisp_test;
using quisp::rules::PurType;

TEST(RuleSetTest, Init) {
  prepareSimulation();
  RuleSet ruleset(1234, 2);
  EXPECT_EQ(1234, ruleset.ruleset_id);
  EXPECT_EQ(2, ruleset.owner_addr);

  RuleSet ruleset2(324, 10);
  EXPECT_EQ(324, ruleset2.ruleset_id);
  EXPECT_EQ(10, ruleset2.owner_addr);
}

TEST(RuleSetTest, addRule) {
  prepareSimulation();
  RuleSet ruleset(1, 2);
  auto purification = std::make_unique<Rule>();
  auto rule1 = ruleset.addRule(std::move(purification), {1});  // rule type, partners
  EXPECT_EQ(ruleset.rules.size(), 1);
  EXPECT_EQ(ruleset.rules.at(0)->parent_ruleset_id, ruleset.ruleset_id);
  EXPECT_EQ(ruleset.rules.at(0)->rule_id, rule1->rule_id);
  EXPECT_EQ(ruleset.rules.at(0)->partners.at(0), 1);

  auto purification2 = std::make_unique<Rule>();
  auto rule2 = ruleset.addRule(std::move(purification2), {3});  // return address to rule
  EXPECT_EQ(ruleset.rules.at(1)->parent_ruleset_id, ruleset.ruleset_id);
  EXPECT_EQ(ruleset.rules.at(1)->rule_id, rule2->rule_id);
  EXPECT_EQ(ruleset.rules.at(1)->partners.at(0), 3);

  auto swapping = std::make_unique<Rule>();
  auto rule3 = ruleset.addRule(std::move(swapping), {1, 3});
  EXPECT_EQ(ruleset.rules.at(2)->parent_ruleset_id, ruleset.ruleset_id);
  EXPECT_EQ(ruleset.rules.at(2)->rule_id, rule3->rule_id);
  EXPECT_EQ(ruleset.rules.at(2)->partners.at(0), 1);
  EXPECT_EQ(ruleset.rules.at(2)->partners.at(1), 3);
}

TEST(RuleSetTest, metadata_serialize_json) {
  prepareSimulation();
  RuleSet ruleset(1234, 2);  // ruleset_id, owner_addr
  auto purification = std::make_unique<Rule>();
  auto rule1 = ruleset.addRule(std::move(purification), {1});  // rule type, partners

  auto ruleset_json = ruleset.serialize_json();
  json expected_json = R"({"ruleset_id": 1234,
                           "owner_address": 2,
                           "num_rules": 1,
                           "rules": [{
                             "name": "",
                             "next_rule_id": -1,
                             "partners": [1],
                             "rule_id": 0
                            }]
                          })"_json;
  EXPECT_EQ(ruleset_json, expected_json);
}

TEST(RuleSetTest, deserialize_json) {
  prepareSimulation();
  RuleSet ruleset(1234, 2);  // ruleset_id, owner_addr

  auto purification = std::make_unique<Rule>();
  auto rule1 = ruleset.addRule(std::move(purification), {1});  // rule type, partners
  auto serialized = ruleset.serialize_json();

  // transfer serialized ruleset from HM to RE here.
  RuleSet empty_ruleset(1234, 2);
  empty_ruleset.deserialize_json(serialized);
  EXPECT_EQ(empty_ruleset.ruleset_id, 1234);
  EXPECT_EQ(empty_ruleset.owner_addr, 2);
  EXPECT_EQ(empty_ruleset.rules.size(), 1);
}

}  // namespace
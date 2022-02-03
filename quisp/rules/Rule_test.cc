#include "Rule.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <memory>
#include "Action.h"
#include "Clause.h"
#include "RuleSet.h"
namespace {
using namespace quisp_test;
using namespace quisp::rules;
using quisp::modules::QNIC_type;
using quisp::rules::PurType;

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

TEST(RuleTest, serialize_json_purification_rule) {
  prepareSimulation();
  RuleSet ruleset(1234, 2);

  auto purification = std::make_unique<Rule>("purification");  // name
  auto condition = std::make_unique<Condition>();
  // arguments: num_resource, required_fidelity, partner_addr, qnic_type, qnic_id
  auto enough_resource_clause = std::make_unique<EnoughResourceConditionClause>(1, 0.85, 1, QNIC_E, 13);
  condition->addClause(std::move(enough_resource_clause));
  // purification_type, partner_addr, qnic_type, qnic_id
  auto action = std::make_unique<Purification>(PurType::SSDP_X, 1, QNIC_E, 13);
  // addd condition and action
  purification->setCondition(std::move(condition));
  purification->setAction(std::move(action));
  auto swapping = std::make_unique<Rule>();

  // append rules to RuleSet
  auto rule1 = ruleset.addRule(std::move(purification), {1});
  auto rule2 = ruleset.addRule(std::move(swapping), {1, 3});

  rule1->setNextRule(rule2->rule_id);

  json purification_json = rule1->serialize_json();
  EXPECT_EQ(purification_json["rule_id"], rule1->rule_id);
  EXPECT_EQ(purification_json["next_rule_id"], rule1->to);
  EXPECT_EQ(purification_json["name"], "purification");
  EXPECT_EQ(purification_json["partners"][0], 1);
  auto condition_json = purification_json["condition"];  // (first clause) enough resource clause
  EXPECT_EQ(condition_json["type"], "enough_resource");
  EXPECT_EQ(condition_json["options"]["num_resources"], 1);
  EXPECT_EQ(condition_json["options"]["required_fidelity"], 0.85);
  EXPECT_EQ(condition_json["options"]["partner_address"], 1);
  EXPECT_EQ(condition_json["options"]["qnic_type"], QNIC_E);
  EXPECT_EQ(condition_json["options"]["qnic_id"], 13);
  auto action_json = purification_json["action"];
  EXPECT_EQ(action_json["type"], "purification");
  EXPECT_EQ(action_json["options"]["purification_type"], 4);
  EXPECT_EQ(action_json["options"]["partner_address"][0], 1);
  EXPECT_EQ(action_json["options"]["qnic_type"][0], 0);
  EXPECT_EQ(action_json["options"]["qnic_id"][0], 13);
}

}  // namespace
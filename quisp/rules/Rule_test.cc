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

  auto purification = std::make_unique<Rule>();
  purification->setName("purification");
  auto condition = std::make_unique<Condition>();
  // arguments: num_resource, required_fidelity, partner_addr, qnic_type, qnic_id
  auto enough_resource_clause = std::make_unique<EnoughResourceConditionClause>(1, 0.85, 1, QNIC_E, 13);
  condition->addClause(std::move(enough_resource_clause));
  // purification_type, partner_addr, qnic_type, qnic_id
  auto action = std::make_unique<Purification>(PurType::SSDP_X, 1, QNIC_E, 13);
  // add condition and action
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
  auto clause_json = purification_json["condition"]["clauses"][0];  // (first clause) enough resource clause
  EXPECT_EQ(clause_json["type"], "enough_resource");
  EXPECT_EQ(clause_json["options"]["num_resource"], 1);
  EXPECT_EQ(clause_json["options"]["required_fidelity"], 0.85);
  EXPECT_EQ(clause_json["options"]["partner_address"], 1);
  EXPECT_EQ(clause_json["options"]["qnic_type"], QNIC_E);
  EXPECT_EQ(clause_json["options"]["qnic_id"], 13);
  auto action_json = purification_json["action"];
  EXPECT_EQ(action_json["type"], "purification");
  EXPECT_EQ(action_json["options"]["purification_type"], "SSDP_X");
  EXPECT_EQ(action_json["options"]["partner_address"][0], 1);
  EXPECT_EQ(action_json["options"]["qnic_type"][0], "QNIC_E");
  EXPECT_EQ(action_json["options"]["qnic_id"][0], 13);
}

TEST(RuleTest, serialize_json_swapping_rule) {
  prepareSimulation();
  RuleSet ruleset(1234, 2);

  auto swapping = std::make_unique<Rule>();
  swapping->setName("swapping");
  auto condition = std::make_unique<Condition>();

  // {partner_addrs}, {qnic_type}, {qnic_id}
  std::vector<int> partners = {1, 3};
  std::vector<QNIC_type> qnic_types = {QNIC_E, QNIC_R};
  std::vector<int> qnic_id = {13, 15};

  // arguments: num_resource, required_fidelity, partner_addr, qnic_type, qnic_id
  auto enough_resource_clause_left = std::make_unique<EnoughResourceConditionClause>(1, 0.85, partners.at(0), qnic_types.at(0), qnic_id.at(0));
  auto enough_resource_clause_right = std::make_unique<EnoughResourceConditionClause>(1, 0.85, partners.at(1), qnic_types.at(1), qnic_id.at(1));
  condition->addClause(std::move(enough_resource_clause_left));
  condition->addClause(std::move(enough_resource_clause_right));

  auto action = std::make_unique<EntanglementSwapping>(partners, qnic_types, qnic_id);

  // add condition and action
  swapping->setCondition(std::move(condition));
  swapping->setAction(std::move(action));

  // dummy rules
  auto purification1 = std::make_unique<Rule>();
  auto purification3 = std::make_unique<Rule>();

  // append rules to RuleSet
  auto rule1 = ruleset.addRule(std::move(swapping), {1, 3});
  auto rule2 = ruleset.addRule(std::move(purification1), {1});
  auto rule3 = ruleset.addRule(std::move(purification3), {3});

  rule1->setNextRule(rule2->rule_id);

  json swapping_json = rule1->serialize_json();
  EXPECT_EQ(swapping_json["rule_id"], rule1->rule_id);
  EXPECT_EQ(swapping_json["next_rule_id"], rule1->to);
  EXPECT_EQ(swapping_json["name"], "swapping");
  EXPECT_EQ(swapping_json["partners"][0], 1);
  EXPECT_EQ(swapping_json["partners"][1], 3);

  // first clause: enough resource with partner 1 and fidelity > 0.85
  auto clause1_json = swapping_json["condition"]["clauses"][0];
  EXPECT_EQ(clause1_json["type"], "enough_resource");
  EXPECT_EQ(clause1_json["options"]["num_resource"], 1);
  EXPECT_EQ(clause1_json["options"]["required_fidelity"], 0.85);
  EXPECT_EQ(clause1_json["options"]["partner_address"], 1);
  EXPECT_EQ(clause1_json["options"]["qnic_type"], "QNIC_E");
  EXPECT_EQ(clause1_json["options"]["qnic_id"], 13);

  // second clause: enough resource with partner 3 and fidelity > 0.85
  auto clause2_json = swapping_json["condition"]["clauses"][1];
  EXPECT_EQ(clause2_json["type"], "enough_resource");
  EXPECT_EQ(clause2_json["options"]["num_resource"], 1);
  EXPECT_EQ(clause2_json["options"]["required_fidelity"], 0.85);
  EXPECT_EQ(clause2_json["options"]["partner_address"], 3);
  EXPECT_EQ(clause2_json["options"]["qnic_type"], "QNIC_R");
  EXPECT_EQ(clause2_json["options"]["qnic_id"], 15);

  // action: entanglement swapping ("swapping")
  auto action_json = swapping_json["action"];
  EXPECT_EQ(action_json["type"], "swapping");
  EXPECT_EQ(action_json["options"]["partner_address"][0], 1);
  EXPECT_EQ(action_json["options"]["qnic_type"][0], "QNIC_E");
  EXPECT_EQ(action_json["options"]["qnic_id"][0], 13);
  EXPECT_EQ(action_json["options"]["partner_address"][1], 3);
  EXPECT_EQ(action_json["options"]["qnic_type"][1], "QNIC_R");
  EXPECT_EQ(action_json["options"]["qnic_id"][1], 15);
}

TEST(RuleTest, deserialize_json_purification_rule) {
  prepareSimulation();
  RuleSet ruleset(1234, 2);

  auto purification = std::make_unique<Rule>();
  purification->setName("purification");
  auto condition = std::make_unique<Condition>();
  // arguments: num_resource, required_fidelity, partner_addr, qnic_type, qnic_id
  auto enough_resource_clause = std::make_unique<EnoughResourceConditionClause>(1, 0.85, 1, QNIC_E, 13);
  condition->addClause(std::move(enough_resource_clause));
  // purification_type, partner_addr, qnic_type, qnic_id
  auto action = std::make_unique<Purification>(PurType::SSDP_X, 1, QNIC_E, 13);
  // add condition and action
  purification->setCondition(std::move(condition));
  purification->setAction(std::move(action));
  auto swapping = std::make_unique<Rule>();

  // append rules to RuleSet
  auto rule1 = ruleset.addRule(std::move(purification), {1});
  auto rule2 = ruleset.addRule(std::move(swapping), {1, 3});

  rule1->setNextRule(rule2->rule_id);

  json purification_json = rule1->serialize_json();

  // empty rule injected purification rule json
  auto empty_rule = std::make_unique<Rule>(purification_json);
  EXPECT_EQ(empty_rule->rule_id, 0);
  EXPECT_EQ(empty_rule->to, 1);
  EXPECT_EQ(empty_rule->name, "purification");
  EXPECT_EQ(empty_rule->partners.at(0), 1);
}

}  // namespace
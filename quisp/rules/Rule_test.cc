#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Rule.h"

#include "Action.h"
#include "Clause.h"
#include "RuleSet.h"
#include "test_utils/TestUtils.h"
namespace {
using namespace quisp_test;
using namespace quisp::rules;
using quisp::modules::QNIC_E;
using quisp::modules::QNIC_N;
using quisp::modules::QNIC_R;
using quisp::modules::QNIC_RP;
using quisp::modules::QNIC_type;
using quisp::rules::PurType;

TEST(RuleTest, serialize_json_purification_rule) {
  prepareSimulation();
  RuleSet ruleset(1234, 2);

  auto purification = std::make_unique<Rule>(1, 0, false);
  purification->setName("purification");
  auto condition = std::make_unique<Condition>();
  // arguments: num_resource, partner_addr, qnic_type, qnic_id
  auto enough_resource_clause = std::make_unique<EnoughResourceConditionClause>(1, 1);
  condition->addClause(std::move(enough_resource_clause));
  // purification_type, partner_addr, qnic_type, qnic_id
  auto action = std::make_unique<Purification>(PurType::DOUBLE_SELECTION_X_PURIFICATION, 1, 2);
  // add condition and action
  purification->setCondition(std::move(condition));
  purification->setAction(std::move(action));
  std::vector<int> partners = {1, 3};
  std::vector<QNIC_type> qnic_type = {QNIC_R, QNIC_E};
  std::vector<int> qnic_id = {10, 11};
  auto swapping = std::make_unique<Rule>(partners, 0, true);

  // append rules to RuleSet
  auto rule1 = ruleset.addRule(std::move(purification));
  auto rule2 = ruleset.addRule(std::move(swapping));

  json purification_json = rule1->serialize_json();
  EXPECT_EQ(purification_json["name"], "purification");
  EXPECT_EQ(purification_json["interface"][0]["partner_address"], 1);
  auto clause_json = purification_json["condition"]["clauses"][0];  // (first clause) enough resource clause
  EXPECT_EQ(clause_json["type"], "enough_resource");
  EXPECT_EQ(clause_json["options"]["num_resource"], 1);
  EXPECT_EQ(clause_json["options"]["interface"]["partner_address"], 1);
  auto action_json = purification_json["action"];
  EXPECT_EQ(action_json["type"], "purification");
  EXPECT_EQ(action_json["options"]["purification_type"], "DOUBLE_SELECTION_X_PURIFICATION");
  EXPECT_EQ(action_json["options"]["interface"][0]["partner_address"], 1);
}

TEST(RuleTest, serialize_json_swapping_rule) {
  prepareSimulation();
  RuleSet ruleset(1234, 2);

  // {partner_addrs}, {qnic_type}, {qnic_id}
  std::vector<int> partners = {1, 3};
  std::vector<QNIC_type> qnic_types = {QNIC_E, QNIC_R};
  std::vector<int> qnic_id = {13, 15};
  std::vector<QNIC_type> remote_qnic_types = {QNIC_R, QNIC_E};
  std::vector<int> remote_qnic_id = {12, 16};
  std::vector<int> remote_qnic_address = {21, 22};
  auto swapping = std::make_unique<Rule>(partners, -1, -1);
  swapping->setName("swapping");
  auto condition = std::make_unique<Condition>();

  // arguments: num_resource, partner_addr, qnic_type, qnic_id
  auto enough_resource_clause_left = std::make_unique<EnoughResourceConditionClause>(1, partners.at(0));
  auto enough_resource_clause_right = std::make_unique<EnoughResourceConditionClause>(1, partners.at(1));
  condition->addClause(std::move(enough_resource_clause_left));
  condition->addClause(std::move(enough_resource_clause_right));

  auto action = std::make_unique<EntanglementSwapping>(partners, -1);

  // add condition and action
  swapping->setCondition(std::move(condition));
  swapping->setAction(std::move(action));

  // dummy rules
  auto purification1 = std::make_unique<Rule>(partners.at(0), -1, -1);
  auto purification3 = std::make_unique<Rule>(partners.at(1), -1, -1);

  // append rules to RuleSet
  auto rule1 = ruleset.addRule(std::move(swapping));
  auto rule2 = ruleset.addRule(std::move(purification1));
  ruleset.addRule(std::move(purification3));

  json swapping_json = rule1->serialize_json();
  EXPECT_EQ(swapping_json["name"], "swapping");
  EXPECT_EQ(swapping_json["interface"][0]["partner_address"], 1);
  EXPECT_EQ(swapping_json["interface"][1]["partner_address"], 3);

  // first clause: enough resource with partner 1
  auto clause1_json = swapping_json["condition"]["clauses"][0];
  EXPECT_EQ(clause1_json["type"], "enough_resource");
  EXPECT_EQ(clause1_json["options"]["num_resource"], 1);
  EXPECT_EQ(clause1_json["options"]["interface"]["partner_address"], 1);

  // second clause: enough resource with partner 3
  auto clause2_json = swapping_json["condition"]["clauses"][1];
  EXPECT_EQ(clause2_json["type"], "enough_resource");
  EXPECT_EQ(clause2_json["options"]["num_resource"], 1);
  EXPECT_EQ(clause2_json["options"]["interface"]["partner_address"], 3);

  // action: entanglement swapping ("swapping")
  auto action_json = swapping_json["action"];
  EXPECT_EQ(action_json["type"], "swapping");
  EXPECT_EQ(action_json["options"]["interface"][0]["partner_address"], 1);
  EXPECT_EQ(action_json["options"]["interface"][1]["partner_address"], 3);
}

TEST(RuleTest, deserialize_json_purification_rule) {
  prepareSimulation();
  RuleSet ruleset(1234, 2);

  auto purification = std::make_unique<Rule>(1, -1, -1);
  purification->setName("purification");
  auto condition = std::make_unique<Condition>();
  // arguments: num_resource, required_fidelity, partner_addr, qnic_type, qnic_id
  auto enough_resource_clause = std::make_unique<EnoughResourceConditionClause>(1, 1);
  condition->addClause(std::move(enough_resource_clause));
  // purification_type, partner_addr, qnic_type, qnic_id
  auto action = std::make_unique<Purification>(PurType::DOUBLE_SELECTION_X_PURIFICATION, 1, 3);
  // add condition and action
  purification->setCondition(std::move(condition));
  purification->setAction(std::move(action));
  std::vector<int> partners = {1, 3};
  std::vector<QNIC_type> qnic_type = {QNIC_E, QNIC_R};
  std::vector<int> qnic_id = {14, 15};
  auto swapping = std::make_unique<Rule>(partners, -1, -1);

  // append rules to RuleSet
  auto rule1 = ruleset.addRule(std::move(purification));
  auto rule2 = ruleset.addRule(std::move(swapping));

  json purification_json = rule1->serialize_json();

  // empty rule injected purification rule json
  auto empty_rule = std::make_unique<Rule>(purification_json);
  EXPECT_EQ(empty_rule->name, "purification");
  EXPECT_EQ(empty_rule->qnic_interfaces.at(0).partner_addr, 1);
}

}  // namespace

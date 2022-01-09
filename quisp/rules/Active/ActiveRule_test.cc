#include "ActiveRule.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <memory>

namespace {
using namespace quisp_test;
using namespace quisp::rules;
using OriginalActiveRule = quisp::rules::active::ActiveRule;
class Rule : public OriginalActiveRule {
 public:
  using OriginalActiveRule::ActiveRule;
  static std::unique_ptr<ActiveRule> setupActiveRule() {
    unsigned long ruleset_id = 1234;
    unsigned long rule_id = 3456;
    std::string rule_name = "example rule";
    std::vector<int> action_partners = {1, 3};

    return std::make_unique<ActiveRule>(ruleset_id, rule_id, rule_name, action_partners);
  }
};

TEST(ActiveRuleTest, Init) {
  prepareSimulation();
  unsigned long ruleset_id = 1234;
  unsigned long rule_id = 3452;
  std::string rule_name = "empty rule";
  std::vector<int> action_partners = {1, 3};
  ActiveRule rule(ruleset_id, rule_id, rule_name, action_partners);
  EXPECT_EQ(rule.ruleset_id, ruleset_id);
  EXPECT_EQ(rule.rule_id, rule_id);
  EXPECT_EQ(rule.name, rule_name);
  EXPECT_EQ(rule.action_partners.at(0), 1);
  EXPECT_EQ(rule.action_partners.at(1), 3);
}

TEST(RuleTest, addResourceTest) {
  prepareSimulation();
  auto rule = Rule::setupActiveRule();
  int entangled_partner_address1 = 1;
  int entangled_partner_address2 = 3;
  auto *qubit1 = new MockQubit();
  auto *qubit2 = new MockQubit();
  rule->addResource(entangled_partner_address1, qubit1);
  auto resources = rule->resources;
  EXPECT_EQ(resources.size(), 1);
  auto qubit_record = resources.find(entangled_partner_address1);
  ASSERT_NE(qubit_record, resources.end());
  EXPECT_EQ(qubit_record->first, entangled_partner_address1);
  EXPECT_EQ(qubit_record->second, qubit1);

  rule->addResource(entangled_partner_address2, qubit2);
  resources = rule->resources;
  auto qubit_record2 = resources.find(entangled_partner_address2);
  EXPECT_NE(qubit_record2, resources.end());
  EXPECT_EQ(qubit_record2->first, entangled_partner_address2);
  EXPECT_EQ(qubit_record2->second, qubit2);
}

}  // namespace
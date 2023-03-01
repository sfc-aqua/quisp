#include <memory>

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "RuleSet.h"
#include "test_utils/TestUtils.h"

using json = nlohmann::json;

namespace {
using namespace quisp::rules;
using namespace quisp_test;
using quisp::modules::QNIC_E;
using quisp::modules::QNIC_N;
using quisp::modules::QNIC_R;
using quisp::modules::QNIC_RP;
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
  auto purification = std::make_unique<Rule>(1, -1, 2);
  auto rule1 = ruleset.addRule(std::move(purification));  // rule type, partners
  EXPECT_EQ(ruleset.rules.size(), 1);
  EXPECT_EQ(ruleset.rules.at(0)->qnic_interfaces.at(0).partner_addr, 1);

  auto purification2 = std::make_unique<Rule>(3, -1, 2);
  auto rule2 = ruleset.addRule(std::move(purification2));  // return address to rule
  EXPECT_EQ(ruleset.rules.at(1)->qnic_interfaces.at(0).partner_addr, 3);

  std::vector<int> partners = {1, 3};
  std::vector<QNIC_type> qnic_types = {QNIC_E, QNIC_R};
  std::vector<int> qnic_id = {10, 11};
  auto swapping = std::make_unique<Rule>(partners, -1, 2);
  auto rule3 = ruleset.addRule(std::move(swapping));
  EXPECT_EQ(ruleset.rules.at(2)->qnic_interfaces.at(0).partner_addr, 1);
  EXPECT_EQ(ruleset.rules.at(2)->qnic_interfaces.at(1).partner_addr, 3);
}

TEST(RuleSetTest, Reversible_Check) {
  prepareSimulation();
  unsigned long ruleset_id = 123987;
  int self_addr = 13;
  int partner_addr = 84;
  int send_tag = 14;
  int receive_tag = 93;
  RuleSet ruleset(ruleset_id, self_addr);
  auto rule = std::make_unique<Rule>(partner_addr, send_tag, receive_tag);
  ruleset.addRule(std::move(rule));
  RuleSet reverted_ruleset;
  reverted_ruleset.deserialize_json(ruleset.serialize_json());

  EXPECT_EQ(ruleset.owner_addr, reverted_ruleset.owner_addr);
  EXPECT_EQ(ruleset.ruleset_id, reverted_ruleset.ruleset_id);
  EXPECT_EQ(ruleset.rules.size(), reverted_ruleset.rules.size());
  EXPECT_EQ(ruleset.rules.at(0)->send_tag, reverted_ruleset.rules.at(0)->send_tag);
  EXPECT_EQ(ruleset.rules.at(0)->receive_tag, reverted_ruleset.rules.at(0)->receive_tag);
  EXPECT_EQ(ruleset.rules.at(0)->qnic_interfaces.size(), reverted_ruleset.rules.at(0)->qnic_interfaces.size());
  EXPECT_EQ(ruleset.rules.at(0)->qnic_interfaces.at(0).partner_addr, reverted_ruleset.rules.at(0)->qnic_interfaces.at(0).partner_addr);
}

}  // namespace

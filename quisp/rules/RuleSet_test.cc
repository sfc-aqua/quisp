#include "RuleSet.h"
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <memory>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace {
using namespace quisp::rules;
using namespace quisp_test;
using quisp::modules::QNIC_E;
using quisp::modules::QNIC_N;
using quisp::modules::QNIC_R;
using quisp::modules::QNIC_RP;
using quisp::rules::PurType;
using quisp::types::QNodeAddr;

TEST(RuleSetTest, Init) {
  prepareSimulation();
  RuleSet ruleset(1234, QNodeAddr{2});
  EXPECT_EQ(1234, ruleset.ruleset_id);
  EXPECT_EQ(QNodeAddr{2}, ruleset.owner_addr);

  RuleSet ruleset2(324, QNodeAddr{10});
  EXPECT_EQ(324, ruleset2.ruleset_id);
  EXPECT_EQ(QNodeAddr{10}, ruleset2.owner_addr);
}

TEST(RuleSetTest, addRule) {
  prepareSimulation();
  RuleSet ruleset(1, QNodeAddr{2});
  auto purification = std::make_unique<Rule>(QNodeAddr{1}, 0, false);
  auto rule1 = ruleset.addRule(std::move(purification));  // rule type, partners
  EXPECT_EQ(ruleset.rules.size(), 1);
  EXPECT_EQ(ruleset.rules.at(0)->parent_ruleset_id, ruleset.ruleset_id);
  EXPECT_EQ(ruleset.rules.at(0)->rule_id, rule1->rule_id);
  EXPECT_EQ(ruleset.rules.at(0)->qnic_interfaces.at(0).partner_addr, QNodeAddr{1});

  auto purification2 = std::make_unique<Rule>(QNodeAddr{3}, 0, false);
  auto rule2 = ruleset.addRule(std::move(purification2));  // return address to rule
  EXPECT_EQ(ruleset.rules.at(1)->parent_ruleset_id, ruleset.ruleset_id);
  EXPECT_EQ(ruleset.rules.at(1)->rule_id, rule2->rule_id);
  EXPECT_EQ(ruleset.rules.at(1)->qnic_interfaces.at(0).partner_addr, QNodeAddr{3});

  std::vector<QNodeAddr> partners = {QNodeAddr{1}, QNodeAddr{3}};
  std::vector<QNIC_type> qnic_types = {QNIC_E, QNIC_R};
  std::vector<int> qnic_id = {10, 11};
  auto swapping = std::make_unique<Rule>(partners, 0, false);
  auto rule3 = ruleset.addRule(std::move(swapping));
  EXPECT_EQ(ruleset.rules.at(2)->parent_ruleset_id, ruleset.ruleset_id);
  EXPECT_EQ(ruleset.rules.at(2)->rule_id, rule3->rule_id);
  EXPECT_EQ(ruleset.rules.at(2)->qnic_interfaces.at(0).partner_addr, QNodeAddr{1});
  EXPECT_EQ(ruleset.rules.at(2)->qnic_interfaces.at(1).partner_addr, QNodeAddr{3});
}

TEST(RuleSetTest, metadata_serialize_json) {
  prepareSimulation();
  RuleSet ruleset(1234, QNodeAddr{2});  // ruleset_id, owner_addr
  auto purification = std::make_unique<Rule>(QNodeAddr{1}, 0, false);
  ruleset.addRule(std::move(purification));  // rule type, partners

  auto ruleset_json = ruleset.serialize_json();
  json expected_json = R"({"ruleset_id": 1234,
                           "owner_address": "0.2",
                           "num_rules": 1,
                           "rules": [{
                             "name": "",
                             "next_rule_id": -1,
                             "shared_tag": 0,
                             "interface":[
                               {"partner_address": "0.1"}
                             ],
                             "rule_id": 0
                            }]
                          })"_json;
  EXPECT_EQ(ruleset_json, expected_json);
}

TEST(RuleSetTest, deserialize_json) {
  prepareSimulation();
  RuleSet ruleset(1234, QNodeAddr{2});  // ruleset_id, owner_addr

  auto purification = std::make_unique<Rule>(QNodeAddr{1}, 0, false);
  ruleset.addRule(std::move(purification));  // rule type, partners
  auto serialized = ruleset.serialize_json();

  // transfer serialized ruleset from HM to RE here.
  RuleSet empty_ruleset(1234, QNodeAddr{2});
  empty_ruleset.deserialize_json(serialized);
  EXPECT_EQ(empty_ruleset.ruleset_id, 1234);
  EXPECT_EQ(empty_ruleset.owner_addr, QNodeAddr{2});
  EXPECT_EQ(empty_ruleset.rules.size(), 1);
}

}  // namespace

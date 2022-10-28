#include "RuleSetConverter.h"

#include <gtest/gtest.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>

#include <modules/QNIC.h>
#include <rules/RuleSet.h>
#include <runtime/types.h>
#include <test_utils/TestUtils.h>
#include <test_utils/UtilFunctions.h>

namespace {
using namespace quisp_test;
using namespace quisp::modules::rs_converter;
using RSData = quisp::rules::RuleSet;

template <typename T>
T get_instruction(const quisp::runtime::Rule& rule) {
  for (auto& instr : rule.action.opcodes) {
    if (std::holds_alternative<T>(instr)) {
      return std::get<T>(instr);
    }
  }
  throw std::runtime_error("the instruction type not found");
}

std::vector<quisp::runtime::QNodeAddr> get_partners(const quisp::runtime::Rule& rule) {
  std::vector<quisp::runtime::QNodeAddr> partners{};
  for (auto& instr : rule.condition.opcodes) {
    if (std::holds_alternative<quisp::runtime::INSTR_GET_QUBIT_QubitId_QNodeAddr_int_>(instr)) {
      auto [_qubit_id, partner_addr, _index] = std::get<quisp::runtime::INSTR_GET_QUBIT_QubitId_QNodeAddr_int_>(instr).args;
      partners.push_back(partner_addr);
    }
    if (std::holds_alternative<quisp::runtime::INSTR_GET_QUBIT_RegId_QNodeAddr_RegId_>(instr)) {
      auto [_qubit_id, partner_addr, _index] = std::get<quisp::runtime::INSTR_GET_QUBIT_RegId_QNodeAddr_RegId_>(instr).args;
      partners.push_back(partner_addr);
    }
  }
  return partners;
}

TEST(RSConverterTest, activeRuleSetConstructionFromJson) {
  // translate static ruleset into active ruleset
  prepareSimulation();

  auto serialized_ruleset = R"({
	"num_rules": 4,
	"owner_address": 2,
	"rules": [{
		"action": {
			"options": {
				"interface": [{
					"partner_address": 3,
					"qnic_id": 11,
					"qnic_type": "QNIC_E"
				}],
				"purification_type": "SINGLE_X"
			},
			"type": "purification"
		},
		"condition": {
			"clauses": [{
				"options": {
					"interface": {
						"partner_address": 3,
						"qnic_id": 11,
						"qnic_type": "QNIC_E"
					},
					"num_resource": 2,
					"required_fidelity": 0.0
				},
				"type": "enough_resource"
			}]
		},
		"interface": [{
			"partner_address": 3,
			"qnic_id": 11,
			"qnic_type": "QNIC_E"
		}],
    "shared_tag": 0,
		"name": "purification",
		"next_rule_id": 1,
		"rule_id": 0
	}, {
		"action": {
			"options": {
				"interface": [{
					"partner_address": 3,
					"qnic_id": 11,
					"qnic_type": "QNIC_E"
				}]
			},
			"type": "wait"
		},
		"condition": {
			"clauses": [{
				"options": {
					"interface": {
						"partner_address": 3,
						"qnic_id": 11,
						"qnic_type": "QNIC_E"
					}
				},
				"type": "wait"
			}]
		},
		"interface": [{
			"partner_address": 3,
			"qnic_id": 11,
			"qnic_type": "QNIC_E"
		}],
    "shared_tag": 0,
		"name": "wait",
		"next_rule_id": 2,
		"rule_id": 1
	}, {
		"action": {
			"options": {
				"interface": [{
					"partner_address": 5,
					"qnic_id": 11,
					"qnic_type": "QNIC_E"
				}],
				"purification_type": "SINGLE_X"
			},
			"type": "purification"
		},
		"condition": {
			"clauses": [{
				"options": {
					"interface": {
						"partner_address": 5,
						"qnic_id": 11,
						"qnic_type": "QNIC_E"
					},
					"num_resource": 2,
					"required_fidelity": 0.0
				},
				"type": "enough_resource"
			}]
		},
		"interface": [{
			"partner_address": 5,
			"qnic_id": 11,
			"qnic_type": "QNIC_E"
		}],
    "shared_tag": 0,
		"name": "purification",
		"next_rule_id": 3,
		"rule_id": 2
	}, {
		"action": {
			"options": {
				"interface": [{
					"partner_address": 5,
					"qnic_id": 11,
					"qnic_type": "QNIC_E"
				}],
				"num_measure": 0,
				"owner_address": 2
			},
			"type": "tomography"
		},
		"condition": {
			"clauses": [{
				"options": {
					"interface": {
						"partner_address": 5,
						"qnic_id": 11,
						"qnic_type": "QNIC_E"
					},
					"num_resource": 1,
					"required_fidelity": 0.0
				},
				"type": "enough_resource"
			}, {
				"options": {
					"interface": {
						"partner_address": 5,
						"qnic_id": 11,
						"qnic_type": "QNIC_E"
					},
					"num_measure": 100
				},
				"type": "measure_count"
			}]
		},
		"interface": [{
			"partner_address": 5,
			"qnic_id": 11,
			"qnic_type": "QNIC_E"
		}],
    "shared_tag": 0,
		"name": "tomography",
		"next_rule_id": -1,
		"rule_id": 3
	}],
	"ruleset_id": 1234
})"_json;

  quisp::rules::RuleSet deserialized_ruleset;
  deserialized_ruleset.deserialize_json(serialized_ruleset);

  auto active_ruleset = RuleSetConverter::construct(std::move(deserialized_ruleset));
  active_ruleset.finalize();

  // check property of resulted
  EXPECT_EQ(active_ruleset.rules.size(), 4);
  auto ruleset_id = active_ruleset.id;
  auto expected_ruleset_id = 1234;
  EXPECT_EQ(active_ruleset.id, expected_ruleset_id);
  ASSERT_EQ(active_ruleset.partners.size(), 2);

  // partner must be the next neighbor qnode3 (this qnode is qnode2[initiator])
  EXPECT_NE(active_ruleset.partners.find(3), active_ruleset.partners.end());

  // checking the 1st rule of QNode2(initiator): if EnoughResource -> Purify
  {
    auto rule = active_ruleset.rules.at(0);
    // first action is the purification with the neighbor qnode
    get_instruction<quisp::runtime::INSTR_PURIFY_X_RegId_QubitId_QubitId_>(rule);
  }
  // checking the 2nd rule of QNode2(initiator): Wait
  {
    auto rule = active_ruleset.rules.at(1);
    EXPECT_EQ(rule.name, "wait with 3");
    auto partners = get_partners(rule);
    ASSERT_EQ(partners.size(), 1);
    EXPECT_EQ(partners.at(0), 3);  // just wait QNode 3
  }
  // checking the 3rd rule of QNode2(initiator): if EnoughResource -> Purify
  {
    auto rule = active_ruleset.rules.at(2);
    EXPECT_EQ(rule.name, "purification with 5");
    auto partners = get_partners(rule);
    ASSERT_EQ(partners.size(), 1);
    // action partner must be the qnode5(responder)
    // third action is the purification with the opposite end qnode
    EXPECT_EQ(partners.at(0), 5);

    auto action = rule.action;
    get_instruction<quisp::runtime::INSTR_PURIFY_X_RegId_QubitId_QubitId_>(rule);
  }

  // checking the 4th rule of QNode2(initiator): EnoughResource && MeasureCount -> Tomography
  {
    auto rule = active_ruleset.rules.at(3);
    EXPECT_EQ(rule.name, "tomography with 5");

    auto partners = get_partners(rule);
    ASSERT_EQ(partners.size(), 1);
    // action partner must be the qnode5(responder)
    // last action is the tomography with the opposite end qnode
    EXPECT_EQ(partners.at(0), 5);

    get_instruction<quisp::runtime::INSTR_MEASURE_RANDOM_MemoryKey_QubitId_>(rule);
  }
}

TEST(RSConverterTest, generateActiveRuleSetFromRuleSet) {
  prepareSimulation();

  // prepare (static) ruleset being sent by responder
  unsigned long ruleset_id = 1234;
  int owner_address = 2;
  // ruleset creation
  quisp::rules::RuleSet ruleset(ruleset_id, owner_address);  // static ruleset
  ruleset.ruleset_id = ruleset_id;
  ruleset.owner_addr = owner_address;

  auto purify_rule = std::make_unique<quisp::rules::Rule>(0, quisp::modules::QNIC_E, 0, 0, false);
  purify_rule->setName("purification");
  auto pur_condition = std::make_unique<quisp::rules::Condition>();
  auto enough_resource_clause = std::make_unique<EnoughResourceConditionClause>(1, 0, 0, quisp::modules::QNIC_E, 0);
  pur_condition->addClause(std::move(enough_resource_clause));
  purify_rule->setCondition(std::move(pur_condition));
  auto pur_action = std::make_unique<Purification>(quisp::rules::PurType::DSDA, 0, quisp::modules::QNIC_E, 0);
  purify_rule->setAction(std::move(pur_action));
  ruleset.addRule(std::move(purify_rule));
  // swapping rule
  auto swapping_rule = std::make_unique<quisp::rules::Rule>(0, quisp::modules::QNIC_E, 0, 0, false);
  swapping_rule->setName("swapping");
  auto swap_condition = std::make_unique<quisp::rules::Condition>();
  auto enough_resource_clause_left = std::make_unique<EnoughResourceConditionClause>(1, 0, 0, quisp::modules::QNIC_E, 0);
  auto enough_resource_clause_right = std::make_unique<EnoughResourceConditionClause>(1, 0, 0, quisp::modules::QNIC_E, 0);
  swap_condition->addClause(std::move(enough_resource_clause_left));
  swap_condition->addClause(std::move(enough_resource_clause_right));
  swapping_rule->setCondition(std::move(swap_condition));
  std::vector<int> partners = {0, 0};
  std::vector<QNIC_type> qnic_type = {quisp::modules::QNIC_E, quisp::modules::QNIC_E};
  std::vector<int> qnic_id = {0, 0};
  std::vector<QNIC_type> remote_qnic_type = {quisp::modules::QNIC_E, quisp::modules::QNIC_E};
  std::vector<int> remote_qnic_id = {0, 0};
  std::vector<int> remote_qnic_address = {0, 0};
  auto swap_action = std::make_unique<EntanglementSwapping>(partners, qnic_type, qnic_id, remote_qnic_type, remote_qnic_id, remote_qnic_address);
  swapping_rule->setAction(std::move(swap_action));
  ruleset.addRule(std::move(swapping_rule));
  // wait rule
  auto wait_rule = std::make_unique<quisp::rules::Rule>(0, quisp::modules::QNIC_E, 0, 0, false);
  wait_rule->setName("wait");
  auto wait_condition = std::make_unique<quisp::rules::Condition>();
  auto wait_clause = std::make_unique<WaitConditionClause>(0, quisp::modules::QNIC_E, 0);
  wait_condition->addClause(std::move(wait_clause));
  wait_rule->setCondition(std::move(wait_condition));
  auto wait_action = std::make_unique<Wait>(0, quisp::modules::QNIC_E, 0);
  wait_rule->setAction(std::move(wait_action));
  ruleset.addRule(std::move(wait_rule));
  // tomography rule
  auto tomography_rule = std::make_unique<quisp::rules::Rule>(0, quisp::modules::QNIC_E, 0, 0, true);
  tomography_rule->setName("tomography");
  auto tomo_condition = std::make_unique<quisp::rules::Condition>();
  auto enough_resource_clause_tomo = std::make_unique<EnoughResourceConditionClause>(0, 0, 0, quisp::modules::QNIC_E, 0);
  tomo_condition->addClause(std::move(enough_resource_clause_tomo));
  tomography_rule->setCondition(std::move(tomo_condition));
  auto tomo_action = std::make_unique<Tomography>(0, 0, 0, quisp::modules::QNIC_E, 0);
  tomography_rule->setAction(std::move(tomo_action));
  ruleset.addRule(std::move(tomography_rule));

  // return active ruleset corresponding to input ruleset
  auto active_ruleset = RuleSetConverter::construct(std::move(ruleset));
  EXPECT_EQ(active_ruleset.id, ruleset_id);
  EXPECT_EQ(active_ruleset.rules.size(), 4);
  auto rule0 = std::move(active_ruleset.rules.at(0));
  EXPECT_EQ(rule0.id, 0);
  EXPECT_EQ(rule0.name, "purification with 0 ");
  auto rule1 = std::move(active_ruleset.rules.at(1));
  EXPECT_EQ(rule1.id, 1);
  EXPECT_EQ(rule1.name, "swapping with 0 ");
  auto rule2 = std::move(active_ruleset.rules.at(2));
  EXPECT_EQ(rule2.id, 2);
  EXPECT_EQ(rule2.name, "wait with 0 ");
  auto rule3 = std::move(active_ruleset.rules.at(3));
  EXPECT_EQ(rule3.id, 3);
  EXPECT_EQ(rule3.name, "tomography with 0 ");
}
}  // namespace

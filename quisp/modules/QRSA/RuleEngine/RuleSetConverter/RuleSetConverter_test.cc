#include "RuleSetConverter.h"

#include <gtest/gtest.h>
#include <iostream>
#include <nlohmann/json.hpp>

#include <rules/RuleSet.h>

namespace {
using namespace quisp::modules::rs_converter;
using RSData = quisp::rules::RuleSet;

TEST(RSConverterTest, init) {
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

  RSData rs_data;
  rs_data.deserialize_json(serialized_ruleset);
  RuleSet rs = RuleSetConverter::construct(rs_data);
  std::cout << "finish" << std::endl;
}
}  // namespace

#include <gtest/gtest.h>
#include <omnetpp.h>
#include <nlohmann/json.hpp>

#include <messages/classical_messages.h>
#include "ConnectionManager.h"
#include "RuleSetGenerator.h"
#include "modules/QRSA/HardwareMonitor/IHardwareMonitor.h"
#include "test_utils/UtilFunctions.h"

using json = nlohmann::json;
using OriginalRSG = quisp::modules::ruleset_gen::RuleSetGenerator;
using namespace quisp::messages;
using quisp::modules::NULL_CONNECTION_SETUP_INFO;
using quisp::modules::QNIC_E;
using namespace quisp_test::utils;
namespace {
class RuleSetGenerator : public OriginalRSG {
 public:
  RuleSetGenerator(int responder_addr) : OriginalRSG(responder_addr) {}
  using OriginalRSG::collectPath;
  using OriginalRSG::collectSwappingPartners;
  using OriginalRSG::fillPathDivision;
  using OriginalRSG::purifyRule;
  using OriginalRSG::swapRule;
  using OriginalRSG::tomographyRule;
  using OriginalRSG::waitRule;
};
TEST(RuleSetGenerator, Simple) {
  prepareSimulation();
  int responder_addr = 5;
  RuleSetGenerator rsg{responder_addr};
  auto *req = new ConnectionSetupRequest();
  // qnic_index(id)     11       12           13       14           15       16
  // [QNode2](qnic_addr:101) -- (102)[QNode3](103) -- (104)[QNode4](105) -- (106)[QNode5(test target)]
  req->setActual_destAddr(5);
  req->setActual_srcAddr(2);
  req->setDestAddr(5);
  req->setSrcAddr(4);
  req->setStack_of_QNICsArraySize(3);
  req->setStack_of_QNodeIndexesArraySize(3);
  req->setStack_of_QNodeIndexes(0, 2);
  req->setStack_of_QNodeIndexes(1, 3);
  req->setStack_of_QNodeIndexes(2, 4);
  req->setStack_of_QNICs(0, QNIC_pair_info{.fst = NULL_CONNECTION_SETUP_INFO.qnic, .snd = {.type = QNIC_E, .index = 11, .address = 101}});
  req->setStack_of_QNICs(1, QNIC_pair_info{.fst = {.type = QNIC_E, .index = 12, .address = 102}, .snd = {.type = QNIC_E, .index = 13, .address = 103}});
  req->setStack_of_QNICs(2, QNIC_pair_info{.fst = {.type = QNIC_E, .index = 14, .address = 104}, .snd = {.type = QNIC_E, .index = 15, .address = 105}});
  auto rulesets = rsg.generateRuleSets(req, 1234);
  EXPECT_EQ(rulesets.size(), 4);
  for (auto rs : rulesets) {
    std::cout << rs.second.dump() << std::endl;
  }
  {
    auto ruleset = rulesets.find(2)->second;
    auto expected_ruleset = R"({
	"num_rules": 4,
	"owner_address": 2,
	"rules": [{
		"action": {
			"options": {
				"interface": [{
					"partner_address": 3
				}],
				"purification_type": "SINGLE_X"
			},
			"type": "purification"
		},
		"condition": {
			"clauses": [{
				"options": {
					"interface": {
						"partner_address": 3
					},
					"num_resource": 2,
					"required_fidelity": 0.0
				},
				"type": "enough_resource"
			}]
		},
		"interface": [{
			"partner_address": 3
		}],
    "shared_tag": 0,
		"name": "purification",
		"next_rule_id": -1,
		"rule_id": 0
	}, {
		"action": {
			"options": {
				"interface": [{
					"partner_address": 3
				}]
			},
			"type": "wait"
		},
		"condition": {
			"clauses": [{
				"options": {
					"interface": {
						"partner_address": 3
					}
				},
				"type": "wait"
			}]
		},
		"interface": [{
			"partner_address": 3
		}],
    "shared_tag": 5,
		"name": "wait",
		"next_rule_id": -1,
		"rule_id": 1
	}, {
		"action": {
			"options": {
				"interface": [{
					"partner_address": 5
				}],
				"purification_type": "SINGLE_X"
			},
			"type": "purification"
		},
		"condition": {
			"clauses": [{
				"options": {
					"interface": {
						"partner_address": 5
					},
					"num_resource": 2,
					"required_fidelity": 0.0
				},
				"type": "enough_resource"
			}]
		},
		"interface": [{
			"partner_address": 5
		}],
    "shared_tag": 6,
		"name": "purification",
		"next_rule_id": -1,
		"rule_id": 2
	}, {
		"action": {
			"options": {
				"interface": [{
					"partner_address": 5
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
						"partner_address": 5
					},
					"num_resource": 1,
					"required_fidelity": 0.0
				},
				"type": "enough_resource"
			}, {
				"options": {
					"interface": {
						"partner_address": 5
					},
					"num_measure": 0
				},
				"type": "measure_count"
			}]
		},
		"interface": [{
			"partner_address": 5
		}],
    "shared_tag": 7,
		"name": "tomography",
		"next_rule_id": -1,
		"rule_id": 3
	}],
	"ruleset_id": 1234
})"_json;
    EXPECT_EQ(expected_ruleset, ruleset);
  }
}
}  // namespace

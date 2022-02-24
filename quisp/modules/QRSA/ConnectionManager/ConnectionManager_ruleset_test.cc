#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include <nlohmann/json.hpp>
#include "ConnectionManager.h"
#include "IConnectionManager.h"
#include "gtest/gtest_prod.h"
#include "modules/QNIC.h"
#include "modules/QRSA/ConnectionManager/IConnectionManager.h"
#include "test_utils/TestUtils.h"

using json = nlohmann::json;
namespace {
using namespace omnetpp;
using namespace quisp_test;
using namespace quisp::rules;
using PurType = quisp::rules::PurType;

class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy() {}
  ~Strategy() {}
};

class ConnectionManager : public quisp::modules::ConnectionManager {
 public:
  using quisp::modules::ConnectionManager::par;
  using quisp::modules::ConnectionManager::purifyRule;
  using quisp::modules::ConnectionManager::swapRule;
  using quisp::modules::ConnectionManager::tomographyRule;
  using quisp::modules::ConnectionManager::waitRule;

  ConnectionManager() : quisp::modules::ConnectionManager() {
    setParInt(this, "address", 123);
    setParInt(this, "total_number_of_qnics", 10);
    this->setName("connection_manager_test_target");
    this->provider.setStrategy(std::make_unique<Strategy>());
  }
};

TEST(ConnectionManagerRuleSetTest, PurificationRule) {
  prepareSimulation();
  ConnectionManager connection_manager;

  // rule arguments
  int partner_addr = 1;
  PurType purification_type = PurType::DOUBLE;
  QNIC_type qnic_type = QNIC_E;
  int qnic_id = 4;
  double threshold_fidelity = 0;

  auto purification_rule = connection_manager.purifyRule(partner_addr, purification_type, threshold_fidelity, qnic_type, qnic_id);
  EXPECT_EQ(purification_rule->rule_id, -1);
  EXPECT_EQ(purification_rule->name, "purification");

  auto serialized = purification_rule->serialize_json();
  //  rule_id is given by RuleSet and next_rule_id is given outside of Rule decration.
  json expected = R"({
	  				"rule_id": -1,
					"next_rule_id": -1,
					"name": "purification",
					"partners": [1],
					"condition": {
						"clauses": [{
							"type": "enough_resource",
							"options": {
								"num_resource": 2,
								"required_fidelity": 0.0,
								"partner_address": 1,
								"qnic_type": "QNIC_E",
								"qnic_id": 4
								}
							}]
						},
					"action": {
						"type": "purification",
						"options": {
							"purification_type": "DOUBLE",
							"partner_address": [1],
							"qnic_type": ["QNIC_E"],
							"qnic_id": [4]
							}
						}
					})"_json;
  EXPECT_EQ(serialized, expected);
}

TEST(ConnectionManagerRuleSetTest, SwapRule) {
  prepareSimulation();
  ConnectionManager connection_manager;

  // rule arguments
  std::vector<int> partner_addr = {1, 3};
  std::vector<QNIC_type> qnic_type = {QNIC_E, QNIC_R};
  std::vector<int> qnic_id = {4, 5};
  double threshold_fidelity = 0;

  auto purification_rule = connection_manager.swapRule(partner_addr, threshold_fidelity, qnic_type, qnic_id);
  EXPECT_EQ(purification_rule->rule_id, -1);
  EXPECT_EQ(purification_rule->name, "swapping");

  auto serialized = purification_rule->serialize_json();
  //  rule_id is given by RuleSet and next_rule_id is given outside of Rule decration.
  json expected = R"({
          "rule_id": -1,
					"next_rule_id": -1,
					"name": "swapping",
					"partners": [1, 3],
					"condition": {
						"clauses": [{
							"type": "enough_resource",
							"options": {
								"num_resource": 1,
								"required_fidelity": 0.0,
								"partner_address": 1,
								"qnic_type": "QNIC_E",
								"qnic_id": 4
								}
							},
              {
                "type": "enough_resource",
                "options": {
                  "num_resource": 1,
                  "required_fidelity": 0.0,
                  "partner_address": 3,
                  "qnic_type": "QNIC_R",
                  "qnic_id": 5
                }
              }]
						},
					"action": {
						"type": "swapping",
						"options": {
							"partner_address": [1, 3],
							"qnic_type": ["QNIC_E", "QNIC_R"],
							"qnic_id": [4, 5]
							}
						}
					})"_json;
  EXPECT_EQ(serialized, expected);
}

TEST(ConnectionManagerRuleSetTest, waitRule) {
  prepareSimulation();
  ConnectionManager connection_manager;

  // rule arguments
  int partner_addr = 1;
  QNIC_type qnic_type = QNIC_E;
  int qnic_id = 4;

  auto purification_rule = connection_manager.waitRule(partner_addr, qnic_type, qnic_id);
  EXPECT_EQ(purification_rule->rule_id, -1);
  EXPECT_EQ(purification_rule->name, "wait");

  auto serialized = purification_rule->serialize_json();
  //  rule_id is given by RuleSet and next_rule_id is given outside of Rule decration.
  json expected = R"({
          "rule_id": -1,
					"next_rule_id": -1,
					"name": "wait",
					"partners": [1],
					"condition": {
						"clauses": [{
							"type": "wait",
							"options": {
								"partner_address": 1,
								"qnic_type": "QNIC_E",
								"qnic_id": 4
								}
							}]
						},
					"action": {
						"type": "wait",
						"options": {
							"partner_address": [1],
							"qnic_type": ["QNIC_E"],
							"qnic_id": [4]
							}
						}
					})"_json;
  EXPECT_EQ(serialized, expected);
}

TEST(ConnectionManagerRuleSetTest, tomographyRule) {
  prepareSimulation();
  ConnectionManager connection_manager;

  // rule arguments
  int partner_addr = 1;
  QNIC_type qnic_type = QNIC_E;
  int qnic_id = 4;
  int num_measurement = 5000;
  double threshold_fidelity = 0;

  auto tomography_rule = connection_manager.tomographyRule(partner_addr, num_measurement, threshold_fidelity, qnic_type, qnic_id);
  EXPECT_EQ(tomography_rule->rule_id, -1);
  EXPECT_EQ(tomography_rule->name, "tomography");

  auto serialized = tomography_rule->serialize_json();
  //  rule_id is given by RuleSet and next_rule_id is given outside of Rule decration.
  json expected = R"({
          "rule_id": -1,
					"next_rule_id": -1,
					"name": "tomography",
					"partners": [1],
					"condition": {
						"clauses": [{
							"type": "enough_resource",
							"options": {
								"num_resource": 1,
								"required_fidelity": 0.0,
								"partner_address": 1,
								"qnic_type": "QNIC_E",
								"qnic_id": 4
								}
							}]
						},
					"action": {
						"type": "tomography",
						"options": {
              "num_measure": 5000,
							"partner_address": [1],
							"qnic_type": ["QNIC_E"],
							"qnic_id": [4]
							}
						}
					})"_json;
  EXPECT_EQ(serialized, expected);
}

}  // namespace

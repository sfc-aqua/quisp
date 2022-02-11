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
  using quisp::modules::ConnectionManager::swappingRule;
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
					"partners": [],
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

// TEST(ConnectionManagerRuleGenTest, SwappingRule) {
//   ConnectionManager connection_manager;
//   unsigned long ruleset_id = 5;
//   unsigned long rule_id = 6;

//   SwappingConfig conf{
//       .left_partner = 40,
//       .lqnic_type = QNIC_R,
//       .lqnic_index = 41,
//       .lqnic_address = 42,
//       .lres = 43,
//       .right_partner = 70,
//       .rqnic_type = QNIC_RP,
//       .rqnic_index = 71,
//       .rqnic_address = 72,
//       .rres = 73,
//       .self_left_qnic_index = 80,
//       .self_left_qnic_type = QNIC_RP,
//       .self_right_qnic_index = 81,
//       .self_right_qnic_type = QNIC_R,
//   };

//   std::unique_ptr<ActiveRule> rule;
//   rule = connection_manager.swappingRule(conf, ruleset_id, rule_id);
//   ASSERT_NE(rule, nullptr);
//   ASSERT_NE(rule->condition, nullptr);

//   ASSERT_NE(rule->action, nullptr);
//   EXPECT_EQ(rule->ruleset_id, ruleset_id);
//   EXPECT_EQ(rule->rule_id, rule_id);

//   EXPECT_EQ(rule->name, "Entanglement Swapping with 40 : 70");
//   EXPECT_EQ(rule->condition->clauses.size(), 2);
//   auto *left_clause = dynamic_cast<EnoughResourceClause *>(rule->condition->clauses.at(0));
//   EXPECT_EQ(access_private::partner(*left_clause), conf.left_partner);
//   EXPECT_EQ(access_private::num_resource_required(*left_clause), 1);

//   auto *right_clause = dynamic_cast<EnoughResourceClause *>(rule->condition->clauses.at(1));
//   EXPECT_EQ(access_private::partner(*right_clause), conf.right_partner);
//   EXPECT_EQ(access_private::num_resource_required(*right_clause), 1);

//   auto *action = dynamic_cast<SwappingAction *>(rule->action.get());
//   ASSERT_NE(action, nullptr);
//   EXPECT_EQ(action->ruleset_id, ruleset_id);
//   EXPECT_EQ(action->rule_id, rule_id);
//   EXPECT_EQ(access_private::left_partner(*action), conf.left_partner);
//   EXPECT_EQ(access_private::left_qnic_id(*action), conf.lqnic_index);
//   EXPECT_EQ(access_private::left_qnic_type(*action), conf.lqnic_type);
//   EXPECT_EQ(access_private::left_qnic_address(*action), conf.lqnic_address);
//   EXPECT_EQ(access_private::left_resource(*action), conf.lres);
//   EXPECT_EQ(access_private::self_left_qnic_id(*action), conf.self_left_qnic_index);
//   EXPECT_EQ(access_private::self_left_qnic_type(*action), conf.self_left_qnic_type);

//   EXPECT_EQ(access_private::right_partner(*action), conf.right_partner);
//   EXPECT_EQ(access_private::right_qnic_id(*action), conf.rqnic_index);
//   EXPECT_EQ(access_private::right_qnic_type(*action), conf.rqnic_type);
//   EXPECT_EQ(access_private::right_qnic_address(*action), conf.rqnic_address);
//   EXPECT_EQ(access_private::right_resource(*action), conf.rres);
//   EXPECT_EQ(access_private::self_right_qnic_id(*action), conf.self_right_qnic_index);
//   EXPECT_EQ(access_private::self_right_qnic_type(*action), conf.self_right_qnic_type);
// }
}  // namespace

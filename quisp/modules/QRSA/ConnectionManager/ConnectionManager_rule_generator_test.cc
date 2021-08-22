#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include "ConnectionManager.h"
#include "gtest/gtest_prod.h"
#include "modules/QNIC.h"
#include "modules/QRSA/ConnectionManager/IConnectionManager.h"
#include "rules/Action.h"
#include "test_utils/TestUtils.h"

namespace {
using namespace omnetpp;
using namespace quisp_test;
class Strategy : public quisp_test::TestComponentProviderStrategy {
 public:
  Strategy() {}
  ~Strategy() {}
};

class ConnectionManager : public quisp::modules::ConnectionManager {
 public:
  using quisp::modules::ConnectionManager::par;
  using quisp::modules::ConnectionManager::purificationRule;
  using quisp::modules::ConnectionManager::swappingRule;

  ConnectionManager() : quisp::modules::ConnectionManager() {
    setParInt(this, "address", 123);
    setParInt(this, "total_number_of_qnics", 10);
    this->setName("connection_manager_test_target");
    this->provider.setStrategy(std::make_unique<Strategy>());
  }
};

TEST(ConnectionManagerRuleGenTest, PurificationRule) {
  ConnectionManager connection_manager;
  int partner_addr = 1;
  int purification_type = 0;  // 0: X, 1: Z
  int num_purification = 1;
  QNIC_type qnic_type = QNIC_E;
  int qnic_id = 4;
  unsigned long ruleset_id = 5;
  unsigned long rule_id = 6;
  std::unique_ptr<Rule> rule;
  rule = connection_manager.purificationRule(partner_addr, purification_type, num_purification, qnic_type, qnic_id, ruleset_id, rule_id);
  ASSERT_NE(rule, nullptr);
  ASSERT_NE(rule->condition, nullptr);

  ASSERT_NE(rule->action, nullptr);
  ASSERT_NE(dynamic_cast<PurifyAction*>(rule->action.get()), nullptr);
  EXPECT_EQ(rule->ruleset_id, ruleset_id);
  EXPECT_EQ(rule->rule_index, rule_id);
  // now action's ruleset_id and rule_id are not used.
  // EXPECT_EQ(rule->action->ruleset_id, ruleset_id);
  // EXPECT_EQ(rule->action->rule_id, rule_id);
  EXPECT_EQ(rule->name, "X purification with : 1");

  purification_type = 1;
  rule = connection_manager.purificationRule(partner_addr, purification_type, num_purification, qnic_type, qnic_id, ruleset_id, rule_id);
  ASSERT_NE(rule, nullptr);
  ASSERT_NE(rule->condition, nullptr);
  ASSERT_NE(rule->action, nullptr);
  ASSERT_NE(dynamic_cast<PurifyAction*>(rule->action.get()), nullptr);
  EXPECT_EQ(rule->ruleset_id, ruleset_id);
  EXPECT_EQ(rule->rule_index, rule_id);
  // EXPECT_EQ(rule->action->ruleset_id, ruleset_id);
  // EXPECT_EQ(rule->action->rule_id, rule_id);
  EXPECT_EQ(rule->name, "Z purification with : 1");
}

TEST(ConnectionManagerRuleGenTest, SwappingRule) {
  ConnectionManager connection_manager;
  unsigned long ruleset_id = 5;
  unsigned long rule_id = 6;
  SwappingConfig conf{.left_partner = 4, .right_partner = 7};
  std::unique_ptr<Rule> rule;
  rule = connection_manager.swappingRule(conf, ruleset_id, rule_id);
  ASSERT_NE(rule, nullptr);
  ASSERT_NE(rule->condition, nullptr);

  ASSERT_NE(rule->action, nullptr);
  ASSERT_NE(dynamic_cast<SwappingAction*>(rule->action.get()), nullptr);
  EXPECT_EQ(rule->ruleset_id, ruleset_id);
  EXPECT_EQ(rule->rule_index, rule_id);
  EXPECT_EQ(rule->action->ruleset_id, ruleset_id);
  EXPECT_EQ(rule->action->rule_id, rule_id);
  EXPECT_EQ(rule->name, "Entanglement Swapping with 4 : 7");
}
}  // namespace

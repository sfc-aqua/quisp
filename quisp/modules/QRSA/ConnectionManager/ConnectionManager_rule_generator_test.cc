#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <omnetpp.h>
#include "ConnectionManager.h"
#include "gtest/gtest_prod.h"
#include "modules/QNIC.h"
#include "modules/QRSA/ConnectionManager/IConnectionManager.h"
#include "rules/Active/ActiveAction.h"
#include "test_utils/TestUtils.h"

ACCESS_PRIVATE_FIELD(quisp::modules::ActiveAction, unsigned long, ruleset_id);
ACCESS_PRIVATE_FIELD(quisp::modules::ActiveAction, unsigned long, rule_id);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, int, qnic_id);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, QNIC_type, qnic_type);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, int, partner);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, int, resource);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, int, trash_resource);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, int, purification_count);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, bool, X);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, bool, Z);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, int, num_purify);
ACCESS_PRIVATE_FIELD(quisp::modules::PurifyAction, int, action_index);

ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, left_partner);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, left_qnic_id);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, self_left_qnic_id);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, left_qnic_address);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, QNIC_type, left_qnic_type);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, QNIC_type, self_left_qnic_type);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, left_resource);

ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, right_partner);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, right_qnic_id);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, self_right_qnic_id);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, right_qnic_address);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, QNIC_type, right_qnic_type);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, QNIC_type, self_right_qnic_type);
ACCESS_PRIVATE_FIELD(quisp::modules::SwappingAction, int, right_resource);

ACCESS_PRIVATE_FIELD(quisp::modules::EnoughResourceClause, int, partner);
ACCESS_PRIVATE_FIELD(quisp::modules::EnoughResourceClause, int, num_resource_required);

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
  int rule_id = 6;
  std::unique_ptr<ActiveRule> rule;
  rule = connection_manager.purificationRule(partner_addr, purification_type, num_purification, qnic_type, qnic_id, ruleset_id, rule_id);
  ASSERT_NE(rule, nullptr);
  ASSERT_NE(rule->condition, nullptr);

  ASSERT_NE(rule->action, nullptr);
  PurifyAction *action;
  action = dynamic_cast<PurifyAction *>(rule->action.get());

  ASSERT_NE(action, nullptr);
  EXPECT_EQ(rule->ruleset_id, ruleset_id);
  EXPECT_EQ(rule->rule_id, rule_id);
  // now action's ruleset_id and rule_id are not used.
  // EXPECT_EQ(rule->action->ruleset_id, ruleset_id);
  // EXPECT_EQ(rule->action->rule_id, rule_id);
  EXPECT_EQ(access_private::rule_id(*action), rule->rule_id);
  EXPECT_EQ(access_private::ruleset_id(*action), ruleset_id);
  EXPECT_EQ(access_private::partner(*action), partner_addr);
  EXPECT_EQ(access_private::X(*action), true);
  EXPECT_EQ(access_private::Z(*action), false);
  EXPECT_EQ(access_private::qnic_id(*action), qnic_id);
  EXPECT_EQ(access_private::qnic_type(*action), qnic_type);
  EXPECT_EQ(access_private::resource(*action), 0);
  EXPECT_EQ(access_private::trash_resource(*action), 1);
  EXPECT_EQ(access_private::action_index(*action), 0);
  EXPECT_EQ(access_private::purification_count(*action), 1);
  EXPECT_EQ(access_private::num_purify(*action), 1);
  EXPECT_EQ(rule->name, "X purification with : 1");

  purification_type = 1;
  rule = connection_manager.purificationRule(partner_addr, purification_type, num_purification, qnic_type, qnic_id, ruleset_id, rule_id);
  ASSERT_NE(rule, nullptr);
  ASSERT_NE(rule->condition, nullptr);
  ASSERT_NE(rule->action, nullptr);
  action = dynamic_cast<PurifyAction *>(rule->action.get());
  ASSERT_NE(action, nullptr);
  EXPECT_EQ(access_private::rule_id(*action), rule->rule_id);
  EXPECT_EQ(access_private::ruleset_id(*action), ruleset_id);
  EXPECT_EQ(access_private::partner(*action), partner_addr);
  EXPECT_EQ(access_private::X(*action), false);
  EXPECT_EQ(access_private::Z(*action), true);
  EXPECT_EQ(access_private::qnic_id(*action), qnic_id);
  EXPECT_EQ(access_private::qnic_type(*action), qnic_type);
  EXPECT_EQ(access_private::resource(*action), 0);
  EXPECT_EQ(access_private::trash_resource(*action), 1);
  EXPECT_EQ(access_private::action_index(*action), 0);
  EXPECT_EQ(access_private::purification_count(*action), 1);
  EXPECT_EQ(access_private::num_purify(*action), 1);
  EXPECT_EQ(rule->ruleset_id, ruleset_id);
  EXPECT_EQ(rule->rule_id, rule_id);
  // EXPECT_EQ(rule->action->ruleset_id, ruleset_id);
  // EXPECT_EQ(rule->action->rule_id, rule_id);
  EXPECT_EQ(rule->name, "Z purification with : 1");
}

TEST(ConnectionManagerRuleGenTest, SwappingRule) {
  ConnectionManager connection_manager;
  unsigned long ruleset_id = 5;
  int rule_id = 6;

  SwappingConfig conf{
      .left_partner = 40,
      .lqnic_type = QNIC_R,
      .lqnic_index = 41,
      .lqnic_address = 42,
      .lres = 43,
      .right_partner = 70,
      .rqnic_type = QNIC_RP,
      .rqnic_index = 71,
      .rqnic_address = 72,
      .rres = 73,
      .self_left_qnic_index = 80,
      .self_left_qnic_type = QNIC_RP,
      .self_right_qnic_index = 81,
      .self_right_qnic_type = QNIC_R,
  };

  std::unique_ptr<ActiveRule> rule;
  rule = connection_manager.swappingRule(conf, ruleset_id, rule_id);
  ASSERT_NE(rule, nullptr);
  ASSERT_NE(rule->condition, nullptr);

  ASSERT_NE(rule->action, nullptr);
  EXPECT_EQ(rule->ruleset_id, ruleset_id);
  EXPECT_EQ(rule->rule_id, rule_id);

  EXPECT_EQ(rule->name, "Entanglement Swapping with 40 : 70");
  EXPECT_EQ(rule->condition->clauses.size(), 2);
  auto *left_clause = dynamic_cast<EnoughResourceClause *>(rule->condition->clauses.at(0));
  EXPECT_EQ(access_private::partner(*left_clause), conf.left_partner);
  EXPECT_EQ(access_private::num_resource_required(*left_clause), 1);

  auto *right_clause = dynamic_cast<EnoughResourceClause *>(rule->condition->clauses.at(1));
  EXPECT_EQ(access_private::partner(*right_clause), conf.right_partner);
  EXPECT_EQ(access_private::num_resource_required(*right_clause), 1);

  auto *action = dynamic_cast<SwappingAction *>(rule->action.get());
  ASSERT_NE(action, nullptr);
  EXPECT_EQ(action->ruleset_id, ruleset_id);
  EXPECT_EQ(action->rule_id, rule_id);
  EXPECT_EQ(access_private::left_partner(*action), conf.left_partner);
  EXPECT_EQ(access_private::left_qnic_id(*action), conf.lqnic_index);
  EXPECT_EQ(access_private::left_qnic_type(*action), conf.lqnic_type);
  EXPECT_EQ(access_private::left_qnic_address(*action), conf.lqnic_address);
  EXPECT_EQ(access_private::left_resource(*action), conf.lres);
  EXPECT_EQ(access_private::self_left_qnic_id(*action), conf.self_left_qnic_index);
  EXPECT_EQ(access_private::self_left_qnic_type(*action), conf.self_left_qnic_type);

  EXPECT_EQ(access_private::right_partner(*action), conf.right_partner);
  EXPECT_EQ(access_private::right_qnic_id(*action), conf.rqnic_index);
  EXPECT_EQ(access_private::right_qnic_type(*action), conf.rqnic_type);
  EXPECT_EQ(access_private::right_qnic_address(*action), conf.rqnic_address);
  EXPECT_EQ(access_private::right_resource(*action), conf.rres);
  EXPECT_EQ(access_private::self_right_qnic_id(*action), conf.self_right_qnic_index);
  EXPECT_EQ(access_private::self_right_qnic_type(*action), conf.self_right_qnic_type);
}
}  // namespace

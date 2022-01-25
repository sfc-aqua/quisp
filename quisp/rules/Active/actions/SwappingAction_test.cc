#include "SwappingAction.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <messages/classical_messages.h>
#include <modules/QNIC.h>
#include <modules/QNIC/StationaryQubit/IStationaryQubit.h>
#include <modules/QNIC/StationaryQubit/StationaryQubit.h>
#include <modules/QRSA/RuleEngine/IRuleEngine.h>
#include <modules/QRSA/RuleEngine/RuleEngine.h>
#include <test_utils/TestUtils.h>

namespace {

using namespace testing;
using namespace quisp::messages;
using namespace quisp_test;

using quisp::modules::IRuleEngine;
using quisp::modules::IStationaryQubit;
using quisp::modules::QNIC_E;
using quisp::modules::QNIC_type;
using quisp::modules::StationaryQubit;
using OriginalSwappingAction = quisp::rules::active::actions::SwappingAction;

class SwappingAction : public OriginalSwappingAction {
 public:
  using OriginalSwappingAction::left_partner;
  using OriginalSwappingAction::left_qnic_address;
  using OriginalSwappingAction::left_qnic_id;
  using OriginalSwappingAction::left_qnic_type;
  using OriginalSwappingAction::left_resource;
  using OriginalSwappingAction::right_partner;
  using OriginalSwappingAction::right_qnic_address;
  using OriginalSwappingAction::right_qnic_id;
  using OriginalSwappingAction::right_qnic_type;
  using OriginalSwappingAction::right_resource;
  using OriginalSwappingAction::self_left_qnic_id;
  using OriginalSwappingAction::self_left_qnic_type;
  using OriginalSwappingAction::self_right_qnic_id;
  using OriginalSwappingAction::self_right_qnic_type;
  using OriginalSwappingAction::SwappingAction;
  static std::unique_ptr<SwappingAction> setupAction() {
    unsigned long ruleset_id = 0;
    unsigned long rule_id = 1;

    int left_partner_addr = 2;
    QNIC_type left_qnic_type = QNIC_E;
    int left_qnic_id = 3;
    int left_qnic_addr = 4;
    int left_resource = 5;

    int right_partner_addr = 6;
    QNIC_type right_qnic_type = QNIC_E;
    int right_qnic_id = 7;
    int right_qnic_addr = 8;
    int right_resource = 9;

    int self_left_qnic_id = 11;
    QNIC_type self_left_qnic_type = QNIC_E;
    int self_right_qnic_id = 13;
    QNIC_type self_right_qnic_type = QNIC_E;

    return std::make_unique<SwappingAction>(ruleset_id, rule_id, left_partner_addr, left_qnic_type, left_qnic_id, left_qnic_addr, left_resource, right_partner_addr,
                                            right_qnic_type, right_qnic_id, right_qnic_addr, right_resource, self_left_qnic_id, self_left_qnic_type, self_right_qnic_id,
                                            self_right_qnic_type);
  }

  MOCK_METHOD(IStationaryQubit *, getResource, (int required_index, int partner), (override));
  MOCK_METHOD(void, removeResource_fromRule, (IStationaryQubit *), (override));
};

class SwappingActionTest : public ::testing::Test {
 protected:
  void SetUp() override {
    prepareSimulation();
    action = SwappingAction::setupAction();
    rule_engine = new MockRuleEngine();
    right_qubit = new MockQubit();
    left_qubit = new MockQubit();
    left_partner_qubit = new MockQubit();
    right_partner_qubit = new MockQubit();
  }
  void TearDown() override {
    delete rule_engine;
    delete right_qubit;
    delete left_qubit;
    delete left_partner_qubit;
    delete right_partner_qubit;
  }
  MockRuleEngine *rule_engine = nullptr;
  std::unique_ptr<SwappingAction> action = nullptr;
  MockQubit *right_qubit = nullptr;
  MockQubit *left_qubit = nullptr;
  MockQubit *left_partner_qubit = nullptr;
  MockQubit *right_partner_qubit = nullptr;
};

TEST_F(SwappingActionTest, init) {
  unsigned long ruleset_id = 0;
  unsigned long rule_id = 1;

  int left_partner_addr = 2;
  QNIC_type left_qnic_type = QNIC_E;
  int left_qnic_id = 3;
  int left_qnic_addr = 4;
  int left_resource = 5;

  int right_partner_addr = 6;
  QNIC_type right_qnic_type = QNIC_E;
  int right_qnic_id = 7;
  int right_qnic_addr = 8;
  int right_resource = 9;

  int self_left_qnic_id = 11;
  QNIC_type self_left_qnic_type = QNIC_E;
  int self_right_qnic_id = 13;
  QNIC_type self_right_qnic_type = QNIC_E;

  auto action = new SwappingAction(ruleset_id, rule_id, left_partner_addr, left_qnic_type, left_qnic_id, left_qnic_addr, left_resource, right_partner_addr, right_qnic_type,
                                   right_qnic_id, right_qnic_addr, right_resource, self_left_qnic_id, self_left_qnic_type, self_right_qnic_id, self_right_qnic_type);
  EXPECT_EQ(ruleset_id, action->ruleset_id);
  EXPECT_EQ(rule_id, action->rule_id);
  EXPECT_EQ(left_partner_addr, action->left_partner);
  EXPECT_EQ(right_partner_addr, action->right_partner);
  EXPECT_EQ(left_qnic_id, action->left_qnic_id);
  EXPECT_EQ(right_qnic_id, action->right_qnic_id);
  EXPECT_EQ(left_qnic_addr, action->left_qnic_address);
  EXPECT_EQ(right_qnic_addr, action->right_qnic_address);
  EXPECT_EQ(left_qnic_type, action->left_qnic_type);
  EXPECT_EQ(right_qnic_type, action->right_qnic_type);
  EXPECT_EQ(left_resource, action->left_resource);
  EXPECT_EQ(right_resource, action->right_resource);
  EXPECT_EQ(self_left_qnic_id, action->self_left_qnic_id);
  EXPECT_EQ(self_right_qnic_id, action->self_right_qnic_id);
  EXPECT_EQ(self_left_qnic_type, action->self_left_qnic_type);
  EXPECT_EQ(self_right_qnic_type, action->self_right_qnic_type);
}

TEST_F(SwappingActionTest, runWithoutQubit) {
  action->right_resource = 21;
  action->right_partner = 22;
  action->left_resource = 23;
  action->left_partner = 24;
  EXPECT_CALL(*action, getResource(21, 22)).WillOnce(Return(nullptr));
  EXPECT_CALL(*action, getResource(23, 24)).WillOnce(Return(nullptr));

  auto packet = action->run(nullptr);

  EXPECT_NE(nullptr, packet);
  EXPECT_NE(nullptr, dynamic_cast<Error *>(packet));
}

TEST_F(SwappingActionTest, runWithInvalidQnicId) {
  action->right_resource = 21;
  action->right_partner = 22;
  action->left_resource = 23;
  action->left_partner = 24;
  action->left_qnic_id = -1;
  action->right_qnic_id = -1;
  right_qubit->fillParams();
  left_qubit->fillParams();

  EXPECT_CALL(*action, getResource(21, 22)).WillOnce(Return(right_qubit));
  EXPECT_CALL(*action, getResource(23, 24)).WillOnce(Return(left_qubit));

  auto packet = action->run(rule_engine);

  EXPECT_NE(nullptr, packet);
  EXPECT_NE(nullptr, dynamic_cast<Error *>(packet));
}

TEST_F(SwappingActionTest, runWithMeasuredResult00) {
  action->right_resource = 21;
  action->right_partner = 22;
  action->left_resource = 23;
  action->left_partner = 24;
  action->self_left_qnic_id = 25;
  action->self_right_qnic_id = 26;
  right_qubit->fillParams();
  left_qubit->fillParams();
  left_partner_qubit->fillParams();
  right_partner_qubit->fillParams();
  right_qubit->entangled_partner = right_partner_qubit;
  right_partner_qubit->entangled_partner = right_qubit;
  left_qubit->entangled_partner = left_partner_qubit;
  left_partner_qubit->entangled_partner = left_qubit;

  EXPECT_CALL(*right_qubit, CNOT_gate(left_qubit));
  EXPECT_CALL(*left_qubit, localMeasureX()).WillOnce(Return(quisp::types::EigenvalueResult::PLUS_ONE));
  EXPECT_CALL(*right_qubit, localMeasureZ()).WillOnce(Return(quisp::types::EigenvalueResult::PLUS_ONE));
  EXPECT_CALL(*left_partner_qubit, setEntangledPartnerInfo(right_partner_qubit));
  EXPECT_CALL(*right_partner_qubit, setEntangledPartnerInfo(left_partner_qubit));

  EXPECT_CALL(*action, getResource(21, 22)).WillOnce(Return(right_qubit));
  EXPECT_CALL(*action, getResource(23, 24)).WillOnce(Return(left_qubit));
  EXPECT_CALL(*action, removeResource_fromRule(right_qubit));
  EXPECT_CALL(*action, removeResource_fromRule(left_qubit));
  EXPECT_CALL(*rule_engine, freeConsumedResource(25, left_qubit, QNIC_E));
  EXPECT_CALL(*rule_engine, freeConsumedResource(26, right_qubit, QNIC_E));

  auto packet = action->run(rule_engine);

  ASSERT_NE(nullptr, packet);
  auto result = dynamic_cast<SwappingResult *>(packet);
  ASSERT_NE(nullptr, result);
  EXPECT_EQ(0, result->getOperation_type_left());
  EXPECT_EQ(0, result->getOperation_type_right());
}

TEST_F(SwappingActionTest, runWithMeasuredResult01) {
  action->right_resource = 21;
  action->right_partner = 22;
  action->left_resource = 23;
  action->left_partner = 24;
  action->self_left_qnic_id = 25;
  action->self_right_qnic_id = 26;
  right_qubit->fillParams();
  left_qubit->fillParams();
  left_partner_qubit->fillParams();
  right_partner_qubit->fillParams();
  right_qubit->entangled_partner = right_partner_qubit;
  right_partner_qubit->entangled_partner = right_qubit;
  left_qubit->entangled_partner = left_partner_qubit;
  left_partner_qubit->entangled_partner = left_qubit;

  EXPECT_CALL(*right_qubit, CNOT_gate(left_qubit));
  EXPECT_CALL(*left_qubit, localMeasureX()).WillOnce(Return(quisp::types::EigenvalueResult::PLUS_ONE));
  EXPECT_CALL(*right_qubit, localMeasureZ()).WillOnce(Return(quisp::types::EigenvalueResult::MINUS_ONE));
  EXPECT_CALL(*right_partner_qubit, setEntangledPartnerInfo(left_partner_qubit));
  EXPECT_CALL(*left_partner_qubit, setEntangledPartnerInfo(right_partner_qubit));

  EXPECT_CALL(*action, getResource(21, 22)).WillOnce(Return(right_qubit));
  EXPECT_CALL(*action, getResource(23, 24)).WillOnce(Return(left_qubit));
  EXPECT_CALL(*action, removeResource_fromRule(right_qubit));
  EXPECT_CALL(*action, removeResource_fromRule(left_qubit));
  EXPECT_CALL(*rule_engine, freeConsumedResource(25, left_qubit, QNIC_E));
  EXPECT_CALL(*rule_engine, freeConsumedResource(26, right_qubit, QNIC_E));

  auto packet = action->run(rule_engine);

  ASSERT_NE(nullptr, packet);
  auto result = dynamic_cast<SwappingResult *>(packet);
  ASSERT_NE(nullptr, result);
  EXPECT_EQ(0, result->getOperation_type_left());
  EXPECT_EQ(1, result->getOperation_type_right());
}

TEST_F(SwappingActionTest, runWithMeasuredResult10) {
  action->right_resource = 21;
  action->right_partner = 22;
  action->left_resource = 23;
  action->left_partner = 24;
  action->self_left_qnic_id = 25;
  action->self_right_qnic_id = 26;
  right_qubit->fillParams();
  left_qubit->fillParams();
  left_partner_qubit->fillParams();
  right_partner_qubit->fillParams();
  right_qubit->entangled_partner = right_partner_qubit;
  right_partner_qubit->entangled_partner = right_qubit;
  left_qubit->entangled_partner = left_partner_qubit;
  left_partner_qubit->entangled_partner = left_qubit;

  EXPECT_CALL(*right_qubit, CNOT_gate(left_qubit));
  EXPECT_CALL(*left_qubit, localMeasureX()).WillOnce(Return(quisp::types::EigenvalueResult::MINUS_ONE));
  EXPECT_CALL(*right_qubit, localMeasureZ()).WillOnce(Return(quisp::types::EigenvalueResult::PLUS_ONE));
  EXPECT_CALL(*right_partner_qubit, setEntangledPartnerInfo(left_partner_qubit));
  EXPECT_CALL(*left_partner_qubit, setEntangledPartnerInfo(right_partner_qubit));

  EXPECT_CALL(*action, getResource(21, 22)).WillOnce(Return(right_qubit));
  EXPECT_CALL(*action, getResource(23, 24)).WillOnce(Return(left_qubit));
  EXPECT_CALL(*action, removeResource_fromRule(right_qubit));
  EXPECT_CALL(*action, removeResource_fromRule(left_qubit));
  EXPECT_CALL(*rule_engine, freeConsumedResource(25, left_qubit, QNIC_E));
  EXPECT_CALL(*rule_engine, freeConsumedResource(26, right_qubit, QNIC_E));

  auto packet = action->run(rule_engine);

  ASSERT_NE(nullptr, packet);
  auto result = dynamic_cast<SwappingResult *>(packet);
  ASSERT_NE(nullptr, result);
  EXPECT_EQ(2, result->getOperation_type_left());
  EXPECT_EQ(0, result->getOperation_type_right());
}

TEST_F(SwappingActionTest, runWithMeasuredResult11) {
  action->right_resource = 21;
  action->right_partner = 22;
  action->left_resource = 23;
  action->left_partner = 24;
  action->self_left_qnic_id = 25;
  action->self_right_qnic_id = 26;
  right_qubit->fillParams();
  left_qubit->fillParams();
  left_partner_qubit->fillParams();
  right_partner_qubit->fillParams();
  right_qubit->entangled_partner = right_partner_qubit;
  right_partner_qubit->entangled_partner = right_qubit;
  left_qubit->entangled_partner = left_partner_qubit;
  left_partner_qubit->entangled_partner = left_qubit;

  EXPECT_CALL(*right_qubit, CNOT_gate(left_qubit));
  EXPECT_CALL(*left_qubit, localMeasureX()).WillOnce(Return(quisp::types::EigenvalueResult::MINUS_ONE));
  EXPECT_CALL(*right_qubit, localMeasureZ()).WillOnce(Return(quisp::types::EigenvalueResult::MINUS_ONE));
  EXPECT_CALL(*right_partner_qubit, setEntangledPartnerInfo(left_partner_qubit));
  EXPECT_CALL(*left_partner_qubit, setEntangledPartnerInfo(right_partner_qubit));

  EXPECT_CALL(*action, getResource(21, 22)).WillOnce(Return(right_qubit));
  EXPECT_CALL(*action, getResource(23, 24)).WillOnce(Return(left_qubit));
  EXPECT_CALL(*action, removeResource_fromRule(right_qubit));
  EXPECT_CALL(*action, removeResource_fromRule(left_qubit));
  EXPECT_CALL(*rule_engine, freeConsumedResource(25, left_qubit, QNIC_E));
  EXPECT_CALL(*rule_engine, freeConsumedResource(26, right_qubit, QNIC_E));

  auto packet = action->run(rule_engine);

  ASSERT_NE(nullptr, packet);
  auto result = dynamic_cast<SwappingResult *>(packet);
  ASSERT_NE(nullptr, result);
  EXPECT_EQ(2, result->getOperation_type_left());
  EXPECT_EQ(1, result->getOperation_type_right());
}
}  // namespace

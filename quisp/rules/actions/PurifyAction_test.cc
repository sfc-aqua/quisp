#include "PurifyAction.h"
#include <classical_messages_m.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <modules/QNIC.h>
#include <modules/QNIC/StationaryQubit/StationaryQubit.h>
#include <modules/QRSA/RuleEngine/IRuleEngine.h>
#include <test_utils/TestUtils.h>
#include "modules/QRSA/RuleEngine/RuleEngine.h"

namespace {
using namespace testing;
using namespace quisp::messages;
using namespace quisp_test;

using quisp::modules::IRuleEngine;
using quisp::modules::IStationaryQubit;
using quisp::modules::QNIC_E;
using quisp::modules::QNIC_type;
using quisp::modules::StationaryQubit;
using OriginalPurifyAction = quisp::rules::actions::PurifyAction;

class PurifyAction : public OriginalPurifyAction {
 public:
  using OriginalPurifyAction::action_index;
  using OriginalPurifyAction::num_purify;
  using OriginalPurifyAction::partner;
  using OriginalPurifyAction::PurifyAction;
  using OriginalPurifyAction::qnic_id;
  using OriginalPurifyAction::qnic_type;
  using OriginalPurifyAction::resource;
  using OriginalPurifyAction::rule_id;
  using OriginalPurifyAction::ruleset_id;
  using OriginalPurifyAction::trash_resource;
  using OriginalPurifyAction::X;
  using OriginalPurifyAction::Z;

  static std::unique_ptr<PurifyAction> setupAction() {
    int partner_addr = 2;
    QNIC_type qnic_type = QNIC_E;
    int qnic_id = 3;
    int resource_index = 4;
    int trash_resource_index = 5;
    unsigned long ruleset_id = 6;
    unsigned long rule_id = 7;
    bool x_purification_enabled = false;
    bool z_purification_enabled = false;
    int num_purification = 8;

    return std::make_unique<PurifyAction>(ruleset_id, rule_id, x_purification_enabled, z_purification_enabled, num_purification, partner_addr, qnic_type, qnic_id, resource_index,
                                          trash_resource_index);
  }
  MOCK_METHOD(IStationaryQubit *, getResource, (int required_index, int partner), (override));
  MOCK_METHOD(void, removeResource_fromRule, (IStationaryQubit *), (override));
};

TEST(PurifyActionTest, Init) {
  int partner_addr = 2;
  QNIC_type qnic_type = QNIC_E;
  int qnic_id = 3;
  int resource_index = 4;
  int trash_resource_index = 5;
  unsigned long ruleset_id = 6;
  unsigned long rule_id = 7;
  bool x_purification_enabled = true;
  bool z_purification_enabled = true;
  int num_purification = 8;

  auto *action = new PurifyAction(ruleset_id, rule_id, x_purification_enabled, z_purification_enabled, num_purification, partner_addr, qnic_type, qnic_id, resource_index,
                                  trash_resource_index);
  EXPECT_EQ(action->partner, partner_addr);
  EXPECT_EQ(action->qnic_type, QNIC_E);
  EXPECT_EQ(action->qnic_id, qnic_id);
  EXPECT_EQ(action->resource, resource_index);
  EXPECT_EQ(action->trash_resource, trash_resource_index);
  EXPECT_EQ(action->ruleset_id, ruleset_id);
  EXPECT_EQ(action->rule_id, rule_id);
  EXPECT_EQ(action->X, x_purification_enabled);
  EXPECT_EQ(action->Z, z_purification_enabled);
  EXPECT_EQ(action->num_purify, num_purification);
}

TEST(PurifyActionTest, runWithoutQubit) {
  prepareSimulation();
  auto action = PurifyAction::setupAction();
  auto *rule_engine = new MockRuleEngine();
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).WillOnce(Return(nullptr));
  EXPECT_CALL(*action, getResource(action->trash_resource, action->partner)).WillOnce(Return(nullptr));
  auto packet = action->run(rule_engine);
  ASSERT_NE(packet, nullptr);
  auto result = dynamic_cast<Error *>(packet);
  ASSERT_NE(result, nullptr);
}

TEST(PurifyActionTest, runWithOneQubit) {
  auto sim = prepareSimulation();
  auto action = PurifyAction::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  sim->registerComponent(qubit);
  qubit->fillParams();
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource, action->partner)).WillOnce(Return(nullptr));
  auto packet = action->run(rule_engine);
  ASSERT_NE(packet, nullptr);
  auto result = dynamic_cast<Error *>(packet);
  ASSERT_NE(result, nullptr);
}

TEST(PurifyActionTest, runWithSameQubit) {
  auto sim = prepareSimulation();
  auto action = PurifyAction::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  sim->registerComponent(qubit);
  qubit->fillParams();
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource, action->partner)).WillOnce(Return(qubit));
  auto packet = action->run(rule_engine);
  ASSERT_NE(packet, nullptr);
  auto result = dynamic_cast<Error *>(packet);
  ASSERT_NE(result, nullptr);
}

TEST(PurifyActionTest, runXPurifyOutcomeTrue) {
  prepareSimulation();
  auto action = PurifyAction::setupAction();
  action->X = true;
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *trash_qubit = new MockQubit();

  EXPECT_CALL(*qubit, Lock(action->ruleset_id, action->rule_id, action->action_index)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).Times(1).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource, action->partner)).WillOnce(Return(trash_qubit));
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit)).Times(1).WillOnce(Return());

  EXPECT_CALL(*trash_qubit, Xpurify(qubit)).Times(1).WillOnce(Return(true));

  auto packet = action->run(rule_engine);

  ASSERT_NE(packet, nullptr);
  PurificationResult *result = dynamic_cast<PurificationResult *>(packet);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->getDestAddr(), action->partner);
  EXPECT_EQ(result->getRule_id(), action->rule_id);
  EXPECT_EQ(result->getRuleset_id(), action->ruleset_id);
  EXPECT_EQ(result->getEntangled_with(), qubit);
  EXPECT_EQ(result->getOutput_is_plus(), true);

  delete qubit;
  delete trash_qubit;
  delete rule_engine;
}

TEST(PurifyActionTest, runXPurifyOutcomeFalse) {
  prepareSimulation();
  auto action = PurifyAction::setupAction();
  action->X = true;
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *trash_qubit = new MockQubit();

  EXPECT_CALL(*qubit, Lock(action->ruleset_id, action->rule_id, action->action_index)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).Times(1).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource, action->partner)).WillOnce(Return(trash_qubit));
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit)).Times(1).WillOnce(Return());

  EXPECT_CALL(*trash_qubit, Xpurify(qubit)).Times(1).WillOnce(Return(false));

  auto packet = action->run(rule_engine);

  ASSERT_NE(packet, nullptr);
  PurificationResult *result = dynamic_cast<PurificationResult *>(packet);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->getDestAddr(), action->partner);
  EXPECT_EQ(result->getRule_id(), action->rule_id);
  EXPECT_EQ(result->getRuleset_id(), action->ruleset_id);
  EXPECT_EQ(result->getEntangled_with(), qubit);
  EXPECT_EQ(result->getOutput_is_plus(), false);

  delete qubit;
  delete trash_qubit;
  delete rule_engine;
}

TEST(PurifyActionTest, runZPurifyOutcomeTrue) {
  prepareSimulation();
  auto action = PurifyAction::setupAction();
  action->Z = true;
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *trash_qubit = new MockQubit();

  EXPECT_CALL(*qubit, Lock(action->ruleset_id, action->rule_id, action->action_index)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).Times(1).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource, action->partner)).WillOnce(Return(trash_qubit));
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit)).Times(1).WillOnce(Return());

  EXPECT_CALL(*trash_qubit, Zpurify(qubit)).Times(1).WillOnce(Return(true));

  auto packet = action->run(rule_engine);

  ASSERT_NE(packet, nullptr);
  PurificationResult *result = dynamic_cast<PurificationResult *>(packet);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->getDestAddr(), action->partner);
  EXPECT_EQ(result->getRule_id(), action->rule_id);
  EXPECT_EQ(result->getRuleset_id(), action->ruleset_id);
  EXPECT_EQ(result->getEntangled_with(), qubit);
  EXPECT_EQ(result->getOutput_is_plus(), true);

  delete qubit;
  delete trash_qubit;
  delete rule_engine;
}

TEST(PurifyActionTest, runZPurifyOutcomeFalse) {
  prepareSimulation();
  auto action = PurifyAction::setupAction();
  action->Z = true;
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *trash_qubit = new MockQubit();

  EXPECT_CALL(*qubit, Lock(action->ruleset_id, action->rule_id, action->action_index)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).Times(1).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource, action->partner)).WillOnce(Return(trash_qubit));
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit)).Times(1).WillOnce(Return());

  EXPECT_CALL(*trash_qubit, Zpurify(qubit)).Times(1).WillOnce(Return(false));

  auto packet = action->run(rule_engine);

  ASSERT_NE(packet, nullptr);
  PurificationResult *result = dynamic_cast<PurificationResult *>(packet);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->getDestAddr(), action->partner);
  EXPECT_EQ(result->getRule_id(), action->rule_id);
  EXPECT_EQ(result->getRuleset_id(), action->ruleset_id);
  EXPECT_EQ(result->getEntangled_with(), qubit);
  EXPECT_EQ(result->getOutput_is_plus(), false);

  delete qubit;
  delete trash_qubit;
  delete rule_engine;
}
}  // namespace

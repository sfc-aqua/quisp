#include "DoubleSelectionDualAction.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <messages/classical_messages.h>
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
using OriginalDoubleSelectionDualAction = quisp::rules::active::actions::DoubleSelectionDualAction;

class DoubleSelectionDualAction : public OriginalDoubleSelectionDualAction {
 public:
  using OriginalDoubleSelectionDualAction::action_index;
  using OriginalDoubleSelectionDualAction::rule_id;
  using OriginalDoubleSelectionDualAction::ruleset_id;

  using OriginalDoubleSelectionDualAction::doubleselection_trash_resource_X;
  using OriginalDoubleSelectionDualAction::doubleselection_trash_resource_Z;
  using OriginalDoubleSelectionDualAction::DoubleSelectionDualAction;
  using OriginalDoubleSelectionDualAction::num_purify;
  using OriginalDoubleSelectionDualAction::partner;
  using OriginalDoubleSelectionDualAction::purification_count;
  using OriginalDoubleSelectionDualAction::qnic_id;
  using OriginalDoubleSelectionDualAction::qnic_type;
  using OriginalDoubleSelectionDualAction::resource;
  using OriginalDoubleSelectionDualAction::trash_resource_X;
  using OriginalDoubleSelectionDualAction::trash_resource_Z;

  static std::unique_ptr<DoubleSelectionDualAction> setupAction() {
    int partner_addr = 2;
    QNIC_type qnic_type = QNIC_E;
    int qnic_id = 3;
    int resource_index = 1;
    int trash_resource_x = 2;
    int trash_resource_z = 3;
    int double_trash_resource_x = 4;
    int double_trash_resource_z = 5;
    unsigned long ruleset_id = 6;
    int rule_id = 7;
    int shared_tag = 3;

    return std::make_unique<DoubleSelectionDualAction>(ruleset_id, rule_id, shared_tag, partner_addr, qnic_type, qnic_id, resource_index, trash_resource_x, trash_resource_z,
                                                       double_trash_resource_x, double_trash_resource_z);
  }
  MOCK_METHOD(IStationaryQubit *, getResource, (int required_index, int partner), (override));
  MOCK_METHOD(void, removeResource_fromRule, (IStationaryQubit *), (override));
};

TEST(DoubleSelectionDualAction, Init) {
  int partner_addr = 2;
  QNIC_type qnic_type = QNIC_E;
  int qnic_id = 3;
  int resource_index = 4;
  int trash_resource_x = 5;
  int trash_resource_z = 6;
  int double_trash_resource_x = 7;
  int double_trash_resource_z = 8;
  unsigned long ruleset_id = 120;
  int rule_id = 2340;
  int shared_tag = 3;

  auto *action = new DoubleSelectionDualAction(ruleset_id, rule_id, shared_tag, partner_addr, qnic_type, qnic_id, resource_index, trash_resource_x, trash_resource_z,
                                               double_trash_resource_x, double_trash_resource_z);
  EXPECT_EQ(action->partner, partner_addr);
  EXPECT_EQ(action->qnic_type, QNIC_E);
  EXPECT_EQ(action->qnic_id, qnic_id);
  EXPECT_EQ(action->resource, resource_index);
  EXPECT_EQ(action->trash_resource_X, trash_resource_x);
  EXPECT_EQ(action->trash_resource_Z, trash_resource_z);
  EXPECT_EQ(action->ruleset_id, ruleset_id);
  EXPECT_EQ(action->rule_id, rule_id);
}

TEST(DoubleSelectionDualAction, runWithoutQubit) {
  prepareSimulation();
  auto action = DoubleSelectionDualAction::setupAction();
  auto *rule_engine = new MockRuleEngine();
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).WillOnce(Return(nullptr));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(nullptr));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(nullptr));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(nullptr));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_Z, action->partner)).WillOnce(Return(nullptr));
  auto packet = action->run(rule_engine);
  ASSERT_NE(packet, nullptr);
  auto result = dynamic_cast<Error *>(packet);
  ASSERT_NE(result, nullptr);
}

TEST(DoubleSelectionDualAction, NoTrashQubit) {
  auto sim = prepareSimulation();
  auto action = DoubleSelectionDualAction::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  sim->registerComponent(qubit);
  qubit->fillParams();
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(nullptr));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(nullptr));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(nullptr));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_Z, action->partner)).WillOnce(Return(nullptr));
  auto packet = action->run(rule_engine);
  ASSERT_NE(packet, nullptr);
  auto result = dynamic_cast<Error *>(packet);
  ASSERT_NE(result, nullptr);
}

TEST(DoubleSelectionDualAction, NoTrashXQubit) {
  auto sim = prepareSimulation();
  auto action = DoubleSelectionDualAction::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *trash_qubit_z = new MockQubit();
  auto *ds_trash_qubit_x = new MockQubit();
  auto *ds_trash_qubit_z = new MockQubit();
  sim->registerComponent(qubit);
  qubit->fillParams();
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(nullptr));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(trash_qubit_z));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(ds_trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_Z, action->partner)).WillOnce(Return(ds_trash_qubit_z));

  auto packet = action->run(rule_engine);
  ASSERT_NE(packet, nullptr);
  auto result = dynamic_cast<Error *>(packet);
  ASSERT_NE(result, nullptr);
}

TEST(DoubleSelectionDualAction, NoTrashZQubit) {
  auto sim = prepareSimulation();
  auto action = DoubleSelectionDualAction::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *trash_qubit_x = new MockQubit();
  auto *ds_trash_qubit_x = new MockQubit();
  auto *ds_trash_qubit_z = new MockQubit();
  sim->registerComponent(qubit);
  qubit->fillParams();
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(nullptr));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(ds_trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_Z, action->partner)).WillOnce(Return(ds_trash_qubit_z));

  auto packet = action->run(rule_engine);
  ASSERT_NE(packet, nullptr);
  auto result = dynamic_cast<Error *>(packet);
  ASSERT_NE(result, nullptr);
}

TEST(DoubleSelectionDualAction, NoDsTrashXQubit) {
  auto sim = prepareSimulation();
  auto action = DoubleSelectionDualAction::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *trash_qubit_x = new MockQubit();
  auto *trash_qubit_z = new MockQubit();
  auto *ds_trash_qubit_z = new MockQubit();
  sim->registerComponent(qubit);
  qubit->fillParams();
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(trash_qubit_z));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(nullptr));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_Z, action->partner)).WillOnce(Return(ds_trash_qubit_z));

  auto packet = action->run(rule_engine);
  ASSERT_NE(packet, nullptr);
  auto result = dynamic_cast<Error *>(packet);
  ASSERT_NE(result, nullptr);
}

TEST(DoubleSelectionDualAction, NoDsTrashZQubit) {
  auto sim = prepareSimulation();
  auto action = DoubleSelectionDualAction::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *trash_qubit_x = new MockQubit();
  auto *trash_qubit_z = new MockQubit();
  auto *ds_trash_qubit_x = new MockQubit();
  sim->registerComponent(qubit);
  qubit->fillParams();
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(trash_qubit_z));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(ds_trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_Z, action->partner)).WillOnce(Return(nullptr));

  auto packet = action->run(rule_engine);
  ASSERT_NE(packet, nullptr);
  auto result = dynamic_cast<Error *>(packet);
  ASSERT_NE(result, nullptr);
}

TEST(DoubleSelectionDualAction, TrashQubitDuplication1) {
  auto sim = prepareSimulation();
  auto action = DoubleSelectionDualAction::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *dup_trash_qubit = new MockQubit();
  //   auto *trash_qubit_x = new MockQubit();
  //   auto *trash_qubit_z = new MockQubit();
  auto *ds_trash_qubit_x = new MockQubit();
  auto *ds_trash_qubit_z = new MockQubit();

  sim->registerComponent(qubit);
  qubit->fillParams();
  //  duplicate trash_X and trash_Z
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(dup_trash_qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(dup_trash_qubit));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(ds_trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_Z, action->partner)).WillOnce(Return(ds_trash_qubit_z));
  auto packet = action->run(rule_engine);
  ASSERT_NE(packet, nullptr);
  auto result = dynamic_cast<Error *>(packet);
  ASSERT_NE(result, nullptr);
}

TEST(DoubleSelectionDualAction, TrashQubitDuplication2) {
  auto sim = prepareSimulation();
  auto action = DoubleSelectionDualAction::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *dup_trash_qubit = new MockQubit();
  //   auto *trash_qubit_x = new MockQubit();
  auto *trash_qubit_z = new MockQubit();
  //   auto *ds_trash_qubit_x = new MockQubit();
  auto *ds_trash_qubit_z = new MockQubit();

  sim->registerComponent(qubit);
  qubit->fillParams();
  //  duplicate trash_X and doubleselection_trash_X
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(dup_trash_qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(trash_qubit_z));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(dup_trash_qubit));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_Z, action->partner)).WillOnce(Return(ds_trash_qubit_z));
  auto packet = action->run(rule_engine);
  ASSERT_NE(packet, nullptr);
  auto result = dynamic_cast<Error *>(packet);
  ASSERT_NE(result, nullptr);
}

TEST(DoubleSelectionDualAction, TrashQubitDuplication3) {
  auto sim = prepareSimulation();
  auto action = DoubleSelectionDualAction::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *dup_trash_qubit = new MockQubit();
  //   auto *trash_qubit_x = new MockQubit();
  auto *trash_qubit_z = new MockQubit();
  auto *ds_trash_qubit_x = new MockQubit();
  //   auto *ds_trash_qubit_z = new MockQubit();

  sim->registerComponent(qubit);
  qubit->fillParams();
  //  duplicate trash_X and doubleselection_trash_Z
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(dup_trash_qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(trash_qubit_z));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(ds_trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_Z, action->partner)).WillOnce(Return(dup_trash_qubit));
  auto packet = action->run(rule_engine);
  ASSERT_NE(packet, nullptr);
  auto result = dynamic_cast<Error *>(packet);
  ASSERT_NE(result, nullptr);
}

TEST(DoubleSelectionDualAction, TrashQubitDuplication4) {
  auto sim = prepareSimulation();
  auto action = DoubleSelectionDualAction::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *dup_trash_qubit = new MockQubit();
  auto *trash_qubit_x = new MockQubit();
  //   auto *trash_qubit_z = new MockQubit();
  //   auto *ds_trash_qubit_x = new MockQubit();
  auto *ds_trash_qubit_z = new MockQubit();

  sim->registerComponent(qubit);
  qubit->fillParams();
  //  duplicate trash_Z and doubleselection_trash_X
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(dup_trash_qubit));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(dup_trash_qubit));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_Z, action->partner)).WillOnce(Return(ds_trash_qubit_z));
  auto packet = action->run(rule_engine);
  ASSERT_NE(packet, nullptr);
  auto result = dynamic_cast<Error *>(packet);
  ASSERT_NE(result, nullptr);
}

TEST(DoubleSelectionDualAction, TrashQubitDuplication5) {
  auto sim = prepareSimulation();
  auto action = DoubleSelectionDualAction::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *dup_trash_qubit = new MockQubit();
  auto *trash_qubit_x = new MockQubit();
  //   auto *trash_qubit_z = new MockQubit();
  auto *ds_trash_qubit_x = new MockQubit();
  //   auto *ds_trash_qubit_z = new MockQubit();

  sim->registerComponent(qubit);
  qubit->fillParams();
  //  duplicate trash_Z and doubleselection_trash_Z
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(dup_trash_qubit));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(ds_trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_Z, action->partner)).WillOnce(Return(dup_trash_qubit));
  auto packet = action->run(rule_engine);
  ASSERT_NE(packet, nullptr);
  auto result = dynamic_cast<Error *>(packet);
  ASSERT_NE(result, nullptr);
}

TEST(DoubleSelectionDualAction, TrashQubitDuplication6) {
  auto sim = prepareSimulation();
  auto action = DoubleSelectionDualAction::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *dup_trash_qubit = new MockQubit();
  auto *trash_qubit_x = new MockQubit();
  auto *trash_qubit_z = new MockQubit();
  //   auto *ds_trash_qubit_x = new MockQubit();
  //   auto *ds_trash_qubit_z = new MockQubit();

  sim->registerComponent(qubit);
  qubit->fillParams();
  //  duplicate double_selection_trash_X and doubleselection_trash_Z
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(trash_qubit_z));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(dup_trash_qubit));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_Z, action->partner)).WillOnce(Return(dup_trash_qubit));
  auto packet = action->run(rule_engine);
  ASSERT_NE(packet, nullptr);
  auto result = dynamic_cast<Error *>(packet);
  ASSERT_NE(result, nullptr);
}

TEST(DoubleSelectionDualAction, AllOutcomeTrue) {
  prepareSimulation();
  auto action = DoubleSelectionDualAction::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *trash_qubit_x = new MockQubit();
  auto *trash_qubit_z = new MockQubit();
  auto *ds_trash_qubit_x = new MockQubit();
  auto *ds_trash_qubit_z = new MockQubit();

  EXPECT_CALL(*qubit, Lock(action->ruleset_id, action->rule_id, action->action_index)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit_x, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit_z, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, ds_trash_qubit_x, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, ds_trash_qubit_z, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).Times(1).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(trash_qubit_z));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(ds_trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_Z, action->partner)).WillOnce(Return(ds_trash_qubit_z));
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit_x)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit_z)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(ds_trash_qubit_x)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(ds_trash_qubit_z)).Times(1).WillOnce(Return());

  EXPECT_CALL(*trash_qubit_x, Xpurify(qubit)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*ds_trash_qubit_z, Zpurify(trash_qubit_x)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*trash_qubit_z, Zpurify(qubit)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*ds_trash_qubit_x, Xpurify(trash_qubit_z)).Times(1).WillOnce(Return(true));

  auto packet = action->run(rule_engine);

  ASSERT_NE(packet, nullptr);
  DS_DoublePurificationResult *result = dynamic_cast<DS_DoublePurificationResult *>(packet);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->getDestAddr(), action->partner);
  EXPECT_EQ(result->getRule_id(), action->rule_id);
  EXPECT_EQ(result->getRuleset_id(), action->ruleset_id);
  EXPECT_EQ(result->getXOutput_is_plus(), true);
  EXPECT_EQ(result->getZOutput_is_plus(), true);
  EXPECT_EQ(result->getDS_XOutput_is_plus(), true);
  EXPECT_EQ(result->getDS_ZOutput_is_plus(), true);

  delete qubit;
  delete trash_qubit_x;
  delete trash_qubit_z;
  delete ds_trash_qubit_x;
  delete ds_trash_qubit_z;
  delete rule_engine;
}

TEST(DoubleSelectionDualAction, FirstOutcomeTrue) {
  prepareSimulation();
  auto action = DoubleSelectionDualAction::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *trash_qubit_x = new MockQubit();
  auto *trash_qubit_z = new MockQubit();
  auto *ds_trash_qubit_x = new MockQubit();
  auto *ds_trash_qubit_z = new MockQubit();

  EXPECT_CALL(*qubit, Lock(action->ruleset_id, action->rule_id, action->action_index)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit_x, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit_z, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, ds_trash_qubit_x, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, ds_trash_qubit_z, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).Times(1).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(trash_qubit_z));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(ds_trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_Z, action->partner)).WillOnce(Return(ds_trash_qubit_z));
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit_x)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit_z)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(ds_trash_qubit_x)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(ds_trash_qubit_z)).Times(1).WillOnce(Return());

  EXPECT_CALL(*trash_qubit_x, Xpurify(qubit)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*ds_trash_qubit_z, Zpurify(trash_qubit_x)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*trash_qubit_z, Zpurify(qubit)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*ds_trash_qubit_x, Xpurify(trash_qubit_z)).Times(1).WillOnce(Return(false));

  auto packet = action->run(rule_engine);

  ASSERT_NE(packet, nullptr);
  DS_DoublePurificationResult *result = dynamic_cast<DS_DoublePurificationResult *>(packet);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->getDestAddr(), action->partner);
  EXPECT_EQ(result->getRule_id(), action->rule_id);
  EXPECT_EQ(result->getRuleset_id(), action->ruleset_id);
  EXPECT_EQ(result->getXOutput_is_plus(), true);
  EXPECT_EQ(result->getZOutput_is_plus(), false);
  EXPECT_EQ(result->getDS_XOutput_is_plus(), false);
  EXPECT_EQ(result->getDS_ZOutput_is_plus(), false);

  delete qubit;
  delete trash_qubit_x;
  delete trash_qubit_z;
  delete ds_trash_qubit_x;
  delete ds_trash_qubit_z;
  delete rule_engine;
}

TEST(DoubleSelectionDualAction, SecondOutcomeTrue) {
  prepareSimulation();
  auto action = DoubleSelectionDualAction::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *trash_qubit_x = new MockQubit();
  auto *trash_qubit_z = new MockQubit();
  auto *ds_trash_qubit_x = new MockQubit();
  auto *ds_trash_qubit_z = new MockQubit();

  EXPECT_CALL(*qubit, Lock(action->ruleset_id, action->rule_id, action->action_index)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit_x, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit_z, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, ds_trash_qubit_x, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, ds_trash_qubit_z, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).Times(1).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(trash_qubit_z));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(ds_trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_Z, action->partner)).WillOnce(Return(ds_trash_qubit_z));
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit_x)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit_z)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(ds_trash_qubit_x)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(ds_trash_qubit_z)).Times(1).WillOnce(Return());

  EXPECT_CALL(*trash_qubit_x, Xpurify(qubit)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*ds_trash_qubit_z, Zpurify(trash_qubit_x)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*trash_qubit_z, Zpurify(qubit)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*ds_trash_qubit_x, Xpurify(trash_qubit_z)).Times(1).WillOnce(Return(false));

  auto packet = action->run(rule_engine);

  ASSERT_NE(packet, nullptr);
  DS_DoublePurificationResult *result = dynamic_cast<DS_DoublePurificationResult *>(packet);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->getDestAddr(), action->partner);
  EXPECT_EQ(result->getRule_id(), action->rule_id);
  EXPECT_EQ(result->getRuleset_id(), action->ruleset_id);
  EXPECT_EQ(result->getXOutput_is_plus(), false);
  EXPECT_EQ(result->getDS_ZOutput_is_plus(), true);
  EXPECT_EQ(result->getZOutput_is_plus(), false);
  EXPECT_EQ(result->getDS_XOutput_is_plus(), false);

  delete qubit;
  delete trash_qubit_x;
  delete trash_qubit_z;
  delete ds_trash_qubit_x;
  delete ds_trash_qubit_z;
  delete rule_engine;
}

TEST(DoubleSelectionDualAction, ThirdOutcomeTrue) {
  prepareSimulation();
  auto action = DoubleSelectionDualAction::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *trash_qubit_x = new MockQubit();
  auto *trash_qubit_z = new MockQubit();
  auto *ds_trash_qubit_x = new MockQubit();
  auto *ds_trash_qubit_z = new MockQubit();

  EXPECT_CALL(*qubit, Lock(action->ruleset_id, action->rule_id, action->action_index)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit_x, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit_z, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, ds_trash_qubit_x, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, ds_trash_qubit_z, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).Times(1).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(trash_qubit_z));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(ds_trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_Z, action->partner)).WillOnce(Return(ds_trash_qubit_z));
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit_x)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit_z)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(ds_trash_qubit_x)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(ds_trash_qubit_z)).Times(1).WillOnce(Return());

  EXPECT_CALL(*trash_qubit_x, Xpurify(qubit)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*ds_trash_qubit_z, Zpurify(trash_qubit_x)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*trash_qubit_z, Zpurify(qubit)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*ds_trash_qubit_x, Xpurify(trash_qubit_z)).Times(1).WillOnce(Return(false));

  auto packet = action->run(rule_engine);

  ASSERT_NE(packet, nullptr);
  DS_DoublePurificationResult *result = dynamic_cast<DS_DoublePurificationResult *>(packet);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->getDestAddr(), action->partner);
  EXPECT_EQ(result->getRule_id(), action->rule_id);
  EXPECT_EQ(result->getRuleset_id(), action->ruleset_id);
  EXPECT_EQ(result->getXOutput_is_plus(), false);
  EXPECT_EQ(result->getDS_ZOutput_is_plus(), false);
  EXPECT_EQ(result->getZOutput_is_plus(), true);
  EXPECT_EQ(result->getDS_XOutput_is_plus(), false);

  delete qubit;
  delete trash_qubit_x;
  delete trash_qubit_z;
  delete ds_trash_qubit_x;
  delete ds_trash_qubit_z;
  delete rule_engine;
}

TEST(DoubleSelectionDualAction, FinalOutcomeTrue) {
  prepareSimulation();
  auto action = DoubleSelectionDualAction::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *trash_qubit_x = new MockQubit();
  auto *trash_qubit_z = new MockQubit();
  auto *ds_trash_qubit_x = new MockQubit();
  auto *ds_trash_qubit_z = new MockQubit();

  EXPECT_CALL(*qubit, Lock(action->ruleset_id, action->rule_id, action->action_index)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit_x, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit_z, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, ds_trash_qubit_x, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, ds_trash_qubit_z, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).Times(1).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(trash_qubit_z));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(ds_trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_Z, action->partner)).WillOnce(Return(ds_trash_qubit_z));
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit_x)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit_z)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(ds_trash_qubit_x)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(ds_trash_qubit_z)).Times(1).WillOnce(Return());

  EXPECT_CALL(*trash_qubit_x, Xpurify(qubit)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*ds_trash_qubit_z, Zpurify(trash_qubit_x)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*trash_qubit_z, Zpurify(qubit)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*ds_trash_qubit_x, Xpurify(trash_qubit_z)).Times(1).WillOnce(Return(true));

  auto packet = action->run(rule_engine);

  ASSERT_NE(packet, nullptr);
  DS_DoublePurificationResult *result = dynamic_cast<DS_DoublePurificationResult *>(packet);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->getDestAddr(), action->partner);
  EXPECT_EQ(result->getRule_id(), action->rule_id);
  EXPECT_EQ(result->getRuleset_id(), action->ruleset_id);
  // EXPECT_EQ(result->getEntangled_with(), qubit);
  EXPECT_EQ(result->getXOutput_is_plus(), false);
  EXPECT_EQ(result->getDS_ZOutput_is_plus(), false);
  EXPECT_EQ(result->getZOutput_is_plus(), false);
  EXPECT_EQ(result->getDS_XOutput_is_plus(), true);

  delete qubit;
  delete trash_qubit_x;
  delete trash_qubit_z;
  delete ds_trash_qubit_x;
  delete ds_trash_qubit_z;
  delete rule_engine;
}

TEST(DoubleSelectionDualAction, AllOutcomeFalse) {
  prepareSimulation();
  auto action = DoubleSelectionDualAction::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *trash_qubit_x = new MockQubit();
  auto *trash_qubit_z = new MockQubit();
  auto *ds_trash_qubit_x = new MockQubit();
  auto *ds_trash_qubit_z = new MockQubit();

  EXPECT_CALL(*qubit, Lock(action->ruleset_id, action->rule_id, action->action_index)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit_x, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit_z, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, ds_trash_qubit_x, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, ds_trash_qubit_z, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).Times(1).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(trash_qubit_z));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(ds_trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_Z, action->partner)).WillOnce(Return(ds_trash_qubit_z));
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit_x)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit_z)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(ds_trash_qubit_x)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(ds_trash_qubit_z)).Times(1).WillOnce(Return());

  EXPECT_CALL(*trash_qubit_x, Xpurify(qubit)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*ds_trash_qubit_z, Zpurify(trash_qubit_x)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*trash_qubit_z, Zpurify(qubit)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*ds_trash_qubit_x, Xpurify(trash_qubit_z)).Times(1).WillOnce(Return(false));

  auto packet = action->run(rule_engine);

  ASSERT_NE(packet, nullptr);
  DS_DoublePurificationResult *result = dynamic_cast<DS_DoublePurificationResult *>(packet);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->getDestAddr(), action->partner);
  EXPECT_EQ(result->getRule_id(), action->rule_id);
  EXPECT_EQ(result->getRuleset_id(), action->ruleset_id);
  // EXPECT_EQ(result->getEntangled_with(), qubit);
  EXPECT_EQ(result->getXOutput_is_plus(), false);
  EXPECT_EQ(result->getDS_ZOutput_is_plus(), false);
  EXPECT_EQ(result->getZOutput_is_plus(), false);
  EXPECT_EQ(result->getDS_XOutput_is_plus(), false);

  delete qubit;
  delete trash_qubit_x;
  delete trash_qubit_z;
  delete ds_trash_qubit_x;
  delete ds_trash_qubit_z;
  delete rule_engine;
}

}  // namespace

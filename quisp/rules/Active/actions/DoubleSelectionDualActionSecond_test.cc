#include "DoubleSelectionDualActionSecond.h"
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
using OriginalDoubleSelectionDualActionSecond = quisp::rules::active::actions::DoubleSelectionDualActionSecond;

class DoubleSelectionDualActionSecond : public OriginalDoubleSelectionDualActionSecond {
 public:
  using OriginalDoubleSelectionDualActionSecond::action_index;
  using OriginalDoubleSelectionDualActionSecond::rule_id;
  using OriginalDoubleSelectionDualActionSecond::ruleset_id;

  using OriginalDoubleSelectionDualActionSecond::doubleselection_trash_resource_X;
  using OriginalDoubleSelectionDualActionSecond::DoubleSelectionDualActionSecond;
  using OriginalDoubleSelectionDualActionSecond::num_purify;
  using OriginalDoubleSelectionDualActionSecond::partner;
  using OriginalDoubleSelectionDualActionSecond::purification_count;
  using OriginalDoubleSelectionDualActionSecond::qnic_id;
  using OriginalDoubleSelectionDualActionSecond::qnic_type;
  using OriginalDoubleSelectionDualActionSecond::resource;
  using OriginalDoubleSelectionDualActionSecond::trash_resource_X;
  using OriginalDoubleSelectionDualActionSecond::trash_resource_Z;

  static std::unique_ptr<DoubleSelectionDualActionSecond> setupAction() {
    int partner_addr = 2;
    QNIC_type qnic_type = QNIC_E;
    int qnic_id = 3;
    int resource_index = 1;
    int trash_resource_x = 2;
    int trash_resource_z = 3;
    int double_trash_resource_x = 4;
    unsigned long ruleset_id = 6;
    int rule_id = 7;
    int shared_tag = 3;

    return std::make_unique<DoubleSelectionDualActionSecond>(ruleset_id, rule_id, shared_tag, partner_addr, qnic_type, qnic_id, resource_index, trash_resource_x, trash_resource_z,
                                                             double_trash_resource_x);
  }
  MOCK_METHOD(IStationaryQubit *, getResource, (int required_index, int partner), (override));
  MOCK_METHOD(void, removeResource_fromRule, (IStationaryQubit *), (override));
};

TEST(DoubleSelectionDualActionSecond, Init) {
  int partner_addr = 2;
  QNIC_type qnic_type = QNIC_E;
  int qnic_id = 3;
  int resource_index = 4;
  int trash_resource_x = 5;
  int trash_resource_z = 6;
  int double_trash_resource_x = 7;
  unsigned long ruleset_id = 120;
  int rule_id = 2340;
  int shared_tag = 3;

  auto *action = new DoubleSelectionDualActionSecond(ruleset_id, rule_id, shared_tag, partner_addr, qnic_type, qnic_id, resource_index, trash_resource_x, trash_resource_z,
                                                     double_trash_resource_x);
  EXPECT_EQ(action->partner, partner_addr);
  EXPECT_EQ(action->qnic_type, QNIC_E);
  EXPECT_EQ(action->qnic_id, qnic_id);
  EXPECT_EQ(action->resource, resource_index);
  EXPECT_EQ(action->trash_resource_X, trash_resource_x);
  EXPECT_EQ(action->ruleset_id, ruleset_id);
  EXPECT_EQ(action->rule_id, rule_id);
}

TEST(DoubleSelectionDualActionSecond, runWithoutQubit) {
  prepareSimulation();
  auto action = DoubleSelectionDualActionSecond::setupAction();
  auto *rule_engine = new MockRuleEngine();
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).WillOnce(Return(nullptr));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(nullptr));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(nullptr));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(nullptr));
  auto packet = action->run(rule_engine);
  ASSERT_NE(packet, nullptr);
  auto result = dynamic_cast<Error *>(packet);
  ASSERT_NE(result, nullptr);
}

TEST(DoubleSelectionDualActionSecond, NoTrashQubit) {
  auto sim = prepareSimulation();
  auto action = DoubleSelectionDualActionSecond::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  sim->registerComponent(qubit);
  qubit->fillParams();
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(nullptr));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(nullptr));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(nullptr));
  auto packet = action->run(rule_engine);
  ASSERT_NE(packet, nullptr);
  auto result = dynamic_cast<Error *>(packet);
  ASSERT_NE(result, nullptr);
}

TEST(DoubleSelectionDualActionSecond, NoTrashXQubit) {
  auto sim = prepareSimulation();
  auto action = DoubleSelectionDualActionSecond::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *trash_qubit_z = new MockQubit();
  auto *ds_trash_qubit_x = new MockQubit();
  sim->registerComponent(qubit);
  qubit->fillParams();
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(nullptr));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(trash_qubit_z));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(ds_trash_qubit_x));

  auto packet = action->run(rule_engine);
  ASSERT_NE(packet, nullptr);
  auto result = dynamic_cast<Error *>(packet);
  ASSERT_NE(result, nullptr);
}

TEST(DoubleSelectionDualActionSecond, NoDsTrashXQubit) {
  auto sim = prepareSimulation();
  auto action = DoubleSelectionDualActionSecond::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *trash_qubit_x = new MockQubit();
  auto *trash_qubit_z = new MockQubit();
  sim->registerComponent(qubit);
  qubit->fillParams();
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(trash_qubit_z));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(nullptr));

  auto packet = action->run(rule_engine);
  ASSERT_NE(packet, nullptr);
  auto result = dynamic_cast<Error *>(packet);
  ASSERT_NE(result, nullptr);
}

TEST(DoubleSelectionDualActionSecond, TrashQubitDuplication1) {
  auto sim = prepareSimulation();
  auto action = DoubleSelectionDualActionSecond::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *dup_trash_qubit = new MockQubit();
  auto *ds_trash_qubit_x = new MockQubit();

  sim->registerComponent(qubit);
  qubit->fillParams();
  //  duplicate trash_X and trash_Z
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(dup_trash_qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(dup_trash_qubit));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(ds_trash_qubit_x));
  auto packet = action->run(rule_engine);
  ASSERT_NE(packet, nullptr);
  auto result = dynamic_cast<Error *>(packet);
  ASSERT_NE(result, nullptr);
}

TEST(DoubleSelectionDualActionSecond, TrashQubitDuplication2) {
  auto sim = prepareSimulation();
  auto action = DoubleSelectionDualActionSecond::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *dup_trash_qubit = new MockQubit();
  //   auto *trash_qubit_x = new MockQubit();
  auto *trash_qubit_z = new MockQubit();
  //   auto *ds_trash_qubit_x = new MockQubit();

  sim->registerComponent(qubit);
  qubit->fillParams();
  //  duplicate trash_X and doubleselection_trash_X
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(dup_trash_qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(trash_qubit_z));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(dup_trash_qubit));
  auto packet = action->run(rule_engine);
  ASSERT_NE(packet, nullptr);
  auto result = dynamic_cast<Error *>(packet);
  ASSERT_NE(result, nullptr);
}

TEST(DoubleSelectionDualActionSecond, TrashQubitDuplication3) {
  auto sim = prepareSimulation();
  auto action = DoubleSelectionDualActionSecond::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *dup_trash_qubit = new MockQubit();
  auto *trash_qubit_x = new MockQubit();
  sim->registerComponent(qubit);
  qubit->fillParams();
  //  duplicate trash_Z and doubleselection_trash_X
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(dup_trash_qubit));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(dup_trash_qubit));
  auto packet = action->run(rule_engine);
  ASSERT_NE(packet, nullptr);
  auto result = dynamic_cast<Error *>(packet);
  ASSERT_NE(result, nullptr);
}

TEST(DoubleSelectionDualActionSecond, AllOutcomeTrue) {
  prepareSimulation();
  auto action = DoubleSelectionDualActionSecond::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *trash_qubit_x = new MockQubit();
  auto *trash_qubit_z = new MockQubit();
  auto *ds_trash_qubit_x = new MockQubit();

  EXPECT_CALL(*qubit, Lock(action->ruleset_id, action->rule_id, action->action_index)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit_x, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit_z, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, ds_trash_qubit_x, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).Times(1).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(trash_qubit_z));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(ds_trash_qubit_x));
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit_x)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit_z)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(ds_trash_qubit_x)).Times(1).WillOnce(Return());

  EXPECT_CALL(*trash_qubit_x, Xpurify(qubit)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*trash_qubit_z, Zpurify(qubit)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*ds_trash_qubit_x, Xpurify(trash_qubit_z)).Times(1).WillOnce(Return(true));

  auto packet = action->run(rule_engine);

  ASSERT_NE(packet, nullptr);
  DS_DoublePurificationSecondResult *result = dynamic_cast<DS_DoublePurificationSecondResult *>(packet);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->getDestAddr(), action->partner);
  EXPECT_EQ(result->getRule_id(), action->rule_id);
  EXPECT_EQ(result->getRuleset_id(), action->ruleset_id);
  // EXPECT_EQ(result->getEntangled_with(), qubit);
  EXPECT_EQ(result->getXOutput_is_plus(), true);
  EXPECT_EQ(result->getZOutput_is_plus(), true);
  EXPECT_EQ(result->getDS_Output_is_plus(), true);

  delete qubit;
  delete trash_qubit_x;
  delete trash_qubit_z;
  delete ds_trash_qubit_x;
  delete rule_engine;
}

TEST(DoubleSelectionDualActionSecond, FirstOutcomeTrue) {
  prepareSimulation();
  auto action = DoubleSelectionDualActionSecond::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *trash_qubit_x = new MockQubit();
  auto *trash_qubit_z = new MockQubit();
  auto *ds_trash_qubit_x = new MockQubit();

  EXPECT_CALL(*qubit, Lock(action->ruleset_id, action->rule_id, action->action_index)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit_x, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit_z, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, ds_trash_qubit_x, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).Times(1).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(trash_qubit_z));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(ds_trash_qubit_x));
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit_x)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit_z)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(ds_trash_qubit_x)).Times(1).WillOnce(Return());

  EXPECT_CALL(*trash_qubit_x, Xpurify(qubit)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*trash_qubit_z, Zpurify(qubit)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*ds_trash_qubit_x, Xpurify(trash_qubit_z)).Times(1).WillOnce(Return(false));

  auto packet = action->run(rule_engine);

  ASSERT_NE(packet, nullptr);
  DS_DoublePurificationSecondResult *result = dynamic_cast<DS_DoublePurificationSecondResult *>(packet);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->getDestAddr(), action->partner);
  EXPECT_EQ(result->getRule_id(), action->rule_id);
  EXPECT_EQ(result->getRuleset_id(), action->ruleset_id);
  // EXPECT_EQ(result->getEntangled_with(), qubit);
  EXPECT_EQ(result->getXOutput_is_plus(), true);
  EXPECT_EQ(result->getZOutput_is_plus(), false);
  EXPECT_EQ(result->getDS_Output_is_plus(), false);

  delete qubit;
  delete trash_qubit_x;
  delete trash_qubit_z;
  delete ds_trash_qubit_x;
  delete rule_engine;
}

TEST(DoubleSelectionDualActionSecond, SecondOutcomeTrue) {
  prepareSimulation();
  auto action = DoubleSelectionDualActionSecond::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *trash_qubit_x = new MockQubit();
  auto *trash_qubit_z = new MockQubit();
  auto *ds_trash_qubit_x = new MockQubit();

  EXPECT_CALL(*qubit, Lock(action->ruleset_id, action->rule_id, action->action_index)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit_x, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit_z, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, ds_trash_qubit_x, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).Times(1).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(trash_qubit_z));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(ds_trash_qubit_x));
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit_x)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit_z)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(ds_trash_qubit_x)).Times(1).WillOnce(Return());

  EXPECT_CALL(*trash_qubit_x, Xpurify(qubit)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*trash_qubit_z, Zpurify(qubit)).Times(1).WillOnce(Return(true));
  EXPECT_CALL(*ds_trash_qubit_x, Xpurify(trash_qubit_z)).Times(1).WillOnce(Return(false));

  auto packet = action->run(rule_engine);

  ASSERT_NE(packet, nullptr);
  DS_DoublePurificationSecondResult *result = dynamic_cast<DS_DoublePurificationSecondResult *>(packet);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->getDestAddr(), action->partner);
  EXPECT_EQ(result->getRule_id(), action->rule_id);
  EXPECT_EQ(result->getRuleset_id(), action->ruleset_id);
  // EXPECT_EQ(result->getEntangled_with(), qubit);
  EXPECT_EQ(result->getXOutput_is_plus(), false);
  EXPECT_EQ(result->getZOutput_is_plus(), true);
  EXPECT_EQ(result->getDS_Output_is_plus(), false);

  delete qubit;
  delete trash_qubit_x;
  delete trash_qubit_z;
  delete ds_trash_qubit_x;
  delete rule_engine;
}

TEST(DoubleSelectionDualActionSecond, ThirdOutcomeTrue) {
  prepareSimulation();
  auto action = DoubleSelectionDualActionSecond::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *trash_qubit_x = new MockQubit();
  auto *trash_qubit_z = new MockQubit();
  auto *ds_trash_qubit_x = new MockQubit();

  EXPECT_CALL(*qubit, Lock(action->ruleset_id, action->rule_id, action->action_index)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit_x, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit_z, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, ds_trash_qubit_x, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).Times(1).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(trash_qubit_z));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(ds_trash_qubit_x));
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit_x)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit_z)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(ds_trash_qubit_x)).Times(1).WillOnce(Return());

  EXPECT_CALL(*trash_qubit_x, Xpurify(qubit)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*trash_qubit_z, Zpurify(qubit)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*ds_trash_qubit_x, Xpurify(trash_qubit_z)).Times(1).WillOnce(Return(true));

  auto packet = action->run(rule_engine);

  ASSERT_NE(packet, nullptr);
  DS_DoublePurificationSecondResult *result = dynamic_cast<DS_DoublePurificationSecondResult *>(packet);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->getDestAddr(), action->partner);
  EXPECT_EQ(result->getRule_id(), action->rule_id);
  EXPECT_EQ(result->getRuleset_id(), action->ruleset_id);
  // EXPECT_EQ(result->getEntangled_with(), qubit);
  EXPECT_EQ(result->getXOutput_is_plus(), false);
  EXPECT_EQ(result->getZOutput_is_plus(), false);
  EXPECT_EQ(result->getDS_Output_is_plus(), true);

  delete qubit;
  delete trash_qubit_x;
  delete trash_qubit_z;
  delete ds_trash_qubit_x;
  delete rule_engine;
}

TEST(DoubleSelectionDualActionSecond, AllOutcomeFalse) {
  prepareSimulation();
  auto action = DoubleSelectionDualActionSecond::setupAction();
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();
  auto *trash_qubit_x = new MockQubit();
  auto *trash_qubit_z = new MockQubit();
  auto *ds_trash_qubit_x = new MockQubit();

  EXPECT_CALL(*qubit, Lock(action->ruleset_id, action->rule_id, action->action_index)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit_x, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, trash_qubit_z, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, ds_trash_qubit_x, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).Times(1).WillOnce(Return(qubit));
  EXPECT_CALL(*action, getResource(action->trash_resource_X, action->partner)).WillOnce(Return(trash_qubit_x));
  EXPECT_CALL(*action, getResource(action->trash_resource_Z, action->partner)).WillOnce(Return(trash_qubit_z));
  EXPECT_CALL(*action, getResource(action->doubleselection_trash_resource_X, action->partner)).WillOnce(Return(ds_trash_qubit_x));
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit_x)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(trash_qubit_z)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, removeResource_fromRule(ds_trash_qubit_x)).Times(1).WillOnce(Return());

  EXPECT_CALL(*trash_qubit_x, Xpurify(qubit)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*trash_qubit_z, Zpurify(qubit)).Times(1).WillOnce(Return(false));
  EXPECT_CALL(*ds_trash_qubit_x, Xpurify(trash_qubit_z)).Times(1).WillOnce(Return(false));

  auto packet = action->run(rule_engine);

  ASSERT_NE(packet, nullptr);
  DS_DoublePurificationSecondResult *result = dynamic_cast<DS_DoublePurificationSecondResult *>(packet);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->getDestAddr(), action->partner);
  EXPECT_EQ(result->getRule_id(), action->rule_id);
  EXPECT_EQ(result->getRuleset_id(), action->ruleset_id);
  // EXPECT_EQ(result->getEntangled_with(), qubit);
  EXPECT_EQ(result->getXOutput_is_plus(), false);
  EXPECT_EQ(result->getZOutput_is_plus(), false);
  EXPECT_EQ(result->getDS_Output_is_plus(), false);

  delete qubit;
  delete trash_qubit_x;
  delete trash_qubit_z;
  delete ds_trash_qubit_x;
  delete rule_engine;
}

}  // namespace

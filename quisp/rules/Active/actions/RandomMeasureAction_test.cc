#include "RandomMeasureAction.h"
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
using OriginalRandomMeasureAction = quisp::rules::active::actions::RandomMeasureAction;

class RandomMeasureAction : public OriginalRandomMeasureAction {
 public:
  using OriginalRandomMeasureAction::current_count;
  using OriginalRandomMeasureAction::dst;
  using OriginalRandomMeasureAction::max_count;
  using OriginalRandomMeasureAction::partner;
  using OriginalRandomMeasureAction::qnic_id;
  using OriginalRandomMeasureAction::qnic_type;
  using OriginalRandomMeasureAction::RandomMeasureAction;
  using OriginalRandomMeasureAction::resource;
  using OriginalRandomMeasureAction::src;
  using OriginalRandomMeasureAction::start;

  static std::unique_ptr<RandomMeasureAction> setupAction() {
    int owner_address = 1;
    int partner_address = 2;
    QNIC_type qnic_type = QNIC_E;
    int qnic_id = 11;
    int resource_index = 1;
    int max_count = 8000;

    return std::make_unique<RandomMeasureAction>(0, 0, owner_address, partner_address, qnic_type, qnic_id, resource_index, max_count);
  }
  MOCK_METHOD(IStationaryQubit *, getResource, (int required_index, int partner), (override));
  MOCK_METHOD(void, removeResource_fromRule, (IStationaryQubit *), (override));
};

TEST(RandomMeasureActionTest, Init) {
  int owner_address = 1;
  int partner_address = 2;
  QNIC_type qnic_type = QNIC_E;
  int qnic_id = 11;
  int resource_index = 1;
  int num_measure = 8000;

  auto *action = new RandomMeasureAction(0, 0, owner_address, partner_address, qnic_type, qnic_id, resource_index, num_measure);
  EXPECT_EQ(action->src, owner_address);
  EXPECT_EQ(action->dst, partner_address);
  EXPECT_EQ(action->partner, partner_address);
  EXPECT_EQ(action->qnic_type, qnic_type);
  EXPECT_EQ(action->qnic_id, qnic_id);
  EXPECT_EQ(action->resource, resource_index);
  EXPECT_EQ(action->max_count, num_measure);
}

TEST(RandomMeasureActionTest, NullQubit) {
  prepareSimulation();
  auto action = RandomMeasureAction::setupAction();
  auto *rule_engine = new MockRuleEngine();
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).WillOnce(Return(nullptr));
  auto packet = action->run(rule_engine);
  ASSERT_NE(packet, nullptr);
  auto result = dynamic_cast<Error *>(packet);
  ASSERT_NE(result, nullptr);
}

TEST(RandomMeasureActionTest, MeasureResultNotFinished) {
  prepareSimulation();
  auto action = RandomMeasureAction::setupAction();
  int current_count = 4999;
  action->current_count = current_count;
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();

  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, qubit, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).Times(1).WillOnce(Return(qubit));
  EXPECT_CALL(*action, removeResource_fromRule(qubit)).Times(1).WillOnce(Return());
  measurement_outcome outcome;
  outcome.basis = 'X';
  outcome.outcome_is_plus = true;
  EXPECT_CALL(*qubit, measure_density_independent()).Times(1).WillOnce(Return(outcome));

  auto packet = action->run(rule_engine);
  ASSERT_NE(packet, nullptr);
  LinkTomographyResult *result = dynamic_cast<LinkTomographyResult *>(packet);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->getSrcAddr(), action->src);
  EXPECT_EQ(result->getDestAddr(), action->partner);
  EXPECT_EQ(result->getCount_id(), current_count + 1);  // increment trial count
  EXPECT_EQ(result->getPartner_address(), action->src);  // partner of partner's qubit is source
  EXPECT_EQ(result->getOutput_is_plus(), true);
  EXPECT_EQ(result->getBasis(), 'X');

  delete qubit;
  delete rule_engine;
}

TEST(RandomMeasureActionTest, FinalMeasurement) {
  prepareSimulation();
  auto action = RandomMeasureAction::setupAction();
  int current_count = 7999;
  action->current_count = current_count;
  auto *rule_engine = new MockRuleEngine();
  auto *qubit = new MockQubit();

  EXPECT_CALL(*rule_engine, freeConsumedResource(action->qnic_id, qubit, action->qnic_type)).Times(1).WillOnce(Return());
  EXPECT_CALL(*action, getResource(action->resource, action->partner)).Times(1).WillOnce(Return(qubit));
  EXPECT_CALL(*action, removeResource_fromRule(qubit)).Times(1).WillOnce(Return());
  measurement_outcome outcome;
  outcome.basis = 'Z';
  outcome.outcome_is_plus = false;
  EXPECT_CALL(*qubit, measure_density_independent()).Times(1).WillOnce(Return(outcome));

  auto packet = action->run(rule_engine);

  ASSERT_NE(packet, nullptr);
  LinkTomographyResult *result = dynamic_cast<LinkTomographyResult *>(packet);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->getSrcAddr(), action->src);
  EXPECT_EQ(result->getDestAddr(), action->partner);
  EXPECT_EQ(result->getCount_id(), current_count + 1);  // increment trial count
  EXPECT_EQ(result->getPartner_address(), action->src);  // partner of partner's qubit is source
  EXPECT_EQ(result->getOutput_is_plus(), false);
  EXPECT_EQ(result->getBasis(), 'Z');
  EXPECT_EQ(result->getMax_count(), action->max_count);

  delete qubit;
  delete rule_engine;
}
}  // namespace

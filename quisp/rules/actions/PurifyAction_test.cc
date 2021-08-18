#include "PurifyAction.h"
#include <classical_messages_m.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <modules/QNIC.h>
#include <modules/QNIC/StationaryQubit/StationaryQubit.h>
#include <modules/QRSA/RuleEngine/IRuleEngine.h>
#include <test_utils/TestUtils.h>
#include "modules/QRSA/RuleEngine/RuleEngine.h"

using namespace testing;
using namespace quisp::messages;
using namespace quisp_test;

using quisp::modules::IRuleEngine;
using quisp::modules::IStationaryQubit;
using quisp::modules::QNIC_E;
using quisp::modules::QNIC_type;
using quisp::modules::StationaryQubit;
using OriginalPurifyAction = quisp::rules::actions::PurifyAction;

namespace {
class PurifyAction : public OriginalPurifyAction {
 public:
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

TEST(PurifyActionTest, runXPurify) { auto *sim = prepareSimulation(); }

TEST(PurifyActionTest, runZPurify) { auto *sim = prepareSimulation(); }
}  // namespace

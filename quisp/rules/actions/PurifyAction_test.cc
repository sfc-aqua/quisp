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
  using OriginalPurifyAction::PurifyAction;
};

TEST(PurifyActionTest, Init) {
  int partner_addr = 2;
  QNIC_type qnic_type = QNIC_E;
  int qnic_id = 3;
  int resource_index = 4;
  int trash_resource_index = 5;
  unsigned long ruleset_id = 6;
  unsigned long rule_id = 7;

  auto *action = new PurifyAction(partner_addr, qnic_type, qnic_id, resource_index, trash_resource_index, ruleset_id, rule_id);
}

TEST(PurifyActionTest, runXPurify) { auto *sim = prepareSimulation(); }

TEST(PurifyActionTest, runZPurify) { auto *sim = prepareSimulation(); }
}  // namespace

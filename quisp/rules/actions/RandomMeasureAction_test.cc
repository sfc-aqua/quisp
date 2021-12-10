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
using OriginalRandomMeasureAction = quisp::rules::actions::RandomMeasureAction;

class RandomMeasureAction : public OriginalRandomMeausreAction {
 public:
  using OriginalRandomMeasureAction::partner;
  using OriginalRandomMeasureAction::qnic_type;
  using OriginalRandomMeasureAction::qnic_id;
  using OriginalRandomMeasureAction::resource;
  using OriginalRandomMeasureAction::src;
  using OriginalRandomMeasureAction::dst;
  using OriginalRandomMeasureAction::current_count;
  using OriginalRandomMeasureAction::max_count;
  using OriginalRandomMeasureAction::start;

  static std::unique_ptr<RandomMeasureAction> setupAction() {
	int owner_address = 1;
	int partner_address = 2;
	QNIC_type qnic_type = QNIC_E;
	int qnic_id = 11;
	int resource_index = 1;
	int src = 1;
	int dst = 2;
	int current_count = 100;
	int max_count = 8000;
	simtime_t start = 0;

    return std::make_unique<RandomMeasureAction>(owner_address, partner_address, qnic_type, qnic_id, resource_index, max_count);
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

  auto *action = new RandomMeasureAction(owner_address, partner_address, qnic_type, qnic_id, resource_index, num_measure);
  EXPECT_EQ(action->src, owner_address);
  EXPECT_EQ(action->dst, partner_address);
  EXPECT_EQ(action->partner, partner_address);
  EXPECT_EQ(action->qnic_type, qnic_type);
  EXPECT_EQ(action->qnic_id, qnic_id);
  EXPECT_EQ(action->resource, resource_index);
  EXPECT_EQ(max_count, num_measure);
}
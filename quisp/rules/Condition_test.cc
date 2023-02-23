#include "Condition.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <memory>
#include "Clause.h"
#include "types/QNodeAddr.h"

namespace {
using namespace quisp_test;
using namespace quisp::rules;
using quisp::modules::QNIC_E;
using quisp::modules::QNIC_N;
using quisp::modules::QNIC_R;
using quisp::modules::QNIC_RP;
using quisp::types::QNodeAddr;

TEST(ConditionTest, Init) {
  prepareSimulation();
  auto condition = std::make_unique<Condition>();
  EXPECT_EQ(condition->clauses.size(), 0);
}

TEST(ConditionTest, serialize_json_test) {
  prepareSimulation();
  auto condition = std::make_unique<Condition>();
  // num_resource, required_fidelity, partner_addr, qnic_type, qnic_id
  auto enough_resource = std::make_unique<EnoughResourceConditionClause>(1, QNodeAddr{3});
  condition->addClause(std::move(enough_resource));
  auto serialized_condition = condition->serialize_json();
  auto clauses = serialized_condition["clauses"];
  ASSERT_NE(clauses, nullptr);
  EXPECT_EQ(clauses.size(), 1);
}

TEST(ConditionTest, deserialize_json_test) {
  prepareSimulation();
  auto condition = std::make_unique<Condition>();
  // num_resource, required_fidelity, partner_addr, qnic_type, qnic_id
  auto enough_resource = std::make_unique<EnoughResourceConditionClause>(1, QNodeAddr{3});
  condition->addClause(std::move(enough_resource));
  auto serialized_condition = condition->serialize_json();

  // prepare empty condition
  auto empty_condition = std::make_unique<Condition>();
  empty_condition->deserialize_json(serialized_condition);
  EXPECT_EQ(empty_condition->clauses.size(), 1);
}

}  // namespace

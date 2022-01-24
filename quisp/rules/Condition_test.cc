#include "Condition.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <memory>

namespace {
using namespace quisp_test;
using namespace quisp::rules;

TEST(ConditionTest, Init) {
  prepareSimulation();
  auto condition = std::make_unique<Condition>();
  EXPECT_EQ(condition->clauses.size(), 0);
}

TEST(ConditionTest, addCluase) {
  prepareSimulation();
  auto condition = std::make_unique<Condition>();
  auto enough_resource_clause = std::make_unique<EnoughResourceConditionClause>(1, 2, 0.85);  // num_resource, partner, fidelity
  condition->addClause(std::move(enough_resource_clause));
  EXPECT_EQ(condition->clauses.size(), 1);
  //   EXPECT_EQ(condition->clauses.at(0).num_resource, 1);
  //   EXPECT_EQ(condition->clauses.at(0).partner_addr, 2);
  //   EXPECT_EQ(condition->clauses.at(0).required_fidelity, 0.85);
}

}  // namespace
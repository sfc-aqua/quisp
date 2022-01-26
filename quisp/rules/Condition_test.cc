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

}  // namespace
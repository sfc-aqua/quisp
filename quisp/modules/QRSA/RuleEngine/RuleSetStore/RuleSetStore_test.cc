#include "RuleSetStore.h"
#include <gtest/gtest.h>
#include <memory>
#include "rules/RuleSet.h"
#include "test_utils/TestUtils.h"

namespace {
using namespace quisp::rules;
using namespace quisp_test;
class RuleSetStore : public quisp::modules::ruleset_store::RuleSetStore {
 public:
  using quisp::modules::ruleset_store::RuleSetStore::rulesets;
  RuleSetStore() : quisp::modules::ruleset_store::RuleSetStore() {}
  virtual ~RuleSetStore() {}
};

TEST(RuleSetStore, Init) {
  RuleSetStore rs;
  EXPECT_EQ(rs.rulesets.size(), 0);
}

TEST(RuleSetStore, InsertUniquePtr) {
  prepareSimulation();
  RuleSetStore rs;
  EXPECT_EQ(rs.rulesets.size(), 0);
  auto ruleset = std::make_unique<RuleSet>(0, 1, 2);
  rs.insert(ruleset);
  EXPECT_EQ(rs.rulesets.size(), 1);
}
TEST(RuleSetStore, InsertRawPtr) {
  prepareSimulation();
  RuleSetStore rs;
  EXPECT_EQ(rs.rulesets.size(), 0);
  auto ruleset = new RuleSet(0, 1, 2);
  rs.insert(ruleset);
  EXPECT_EQ(rs.rulesets.size(), 1);
}
TEST(RuleSetStore, Erase) {
  prepareSimulation();
  RuleSetStore rs;
  EXPECT_EQ(rs.rulesets.size(), 0);
  auto ruleset = new RuleSet(0, 1, 2);
  rs.insert(ruleset);
  EXPECT_EQ(rs.rulesets.size(), 1);
  const auto& first_ruleset = rs.cbegin();
  rs.erase(first_ruleset);
  EXPECT_EQ(rs.rulesets.size(), 0);
}
}  // namespace

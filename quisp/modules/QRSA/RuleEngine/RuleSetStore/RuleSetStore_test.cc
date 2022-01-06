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
  auto ruleset = std::make_unique<ActiveRuleSet>(0, 1);
  rs.insert(ruleset);
  EXPECT_EQ(rs.rulesets.size(), 1);
}
TEST(RuleSetStore, InsertRawPtr) {
  prepareSimulation();
  RuleSetStore rs;
  EXPECT_EQ(rs.rulesets.size(), 0);
  auto ruleset = new ActiveRuleSet(0, 1);
  rs.insert(ruleset);
  EXPECT_EQ(rs.rulesets.size(), 1);
}
TEST(RuleSetStore, Erase) {
  prepareSimulation();
  RuleSetStore rs;
  EXPECT_EQ(rs.rulesets.size(), 0);
  auto ruleset = new ActiveRuleSet(0, 1);
  rs.insert(ruleset);
  EXPECT_EQ(rs.rulesets.size(), 1);
  const auto& first_ruleset = rs.cbegin();
  rs.erase(first_ruleset);
  EXPECT_EQ(rs.rulesets.size(), 0);
}

TEST(RuleSetStore, EraseWhileIterating) {
  prepareSimulation();
  RuleSetStore rs;
  for (int i = 0; i < 10; i++) {
    auto ruleset = new ActiveRuleSet(i, i * 2);
    rs.insert(ruleset);
  }
  int i = 0;
  for (auto&& ruleset = rs.cbegin(); ruleset != rs.cend();) {
    if (i == 9) {
      ruleset = rs.erase(ruleset);
    } else {
      ruleset++;
    }
    i++;
  }
  EXPECT_EQ(rs.rulesets.size(), 9);
}
TEST(RuleSetStore, IterateWithConst) {
  prepareSimulation();
  RuleSetStore rs;
  EXPECT_EQ(rs.rulesets.size(), 0);
  EXPECT_EQ(rs.cbegin(), rs.cend());
  for (int i = 0; i < 10; i++) {
    auto ruleset = new ActiveRuleSet(i, i * 2);
    rs.insert(ruleset);
  }

  EXPECT_EQ(rs.rulesets.size(), 10);
  int i = 0;
  for (auto&& ruleset = rs.cbegin(); ruleset != rs.cend(); ++ruleset) {
    EXPECT_EQ((*ruleset)->ruleset_id, i);
    EXPECT_EQ((*ruleset)->owner_addr, i * 2);
    i++;
  }
}
}  // namespace

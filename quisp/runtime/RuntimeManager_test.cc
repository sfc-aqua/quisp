#include <gtest/gtest.h>
#include <memory>

#include "RuleSet.h"
#include "RuntimeManager.h"
#include "runtime/types.h"
#include "test.h"

namespace {
using namespace quisp::runtime;
using namespace quisp_test;
using namespace testing;

class RuntimeManagerTest : public testing::Test {
 protected:
  void SetUp() {
    auto cb = std::make_unique<MockRuntimeCallback>();
    callback = cb.get();
    runtimes = new RuntimeManager(std::move(cb));
  }
  void TearDown() { delete runtimes; }
  RuntimeManager* runtimes;
  MockRuntimeCallback* callback;
};

TEST_F(RuntimeManagerTest, AcceptRuleSet) {
  RuleSet rs{"test ruleset"};
  EXPECT_EQ(runtimes->size(), 0);
  runtimes->acceptRuleSet(rs);
  EXPECT_EQ(runtimes->size(), 1);
  auto& runtime = runtimes->at(0);
  EXPECT_EQ(runtime.ruleset.name, rs.name);
}

TEST_F(RuntimeManagerTest, FindById) {
  RuleSet rs1{};
  rs1.id = 1;
  RuleSet rs2{};
  rs2.id = 2;
  RuleSet rs3{};
  rs3.id = 3;
  runtimes->acceptRuleSet(rs1);
  runtimes->acceptRuleSet(rs2);
  runtimes->acceptRuleSet(rs3);
  EXPECT_EQ(runtimes->size(), 3);
  EXPECT_EQ(runtimes->findById(rs2.id).ruleset.id, rs2.id);
  EXPECT_EQ(runtimes->findById(rs1.id).ruleset.id, rs1.id);
  EXPECT_EQ(runtimes->findById(rs3.id).ruleset.id, rs3.id);
}

TEST_F(RuntimeManagerTest, Iterate) {
  RuleSet rs1{};
  rs1.id = 1;
  RuleSet rs2{};
  rs2.id = 2;
  RuleSet rs3{};
  rs3.id = 3;
  runtimes->acceptRuleSet(rs1);
  runtimes->acceptRuleSet(rs2);
  runtimes->acceptRuleSet(rs3);
  EXPECT_EQ(runtimes->size(), 3);
  int count = 0;
  bool rs1_exist = false, rs2_exist = false, rs3_exist = false;
  for (auto it = runtimes->begin(); it != runtimes->end(); it++) {
    count++;
    if (it->ruleset.id == rs1.id) rs1_exist = true;
    if (it->ruleset.id == rs2.id) rs2_exist = true;
    if (it->ruleset.id == rs3.id) rs3_exist = true;
  }
  EXPECT_EQ(count, 3);
  EXPECT_TRUE(rs1_exist);
  EXPECT_TRUE(rs2_exist);
  EXPECT_TRUE(rs3_exist);
}

TEST_F(RuntimeManagerTest, Exec) {
  Program empty{"empty", {}};
  Program terminater{"terminater", {INSTR_RET_ReturnCode_{{ReturnCode::RS_TERMINATED}}}};
  Program checker{"cond", {INSTR_STORE_MemoryKey_int_{{MemoryKey{"test"}, 123}}}};
  Rule rule{
      "",
      0,
      checker,
      empty,
  };
  RuleSet rs1{"", {rule}, terminater};
  rs1.id = 1;
  RuleSet rs2{"", {rule}, terminater};
  rs2.id = 2;
  RuleSet rs3{"", {rule}, terminater};
  rs3.id = 3;
  runtimes->acceptRuleSet(rs1);
  runtimes->acceptRuleSet(rs2);
  runtimes->acceptRuleSet(rs3);
  EXPECT_EQ(runtimes->size(), 3);
  runtimes->exec();
  EXPECT_EQ(runtimes->at(0).loadVal(MemoryKey{"test"}).intValue(), 123);
  EXPECT_EQ(runtimes->at(1).loadVal(MemoryKey{"test"}).intValue(), 123);
  EXPECT_EQ(runtimes->at(2).loadVal(MemoryKey{"test"}).intValue(), 123);
}
}  // namespace
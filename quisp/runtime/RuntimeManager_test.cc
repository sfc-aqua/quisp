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

Program empty{"empty", {}};
Program cond_passed_once{"passed_once",
                         {
                             INSTR_LOAD_RegId_MemoryKey_{{RegId::REG0, MemoryKey{"count"}}},
                             INSTR_BEZ_Label_RegId_{{Label{"first_time"}, RegId::REG0}},
                             INSTR_RET_ReturnCode_{{ReturnCode::COND_FAILED}},
                             INSTR_INC_RegId_{{RegId::REG0}, "first_time"},
                             INSTR_STORE_MemoryKey_RegId_{{MemoryKey{"count"}, RegId::REG0}},
                             INSTR_RET_ReturnCode_{{ReturnCode::COND_PASSED}},
                         }};
Program checker{"cond", {INSTR_STORE_MemoryKey_int_{{MemoryKey{"test"}, 123}}}};

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
  EXPECT_EQ(runtimes->findById(rs2.id)->ruleset.id, rs2.id);
  EXPECT_EQ(runtimes->findById(rs1.id)->ruleset.id, rs1.id);
  EXPECT_EQ(runtimes->findById(rs3.id)->ruleset.id, rs3.id);
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
  Rule rule{
      "", -1, -1, cond_passed_once, checker,
  };
  RuleSet rs1{"", {rule}, empty};
  rs1.id = 1;
  RuleSet rs2{"", {rule}, empty};
  rs2.id = 2;
  RuleSet rs3{"", {rule}, empty};
  rs3.id = 3;
  runtimes->acceptRuleSet(rs1);
  runtimes->acceptRuleSet(rs2);
  runtimes->acceptRuleSet(rs3);
  EXPECT_EQ(runtimes->size(), 3);
  bool terminated = runtimes->exec();
  EXPECT_FALSE(terminated);
  {
    auto& rs1 = runtimes->at(0);
    auto& rs2 = runtimes->at(1);
    auto& rs3 = runtimes->at(2);
    EXPECT_EQ(rs1.loadVal(MemoryKey{"test"}).intValue(), 123);
    EXPECT_EQ(rs2.loadVal(MemoryKey{"test"}).intValue(), 123);
    EXPECT_EQ(rs3.loadVal(MemoryKey{"test"}).intValue(), 123);
    EXPECT_FALSE(rs1.terminated);
    EXPECT_FALSE(rs2.terminated);
    EXPECT_FALSE(rs3.terminated);
  }
}

TEST_F(RuntimeManagerTest, ExecAndTerminated) {
  Program terminator{"terminator", {INSTR_RET_ReturnCode_{{ReturnCode::RS_TERMINATED}}}};
  Rule rule{
      "", -1, -1, cond_passed_once, checker,
  };
  RuleSet rs1{"rs1", {rule}, empty};
  rs1.id = 1;
  RuleSet rs2{"rs2", {rule}, terminator};
  rs2.id = 2;
  RuleSet rs3{"rs3", {rule}, empty};
  rs3.id = 3;
  runtimes->acceptRuleSet(rs1);
  runtimes->acceptRuleSet(rs2);
  runtimes->acceptRuleSet(rs3);
  EXPECT_EQ(runtimes->size(), 3);
  bool terminated = runtimes->exec();
  EXPECT_FALSE(terminated);
  ASSERT_EQ(runtimes->size(), 2);
  {
    auto& rs1 = runtimes->at(0);
    auto& rs3 = runtimes->at(1);
    EXPECT_EQ(rs1.loadVal(MemoryKey{"test"}).intValue(), 123);
    EXPECT_EQ(rs3.loadVal(MemoryKey{"test"}).intValue(), 123);
    EXPECT_FALSE(rs1.terminated);
    EXPECT_FALSE(rs3.terminated);
  }
}
}  // namespace

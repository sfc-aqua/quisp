#include <gtest/gtest.h>
#include <modules/QRSA/RuleEngine/QubitRecord/QubitRecord.h>
#include <cstddef>
#include <sstream>
#include "Runtime.h"
#include "modules/QRSA/QRSA.h"
#include "rules/Active/ActiveRuleSet.h"
#include "runtime/types.h"
#include "test.h"

using namespace quisp::runtime;
using namespace quisp::rules;
using namespace quisp::rules::active;
using quisp::modules::qubit_record::QubitRecord;
using namespace quisp_test;

namespace {
auto r0 = RegId::REG0;
auto r1 = RegId::REG1;
auto r2 = RegId::REG2;
auto r3 = RegId::REG3;
auto r4 = RegId::REG4;

class RuntimeInstructionsTest : public testing::Test {
 protected:
  void SetUp() {
    runtime = new Runtime();
    runtime->callback = new MockRuntimeCallback();
    runtime->rule_id = 0;
    runtime->cleanup();
    qubit = new QubitRecord{QNIC_E, 2, 3};
  }

  void TearDown() { delete runtime; }

 public:
  void execProgram(const Program& p) {
    RuleSet rs{"test rs", {Rule{p, Program{"empty", {}}}}};
    rs.finalize();
    runtime->execProgram(p);
  }

  testing::AssertionResult checkRegisters(std::array<int32_t, 5> expected_vals) {
    std::stringstream ss;
    bool passed = true;
    for (int i = 0; i < 5; i++) {
      auto val = runtime->registers[i].value;
      if (val != expected_vals[i]) {
        ss << "register[" << i << "] is " << val << ", expected: " << expected_vals[i] << ". ";
        passed = false;
      }
    }
    if (passed) return testing::AssertionSuccess();
    ss << "registers: {";
    for (int i = 0; i < 5; i++) {
      ss << runtime->registers[i].value << (i == 4 ? "}" : ", ");
    }
    return testing::AssertionFailure() << ss.str();
  }
  Runtime* runtime;
  qrsa::IQubitRecord* qubit;
};

TEST_F(RuntimeInstructionsTest, SetRegisters) {
  Program p{"test",
            {
                INSTR_SET_RegId_int_{{r0, 1}},
                INSTR_SET_RegId_int_{{r1, 2}},
                INSTR_SET_RegId_int_{{r2, 3}},
                INSTR_SET_RegId_int_{{r3, 4}},
                INSTR_SET_RegId_int_{{r4, 5}},
            }};
  execProgram(p);
  EXPECT_TRUE(checkRegisters({1, 2, 3, 4, 5}));
  EXPECT_EQ(runtime->return_code, ReturnCode::NONE);
}

TEST_F(RuntimeInstructionsTest, SimpleArithmetics) {
  Program p{"",
            {
                INSTR_SET_RegId_int_{{r0, 1}},
                INSTR_SET_RegId_int_{{r1, 2}},
                INSTR_SET_RegId_int_{{r2, 3}},
                INSTR_SET_RegId_int_{{r3, 4}},
                INSTR_SET_RegId_int_{{r4, 5}},
                INSTR_ADD_RegId_RegId_int_{{r0, r0, 1}},
                INSTR_ADD_RegId_RegId_RegId_{{r1, r0, r0}},
                INSTR_ADD_RegId_RegId_int_{{r2, r1, 2}},
                INSTR_SUB_RegId_RegId_int_{{r3, r3, 1}},
                INSTR_SUB_RegId_RegId_RegId_{{r4, r4, r0}},
            }};
  execProgram(p);
  EXPECT_TRUE(checkRegisters({2, 4, 6, 3, 3}));
  EXPECT_EQ(runtime->return_code, ReturnCode::NONE);
}
TEST_F(RuntimeInstructionsTest, Increment) {
  Program p{"",
            {
                INSTR_SET_RegId_int_{{r0, 1}},
                INSTR_SET_RegId_int_{{r1, 2}},
                INSTR_SET_RegId_int_{{r2, 3}},
                INSTR_SET_RegId_int_{{r3, 4}},
                INSTR_SET_RegId_int_{{r4, 5}},
                INSTR_INC_RegId_{{r0}},
                INSTR_INC_RegId_{{r1}},
                INSTR_INC_RegId_{{r2}},
                INSTR_INC_RegId_{{r3}},
                INSTR_INC_RegId_{{r4}},

            }};
  execProgram(p);
  EXPECT_TRUE(checkRegisters({2, 3, 4, 5, 6}));
  EXPECT_EQ(runtime->return_code, ReturnCode::NONE);
}

TEST_F(RuntimeInstructionsTest, BEQ) {
  Label passed1{"passed1"}, passed2{"passed2"}, passed3{"passed3"}, passed4{"passed4"};
  Label l1{"l1"}, l2{"l2"}, l3{"l3"}, l4{"l4"};
  Program p{"",
            {
                // clang-format off
                INSTR_BEQ_Label_RegId_int_{{passed1, r0, 0}},
                INSTR_SET_RegId_int_{{r1, 2}},
                INSTR_JMP_Label_{l1},
                INSTR_SET_RegId_int_{{r1, 3}, passed1},
                INSTR_BEQ_Label_RegId_int_{{passed2, r0, 1}, l1},
                INSTR_SET_RegId_int_{{r2, 2}},
                INSTR_JMP_Label_{l2},
                INSTR_SET_RegId_int_{{r2, 3}, passed2},
                INSTR_BEQ_Label_RegId_RegId_{{passed3, r0, r1}, l2},
                INSTR_SET_RegId_int_{{r3, 2}},
                INSTR_JMP_Label_{l3},
                INSTR_SET_RegId_int_{{r3, 3}, passed3},
                INSTR_BEQ_Label_RegId_RegId_{{passed4, r2, r2}, l3},
                INSTR_SET_RegId_int_{{r4, 2}},
                INSTR_JMP_Label_{l4},
                INSTR_SET_RegId_int_{{r4, 3}, passed4},
                INSTR_NOP_None_{{nullptr}, l4},
                // clang-format on
            }};
  execProgram(p);
  EXPECT_TRUE(checkRegisters({0, 3, 2, 2, 3}));
  EXPECT_EQ(runtime->return_code, ReturnCode::NONE);
}

TEST_F(RuntimeInstructionsTest, BEZ) {
  Label passed1{"passed1"}, passed2{"passed2"};
  Label l1{"l1"}, l2{"l2"};
  Program p{
      "",
      {
          // clang-format off
                INSTR_BEZ_Label_RegId_{{passed1,r0}},
                INSTR_SET_RegId_int_{{r1, 2}},
                INSTR_JMP_Label_{l1},
                INSTR_SET_RegId_int_{{r1, 3}, passed1},
                INSTR_SET_RegId_int_{{r0, 1}, l1},
                INSTR_BEZ_Label_RegId_{{passed2, r0}},
                INSTR_SET_RegId_int_{{r2, 2}},
                INSTR_JMP_Label_{l2},
                INSTR_SET_RegId_int_{{r2, 3}, passed2},
                INSTR_NOP_None_{{nullptr}, l2},
          // clang-format on
      }};
  execProgram(p);
  EXPECT_TRUE(checkRegisters({1, 3, 2, 0, 0}));
  EXPECT_EQ(runtime->return_code, ReturnCode::NONE);
}

TEST_F(RuntimeInstructionsTest, BNZ) {
  Label passed1{"passed1"}, passed2{"passed2"};
  Label l1{"l1"}, l2{"l2"};
  Program p{
      "",
      {
          // clang-format off
                INSTR_BNZ_Label_RegId_{{passed1,r0}},
                INSTR_SET_RegId_int_{{r1, 2}},
                INSTR_JMP_Label_{l1},
                INSTR_SET_RegId_int_{{r1, 3}, passed1},
                INSTR_SET_RegId_int_{{r0, 1}, l1},
                INSTR_BNZ_Label_RegId_{{passed2, r0}},
                INSTR_SET_RegId_int_{{r2, 2}},
                INSTR_JMP_Label_{l2},
                INSTR_SET_RegId_int_{{r2, 3}, passed2},
                INSTR_NOP_None_{{nullptr}, l2},
          // clang-format on
      }};
  execProgram(p);
  EXPECT_TRUE(checkRegisters({1, 2, 3, 0, 0}));
  EXPECT_EQ(runtime->return_code, ReturnCode::NONE);
}

TEST_F(RuntimeInstructionsTest, BLT) {
  Label passed1{"passed1"}, passed2{"passed2"}, passed3{"passed3"};
  Label l1{"l1"}, l2{"l2"}, l3{"l3"};
  Program p{"",
            {
                // clang-format off
                INSTR_BLT_Label_RegId_int_{{passed1, r0, 0}}, // same value
                INSTR_SET_RegId_int_{{r1, 2}},
                INSTR_JMP_Label_{l1},
                INSTR_SET_RegId_int_{{r1, 3}, passed1},
                INSTR_BLT_Label_RegId_int_{{passed2, r0, 1}, l1}, // r0(val: 0) less than 1? yes
                INSTR_SET_RegId_int_{{r2, 2}},
                INSTR_JMP_Label_{l2},
                INSTR_SET_RegId_int_{{r2, 3}, passed2},
                INSTR_BLT_Label_RegId_int_{{passed3, r0, -1}, l2}, // r0(val: 0) less than -1? no
                INSTR_SET_RegId_int_{{r3, 2}},
                INSTR_JMP_Label_{l3},
                INSTR_SET_RegId_int_{{r3, 3}, passed3},
                INSTR_NOP_None_{{nullptr}, l3},
                // clang-format on
            }};
  execProgram(p);
  EXPECT_TRUE(checkRegisters({0, 2, 3, 2, 0}));
  EXPECT_EQ(runtime->return_code, ReturnCode::NONE);
}

TEST_F(RuntimeInstructionsTest, ERROR) {
  testing::internal::CaptureStdout();
  Label passed1{"passed1"}, passed2{"passed2"}, passed3{"passed3"};
  Label l1{"l1"}, l2{"l2"}, l3{"l3"};
  Program p{"",
            {
                // clang-format off
                INSTR_SET_RegId_int_{{r0, 1} },
                INSTR_RET_ReturnCode_{{ReturnCode::ERROR}},
                INSTR_SET_RegId_int_{{r1, 1} },
                INSTR_SET_RegId_int_{{r2, 1} },
                // clang-format on
            }};
  EXPECT_THROW({ execProgram(p); }, std::runtime_error);
  EXPECT_TRUE(checkRegisters({1, 0, 0, 0, 0}));
  EXPECT_EQ(runtime->return_code, ReturnCode::ERROR);
  testing::internal::GetCapturedStdout();
}

TEST_F(RuntimeInstructionsTest, RET) {
  Label passed1{"passed1"}, passed2{"passed2"}, passed3{"passed3"};
  Label l1{"l1"}, l2{"l2"}, l3{"l3"};
  Program p{"",
            {
                // clang-format off
                INSTR_SET_RegId_int_{{r0, 1} },
                INSTR_RET_ReturnCode_{ReturnCode::COND_PASSED},
                INSTR_SET_RegId_int_{{r1, 1} },
                INSTR_SET_RegId_int_{{r2, 1} },
                // clang-format on
            }};
  execProgram(p);
  EXPECT_TRUE(checkRegisters({1, 0, 0, 0, 0}));
  EXPECT_EQ(runtime->return_code, ReturnCode::COND_PASSED);
}

TEST_F(RuntimeInstructionsTest, MemoryOperation) {
  Label passed1{"passed1"}, passed2{"passed2"}, passed3{"passed3"};
  Label l1{"l1"}, l2{"l2"}, l3{"l3"};
  MemoryKey key1{"key1"}, key2{"key2"};
  Program p{"",
            {
                // clang-format off
                INSTR_LOAD_RegId_MemoryKey_{{r0, key1}}, // r0 should be 0
                INSTR_ADD_RegId_RegId_int_{{r1, r0, 15}},
                INSTR_STORE_MemoryKey_RegId_{{key1, r1}}, // key1 should store 15
                INSTR_STORE_MemoryKey_int_{{key2, 23}},
                INSTR_LOAD_RegId_MemoryKey_{{r2, key1}},
                INSTR_LOAD_RegId_MemoryKey_{{r3, key2}},
                // clang-format on
            }};
  execProgram(p);
  EXPECT_TRUE(checkRegisters({0, 15, 15, 23, 0}));
  EXPECT_EQ(runtime->loadVal(key1).intValue(), 15);
  EXPECT_EQ(runtime->loadVal(key2).intValue(), 23);
  EXPECT_EQ(runtime->return_code, ReturnCode::NONE);
}
}  // namespace

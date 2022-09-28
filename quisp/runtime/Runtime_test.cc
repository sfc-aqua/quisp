#include "Runtime.h"
#include <gtest/gtest.h>
#include <modules/QRSA/RuleEngine/QubitRecord/QubitRecord.h>
#include "modules/QRSA/QRSA.h"
#include "rules/Active/ActiveRuleSet.h"
#include "runtime/types.h"

using namespace quisp::runtime;
using namespace quisp::rules;
using namespace quisp::rules::active;
using quisp::modules::qubit_record::QubitRecord;
namespace {

struct MockRuleEngineCallback : public Runtime::ICallBack {
  void freeAndResetQubit(IQubitRecord* qubit_ref) override {}
  MeasurementOutcome measureQubitRandomly(IQubitRecord* qubit_ref) override { return MeasurementOutcome(); }
  virtual void sendLinkTomographyResult(QNodeAddr partner_addr, int count, MeasurementOutcome outcome, bool is_finished) override {}
};

class RuntimeTest : public testing::Test {
 protected:
  void SetUp() {
    runtime = new Runtime();
    runtime->rule_engine = new MockRuleEngineCallback();
    runtime->rule_id = 0;
    runtime->cleanup();
    qubit = new QubitRecord{QNIC_E, 2, 3};
  }

  void TearDown() { delete runtime; }

 public:
  Runtime* runtime;
  qrsa::IQubitRecord* qubit;
};

TEST_F(RuntimeTest, initialize) { ASSERT_NE(runtime, nullptr); }

TEST_F(RuntimeTest, execSimpleRuleSet) {
  RuleSet rs{"1st ruleset",
             {
                 Rule{Program{"cond2",
                              {
                                  // clang-format off
INSTR_SET_RegId_int_{{RegId::REG0, 3}},
INSTR_DEBUG_RegId_{RegId::REG0},
INSTR_ADD_RegId_RegId_RegId_{{RegId::REG0, RegId::REG0, RegId::REG0}},
INSTR_DEBUG_RegId_{RegId::REG0},
INSTR_ADD_RegId_RegId_int_{{RegId::REG0, RegId::REG0, 1}},
INSTR_DEBUG_RegId_{RegId::REG0},
                                  // clang-format on
                              }},
                      Program{"cond2", {}}},

             }};
  rs.finalize();
  runtime->exec(std::move(rs));
}

TEST_F(RuntimeTest, evalQubitIdOperation) {
  auto q0 = 0;
  auto count = RegId::REG0;
  int max_count = 100;
  QNodeAddr partner_addr = 1;
  auto qubit_index = 0;  // former 'resource'
  runtime->assignQubitToRuleSet(partner_addr, qubit);
  runtime->debugging = true;
  Program program{"RandomMeasureAction",
                  {
                      // clang-format off
INSTR_LOAD_RegId_MemoryKey_{{count, "count"}},
INSTR_GET_QUBIT_QubitId_QNodeAddr_int_{{q0, partner_addr, qubit_index}},
INSTR_BNERR_Label_{"L1"},
INSTR_ERROR_String_{"Qubit not found for mesaurement"},
INSTR_MEASURE_RANDOM_MemoryKey_QubitId_{{"outcome", q0}, "L1"},
INSTR_INC_RegId_{count},
INSTR_STORE_MemoryKey_RegId_{{"count", count}},
INSTR_FREE_QUBIT_QubitId_{q0},
INSTR_SEND_LINK_TOMOGRAPHY_RESULT_QNodeAddr_RegId_MemoryKey_int_{{partner_addr, count, "outcome", max_count}}
                      // clang-format on
                  }};
  runtime->eval(program);
}

TEST_F(RuntimeTest, jump) {
  auto r0 = RegId::REG0;
  Program program{"JumpTest",
                  {
                      // clang-format off
INSTR_SET_RegId_int_{{r0, 10}},
INSTR_JMP_Label_{"test"},
INSTR_ADD_RegId_RegId_int_{{r0, r0, 1}},
INSTR_NOP_int_{0, "test"}
                      // clang-format on
                  }};
  runtime->cleanup();
  runtime->eval(program);
  EXPECT_EQ(runtime->getRegVal(r0), 10);
}

TEST_F(RuntimeTest, branch_if_no_error) {
  auto r0 = RegId::REG0;
  Program program{"BNErrTest",
                  {
                      // clang-format off
INSTR_SET_RegId_int_{{r0, 10}},
INSTR_BNERR_Label_{"test"},
// skip until "test" label
INSTR_ADD_RegId_RegId_int_{{r0, r0, 3}},
INSTR_NOP_int_{0, "test"}
                      // clang-format on
                  }};
  runtime->cleanup();
  runtime->eval(program);
  EXPECT_EQ(runtime->getRegVal(r0), 10);
}

TEST_F(RuntimeTest, memoryOperations) {
  auto r0 = RegId::REG0;
  Program program{"MemoryTest",
                  {
                      // clang-format off
INSTR_SET_RegId_int_{{r0, 10}},
INSTR_STORE_MemoryKey_RegId_{{"count", r0}, "INIT"},
INSTR_SUB_RegId_RegId_int_{{r0, r0, 1}},
INSTR_BNZ_Label_RegId_{{"INIT", r0}},
INSTR_LOAD_RegId_MemoryKey_{{r0, "count"}}
                      // clang-format on
                  }};
  runtime->cleanup();
  runtime->eval(program);
  EXPECT_EQ(runtime->getRegVal(r0), 1);
}
}  // namespace

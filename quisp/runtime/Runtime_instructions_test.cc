#include <gtest/gtest.h>
#include <modules/QRSA/RuleEngine/QubitRecord/QubitRecord.h>
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
  void evalProgram(const Program& p) {
    RuleSet rs{"test rs", {Rule{p, Program{"empty", {}}}}};
    rs.finalize();
    runtime->execProgram(p);
  }
  Runtime* runtime;
  qrsa::IQubitRecord* qubit;
};

TEST_F(RuntimeInstructionsTest, setRegisters) {
  auto r0 = RegId::REG0;
  auto r1 = RegId::REG1;
  auto r2 = RegId::REG2;
  auto r3 = RegId::REG3;
  Program p{"test",
            {
                INSTR_SET_RegId_int_{{r0, 1}},
                INSTR_SET_RegId_int_{{r1, 2}},
                INSTR_SET_RegId_int_{{r2, 3}},
                INSTR_SET_RegId_int_{{r3, 4}},
            }};

  evalProgram(p);
  auto& regs = runtime->registers;
  EXPECT_EQ(regs[0].value, 1);
  EXPECT_EQ(regs[1].value, 2);
  EXPECT_EQ(regs[2].value, 3);
  EXPECT_EQ(regs[3].value, 4);
}

}  // namespace

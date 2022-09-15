#include "Runtime.h"
#include <gtest/gtest.h>
#include "rules/Active/ActiveRuleSet.h"

using namespace quisp::runtime;
using namespace quisp::rules;
using namespace quisp::rules::active;

namespace {
class RuntimeTest : public testing::Test {
 protected:
  void SetUp() { runtime = new Runtime(); }

  void TearDown() { delete runtime; }

 public:
  Runtime* runtime;
};

TEST_F(RuntimeTest, initialize) { ASSERT_NE(runtime, nullptr); }
TEST_F(RuntimeTest, execSimpleRuleSet) {
  Rule rule{Program{"cond1",
                    {
                        {INSTR_NOP_int_(0)},
                    }},
            Program{"action1", {{INSTR_NOP_int_(0)}}}};
  Program p{"cond2", {INSTR_DEBUG_String_{"test"}}};
  std::cout << p.opcodes[0].index() << std::endl;
  RuleSet rs{"1st ruleset",
             {
                 Rule{Program{"cond2",
                              {
                                  INSTR_DEBUG_int_{1},
                                  INSTR_SET_RegId_int_{{RegId::REG0, 3}},
                                  INSTR_ADD_RegId_RegId_RegId_{{RegId::REG0, RegId::REG0, RegId::REG0}},
                                  INSTR_DEBUG_RegId_{RegId::REG0},
                                  INSTR_ADD_RegId_RegId_int_{{RegId::REG0, RegId::REG0, 1}},
                                  INSTR_DEBUG_RegId_{RegId::REG0},
                              }},
                      Program{"cond2", {INSTR_DEBUG_String_{"test"}}}},

             }};
  runtime->exec(std::move(rs));
  // runtime->exec(RuleSet{"test ruleset"});

  // auto count = RegId::REG0;
  // auto outcome = RegId::REG1;
  // auto qubit0 = QubitId::Qubit0;
  // Program{"RandomMeasureAction", {
  //   INSTR_GET_QUBIT_QubitId_PartnerId_{Qubit0}
  //   INSTR_BEQ_Label_{3},
  //   INSTR_ERROR_String_{"Qubit not found for mesaurement"},
  //   INSTR_MEASURE_RegId_QubitId_{count, Qubit0},
  //   INSTR_INC_RegId_{RegId::REG1},
  //   INSTR_SEND_LINK_TOMOGRAPHY_RESULT{RegId::REG0,RegId::REG1}
  // }};
}
}  // namespace

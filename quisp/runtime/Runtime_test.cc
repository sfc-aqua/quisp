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
                        {Inst_NOP_int_(0)},
                    }},
            Program{"action1", {{Inst_NOP_int_(0)}}}};
  Program p{"cond2", {Inst_DEBUG_String_{"test"}}};
  std::cout << p.opcodes[0].index() << std::endl;
  RuleSet rs{"1st ruleset",
             {
                 Rule{Program{"cond2",
                              {
                                  Inst_DEBUG_int_{1},
                                  Inst_ADD_RegisterId_int_int_{{REG0, 1, 2}},
                                  Inst_ADD_RegisterId_RegisterId_RegisterId_{{REG0, REG0, REG0}},
                                  Inst_DEBUG_RegisterId_{REG0},
                              }},
                      Program{"cond2", {Inst_DEBUG_String_{"test"}}}},

             }};
  runtime->exec(std::move(rs));
  // runtime->exec(RuleSet{"test ruleset"});
}
}  // namespace

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
                        {OpType::NONE},
                    }},
            Program{"action1", {{OpType::DEBUG}}}};
  RuleSet rs{"1st ruleset",
             {
                 Rule{Program{"cond2", {{OpType::DEBUG}}}, Program{"cond2", {{OpType::DEBUG}}}},

             }};
  runtime->exec(std::move(rs));
  runtime->exec(RuleSet{"test ruleset"});
}
}  // namespace

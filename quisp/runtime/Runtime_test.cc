#include "Runtime.h"
#include <gtest/gtest.h>
#include "rules/Active/ActiveRuleSet.h"

using namespace quisp::runtime;
using namespace quisp::rules;
using namespace quisp::rules::active;

namespace {
class RuntimeTest : public testing::Test {
 protected:
  void SetUp() {}

  void TearDown() {}

 public:
  Runtime* runtime;
};

TEST_F(RuntimeTest, initialize) { ASSERT_NE(runtime, nullptr); }
TEST_F(RuntimeTest, execSimpleRuleSet) {
  auto rs = new ActiveRuleSet(0, 1);
  rs->addRule(std::make_unique<ActiveRule>(0, 0, 3, "test"));
  runtime->exec(rs);
}
}  // namespace

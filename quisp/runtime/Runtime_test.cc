#include "Runtime.h"
#include <gtest/gtest.h>

using namespace quisp::runtime;

namespace {
class RuntimeTest : public testing::Test {
 protected:
  void SetUp() {}

  void TearDown() {}

 public:
  Runtime* runtime;
};

TEST_F(RuntimeTest, initialize) { ASSERT_NE(runtime, nullptr); }
}  // namespace

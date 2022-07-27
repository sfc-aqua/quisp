#include "LoggerModule.h"
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>

namespace {
using namespace quisp_test;
using namespace quisp::modules;
class LoggerModule : public quisp::modules::Logger::LoggerModule {
 public:
  using quisp::modules::Logger::LoggerModule::trim_quotes;
};
class LoggerModuleTest : public testing::Test {
 protected:
  void SetUp() { utils::prepareSimulation(); }
};

TEST_F(LoggerModuleTest, trim_quote) {
  EXPECT_EQ(LoggerModule::trim_quotes("\"test\""), "test");
  EXPECT_EQ(LoggerModule::trim_quotes("test\""), "test");
  EXPECT_EQ(LoggerModule::trim_quotes("\"test"), "test");
  EXPECT_EQ(LoggerModule::trim_quotes("test"), "test");
}
}  // namespace

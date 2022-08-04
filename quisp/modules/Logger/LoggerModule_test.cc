#include "LoggerModule.h"
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include "test_utils/UtilFunctions.h"

namespace {
using namespace quisp_test;
using namespace quisp_test::utils;
using namespace quisp::modules;
class LoggerModule : public quisp::modules::Logger::LoggerModule {
 public:
  using quisp::modules::Logger::LoggerModule::trim_quotes;
};
class LoggerModuleTest : public testing::Test {
 protected:
  void SetUp() {
    sim = utils::prepareSimulation();
    logger_module = new LoggerModule();
    logger_module->setComponentType(new TestModuleType("test logger module"));
    setParStr(logger_module, "log_filename", "test.log");
    sim->registerComponent(logger_module);
  }
  void TearDown() { logger_module->deleteModule(); }
  LoggerModule *logger_module;
  utils::TestSimulation *sim;
};

TEST_F(LoggerModuleTest, trim_quote) {
  EXPECT_EQ(LoggerModule::trim_quotes("\"test\""), "test");
  EXPECT_EQ(LoggerModule::trim_quotes("test\""), "test");
  EXPECT_EQ(LoggerModule::trim_quotes("\"test"), "test");
  EXPECT_EQ(LoggerModule::trim_quotes("test"), "test");
}
TEST_F(LoggerModuleTest, initialize) { logger_module->callInitialize(); }

TEST_F(LoggerModuleTest, finish) {
  logger_module->callInitialize();
  logger_module->callFinish();
}

TEST_F(LoggerModuleTest, getLogger) {
  logger_module->callInitialize();
  auto *logger = logger_module->getLogger();
  ASSERT_NE(logger, nullptr);
}
}  // namespace

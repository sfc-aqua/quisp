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
  using quisp::modules::Logger::LoggerModule::toLoggerType;
  using quisp::modules::Logger::LoggerModule::trimQuotes;
};
class LoggerModuleTest : public testing::Test {
 protected:
  void SetUp() {
    sim = utils::prepareSimulation();
    logger_module = new LoggerModule();
    logger_module->setComponentType(new TestModuleType("test logger module"));
    setParStr(logger_module, "log_filename", "test.log");
    setParStr(logger_module, "logger", "JsonLogger");
    sim->registerComponent(logger_module);
  }
  void TearDown() { logger_module->deleteModule(); }
  LoggerModule *logger_module;
  utils::TestSimulation *sim;
};

TEST_F(LoggerModuleTest, trimQuote) {
  EXPECT_EQ(LoggerModule::trimQuotes("\"test\""), "test");
  EXPECT_EQ(LoggerModule::trimQuotes("test\""), "test");
  EXPECT_EQ(LoggerModule::trimQuotes("\"test"), "test");
  EXPECT_EQ(LoggerModule::trimQuotes("test"), "test");
}

TEST_F(LoggerModuleTest, toLoggerType) {
  using quisp::modules::Logger::LoggerType;
  EXPECT_EQ(LoggerModule::toLoggerType("JsonLogger"), LoggerType::JsonLogger);
  EXPECT_EQ(LoggerModule::toLoggerType("UnknownLogger"), LoggerType::Unknown);
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

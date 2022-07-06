#include "Logger.h"
#include <gtest/gtest.h>
#include <messages/classical_messages.h>
#include <spdlog/sinks/ostream_sink.h>
#include <spdlog/spdlog.h>
#include <test_utils/TestUtils.h>
#include <memory>
#include "messages/connection_setup_messages_m.h"
#include "test_utils/UtilFunctions.h"

namespace {

using quisp::messages::ConnectionSetupRequest;
using quisp::modules::Logger::Logger;
using namespace quisp_test;

class LoggerTest : public testing::Test {
 protected:
  void SetUp() {
    utils::prepareSimulation();
    ostream_sink = std::make_shared<spdlog::sinks::ostream_sink_mt>(log_stream);
    logger = new Logger(std::make_shared<spdlog::logger>("test_logger", ostream_sink));
  }
  Logger* logger;
  std::ostringstream log_stream;
  std::shared_ptr<spdlog::sinks::ostream_sink_mt> ostream_sink;
};

TEST_F(LoggerTest, Init) {
  auto* req = new ConnectionSetupRequest();
  logger->logPacket("test", req);
  std::cout << log_stream.str();
}
}  // namespace

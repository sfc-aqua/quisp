#include "JsonLogger.h"
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
using quisp::modules::Logger::JsonLogger;
using namespace quisp_test;

class JsonLoggerTest : public testing::Test {
 protected:
  void SetUp() {
    utils::prepareSimulation();
    ostream_sink = std::make_shared<spdlog::sinks::ostream_sink_mt>(log_stream);
    logger = new JsonLogger(std::make_shared<spdlog::logger>("test_logger", ostream_sink));
  }
  JsonLogger* logger;
  std::ostringstream log_stream;
  std::shared_ptr<spdlog::sinks::ostream_sink_mt> ostream_sink;
};

TEST_F(JsonLoggerTest, ConnReqSetupTest) {
  auto* req = new ConnectionSetupRequest();
  req->setActual_destAddr(1);
  req->setActual_srcAddr(2);
  req->setNum_measure(5);
  req->setNumber_of_required_Bellpairs(7);
  logger->logPacket("test", req);
  EXPECT_EQ(log_stream.str(),
            "{\"level\": \"info\", \"simtime\": 0, \"event_type\": \"test\", \"path\": \"\", \"msg_type\": \"ConnectionSetupRequest\", \"actual_dest_addr\": 1, "
            "\"actual_src_addr\": 2, \"num_measure\": 5, "
            "\"num_required_bell_pairs\": 7}\n");
}
}  // namespace

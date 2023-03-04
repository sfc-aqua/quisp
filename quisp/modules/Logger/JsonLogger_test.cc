#include <gtest/gtest.h>
#include <messages/classical_messages.h>
#include <spdlog/sinks/ostream_sink.h>
#include <spdlog/spdlog.h>
#include <test_utils/TestUtils.h>
#include <memory>

#include "JsonLogger.h"
#include "messages/connection_setup_messages_m.h"
#include "modules/QNIC.h"
#include "omnetpp/cmessage.h"
#include "test_utils/UtilFunctions.h"

namespace {

using quisp::messages::ConnectionSetupRequest;
using quisp::modules::Logger::JsonLogger;
using namespace quisp::messages;
using namespace quisp_test;

class JsonLoggerTest : public testing::Test {
 protected:
  void SetUp() {
    utils::prepareSimulation();
    ostream_sink = std::make_shared<spdlog::sinks::ostream_sink_mt>(log_stream);
    logger = new JsonLogger(std::make_shared<spdlog::logger>("test_logger", ostream_sink));
  }
  void TearDown() { delete logger; }
  JsonLogger* logger;
  std::ostringstream log_stream;
  std::shared_ptr<spdlog::sinks::ostream_sink_mt> ostream_sink;
};

TEST_F(JsonLoggerTest, ConnSetupTest) {
  auto* req = new ConnectionSetupRequest();
  req->setApplicationId(1);
  req->setActual_destAddr(1);
  req->setActual_srcAddr(2);
  req->setNum_measure(5);
  req->setNumber_of_required_Bellpairs(7);
  logger->setQNodeAddress(7);
  logger->logPacket("test", req);
  EXPECT_EQ(log_stream.str(),
            "{\"simtime\": 0, \"event_type\": \"test\", \"address\": \"7\", \"msg_type\": \"ConnectionSetupRequest\", "
            "\"application_id\": 1, \"actual_dest_addr\": 1, "
            "\"actual_src_addr\": 2, \"num_measure\": 5, "
            "\"num_required_bell_pairs\": 7}\n");
}

TEST_F(JsonLoggerTest, ConnSetupRespTest) {
  auto* res = new ConnectionSetupResponse();
  res->setApplicationId(1);
  res->setActual_destAddr(1);
  res->setActual_srcAddr(2);
  logger->setQNodeAddress(7);
  logger->logPacket("test", res);
  EXPECT_EQ(log_stream.str(),
            "{\"simtime\": 0, \"event_type\": \"test\", \"address\": \"7\", \"msg_type\": \"ConnectionSetupResponse\", "
            "\"application_id\": 1, \"actual_dest_addr\": 1, \"actual_src_addr\": 2, "
            "\"ruleset_id\": 0, \"ruleset\": null, \"application_type\": 0, "
            "\"stack_of_qnode_indices\": []}\n");
}

TEST_F(JsonLoggerTest, ConnRejectTest) {
  auto* rej = new RejectConnectionSetupRequest();
  rej->setApplicationId(1);
  rej->setActual_destAddr(1);
  rej->setActual_srcAddr(2);
  logger->setQNodeAddress(7);
  logger->logPacket("test", rej);
  EXPECT_EQ(log_stream.str(),
            "{\"simtime\": 0, \"event_type\": \"test\", \"address\": \"7\", \"msg_type\": \"RejectConnectionSetupRequest\", "
            "\"application_id\": 1, \"actual_dest_addr\": 1, "
            "\"actual_src_addr\": 2, \"num_required_bell_pairs\": 0}\n");
}
TEST_F(JsonLoggerTest, UnknownPacket) {
  auto* packet = new cMessage();
  logger->logPacket("test", packet);
  EXPECT_EQ(log_stream.str(), "{\"simtime\": 0, \"event_type\": \"test\", \"address\": \"-1\", \"msg\": \"unknown class\": \"globalOwningContext.\"}\n");
}

TEST_F(JsonLoggerTest, LogBellPairTest) {
  logger->logBellPairInfo("Generated", 1, quisp::modules::QNIC_E, 2, 3);
  EXPECT_EQ(log_stream.str(),
            "{\"simtime\": 0, \"event_type\": \"BellPairGenerated\", \"address\": \"-1\", \"partner_addr\": 1, \"qnic_type\": 0, \"qnic_index\": 2, \"qubit_index\": 3}\n");
}

TEST_F(JsonLoggerTest, LogQubitState) {
  logger->logQubitState(quisp::modules::QNIC_E, 1, 2, true, false);
  EXPECT_EQ(log_stream.str(),
            "{\"simtime\": 0, \"event_type\": \"QubitStateChange\", \"address\": \"-1\", \"qnic_type\": 0, \"qnic_index\": 1, \"qubit_index\": 2, \"busy\": true, \"allocated\": "
            "false}\n");
}
}  // namespace

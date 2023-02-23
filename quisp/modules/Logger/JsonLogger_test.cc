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
    logger->setQNodeAddress(QNodeAddr{7});
  }
  void TearDown() { delete logger; }
  JsonLogger* logger;
  std::ostringstream log_stream;
  std::shared_ptr<spdlog::sinks::ostream_sink_mt> ostream_sink;
};

TEST_F(JsonLoggerTest, ConnSetupTest) {
  auto* req = new ConnectionSetupRequest();
  req->setActual_destAddr(QNodeAddr{1});
  req->setActual_srcAddr(QNodeAddr{2});
  req->setNum_measure(5);
  req->setNumber_of_required_Bellpairs(7);
  logger->logPacket("test", req);
  EXPECT_EQ(log_stream.str(),
            "{\"simtime\": 0, \"event_type\": \"test\", \"address\": \"0.7\", \"msg_type\": \"ConnectionSetupRequest\", \"actual_dest_addr\": \"0.1\", "
            "\"actual_src_addr\": \"0.2\", \"num_measure\": 5, "
            "\"num_required_bell_pairs\": 7}\n");
}

TEST_F(JsonLoggerTest, ConnSetupRespTest) {
  auto* res = new ConnectionSetupResponse();
  res->setActual_destAddr(QNodeAddr{1});
  res->setActual_srcAddr(QNodeAddr{2});
  logger->logPacket("test", res);
  EXPECT_EQ(
      log_stream.str(),
      "{\"simtime\": 0, \"event_type\": \"test\", \"address\": \"0.7\", \"msg_type\": \"ConnectionSetupResponse\", \"actual_dest_addr\": \"0.1\", \"actual_src_addr\": \"0.2\", "
      "\"ruleset_id\": 0, \"ruleset\": null, \"application_type\": 0, \"stack_of_qnode_indices\": []}\n");
}

TEST_F(JsonLoggerTest, ConnRejectTest) {
  auto* rej = new RejectConnectionSetupRequest();
  rej->setActual_destAddr(QNodeAddr{1});
  rej->setActual_srcAddr(QNodeAddr{2});
  logger->logPacket("test", rej);
  EXPECT_EQ(log_stream.str(),
            "{\"simtime\": 0, \"event_type\": \"test\", \"address\": \"0.7\", \"msg_type\": \"RejectConnectionSetupRequest\", \"actual_dest_addr\": \"0.1\", "
            "\"actual_src_addr\": \"0.2\", \"num_required_bell_pairs\": 0}\n");
}
TEST_F(JsonLoggerTest, UnknownPacket) {
  auto* packet = new cMessage();
  logger->logPacket("test", packet);
  EXPECT_EQ(log_stream.str(), "{\"simtime\": 0, \"event_type\": \"test\", \"address\": \"0.7\", \"msg\": \"unknown class\": \"globalOwningContext.\"}\n");
}

TEST_F(JsonLoggerTest, LogBellPairTest) {
  logger->logBellPairInfo("Generated", QNodeAddr{1}, quisp::modules::QNIC_E, 2, 3);
  EXPECT_EQ(log_stream.str(),
            "{\"simtime\": 0, \"event_type\": \"BellPairGenerated\", \"address\": \"0.7\", \"partner_addr\": \"0.1\", \"qnic_type\": 0, \"qnic_index\": 2, \"qubit_index\": 3}\n");
}

TEST_F(JsonLoggerTest, LogQubitState) {
  logger->logQubitState(quisp::modules::QNIC_E, 1, 2, true, false);
  EXPECT_EQ(log_stream.str(),
            "{\"simtime\": 0, \"event_type\": \"QubitStateChange\", \"address\": \"0.7\", \"qnic_type\": 0, \"qnic_index\": 1, \"qubit_index\": 2, \"busy\": true, \"allocated\": "
            "false}\n");
}
}  // namespace

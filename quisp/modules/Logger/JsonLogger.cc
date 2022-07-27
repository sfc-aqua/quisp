#include "JsonLogger.h"
#include <sstream>
#include "messages/connection_setup_messages_m.h"

namespace quisp::modules::Logger {

using quisp::messages::ConnectionSetupRequest;
using quisp::messages::ConnectionSetupResponse;
using quisp::messages::RejectConnectionSetupRequest;

JsonLogger::JsonLogger(std::shared_ptr<spdlog::logger> logger) : _logger(logger) {
  std::string jsonpattern = {"{\"level\": \"%^%l%$\", %v}"};
  _logger->set_pattern(jsonpattern);
}

JsonLogger::~JsonLogger() {}

void JsonLogger::setModule(omnetpp::cModule* mod) {
  module = mod;
  module_path = mod->getFullPath();
}

void JsonLogger::logPacket(std::string event_type, omnetpp::cMessage* msg) {
  auto current_time = omnetpp::simTime();
  _logger->info("\"simtime\": {}, \"event_type\": \"{}\", \"path\": \"{}\", {}", current_time, event_type, module_path, format(msg));
}

std::string JsonLogger::format(omnetpp::cMessage* msg) {
  if (auto req = dynamic_cast<const quisp::messages::ConnectionSetupRequest*>(msg)) {
    std::stringstream os;
    os << "\"actual_dest_addr\": " << req->getActual_destAddr();
    os << ", \"actual_src_addr\": " << req->getActual_srcAddr();
    os << ", \"num_measure\": " << req->getNum_measure();
    os << ", \"num_required_bell_pairs\": " << req->getNumber_of_required_Bellpairs();
    return os.str();
  }
  if (auto req = dynamic_cast<const quisp::messages::RejectConnectionSetupRequest*>(msg)) {
    std::stringstream os;
    os << "\"actual_dest_addr\": " << req->getActual_destAddr();
    os << ", \"actual_src_addr\": " << req->getActual_srcAddr();
    os << ", \"num_required_bell_pairs\": " << req->getNumber_of_required_Bellpairs();
    return os.str();
  }
  if (auto req = dynamic_cast<const quisp::messages::ConnectionSetupResponse*>(msg)) {
    std::stringstream os;
    os << "\"actual_dest_addr\": " << req->getActual_destAddr();
    os << ", \"actual_src_addr\": " << req->getActual_srcAddr();
    os << ", \"ruleset_id\": " << req->getRuleSet_id();
    os << ", \"ruleset\": " << req->getRuleSet();
    os << ", \"application_type\": " << req->getApplication_type();
    os << ", \"stack_of_qnode_indices\": [";
    for (int i = 0; i < req->getStack_of_QNodeIndexesArraySize(); i++) {
      if (i != 0) os << ", ";
      os << req->getStack_of_QNodeIndexes(i);
    }
    os << "]";
    return os.str();
  }
}

}  // namespace quisp::modules::Logger

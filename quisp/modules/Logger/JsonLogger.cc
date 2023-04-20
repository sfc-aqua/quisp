#include "JsonLogger.h"
#include <sstream>
#include "messages/connection_setup_messages_m.h"

namespace quisp::modules::Logger {

using quisp::messages::ConnectionSetupRequest;
using quisp::messages::ConnectionSetupResponse;
using quisp::messages::RejectConnectionSetupRequest;
using quisp::types::QNodeAddr;

JsonLogger::JsonLogger(std::shared_ptr<spdlog::logger> logger) : _logger(logger) {
  std::string jsonpattern = {"{%v}"};
  _logger->set_pattern(jsonpattern);
}

JsonLogger::~JsonLogger() {}

void JsonLogger::setModule(omnetpp::cModule const* const mod) {
  module = mod;
  module_path = mod->getFullPath();
}

void JsonLogger::setQNodeAddress(QNodeAddr addr) { qnode_address = addr; }

void JsonLogger::logPacket(const std::string& event_type, omnetpp::cMessage const* const msg) {
  auto current_time = omnetpp::simTime();
  _logger->info("\"simtime\": {}, \"event_type\": \"{}\", \"address\": \"{}\", {}", current_time, event_type, qnode_address, format(msg));
  _logger->flush();
}

void JsonLogger::logQubitState(quisp::modules::QNIC_type qnic_type, int qnic_index, int qubit_index, bool is_busy, bool is_allocated) {
  // auto current_time = omnetpp::simTime();
  // _logger->info(
  // "\"simtime\": {}, \"event_type\": \"QubitStateChange\", \"address\": \"{}\", \"qnic_type\": {}, \"qnic_index\": {}, \"qubit_index\": {}, \"busy\": {}, \"allocated\": {}",
  // current_time, qnode_address, qnic_type, qnic_index, qubit_index, is_busy, is_allocated);
}

std::string JsonLogger::format(omnetpp::cMessage const* const msg) {
  if (auto* req = dynamic_cast<const quisp::messages::ConnectionSetupRequest*>(msg)) {
    std::stringstream os;
    os << "\"msg_type\": \"ConnectionSetupRequest\"";
    os << ", \"application_id\": " << req->getApplicationId();
    os << ", \"actual_dest_addr\": \"" << req->getActual_destAddr();
    os << "\", \"actual_src_addr\": \"" << req->getActual_srcAddr();
    os << "\", \"num_measure\": " << req->getNum_measure();
    os << ", \"num_required_bell_pairs\": " << req->getNumber_of_required_Bellpairs();
    os << ", \"stack_of_qnode_indices\": [";
    for (int i = 0; i < req->getStack_of_QNodeIndexesArraySize(); i++) {
      if (i != 0) os << ", ";
      os << req->getStack_of_QNodeIndexes(i);
    }
    os << "]";
    return os.str();
  }
  if (auto* req = dynamic_cast<const quisp::messages::RejectConnectionSetupRequest*>(msg)) {
    std::stringstream os;
    os << "\"msg_type\": \"RejectConnectionSetupRequest\"";
    os << ", \"application_id\": " << req->getApplicationId();
    os << ", \"actual_dest_addr\": \"" << req->getActual_destAddr();
    os << "\", \"actual_src_addr\": \"" << req->getActual_srcAddr();
    os << "\", \"num_required_bell_pairs\": " << req->getNumber_of_required_Bellpairs();
    return os.str();
  }
  if (auto* req = dynamic_cast<const quisp::messages::ConnectionSetupResponse*>(msg)) {
    std::stringstream os;
    os << "\"msg_type\": \"ConnectionSetupResponse\"";
    os << ", \"application_id\": " << req->getApplicationId();
    os << ", \"actual_dest_addr\": \"" << req->getActual_destAddr();
    os << "\", \"actual_src_addr\": \"" << req->getActual_srcAddr();
    os << "\", \"ruleset_id\": " << req->getRuleSet_id();
    os << ", \"ruleset\": " << req->getRuleSet();
    os << ", \"application_type\": " << req->getApplication_type();
    return os.str();
  }

  return "\"msg\": \"unknown class\": \"" + msg->getFullPath() + "\"";
}

void JsonLogger::logBellPairInfo(const std::string& event_type, QNodeAddr partner_addr, quisp::modules::QNIC_type qnic_type, int qnic_index, int qubit_index) {
  auto current_time = omnetpp::simTime();
  _logger->info("\"simtime\": {}, \"event_type\": \"BellPair{}\", \"address\": \"{}\", \"partner_addr\": \"{}\", \"qnic_type\": {}, \"qnic_index\": {}, \"qubit_index\": {}",
                current_time, event_type, qnode_address, partner_addr, qnic_type, qnic_index, qubit_index);
}

}  // namespace quisp::modules::Logger

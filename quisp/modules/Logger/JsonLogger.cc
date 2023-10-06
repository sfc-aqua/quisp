#include "JsonLogger.h"
#include <sstream>
#include "messages/QNode_ipc_messages_m.h"
#include "messages/barrier_messages_m.h"
#include "messages/connection_setup_messages_m.h"

namespace quisp::modules::Logger {

using quisp::messages::ConnectionSetupRequest;
using quisp::messages::ConnectionSetupResponse;
using quisp::messages::ConnectionTeardownMessage;
using quisp::messages::RejectConnectionSetupRequest;

JsonLogger::JsonLogger(std::shared_ptr<spdlog::logger> logger) : _logger(logger) {
  std::string jsonpattern = {"{%v}"};
  _logger->set_pattern(jsonpattern);
}

JsonLogger::~JsonLogger() {}

void JsonLogger::setModule(omnetpp::cModule const* const mod) {
  module = mod;
  module_path = mod->getFullPath();
}

void JsonLogger::setQNodeAddress(int addr) { qnode_address = addr; }

void JsonLogger::logPacket(const std::string& event_type, omnetpp::cMessage const* const msg) {
  auto current_time = omnetpp::simTime();
  _logger->info("\"simtime\": {}, \"event_type\": \"{}\", \"address\": \"{}\", {}", current_time, event_type, qnode_address, format(msg));
}

void JsonLogger::logQubitState(quisp::modules::QNIC_type qnic_type, int qnic_index, int qubit_index, bool is_busy, bool is_allocated) {
  auto current_time = omnetpp::simTime();
  _logger->info(
      "\"simtime\": {}, \"event_type\": \"QubitStateChange\", \"address\": \"{}\", \"qnic_type\": {}, \"qnic_index\": {}, \"qubit_index\": {}, \"busy\": {}, \"allocated\": {}",
      current_time, qnode_address, qnic_type, qnic_index, qubit_index, is_busy, is_allocated);
}

std::string JsonLogger::format(omnetpp::cMessage const* const msg) {
  if (auto* req = dynamic_cast<const quisp::messages::ConnectionSetupRequest*>(msg)) {
    std::stringstream os;
    os << "\"msg_type\": \"ConnectionSetupRequest\"";
    os << ", \"application_id\": " << req->getApplicationId();
    os << ", \"actual_dest_addr\": " << req->getActual_destAddr();
    os << ", \"actual_src_addr\": " << req->getActual_srcAddr();
    os << ", \"num_measure\": " << req->getNum_measure();
    os << ", \"num_required_bell_pairs\": " << req->getNumber_of_required_Bellpairs();
    os << ", \"stack_of_qnic_address\": [";
    for (int i = 0; i < req->getStack_of_QNICsArraySize(); i++) {
      if (i != 0) os << ", ";
      os << req->getStack_of_QNICs(i).first.address << " ";
      os << req->getStack_of_QNICs(i).second.address << " ";
    }
    os << "]";
    return os.str();
  }
  if (auto* req = dynamic_cast<const quisp::messages::RejectConnectionSetupRequest*>(msg)) {
    std::stringstream os;
    os << "\"msg_type\": \"RejectConnectionSetupRequest\"";
    os << ", \"application_id\": " << req->getApplicationId();
    os << ", \"actual_dest_addr\": " << req->getActual_destAddr();
    os << ", \"actual_src_addr\": " << req->getActual_srcAddr();
    os << ", \"num_required_bell_pairs\": " << req->getNumber_of_required_Bellpairs();
    return os.str();
  }
  if (auto* req = dynamic_cast<const quisp::messages::ConnectionSetupResponse*>(msg)) {
    std::stringstream os;
    os << "\"msg_type\": \"ConnectionSetupResponse\"";
    os << ", \"application_id\": " << req->getApplicationId();
    os << ", \"actual_dest_addr\": " << req->getActual_destAddr();
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
    os << ", \"stack_of_qnic_address\": [";
    for (int i = 0; i < req->getStack_of_QNICsArraySize(); i++) {
      if (i != 0) os << ", ";
      os << req->getStack_of_QNICs(i).address;
    }
    os << "]";
    return os.str();
  }
  if (auto* req = dynamic_cast<const quisp::messages::ConnectionTeardownMessage*>(msg)) {
    std::stringstream os;
    os << "\"msg_type\": \"ConnectionTeardownMessage\"";
    os << ", \"actual_dest_addr\": " << req->getActual_destAddr();
    os << ", \"actual_src_addr\": " << req->getActual_srcAddr();
    os << ", \"LAU_req_dest_addr\": " << req->getLAU_req_destAddr();
    os << ", \"LAU_req_src_addr\": " << req->getLAU_req_srcAddr();
    os << ", \"ruleset_id\": " << req->getRuleSet_id();
    return os.str();
  }

  if (auto* req = dynamic_cast<const quisp::messages::InternalNodeAddressesAlongPathForwarding*>(msg)) {
    std::stringstream os;
    os << "\"msg_type\": \"InternalNodeAddressesAlongPathForwarding\"";
    for (auto i = 0; i < req->getNode_addresses_along_pathArraySize(); i++) {
      os << ", \"node_address_along_path\": " << req->getNode_addresses_along_path(i);
    }
    os << ", \"ruleset_id\": " << req->getRuleSet_id();
    return os.str();
  }

  if (auto* req = dynamic_cast<const quisp::messages::InternalRuleSetForwarding_Application*>(msg)) {
    std::stringstream os;
    os << "\"msg_type\": \"InternalRuleSetForwarding_Application\"";
    os << ", \"rule_id\": " << req->getRule_id();
    os << ", \"ruleset_id\": " << req->getRuleSet_id();
    os << ", \"ruleset\": " << req->getRuleSet();
    os << ", \"application_type\": " << req->getApplication_type();
    return os.str();
  }

  if (auto* req = dynamic_cast<const quisp::messages::InternalRuleSetForwarding*>(msg)) {
    std::stringstream os;
    os << "\"msg_type\": \"InternalRuleSetForwarding\"";
    os << ", \"rule_id\": " << req->getRule_id();
    os << ", \"ruleset_id\": " << req->getRuleSet_id();
    os << ", \"ruleset\": " << req->getRuleSet();
    return os.str();
  }

  if (auto* req = dynamic_cast<const quisp::messages::InternalConnectionTeardownMessage*>(msg)) {
    std::stringstream os;
    os << "\"msg_type\": \"InternalConnectionTeardownMessage\"";
    os << ", \"actual_dest_addr\": " << req->getActual_destAddr();
    os << ", \"actual_src_addr\": " << req->getActual_srcAddr();
    os << ", \"LAU_req_dest_addr\": " << req->getLAU_req_destAddr();
    os << ", \"LAU_req_src_addr\": " << req->getLAU_req_srcAddr();
    os << ", \"ruleset_id\": " << req->getRuleSet_id();
    return os.str();
  }

  if (auto* req = dynamic_cast<const quisp::messages::LinkAllocationUpdateDecisionRequest*>(msg)) {
    std::stringstream os;
    os << "\"msg_type\": \"LinkAllocationUpdateDecisionRequest\"";
    os << ", \"dest_addr\": " << req->getDestAddr();
    os << ", \"src_addr\": " << req->getSrcAddr();
    os << ", \"current_ruleset_id\": " << req->getCurrentRuleSet_id();
    for (auto i = 0; i < req->getOffered_ruleset_idsArraySize(); i++) {
      os << ", \"offered_ruleset_id\": " << req->getOfferedRuleSet_ids(i);
    }
    return os.str();
  }

  if (auto* req = dynamic_cast<const quisp::messages::LinkAllocationUpdateDecisionResponse*>(msg)) {
    std::stringstream os;
    os << "\"msg_type\": \"LinkAllocationUpdateDecisionResponse\"";
    os << ", \"dest_addr\": " << req->getDestAddr();
    os << ", \"src_addr\": " << req->getSrcAddr();
    os << ", \"current_ruleset_id\": " << req->getCurrentRuleSet_id();
    os << ", \"negotiated_ruleset_id\": " << req->getNegotiatedRuleSet_id();
    return os.str();
  }

  if (auto* req = dynamic_cast<const quisp::messages::BarrierMessage*>(msg)) {
    std::stringstream os;
    os << "\"msg_type\": \"BarrierMessage\"";
    os << ", \"dest_addr\": " << req->getDestAddr();
    os << ", \"src_addr\": " << req->getSrcAddr();
    os << ", \"actual_dest_addr\": " << req->getActual_destAddr();
    os << ", \"actual_src_addr\": " << req->getActual_srcAddr();
    os << ", \"negotiated_ruleset_id\": " << req->getNegotiatedRuleSet_id();
    os << ", \"qubit_record\": " << req->getQubitRecord();
    os << ", \"sequence_number\": " << req->getSequence_number();
    os << ", \"is_sender\": " << req->getIs_sender();
    os << ", \"is_last\": " << req->getIs_last();
    return os.str();
  }

  if (auto* req = dynamic_cast<const quisp::messages::LinkAllocationUpdateRequest*>(msg)) {
    std::stringstream os;
    os << "\"msg_type\": \"LinkAllocationUpdateRequest\"";
    os << ", \"dest_addr\": " << req->getDestAddr();
    os << ", \"src_addr\": " << req->getSrcAddr();
    os << ", \"current_ruleset_id\": " << req->getCurrentRuleSet_id();
    os << ", \"negotiated_ruleset_id\": " << req->getNegotiatedRuleSet_id();
    return os.str();
  }

  if (auto* req = dynamic_cast<const quisp::messages::LinkAllocationUpdateResponse*>(msg)) {
    std::stringstream os;
    os << "\"msg_type\": \"LinkAllocationUpdateResponse\"";
    os << ", \"dest_addr\": " << req->getDestAddr();
    os << ", \"src_addr\": " << req->getSrcAddr();
    os << ", \"current_ruleset_id\": " << req->getCurrentRuleSet_id();
    os << ", \"negotiated_ruleset_id\": " << req->getNegotiatedRuleSet_id();
    return os.str();
  }

  return "\"msg\": \"unknown class\": \"" + msg->getFullPath() + "\"";
}

void JsonLogger::logBellPairInfo(const std::string& event_type, int partner_addr, quisp::modules::QNIC_type qnic_type, int qnic_index, int qubit_index) {
  auto current_time = omnetpp::simTime();
  _logger->info("\"simtime\": {}, \"event_type\": \"BellPair{}\", \"address\": \"{}\", \"partner_addr\": {}, \"qnic_type\": {}, \"qnic_index\": {}, \"qubit_index\": {}",
                current_time, event_type, qnode_address, partner_addr, qnic_type, qnic_index, qubit_index);
}

}  // namespace quisp::modules::Logger

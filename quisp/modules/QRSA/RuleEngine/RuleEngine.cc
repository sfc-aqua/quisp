/** \file RuleEngine.cc
 *
 *  \brief RuleEngine
 */
#include "RuleEngine.h"

#include <cassert>
#include <cstddef>
#include <fstream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "QNicStore/QNicStore.h"
#include "RuntimeCallback.h"
#include "messages/QNode_ipc_messages_m.h"
#include "messages/barrier_messages_m.h"
#include "messages/connection_teardown_messages_m.h"
#include "messages/link_allocation_update_messages_m.h"
#include "messages/tomography_messages_m.h"
#include "modules/PhysicalConnection/BSA/types.h"
#include "modules/QRSA/RuleEngine/QubitRecord/IQubitRecord.h"
#include "rules/RuleSet.h"
#include "runtime/RuleSet.h"
#include "runtime/Runtime.h"

namespace quisp::modules {

using namespace std;
using namespace rules;
using namespace messages;
using qnic_store::QNicStore;
using runtime_callback::RuntimeCallback;

RuleEngine::RuleEngine() : provider(utils::ComponentProvider{this}), runtimes(std::make_unique<RuntimeCallback>(this)) {}

RuleEngine::~RuleEngine() {
  for (int i = 0; i < number_of_qnics; i++) cancelAndDelete(emit_photon_timer_map[{QNIC_type::QNIC_E, i}]);
  for (int i = 0; i < number_of_qnics_r; i++) cancelAndDelete(emit_photon_timer_map[{QNIC_type::QNIC_R, i}]);
  for (int i = 0; i < number_of_qnics_rp; i++) cancelAndDelete(emit_photon_timer_map[{QNIC_type::QNIC_RP, i}]);
}

void RuleEngine::initialize() {
  // HardwareMonitor's neighbor table is checked in the initialization stage of the simulation
  // This assumes the topology never changes throughout the simulation.
  // If dynamic change in topology is required, recoding this is needed.
  hardware_monitor = provider.getHardwareMonitor();
  realtime_controller = provider.getRealTimeController();
  routingdaemon = provider.getRoutingDaemon();
  initializeLogger(provider);
  bell_pair_store.logger = logger;

  parentAddress = provider.getNodeAddr();
  qnode_indices = {};

  number_of_qnics_all = par("total_number_of_qnics");
  number_of_qnics = par("number_of_qnics");
  number_of_qnics_r = par("number_of_qnics_r");
  number_of_qnics_rp = par("number_of_qnics_rp");
  if (qnic_store == nullptr) {
    qnic_store = std::make_unique<QNicStore>(provider, number_of_qnics, number_of_qnics_r, number_of_qnics_rp, logger);
  }
  for (int i = 0; i < number_of_qnics; i++) {
    emit_photon_timer_map[{QNIC_type::QNIC_E, i}] = new EmitPhotonRequest();
    emit_photon_timer_map[{QNIC_type::QNIC_E, i}]->setQnicType(QNIC_type::QNIC_E);
    emit_photon_timer_map[{QNIC_type::QNIC_E, i}]->setQnicIndex(i);
  }
  for (int i = 0; i < number_of_qnics_r; i++) {
    emit_photon_timer_map[{QNIC_type::QNIC_R, i}] = new EmitPhotonRequest();
    emit_photon_timer_map[{QNIC_type::QNIC_R, i}]->setQnicType(QNIC_type::QNIC_R);
    emit_photon_timer_map[{QNIC_type::QNIC_R, i}]->setQnicIndex(i);
  }
  for (int i = 0; i < number_of_qnics_rp; i++) {
    emit_photon_timer_map[{QNIC_type::QNIC_RP, i}] = new EmitPhotonRequest();
    emit_photon_timer_map[{QNIC_type::QNIC_RP, i}]->setQnicType(QNIC_type::QNIC_RP);
    emit_photon_timer_map[{QNIC_type::QNIC_RP, i}]->setQnicIndex(i);
  }
}

void RuleEngine::handleMessage(cMessage *msg) {
  logger->logPacket("handleRuleEngineMessage", msg);

  // executeAllRuleSets();  // New resource added to QNIC with qnic_type qnic_index.

  if (auto *notification_packet = dynamic_cast<BSMTimingNotification *>(msg)) {
    if (auto *bsa_results = dynamic_cast<CombinedBSAresults *>(msg)) {
      handleLinkGenerationResult(bsa_results);
    }
    auto type = notification_packet->getQnicType();
    auto qnic_index = notification_packet->getQnicIndex();
    stopOnGoingPhotonEmission(type, qnic_index);
    freeFailedEntanglementAttemptQubits(type, qnic_index);
    schedulePhotonEmission(type, qnic_index, notification_packet);
  } else if (auto *pk = dynamic_cast<EmitPhotonRequest *>(msg)) {
    auto type = pk->getQnicType();
    auto qnic_index = pk->getQnicIndex();
    auto number_of_free_emitters = qnic_store->countNumFreeQubits(type, qnic_index);
    auto is_first = pk->isFirst();
    auto is_last = (number_of_free_emitters == 1);
    auto qubit_index = qnic_store->takeFreeQubitIndex(type, qnic_index);

    if (number_of_free_emitters == 0) return;

    // need to set is_first to false
    pk->setFirst(false);
    sendEmitPhotonSignalToQnic(type, qnic_index, qubit_index, is_first, is_last);
    if (!is_last) {
      scheduleAt(simTime() + pk->getIntervalBetweenPhotons(), pk);
    }
    // early return since this doesn't affect entangled resource
    // and we don't want to delete these messages
    return;
  } else if (auto *pk = dynamic_cast<LinkTomographyRuleSet *>(msg)) {
    auto *ruleset = pk->getRuleSet();
    runtimes.acceptRuleSet(ruleset->construct());
    std::cout << "Link Tomography: " << ruleset.id << std::endl;
  } else if (auto *pkt = dynamic_cast<PurificationResult *>(msg)) {
    handlePurificationResult(pkt);
  } else if (auto *pkt = dynamic_cast<SwappingResult *>(msg)) {
    handleSwappingResult(pkt);
  } else if (auto *pkt = dynamic_cast<InternalRuleSetForwarding *>(msg)) {
    // add actual process
    auto serialized_ruleset = pkt->getRuleSet();
    RuleSet ruleset(0, 0);
    ruleset.deserialize_json(serialized_ruleset);
    runtimes.acceptRuleSet(ruleset.construct());
  } else if (auto *pkt = dynamic_cast<InternalRuleSetForwarding_Application *>(msg)) {
    if (pkt->getApplication_type() != 0) error("This application is not recognized yet");
    auto serialized_ruleset = pkt->getRuleSet();
    RuleSet ruleset(0, 0);
    ruleset.deserialize_json(serialized_ruleset);
    runtimes.acceptRuleSet(ruleset.construct());
  } else if (auto *pkt = dynamic_cast<InternalNodeAddressesAlongPathForwarding *>(msg)) {
    auto ruleset_id = pkt->getRuleSet_id();
    for (auto index = 0; index < pkt->getNode_addresses_along_pathArraySize(); index++) {
      ruleset_id_node_addresses_along_path_map[ruleset_id].push_back(pkt->getNode_addresses_along_path(index));
    }
  } else if (auto *pkt = dynamic_cast<InternalNeighborAddressesMessage *>(msg)) {
    sendLinkAllocationUpdateMessageForConnectionSetup(pkt);
  } else if (auto *pkt = dynamic_cast<InternalConnectionTeardownMessage *>(msg)) {
    handleConnectionTeardownMessage(pkt);
  } else if (auto *pkt = dynamic_cast<LinkAllocationUpdateMessage *>(msg)) {
    auto is_sender = pkt->getIs_sender();
    if (is_sender) {
      respondToLinkAllocationUpdateMessage(pkt);
    }
  }
  for (int i = 0; i < number_of_qnics; i++) {
    ResourceAllocation(QNIC_E, i);
  }
  for (int i = 0; i < number_of_qnics_r; i++) {
    ResourceAllocation(QNIC_R, i);
  }
  for (int i = 0; i < number_of_qnics_rp; i++) {
    ResourceAllocation(QNIC_RP, i);
  }

  // executeAllRuleSets();
  delete msg;
}

void RuleEngine::schedulePhotonEmission(QNIC_type type, int qnic_index, BSMTimingNotification *notification) {
  auto first_photon_emit_time = getEmitTimeFromBSMNotification(notification);
  auto *timer = emit_photon_timer_map[{type, qnic_index}];
  timer->setFirst(true);
  timer->setIntervalBetweenPhotons(notification->getInterval());
  scheduleAt(first_photon_emit_time, timer);
}

void RuleEngine::sendEmitPhotonSignalToQnic(QNIC_type qnic_type, int qnic_index, int qubit_index, bool is_first, bool is_last) {
  int pulse = 0;
  if (is_first) pulse |= STATIONARYQUBIT_PULSE_BEGIN;
  if (is_last) pulse |= STATIONARYQUBIT_PULSE_END;
  realtime_controller->EmitPhoton(qnic_index, qubit_index, qnic_type, pulse);
  emitted_photon_order_map[{qnic_type, qnic_index}].push_back(qubit_index);
}

simtime_t RuleEngine::getEmitTimeFromBSMNotification(quisp::messages::BSMTimingNotification *notification) { return notification->getFirstPhotonEmitTime(); }

void RuleEngine::stopOnGoingPhotonEmission(QNIC_type type, int qnic_index) { cancelEvent(emit_photon_timer_map[{type, qnic_index}]); }

void RuleEngine::freeFailedEntanglementAttemptQubits(QNIC_type type, int qnic_index) {
  auto &emitted_indices = emitted_photon_order_map[{type, qnic_index}];
  for (auto qubit_index : emitted_indices) {
    realtime_controller->ReInitialize_StationaryQubit(qnic_index, qubit_index, type, false);
    qnic_store->setQubitBusy(type, qnic_index, qubit_index, false);
  }
  emitted_indices.clear();
}

void RuleEngine::handleLinkGenerationResult(CombinedBSAresults *bsa_result) {
  auto type = bsa_result->getQnicType();
  auto qnic_index = bsa_result->getQnicIndex();
  auto num_success = bsa_result->getSuccessCount();
  auto partner_address = bsa_result->getNeighborAddress();
  auto &emitted_indices = emitted_photon_order_map[{type, qnic_index}];
  for (int i = num_success - 1; i >= 0; i--) {
    auto emitted_index = bsa_result->getSuccessfulPhotonIndices(i);
    auto qubit_index = emitted_indices[emitted_index];
    auto *qubit_record = qnic_store->getQubitRecord(type, qnic_index, qubit_index);
    auto iterator = emitted_indices.begin();
    std::advance(iterator, emitted_index);
    bell_pair_store.insertEntangledQubit(partner_address, qubit_record);
    emitted_indices.erase(iterator);

    auto correction_operation = bsa_result->getCorrectionOperationList(i);
    if (correction_operation == PauliOperator::X) {
      realtime_controller->applyXGate(qubit_record);
    } else if (correction_operation == PauliOperator::Y) {
      realtime_controller->applyXGate(qubit_record);
      realtime_controller->applyZGate(qubit_record);
    }
  }
}

void RuleEngine::handlePurificationResult(PurificationResult *result) {
  auto ruleset_id = result->getRulesetId();
  auto shared_rule_tag = result->getSharedRuleTag();
  auto sequence_number = result->getSequenceNumber();
  auto measurement_result = result->getMeasurementResult();
  auto purification_protocol = result->getProtocol();
  std::vector<int> message_content = {sequence_number, measurement_result, purification_protocol};
  auto runtime = runtimes.findById(ruleset_id);
  if (runtime == runtimes.end()) return;
  runtime->assignMessageToRuleSet(shared_rule_tag, message_content);
}

void RuleEngine::handleSwappingResult(SwappingResult *result) {
  auto ruleset_id = result->getRulesetId();
  auto shared_rule_tag = result->getSharedRuleTag();
  auto sequence_number = result->getSequenceNumber();
  auto correction_frame = result->getCorrectionFrame();
  auto new_partner_addr = result->getNewPartner();
  std::vector<int> message_content = {sequence_number, correction_frame, new_partner_addr};
  auto runtime = runtimes.findById(ruleset_id);
  if (runtime == runtimes.end()) return;
  runtime->assignMessageToRuleSet(shared_rule_tag, message_content);
}

void RuleEngine::handleConnectionTeardownMessage(InternalConnectionTeardownMessage *msg) {
  addAllocatedQNICs(msg);
  stopRuleSetExecution(msg);
}

void RuleEngine::addAllocatedQNICs(InternalConnectionTeardownMessage *msg) {
  auto ruleset_id = msg->getRuleSet_id();
  auto num_of_qnics = msg->getStack_of_QNICAddressesArraySize();
  for (auto index = 0; index < num_of_qnics; index++) {
    ruleset_id_qnic_addresses_map[ruleset_id].push_back(msg->getStack_of_QNICAddresses(index));
  }
}

void RuleEngine::stopRuleSetExecution(InternalConnectionTeardownMessage *msg) {
  auto ruleset_id = msg->getRuleSet_id();
  runtimes.stopById(ruleset_id);
}

void RuleEngine::sendConnectionTeardownMessageForRuleSet(unsigned long ruleset_id) {
  auto node_addresses_along_path = (std::vector<int>)ruleset_id_node_addresses_along_path_map[ruleset_id];
  for (int index = 0; index < node_addresses_along_path.size(); index++) {
    auto pkt = new ConnectionTeardownMessage();
    pkt->setSrcAddr(parentAddress);
    pkt->setDestAddr(node_addresses_along_path.at(index));
    pkt->setActual_srcAddr(parentAddress);
    pkt->setActual_destAddr(node_addresses_along_path.at(index));
    if (index == 0) {
      pkt->setLAU_destAddr_left(-1);
    } else {
      pkt->setLAU_destAddr_left(node_addresses_along_path.at(index - 1));
    }
    if (index == node_addresses_along_path.size() - 1) {
      pkt->setLAU_destAddr_right(-1);
    } else {
      pkt->setLAU_destAddr_right(node_addresses_along_path.at(index + 1));
    }
    pkt->setRuleSet_id(ruleset_id);
    send(pkt, "RouterPort$o");
  }
}

void RuleEngine::sendBarrierMessageAck(BarrierMessage *msg) {
  BarrierMessage *pkt = new BarrierMessage("BarrierMessage");
  pkt->setSrcAddr(msg->getDestAddr());
  pkt->setDestAddr(msg->getSrcAddr());
  pkt->setNegotiatedRuleset_id(msg->getNegotiatedRuleSet_id());
  pkt->setQubitRecord((IQubitRecord *)msg->getQubitRecord());
  pkt->setSequence_number(msg->getSequence_number() + 1);
  pkt->setIs_sender(false);
  send(pkt, "RouterPort$o");
}

void RuleEngine::sendLinkAllocationUpdateMessageForConnectionTeardown(InternalConnectionTeardownMessage *msg) {
  if (msg->getLAU_destAddr_left() != -1) {
    LinkAllocationUpdateMessage *pkt1 = new LinkAllocationUpdateMessage("LinkAllocationUpdateMessage");
    pkt1->setSrcAddr(msg->getDestAddr());
    pkt1->setDestAddr(msg->getLAU_destAddr_left());
    pkt1->setStack_of_ActiveLinkAllocationsArraySize(runtimes.size());
    auto index = 0;
    for (auto it = runtimes.begin(); it < runtimes.end(); ++it) {
      pkt1->setStack_of_ActiveLinkAllocations(index, it->ruleset.id);
      index += 1;
    }
    pkt1->setRandom_number(rand());
    send(pkt1, "RouterPort$o");
  }
  if (msg->getLAU_destAddr_right() != -1) {
    LinkAllocationUpdateMessage *pkt2 = new LinkAllocationUpdateMessage("LinkAllocationUpdateMessage");
    pkt2->setSrcAddr(msg->getDestAddr());
    pkt2->setDestAddr(msg->getLAU_destAddr_left());
    pkt2->setStack_of_ActiveLinkAllocationsArraySize(runtimes.size());
    auto index = 0;
    for (auto it = runtimes.begin(); it < runtimes.end(); ++it) {
      pkt2->setStack_of_ActiveLinkAllocations(index, it->ruleset.id);
      index += 1;
    }
    pkt2->setRandom_number(rand());
    send(pkt2, "RouterPort$o");
  }
}

void RuleEngine::respondToLinkAllocationUpdateMessage(LinkAllocationUpdateMessage *msg) {
  LinkAllocationUpdateMessage *pkt = new LinkAllocationUpdateMessage("LinkAllocationUpdateMessage");
  pkt->setSrcAddr(msg->getDestAddr());
  pkt->setDestAddr(msg->getSrcAddr());
  pkt->setIs_sender(false);
  pkt->setStack_of_ActiveLinkAllocationsArraySize(runtimes.size());
  auto index = 0;
  for (auto it = runtimes.begin(); it < runtimes.end(); ++it) {
    pkt->setStack_of_ActiveLinkAllocations(index, it->ruleset.id);
    index += 1;
  }
  pkt->setRandom_number(rand());
  send(pkt, "RouterPort$o");
}

void RuleEngine::sendLinkAllocationUpdateMessageForConnectionSetup(InternalNeighborAddressesMessage *msg) {
  std::vector<int> neighbor_addresses;
  auto num_neighbors = msg->getStack_of_NeighboringQNodeIndicesArraySize();
  for (auto i = 0; i < num_neighbors; i++) {
    neighbor_addresses.push_back(msg->getStack_of_NeighboringQNodeIndices(i));
  }

  auto ruleset_id = msg->getRuleSet_id();
  std::vector<unsigned long long> active_link_allocations;
  for (auto it = runtimes.begin(); it != runtimes.end(); ++it) {
    active_link_allocations.push_back(it->ruleset.id);
  }

  for (auto neighbor_address : neighbor_addresses) {
    LinkAllocationUpdateMessage *pkt = new LinkAllocationUpdateMessage("LinkAllocationUpdateMessage");
    pkt->setSrcAddr(parentAddress);
    pkt->setDestAddr(neighbor_address);
    pkt->setIs_sender(true);
    pkt->setStack_of_ActiveLinkAllocationsArraySize(neighbor_addresses.size());
    for (auto i = 0; i < neighbor_addresses.size(); i++) {
      pkt->setStack_of_ActiveLinkAllocations(i, neighbor_addresses.at(i));
    }
    pkt->setRandom_number(rand());
    send(pkt, "RouterPort$o");
  }
}

// Invoked whenever a new resource (entangled with neighbor) has been created.
// Allocates those resources to a particular ruleset, from top to bottom (all of it).
void RuleEngine::ResourceAllocation(int qnic_type, int qnic_index) {
  for (auto &runtime : runtimes) {
    auto &partners = runtime.partners;
    for (auto &partner_addr : partners) {
      auto range = bell_pair_store.getBellPairsRange((QNIC_type)qnic_type, qnic_index, partner_addr.val);
      for (auto it = range.first; it != range.second; ++it) {
        auto qubit_record = it->second;

        // 3. if the qubit is not allocated yet, and the qubit has not been allocated to this rule,
        // if the qubit has already been assigned to the rule, the qubit is not allocatable to that rule
        if (!qubit_record->isAllocated()) {  //&& !qubit_record->isRuleApplied((*rule)->rule_id
          qubit_record->setAllocated(true);
          runtime.assignQubitToRuleSet(partner_addr, qubit_record);
        }
      }
    }
  }
}

// Invoked whenever a new resource (entangled with neighbor) has been created.
// Allocates those resources to a particular ruleset, from top to bottom (all of it).
void RuleEngine::AllocateResourceToRuleSet(int qnic_type, int qnic_index, unsigned long ruleset_id) {
  auto runtime = runtimes.findById(ruleset_id);
  auto &partners = runtime->partners;
  for (auto &partner_addr : partners) {
    auto range = bell_pair_store.getBellPairsRange((QNIC_type)qnic_type, qnic_index, partner_addr.val);
    for (auto it = range.first; it != range.second; ++it) {
      auto qubit_record = it->second;

      // 3. if the qubit is not allocated yet, and the qubit has not been allocated to this rule,
      // if the qubit has already been assigned to the rule, the qubit is not allocatable to that rule
      if (!qubit_record->isAllocated()) {  //&& !qubit_record->isRuleApplied((*rule)->rule_id
        qubit_record->setAllocated(true);
        runtime->assignQubitToRuleSet(partner_addr, qubit_record);
      }
    }
  }
}

// Invoked whenever existing resource (entangled with neighbor) need to be released.
// Get those resources from a particular ruleset, from top to bottom (all of it).
std::vector<IQubitRecord *> RuleEngine::getAllocatedResourceToRuleSet(int qnic_type, int qnic_index, unsigned long ruleset_id) {
  auto runtime = runtimes.findById(ruleset_id);
  auto &partners = runtime->partners;

  std::vector<IQubitRecord *> qubit_record_list;
  for (auto &partner_addr : partners) {
    auto range = bell_pair_store.getBellPairsRange((QNIC_type)qnic_type, qnic_index, partner_addr.val);
    for (auto it = range.first; it != range.second; ++it) {
      auto qubit_record = it->second;
      if (qubit_record->isAllocated()) {  //&& !qubit_record->isRuleApplied((*rule)->rule_id
        qubit_record_list.push_back(qubit_record);
      }
    }
  }
  return qubit_record_list;
}

// Invoked whenever existing resource (entangled with neighbor) need to be released.
// Frees those resources from a particular ruleset, from top to bottom (all of it).
void RuleEngine::freeResourceFromRuleSet(int qnic_type, int qnic_index, unsigned long ruleset_id) {
  auto partners = runtimes.findPartnersById(ruleset_id);
  for (auto &partner_addr : partners) {
    auto range = bell_pair_store.getBellPairsRange((QNIC_type)qnic_type, qnic_index, partner_addr.val);
    for (auto it = range.first; it != range.second; ++it) {
      auto qubit_record = it->second;

      // 3. if the qubit is allocated, and the qubit need to be released from this rule,
      // if the qubit is not assigned to the rule, the qubit is not releasable from that rule
      if (qubit_record->isAllocated()) {  //&& !qubit_record->isRuleApplied((*rule)->rule_id
        qubit_record->setAllocated(false);
        auto terminated_runtime = runtimes.findTerminatedRuntimeById(ruleset_id);
        terminated_runtime->freeQubitFromRuleSet(partner_addr, qubit_record);
      }
    }
  }
}

void RuleEngine::executeAllRuleSets() {
  auto terminated_ruleset_iterator_list = runtimes.exec();
  for (auto terminated_ruleset : terminated_ruleset_iterator_list) {
    sendConnectionTeardownMessageForRuleSet(terminated_ruleset.id);
  }
}

void RuleEngine::freeConsumedResource(int qnic_index /*Not the address!!!*/, IStationaryQubit *qubit, QNIC_type qnic_type) {
  auto *qubit_record = qnic_store->getQubitRecord(qnic_type, qnic_index, qubit->par("stationary_qubit_address"));
  realtime_controller->ReInitialize_StationaryQubit(qubit_record, false);
  qubit_record->setBusy(false);
  if (qubit_record->isAllocated()) {
    qubit_record->setAllocated(false);
  }
  bell_pair_store.eraseQubit(qubit_record);
}

void RuleEngine::reallocateResource(int qnic_type, int qnic_index, unsigned long current_ruleset_id, unsigned long next_ruleset_id) {
  auto current_runtime = runtimes.findById(current_ruleset_id);
  auto next_runtime = runtimes.findById(next_ruleset_id);
  auto &partners = current_runtime->partners;

  for (auto &partner_addr : partners) {
    auto range = bell_pair_store.getBellPairsRange((QNIC_type)qnic_type, qnic_index, partner_addr.val);
    for (auto it = range.first; it != range.second; ++it) {
      auto qubit_record = it->second;

      // 3. if the qubit is allocated, and the qubit need to be released from this rule,
      // if the qubit is not assigned to the rule, the qubit is not releasable from that rule
      if (qubit_record->isAllocated()) {  //&& !qubit_record->isRuleApplied((*rule)->rule_id
        current_runtime->freeQubitFromRuleSet(partner_addr, qubit_record);
        next_runtime->assignQubitToRuleSet(partner_addr, qubit_record);
      }
    }
  }
}

}  // namespace quisp::modules

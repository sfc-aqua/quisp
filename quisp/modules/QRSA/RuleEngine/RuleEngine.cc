/** \file RuleEngine.cc
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/04/04
 *
 *  \brief RuleEngine
 */

#include <cassert>
#include <fstream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <utility>

#include <messages/classical_messages.h>
#include "QNicStore/QNicStore.h"
#include "RuleEngine.h"
#include "RuntimeCallback.h"
#include "messages/QNode_ipc_messages_m.h"
#include "messages/link_generation_messages_m.h"
#include "modules/PhysicalConnection/BSA/types.h"
#include "modules/QNIC.h"

namespace quisp::modules {

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

  parentAddress = par("address");
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
    emit_photon_timer_map[{QNIC_type::QNIC_E, i}]->setQniceIndex(i);
  }
  for (int i = 0; i < number_of_qnics_r; i++) {
    emit_photon_timer_map[{QNIC_type::QNIC_R, i}] = new EmitPhotonRequest();
    emit_photon_timer_map[{QNIC_type::QNIC_R, i}]->setQnicType(QNIC_type::QNIC_R);
    emit_photon_timer_map[{QNIC_type::QNIC_R, i}]->setQniceIndex(i);
  }
  for (int i = 0; i < number_of_qnics_rp; i++) {
    emit_photon_timer_map[{QNIC_type::QNIC_RP, i}] = new EmitPhotonRequest();
    emit_photon_timer_map[{QNIC_type::QNIC_RP, i}]->setQnicType(QNIC_type::QNIC_RP);
    emit_photon_timer_map[{QNIC_type::QNIC_RP, i}]->setQniceIndex(i);
  }
}

void RuleEngine::handleMessage(cMessage *msg) {
  executeAllRuleSets();  // New resource added to QNIC with qnic_type qnic_index.

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
    /** pseudocode
     * emit the request photons if possible.
     * set first and last appropriately.
     * if this is the last free photon set last
     * schedule this message again with interval
     */
    auto type = pk->getQnicType();
    auto qnic_index = pk->getQnicIndex();
    auto is_first = pk->isFirst();
    auto is_last = (qnic_store->countNumFreeQubits(type, qnic_index) == 1);
    auto qubit_index = qnic_store->takeFreeQubitIndex(type, qnic_index);

    // need to set is_first to false;
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
  } else if (auto *pkt = dynamic_cast<PurificationResult *>(msg)) {
    bool from_self = pkt->getSrcAddr() == parentAddress;
    const PurificationResultKey key{*pkt};
    handlePurificationResult(key, PurificationResultData{*pkt}, from_self);
  } else if (auto *pkt = dynamic_cast<SwappingResult *>(msg)) {
    const SwappingResultData data{
        .ruleset_id = pkt->getRuleSet_id(),
        .shared_tag = pkt->getShared_tag(),
        .new_partner_addr = pkt->getNew_partner(),
        .operation_type = pkt->getOperation_type(),
        .qubit_index = pkt->getMeasured_qubit_index()  // qubit index for this node, the name is misleading
    };
    handleSwappingResult(data);
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

  executeAllRuleSets();
  delete msg;
}

void RuleEngine::schedulePhotonEmission(QNIC_type type, int qnic_index, BSMTimingNotification *notification) {
  auto first_photon_emit_time = getEmitTimeFromArrivalTime(notification);
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

simtime_t RuleEngine::getEmitTimeFromArrivalTime(quisp::messages::BSMTimingNotification *) { return 0; }

void RuleEngine::stopOnGoingPhotonEmission(QNIC_type type, int qnic_index) { cancelEvent(emit_photon_timer_map[{type, qnic_index}]); }

void RuleEngine::freeFailedEntanglementAttemptQubits(QNIC_type type, int qnic_index) {
  auto &emitted_indices = emitted_photon_order_map[{type, qnic_index}];
  for (auto qubit_index : emitted_indices) {
    realtime_controller->ReInitialize_StationaryQubit(qnic_index, qubit_index, type, false);
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
    auto qubit_index = bsa_result->getSuccessfulPhotonIndices(i);
    auto *qubit_record = qnic_store->getQubitRecord(type, qnic_index, qubit_index);
    auto iterator = emitted_indices.begin();
    std::advance(iterator, qubit_index);
    // TODO: revamp is_busy
    qnic_store->setQubitBusy(type, qnic_index, qubit_index, false);
    bell_pair_store.insertEntangledQubit(partner_address, qubit_record);
    emitted_indices.erase(iterator);

    auto correction_operation = bsa_result->getCorrectionOperationList(i);
    if (correction_operation == PauliOperator::X) {
      realtime_controller->applyXGate(qubit_record);
    } else if (correction_operation == PauliOperator::Y) {
      // TODO: Y gate?
      realtime_controller->applyXGate(qubit_record);
      realtime_controller->applyZGate(qubit_record);
    }
  }
}

void RuleEngine::handlePurificationResult(const PurificationResultKey &key, const PurificationResultData &result, bool from_self) {
  auto it = purification_result_table.find(key);
  if (it == purification_result_table.end()) {
    purification_result_table.insert({key, result});
    return;
  }
  // rule_id might be different from other node's rule, so use rule id comes from our runtime
  auto rule_id = from_self ? key.rule_id : it->first.rule_id;

  auto *runtime = runtimes.findById(key.rs_id);
  if (runtime == nullptr) {
    purification_result_table.erase(it);
    return;
  }

  auto qubit_key = runtime->findQubit(rule_id, key.shared_tag, key.action_index);

  auto *qubit = provider.getStationaryQubit(qubit_key->second);
  qubit->Unlock();

  if (result.isResultMatched(it->second, key.type)) {
    runtime->promoteQubit(qubit_key);
  } else {
    runtime->qubits.erase(qubit_key);
    freeConsumedResource(qubit->qnic_index, qubit, (QNIC_type)qubit->qnic_type);
  }
  purification_result_table.erase(it);
}

InterfaceInfo RuleEngine::getInterface_toNeighbor(int destAddr) {
  InterfaceInfo inf;
  auto it = ntable.find(destAddr);

  // Neighbor not found! This should not happen unless you simulate broken links in real time.
  if (it == ntable.end())
    error("Interface to neighbor not found in neighbor table prepared by the Hardware Manager.... This should probably not happen now.");
  else
    inf = (*it).second;  // store gate index connected to the destination (BSA) node by refering to the neighbor table.
  return inf;
}

InterfaceInfo RuleEngine::getInterface_toNeighbor_Internal(int local_qnic_address) {
  InterfaceInfo inf;
  for (auto i = ntable.begin(); i != ntable.end(); i++) {
    // Neighbor not found! This should not happen unless you simulate broken links in real time.
    if (i == ntable.end()) error("Interface to neighbor not found in neighbor table prepared by the Hardware Manager.... This should probably not happen now.");

    if (i->second.qnic.address == local_qnic_address) inf = (*i).second;
  }
  return inf;
}

void RuleEngine::handleSwappingResult(const SwappingResultData &data) {
  auto qnic_addr = routingdaemon->return_QNIC_address_to_destAddr(data.new_partner_addr);
  auto conn_info = hardware_monitor->findConnectionInfoByQnicAddr(qnic_addr);
  if (conn_info == nullptr) error("qnic(addr: %d) info not found", qnic_addr);
  auto qnic_type = conn_info->qnic.type;
  auto qnic_index = conn_info->qnic.index;
  auto qubit_index = data.qubit_index;

  auto *qubit_record = qnic_store->getQubitRecord(qnic_type, qnic_index, qubit_index);
  switch (data.operation_type) {
    case 0:  // do nothing
      break;
    case 1:
      realtime_controller->applyXGate(qubit_record);
      break;
    case 2:
      realtime_controller->applyZGate(qubit_record);
      break;
    default:
      error("Something went wrong. This operation type: %d isn't recorded!", data.operation_type);
  }

  auto *runtime = runtimes.findById(data.ruleset_id);
  bell_pair_store.eraseQubit(qubit_record);
  bell_pair_store.insertEntangledQubit(data.new_partner_addr, qubit_record);
  runtime->promoteQubitWithNewPartner(qubit_record, data.new_partner_addr);
}

void RuleEngine::freeResource(int qnic_index /*The actual index. Not address. This with qnic_type makes the id unique.*/, int qubit_index, QNIC_type qnic_type) {
  auto *qubit_record = qnic_store->getQubitRecord(qnic_type, qnic_index, qubit_index);
  realtime_controller->ReInitialize_StationaryQubit(qubit_record, false);
  qubit_record->setBusy(false);
  if (qubit_record->isAllocated()) qubit_record->setAllocated(false);
}

double RuleEngine::predictResourceFidelity(QNIC_type qnic_type, int qnic_index, int entangled_node_address, int resource_index) { return uniform(.6, .9); }

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
          // qubit_record->markRuleApplied((*rule)->rule_id);
          runtime.assignQubitToRuleSet(partner_addr, qubit_record);
        }
      }
    }
  }
}

void RuleEngine::executeAllRuleSets() { runtimes.exec(); }

void RuleEngine::freeConsumedResource(int qnic_index /*Not the address!!!*/, IStationaryQubit *qubit, QNIC_type qnic_type) {
  auto *qubit_record = qnic_store->getQubitRecord(qnic_type, qnic_index, qubit->par("stationary_qubit_address"));
  realtime_controller->ReInitialize_StationaryQubit(qubit_record, false);
  qubit_record->setBusy(false);
  if (qubit_record->isAllocated()) {
    qubit_record->setAllocated(false);
  }
  qubit_record->clearAppliedRules();
  bell_pair_store.eraseQubit(qubit_record);
}

}  // namespace quisp::modules

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

#include <utils/ComponentProvider.h>
#include "QNicStore/QNicStore.h"
#include "RuleEngine.h"
#include "RuleSetConverter/RuleSetConverter.h"
#include "RuntimeCallback.h"
#include "modules/QNIC/StationaryQubit/IStationaryQubit.h"
#include "runtime/RuleSet.h"
#include "runtime/Runtime.h"
#include "runtime/types.h"

namespace quisp::modules {

using namespace rules;
using namespace rules::active;
using qnic_store::QNicStore;
using rs_converter::RuleSetConverter;
using runtime_callback::RuntimeCallback;

RuleEngine::RuleEngine() : provider(utils::ComponentProvider{this}) {}

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

  terminated_qnic = new bool[number_of_qnics_all];
  // if there are 2 qnics, 1 qnic_r, and 2 qnic_rp,
  // then trial_index[0~1] is assigned for qnics, trial_index[2~2] for qnic_r and trial_index[3~4] for qnic_rp....
  qnic_burst_trial_counter = new int[number_of_qnics_all];

  for (int i = 0; i < number_of_qnics_all; i++) {
    qnic_burst_trial_counter[i] = 0;
    terminated_qnic[i] = false;
  }

  // Tracks which qubit was sent first, second and so on per qnic(r,rp)
  tracker = new sentQubitIndexTracker[number_of_qnics_all];
  for (int qnic_address = 0; qnic_address < number_of_qnics_all; qnic_address++) {
    tracker_accessible.push_back(true);
  }
  WATCH_VECTOR(tracker_accessible);

  runtime_callback = std::make_unique<RuntimeCallback>(this);
}

void RuleEngine::handleMessage(cMessage *msg) {
  traverseThroughAllProcesses2();  // New resource added to QNIC with qnic_type qnic_index.

  if (auto *pk = dynamic_cast<EmitPhotonRequest *>(msg)) {  // From self.
    // Index the qnic and qubit index to the tracker.
    int qnic_address = pk->getQnic_address();
    // Terminate emission if trial is over already (e.g. the neighbor ran out of free qubits and the BSA already returned the results)
    if (burstTrial_outdated(pk->getTrial(), qnic_address)) {
      // Terminate bursting if this trial has finished already.
      delete msg;
      return;
    } else {
      QubitAddr_cons Addr(parentAddress, pk->getQnic_index(), pk->getQubit_index());
      int nth_shot = tracker[qnic_address].size();
      // qubit with address Addr was shot in nth time. This list is ordered from old to new.
      tracker[qnic_address].insert(std::make_pair(nth_shot, Addr));
    }

    realtime_controller->EmitPhoton(pk->getQnic_index(), pk->getQubit_index(), (QNIC_type)pk->getQnic_type(), pk->getKind());
  }

  else if (auto *pk_result = dynamic_cast<CombinedBSAresults *>(msg)) {
    // First, keep all the qubits that were successfully entangled, and reinitialize the failed ones.
    BSMtimingNotifier *pk = check_and_cast<BSMtimingNotifier *>(msg);
    bubble("trial over is set to true");
    // Set qubits free according to results
    // Also needs to send which qubit was which to the neighbor (not BSA but the neighboring QNode). To update the QubitState table's entangled address.
    incrementBurstTrial(pk->getSrcAddr(), pk->getInternal_qnic_address(), pk->getInternal_qnic_index());
    // successfully entangled qubits as resources.
    freeFailedQubits_and_AddAsResource(pk->getSrcAddr(), pk->getInternal_qnic_address(), pk->getInternal_qnic_index(), pk_result);
    // Clear tracker every end of burst trial. This keeps which qubit was fired first, second, third and so on only for that trial.
    clearTrackerTable(pk->getSrcAddr(), pk->getInternal_qnic_address());

    // Second, schedule the next burst by referring to the received timing information.
    int qnic_address;
    if (pk->getInternal_qnic_address() == -1) {  // destination hom is outside this node.
      InterfaceInfo inf = getInterface_toNeighbor(pk->getSrcAddr());
      qnic_address = inf.qnic.address;
      // neighborQNodeAddress = inf.neighborQNode_address;
    } else {  // destination hom is in the qnic in this node. This gets invoked when the request from internal hom is send from the same node.
      qnic_address = pk->getInternal_qnic_address();
    }

    if (terminated_qnic[qnic_address]) {
      // std::cout<<"NOT ANY MORE qnic["<<qnic_address<<"] in node["<<parentAddress<<"]";
      // error("qnic should not be terminated here, Node: %d, qnic_address: %d", parentAddress, qnic_address);
      delete msg;
      return;
    } else if (pk->getInternal_qnic_index() == -1) {  // Schedule next burst. MIM, or the other node without internal HOM of MM
      EV_DEBUG << "This BSA request is non-internal\n";
      scheduleFirstPhotonEmission(pk, QNIC_E);
    } else {
      EV_DEBUG << "This BSA request is internal\n";
      scheduleFirstPhotonEmission(pk, QNIC_R);
    }
  }

  else if (auto *pk = dynamic_cast<SchedulePhotonTransmissionsOnebyOne *>(msg)) {
    EV_DEBUG << provider.getQNode()->getFullName() << ": Photon shooting is from qnic[" << pk->getQnic_index() << "] with address=" << pk->getQnic_address() << "\n";
    // Terminate emission if trial is over already (the neighbor ran out of free qubits)
    if (burstTrial_outdated(pk->getTrial(), pk->getQnic_address())) {
      delete msg;
      return;
    }
    if (pk->getInternal_hom() == 0) {  // for MIM
      shootPhoton(pk);
    } else {  // for MM
      shootPhoton_internal(pk);
    }
  }

  // Bell pair generation timing syncronization from HOM
  else if (dynamic_cast<BSMtimingNotifier *>(msg) != nullptr && dynamic_cast<CombinedBSAresults *>(msg) == nullptr) {
    bubble("timing received");
    EV << "BSM timing notifier received\n";
    BSMtimingNotifier *pk = check_and_cast<BSMtimingNotifier *>(msg);
    if (pk->getInternal_qnic_index() == -1) {  // MIM, or the other node without internnal HOM of MM
      EV_DEBUG << "This BSA request is non-internal\n";
      scheduleFirstPhotonEmission(pk, QNIC_E);
    } else {
      EV_DEBUG << "This BSA request is internal\n";
      scheduleFirstPhotonEmission(pk, QNIC_R);
    }
  } else if (dynamic_cast<EPPStimingNotifier *>(msg)) {
    bubble("EPPS");
    error("EPPS is not implemented yet");
  }

  else if (auto *pk = dynamic_cast<LinkTomographyRuleSet *>(msg)) {
    // Received a tomography rule set.
    // std::cout<<"node["<<parentAddress<<"] !!!!!!!!!!Ruleset reveid!!!!!!!!! ruleset id = "<<pk->getRuleSet()->ruleset_id<<"\n";
    auto *ruleset = const_cast<ActiveRuleSet *>(pk->getActiveRuleSet());
    // int process_id = rp.size();  // This is temporary because it will not be unique when processes have been deleted.
    std::cout << "Process size is ...." << ruleset->size() << " node[" << parentAddress << "\n";
    // todo:We also need to allocate resources. e.g. if all qubits were entangled already, and got a new ruleset.
    // ResourceAllocation();
    if (ruleset->size() > 0) {
      rp.insert(ruleset);
      EV << "New process arrived !\n";
    } else {
      error("Empty rule set...");
    }
  } else if (auto *pkt = dynamic_cast<PurificationResult *>(msg)) {
    bool from_self = pkt->getSrcAddr() == parentAddress;
    const PurificationResultKey key{
        .rs_id = pkt->getRuleset_id(),
        .rule_id = pkt->getRule_id(),
        .action_index = pkt->getAction_index(),
        .shared_tag = pkt->getShared_tag(),
        .type = rules::PurType::SINGLE_X  // TODO: read from pkt
    };
    handlePurificationResult(key, PurificationResultData{.is_x_plus = pkt->getOutput_is_plus()}, from_self);
  } else if (auto *pkt = dynamic_cast<DoublePurificationResult *>(msg)) {
    error("DoublePurification is not implemented yet");
    process_id purification_id;
    Doublepurification_result pr;
    purification_id.ruleset_id = pkt->getRuleset_id();
    purification_id.rule_id = pkt->getRule_id();
    purification_id.index = pkt->getAction_index();
    purification_id.shared_tag = pkt->getShared_tag();
    pr.id = purification_id;
    pr.Xpurification_outcome = pkt->getXOutput_is_plus();
    pr.Zpurification_outcome = pkt->getZOutput_is_plus();
    storeCheck_DoublePurification_Agreement(pr);
  } else if (auto *pkt = dynamic_cast<DS_DoublePurificationResult *>(msg)) {
    error("DS DoublePurification is not implemented yet");
    // std::cout<<"!!!!Purification result reveid!!! node["<<parentAddress<<"]\n";
    // std::cout<<"Presult from node["<<pkt->getSrcAddr()<<"]\n";
    process_id purification_id;
    Quatropurification_result pr;
    purification_id.ruleset_id = pkt->getRuleset_id();
    purification_id.rule_id = pkt->getRule_id();
    purification_id.index = pkt->getAction_index();
    purification_id.shared_tag = pkt->getShared_tag();
    pr.id = purification_id;
    pr.Xpurification_outcome = pkt->getXOutput_is_plus();
    pr.Zpurification_outcome = pkt->getZOutput_is_plus();
    pr.DS_Xpurification_outcome = pkt->getDS_XOutput_is_plus();
    pr.DS_Zpurification_outcome = pkt->getDS_ZOutput_is_plus();
    storeCheck_QuatroPurification_Agreement(pr);
  } else if (auto *pkt = dynamic_cast<DS_DoublePurificationSecondResult *>(msg)) {
    error("DS DoublePurification is not implemented yet");
    // std::cout<<"!!!!Purification result reveid!!! node["<<parentAddress<<"]\n";
    process_id purification_id;
    Triplepurification_result pr;
    purification_id.ruleset_id = pkt->getRuleset_id();
    purification_id.rule_id = pkt->getRule_id();
    purification_id.index = pkt->getAction_index();
    purification_id.shared_tag = pkt->getShared_tag();
    pr.id = purification_id;
    pr.Xpurification_outcome = pkt->getXOutput_is_plus();
    pr.Zpurification_outcome = pkt->getZOutput_is_plus();
    pr.DS_purification_outcome = pkt->getDS_Output_is_plus();
    storeCheck_TriplePurification_Agreement(pr);
  } else if (auto *pkt = dynamic_cast<SwappingResult *>(msg)) {
    const SwappingResultData data{
        .ruleset_id = pkt->getRuleSet_id(),
        .shared_tag = pkt->getShared_tag(),
        .new_partner_addr = pkt->getNew_partner(),
        .swapper_addr = pkt->getSrcAddr(),
        .operation_type = pkt->getOperation_type(),
        .qubit_index = pkt->getMeasured_qubit_index()  // qubit index for this node, the name is misleading
    };
    handleSwappingResult(data);
  }

  else if (auto *pkt = dynamic_cast<SimultaneousSwappingResult *>(msg)) {
    // Add messeage to collection [ruleSetid][index_in_path]
    error("Simultaneous Swapping is not implemented yet");
    unsigned long rule_id = pkt->getRuleSet_id();
    simultaneous_es_results[rule_id][pkt->getIndex_in_path()] = pkt->getOperation_type();

    // Check if all message is here or not
    if (simultaneous_es_results[rule_id].size() == pkt->getPath_length_exclude_IR()) {
      // optimize correction operation, without global phase consideration
      std::map<int, int>::iterator it;
      int oco_result = 0;
      for (it = simultaneous_es_results[rule_id].begin(); it != simultaneous_es_results[rule_id].end(); it++) {  // this may wrong due to using of index, not iterator
        oco_result ^= it->second;
      }

      process_id swapping_id;
      swapping_id.ruleset_id = pkt->getRuleSet_id();  // just in case
      swapping_id.rule_id = pkt->getRule_id();
      swapping_id.index = pkt->getAction_index();

      swapping_result swapr;  // result of entanglement swapping
      swapr.id = swapping_id;
      swapr.new_partner = pkt->getNew_partner();
      swapr.new_partner_qnic_index = pkt->getNew_partner_qnic_index();
      swapr.new_partner_qnic_address = pkt->getNew_partner_qnic_address();
      swapr.new_partner_qnic_type = pkt->getNew_partner_qnic_type();
      swapr.measured_qubit_index = pkt->getMeasured_qubit_index();
      swapr.operation_type = oco_result;
      updateResources_SimultaneousEntanglementSwapping(swapr);
    }
  }

  else if (auto *pkt = dynamic_cast<InternalRuleSetForwarding *>(msg)) {
    // add actual process
    auto serialized_ruleset = pkt->getRuleSet();
    RuleSet ruleset(0, 0);
    ruleset.deserialize_json(serialized_ruleset);

    auto rs = RuleSetConverter::construct(ruleset);
    runtimes.emplace_back(runtime::Runtime(rs, runtime_callback.get()));

  } else if (auto *pkt = dynamic_cast<InternalRuleSetForwarding_Application *>(msg)) {
    if (pkt->getApplication_type() != 0) error("This application is not recognized yet");
    auto serialized_ruleset = pkt->getRuleSet();
    RuleSet ruleset(0, 0);
    ruleset.deserialize_json(serialized_ruleset);
    auto rs = RuleSetConverter::construct(ruleset);
    runtimes.emplace_back(runtime::Runtime(rs, runtime_callback.get()));

  } else if (auto *pkt = dynamic_cast<StopEmitting *>(msg)) {
    terminated_qnic[pkt->getQnic_address()] = true;
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

  traverseThroughAllProcesses2();
  delete msg;
}

void RuleEngine::handlePurificationResult(const PurificationResultKey &key, const PurificationResultData &result, bool from_self) {
  auto it = purification_result_table.find(key);
  if (it == purification_result_table.end()) {
    purification_result_table.insert({key, result});
    return;
  }
  // rule_id might be different from other node's rule, so use rule id comes from our runtime
  auto rule_id = from_self ? key.rule_id : it->first.rule_id;

  runtime::Runtime *runtime = nullptr;
  for (auto &rt : runtimes) {
    if (rt.ruleset.id == key.rs_id) {
      runtime = &rt;
      break;
    }
  }
  assert(runtime != nullptr);

  // find qubit
  runtime::Rule *rule;
  for (auto &_rule : runtime->ruleset.rules) {
    if (_rule.id == rule_id && _rule.shared_tag == key.shared_tag) {
      rule = &_rule;
    }
  }
  assert(rule != nullptr);

  IQubitRecord *qubit_rec = nullptr;
  IStationaryQubit *qubit = nullptr;
  runtime::QubitResources::iterator qubit_key;
  for (auto it = runtime->qubits.begin(); it != runtime->qubits.end(); it++) {
    auto &[addr, rule_id] = it->first;
    if (rule_id != rule->id) continue;
    auto *q = provider.getStationaryQubit(it->second);
    if (q->action_index == key.action_index) {
      // found qubit
      qubit = q;
      qubit_rec = it->second;
      qubit_key = it;
      break;
    }
  }

  if (qubit == nullptr) error("cannot found the qubit for purification result");
  assert(qubit_rec != nullptr);
  qubit->Unlock();

  if (result.isResultMatched(it->second, key.type)) {
    runtime->promoteQubit(qubit_key);
  } else {
    runtime->qubits.erase(qubit_key);
    freeConsumedResource(qubit->qnic_index, qubit, (QNIC_type)qubit->qnic_type);
  }
  purification_result_table.erase(it);
}

void RuleEngine::storeCheck_Purification_Agreement(purification_result pur_result) {
  auto ruleset_result = rp.findById(pur_result.id.ruleset_id);
  if (ruleset_result == rp.end()) {
    // Probably process already finished. Delete the table and ignore the result.
    return;
  }

  // 2. Check if there are some records existed.
  // check the purification results that belong to the same connection
  auto range = Purification_table.equal_range(pur_result.id.ruleset_id);
  for (auto it = range.first; it != range.second; it++) {
    if (it->second.id.shared_tag == pur_result.id.shared_tag && it->second.id.index == pur_result.id.index) {
      if (it->second.outcome == pur_result.outcome) {
        // the result is coordinate to the counter part
        Unlock_resource_and_upgrade_stage(pur_result.id.ruleset_id, pur_result.id.rule_id, pur_result.id.shared_tag, pur_result.id.index);
      } else {
        // the result is different. discard the resource
        Unlock_resource_and_discard(pur_result.id.ruleset_id, pur_result.id.rule_id, pur_result.id.shared_tag, pur_result.id.index);
      }
      Purification_table.erase(it);
      return;
    }
  }
  Purification_table.insert(std::make_pair(pur_result.id.ruleset_id, pur_result));
}

void RuleEngine::storeCheck_DoublePurification_Agreement(Doublepurification_result pr) {
  auto ruleset_result = rp.findById(pr.id.ruleset_id);
  if (ruleset_result == rp.end()) {
    // Probably process already finished. Delete the table and ignore the result.
    return;
  }

  // Find all resource in qytpe/qid entangled with partner.
  auto ret = DoublePurification_table.equal_range(pr.id.ruleset_id);
  // If the RuleSet has been deleted already, do not do anything.

  for (auto it = ret.first; it != ret.second; it++) {
    if (it->second.id.shared_tag == pr.id.shared_tag && it->second.id.index == pr.id.index) {
      // std::cout<<"Rule_id="<<pr.id.rule_id<<", index="<<pr.id.index<<"\n";
      // std::cout<<"node["<<parentAddress<<"] Rule found: Discard/Keep purification.\n";
      if ((it->second.Xpurification_outcome == pr.Xpurification_outcome) && (it->second.Zpurification_outcome == pr.Zpurification_outcome)) {
        // Outcomes agreed. Keep the entangled pair.
        // std::cout<<"Unlocking and upgrading!\n";
        Unlock_resource_and_upgrade_stage(pr.id.ruleset_id, pr.id.rule_id, pr.id.shared_tag, pr.id.index);
      } else {
        // Discard
        // std::cout<<"node["<<parentAddress<<"] discaard ";
        // std::cout<<"Unlocking and discarding!\n";
        Unlock_resource_and_discard(pr.id.ruleset_id, pr.id.rule_id, pr.id.shared_tag, pr.id.index);
      }
      DoublePurification_table.erase(it);
      return;
    }
  }
  // New data.
  // std::cout<<"New data arrived. Need to keep the outcome of rulset_id="<<pr.id.ruleset_id<<" Rule_id="<<pr.id.rule_id<<", index="<<pr.id.index<<"\n";
  DoublePurification_table.insert(std::make_pair(pr.id.ruleset_id, pr));  // Otherwise, if data has not been found, store it.
}

void RuleEngine::storeCheck_TriplePurification_Agreement(Triplepurification_result pr) {
  auto ruleset_result = rp.findById(pr.id.ruleset_id);
  if (ruleset_result == rp.end()) {
    // Probably process already finished. Delete the table and ignore the result.
    return;
  }
  auto ret = TriplePurification_table.equal_range(pr.id.ruleset_id);  // Find all resource in qytpe/qid entangled with partner.
  // If the RuleSet has been deleted already, do not do anything.

  for (auto it = ret.first; it != ret.second; it++) {
    if (it->second.id.shared_tag == pr.id.shared_tag && it->second.id.index == pr.id.index) {
      if ((it->second.Xpurification_outcome == pr.Xpurification_outcome) && (it->second.Zpurification_outcome == pr.Zpurification_outcome) &&
          (it->second.DS_purification_outcome == pr.DS_purification_outcome)) {
        // Outcomes agreed. Keep the entangled pair.
        Unlock_resource_and_upgrade_stage(pr.id.ruleset_id, pr.id.rule_id, pr.id.shared_tag, pr.id.index);
      } else {
        // Discard
        Unlock_resource_and_discard(pr.id.ruleset_id, pr.id.rule_id, pr.id.shared_tag, pr.id.index);
      }
      TriplePurification_table.erase(it);
      return;
    }
  }
  // New data.
  TriplePurification_table.insert(std::make_pair(pr.id.ruleset_id, pr));  // Otherwise, if data has not been found, store it.
}

void RuleEngine::storeCheck_QuatroPurification_Agreement(Quatropurification_result pr) {
  auto ruleset_result = rp.findById(pr.id.ruleset_id);
  if (ruleset_result == rp.end()) {
    // Probably process already finished. Delete the table and ignore the result.
    return;
  }
  auto ret = QuatroPurification_table.equal_range(pr.id.ruleset_id);  // Find all resource in qytpe/qid entangled with partner.
  // If the RuleSet has been deleted already, do not do anything.

  for (auto it = ret.first; it != ret.second; it++) {
    if (it->second.id.shared_tag == pr.id.shared_tag && it->second.id.index == pr.id.index) {
      // std::cout<<"Rule_id="<<pr.id.rule_id<<", index="<<pr.id.index<<"\n";
      // std::cout<<"node["<<parentAddress<<"] Rule found: Discard/Keep purification.\n";
      if ((it->second.Xpurification_outcome == pr.Xpurification_outcome) && (it->second.Zpurification_outcome == pr.Zpurification_outcome) &&
          (it->second.DS_Zpurification_outcome == pr.DS_Zpurification_outcome) && (it->second.DS_Xpurification_outcome == pr.DS_Xpurification_outcome)) {
        // Outcomes agreed. Keep the entangled pair.
        Unlock_resource_and_upgrade_stage(pr.id.ruleset_id, pr.id.rule_id, pr.id.shared_tag, pr.id.index);
      } else {
        // Discard
        Unlock_resource_and_discard(pr.id.ruleset_id, pr.id.rule_id, pr.id.shared_tag, pr.id.index);
      }
      QuatroPurification_table.erase(it);
      return;
    }
  }
  // New data.
  // std::cout<<"New data arrived. Need to keep the outcome of rulset_id="<<pr.id.ruleset_id<<" Rule_id="<<pr.id.rule_id<<", index="<<pr.id.index<<"\n";
  QuatroPurification_table.insert(std::make_pair(pr.id.ruleset_id, pr));  // Otherwise, if data has not been found, store it.
}

void RuleEngine::Unlock_resource_and_upgrade_stage(unsigned long ruleset_id, int rule_id, int shared_tag, int index) {
  // There should be better way
  // 0. this resorce update only update just one entanglement
  int partner_address;
  IStationaryQubit *qubit;
  if (rp.size() == 0) {
    return;
  }

  // 1. find ruleset
  auto ruleset_result = rp.findById(ruleset_id);
  if (ruleset_result == rp.end()) {
    error("Resource is not successfully updated");
  }
  auto &&ruleset = *ruleset_result;

  // 2. pick up proper rule inside the ruleset
  for (auto rule = ruleset->rules.cbegin(); rule != ruleset->cend(); ++rule) {
    // RuleID id not shared and consistent over the different node anymore.
    // To identify the rule corresponding to the result, we need other way.
    if ((*rule)->shared_tag == shared_tag) {  // here we can identify the rule of purification
      // 3. loop for resources currently assined
      for (auto qubit_record = (*rule)->resources.begin(); qubit_record != (*rule)->resources.end(); ++qubit_record) {
        partner_address = qubit_record->first;
        qubit = qubit_record->second;
        // 4. check which trial of purification
        if (qubit->action_index == index) {
          // 5. unlock qubit for later use
          qubit->Unlock();
          // remove qubit from resource list in the rule
          (*rule)->resources.erase(qubit_record);
          unsigned long next_rule_id = (*rule)->next_rule_id;
          for (; rule != ruleset->cend(); ++rule) {
            if ((*rule)->rule_id == next_rule_id) {
              (*rule)->addResource(partner_address, qubit);
              return;
            }
          }
          error("next rule not found: RuleSetID: %lu, RuleId: %d, index: %d", ruleset_id, rule_id, index);
        }
      }
    }
  }
}

void RuleEngine::Unlock_resource_and_discard(unsigned long ruleset_id, int rule_id, int shared_tag, int index) {
  auto ruleset_result = rp.findById(ruleset_id);
  if (ruleset_result == rp.end()) {
    error("Discard: Resource in rule not found.");
  }
  auto &&ruleset = *ruleset_result;

  // One Process. From top to bottom.
  for (auto rule = ruleset->cbegin(), end = ruleset->cend(); rule != end; rule++) {  // Traverse through rules
    if ((*rule)->shared_tag == shared_tag) {  // Find the corresponding rule.
      for (auto qubit_record = (*rule)->resources.begin(); qubit_record != (*rule)->resources.end(); ++qubit_record) {
        auto qubit = qubit_record->second;
        if (qubit->action_index == index) {
          // Purification failed, discard resource.
          qubit->Unlock();
          QNIC_type qt = (QNIC_type)qubit->qnic_type;
          qubit->par("god_x_error") = false;
          qubit->par("god_z_error") = false;
          // remove from current rule
          (*rule)->resources.erase(qubit_record);
          freeConsumedResource(qubit->qnic_index, qubit, qt);  // Remove from entangled resource list.
          return;
        }
      }
    }
  }
  error("Discard: Resource in rule not found....");
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

void RuleEngine::scheduleFirstPhotonEmission(BSMtimingNotifier *pk, QNIC_type qnic_type) {
  if (ntable.empty()) {
    ntable = hardware_monitor->passNeighborTable();  // Get neighbor table from Hardware Manager: neighbor address--> InterfaceInfo.
  }  // Just do this once, unless the network changes during the simulation.

  PhotonTransmissionConfig transmission_config;
  int destAddr = pk->getSrcAddr();  // The destination is where the request is generated (source of stand-alone or internal BSA node).
  switch (qnic_type) {
    case QNIC_E: {
      InterfaceInfo inf = getInterface_toNeighbor(destAddr);
      transmission_config.qnic_index = inf.qnic.index;
      transmission_config.qnic_address = inf.qnic.address;
    }  // inf is not defined beyound this point
    break;
    case QNIC_R:
      transmission_config.qnic_index = pk->getInternal_qnic_index();
      transmission_config.qnic_address = pk->getInternal_qnic_address();
      break;
    case QNIC_RP:
      error("This is not implemented yet");
      break;
    default:
      error("Only 3 qnic types are currently recognized....");
  }
  transmission_config.timing = pk->getTiming_at();
  transmission_config.interval = pk->getInterval();
  transmission_config.qnic_type = qnic_type;
  // store the interface information for the futhter link generation process
  int num_free = qnic_store->countNumFreeQubits(transmission_config.qnic_type, transmission_config.qnic_index);
  if (num_free > 0 && tracker_accessible.at(transmission_config.qnic_address)) {
    tracker_accessible.at(transmission_config.qnic_address) = false;  // block access to tracker
    sendPhotonTransmissionSchedule(transmission_config);
  }
}

void RuleEngine::sendPhotonTransmissionSchedule(PhotonTransmissionConfig transmission_config) {
  SchedulePhotonTransmissionsOnebyOne *st = new SchedulePhotonTransmissionsOnebyOne("SchedulePhotonTransmissionsOneByOne(First)");
  st->setQnic_index(transmission_config.qnic_index);
  st->setQnic_address(transmission_config.qnic_address);
  st->setInterval(transmission_config.interval);
  st->setTiming(transmission_config.timing);
  st->setTrial(qnic_burst_trial_counter[transmission_config.qnic_address]);  // Keeps the burst counter. First burst index is 0.

  bool internal = false;
  if (transmission_config.qnic_type == QNIC_R) {
    // Note: just add internal qnic type
    internal = true;
  } else if (transmission_config.qnic_type == QNIC_E) {
    internal = false;
  } else if (transmission_config.qnic_type == QNIC_RP) {
    error("Not implemented yet");
  } else {
    // for later implementations
    error("New qnic type detected. Add here.");
  }

  if (internal) {
    st->setInternal_hom(1);  // Mark request that the request is for internal BSA node.
  }

  int num_free = qnic_store->countNumFreeQubits(transmission_config.qnic_type, transmission_config.qnic_index);
  if (num_free > 0) {
    scheduleAt(simTime(), st);
  } else {
    delete st;
  }
}

bool RuleEngine::burstTrial_outdated(int this_trial, int qnic_address) {
  bool stop_emitting = false;
  if (this_trial != qnic_burst_trial_counter[qnic_address]) {
    stop_emitting = true;
  }
  return stop_emitting;
}

void RuleEngine::shootPhoton_internal(SchedulePhotonTransmissionsOnebyOne *pk) {
  int qnic_index = pk->getQnic_index();
  QNIC_type qnic_type = QNIC_R;
  int num_free = qnic_store->countNumFreeQubits(qnic_type, qnic_index);
  if (num_free == 0) {
    return;
  }

  emt = new EmitPhotonRequest("EmitPhotonRequest(internal)");
  int qubit_index = qnic_store->takeFreeQubitIndex(qnic_type, qnic_index);
  num_free--;
  emt->setQubit_index(qubit_index);
  emt->setQnic_index(pk->getQnic_index());
  emt->setQnic_address(pk->getQnic_address());
  emt->setTrial(pk->getTrial());
  emt->setQnic_type(QNIC_R);

  if (pk->getNum_sent() == 0) {  // First shot!!!
    if (num_free == 0)
      emt->setKind(STATIONARYQUBIT_PULSE_BOUND);  // First and last photon.
    else
      emt->setKind(STATIONARYQUBIT_PULSE_BEGIN);  // First photon
    scheduleAt(simTime() + pk->getTiming(), emt);
  } else {
    if (num_free == 0)  // If no more free qubit
      emt->setKind(STATIONARYQUBIT_PULSE_END);  // last one
    else
      emt->setKind(0);  // Just a photon in a burst. Not the beginning, nor the end.
    scheduleAt(simTime() + pk->getInterval(), emt);
  }
  scheduleNextEmissionEvent(pk->getQnic_index(), pk->getQnic_address(), pk->getInterval(), pk->getTiming(), pk->getNum_sent(), true, pk->getTrial());
}

// This method is for qnic (not qnic_r, qnic_rp).
void RuleEngine::shootPhoton(SchedulePhotonTransmissionsOnebyOne *pk) {
  int qnic_index = pk->getQnic_index();
  QNIC_type qnic_type = QNIC_E;
  int num_free = qnic_store->countNumFreeQubits(qnic_type, qnic_index);

  if (num_free == 0) {
    return;
  }

  emt = new EmitPhotonRequest("EmitPhotonRequest");
  int qubit_index = qnic_store->takeFreeQubitIndex(qnic_type, qnic_index);
  num_free--;
  emt->setQubit_index(qubit_index);
  emt->setQnic_address(pk->getQnic_address());
  emt->setTrial(pk->getTrial());
  emt->setQnic_index(pk->getQnic_index());
  emt->setQnic_type(QNIC_E);

  if (pk->getNum_sent() == 0) {
    if (num_free == 0)
      emt->setKind(STATIONARYQUBIT_PULSE_BOUND);  // First and last photon.
    else
      emt->setKind(STATIONARYQUBIT_PULSE_BEGIN);  // First photon
    scheduleAt(simTime() + pk->getTiming(), emt);
  } else {
    if (num_free == 0)
      emt->setKind(STATIONARYQUBIT_PULSE_END);  // last one
    else
      emt->setKind(0);  // others
    scheduleAt(simTime() + pk->getInterval(), emt);
  }
  scheduleNextEmissionEvent(pk->getQnic_index(), pk->getQnic_address(), pk->getInterval(), pk->getTiming(), pk->getNum_sent(), false, pk->getTrial());
}

void RuleEngine::scheduleNextEmissionEvent(int qnic_index, int qnic_address, double interval, simtime_t timing, int num_sent, bool internal, int trial) {
  SchedulePhotonTransmissionsOnebyOne *st = new SchedulePhotonTransmissionsOnebyOne("SchedulePhotonTransmissionsOneByOne");
  st->setQnic_index(qnic_index);
  st->setQnic_address(qnic_address);
  st->setInterval(interval);
  st->setTiming(timing);
  st->setNum_sent(num_sent + 1);  // increment
  st->setTrial(trial);
  if (internal) st->setInternal_hom(1);
  if (num_sent == 0)  // First scheduling must be adjusted to timing
    scheduleAt(simTime() + timing, st);
  else  // from the second emission, 1 photon per interval
    scheduleAt(simTime() + interval, st);
}

void RuleEngine::incrementBurstTrial(int destAddr, int internal_qnic_address, int internal_qnic_index) {
  int qnic_address = -1, qnic_index, qnic_type;
  if (internal_qnic_address == -1) {  // destination hom is outside this node.
    InterfaceInfo inf = getInterface_toNeighbor(destAddr);
    qnic_index = inf.qnic.index;
    qnic_address = inf.qnic.address;
    qnic_type = QNIC_E;
  } else {  // destination hom is in the qnic in this node. This gets invoked when the request from internal hom is send from the same node.
    qnic_address = internal_qnic_address;
    qnic_index = internal_qnic_index;
    qnic_type = QNIC_R;
  }
  qnic_burst_trial_counter[qnic_address]++;  // Increment the burst trial counter.
  // You dont need this unless you want to see how many trials have been dealt by each qnic via IDE.
  switch (qnic_type) {  // if ((qnic_type == QNIC_E) || (qnic_type == QNIC_R)) // if (qnic_type < QNIC_RP)
    case QNIC_E:
    case QNIC_R:
      provider.getQNIC(qnic_index, QNIC_type(qnic_type))->par("burst_trial_counter") = qnic_burst_trial_counter[qnic_address];
  }
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

  runtime::Runtime *runtime = nullptr;
  for (auto &rt : runtimes) {
    if (rt.ruleset.id == data.ruleset_id) {
      runtime = &rt;
      break;
    }
  }
  assert(runtime != nullptr);
  bell_pair_store.eraseQubit(qubit_record);
  bell_pair_store.insertEntangledQubit(data.new_partner_addr, qubit_record);
  runtime->promoteQubitWithNewPartner(qubit_record, data.new_partner_addr);
}
void RuleEngine::updateResources_EntanglementSwapping(swapping_result swapr) {
  // swapper believe previous BSM was succeeded.
  // These are new partner's info

  int new_partner = swapr.new_partner;
  int operation_type = swapr.operation_type;
  int shared_tag = swapr.id.shared_tag;
  int qnic_address = routingdaemon->return_QNIC_address_to_destAddr(new_partner);
  auto info = hardware_monitor->findConnectionInfoByQnicAddr(qnic_address);
  if (info == nullptr) {
    error("qnic(addr: %d) info not found", qnic_address);
  }
  int qnic_index = info->qnic.index;
  QNIC_type qnic_type = info->qnic.type;
  int qubit_index = swapr.measured_qubit_index;

  // qubit with address Addr was shot in nth time. This list is ordered from old to new.
  auto *qubit_record = qnic_store->getQubitRecord(qnic_type, qnic_index, qubit_index);
  // check
  if (operation_type == 0) {
    // do nothing
  } else if (operation_type == 1) {
    // do X
    realtime_controller->applyXGate(qubit_record);
  } else if (operation_type == 2) {
    realtime_controller->applyZGate(qubit_record);
  } else {
    error("Something went wrong. This operation type isn't recorded!");
  }

  realtime_controller->assertNoEntanglement(qubit_record);
  auto qubit = provider.getStationaryQubit(qubit_record);

  // Promote entanglement from this rule to the next rule
  unsigned long ruleset_id = swapr.id.ruleset_id;
  const int rule_id = swapr.id.rule_id;
  const int swapper_addr = swapr.swapper_addr;
  if (rp.size() == 0) {
    return;
  }
  const auto &ruleset_result = rp.findById(ruleset_id);
  if (ruleset_result == rp.end()) {
    error("The qubit is not promoted from entanglement swapping to the next rule. no ruleset(%lu) found", ruleset_id);
  }
  const auto &ruleset = *ruleset_result;

  // The target rule must be wait rule that has a single action partner (swapper)
  for (int index = 0; index < ruleset->size(); index++) {
    auto target_rule_ptr = ruleset->getRule(index).get();
    // Detect the target wait Rule
    if (target_rule_ptr->shared_tag == shared_tag) {
      // 2. erase qubit from target rule
      for (auto qubit_rec = target_rule_ptr->resources.cbegin(); qubit_rec != target_rule_ptr->resources.cend(); qubit_rec++) {
        auto target_qubit = qubit_rec->second;
        if (target_qubit == qubit) {
          target_rule_ptr->resources.erase(qubit_rec);
          break;
        }
      }
      // // 3. add qubit as a resource to the next rule
      const int next_rule_id = target_rule_ptr->next_rule_id;
      if (next_rule_id == -1) {
        // After the exntanglement swapping, resource must be promoted to somewhere
        error("The resource must be promoted to be used by the next rule after the entanglement swapping.");
      }
      auto target_next_rule_ptr = ruleset->getRule(next_rule_id).get();
      target_next_rule_ptr->addResource(new_partner, qubit);
      return;
    }
  }
  error("Resource is not promoted properly");
}

void RuleEngine::updateResources_SimultaneousEntanglementSwapping(swapping_result swapr) {
  int new_partner = swapr.new_partner;
  int operation_type = swapr.operation_type;

  int qnic_address = routingdaemon->return_QNIC_address_to_destAddr(new_partner);
  auto info = hardware_monitor->findConnectionInfoByQnicAddr(qnic_address);
  if (info == nullptr) {
    error("qnic(addr: %d) info not found", qnic_address);
  }
  int qnic_index = info->qnic.index;
  QNIC_type qnic_type = info->qnic.type;
  int qubit_index = swapr.measured_qubit_index;
  auto *qubit_record = qnic_store->getQubitRecord(qnic_type, qnic_index, qubit_index);

  if (operation_type == 0) {
    // nothing
  } else if (operation_type == 1) {
    // do Z
    realtime_controller->applyZGate(qubit_record);
  } else if (operation_type == 2) {
    // do X
    realtime_controller->applyZGate(qubit_record);

  } else if (operation_type == 3) {
    // do XZ
    realtime_controller->applyZGate(qubit_record);
    realtime_controller->applyXGate(qubit_record);
  } else {
    error("something error happened! This operation type doesn't recorded!");
  }
  realtime_controller->assertNoEntanglement(qubit_record);
  IStationaryQubit *qubit = provider.getStationaryQubit(qubit_record);
  // first delete old record
  bell_pair_store.eraseQubit(qubit_record);

  // Make this qubit available for rules
  if (qubit_record->isAllocated()) {
    error("qubit is already allocated");
  }
  if (qubit->isLocked()) {
    error("qubit is locked");
  }
  bell_pair_store.insertEntangledQubit(new_partner, qubit_record);
  if (qubit->entangled_partner != nullptr) {
    if (qubit->entangled_partner->entangled_partner == nullptr) {
      error("1. Entanglement tracking is not doing its job. in update resource E.S.");
    }
    if (qubit->entangled_partner->entangled_partner != qubit) {
      error("2. Entanglement tracking is not doing its job. in update resource E.S.");
    }
  }
  ResourceAllocation(qnic_type, qnic_index);
  traverseThroughAllProcesses2();  // New resource added to QNIC with qnic_type qnic_index.
}

// Only for MIM and MM
void RuleEngine::freeFailedQubits_and_AddAsResource(int destAddr, int internal_qnic_address, int internal_qnic_index, CombinedBSAresults *pk_result) {
  // get the size of failed bsa
  int list_size = pk_result->getList_of_failedArraySize();
  int qnic_index, qnic_address, neighborQNodeAddress = -1;
  QNIC_type qnic_type;

  // if the HOM is external
  if (internal_qnic_index == -1) {  // destination hom is outside this node.
    InterfaceInfo inf = getInterface_toNeighbor(destAddr);
    neighborQNodeAddress = inf.neighborQNode_address;  // Because we need the address of the neighboring QNode, not BSA!
    qnic_index = inf.qnic.index; /*Only unique inside the same qnic_type.*/
    qnic_address = inf.qnic.address; /*Unique address*/
    qnic_type = QNIC_E;
  } else {  // destination hom is in the qnic in this node. This gets invoked when the request from internal hom is send from the same node.
    qnic_index = internal_qnic_index;
    qnic_address = internal_qnic_address;
    qnic_type = QNIC_R;
    neighborQNodeAddress = getInterface_toNeighbor_Internal(qnic_address).neighborQNode_address;
  }

  // How many photons are bursted?
  int num_emitted_in_this_burstTrial = tracker[qnic_address].size();
  // start iteration from 0 .. number of failed bsm
  for (int i = 0; i < list_size; i++) {
    // This includes not only failed result but also success result
    bool failed = pk_result->getList_of_failed(i);

    // check the tracker records
    auto it = tracker[qnic_address].find(i);  // check ith shot's information (qnic, qubit index).
    if (it == tracker[qnic_address].end())
      error("Something is wrong with the tracker....%d th shot not recorded", i);  // Neighbor not found! This should not happen unless you simulate broken links in real time.

    // if the ith BSM failed
    if (failed) {
      // Free failed qubits
      freeResource(it->second.qnic_index, it->second.qubit_index, qnic_type);
    } else {
      // Keep the entangled qubits
      auto *qubit_record = qnic_store->getQubitRecord(qnic_type, qnic_index, it->second.qubit_index);
      IStationaryQubit *qubit = provider.getStationaryQubit(qubit_record);

      // if the partner is null, not correct
      if (qubit->entangled_partner != nullptr) {
        if (qubit->entangled_partner->entangled_partner == nullptr) {
          // my instance is null (no way)
          error("1. Entanglement tracking is not doing its job.");
        }
        if (qubit->entangled_partner->entangled_partner != qubit) {
          // partner's qubit doesn't point this qubit -> wrong
          error("2. Entanglement tracking is not doing its job.");
        }
      }

      if (qubit->entangled_partner == nullptr && qubit->Density_Matrix_Collapsed(0, 0).real() == -111 && !qubit->no_density_matrix_nullptr_entangled_partner_ok) {
        EV << "entangle partner null?" << qubit->entangled_partner << " == nullptr?\n";
        EV << "density matrix collapsed?" << qubit->Density_Matrix_Collapsed(0, 0).real() << "==-111?\n";
        EV << "here should be true" << qubit->no_density_matrix_nullptr_entangled_partner_ok << "\n";
        error("RuleEngine. Ebit succeed. but wrong");
      }
      // Add qubit as available resource between NeighborQNodeAddress.
      bell_pair_store.insertEntangledQubit(neighborQNodeAddress, qubit_record);
    }
  }

  // Any qubit that has been shot while BSA result is actually on the way to the node, needs to be freed as well.
  if (num_emitted_in_this_burstTrial > list_size) {
    for (int i = list_size; i < num_emitted_in_this_burstTrial; i++) {
      auto it = tracker[qnic_address].find(i);  // check ith shot's information (qnic, qubit index).
      // Neighbor not found! This should not happen unless you simulate broken links in real time.
      if (it == tracker[qnic_address].end()) {
        error("Wait.... something is wrong with the tracker....%d th shot not recorded", i);
      }
      freeResource(it->second.qnic_index, it->second.qubit_index, qnic_type);
    }
  }
  ResourceAllocation(qnic_type, qnic_index);
  traverseThroughAllProcesses2();  // New resource added to QNIC with qnic_type qnic_index.
}

void RuleEngine::freeResource(int qnic_index /*The actual index. Not address. This with qnic_type makes the id unique.*/, int qubit_index, QNIC_type qnic_type) {
  auto *qubit_record = qnic_store->getQubitRecord(qnic_type, qnic_index, qubit_index);
  realtime_controller->ReInitialize_StationaryQubit(qubit_record, false);
  qubit_record->setBusy(false);
  if (qubit_record->isAllocated()) qubit_record->setAllocated(false);
}

void RuleEngine::clearTrackerTable(int destAddr, int internal_qnic_address) {
  int qnic_address = -1;
  if (internal_qnic_address == -1) {  // destination hom is outside this node.
    InterfaceInfo inf = getInterface_toNeighbor(destAddr);
    qnic_address = inf.qnic.address;
  } else {  // destination hom is in the qnic in this node. This gets invoked when the request from internal hom is send from the same node.
    qnic_address = internal_qnic_address;
  }
  if (qnic_address == -1) error("Failed clearing tracker of a qnic. This should not happen.");
  tracker[qnic_address].clear();
  tracker_accessible.at(qnic_address) = true;
}

void RuleEngine::finish() { delete qnic_burst_trial_counter; }

double RuleEngine::predictResourceFidelity(QNIC_type qnic_type, int qnic_index, int entangled_node_address, int resource_index) { return uniform(.6, .9); }

// Invoked whenever a new resource (entangled with neighbor) has been created.
// Allocates those resources to a particular ruleset, from top to bottom (all of it).
void RuleEngine::ResourceAllocation(int qnic_type, int qnic_index) {
  for (auto &runtime : runtimes) {
    auto partners = runtime.partners;
    for (auto partner_addr : partners) {
      auto range = bell_pair_store.getBellPairsRange((QNIC_type)qnic_type, qnic_index, partner_addr.val);
      for (auto it = range.first; it != range.second; ++it) {
        auto qubit_record = it->second;
        auto *qubit = provider.getStationaryQubit(qubit_record);

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

void RuleEngine::traverseThroughAllProcesses2() {
  for (auto &runtime : runtimes) {
    // how should we delete the runtime and its ruleset?
    runtime.exec(runtime.ruleset);
  }
  return;
  /*
            SimultaneousSwappingResult *pkt = check_and_cast<SimultaneousSwappingResult *>(pk);
            // packet for right node
            SimultaneousSwappingResult *pkt_for_responder = new SimultaneousSwappingResult("SimultaneousSwappingResult(Right)");
            pkt_for_responder->setKind(5);  // cyan
            pkt_for_responder->setDestAddr(pkt->getResponder_Dest());
            pkt_for_responder->setSrcAddr(parentAddress);
            pkt_for_responder->setOperation_type(pkt->getOperation_type_right());
            pkt_for_responder->setMeasured_qubit_index(pkt->getMeasured_qubit_index_right());
            pkt_for_responder->setNew_partner(pkt->getNew_partner_right());
            pkt_for_responder->setNew_partner_qnic_index(pkt->getNew_partner_qnic_index_right());
            pkt_for_responder->setNew_partner_qnic_address(pkt->getNew_partner_qnic_address_right());
            pkt_for_responder->setNew_partner_qnic_type(pkt->getNew_partner_qnic_type_right());

          process_done = (*rule)->checkTerminate();  // The entire process is done. e.g. enough measurement for tomography.
          if (process_done) {  // Delete rule set if done
            // delete ruleset
            rs_iter = rp.erase(rs_iter);
            ruleset_deleted = true;
            break;  // get out from this for loop.
          }

        }  // While
        if (process_done) {
          break;
        }
      }  // For
      // if the ruleset deleted, the rs_iter points the next ruleset.
      if (!ruleset_deleted) {
        // if not, we need to incremet the rs_iter to point the next ruleset.
        rs_iter++;
      }
    }  // For loop
    */
}

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

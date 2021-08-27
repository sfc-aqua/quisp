/** \file RuleEngine.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/04/04
 *
 *  \brief RuleEngine
 */

#include "RuleEngine.h"
#include <fstream>
#include <utility>
#include "utils/ComponentProvider.h"

namespace quisp {
namespace modules {

Define_Module(RuleEngine);

using namespace rules;

RuleEngine::RuleEngine() : provider(utils::ComponentProvider{this}) {}

void RuleEngine::initialize() {
  // HardwareMonitor's neighbor table is checked in the initialization stage of the simulation
  // This assumes the topology never changes throughout the simulation.
  // If dynamic change in topology is required, recoding this is needed.
  hardware_monitor = provider.getHardwareMonitor();
  realtime_controller = provider.getRealTimeController();
  routingdaemon = provider.getRoutingDaemon();

  parentAddress = par("address");
  number_of_qnics_all = par("total_number_of_qnics");
  number_of_qnics = par("number_of_qnics");
  number_of_qnics_r = par("number_of_qnics_r");
  number_of_qnics_rp = par("number_of_qnics_rp");
  // recog_resSignal = registerSignal("recog_res");
  actual_resSignal = registerSignal("actual_res");

  terminated_qnic = new bool[number_of_qnics_all];
  // if there are 2 qnics, 1 qnic_r, and 2 qnic_rp,
  // then trial_index[0~1] is assigned for qnics, trial_index[2~2] for qnic_r and trial_index[3~4] for qnic_rp....
  qnic_burst_trial_counter = new int[number_of_qnics_all];

  for (int i = 0; i < number_of_qnics_all; i++) {
    qnic_burst_trial_counter[i] = 0;
    terminated_qnic[i] = false;
  }

  Busy_OR_Free_QubitState_table = new QubitStateTable[QNIC_N];
  Busy_OR_Free_QubitState_table[QNIC_E] = initializeQubitStateTable(Busy_OR_Free_QubitState_table[QNIC_E], QNIC_E);
  Busy_OR_Free_QubitState_table[QNIC_R] = initializeQubitStateTable(Busy_OR_Free_QubitState_table[QNIC_R], QNIC_R);
  Busy_OR_Free_QubitState_table[QNIC_RP] = initializeQubitStateTable(Busy_OR_Free_QubitState_table[QNIC_RP], QNIC_RP);

  // Tracks which qubit was sent first, second and so on per qnic(r,rp)
  tracker = new sentQubitIndexTracker[number_of_qnics_all];
  for (int qnic_address = 0; qnic_address < number_of_qnics_all; qnic_address++) {
    tracker_accessible.push_back(true);
  }

  // running_processes = new RuleSetPtr[QNIC_N];//One process per QNIC for now. No multiplexing.
  // WATCH(assigned);
}

void RuleEngine::handleMessage(cMessage *msg) {
  traverseThroughAllProcesses2();  // New resource added to QNIC with qnic_type qnic_index.

  if (dynamic_cast<EmitPhotonRequest *>(msg) != nullptr) {  // From self.
    EmitPhotonRequest *pk = check_and_cast<EmitPhotonRequest *>(msg);
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
      // std::cout<<getQNode()->getFullName() <<": Emitted the "<<nth_shot<<" from qnic["<<qnic_address<<"]....tracker["<<qnic_address<<"] now size = "<<new_nth_shot<<"\n";
    }
    // switch: Only bubble messages
    switch (pk->getKind()) {
      case STATIONARYQUBIT_PULSE_BEGIN:
        bubble("first..");
        break;
      case STATIONARYQUBIT_PULSE_END:
        bubble("last..");
        break;
      case STATIONARYQUBIT_PULSE_BOUND:
        bubble("first and last..");
        break;
      default:
        bubble("order received!");
    }
    realtime_controller->EmitPhoton(pk->getQnic_index(), pk->getQubit_index(), (QNIC_type)pk->getQnic_type(), pk->getKind());
  }

  else if (dynamic_cast<CombinedBSAresults *>(msg) != nullptr) {
    // First, keep all the qubits that were successfully entangled, and reinitialize the failed ones.
    CombinedBSAresults *pk_result = check_and_cast<CombinedBSAresults *>(msg);
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
    int qnic_address, qnic_type;
    int qnic_index;
    if (pk->getInternal_qnic_address() == -1) {  // destination hom is outside this node.
      InterfaceInfo inf = getInterface_toNeighbor(pk->getSrcAddr());
      qnic_index = inf.qnic.index;
      qnic_address = inf.qnic.address;
      qnic_type = QNIC_E;
      // neighborQNodeAddress = inf.neighborQNode_address;
    } else {  // destination hom is in the qnic in this node. This gets invoked when the request from internal hom is send from the same node.
      qnic_index = pk->getInternal_qnic_index();
      qnic_address = pk->getInternal_qnic_address();
      qnic_type = QNIC_R;
    }

    if (terminated_qnic[qnic_address]) {
      // std::cout<<"NOT ANY MORE qnic["<<qnic_address<<"] in node["<<parentAddress<<"]";
      // error("qnic should not be terminated here, Node: %d, qnic_address: %d", parentAddress, qnic_address);
      return;
    } else if (pk->getInternal_qnic_index() == -1) {  // Schedule next burst. MIM, or the other node without internal HoM of MM
      EV_DEBUG << "This BSA request is non-internal\n";
      scheduleFirstPhotonEmission(pk, QNIC_E);
    } else {
      EV_DEBUG << "This BSA request is internal\n";
      scheduleFirstPhotonEmission(pk, QNIC_R);
    }
  }

  else if (dynamic_cast<SchedulePhotonTransmissionsOnebyOne *>(msg) != nullptr) {
    SchedulePhotonTransmissionsOnebyOne *pk = check_and_cast<SchedulePhotonTransmissionsOnebyOne *>(msg);
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

  // Bell pair generation timing syncronization from HoM
  else if (dynamic_cast<BSMtimingNotifier *>(msg) != nullptr && dynamic_cast<CombinedBSAresults *>(msg) == nullptr) {
    bubble("timing received");
    EV << "BSM timing notifier received\n";
    BSMtimingNotifier *pk = check_and_cast<BSMtimingNotifier *>(msg);
    if (pk->getInternal_qnic_index() == -1) {  // MIM, or the other node without internnal HoM of MM
      EV_DEBUG << "This BSA request is non-internal\n";
      scheduleFirstPhotonEmission(pk, QNIC_E);
    } else {
      EV_DEBUG << "This BSA request is internal\n";
      scheduleFirstPhotonEmission(pk, QNIC_R);
    }
  } else if (dynamic_cast<EPPStimingNotifier *>(msg) != nullptr) {
    bubble("EPPS");
    error("EPPS is not implemented yet");
  }

  else if (dynamic_cast<LinkTomographyRuleSet *>(msg) != nullptr) {
    // Received a tomography rule set.
    LinkTomographyRuleSet *pk = check_and_cast<LinkTomographyRuleSet *>(msg);
    // std::cout<<"node["<<parentAddress<<"] !!!!!!!!!!Ruleset reveid!!!!!!!!! ruleset id = "<<pk->getRuleSet()->ruleset_id<<"\n";
    Process p;
    p.owner_addr = pk->getRuleSet()->owner_addr;
    p.Rs = pk->getRuleSet();
    int process_id = rp.size();  // This is temporary because it will not be unique when processes have been deleted.
    std::cout << "Process size is ...." << p.Rs->size() << " node[" << parentAddress << "\n";
    // todo:We also need to allocate resources. e.g. if all qubits were entangled already, and got a new ruleset.
    // ResourceAllocation();
    if (p.Rs->size() > 0) {
      rp.insert(std::make_pair(process_id, p));
      EV << "New process arrived !\n";
    } else {
      error("Empty rule set...");
    }
  } else if (dynamic_cast<PurificationResult *>(msg) != nullptr) {
    PurificationResult *pkt = check_and_cast<PurificationResult *>(msg);
    process_id purification_id;
    purification_result pr;
    purification_id.ruleset_id = pkt->getRuleset_id();
    purification_id.rule_id = pkt->getRule_id();
    purification_id.index = pkt->getAction_index();
    pr.id = purification_id;
    pr.outcome = pkt->getOutput_is_plus();
    storeCheck_Purification_Agreement(pr);
  } else if (dynamic_cast<DoublePurificationResult *>(msg) != nullptr) {
    DoublePurificationResult *pkt = check_and_cast<DoublePurificationResult *>(msg);
    process_id purification_id;
    Doublepurification_result pr;
    purification_id.ruleset_id = pkt->getRuleset_id();
    purification_id.rule_id = pkt->getRule_id();
    purification_id.index = pkt->getAction_index();
    pr.id = purification_id;
    pr.Xpurification_outcome = pkt->getXOutput_is_plus();
    pr.Zpurification_outcome = pkt->getZOutput_is_plus();
    storeCheck_DoublePurification_Agreement(pr);
  } else if (dynamic_cast<DS_DoublePurificationResult *>(msg) != nullptr) {
    // std::cout<<"!!!!Purification result reveid!!! node["<<parentAddress<<"]\n";
    DS_DoublePurificationResult *pkt = check_and_cast<DS_DoublePurificationResult *>(msg);
    // std::cout<<"Presult from node["<<pkt->getSrcAddr()<<"]\n";
    process_id purification_id;
    Quatropurification_result pr;
    purification_id.ruleset_id = pkt->getRuleset_id();
    purification_id.rule_id = pkt->getRule_id();
    purification_id.index = pkt->getAction_index();
    pr.id = purification_id;
    pr.Xpurification_outcome = pkt->getXOutput_is_plus();
    pr.Zpurification_outcome = pkt->getZOutput_is_plus();
    pr.DS_Xpurification_outcome = pkt->getDS_XOutput_is_plus();
    pr.DS_Zpurification_outcome = pkt->getDS_ZOutput_is_plus();
    // StationaryQubit *q = check_and_cast<StationaryQubit *>(pkt->getEntangled_with());
    // std::cout<<"Purification result is from node["<<pkt->getSrcAddr()<<"] rid="<< pkt->getRuleset_id()<<"Must be qnic["<<my_qnic_index<<" type="<<my_qnic_type<<"\n";
    // std::cout<<"Locked one is "<<pkt->getEntangled_with()<<"in node["<<q->node_address<<"] \n";
    storeCheck_QuatroPurification_Agreement(pr);
  } else if (dynamic_cast<DS_DoublePurificationSecondResult *>(msg) != nullptr) {
    // std::cout<<"!!!!Purification result reveid!!! node["<<parentAddress<<"]\n";
    DS_DoublePurificationSecondResult *pkt = check_and_cast<DS_DoublePurificationSecondResult *>(msg);
    process_id purification_id;
    Triplepurification_result pr;
    purification_id.ruleset_id = pkt->getRuleset_id();
    purification_id.rule_id = pkt->getRule_id();
    purification_id.index = pkt->getAction_index();
    pr.id = purification_id;
    pr.Xpurification_outcome = pkt->getXOutput_is_plus();
    pr.Zpurification_outcome = pkt->getZOutput_is_plus();
    pr.DS_purification_outcome = pkt->getDS_Output_is_plus();
    storeCheck_TriplePurification_Agreement(pr);
  } else if (dynamic_cast<SwappingResult *>(msg) != nullptr) {
    SwappingResult *pkt = check_and_cast<SwappingResult *>(msg);
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
    swapr.operation_type = pkt->getOperation_type();
    updateResources_EntanglementSwapping(swapr);
  }

  else if (dynamic_cast<SimultaneousSwappingResult *>(msg) != nullptr) {
    SimultaneousSwappingResult *pkt = check_and_cast<SimultaneousSwappingResult *>(msg);
    // Add messeage to collection [ruleSetid][index_in_path]
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

  else if (dynamic_cast<InternalRuleSetForwarding *>(msg) != nullptr) {
    InternalRuleSetForwarding *pkt = check_and_cast<InternalRuleSetForwarding *>(msg);
    // add actual process
    Process p;
    p.owner_addr = pkt->getRuleSet()->owner_addr;
    // for check
    p.Rs = pkt->getRuleSet();
    // here swappers got swapping ruleset with internal packet
    int process_id = rp.size();  // This is temporary because it will not be unique when processes have been deleted.
    // todo:We also need to allocate resources. e.g. if all qubits were entangled already, and got a new ruleset.
    // ResourceAllocation();
    if (p.Rs->size() > 0) {
      rp.insert(std::make_pair(process_id, p));
      EV << "New process arrived !\n";
    } else {
      error("Empty rule set...");
    }
  } else if (dynamic_cast<InternalRuleSetForwarding_Application *>(msg) != nullptr) {
    InternalRuleSetForwarding_Application *pkt = check_and_cast<InternalRuleSetForwarding_Application *>(msg);
    // doing end to end tomography
    if (pkt->getApplication_type() == 0) {
      // Received a tomography rule set.
      Process p;
      p.owner_addr = pkt->getRuleSet()->owner_addr;
      p.Rs = pkt->getRuleSet();
      int process_id = rp.size();  // This is temporary because it will not be unique when processes have been deleted.
      std::cout << "Process size is ...." << p.Rs->size() << " node[" << parentAddress << "\n";
      if (p.Rs->size() > 0) {
        rp.insert(std::make_pair(process_id, p));
        EV << "New process arrived !\n";
      } else {
        error("Empty rule set...");
      }

    } else {
      error("This application is not recognized yet");
    }
  } else if (dynamic_cast<StopEmitting *>(msg) != nullptr) {
    StopEmitting *pkt = check_and_cast<StopEmitting *>(msg);
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

void RuleEngine::storeCheck_Purification_Agreement(purification_result pur_result) {
  bool ruleset_running = false;
  for (auto it = rp.cbegin(), next_it = rp.cbegin(); it != rp.cend(); it = next_it) {
    next_it = it;
    ++next_it;
    RuleSet *process = it->second.Rs;  // One Process. From top to bottom.
    if (process->ruleset_id == pur_result.id.ruleset_id) {
      ruleset_running = true;
      break;
    }
  }

  // 1. check the ruleset is currently running.
  if (rp.size() == 0 || !ruleset_running) {
    // Probably process already finished. Delete the table and ignore the result.
    return;
  } else {
    // 2. Check if there are some records existed.
    // check the purification results that belong to the same connection
    auto range = Purification_table.equal_range(pur_result.id.ruleset_id);
    for (auto it = range.first; it != range.second; it++) {
      if (it->second.id.rule_id == pur_result.id.rule_id && it->second.id.index == pur_result.id.index) {
        if (it->second.outcome == pur_result.outcome) {
          // the result is coordinate to the counter part
          Unlock_resource_and_upgrade_stage(pur_result.id.ruleset_id, pur_result.id.rule_id, pur_result.id.index);
        } else {
          // the result is different. discard the resource
          Unlock_resource_and_discard(pur_result.id.ruleset_id, pur_result.id.rule_id, pur_result.id.index);
        }
        Purification_table.erase(it);
        return;
      }
    }
    Purification_table.insert(std::make_pair(pur_result.id.ruleset_id, pur_result));
    return;
  }
}

void RuleEngine::storeCheck_DoublePurification_Agreement(Doublepurification_result pr) {
  bool ruleset_running = false;
  for (auto it = rp.cbegin(), next_it = rp.cbegin(); it != rp.cend(); it = next_it) {
    next_it = it;
    ++next_it;
    RuleSet *process = it->second.Rs;  // One Process. From top to bottom.
    if (process->ruleset_id == pr.id.ruleset_id) {
      ruleset_running = true;
      break;
    }
  }
  if (rp.size() == 0 || !ruleset_running) {
    // Probably process already finished. Delete the table and ignore the result.
    return;
  } else {
    // Find all resource in qytpe/qid entangled with partner.
    auto ret = DoublePurification_table.equal_range(pr.id.ruleset_id);
    // If the RuleSet has been deleted already, do not do anything.

    for (auto it = ret.first; it != ret.second; it++) {
      if (it->second.id.rule_id == pr.id.rule_id && it->second.id.index == pr.id.index) {
        // std::cout<<"Rule_id="<<pr.id.rule_id<<", index="<<pr.id.index<<"\n";
        // std::cout<<"node["<<parentAddress<<"] Rule found: Discard/Keep purification.\n";
        if ((it->second.Xpurification_outcome == pr.Xpurification_outcome) && (it->second.Zpurification_outcome == pr.Zpurification_outcome)) {
          // Outcomes agreed. Keep the entangled pair.
          // std::cout<<"Unlocking and upgrading!\n";
          Unlock_resource_and_upgrade_stage(pr.id.ruleset_id, pr.id.rule_id, pr.id.index);
        } else {
          // Discard
          // std::cout<<"node["<<parentAddress<<"] discaard ";
          // std::cout<<"Unlocking and discarding!\n";
          Unlock_resource_and_discard(pr.id.ruleset_id, pr.id.rule_id, pr.id.index);
        }
        DoublePurification_table.erase(it);
        return;
      }
    }
    // New data.
    // std::cout<<"New data arrived. Need to keep the outcome of rulset_id="<<pr.id.ruleset_id<<" Rule_id="<<pr.id.rule_id<<", index="<<pr.id.index<<"\n";
    DoublePurification_table.insert(std::make_pair(pr.id.ruleset_id, pr));  // Otherwise, if data has not been found, store it.
  }
}

void RuleEngine::storeCheck_TriplePurification_Agreement(Triplepurification_result pr) {
  bool ruleset_running = false;
  for (auto it = rp.cbegin(), next_it = rp.cbegin(); it != rp.cend(); it = next_it) {
    next_it = it;
    ++next_it;
    RuleSet *process = it->second.Rs;  // One Process. From top to bottom.
    if (process->ruleset_id == pr.id.ruleset_id) {
      ruleset_running = true;
      break;
    }
  }
  if (rp.size() == 0 || !ruleset_running) {
    // Probably process already finished. Delete the table and ignore the result.
    return;
  } else {
    auto ret = TriplePurification_table.equal_range(pr.id.ruleset_id);  // Find all resource in qytpe/qid entangled with partner.
    // If the RuleSet has been deleted already, do not do anything.

    for (auto it = ret.first; it != ret.second; it++) {
      if (it->second.id.rule_id == pr.id.rule_id && it->second.id.index == pr.id.index) {
        if ((it->second.Xpurification_outcome == pr.Xpurification_outcome) && (it->second.Zpurification_outcome == pr.Zpurification_outcome) &&
            (it->second.DS_purification_outcome == pr.DS_purification_outcome)) {
          // Outcomes agreed. Keep the entangled pair.
          Unlock_resource_and_upgrade_stage(pr.id.ruleset_id, pr.id.rule_id, pr.id.index);
        } else {
          // Discard
          Unlock_resource_and_discard(pr.id.ruleset_id, pr.id.rule_id, pr.id.index);
        }
        TriplePurification_table.erase(it);
        return;
      }
    }
    // New data.
    TriplePurification_table.insert(std::make_pair(pr.id.ruleset_id, pr));  // Otherwise, if data has not been found, store it.
  }
}

void RuleEngine::storeCheck_QuatroPurification_Agreement(Quatropurification_result pr) {
  bool ruleset_running = false;
  for (auto it = rp.cbegin(), next_it = rp.cbegin(); it != rp.cend(); it = next_it) {
    next_it = it;
    ++next_it;
    RuleSet *process = it->second.Rs;  // One Process. From top to bottom.
    if (process->ruleset_id == pr.id.ruleset_id) {
      ruleset_running = true;
      break;
    }
  }
  if (rp.size() == 0 || !ruleset_running) {
    // Probably process already finished. Delete the table and ignore the result.
    return;
  } else {
    auto ret = QuatroPurification_table.equal_range(pr.id.ruleset_id);  // Find all resource in qytpe/qid entangled with partner.
    // If the RuleSet has been deleted already, do not do anything.

    for (auto it = ret.first; it != ret.second; it++) {
      if (it->second.id.rule_id == pr.id.rule_id && it->second.id.index == pr.id.index) {
        // std::cout<<"Rule_id="<<pr.id.rule_id<<", index="<<pr.id.index<<"\n";
        // std::cout<<"node["<<parentAddress<<"] Rule found: Discard/Keep purification.\n";
        if ((it->second.Xpurification_outcome == pr.Xpurification_outcome) && (it->second.Zpurification_outcome == pr.Zpurification_outcome) &&
            (it->second.DS_Zpurification_outcome == pr.DS_Zpurification_outcome) && (it->second.DS_Xpurification_outcome == pr.DS_Xpurification_outcome)) {
          // Outcomes agreed. Keep the entangled pair.
          Unlock_resource_and_upgrade_stage(pr.id.ruleset_id, pr.id.rule_id, pr.id.index);
        } else {
          // Discard
          Unlock_resource_and_discard(pr.id.ruleset_id, pr.id.rule_id, pr.id.index);
        }
        QuatroPurification_table.erase(it);
        return;
      }
    }
    // New data.
    // std::cout<<"New data arrived. Need to keep the outcome of rulset_id="<<pr.id.ruleset_id<<" Rule_id="<<pr.id.rule_id<<", index="<<pr.id.index<<"\n";
    QuatroPurification_table.insert(std::make_pair(pr.id.ruleset_id, pr));  // Otherwise, if data has not been found, store it.
  }
}

/*

//todo:This assumes ordering. Not good. Better implement the same was as tomography.
void RuleEngine::check_Purification_Agreement(purification_result pr){

    std::cout<<"check_Purification_Agreement: "<<pr.id.ruleset_id<<"\n";
    std::cout<<"rp size = "<<rp.size()<<"\n";

    bool ruleset_running = false;
    for(auto it = rp.cbegin(), next_it = rp.cbegin(); it != rp.cend(); it = next_it){
               next_it = it; ++next_it;
               RuleSet* process = it->second.RuleSet;//One Process. From top to bottom.
               if(process->ruleset_id == pr.id.ruleset_id){
                   ruleset_running = true;
                   break;
               }
    }
    if(rp.size()==0 || !ruleset_running){
        //Already finished process. delete the table and ignore the result.
        return;
    }else{
        auto ret = Purification_table.equal_range(pr.id.ruleset_id);//Find all resource in qytpe/qid entangled with partner.
        //If the RuleSet has been deleted already, do not do anything.

        for (auto it=ret.first; it!=ret.second; it++) {
            if(it->second.id.rule_id == pr.id.rule_id && it->second.id.index == pr.id.index){
                //std::cout<<"Rule_id="<<pr.id.rule_id<<", index="<<pr.id.index<<"\n";
                //std::cout<<"node["<<parentAddress<<"] Rule found: Discard/Keep purification.\n";
                if(it->second.outcome == pr.outcome){
                    //Outcomes agreed. Keep the entangled pair.
                    std::cout<<"Unlocking and upgrading!\n";
                    Unlock_resource_and_upgrade_stage(pr.id.ruleset_id, pr.id.rule_id, pr.id.index);
                }else{
                    //Discard
                    //std::cout<<"node["<<parentAddress<<"] discaard ";
                    std::cout<<"Unlocking and discarding!\n";
                    Unlock_resource_and_discard(pr.id.ruleset_id, pr.id.rule_id, pr.id.index);
                }
                Purification_table.erase(it);
                return;
            }
        }
        traverseThroughAllProcesses2();
    }
}*/

void RuleEngine::Unlock_resource_and_upgrade_stage(unsigned long ruleset_id, unsigned long rule_id, int index) {
  // There should be better way
  // 0. this resorce update only update just one entanglement
  int partner_address;
  IStationaryQubit *qubit;
  unsigned long next_rule_id;
  if (rp.size() == 0) {
    return;
  }
  // 1. loop for ruleset and check where the target index
  for (auto it = rp.cbegin(); it != rp.cend(); ++it) {
    RuleSet *process = it->second.Rs;  // check ruleset
    if (process->ruleset_id == ruleset_id) {
      // 2. pick up proper rule inside the ruleset
      for (auto rule = process->cbegin(); rule != process->cend(); ++rule) {
        if ((*rule)->rule_index == rule_id) {  // here we can identify the rule of purification
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
              next_rule_id = (*rule)->next_rule_id;
              break;
            }
          }
        } else if ((*rule)->rule_index == next_rule_id) {
          (*rule)->addResource(partner_address, qubit);
          return;
        }
      }
    }
  }
  error("Resource is not successfully updated");
}

void RuleEngine::updateAppliedRule(IStationaryQubit *qubit, unsigned long rule_id) {
  // find there is a key
  auto iter = applied_rules.find(qubit);
  if (iter != applied_rules.end()) {
    // qubit key found;
    iter->second.push_back(rule_id);
  } else {
    std::vector<unsigned long> rule_vector = {rule_id};
    applied_rules.insert(std::make_pair(qubit, rule_vector));
  }
}

bool RuleEngine::checkAppliedRule(IStationaryQubit *qubit, unsigned long rule_id) {
  // check if the rule can be applied (target rule id is not in the applied rules)
  auto iter = applied_rules.find(qubit);
  if (iter != applied_rules.end()) {
    auto rules = applied_rules[qubit];
    auto rule_iter = std::find(rules.begin(), rules.end(), rule_id);
    if (rule_iter != rules.end()) {
      // this rule is already applied
      return false;
    } else {
      // not applied yet. you can go ahead to apply the rule
      return true;
    }
  } else {
    // completely fresh resource
    return true;
  }
  return false;
}

void RuleEngine::clearAppliedRule(IStationaryQubit *qubit) {
  // erase the record when the qubit is initialized
  auto iter = applied_rules.find(qubit);
  if (iter != applied_rules.end()) {
    applied_rules.erase(iter);
  } else {
    error("No rule record found at clearing");
  }
}

void RuleEngine::Unlock_resource_and_discard(unsigned long ruleset_id, unsigned long rule_id, int index) {
  bool ok = false;
  for (auto it = rp.cbegin(), next_it = rp.cbegin(); it != rp.cend(); it = next_it) {  // In a particular RuleSet
    next_it = it;
    ++next_it;
    if (it->second.Rs->ruleset_id == ruleset_id) {  // Find the corresponding ruleset.
      RuleSet *process = it->second.Rs;  // One Process. From top to bottom.
      for (auto rule = process->cbegin(), end = process->cend(); rule != end; rule++) {  // Traverse through rules
        if ((*rule)->rule_index == rule_id) {  // Find the corresponding rule.
          for (auto qubit_record = (*rule)->resources.begin(); qubit_record != (*rule)->resources.end(); ++qubit_record) {
            auto qubit = qubit_record->second;
            // std::cout<<".....node["<<qubit->second->node_address<<" qnic["<<qubit->second->qnic_index<<"]" << qubit->second<<"\n";
            if (qubit->action_index == index) {
              // Purification failed, discard resource.
              qubit->Unlock();
              QNIC_type qt = (QNIC_type)qubit->qnic_type;
              qubit->par("GOD_Xerror") = false;
              qubit->par("GOD_Zerror") = false;
              // remove from current rule
              (*rule)->resources.erase(qubit_record);
              freeConsumedResource(qubit->qnic_index, qubit, qt);  // Remove from entangled resource list.
              ok = true;
              return;
            }
          }
        }
      }
    }  // end if (check ruleset id)
  }
  if (!ok) {
    error("Discard: Resource in rule not found....");
  }
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
  bool internal = false;  // for internal hom?
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
      internal = true;
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
  int numFree = countFreeQubits_inQnic(Busy_OR_Free_QubitState_table[transmission_config.qnic_type], transmission_config.qnic_index);
  if (numFree > 0 && tracker_accessible.at(transmission_config.qnic_address)) {
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

  int numFree = countFreeQubits_inQnic(Busy_OR_Free_QubitState_table[transmission_config.qnic_type], transmission_config.qnic_index);
  if (numFree > 0) {
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
  if (countFreeQubits_inQnic(Busy_OR_Free_QubitState_table[QNIC_R], pk->getQnic_index()) == 0) {
    return;
  }

  int qubit_index;
  emt = new EmitPhotonRequest("EmitPhotonRequest(internal)");
  qubit_index = getOneFreeQubit_inQnic(Busy_OR_Free_QubitState_table[QNIC_R], pk->getQnic_index());
  Busy_OR_Free_QubitState_table[QNIC_R] = setQubitBusy_inQnic(Busy_OR_Free_QubitState_table[QNIC_R], pk->getQnic_index(), qubit_index);
  emt->setQubit_index(qubit_index);
  emt->setQnic_index(pk->getQnic_index());
  emt->setQnic_address(pk->getQnic_address());
  emt->setTrial(pk->getTrial());
  emt->setQnic_type(QNIC_R);

  if (pk->getNum_sent() == 0) {  // First shot!!!
    if (countFreeQubits_inQnic(Busy_OR_Free_QubitState_table[QNIC_R], pk->getQnic_index()) == 0)
      emt->setKind(STATIONARYQUBIT_PULSE_BOUND);  // First and last photon.
    else
      emt->setKind(STATIONARYQUBIT_PULSE_BEGIN);  // First photon
    scheduleAt(simTime() + pk->getTiming(), emt);
  } else {
    if (countFreeQubits_inQnic(Busy_OR_Free_QubitState_table[QNIC_R], pk->getQnic_index()) == 0)  // If no more free qubit
      emt->setKind(STATIONARYQUBIT_PULSE_END);  // last one
    else
      emt->setKind(0);  // Just a photon in a burst. Not the beginning, nor the end.
    scheduleAt(simTime() + pk->getInterval(), emt);
  }
  scheduleNextEmissionEvent(pk->getQnic_index(), pk->getQnic_address(), pk->getInterval(), pk->getTiming(), pk->getNum_sent(), true, pk->getTrial());
}

// This method is for qnic (not qnic_r, qnic_rp).
void RuleEngine::shootPhoton(SchedulePhotonTransmissionsOnebyOne *pk) {
  if (countFreeQubits_inQnic(Busy_OR_Free_QubitState_table[QNIC_E], pk->getQnic_index()) == 0) {
    return;
  }

  emt = new EmitPhotonRequest("EmitPhotonRequest");
  int qubit_index = getOneFreeQubit_inQnic(Busy_OR_Free_QubitState_table[QNIC_E], pk->getQnic_index());
  Busy_OR_Free_QubitState_table[QNIC_E] = setQubitBusy_inQnic(Busy_OR_Free_QubitState_table[QNIC_E], pk->getQnic_index(), qubit_index);
  emt->setQubit_index(qubit_index);
  emt->setQnic_address(pk->getQnic_address());
  emt->setTrial(pk->getTrial());
  emt->setQnic_index(pk->getQnic_index());
  emt->setQnic_type(QNIC_E);

  if (pk->getNum_sent() == 0) {
    if (countFreeQubits_inQnic(Busy_OR_Free_QubitState_table[QNIC_E], pk->getQnic_index()) == 0)
      emt->setKind(STATIONARYQUBIT_PULSE_BOUND);  // First and last photon.
    else
      emt->setKind(STATIONARYQUBIT_PULSE_BEGIN);  // First photon
    scheduleAt(simTime() + pk->getTiming(), emt);
  } else {
    if (countFreeQubits_inQnic(Busy_OR_Free_QubitState_table[QNIC_E], pk->getQnic_index()) == 0)
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

QubitStateTable RuleEngine::initializeQubitStateTable(QubitStateTable table, QNIC_type qnic_type) {
  int qnics = -1;
  switch (qnic_type) {
    case QNIC_E:
      qnics = number_of_qnics;
      break;
    case QNIC_R:
      qnics = number_of_qnics_r;
      break;
    case QNIC_RP:
      qnics = number_of_qnics_rp;
      break;
    default:
      error("Dont put qnic_type except for 0,1 and 2");
  }

  int index = 0;
  for (int i = 0; i < qnics; i++) {
    for (int x = 0; x < hardware_monitor->getQnicNumQubits(i, qnic_type); x++) {
      QubitAddr this_qubit = {parentAddress, i, x};
      // QubitAddr entangled_qubit = {-1, -1, -1};//Entangled address. The system may miss-track the actual entangled partner.  Initialized as -1 'cause no entangled qubits in the
      // beginning QubitAddr actual = {-1, -1, -1};//Entangled address. This is the true physically entangled partner. If there!=actual, then any operation on the qubit is a mess!
      // table[index] = {this_qubit,entangled_qubit,actual,false, simTime()};
      table[index] = {this_qubit, false, simTime()};  // Only stores which qubit is busy or free, and when it became busy.
      index++;
    }
  }
  return table;
}

// Just returns first index of free qubit.
int RuleEngine::getOneFreeQubit_inQnic(QubitStateTable table, int qnic_index) {
  int free_index = -1;
  for (auto it = table.cbegin(); it != table.cend(); ++it) {
    if (it->second.thisQubit_addr.qnic_index == qnic_index && it->second.isBusy == false) {
      free_index = it->second.thisQubit_addr.qubit_index;  // Just return the up-most qubit index in the qubit state table.
      break;
    }
  }
  if (free_index == -1)
    error("Free qubit not found in qnic. This should not happen because thd program checks it before this method. %d", qnic_index);  // This should not happen because
  return free_index;
}

int RuleEngine::countFreeQubits_inQnic(QubitStateTable table, int qnic_index) {
  int num_free = 0;
  for (auto it = table.cbegin(); it != table.cend(); ++it) {
    if (it->second.thisQubit_addr.qnic_index == qnic_index && !table[it->first].isBusy) {
      num_free++;  // count up free qubits in qnic[qnic_index]
    }
  }
  return num_free;
}

QubitStateTable RuleEngine::setQubitBusy_inQnic(QubitStateTable table, int qnic_index, int qubit_index) {
  for (auto it = table.cbegin(); it != table.cend(); ++it) {
    if (!it->second.isBusy && it->second.thisQubit_addr.qnic_index == qnic_index && it->second.thisQubit_addr.qubit_index == qubit_index) {
      table[it->first].isBusy = true;
      break;
    } else if (it->second.isBusy == true && it->second.thisQubit_addr.qnic_index == qnic_index && it->second.thisQubit_addr.qubit_index == qubit_index) {
      error("Trying to set a busy qubit busy. Only free qubits can do that. Something is wrong...");
    }
  }
  return table;
}

QubitStateTable RuleEngine::setQubitFree_inQnic(QubitStateTable table, int qnic_index, int qubit_index) {
  for (auto it = table.cbegin(); it != table.cend(); ++it) {
    // std::cout<<it->first<<" table = "<<table[it->first].isBusy<<"\n";
    if (it->second.isBusy && it->second.thisQubit_addr.qnic_index == qnic_index && it->second.thisQubit_addr.qubit_index == qubit_index) {
      table[it->first].isBusy = false;
      break;
    } else if (!it->second.isBusy && it->second.thisQubit_addr.qnic_index == qnic_index && it->second.thisQubit_addr.qubit_index == qubit_index) {
      error("Trying to set a free qubit free. Only busy qubits can do that. Something is wrong... ");
    }
  }
  return table;
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

void RuleEngine::updateResources_EntanglementSwapping(swapping_result swapr) {
  // swapper believe previous BSM was succeeded.
  // These are new partner's info

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

  // qubit with address Addr was shot in nth time. This list is ordered from old to new.
  StationaryQubit *qubit = provider.getStationaryQubit(qnic_index, qubit_index, qnic_type);
  // check
  if (operation_type == 0) {
    // do nothing
  } else if (operation_type == 1) {
    // do X
    qubit->X_gate();
  } else if (operation_type == 2) {
    qubit->Z_gate();
  } else {
    error("Something went wrong. This operation type isn't recorded!");
  }

  if (qubit->entangled_partner == nullptr && qubit->Density_Matrix_Collapsed(0, 0).real() == -111 && !qubit->no_density_matrix_nullptr_entangled_partner_ok) {
    // std::cout << qubit << ", node[" << qubit->node_address << "] from qnic[" << qubit->qnic_index << "]\n";
    error("RuleEngine. Entanglement swapping went wrong");
  }
  // FOR DEBUGGING
  if (qubit->entangled_partner != nullptr) {
    if (qubit->entangled_partner->entangled_partner == nullptr) {
      error("1. Entanglement tracking is not doing its job. in update resource E.S.");
    }
    if (qubit->entangled_partner->entangled_partner != qubit) {
      error("2. Entanglement tracking is not doing its job. in update resource E.S.");
    }
  }

  bool promoted = false;
  // Promote entanglement from this rule to the next rule
  // 1. erase qubit from the privious rule (Entanglement Swapping)
  // 1.1 take identifiers
  unsigned long ruleset_id = swapr.id.ruleset_id;
  unsigned long rule_id = swapr.id.rule_id;
  unsigned long next_rule_id;
  // this routine can be a function in the ruleset.
  if (rp.size() == 0) {
    return;
  }
  for (auto iter = rp.cbegin(); iter != rp.cend(); iter++) {
    RuleSet *ruleset = iter->second.Rs;
    EV << ruleset->ruleset_id << " : " << ruleset_id << "\n";
    if (ruleset->ruleset_id == ruleset_id) {
      for (auto rule = ruleset->cbegin(); rule != ruleset->cend(); rule++) {
        if ((*rule)->rule_index == rule_id) {  // rule identified
          // remove qubit from previous rule
          for (auto qubit_record = (*rule)->resources.cbegin(); qubit_record != (*rule)->resources.cend(); qubit_record++) {
            auto target_qubit = qubit_record->second;
            if (target_qubit == qubit) {
              (*rule)->resources.erase(qubit_record);
              next_rule_id = (*rule)->next_rule_id;
              break;
            }
          }
        } else if ((*rule)->rule_index == next_rule_id) {
          // next rule id is properly updated
          (*rule)->addResource(new_partner, qubit);
          promoted = true;
          return;
        }
      }
    }
  }
  if (!promoted) {
    error("The qubit is not promoted from entanglement swapping to the next rule");
  }
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
  StationaryQubit *qubit = provider.getStationaryQubit(qnic_index, qubit_index, qnic_type);

  if (operation_type == 0) {
    // nothing
  } else if (operation_type == 1) {
    // do Z
    qubit->Z_gate();
  } else if (operation_type == 2) {
    // do X
    qubit->Z_gate();
  } else if (operation_type == 3) {
    // do XZ
    qubit->Z_gate();
    qubit->X_gate();
  } else {
    error("something error happened! This operation type doesn't recorded!");
  }

  if (qubit->entangled_partner == nullptr && qubit->Density_Matrix_Collapsed(0, 0).real() == -111 && !qubit->no_density_matrix_nullptr_entangled_partner_ok) {
    std::cout << qubit << ", node[" << qubit->node_address << "] from qnic[" << qubit->qnic_index << "]\n";
    error("RuleEngine. Ebit succeed. but wrong");
  }
  // first delete old record
  bell_pair_store.eraseQubit(qubit);

  // Make this qubit available for rules
  if (qubit->isAllocated()) {
    error("qubit is already allocated");
  }
  if (qubit->isLocked()) {
    error("qubit is locked");
  }
  bell_pair_store.insertEntangledQubit(new_partner, qubit);
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

  // if the HoM is external
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
      StationaryQubit *qubit = provider.getStationaryQubit(qnic_index, it->second.qubit_index, qnic_type);

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
      bell_pair_store.insertEntangledQubit(neighborQNodeAddress, qubit);
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
  realtime_controller->ReInitialize_StationaryQubit(qnic_index, qubit_index, qnic_type, false);
  Busy_OR_Free_QubitState_table[qnic_type] = setQubitFree_inQnic(Busy_OR_Free_QubitState_table[qnic_type], qnic_index, qubit_index);
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
  if (!(rp.size() > 0)) {  // If no ruleset running, do nothing.
    return;
  }
  // If there are running rulesets, then try to allocate resource to it
  for (auto it = rp.cbegin(), next_it = rp.cbegin(); it != rp.cend(); it = next_it) {  // In a particular RuleSet
    next_it = it;
    ++next_it;
    // take the first ruleset
    RuleSet *process = it->second.Rs;  // One Process. From top to bottom.

    if (process->empty()) {
      error("RuleSet with no Rule found. Probably not what you want!");
    }
    int assigned = 0;
    for (auto rule = process->cbegin(); rule != process->cend(); rule++) {
      // 1. loop for all rulesets and take the partners for each rule
      for (int action_partner : (*rule)->action_partners) {
        // 2. take available Bell pairs between action partner
        // range contains the begin and end iterators of entangled qubits with the specified qnic_type, qnic_index and partner addr.
        auto range = bell_pair_store.getBellPairsRange((QNIC_type)qnic_type, qnic_index, action_partner);
        for (auto it = range.first; it != range.second; ++it) {
          auto qubit = it->second;
          // 3. if the qubit is not allocated yet, and the qubit has not been allocated to this rule,
          // if the qubit has already been assigned to the rule, the qubit is not allocatable to that rule
          bool allocatable = checkAppliedRule(qubit, (*rule)->rule_index);
          // EV<<" allocatable: "<<allocatable<<" : "<<qubit<<"action_partner:"<<action_partner<<"\n";
          if (!qubit->isAllocated() && allocatable) {
            if (qubit->entangled_partner == nullptr && qubit->Density_Matrix_Collapsed(0, 0).real() == -111 && !qubit->no_density_matrix_nullptr_entangled_partner_ok) {
              error("Freshing qubit wrong");
            }
            // 5. increment the assined counter and set allocated flag
            assigned++;
            qubit->Allocate();
            updateAppliedRule(qubit, (*rule)->rule_index);
            (*rule)->addResource(action_partner, qubit);
          }
        }
      }
    }
  }
}

void RuleEngine::traverseThroughAllProcesses2() {
  int number_of_process = rp.size();  // Number of running processes (in all QNICs).

  if (number_of_process == 0) {
    return;
  }

  for (auto it = rp.cbegin(), next_it = rp.cbegin(); it != rp.cend(); it = next_it) {
    next_it = it;
    ++next_it;
    RuleSet *process = it->second.Rs;  // One Process. From top to bottom.
    for (auto rule = process->cbegin(), end = process->cend(); rule != end; rule++) {
      bool process_done = false;
      bool terminate_this_rule = false;

      while (true) {
        if (!((*rule)->resources.size() > 0)) {
          break;  // No more resource left for now.
        }

        cPacket *pk = (*rule)->checkrun(this);  // Do something on qubits entangled with resource_entangled_with_address.

        if (pk != nullptr) {
          // Feedback to another node required
          if (dynamic_cast<LinkTomographyResult *>(pk) != nullptr) {
            // The cPacket *pk is a single packet forwarded to the neighbor. But this node's HardwareMonitor also needs to store the result.
            LinkTomographyResult *pk_t = check_and_cast<LinkTomographyResult *>(pk);
            LinkTomographyResult *pk_for_self = pk_t->dup();
            pk_for_self->setPartner_address(pk_t->getDestAddr());
            pk_for_self->setDestAddr(pk_t->getSrcAddr());
            if (pk_t->getPartner_address() == pk_for_self->getPartner_address()) {
              error("Wrong");
            }
            send(pk, "RouterPort$o");
            send(pk_for_self, "RouterPort$o");
          } else if (dynamic_cast<PurificationResult *>(pk) != nullptr) {
            PurificationResult *pkt = check_and_cast<PurificationResult *>(pk);
            pkt->setSrcAddr(parentAddress);
            PurificationResult *pk_for_self = pkt->dup();
            pk_for_self->setDestAddr(parentAddress);
            send(pkt, "RouterPort$o");
            send(pk_for_self, "RouterPort$o");
          } else if (dynamic_cast<DoublePurificationResult *>(pk) != nullptr) {
            DoublePurificationResult *pkt = check_and_cast<DoublePurificationResult *>(pk);
            pkt->setSrcAddr(parentAddress);
            DoublePurificationResult *pk_for_self = pkt->dup();
            pk_for_self->setDestAddr(parentAddress);
            send(pkt, "RouterPort$o");
            send(pk_for_self, "RouterPort$o");
          } else if (dynamic_cast<DS_DoublePurificationResult *>(pk) != nullptr) {
            DS_DoublePurificationResult *pkt = check_and_cast<DS_DoublePurificationResult *>(pk);
            pkt->setSrcAddr(parentAddress);
            DS_DoublePurificationResult *pk_for_self = pkt->dup();
            pk_for_self->setDestAddr(parentAddress);
            send(pkt, "RouterPort$o");
            send(pk_for_self, "RouterPort$o");
          } else if (dynamic_cast<DS_DoublePurificationSecondResult *>(pk) != nullptr) {
            DS_DoublePurificationSecondResult *pkt = check_and_cast<DS_DoublePurificationSecondResult *>(pk);
            pkt->setSrcAddr(parentAddress);
            DS_DoublePurificationSecondResult *pk_for_self = pkt->dup();
            pk_for_self->setDestAddr(parentAddress);
            send(pkt, "RouterPort$o");
            send(pk_for_self, "RouterPort$o");
          } else if (dynamic_cast<SwappingResult *>(pk) != nullptr) {
            SwappingResult *pkt = check_and_cast<SwappingResult *>(pk);
            EV << "done swapping at " << parentAddress << " left: " << pkt->getLeft_Dest() << " right: " << pkt->getRight_Dest() << "\n";
            // here this packet goes to two destination.
            // one is left node the other is right node.
            // only swapper knows which is left and right, but qnodes don't

            // packet for left node
            SwappingResult *pkt_for_left = new SwappingResult("SwappingResult(Left)");
            pkt_for_left->setRuleSet_id(pkt->getRuleSet_id());
            pkt_for_left->setRule_id(pkt->getRule_id());
            pkt_for_left->setKind(5);  // cyan
            pkt_for_left->setDestAddr(pkt->getLeft_Dest());
            pkt_for_left->setSrcAddr(parentAddress);
            pkt_for_left->setOperation_type(pkt->getOperation_type_left());
            pkt_for_left->setMeasured_qubit_index(pkt->getMeasured_qubit_index_left());
            pkt_for_left->setNew_partner(pkt->getNew_partner_left());
            pkt_for_left->setNew_partner_qnic_index(pkt->getNew_partner_qnic_index_left());
            pkt_for_left->setNew_partner_qnic_address(pkt->getNew_partner_qnic_address_left());
            pkt_for_left->setNew_partner_qnic_type(pkt->getNew_partner_qnic_type_left());

            // packet for right node
            SwappingResult *pkt_for_right = new SwappingResult("SwappingResult(Right)");
            pkt_for_right->setRuleSet_id(pkt->getRuleSet_id());
            pkt_for_right->setRule_id(pkt->getRule_id());
            pkt_for_right->setKind(5);  // cyan
            pkt_for_right->setDestAddr(pkt->getRight_Dest());
            pkt_for_right->setSrcAddr(parentAddress);
            pkt_for_right->setOperation_type(pkt->getOperation_type_right());
            pkt_for_right->setMeasured_qubit_index(pkt->getMeasured_qubit_index_right());
            pkt_for_right->setNew_partner(pkt->getNew_partner_right());
            pkt_for_right->setNew_partner_qnic_index(pkt->getNew_partner_qnic_index_right());
            pkt_for_right->setNew_partner_qnic_address(pkt->getNew_partner_qnic_address_right());
            pkt_for_right->setNew_partner_qnic_type(pkt->getNew_partner_qnic_type_right());

            send(pkt_for_left, "RouterPort$o");
            send(pkt_for_right, "RouterPort$o");
          } else if (dynamic_cast<SimultaneousSwappingResult *>(pk) != nullptr) {
            SimultaneousSwappingResult *pkt = check_and_cast<SimultaneousSwappingResult *>(pk);
            EV << "done swapping at " << parentAddress << "\n";

            // packet for left node
            SimultaneousSwappingResult *pkt_for_initiator = new SimultaneousSwappingResult("SimultaneousSwappingResult(Left)");
            pkt_for_initiator->setKind(5);  // cyan
            pkt_for_initiator->setDestAddr(pkt->getInitiator_Dest());
            pkt_for_initiator->setSrcAddr(parentAddress);
            pkt_for_initiator->setOperation_type(pkt->getOperation_type_left());
            pkt_for_initiator->setMeasured_qubit_index(pkt->getMeasured_qubit_index_left());
            pkt_for_initiator->setNew_partner(pkt->getNew_partner_left());
            pkt_for_initiator->setNew_partner_qnic_index(pkt->getNew_partner_qnic_index_left());
            pkt_for_initiator->setNew_partner_qnic_address(pkt->getNew_partner_qnic_address_left());
            pkt_for_initiator->setNew_partner_qnic_type(pkt->getNew_partner_qnic_type_left());

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

            send(pkt_for_initiator, "RouterPort$o");
            send(pkt_for_responder, "RouterPort$o");
          }

          else if (dynamic_cast<Error *>(pk) != nullptr) {
            Error *err = check_and_cast<Error *>(pk);
            error(err->getError_text());
            delete pk;
          } else if (dynamic_cast<ConditionNotSatisfied *>(pk) != nullptr) {
            // Condition does not meet. Go to next rule. e.g. Fidelity is good enough by doing purification. Next could be swap.
            delete pk;
            break;
          } else {
            error("Unknown return packet from action.");
            delete pk;
          }
        } else {
          error("Pk nullptr");
        }

        // std::cout<<"Is it done?";
        process_done = (*rule)->checkTerminate();  // The entire process is done. e.g. enough measurement for tomography.
        if (process_done) {  // Delete rule set if done
          // std::cout<<"!!!!!!!!!!!!!!!!!!!!! TERMINATING!!!!!!!!!!!!!!!!!!!!!!!!!";
          std::cout << "RuleSet_id=" << process->ruleset_id << "\n";
          // todo:Also need to deallocate resources!!!!!!!!!!!!not implemented yet.
          delete process;
          rp.erase(it);  // Erase rule set from map.
          terminate_this_rule = true;  // Flag to get out from outer loop
          std::cout << "node[" << parentAddress << "]:RuleSet deleted.\n";
          EV << "node[" << parentAddress << "]:RuleSet deleted.\n";
          break;  // get out from this for loop.
        }

      }  // While
      if (process_done) {
        break;
      }
    }  // For
  }  // For loop
}

void RuleEngine::freeConsumedResource(int qnic_index /*Not the address!!!*/, IStationaryQubit *qubit, QNIC_type qnic_type) {
  realtime_controller->ReInitialize_StationaryQubit(qnic_index, qubit->par("stationaryQubit_address"), qnic_type, true);
  Busy_OR_Free_QubitState_table[qnic_type] = setQubitFree_inQnic(Busy_OR_Free_QubitState_table[qnic_type], qnic_index, qubit->par("stationaryQubit_address"));
  clearAppliedRule(qubit);
  bell_pair_store.eraseQubit(qubit);
}

}  // namespace modules
}  // namespace quisp

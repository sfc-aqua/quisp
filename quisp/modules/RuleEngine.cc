/** \file RuleEngine.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/04/04
 *
 *  \brief RuleEngine
 */

#include "RuleEngine.h"
#include <modules/HardwareMonitor.h>
#include <fstream>

namespace quisp {
namespace modules {

Define_Module(RuleEngine);

using namespace rules;

void RuleEngine::initialize() {
  // HardwareMonitor's neighbor table is checked in the initialization stage of the simulation
  // This assumes the topology never changes throughout the simulation.
  // If dynamic change in topology is required, recoding this is needed.
  cModule *hm = getParentModule()->getSubmodule("hm");
  hardware_monitor = check_and_cast<HardwareMonitor *>(hm);
  cModule *rt = getParentModule()->getSubmodule("rt");
  realtime_controller = check_and_cast<RealTimeController *>(rt);  // Just for qubit color update and Pauli error elimination
  // TODO CHECK: Is this doable?
  cModule *rd = getParentModule()->getSubmodule("rd");
  routingdaemon = check_and_cast<RoutingDaemon *>(rd);

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

  /*Initialize resource list by Age for the actual use of qubits in operations*/
  allResources = new qnicResources[QNIC_N];
  allResources[QNIC_E] = new EntangledPairs[number_of_qnics];
  allResources[QNIC_R] = new EntangledPairs[number_of_qnics_r];
  allResources[QNIC_RP] = new EntangledPairs[number_of_qnics_rp];

  // running_processes = new RuleSetPtr[QNIC_N];//One process per QNIC for now. No multiplexing.
  // WATCH(assigned);
}

void RuleEngine::handleMessage(cMessage *msg) {
  traverseThroughAllProcesses2();  // New resource added to QNIC with qnic_type qnic_index.
  header *pk = check_and_cast<header *>(msg);

  if (dynamic_cast<EmitPhotonRequest *>(msg) != nullptr) {  // From self.
    EmitPhotonRequest *pk = check_and_cast<EmitPhotonRequest *>(msg);
    cModule *rtc = getParentModule()->getSubmodule("rt");
    RealTimeController *realtime_controller = check_and_cast<RealTimeController *>(rtc);

    // Terminate emission if trial is over already (e.g. the neighbor ran out of free qubits and the BSA already returned the results)
    if (burstTrial_outdated(pk->getTrial(), pk->getQnic_address())) {
      // Terminate bursting if this trial has finished already.
      delete msg;
      return;
    } else {
      // Index the qnic and qubit index to the tracker.
      int qnic_address = pk->getQnic_address();
      QubitAddr_cons Addr(-1, pk->getQnic_index(), pk->getQubit_index());
      int nth_shot = tracker[qnic_address].size();

      // qubit with address Addr was shot in nth time. This list is ordered from old to new.
      tracker[qnic_address].insert(std::make_pair(nth_shot, Addr));
      int new_nth_shot = tracker[qnic_address].size();
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
    // std::cout<<"(if internal)The finished qnic["<<pk->getInternal_qnic_index()<<"] with address = "<<pk->getInternal_qnic_address()<<" has emitted
    // tracker["<<pk->getInternal_qnic_address()<<"].size() = "<<tracker[pk->getInternal_qnic_address()].size()<<" photons \n"; Updates free/busy of qubits, and also adds
    // successfully entangled qubits as resources.
    freeFailedQubits_and_AddAsResource(pk->getSrcAddr(), pk->getInternal_qnic_address(), pk->getInternal_qnic_index(), pk_result);

    // Clear tracker every end of burst trial. This keeps which qubit was fired first, second, third and so on only for that trial.
    clearTrackerTable(pk->getSrcAddr(), pk->getInternal_qnic_address());

    // Second, schedule the next burst by referring to the received timing information.
    int qnic_address, qnic_type;
    int qnic_index, neighborQNodeAddress;
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

    // for (EntangledPairs::iterator it =  allResources[qnic_type][qnic_index].begin(); it != allResources[qnic_type][qnic_index].end(); it++)
    //    EV << it->first << " => " << it->second << '\n';
    // EV<< "****************************************\n";

    if (terminated_qnic[qnic_address] == true) {
      // std::cout<<"NOT ANY MORE qnic["<<qnic_address<<"] in node["<<parentAddress<<"]";
      return;
    } else if (pk->getInternal_qnic_index() == -1) {  // Schedule next burst. MIM, or the other node without internal HoM of MM
      EV << "This BSA request is non-internal\n";
      scheduleFirstPhotonEmission(pk, QNIC_E);
    } else {
      EV << "This BSA request is internal\n";
      scheduleFirstPhotonEmission(pk, QNIC_R);
    }
  }

  else if (dynamic_cast<SchedulePhotonTransmissionsOnebyOne *>(msg) != nullptr) {
    SchedulePhotonTransmissionsOnebyOne *pk = check_and_cast<SchedulePhotonTransmissionsOnebyOne *>(msg);
    EV << getQNode()->getFullName() << ": Photon shooting is from qnic[" << pk->getQnic_index() << "] with address=" << pk->getQnic_address();

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
    BSMtimingNotifier *pk = check_and_cast<BSMtimingNotifier *>(msg);
    if (pk->getInternal_qnic_index() == -1) {  // MIM, or the other node without internnal HoM of MM
      EV << "This BSA request is non-internal\n";
      scheduleFirstPhotonEmission(pk, QNIC_E);
    } else {
      EV << "This BSA request is internal\n";
      scheduleFirstPhotonEmission(pk, QNIC_R);
    }
  } else if (dynamic_cast<EPPStimingNotifier *>(msg) != nullptr) {
    bubble("EPPS");
    EPPStimingNotifier *pk = check_and_cast<EPPStimingNotifier *>(msg);
  } else if (dynamic_cast<LinkTomographyRuleSet *>(msg) != nullptr) {
    // Received a tomography rule set.
    LinkTomographyRuleSet *pk = check_and_cast<LinkTomographyRuleSet *>(msg);
    // std::cout<<"node["<<parentAddress<<"] !!!!!!!!!!Ruleset reveid!!!!!!!!! ruleset id = "<<pk->getRuleSet()->ruleset_id<<"\n";
    process p;
    p.ownner_addr = pk->getRuleSet()->owner;
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
    // std::cout<<"!!!!Purification result reveid!!! node["<<parentAddress<<"]\n";
    PurificationResult *pkt = check_and_cast<PurificationResult *>(msg);
    // std::cout<<"Presult from node["<<pkt->getSrcAddr()<<"]\n";
    process_id purification_id;
    purification_result pr;
    purification_id.ruleset_id = pkt->getRuleset_id();
    purification_id.rule_id = pkt->getRule_id();
    purification_id.index = pkt->getAction_index();
    pr.id = purification_id;
    pr.outcome = pkt->getOutput_is_plus();
    // StationaryQubit *q = check_and_cast<StationaryQubit *>(pkt->getEntangled_with());
    // std::cout<<"Purification result is from node["<<pkt->getSrcAddr()<<"] rid="<< pkt->getRuleset_id()<<"Must be qnic["<<my_qnic_index<<" type="<<my_qnic_type<<"\n";
    // std::cout<<"Locked one is "<<pkt->getEntangled_with()<<"in node["<<q->node_address<<"] \n";
    storeCheck_Purification_Agreement(pr);
  } else if (dynamic_cast<DoublePurificationResult *>(msg) != nullptr) {
    // std::cout<<"!!!!Purification result reveid!!! node["<<parentAddress<<"]\n";
    DoublePurificationResult *pkt = check_and_cast<DoublePurificationResult *>(msg);
    // std::cout<<"Presult from node["<<pkt->getSrcAddr()<<"]\n";
    process_id purification_id;
    Doublepurification_result pr;
    purification_id.ruleset_id = pkt->getRuleset_id();
    purification_id.rule_id = pkt->getRule_id();
    purification_id.index = pkt->getAction_index();
    pr.id = purification_id;
    pr.Xpurification_outcome = pkt->getXOutput_is_plus();
    pr.Zpurification_outcome = pkt->getZOutput_is_plus();
    // StationaryQubit *q = check_and_cast<StationaryQubit *>(pkt->getEntangled_with());
    // std::cout<<"Purification result is from node["<<pkt->getSrcAddr()<<"] rid="<< pkt->getRuleset_id()<<"Must be qnic["<<my_qnic_index<<" type="<<my_qnic_type<<"\n";
    // std::cout<<"Locked one is "<<pkt->getEntangled_with()<<"in node["<<q->node_address<<"] \n";
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
    // here next add resources
    int src = pkt->getSrcAddr();
    int dest = pkt->getDestAddr();
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
  } else if (dynamic_cast<InternalRuleSetForwarding *>(msg) != nullptr) {
    InternalRuleSetForwarding *pkt = check_and_cast<InternalRuleSetForwarding *>(msg);
    // add actual process
    process p;
    p.ownner_addr = pkt->getRuleSet()->owner;
    // for check
    p.Rs = pkt->getRuleSet();
    // here swappers got swapping ruleset with internal packet
    // What we have to do here is
    // 1. Add process (RuleSet) of swapping to running process
    // 2. Run it
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
  } else if (dynamic_cast<InternalRuleSetForwarding_Application *>(msg) != nullptr) {
    InternalRuleSetForwarding_Application *pkt = check_and_cast<InternalRuleSetForwarding_Application *>(msg);
    // FIXME This is really naive implementation.
    if (pkt->getApplication_type() == 0) {
      EV << "got application!!!!!!!!!!!!!!!!! at " << parentAddress << "\n";
      // Received a tomography rule set.
      InternalRuleSetForwarding_Application *pk = check_and_cast<InternalRuleSetForwarding_Application *>(msg);
      // std::cout<<"node["<<parentAddress<<"] !!!!!!!!!!Ruleset reveid!!!!!!!!! ruleset id = "<<pk->getRuleSet()->ruleset_id<<"\n";
      process p;
      p.ownner_addr = pkt->getRuleSet()->owner;
      p.Rs = pkt->getRuleSet();
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

void RuleEngine::storeCheck_Purification_Agreement(purification_result pr) {
  // std::cout<<"storeCheck_Purification_Agreement: "<<pr.id.ruleset_id<<" ";
  // std::cout<<"rp size = "<<rp.size()<<"\n";

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
    auto ret = Purification_table.equal_range(pr.id.ruleset_id);
    // If the RuleSet has been deleted already, do not do anything.

    for (auto it = ret.first; it != ret.second; it++) {
      if (it->second.id.rule_id == pr.id.rule_id && it->second.id.index == pr.id.index) {
        // std::cout<<"Rule_id="<<pr.id.rule_id<<", index="<<pr.id.index<<"\n";
        // std::cout<<"node["<<parentAddress<<"] Rule found: Discard/Keep purification.\n";
        if (it->second.outcome == pr.outcome) {
          // Outcomes agreed. Keep the entangled pair.
          // std::cout<<"Unlocking and upgrading!\n";
          Unlock_resource_and_upgrade_stage(pr.id.ruleset_id, pr.id.rule_id, pr.id.index);
        } else {
          // Discard
          // std::cout<<"node["<<parentAddress<<"] discaard ";
          // std::cout<<"Unlocking and discarding!\n";
          Unlock_resource_and_discard(pr.id.ruleset_id, pr.id.rule_id, pr.id.index);
        }
        Purification_table.erase(it);
        return;
      }
    }
    // New data.
    // std::cout<<"New data arrived. Need to keep the outcome of rulset_id="<<pr.id.ruleset_id<<" Rule_id="<<pr.id.rule_id<<", index="<<pr.id.index<<"\n";
    Purification_table.insert(std::make_pair(pr.id.ruleset_id, pr));  // Otherwise, if data has not been found, store it.
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
    // std::cout<<"New data arrived. Need to keep the outcome of rulset_id="<<pr.id.ruleset_id<<" Rule_id="<<pr.id.rule_id<<", index="<<pr.id.index<<"\n";
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
          // std::cout<<"Unlocking and upgrading!\n";
          Unlock_resource_and_upgrade_stage(pr.id.ruleset_id, pr.id.rule_id, pr.id.index);
        } else {
          // Discard
          // std::cout<<"node["<<parentAddress<<"] discaard ";
          // std::cout<<"Unlocking and discarding!\n";
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

void RuleEngine::Unlock_resource_and_upgrade_stage(unsigned long ruleset_id, int rule_id, int index) {
  bool ok = false;
  for (auto it = rp.cbegin(), next_it = rp.cbegin(); it != rp.cend(); it = next_it) {  // In a particular RuleSet
    next_it = it;
    ++next_it;
    if (it->second.Rs->ruleset_id == ruleset_id) {  // Find the corresponding ruleset.
      RuleSet *process = it->second.Rs;  // One Process. From top to bottom.
      int partner_size = process->entangled_partner.size();
      for (int i = 0; i < partner_size; i++) {
        int address_entangled_with = process->entangled_partner[i];
        for (auto rule = process->cbegin(), end = process->cend(); rule != end; rule++) {  // Traverse through rules
          if ((*rule)->rule_index == rule_id) {  // Find the corresponding rule.
            // emit(actual_resSignal, (*rule)->resources.size());
            for (auto qubit = (*rule)->resources.begin(); qubit != (*rule)->resources.end(); ++qubit) {
              if (qubit->second->action_index == index) {
                // Correct resource found! Need to unlock and stage up the resource to the next rule.
                qubit->second->Unlock();
                // std::cout<<"[Upgrade Unlock] "<<qubit->second<<" in node["<<qubit->second->node_address<<"]\n";
                StationaryQubit *q = qubit->second;
                (*rule)->resources.erase(qubit);  // Erase this from resource list
                rule++;
                if (rule == end) {
                  error("Rule came to end after operation (e.g. purification) success");
                }
                // int rsc_index = (*rule)->resources.size();
                //(*rule)->resources.insert(std::make_pair(rsc_index, q));
                (*rule)->addResource(address_entangled_with, q);
                ok = true;
                return;
              }
            }
          }
        }
      }
    }
  }
  if (!ok) {
    error("Upgrade: Resource in rule not found....");
  }
}

void RuleEngine::Unlock_resource_and_discard(unsigned long ruleset_id, int rule_id, int index) {
  bool ok = false;
  for (auto it = rp.cbegin(), next_it = rp.cbegin(); it != rp.cend(); it = next_it) {  // In a particular RuleSet
    next_it = it;
    ++next_it;
    if (it->second.Rs->ruleset_id == ruleset_id) {  // Find the corresponding ruleset.
      RuleSet *process = it->second.Rs;  // One Process. From top to bottom.
      for (auto rule = process->cbegin(), end = process->cend(); rule != end; rule++) {  // Traverse through rules
        if ((*rule)->rule_index == rule_id) {  // Find the corresponding rule.
          for (auto qubit = (*rule)->resources.begin(); qubit != (*rule)->resources.end(); ++qubit) {
            // std::cout<<".....node["<<qubit->second->node_address<<" qnic["<<qubit->second->qnic_index<<"]" << qubit->second<<"\n";
            if (qubit->second->action_index == index) {
              // Correct resource found! Need to unlock and stage up the resource to the next rule.
              // qubit->second->Unlock();
              // std::cout<<"Purification Failed Discard "<<qubit->second<<"\n";
              QNIC_type qt = (QNIC_type)qubit->second->qnic_type;
              qubit->second->par("GOD_Xerror") = false;
              qubit->second->par("GOD_Zerror") = false;
              // std::cout<<"node["<<qubit->second->node_address<<"]"<<qubit->second<<" X = "<<qubit->second->par("GOD_Xerror").str()<<" Z =
              // "<<qubit->second->par("GOD_Zerror").str()<<"\n"; std::cout<<"Rule id = "<<qubit->second->rs<<"\n"; std::cout<<"Freeing
              // qnic["<<qubit->second->qnic_index<<"]"<<"qnic type="<<qt<<" btw addr="<<qubit->second->qnic_address<<"\n"; std::cout<<"[Discard Unlock] "<<qubit->second<<" in
              // node["<<qubit->second->node_address<<"]\n";

              freeConsumedResource(qubit->second->qnic_index, qubit->second, qt);  // Remove from entangled resource list.
              (*rule)->resources.erase(qubit);  // Erase this from resource list                                                               ok = true;
              return;
            }
          }
        }
      }
    }
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
  SchedulePhotonTransmissionsOnebyOne *st = new SchedulePhotonTransmissionsOnebyOne("SchedulePhotonTransmissionsOneByOne(First)");
  if (ntable.empty())  // Just do this once, unless the network changes during the simulation.
    ntable = hardware_monitor->passNeighborTable();  // Get neighbor table from Hardware Manager: neighbor address--> InterfaceInfo.

  int destAddr = pk->getSrcAddr();  // The destination is where the request is generated (source of stand-alone or internal BSA node).
  int qnic_index, qnic_address;
  int numFree;
  cModule *qnic_pointer;

  switch (qnic_type) {
    case QNIC_E: {
      InterfaceInfo inf = getInterface_toNeighbor(destAddr);
      qnic_index = inf.qnic.index;
      qnic_address = inf.qnic.address;
    }  // inf is not defined beyound this point
      numFree =
          countFreeQubits_inQnic(Busy_OR_Free_QubitState_table[QNIC_E], qnic_index);  // Refer the qubit state table. Check number of free qubits of qnic with index qnic_index.
      break;
    case QNIC_R:
      qnic_address = pk->getInternal_qnic_address();
      qnic_index = pk->getInternal_qnic_index();  // If the BSA node is in this node, then obviously it is not in the neighbor table, 'cause it is inside it self. In that case, the
                                                  // gate index is stored in the packet.
      numFree = countFreeQubits_inQnic(Busy_OR_Free_QubitState_table[QNIC_R], qnic_index);  // Same as above, except the table is managed independently.
      st->setInternal_hom(1);  // Mark request that the request is for internal BSA node. Default is 0.
      break;
    case QNIC_RP:
      error("This is not implemented yet");
      break;
    default:
      error("Only 3 qnic types are currently recognized....");
  }

  st->setQnic_index(qnic_index);
  st->setQnic_address(qnic_address);
  EV << getQNode()->getFullName() << ": First photon shooting is from qnic[" << qnic_index << "] with address=" << qnic_address;
  st->setInterval(pk->getInterval());
  st->setTiming(pk->getTiming_at());
  st->setTrial(qnic_burst_trial_counter[qnic_address]);  // Keeps the burst counter. First burst index is 0.

  if (numFree > 0)
    scheduleAt(simTime(), st);
  else {
    delete st;
    // error("This needs to be implemented (Is this needed if entangled particles get consumed properly?). When QNIC buffer is all busy in the 1st shot...");
    // All qubits are free when BSAtimingRequest is received by the node.
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
  EV << pk->getQnic_address() << ", " << pk->getQnic_index();
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

RuleEngine::QubitStateTable RuleEngine::initializeQubitStateTable(QubitStateTable table, QNIC_type qnic_type) {
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
    if (it->second.thisQubit_addr.qnic_index == qnic_index && table[it->first].isBusy == false) {
      num_free++;  // count up free qubits in qnic[qnic_index]
    }
  }
  return num_free;
}

RuleEngine::QubitStateTable RuleEngine::setQubitBusy_inQnic(QubitStateTable table, int qnic_index, int qubit_index) {
  for (auto it = table.cbegin(); it != table.cend(); ++it) {
    if (it->second.isBusy == false && it->second.thisQubit_addr.qnic_index == qnic_index && it->second.thisQubit_addr.qubit_index == qubit_index) {
      table[it->first].isBusy = true;
      break;
    } else if (it->second.isBusy == true && it->second.thisQubit_addr.qnic_index == qnic_index && it->second.thisQubit_addr.qubit_index == qubit_index) {
      error("Trying to set a busy qubit busy. Only free qubits can do that. Something is wrong...");
    }
  }
  return table;
}

RuleEngine::QubitStateTable RuleEngine::setQubitFree_inQnic(QubitStateTable table, int qnic_index, int qubit_index) {
  for (auto it = table.cbegin(); it != table.cend(); ++it) {
    // std::cout<<it->first<<" table = "<<table[it->first].isBusy<<"\n";
    if (it->second.isBusy == true && it->second.thisQubit_addr.qnic_index == qnic_index && it->second.thisQubit_addr.qubit_index == qubit_index) {
      table[it->first].isBusy = false;
      break;
    } else if (it->second.isBusy == false && it->second.thisQubit_addr.qnic_index == qnic_index && it->second.thisQubit_addr.qubit_index == qubit_index) {
      // if(it->second.isBusy){
      //     EV<<"yes";
      // }else{
      //     EV<<"no";
      // }
      // EV<<"check: "<< it->second.thisQubit_addr.qnic_index <<"=="<<qnic_index <<"\n";
      // EV<<"check: "<< it->second.thisQubit_addr.qubit_index <<"=="<<qubit_index <<"\n";
      // std::cout<<"isBusy = "<<table[it->first].isBusy<<"\n";
      // std::cout<<"Busy = "<<(it->second.isBusy==false)<<" && "<<(it->second.thisQubit_addr.qnic_index == qnic_index)<<" && "<<(it->second.thisQubit_addr.qubit_index ==
      // qubit_index)<<"\n";
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
  cModule *qnode = getQNode();
  switch (qnic_type) {  // if ((qnic_type == QNIC_E) || (qnic_type == QNIC_R)) // if (qnic_type < QNIC_RP)
    case QNIC_E:
    case QNIC_R:
      qnode->getSubmodule(QNIC_names[qnic_type], qnic_index)->par("burst_trial_counter") = qnic_burst_trial_counter[qnic_address];
  }
}

void RuleEngine::updateResources_EntanglementSwapping(swapping_result swapr) {
  // swapper believe previous BSM was succeeded.
  // These are new partner's info
  int new_partner = swapr.new_partner;
  int new_partner_qnic_index = swapr.new_partner_qnic_index;
  int new_partner_qnic_address = swapr.new_partner_qnic_address;  // this is not nessesary?
  QNIC_type new_partner_qnic_type = swapr.new_partner_qnic_type;
  int operation_type = swapr.operation_type;

  // neigbor address should be swapper address
  // node1 --- node6 --- node15
  // node6 is swapper and this is the source of swapping result.
  // qnic interface from node1 to node15 and node1 to node6 must be the same.
  // initialize

  int qnic_address = routingdaemon->return_QNIC_address_to_destAddr(new_partner);
  auto info = hardware_monitor->findConnectionInfoByQnicAddr(qnic_address);
  if (info == nullptr) {
    error("qnic(addr: %d) info not found", qnic_address);
  }
  int qnic_index = info->qnic.index;
  QNIC_type qnic_type = info->qnic.type;
  int qubit_index = swapr.measured_qubit_index;

  // First, the qubit used for swapping must be free.s
  // Swapper doesn't know this is success or fail. Is this correct?
  // TODO how to apply correct operation? is this the role of real time contoroller?
  // FIXME here is just one resource, but this should be loop
  // TODO resources for entanglement swapping in swapper should be free
  // Update tracker first get index from Swapping result maybe... get qubit index from swapping result

  // we need to free swapper resources consumed for entanglement swapping.

  // qubit with address Addr was shot in nth time. This list is ordered from old to new.
  StationaryQubit *qubit = check_and_cast<StationaryQubit *>(getQNode()->getSubmodule(QNIC_names[qnic_type], qnic_index)->getSubmodule("statQubit", qubit_index));
  // if(parentAddress == 27 && qubit->entangled_partner->node_address == 15){
  //     EV<<parentAddress<<" is entangled with "<<qubit->entangled_partner->node_address<<" !!\n";
  //     error("Did it! Currently, no application implemeted. So, after resource consumed, simulation will end.");
  // }
  // check
  if (operation_type == 0) {
    // nothing
  } else if (operation_type == 1) {
    // do X
    qubit->X_gate();
  } else if (operation_type == 2) {
    qubit->Z_gate();
  } else {
    error("something error happened! This operation type doesn't recorded!");
  }

  if (qubit->entangled_partner == nullptr && qubit->Density_Matrix_Collapsed(0, 0).real() == -111 && !qubit->no_density_matrix_nullptr_entangled_partner_ok) {
    std::cout << qubit << ", node[" << qubit->node_address << "] from qnic[" << qubit->qnic_index << "]\n";
    // std::cout<<(bool)(qubit->entangled_partner==nullptr)<<" Entangled if ("<<false<<")\n";
    // std::cout<<qubit->Density_Matrix_Collapsed<<"\n";
    EV << "This is node" << qubit->entangled_partner << "\n";
    error("RuleEngine. Ebit succeed. but wrong");
  }
  allResources[qnic_type][qnic_index].insert(std::make_pair(new_partner /*QNode IP address*/, qubit));
  if (qubit->entangled_partner != nullptr) {
    if (qubit->entangled_partner->entangled_partner == nullptr) {
      // std::cout<<qubit<<" in node["<<qubit->node_address<<"] <-> "<<qubit->entangled_partner<<" in node["<<qubit->entangled_partner->node_address<<"]\n";
      error("1. Entanglement tracking is not doing its job. in update resource E.S.");
    }
    if (qubit->entangled_partner->entangled_partner != qubit) {
      // std::cout<<qubit<<" in node["<<qubit->node_address<<"] <-> "<<qubit->entangled_partner<<" in node["<<qubit->entangled_partner->node_address<<"]\n";
      error("2. Entanglement tracking is not doing its job. in update resource E.S.");
    }
  }
  ResourceAllocation(qnic_type, qnic_index);
  traverseThroughAllProcesses2();  // New resource added to QNIC with qnic_type qnic_index.
}

// Only for MIM and MM
void RuleEngine::freeFailedQubits_and_AddAsResource(int destAddr, int internal_qnic_address, int internal_qnic_index, CombinedBSAresults *pk_result) {
  int list_size = pk_result->getList_of_failedArraySize();
  int qnic_index, qnic_address, neighborQNodeAddress = -1;
  QNIC_type qnic_type;

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

  // std::cout<<"This result is for qnic["<<qnic_address<<"]\n";

  int num_emitted_in_this_burstTrial = tracker[qnic_address].size();
  // EV<<"qnic["<<qnic_index<<"] with type = "<<qnic_type<<"address "<<qnic_address<<" has emitted"<<num_emitted_in_this_burstTrial<<" photons. \n";
  // EV<<"num emitted from qnic["<<qnic_address<<"] is "<<num_emitted_in_this_burstTrial;
  /*for(auto it = tracker[qnic_address].cbegin(); it != tracker[qnic_address].cend(); ++it){
          std::cout<<"??????????????????????????????????? node["<<parentAddress<<"]    "<<it->first<<"th shot was from qnic["<<it->second.qnic_index<<"]
  qubit["<<it->second.qubit_index<<"] \n ";
  }*/
  int success_num = 0;
  for (int i = 0; i < list_size; i++) {
    bool failed = pk_result->getList_of_failed(i);
    sentQubitIndexTracker::iterator it = tracker[qnic_address].find(i);  // check ith shot's information (qnic, qubit index).
    if (it == tracker[qnic_address].end())
      error("Something is wrong with the tracker....%d th shot not recorded", i);  // Neighbor not found! This should not happen unless you simulate broken links in real time.
    if (failed) {
      // std::cout<<"node["<<parentAddress<<"] failed!\n";
      // std::cout<<i<<"th shot has failed.....that was qubit["<<it->second.qubit_index<<"] in qnic["<<it->second.qnic_index<<"]\n";
      // realtime_controller->ReInitialize_StationaryQubit(it->second.qnic_index ,it->second.qubit_index, qnic_type);//Re-initialize the qubit. Pauli errors will be eliminated, and
      // the color of the qubit in the GUI changes to blue. Busy_OR_Free_QubitState_table[qnic_type] = setQubitFree_inQnic(Busy_OR_Free_QubitState_table[qnic_type],
      // it->second.qnic_index, it->second.qubit_index);

      freeResource(it->second.qnic_index, it->second.qubit_index, qnic_type);
    } else {
      // std::cout<<"node["<<parentAddress<<"] success!\n";
      // Keep the entangled qubits
      // std::cout<<i<<"th shot has succeeded.....that was qubit["<<it->second.qubit_index<<"] in qnic["<<it->second.qnic_index<<"] node addr["<<it->first<<"] \n";
      // Add this as an available resource
      StationaryQubit *qubit = check_and_cast<StationaryQubit *>(getQNode()->getSubmodule(QNIC_names[qnic_type], qnic_index)->getSubmodule("statQubit", it->second.qubit_index));
      if (qubit->entangled_partner != nullptr) {
        if (qubit->entangled_partner->entangled_partner == nullptr) {
          // std::cout<<qubit<<" in node["<<qubit->node_address<<"] <-> "<<qubit->entangled_partner<<" in node["<<qubit->entangled_partner->node_address<<"]\n";
          error("1. Entanglement tracking is not doing its job.");
        }
        if (qubit->entangled_partner->entangled_partner != qubit) {
          // std::cout<<qubit<<" in node["<<qubit->node_address<<"] <-> "<<qubit->entangled_partner<<" in node["<<qubit->entangled_partner->node_address<<"]\n";
          error("2. Entanglement tracking is not doing its job.");
        }
      }
      // std::cout<<qubit<<" in node["<<parentAddress<<"] qnic["<<qnic_address<<"] entanglement success"<<qubit<<"\n";
      // std::cout<<"Available resource"<<qubit<<" isBusy = "<<qubit->isBusy<<"\n";

      if (qubit->entangled_partner == nullptr && qubit->Density_Matrix_Collapsed(0, 0).real() == -111 && !qubit->no_density_matrix_nullptr_entangled_partner_ok) {
        std::cout << qubit << ", node[" << qubit->node_address << "] from qnic[" << qubit->qnic_index << "]\n";
        // std::cout<<(bool)(qubit->entangled_partner==nullptr)<<" Entangled if ("<<false<<")\n";
        // std::cout<<qubit->Density_Matrix_Collapsed<<"\n";
        error("RuleEngine. Ebit succeed. but wrong");
      }

      // Add qubit as available resource between NeighborQNodeAddress.
      allResources[qnic_type][qnic_index].insert(std::make_pair(neighborQNodeAddress /*QNode IP address*/, qubit));
      success_num++;
      // EV<<"There are "<<allResources[qnic_type][qnic_index].count(neighborQNodeAddress)<<" resources between this and "<<destAddr<<"\n";
    }
  }

  // Any qubit that has been shot while BSA result is actually on the way to the node, needs to be freed as well.
  if (num_emitted_in_this_burstTrial > list_size) {
    /// EV<<num_emitted_in_this_burstTrial<<" shots fired, but only "<<list_size<<" results returned\n";
    for (int i = list_size; i < num_emitted_in_this_burstTrial; i++) {
      sentQubitIndexTracker::iterator it = tracker[qnic_address].find(i);  // check ith shot's information (qnic, qubit index).

      // Neighbor not found! This should not happen unless you simulate broken links in real time.
      if (it == tracker[qnic_address].end()) error("Wait.... something is wrong with the tracker....%d th shot not recorded", i);

      // realtime_controller->ReInitialize_StationaryQubit(it->second.qnic_index ,it->second.qubit_index, qnic_type);
      // Busy_OR_Free_QubitState_table[qnic_type] = setQubitFree_inQnic(Busy_OR_Free_QubitState_table[qnic_type], it->second.qnic_index, it->second.qubit_index);
      freeResource(it->second.qnic_index, it->second.qubit_index, qnic_type);
    }
  }
  // std::cout<<"success num = "<<success_num<<"\n";
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
}

void RuleEngine::finish() {
  delete qnic_burst_trial_counter;

  //   // here output file
  //   std::string file_name = "test";
  //   std::ofstream creation_time_stats(file_name, std::ios_base::app);
  //   // creation_time_stats<<"s\n";
  //   for(int i = 0; i < creation_times.size(); i++){
  //       creation_time_stats<<creation_times[i]<<"\n";
  // }
}

cModule *RuleEngine::getQNode() {
  cModule *currentModule = getParentModule();  // We know that Connection manager is not the QNode, so start from the parent.
  try {
    cModuleType *QNodeType = cModuleType::get("networks.QNode");  // Assumes the node in a network has a type QNode
    while (currentModule->getModuleType() != QNodeType) {
      currentModule = currentModule->getParentModule();
    }
    return currentModule;
  } catch (std::exception &e) {
    error("No module with QNode type found. Have you changed the type name in ned file?");
    endSimulation();
  }
  return currentModule;
}

double RuleEngine::predictResourceFidelity(QNIC_type qnic_type, int qnic_index, int entangled_node_address, int resource_index) { return uniform(.6, .9); }

void RuleEngine::dynamic_ResourceAllocation(int qnic_type, int qnic_index) {
  //     if(!(rp.size()>0)){// If no ruleset running, do nothing.
  //         return;
  //     }
  //     for(auto it = rp.cbegin(), next_it = rp.cbegin(); it != rp.cend(); it = next_it){
  //         next_it = it; ++next_it;
  //         RuleSet* process = it->second.Rs;//One Process. From top to bottom.
  //         unsigned long ruleset_id = process->ruleset_id;
  //         int partner_size = process->entangled_partner.size();
  //         for (int i=0; i<partner_size;i++){

  //         }
  //     }
}

// Invoked whenever a new resource (entangled with neighbor) has been created.
// Allocates those resources to a particular ruleset, from top to bottom (all of it).
void RuleEngine::ResourceAllocation(int qnic_type, int qnic_index) {
  if (!(rp.size() > 0)) {  // If no ruleset running, do nothing.
    return;
  }

  for (auto it = rp.cbegin(), next_it = rp.cbegin(); it != rp.cend(); it = next_it) {  // In a particular RuleSet
    next_it = it;
    ++next_it;
    RuleSet *process = it->second.Rs;  // One Process. From top to bottom.
    unsigned long ruleset_id = process->ruleset_id;
    int partner_size = process->entangled_partner.size();
    std::vector<Rule *> rule_ptr = process->getRule_ptr();
    // EV<<"parent Address"<<parentAddress<<"\n";
    for (int i = 0; i < partner_size; i++) {
      int resource_entangled_with_address = process->entangled_partner[i];
      // EV<<"resource_entangled_with_address is !!"<<resource_entangled_with_address<<"\n";

      if (process->empty()) {
        error("RuleSet with no Rule found. Probably not what you want!");
      }

      int assigned = 0;
      for (auto it = allResources[qnic_type][qnic_index].cbegin(), next_it = allResources[qnic_type][qnic_index].cbegin(); it != allResources[qnic_type][qnic_index].cend();
           it = next_it) {
        next_it = it;
        ++next_it;

        if (!it->second->isAllocated() && resource_entangled_with_address == it->first) {
          // Free resource that has not been assigned to any ruleset.
          // int index = process->front()->resources.size();//Bad idea. Could result in duplicate index when rscs are consumed.
          // int index = process->front()->number_of_resources_allocated_in_total;
          int num_rsc_bf = process->front()->resources.size();
          if (it->second->entangled_partner == nullptr && it->second->Density_Matrix_Collapsed(0, 0).real() == -111 &&
              !it->second->no_density_matrix_nullptr_entangled_partner_ok) {
            error("Fresh ebit wrong");
          }

          if (rule_ptr.size() != partner_size) {
            process->front()->addResource(resource_entangled_with_address, it->second);
          } else {
            rule_ptr.at(i)->addResource(resource_entangled_with_address, it->second);
            // rule
          }

          int num_rsc_af = process->front()->resources.size();
          if (num_rsc_af != num_rsc_bf + 1) {
            error("Resource is not added properly. This happens when an element in the map has the same key as the one that needed to be added.");
          }
          // int rule_id = process->front()->rule_index;
          // it->second->Lock(ruleset_id, rule_id);
          /*if(parentAddress == 1 || parentAddress == 2){
              std::cout<<"size = "<<process->front()->resources.size()<<"\n";
          for (auto it=process->front()->resources.begin(); it!=process->front()->resources.end(); ++it) {
                              std::cout<<"node["<<parentAddress<<"]"<<ruleset_id<< "|resource|"<<it->second<<"\n";
          }
          }*/
          it->second->Allocate();
          assigned++;
          // emit(recog_resSignal, assigned);
        }
      }
      EV << "assigned" << assigned << "\n";
    }
    // std::cout<<parentAddress<<"Assigned = "<<assigned<<"\n";
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
    EV << "Checking first process.... process " << process->size() << "\n";
    for (auto rule = process->cbegin(), end = process->cend(); rule != end; rule++) {
      bool process_done = false;
      // std::cout<<parentAddress<<": Running first Condition & Action now\n";
      bool terminate_this_rule = false;

      while (true) {
        if (!((*rule)->resources.size() > 0)) {
          break;  // No more resource left for now.
        }
        // std::cout<<"module["<<parentAddress<<"]\n";
        cPacket *pk = (*rule)->checkrun(this);  // Do something on qubits entangled with resource_entangled_with_address.

        if (pk != nullptr) {
          // Feedback to another node required
          if (dynamic_cast<LinkTomographyResult *>(pk) != nullptr) {
            // The cPacket *pk is a single packet forwarded to the neighbor. But this node's HardwareMonitor also needs to store the result.
            LinkTomographyResult *pk_t = check_and_cast<LinkTomographyResult *>(pk);
            LinkTomographyResult *pk_for_self = pk_t->dup();
            pk_for_self->setPartner_address(pk_t->getDestAddr());
            pk_for_self->setDestAddr(pk_t->getSrcAddr());
            // std::cout<<" pk_t partner->"<<pk_t->getPartner_address()<<"\n";
            // std::cout<<" pk_t_self partner->"<<pk_for_self->getPartner_address()<<"\n";
            if (pk_t->getPartner_address() == pk_for_self->getPartner_address()) {
              error("Wrong");
            }
            // std::cout<<"time = "<<pk_t->getFinish()<<"\n";
            /*if(pk_t->getFinish()!=-1){
                error("It is...");
            }*/
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
            EV << "done swapping at " << parentAddress << "\n";
            // here this packet goes to two destination.
            // one is left node the other is right node.
            // only swapper knows which is left and right, but qnodes don't

            // packet for left node
            SwappingResult *pkt_for_left = new SwappingResult("SwappingResult(Left)");
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
            pkt_for_right->setKind(5);  // cyan
            pkt_for_right->setDestAddr(pkt->getRight_Dest());
            pkt_for_right->setSrcAddr(parentAddress);
            pkt_for_right->setOperation_type(pkt->getOperation_type_right());
            pkt_for_right->setMeasured_qubit_index(pkt->getMeasured_qubit_index_right());
            pkt_for_right->setNew_partner(pkt->getNew_partner_right());
            pkt_for_right->setNew_partner_qnic_index(pkt->getNew_partner_qnic_index_right());
            pkt_for_right->setNew_partner_qnic_address(pkt->getNew_partner_qnic_address_right());
            pkt_for_right->setNew_partner_qnic_type(pkt->getNew_partner_qnic_type_right());

            // check
            // EV<<"left node should be 1: "<<pkt->getLeft_Dest()<<" right node should be 15: "<<pkt->getRight_Dest()<<"\n";
            // if(parentAddress == 6){
            //     error("here! check!");
            // }

            send(pkt_for_left, "RouterPort$o");
            send(pkt_for_right, "RouterPort$o");
          } else if (dynamic_cast<Error *>(pk) != nullptr) {
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
          process->destroyThis();  // Destroy ruleset object
          rp.erase(it);  // Erase rule set from map.
          terminate_this_rule = true;  // Flag to get out from outer loop
          std::cout << "node[" << parentAddress << "]:RuleSet deleted.\n";
          break;  // get out from this for loop.
        }

      }  // While
      if (process_done) {
        break;
      }
    }  // For

  }  // For loop
}

void RuleEngine::freeConsumedResource(int qnic_index /*Not the address!!!*/, StationaryQubit *qubit, QNIC_type qnic_type) {
  realtime_controller->ReInitialize_StationaryQubit(qnic_index, qubit->par("stationaryQubit_address"), qnic_type, true);
  Busy_OR_Free_QubitState_table[qnic_type] = setQubitFree_inQnic(Busy_OR_Free_QubitState_table[qnic_type], qnic_index, qubit->par("stationaryQubit_address"));

  for (auto it = allResources[qnic_type][qnic_index].cbegin(), next_it = allResources[qnic_type][qnic_index].cbegin(); it != allResources[qnic_type][qnic_index].cend();
       it = next_it) {
    next_it = it;
    ++next_it;
    if (it->second == qubit) {
      // std::cout<<"Let's delete this qubit!"<<it->second<<"\n";
      allResources[qnic_type][qnic_index].erase(it);  // or "it = m.erase(it)" since C++11
      return;
    }
  }
}

}  // namespace modules
}  // namespace quisp

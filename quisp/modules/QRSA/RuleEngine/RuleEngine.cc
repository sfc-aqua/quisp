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

namespace quisp::modules {

using namespace rules;
using namespace messages;
using qnic_store::QNicStore;
using runtime_callback::RuntimeCallback;

RuleEngine::RuleEngine() : provider(utils::ComponentProvider{this}), runtimes(std::make_unique<RuntimeCallback>(this)) {}

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
  tracker = new SentQubitIndexTracker[number_of_qnics_all];
  for (int qnic_address = 0; qnic_address < number_of_qnics_all; qnic_address++) {
    tracker_accessible.push_back(true);
  }
  WATCH_VECTOR(tracker_accessible);
}

void RuleEngine::handleMessage(cMessage *msg) {
  executeAllRuleSets();  // New resource added to QNIC with qnic_type qnic_index.

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
  }

  else if (auto *pkt = dynamic_cast<InternalRuleSetForwarding *>(msg)) {
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

  executeAllRuleSets();
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

  auto *runtime = runtimes.findById(data.ruleset_id);
  bell_pair_store.eraseQubit(qubit_record);
  bell_pair_store.insertEntangledQubit(data.new_partner_addr, qubit_record);
  runtime->promoteQubitWithNewPartner(qubit_record, data.new_partner_addr);
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
      qubit->assertEntangledPartnerValid();
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
  executeAllRuleSets();  // New resource added to QNIC with qnic_type qnic_index.
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

/** \file RuleEngine.h
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/04/04
 *
 *  \brief RuleEngine
 */
#ifndef QUISP_MODULES_RULEENGINE_H_
#define QUISP_MODULES_RULEENGINE_H_

#include <omnetpp.h>
#include <rules/RuleSet.h>
#include <vector>

#include "../../PhysicalConnection/BSA/HoMController.h"
#include "IRuleEngine.h"
#include "classical_messages_m.h"
#include "modules/QNIC/StationaryQubit/StationaryQubit.h"
#include "modules/QRSA/HardwareMonitor/HardwareMonitor.h"
#include "modules/QRSA/RealTimeController/IRealTimeController.h"
#include "modules/QRSA/RoutingDaemon/RoutingDaemon.h"
#include "modules/QUBIT.h"

using namespace omnetpp;

namespace quisp {
namespace modules {
using namespace rules;

/** \class RuleEngine RuleEngine.h
 *  \todo Documentation of the class header.
 *  \note The Connection Manager responds to connection requests received from other nodes.
 *        Connection setup, so a regular operation but not high bandwidth, relatively low constraints.
 *        Connections from nearest neighbors only.
 *        Connection manager needs to know which qnic is connected to where, which QNode not HoM/EPPS.
 *
 *  \brief RuleEngine
 */

class RuleEngine : public IRuleEngine {
 private:
  // simsignal_t recog_resSignal;
  simsignal_t actual_resSignal;
  // friend class Action;
 public:
  int parentAddress;  // Parent QNode's address
  EmitPhotonRequest *emt;
  NeighborTable ntable;
  int number_of_qnics_all;  // qnic,qnic_r,_qnic_rp
  int number_of_qnics;
  int number_of_qnics_r;
  int number_of_qnics_rp;
  PurificationTable Purification_table;
  DoublePurificationTable DoublePurification_table;
  TriplePurificationTable TriplePurification_table;
  QuatroPurificationTable QuatroPurification_table;
  // Although qnic index is in QubitAddr, lest make int qnic_index -> QubisState to lessen the search
  // QubitStateTable stable, stable_r, stable_rp;
  QubitStateTable *Busy_OR_Free_QubitState_table;
  bool *terminated_qnic;  // When you need to intentionally stop the link to make the simulation lighter.
  sentQubitIndexTracker *tracker;
  HardwareMonitor *hardware_monitor;
  RoutingDaemon *routingdaemon;
  IRealTimeController *realtime_controller;
  int *qnic_burst_trial_counter;
  qnicResources *allResources;  // Size will be defined in initialization. If 3 qnic types, then size is 3. Type defined in QUBIT.h
  /*
   * DEFINED in QNIC.h
   * typedef std::multimap<int, StationaryQubit*> EntangledPairs;//entangled Node address -> pointer to that local qubit
   * typedef EntangledPairs* qnicResources;//For each qnic. If the number of "qnic" is 3, then the size is 3.
   * For resource management over.
   * */

  // typedef rules::RuleSet* RuleSetPtr;
  running_processes rp;
  // int assigned = 0;
  // typedef std::map<std::string, quisp::rules::RuleSet> processes;//process_id -> Rule set
  void freeResource(int qnic_index, int qubit_index, QNIC_type qnic_type) override;
  void freeConsumedResource(int qnic_index, StationaryQubit *qubit, QNIC_type qnic_type) override;
  void dynamic_ResourceAllocation(int qnic_type, int qnic_index) override;
  void ResourceAllocation(int qnic_type, int qnic_index) override;

 protected:
  void initialize() override;
  void finish() override;
  void handleMessage(cMessage *msg) override;
  cModule *getQNode();
  int countFreeQubits_inQnic(QubitStateTable table, int qnic_index);
  int getOneFreeQubit_inQnic(QubitStateTable table, int qnic_index);
  QubitStateTable setQubitBusy_inQnic(QubitStateTable table, int qnic_index, int qubit_index);
  QubitStateTable setQubitFree_inQnic(QubitStateTable table, int qnic_index, int qubit_index);
  QubitStateTable initializeQubitStateTable(QubitStateTable temp, QNIC_type qnic_type);
  void scheduleFirstPhotonEmission(BSMtimingNotifier *pk, QNIC_type qnic_type);
  void shootPhoton(SchedulePhotonTransmissionsOnebyOne *pk);
  // virtual int getQNICjob_index_for_this_qnic(int qnic_index, QNIC_type qnic_type);
  void incrementBurstTrial(int destAddr, int internal_qnic_address, int internal_qnic_index);
  void shootPhoton_internal(SchedulePhotonTransmissionsOnebyOne *pk);
  bool burstTrial_outdated(int this_trial, int qnic_address);
  // virtual int getQnicIndex_toNeighbor(int destAddr);
  InterfaceInfo getInterface_toNeighbor(int destAddr);
  InterfaceInfo getInterface_toNeighbor_Internal(int local_qnic_index);
  void scheduleNextEmissionEvent(int qnic_index, int qnic_address, double interval, simtime_t timing, int num_sent, bool internal, int trial);
  void freeFailedQubits_and_AddAsResource(int destAddr, int internal_qnic_address, int internal_qnic_index, CombinedBSAresults *pk_result);
  void clearTrackerTable(int destAddr, int internal_qnic_address);
  // virtual void traverseThroughAllProcesses(RuleEngine *re, int qnic_type, int qnic_index);
  void traverseThroughAllProcesses2();
  double predictResourceFidelity(QNIC_type qnic_type, int qnic_index, int entangled_node_address, int resource_index);
  // virtual void check_Purification_Agreement(purification_result pr);
  void storeCheck_Purification_Agreement(purification_result pr);
  void storeCheck_DoublePurification_Agreement(Doublepurification_result pr);
  void storeCheck_TriplePurification_Agreement(Triplepurification_result pr);
  void storeCheck_QuatroPurification_Agreement(Quatropurification_result pr);
  void Unlock_resource_and_upgrade_stage(unsigned long ruleset_id, int rule_id, int index);
  void Unlock_resource_and_discard(unsigned long ruleset_id, int rule_id, int index);

  void updateResources_EntanglementSwapping(swapping_result swapr);

 private:
  utils::ComponentProvider provider;
};

}  // namespace modules
}  // namespace quisp

#endif /* MODULES_RULEENGINE_H_ */

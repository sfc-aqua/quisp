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

#include <modules/HardwareMonitor.h>
#include <modules/HoM_Controller.h>
#include <modules/QUBIT.h>
#include <modules/RealTimeController.h>
#include <modules/RoutingDaemon.h>
#include <modules/stationaryQubit.h>
#include <omnetpp.h>
#include <rules/RuleSet.h>
#include <vector>
#include "classical_messages_m.h"

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

typedef struct {
  unsigned long ruleset_id;
  int rule_id;
  int index;
} process_id;

struct purification_result {
  process_id id;
  bool outcome;
};

struct Doublepurification_result {
  process_id id;
  bool Xpurification_outcome;
  bool Zpurification_outcome;
};

struct Triplepurification_result {
  process_id id;
  bool Xpurification_outcome;
  bool Zpurification_outcome;
  bool DS_purification_outcome;
};

struct Quatropurification_result {
  process_id id;
  bool Xpurification_outcome;
  bool Zpurification_outcome;
  bool DS_Xpurification_outcome;
  bool DS_Zpurification_outcome;
};

struct swapping_result {
  process_id id;
  int new_partner;
  int new_partner_qnic_index;
  int new_partner_qnic_address;
  int measured_qubit_index;
  QNIC_type new_partner_qnic_type;
  int operation_type;
};

// Process = RuleSet
typedef struct {
  int ownner_addr;
  // int process_ID;
  RuleSet* Rs;
} process;

class RuleEngine : public cSimpleModule {
 private:
  // simsignal_t recog_resSignal;
  simsignal_t actual_resSignal;
  // friend class Action;
 public:
  int parentAddress;  // Parent QNode's address
  EmitPhotonRequest* emt;
  NeighborTable ntable;
  int number_of_qnics_all;  // qnic,qnic_r,_qnic_rp
  int number_of_qnics;
  int number_of_qnics_r;
  int number_of_qnics_rp;
  typedef std::map<int, QubitState> QubitStateTable;
  typedef std::multimap<int, purification_result> PurificationTable;
  PurificationTable Purification_table;
  typedef std::multimap<int, Doublepurification_result> DoublePurificationTable;
  typedef std::multimap<int, Quatropurification_result> QuatroPurificationTable;
  typedef std::multimap<int, Triplepurification_result> TriplePurificationTable;
  DoublePurificationTable DoublePurification_table;
  TriplePurificationTable TriplePurification_table;
  QuatroPurificationTable QuatroPurification_table;
  typedef std::map<int, QubitAddr_cons> sentQubitIndexTracker;  // nth shot -> node/qnic/qubit index (node addr not needed actually)
  // Although qnic index is in QubitAddr, lest make int qnic_index -> QubisState to lessen the search
  // QubitStateTable stable, stable_r, stable_rp;
  QubitStateTable* Busy_OR_Free_QubitState_table;
  bool* terminated_qnic;  // When you need to intentionally stop the link to make the simulation lighter.
  sentQubitIndexTracker* tracker;
  HardwareMonitor* hardware_monitor;
  RoutingDaemon* routingdaemon;
  RealTimeController* realtime_controller;
  int* qnic_burst_trial_counter;
  typedef std::map<int, bool> trial_tracker;  // trial index, false or true (that trial is over or not)
  qnicResources* allResources;  // Size will be defined in initialization. If 3 qnic types, then size is 3. Type defined in QUBIT.h
  /*
   * DEFINED in QNIC.h
   * typedef std::multimap<int, StationaryQubit*> EntangledPairs;//entangled Node address -> pointer to that local qubit
   * typedef EntangledPairs* qnicResources;//For each qnic. If the number of "qnic" is 3, then the size is 3.
   * For resource management over.
   * */

  // typedef rules::RuleSet* RuleSetPtr;
  typedef std::map<int, process> running_processes;  // index -> process
  running_processes rp;
  typedef std::map<int, Rule*> rule_ptr;
  // int assigned = 0;
  // typedef std::map<std::string, quisp::rules::RuleSet> processes;//process_id -> Rule set
  virtual void freeResource(int qnic_index, int qubit_index, QNIC_type qnic_type);
  virtual void freeConsumedResource(int qnic_index, StationaryQubit* qubit, QNIC_type qnic_type);
  virtual void dynamic_ResourceAllocation(int qnic_type, int qnic_index);
  virtual void ResourceAllocation(int qnic_type, int qnic_index);

 protected:
  virtual void initialize() override;
  virtual void finish() override;
  virtual void handleMessage(cMessage* msg) override;
  virtual cModule* getQNode();
  virtual int countFreeQubits_inQnic(QubitStateTable table, int qnic_index);
  virtual int getOneFreeQubit_inQnic(QubitStateTable table, int qnic_index);
  virtual QubitStateTable setQubitBusy_inQnic(QubitStateTable table, int qnic_index, int qubit_index);
  virtual QubitStateTable setQubitFree_inQnic(QubitStateTable table, int qnic_index, int qubit_index);
  virtual QubitStateTable initializeQubitStateTable(QubitStateTable temp, QNIC_type qnic_type);
  virtual void scheduleFirstPhotonEmission(BSMtimingNotifier* pk, QNIC_type qnic_type);
  virtual void shootPhoton(SchedulePhotonTransmissionsOnebyOne* pk);
  // virtual int getQNICjob_index_for_this_qnic(int qnic_index, QNIC_type qnic_type);
  virtual void incrementBurstTrial(int destAddr, int internal_qnic_address, int internal_qnic_index);
  virtual void shootPhoton_internal(SchedulePhotonTransmissionsOnebyOne* pk);
  virtual bool burstTrial_outdated(int this_trial, int qnic_address);
  // virtual int getQnicIndex_toNeighbor(int destAddr);
  virtual InterfaceInfo getInterface_toNeighbor(int destAddr);
  virtual InterfaceInfo getInterface_toNeighbor_Internal(int local_qnic_index);
  virtual void scheduleNextEmissionEvent(int qnic_index, int qnic_address, double interval, simtime_t timing, int num_sent, bool internal, int trial);
  virtual void freeFailedQubits_and_AddAsResource(int destAddr, int internal_qnic_address, int internal_qnic_index, CombinedBSAresults* pk_result);
  virtual void clearTrackerTable(int destAddr, int internal_qnic_address);
  // virtual void traverseThroughAllProcesses(RuleEngine *re, int qnic_type, int qnic_index);
  virtual void traverseThroughAllProcesses2();
  virtual double predictResourceFidelity(QNIC_type qnic_type, int qnic_index, int entangled_node_address, int resource_index);
  // virtual void check_Purification_Agreement(purification_result pr);
  virtual void storeCheck_Purification_Agreement(purification_result pr);
  virtual void storeCheck_DoublePurification_Agreement(Doublepurification_result pr);
  virtual void storeCheck_TriplePurification_Agreement(Triplepurification_result pr);
  virtual void storeCheck_QuatroPurification_Agreement(Quatropurification_result pr);
  virtual void Unlock_resource_and_upgrade_stage(unsigned long ruleset_id, int rule_id, int index);
  virtual void Unlock_resource_and_discard(unsigned long ruleset_id, int rule_id, int index);

  virtual void updateResources_EntanglementSwapping(swapping_result swapr);
};

}  // namespace modules
}  // namespace quisp

#endif /* MODULES_RULEENGINE_H_ */

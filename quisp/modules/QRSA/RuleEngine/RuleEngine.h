/** \file RuleEngine.h
 *
 *  \brief RuleEngine
 */
#pragma once

#include <omnetpp.h>
#include <unordered_map>
#include <vector>

#include <modules/Logger/LoggerBase.h>
#include <modules/QRSA/HardwareMonitor/IHardwareMonitor.h>
#include <modules/QRSA/RealTimeController/IRealTimeController.h>
#include <modules/QRSA/RoutingDaemon/IRoutingDaemon.h>
#include <rules/RuleSet.h>
#include <runtime/Runtime.h>
#include <runtime/RuntimeManager.h>
#include <utils/ComponentProvider.h>

#include "BellPairStore/BellPairStore.h"
#include "IRuleEngine.h"
#include "PurificationResultTable/PurificationResultTable.h"
#include "QNicStore/IQNicStore.h"
#include "QubitRecord/IQubitRecord.h"
#include "messages/QNode_ipc_messages_m.h"
#include "messages/link_generation_messages_m.h"
#include "modules/QNIC.h"
#include "omnetpp/simtime.h"

using namespace omnetpp;
using namespace quisp::rules;

namespace quisp::modules::runtime_callback {
struct RuntimeCallback;
}

namespace quisp::modules {
using pur_result_table::PurificationResultData;
using pur_result_table::PurificationResultKey;
using pur_result_table::PurificationResultTable;
using qnic_store::IQNicStore;
using qubit_record::IQubitRecord;

struct PhotonTransmissionConfig {
  int transmission_partner_address;
  int qnic_index;
  int qnic_address;
  QNIC_type qnic_type;
  simtime_t timing;
  double interval;
};

/// @brief nth shot -> node/qnic/qubit index (node addr not needed actually)
using SentQubitIndexTracker = std::map<int, QubitAddr_cons>;

struct SwappingResultData {
  unsigned long ruleset_id;
  int shared_tag;
  int new_partner_addr;
  int operation_type;
  int qubit_index;
};

/** \class RuleEngine RuleEngine.h
 *  \note The Connection Manager responds to connection requests received from other nodes.
 *        Connection setup, so a regular operation but not high bandwidth, relatively low constraints.
 *        Connections from nearest neighbors only.
 *        Connection manager needs to know which qnic is connected to where, which QNode not BSA/EPPS.
 *
 *  \brief RuleEngine
 */

class RuleEngine : public IRuleEngine, public Logger::LoggerBase {
 public:
  friend runtime_callback::RuntimeCallback;
  RuleEngine();
  ~RuleEngine();
  int parentAddress;  // Parent QNode's address
  messages::EmitPhotonRequest *emt;
  NeighborTable ntable;
  int number_of_qnics_all;  // qnic,qnic_r,_qnic_rp
  int number_of_qnics;
  int number_of_qnics_r;
  int number_of_qnics_rp;
  PurificationResultTable purification_result_table;

  bool *terminated_qnic;  // When you need to intentionally stop the link to make the simulation lighter.
  SentQubitIndexTracker *tracker;
  IHardwareMonitor *hardware_monitor;
  IRoutingDaemon *routingdaemon;
  IRealTimeController *realtime_controller;
  int *qnic_burst_trial_counter;
  BellPairStore bell_pair_store;

  // Vector for store package for simultaneous entanglement swapping
  std::map<int, std::map<int, int>> simultaneous_es_results;

  // tracker accessible table has as many number of boolean value as the number of qnics in the qnode.
  // when the tracker for the qnic is clered by previous BSM trial it goes true
  // when the RuleEngine try to start new Photon emittion, it goes false and other BSM trial can't access to it.
  std::vector<bool> tracker_accessible;

  void freeResource(int qnic_index, int qubit_index, QNIC_type qnic_type) override;
  void freeConsumedResource(int qnic_index, IStationaryQubit *qubit, QNIC_type qnic_type) override;
  void ResourceAllocation(int qnic_type, int qnic_index) override;

 protected:
  void initialize() override;
  void handleMessage(cMessage *msg) override;
  InterfaceInfo getInterface_toNeighbor(int destAddr);
  InterfaceInfo getInterface_toNeighbor_Internal(int local_qnic_index);
  void handleLinkGenerationResult(messages::CombinedBSAresults *bsa_result);
  void handlePurificationResult(const PurificationResultKey &, const PurificationResultData &, bool from_self);
  void handleSwappingResult(const SwappingResultData &data);
  double predictResourceFidelity(QNIC_type qnic_type, int qnic_index, int entangled_node_address, int resource_index);
  void executeAllRuleSets();
  void sendEmitPhotonSignalToQnic(QNIC_type qnic_type, int qnic_index, int qubit_index, bool is_first, bool is_last);
  void stopOnGoingPhotonEmission(QNIC_type qnic_type, int qnic_index);
  void freeFailedEntanglementAttemptQubits(QNIC_type qnic_type, int qnic_index);
  simtime_t getEmitTimeFromBSMNotification(messages::BSMTimingNotification *notification);
  void schedulePhotonEmission(QNIC_type qnic_type, int qnic_index, messages::BSMTimingNotification *notification);

  utils::ComponentProvider provider;
  std::unique_ptr<IQNicStore> qnic_store = nullptr;

  runtime::RuntimeManager runtimes;
  std::unordered_map<std::pair<QNIC_type, int>, messages::EmitPhotonRequest *> emit_photon_timer_map;
  std::unordered_map<std::pair<QNIC_type, int>, std::vector<int>> emitted_photon_order_map;
};

Define_Module(RuleEngine);
}  // namespace quisp::modules

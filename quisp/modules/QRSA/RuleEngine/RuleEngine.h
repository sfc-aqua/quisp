/** \file RuleEngine.h
 *
 *  \brief RuleEngine
 */
#pragma once

#include <unordered_map>
#include <vector>

#include <omnetpp.h>

#include "BellPairStore/BellPairStore.h"
#include "IRuleEngine.h"
#include "QNicStore/IQNicStore.h"
#include "QubitRecord/IQubitRecord.h"
#include "messages/BSA_ipc_messages_m.h"
#include "messages/classical_messages.h"
#include "messages/link_generation_messages_m.h"
#include "modules/Logger/LoggerBase.h"
#include "modules/QNIC.h"
#include "modules/QRSA/HardwareMonitor/IHardwareMonitor.h"
#include "modules/QRSA/RealTimeController/IRealTimeController.h"
#include "modules/QRSA/RoutingDaemon/IRoutingDaemon.h"
#include "rules/RuleSet.h"
#include "runtime/Runtime.h"
#include "runtime/RuntimeManager.h"
#include "utils/ComponentProvider.h"

using namespace omnetpp;
using namespace quisp::rules;

namespace quisp::modules::runtime_callback {
struct RuntimeCallback;
}

namespace quisp::modules {
using qnic_store::IQNicStore;
using qubit_record::IQubitRecord;

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
  int number_of_qnics_all;  // qnic,qnic_r,_qnic_rp
  int number_of_qnics;
  int number_of_qnics_r;
  int number_of_qnics_rp;

  IHardwareMonitor *hardware_monitor;
  IRoutingDaemon *routingdaemon;
  IRealTimeController *realtime_controller;
  BellPairStore bell_pair_store;

  void freeResource(int qnic_index, int qubit_index, QNIC_type qnic_type);
  void freeConsumedResource(int qnic_index, IStationaryQubit *qubit, QNIC_type qnic_type);
  void ResourceAllocation(int qnic_type, int qnic_index);

 protected:
  void initialize() override;
  void handleMessage(cMessage *msg) override;
  void handleMSMResult(messages::MSMResult *msm_result);
  void handleLinkGenerationResult(messages::CombinedBSAresults *bsa_result);
  void handlePurificationResult(messages::PurificationResult *purification_result);
  void handleSwappingResult(messages::SwappingResult *swapping_result);
  void handleSingleClickResult(messages::SingleClickResult *click_result);
  messages::CombinedBSAresults *generateCombinedBSAresults(int qnic_index);
  void executeAllRuleSets();
  void sendEmitPhotonSignalToQnic(QNIC_type qnic_type, int qnic_index, int qubit_index, bool is_first, bool is_last);
  void stopOnGoingPhotonEmission(QNIC_type qnic_type, int qnic_index);
  void freeFailedEntanglementAttemptQubits(QNIC_type qnic_type, int qnic_index);
  simtime_t getEmitTimeFromBSMNotification(messages::BSMTimingNotification *notification);
  void schedulePhotonEmission(QNIC_type qnic_type, int qnic_index, messages::BSMTimingNotification *notification);
  void scheduleMSMPhotonEmission(QNIC_type qnic_type, int qnic_index, messages::EPPSTimingNotification *notification);
  void handleMSMResultArrivalCheck(messages::MSMResultArrivalCheck *msm_result_arrival_check);
  void handleStopEmitting(messages::StopEmitting *stop_emit);

  utils::ComponentProvider provider;
  std::unique_ptr<IQNicStore> qnic_store = nullptr;

  runtime::RuntimeManager runtimes;
  std::unordered_map<std::pair<QNIC_type, int>, messages::EmitPhotonRequest *> emit_photon_timer_map;
  std::unordered_map<std::pair<QNIC_type, int>, std::vector<int>> emitted_photon_order_map;

  struct QubitInfo {
    int qubit_index;
    PauliOperator correction_operation = PauliOperator::I;
    bool handled = false;
  };

  struct MSMInfo {
    int partner_address;
    int partner_qnic_index;
    int epps_address;
    unsigned long long photon_index_counter;
    int iteration_index;
    simtime_t total_travel_time;
    // map of iteration index and qubit index
    std::unordered_map<int, int> qubit_info_map;
    // map of photon index and qubit info
    std::unordered_map<int, QubitInfo> qubit_postprocess_info;
  };

  // [Key: qnic_index, Value: qubit_index]
  std::unordered_map<int, MSMInfo> msm_info_map;
};

Define_Module(RuleEngine);
}  // namespace quisp::modules

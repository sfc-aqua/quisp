#pragma once

#include <omnetpp.h>
#include <vector>

#include <messages/classical_messages.h>
#include <modules/PhysicalConnection/BSA/HOMController.h>
#include <modules/QNIC/StationaryQubit/StationaryQubit.h>
#include <modules/QRSA/HardwareMonitor/HardwareMonitor.h>
#include <modules/QRSA/RealTimeController/IRealTimeController.h>
#include <modules/QRSA/RoutingDaemon/RoutingDaemon.h>
#include <modules/QUBIT.h>
#include <rules/Active/ActiveRuleSet.h>
#include <rules/RuleSet.h>

using namespace omnetpp;

namespace quisp::modules {
using namespace rules::active;

typedef struct {
  unsigned long ruleset_id;
  int rule_id;
  int index;
  int shared_tag;
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
  int swapper_addr;
  int new_partner;
  int new_partner_qnic_index;
  int new_partner_qnic_address;
  int measured_qubit_index;
  QNIC_type new_partner_qnic_type;
  int operation_type;
};

struct PhotonTransmissionConfig {
  int transmission_partner_address;
  int qnic_index;
  int qnic_address;
  QNIC_type qnic_type;
  simtime_t timing;
  double interval;
};

typedef std::multimap<int, purification_result> PurificationTable;  // map<partner, purification_result>
typedef std::multimap<unsigned long, Doublepurification_result> DoublePurificationTable;
typedef std::multimap<unsigned long, Quatropurification_result> QuatroPurificationTable;
typedef std::multimap<unsigned long, Triplepurification_result> TriplePurificationTable;
typedef std::map<int, QubitAddr_cons> sentQubitIndexTracker;  // nth shot -> node/qnic/qubit index (node addr not needed actually)

class IRuleEngine : public cSimpleModule {
 public:
  ~IRuleEngine() {}
  virtual void freeResource(int qnic_index, int qubit_index, QNIC_type qnic_type) = 0;
  virtual void freeConsumedResource(int qnic_index, IStationaryQubit *qubit, QNIC_type qnic_type) = 0;
  virtual void ResourceAllocation(int qnic_type, int qnic_index) = 0;
};

}  // namespace quisp::modules

#ifndef QUISP_MODULES_IRULEENGINE_H_
#define QUISP_MODULES_IRULEENGINE_H_

#include <omnetpp.h>
#include <rules/RuleSet.h>
#include <vector>

#include "../../PhysicalConnection/BSA/HoMController.h"
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

struct photon_transmission_config{
  int transmission_partner_address;
  int qnic_index;
  int qnic_address;
  QNIC_type qnic_type;
  simtime_t timing;
  double interval;
};

// Process = RuleSet
typedef struct {
  int ownner_addr;
  // int process_ID;
  RuleSet *Rs;
} process;

typedef std::map<int, QubitState> QubitStateTable;
typedef std::multimap<int, purification_result> PurificationTable;
typedef std::multimap<int, Doublepurification_result> DoublePurificationTable;
typedef std::multimap<int, Quatropurification_result> QuatroPurificationTable;
typedef std::multimap<int, Triplepurification_result> TriplePurificationTable;
typedef std::map<int, QubitAddr_cons> sentQubitIndexTracker;  // nth shot -> node/qnic/qubit index (node addr not needed actually)
typedef std::map<int, bool> trial_tracker;  // trial index, false or true (that trial is over or not)
typedef std::map<int, process> running_processes;  // index -> process
typedef std::map<int, Rule *> rule_ptr;

class IRuleEngine : public cSimpleModule {
 public:
  ~IRuleEngine() {}
  virtual void freeResource(int qnic_index, int qubit_index, QNIC_type qnic_type) = 0;
  virtual void freeConsumedResource(int qnic_index, StationaryQubit *qubit, QNIC_type qnic_type) = 0;
  virtual void dynamic_ResourceAllocation(int qnic_type, int qnic_index) = 0;
  virtual void ResourceAllocation(int qnic_type, int qnic_index) = 0;
};

}  // namespace modules
}  // namespace quisp

#endif /* MODULES_IRULEENGINE_H_ */

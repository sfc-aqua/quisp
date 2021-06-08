#ifndef MODULES_ICONNECTIONMANAGER_H_
#define MODULES_ICONNECTIONMANAGER_H_

#include <classical_messages_m.h>
#include <modules/QNIC.h>
#include <modules/QRSA/HardwareMonitor/HardwareMonitor.h>
#include <modules/QRSA/RoutingDaemon/RoutingDaemon.h>
#include <modules/QRSA/RuleEngine/RuleEngine.h>
#include <omnetpp.h>
#include <rules/RuleSet.h>
#include <utils/ComponentProvider.h>
#include <vector>

using namespace omnetpp;
using namespace quisp::messages;
using namespace quisp::rules;

namespace quisp {
namespace modules {

typedef struct {  // This is a little bit redundant
  int left_partner;
  QNIC_type lqnic_type;
  int lqnic_index;
  int lqnic_address;
  int lres;
  int right_partner;
  QNIC_type rqnic_type;
  int rqnic_index;
  int rqnic_address;
  int rres;
  int self_left_qnic_index;
  QNIC_type self_left_qnic_type;
  int self_right_qnic_index;
  QNIC_type self_right_qnic_type;
} SwappingConfig;

class IConnectionManager : public cSimpleModule {
 public:
  virtual ~IConnectionManager(){};
};

}  // namespace modules
}  // namespace quisp
#endif /* MODULES_ICONNECTIONMANAGER_H_ */

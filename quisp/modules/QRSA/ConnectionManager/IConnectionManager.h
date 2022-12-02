#ifndef MODULES_ICONNECTIONMANAGER_H_
#define MODULES_ICONNECTIONMANAGER_H_

#include <messages/classical_messages.h>
#include <modules/QNIC.h>
#include <modules/QRSA/HardwareMonitor/HardwareMonitor.h>
#include <modules/QRSA/RoutingDaemon/RoutingDaemon.h>
#include <modules/QRSA/RuleEngine/RuleEngine.h>
#include <omnetpp.h>
#include <utils/ComponentProvider.h>
#include <queue>
#include <vector>

using namespace omnetpp;
using namespace quisp::messages;

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

  // simultaneous config
  int index;

  int initiator;
  QNIC_type initiator_qnic_type;
  int initiator_qnic_index;
  int initiator_qnic_address;
  int initiator_res;

  int responder;
  QNIC_type responder_qnic_type;
  int responder_qnic_index;
  int responder_qnic_address;
  int responder_res;
} SwappingConfig;

class IConnectionManager : public cSimpleModule {
 public:
  virtual ~IConnectionManager(){};
  virtual unsigned long createUniqueId() = 0;
};

}  // namespace modules
}  // namespace quisp
#endif /* MODULES_ICONNECTIONMANAGER_H_ */

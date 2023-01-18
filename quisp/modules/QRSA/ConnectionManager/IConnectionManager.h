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
  int lres;
  int right_partner;
  int rres;

  // simultaneous config
  int index;

  int initiator;
  int initiator_res;

  int responder;
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

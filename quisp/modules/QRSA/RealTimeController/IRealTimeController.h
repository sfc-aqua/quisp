#ifndef QUISP_MODULES_IREALTIMECONTROLLER_H_
#define QUISP_MODULES_IREALTIMECONTROLLER_H_

#include <classical_messages_m.h>
#include <modules/QNIC.h>
#include <omnetpp.h>
#include <vector>

using namespace omnetpp;

namespace quisp {
namespace modules {

class IRealTimeController : public cSimpleModule {
 protected:
  virtual void initialize() = 0;
  virtual void handleMessage(cMessage* msg) = 0;
  virtual cModule* getQNode() = 0;
  virtual cModule* getRGSsource() = 0;

 public:
  virtual void EmitPhoton(int qnic_index, int qubit_index, QNIC_type qnic_type, int pulse) = 0;
  virtual void EmitPhotonForRGS(int qnic_index, int qubit_index, QNIC_type qnic_type) = 0;
  virtual void ReInitialize_StationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type, bool consumed) = 0;
};
}  // namespace modules
}  // namespace quisp

#endif /* QUISP_MODULES_IREALTIMECONTROLLER_H_ */

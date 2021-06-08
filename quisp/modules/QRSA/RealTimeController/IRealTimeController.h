#ifndef QUISP_MODULES_IREALTIMECONTROLLER_H_
#define QUISP_MODULES_IREALTIMECONTROLLER_H_

#include <modules/QNIC.h>

namespace quisp {
namespace modules {

class IRealTimeController : public cSimpleModule {
 protected:
  virtual void initialize() = 0;
  virtual void handleMessage(cMessage* msg) = 0;
<<<<<<< HEAD
  virtual cModule* getQNode() = 0;
  virtual cModule* getRGSsource() = 0;
=======
>>>>>>> bd4fd5195299815cf4a4c38482adc09cd42e3a38

 public:
  virtual void EmitPhoton(int qnic_index, int qubit_index, QNIC_type qnic_type, int pulse) = 0;
  virtual void EmitPhotonForRGS(int qnic_index, int qubit_index, QNIC_type qnic_type) = 0;
  virtual void ReInitialize_StationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type, bool consumed) = 0;
};
}  // namespace modules
}  // namespace quisp

#endif /* QUISP_MODULES_IREALTIMECONTROLLER_H_ */

#ifndef QUISP_MODULES_IREALTIMECONTROLLER_H_
#define QUISP_MODULES_IREALTIMECONTROLLER_H_

#include <modules/QNIC.h>
#include <modules/QRSA/QRSA.h>
#include <modules/QRSA/RuleEngine/QubitRecord/IQubitRecord.h>
namespace quisp {
namespace modules {

class IRealTimeController : public cSimpleModule {
 protected:
  virtual void initialize() = 0;
  virtual void handleMessage(cMessage* msg) = 0;

 public:
  virtual void EmitPhoton(int qnic_index, int qubit_index, QNIC_type qnic_type, int pulse) = 0;
  virtual void ReInitialize_StationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type, bool consumed) = 0;
  virtual void applyXGate(qrsa::IQubitRecord* const qubit_record) = 0;
  virtual void applyZGate(qrsa::IQubitRecord* const qubit_record) = 0;
  virtual void assertNoEntanglement(qrsa::IQubitRecord* const qubit_record) = 0;
};
}  // namespace modules
}  // namespace quisp

#endif /* QUISP_MODULES_IREALTIMECONTROLLER_H_ */

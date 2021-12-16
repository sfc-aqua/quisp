/** \file RealTimeController.h
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/19
 *
 *  \brief RealTimeController
 */
#ifndef QUISP_MODULES_REALTIMECONTROLLER_H_
#define QUISP_MODULES_REALTIMECONTROLLER_H_

#include <utils/ComponentProvider.h>
#include "IRealTimeController.h"

namespace quisp {
namespace modules {

/** \class RealTimeController RealTimeController.h
 *
 *  \brief RealTimeController
 */
class RealTimeController : public IRealTimeController {
 private:
  int myAddress;

 protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage* msg) override;

 public:
  RealTimeController();
  void EmitPhoton(int qnic_index, int qubit_index, QNIC_type qnic_type, int pulse) override;
  void ReInitialize_StationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type, bool consumed) override;
  void applyXGate(qrsa::IQubitRecord* const qubit_record) override;
  void applyZGate(qrsa::IQubitRecord* const qubit_record) override;
  void assertNoEntanglement(qrsa::IQubitRecord* const qubit_record) override;
  utils::ComponentProvider provider;
};

}  // namespace modules
}  // namespace quisp

#endif /* QUISP_MODULES_REALTIMECONTROLLER_H_ */

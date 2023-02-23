/** \file RealTimeController.h
 *
 *  \brief RealTimeController
 */
#ifndef QUISP_MODULES_REALTIMECONTROLLER_H_
#define QUISP_MODULES_REALTIMECONTROLLER_H_

#include "IRealTimeController.h"
#include "types/QNodeAddr.h"
#include "utils/ComponentProvider.h"

namespace quisp {
namespace modules {

/** \class RealTimeController RealTimeController.h
 *
 *  \brief RealTimeController
 */
class RealTimeController : public IRealTimeController {
 private:
  types::QNodeAddr myAddress;

 protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage* msg) override;

 public:
  RealTimeController();
  void EmitPhoton(int qnic_index, int qubit_index, QNIC_type qnic_type, int pulse) override;
  void ReInitialize_StationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type, bool consumed) override;
  void ReInitialize_StationaryQubit(qrsa::IQubitRecord* const qubit_record, bool consumed) override;

  void applyXGate(qrsa::IQubitRecord* const qubit_record) override;
  void applyZGate(qrsa::IQubitRecord* const qubit_record) override;
  void applyYGate(qrsa::IQubitRecord* const qubit_record) override;
  utils::ComponentProvider provider;
};

}  // namespace modules
}  // namespace quisp

#endif /* QUISP_MODULES_REALTIMECONTROLLER_H_ */

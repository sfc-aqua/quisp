/** \file RealTimeController.h
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
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
 *  \todo Documentation of the class header.
 *
 *  \brief RealTimeController
 */
class RealTimeController : public IRealTimeController {
 private:
  int myAddress;

 protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage* msg) override;
<<<<<<< HEAD
  virtual cModule* getQNode();
  virtual cModule* getRGSsource();

 public:
  virtual void EmitPhoton(int qnic_index, int qubit_index, QNIC_type qnic_type, int pulse);
  virtual void EmitPhotonForRGS(int qnic_index, int qubit_index, QNIC_type);
  virtual void ReInitialize_StationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type, bool consumed);
=======

 public:
  RealTimeController();
  void EmitPhoton(int qnic_index, int qubit_index, QNIC_type qnic_type, int pulse) override;
  void ReInitialize_StationaryQubit(int qnic_index, int qubit_index, QNIC_type qnic_type, bool consumed) override;
  utils::ComponentProvider provider;
>>>>>>> bd4fd5195299815cf4a4c38482adc09cd42e3a38
};

}  // namespace modules
}  // namespace quisp

#endif /* QUISP_MODULES_REALTIMECONTROLLER_H_ */

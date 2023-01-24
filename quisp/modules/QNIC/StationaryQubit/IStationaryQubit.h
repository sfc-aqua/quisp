#pragma once

#include <PhotonicQubit_m.h>
#include <backends/Backends.h>
#include <Eigen/Eigen>
#include <unordered_set>

namespace quisp {

namespace types {
using quisp::backends::EigenvalueResult;
using quisp::backends::MeasurementOutcome;
using quisp::backends::MeasureXResult;
using quisp::backends::MeasureYResult;
using quisp::backends::MeasureZResult;

}  // namespace types

namespace modules {

class IStationaryQubit : public omnetpp::cSimpleModule {
 public:
  IStationaryQubit(){};
  virtual ~IStationaryQubit(){};

  // RTC
  virtual void setFree(bool consumed) = 0;
  /*In use. E.g. waiting for purification result.*/
  virtual void Lock(unsigned long rs_id, int rule_id, int action_id) = 0;
  virtual void Unlock() = 0;
  virtual bool isLocked() = 0;

  /**
   * \brief Emit photon.
   * \param pulse is 1 for the beginning of the burst, 2 for the end.
   */
  virtual void emitPhoton(int pulse) = 0;
  virtual types::MeasureXResult correlationMeasureX() = 0;
  virtual types::MeasureYResult correlationMeasureY() = 0;
  virtual types::MeasureZResult correlationMeasureZ() = 0;

  virtual types::EigenvalueResult localMeasureX() = 0;
  virtual types::EigenvalueResult localMeasureY() = 0;
  virtual types::EigenvalueResult localMeasureZ() = 0;

  /**
   * Performs measurement and returns +(true) or -(false) based on the density matrix of the state. Used for tomography.
   * */
  // RandomMeasureAction
  virtual types::MeasurementOutcome measure_density_independent() = 0; /*Separate dm calculation*/

  // SwappingAction, SimultaneousSwappingAction
  virtual void CNOT_gate(IStationaryQubit *control_qubit) = 0;
  // SimultaneousSwappingAction
  virtual void Hadamard_gate() = 0;
  // RTC
  virtual void Z_gate() = 0;
  virtual void X_gate() = 0;
  // Action
  virtual bool Xpurify(IStationaryQubit *resource_qubit) = 0;
  virtual bool Zpurify(IStationaryQubit *resource_qubit) = 0;

  /*GOD parameters*/
  // SwappingAction
  virtual void setEntangledPartnerInfo(IStationaryQubit *partner) = 0;
  virtual backends::IQubit *getEntangledPartner() const = 0;
  virtual backends::IQubit *getBackendQubitRef() const = 0;
  virtual int getPartnerStationaryQubitAddress() const = 0;
  virtual void assertEntangledPartnerValid() = 0;

  int qnic_address;
  int qnic_type;
  int qnic_index;
  int action_index;
};
}  // namespace modules
}  // namespace quisp

#pragma once
#include <stdexcept>
namespace quisp::backends::abstract {

enum class MeasureXResult : int {
  NO_Z_ERROR,
  HAS_Z_ERROR,
};
enum class MeasureYResult : int {
  NO_XZ_ERROR,
  HAS_XZ_ERROR,
};
enum class MeasureZResult : int {
  NO_X_ERROR,
  HAS_X_ERROR,
};
enum class EigenvalueResult : int {
  PLUS_ONE,
  MINUS_ONE,
};
enum Basis{
  X,
  Y,
  Z,
};
struct MeasurementOutcome {
  Basis basis;
  bool outcome_is_plus;
  char GOD_clean;
  bool operator==(const MeasurementOutcome &outcome) const { return basis == outcome.basis && outcome_is_plus == outcome.outcome_is_plus && GOD_clean == outcome.GOD_clean; }
};

class IQubitId;

class IQubit {
 public:
  IQubit(){};
  virtual ~IQubit(){};

  virtual void setFree() = 0;
  virtual const IQubitId *const getId() const { throw std::runtime_error("getId is not implemented"); }
  virtual void relaseBackToPool() { throw std::runtime_error("release back to pool is not implemented. Is this a short-live qubit?"); }

  // single qubit operations
  virtual void gateX() { throw std::runtime_error("gateX not implemented"); }
  virtual void gateY() { throw std::runtime_error("gateY not implemented"); }
  virtual void gateZ() { throw std::runtime_error("gateZ not implemented"); }
  virtual void gateI() { throw std::runtime_error("gateI not implemented"); }
  virtual void gateH() { throw std::runtime_error("gateH not implemented"); }
  virtual void gateT() { throw std::runtime_error("gateT not implemented"); }
  virtual void gateS() { throw std::runtime_error("gateS not implemented"); }
  virtual void gateSdg() { throw std::runtime_error("gateS not implemented"); }

  // two qubit operations
  virtual void gateCNOT(IQubit *const target_qubit) { throw std::runtime_error("gateCNOT not implemented"); };
  virtual void gateCZ(IQubit *const target_qubit) { throw std::runtime_error("gateCZ not implemented"); };

  // ideal noiseless operations
  virtual void noiselessX() { throw std::runtime_error("noiselessX not implemented"); }
  virtual void noiselessZ() { throw std::runtime_error("noiselessZ not implemented"); }
  virtual void noiselessH() { throw std::runtime_error("noiselessH not implemented"); }
  virtual void noiselessCNOT(IQubit *const target_qubit) { throw std::runtime_error("noiselessCNOT not implemented"); }
  virtual EigenvalueResult noiselessMeasureZ() { throw std::runtime_error("noiselessMeasureZ not implemented"); }
  virtual EigenvalueResult noiselessMeasureX() { throw std::runtime_error("noiselessMeasureX not implemented"); }
  virtual EigenvalueResult noiselessMeasureZ(EigenvalueResult forced_result) { throw std::runtime_error("noiselessMeasureZ not implemented"); }
  virtual EigenvalueResult noiselessMeasureX(EigenvalueResult forced_result) { throw std::runtime_error("noiselessMeasureX not implemented"); }

  // measurements
  virtual EigenvalueResult measureX() { throw std::runtime_error("measureX not implemented"); }
  virtual EigenvalueResult measureY() { throw std::runtime_error("measureY not implemented"); }
  virtual EigenvalueResult measureZ() { throw std::runtime_error("measureZ not implemented"); }
};

}  // namespace quisp::backends::abstract

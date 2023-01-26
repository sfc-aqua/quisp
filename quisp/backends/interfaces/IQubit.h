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
struct MeasurementOutcome {
  char basis;
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

  // // single qubit operations
  virtual void gateX() { throw std::runtime_error("gateX not implemented"); }
  virtual void gateY() { throw std::runtime_error("gateY not implemented"); }
  virtual void gateZ() { throw std::runtime_error("gateZ not implemented"); }
  virtual void gateI() { throw std::runtime_error("gateI not implemented"); }
  virtual void gateH() { throw std::runtime_error("gateH not implemented"); }
  virtual void gateT() { throw std::runtime_error("gateT not implemented"); }
  virtual void gateS() { throw std::runtime_error("gateS not implemented"); }
  virtual void gateSdg() { throw std::runtime_error("gateS not implemented"); }

  // two qubit operations
  virtual void gateCNOT(IQubit *const control_qubit) { throw std::runtime_error("gateCNOT not implemented"); };
  virtual void gateCZ(IQubit *const control_qubit) { throw std::runtime_error("gateCZ not implemented"); };

  // measurements
  virtual EigenvalueResult measureX() { throw std::runtime_error("measureX not implemented"); }
  virtual EigenvalueResult measureY() { throw std::runtime_error("measureY not implemented"); }
  virtual EigenvalueResult measureZ() { throw std::runtime_error("measureZ not implemented"); }
  virtual MeasurementOutcome measureRandomPauliBasis() { throw std::runtime_error("measureRandomPauliBasis not implemented"); }  // for debugging
  // for debugging
  virtual void assertEntangledPartnerValid() { throw std::runtime_error("assertEntangledPartnerValid not implemented"); };

  // deprecated (ErrorTraciking Qubit specific)
  virtual void addErrorX() { throw std::runtime_error("addErrorX is not implemented. will be removed"); }
  virtual void addErrorZ() { throw std::runtime_error("addErrorZ is not implemented. will be removed"); }
  virtual void setCompletelyMixedState() { throw std::runtime_error("setCompletelyMixedState is not implemented. will be removed"); }
  virtual void setMaximallyEntangledWith(IQubit *const partner) { throw std::runtime_error("setMaximallyEntangledWith is not implemented. will be removed"); }
    virtual IQubit *const getEntangledPartner() const { throw std::runtime_error("getEntangledPartner is not implemented. will be removed"); }
};

}  // namespace quisp::backends::abstract

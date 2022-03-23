#include <stdexcept>
namespace quisp::backends::abstract {
class IQubit {
 public:
  IQubit(){};
  virtual ~IQubit(){};

  virtual void setFree() = 0;
  // // single qubit operations
  virtual void gateX() { throw std::runtime_error("gateX not implemented"); }
  virtual void gateY() { throw std::runtime_error("gateY not implemented"); }
  virtual void gateZ() { throw std::runtime_error("gateZ not implemented"); }
  virtual void gateI() { throw std::runtime_error("gateI not implemented"); }
  virtual void gateH() { throw std::runtime_error("gateH not implemented"); }
  virtual void gateT() { throw std::runtime_error("gateT not implemented"); }
  virtual void gateS() { throw std::runtime_error("gateS not implemented"); }

  // two qubit operations
  virtual void gateCNOT(IQubit *const control_qubit) { throw std::runtime_error("gateCNOT not implemented"); };
  virtual void gateCZ(IQubit *const control_qubit) { throw std::runtime_error("gateCZ not implemented"); };
  virtual bool purifyX(IQubit *const control_qubit) { throw std::runtime_error("gateCZ not implemented"); };
  virtual bool purifyZ(IQubit *const target_qubit) { throw std::runtime_error("gateCZ not implemented"); };
};

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
}  // namespace quisp::backends::abstract

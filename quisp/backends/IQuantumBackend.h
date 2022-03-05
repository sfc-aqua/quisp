#pragma once
#include <omnetpp/simtime_t.h>
#include <functional>
#include <tuple>
#include "IQubitId.h"
#include "omnetpp/simtime.h"

namespace quisp::backends::abstract {

using omnetpp::SimTime;
using omnetpp::SimTimeUnit;
class IQubit;

class IQuantumBackend {
 public:
  IQuantumBackend(){};
  virtual ~IQuantumBackend(){};

  virtual IQubit* getQubit(const IQubitId* id) = 0;
  virtual const SimTime& getSimTime() = 0;
  virtual void setSimTime(SimTime time) = 0;

 protected:
};

class IQubit {
 public:
  IQubit(){};
  virtual ~IQubit(){};

  // // single qubit operations
  // virtual void gateX() = 0;
  // virtual void gateY() = 0;
  // virtual void gateZ() = 0;
  // virtual void gateI() = 0;
  // virtual void gateH() = 0;
  // virtual void gateT() = 0;
  // virtual void gateS() = 0;
  // virtual void gateRx() = 0;
  // virtual void gateRy() = 0;
  // virtual void gateRz() = 0;

  // // two qubit operations
  // virtual void gateCNOT(IQubit const* target) = 0;
  // virtual void gateCZ(IQubit const* anoter) = 0;
  // virtual void gateSWAP() = 0;
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

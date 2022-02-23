#pragma once

namespace quisp::backends::abstract {
using QubitId = int;

class IQubit;

class IQuantumBackend {
 public:
  IQuantumBackend(){};
  virtual ~IQuantumBackend(){};

  virtual IQubit* getQubit(QubitId id) = 0;

 protected:
};

class IQubit {
 public:
  IQubit(){};
  virtual ~IQubit(){};

  // single qubit operations
  virtual void gateX() = 0;
  virtual void gateY() = 0;
  virtual void gateZ() = 0;
  virtual void gateI() = 0;
  virtual void gateH() = 0;
  virtual void gateT() = 0;
  virtual void gateS() = 0;
  virtual void gateRx() = 0;
  virtual void gateRy() = 0;
  virtual void gateRz() = 0;

  // two qubit operations
  virtual void gateCNOT(IQubit const* target) = 0;
  virtual void gateCZ(IQubit const* anoter) = 0;
  virtual void gateSWAP() = 0;
};
}  // namespace quisp::backends::abstract

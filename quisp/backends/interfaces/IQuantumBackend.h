#pragma once
#include <omnetpp/simtime_t.h>
#include <memory>
#include "IConfiguration.h"
#include "IQubitId.h"

namespace quisp::backends::abstract {

using omnetpp::SimTime;
using omnetpp::SimTimeUnit;
class IQubit;

/**
 * @brief The abstract interface for a quantum backend.
 *
 * the QuantumBackend class manages its own qubits and the simulator instance.
 * It is responsible for creating qubits and managing their lifecycle.
 */
class IQuantumBackend {
 public:
  IQuantumBackend(){};
  virtual ~IQuantumBackend(){};

  virtual IQubit* createQubit(const IQubitId* id, std::unique_ptr<IConfiguration> conf) = 0;
  virtual IQubit* createQubit(const IQubitId* id) = 0;
  virtual IQubit* getQubit(const IQubitId* id) = 0;
  virtual void deleteQubit(const IQubitId* id) = 0;
  virtual std::unique_ptr<IConfiguration> getDefaultConfiguration() const = 0;
  virtual const SimTime& getSimTime() = 0;
  virtual void setSimTime(SimTime time) = 0;

 protected:
};

}  // namespace quisp::backends::abstract

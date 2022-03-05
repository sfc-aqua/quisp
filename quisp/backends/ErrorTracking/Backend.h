#pragma once
#include <omnetpp.h>
#include <unordered_map>
#include "../IQuantumBackend.h"
#include "../IRandomNumberGenerator.h"
#include "Qubit.h"

namespace quisp::backends::error_tracking {
using abstract::IQuantumBackend;
using abstract::IQubit;
using abstract::IQubitId;
using abstract::IRandomNumberGenerator;
using error_tracking::ErrorTrackingQubit;
using omnetpp::SimTime;

class ErrorTrackingBackend : public IQuantumBackend {
 public:
  ErrorTrackingBackend(IRandomNumberGenerator* const rng);
  ~ErrorTrackingBackend() {}
  IQubit* getQubit(const IQubitId* id) override;
  const SimTime& getSimTime() override;
  void setSimTime(SimTime time) override;
  double dblrand();

 protected:
  std::unordered_map<const IQubitId*, std::unique_ptr<ErrorTrackingQubit>> qubits;
  SimTime current_time;
  IRandomNumberGenerator* rng;
};

}  // namespace quisp::backends::error_tracking

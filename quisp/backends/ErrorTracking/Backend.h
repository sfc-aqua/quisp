#pragma once
#include <omnetpp.h>
#include <memory>
#include <unordered_map>

#include "../interfaces/IConfiguration.h"
#include "../interfaces/IQuantumBackend.h"
#include "../interfaces/IQubitId.h"
#include "../interfaces/IRandomNumberGenerator.h"
#include "Configuration.h"
#include "Qubit.h"

namespace quisp::backends::error_tracking {
using abstract::IConfiguration;
using abstract::IQuantumBackend;
using abstract::IQubit;
using abstract::IQubitId;
using abstract::IRandomNumberGenerator;
using error_tracking::ErrorTrackingQubit;
using omnetpp::SimTime;

class ErrorTrackingBackend : public IQuantumBackend {
 public:
  ErrorTrackingBackend(std::unique_ptr<IRandomNumberGenerator> rng, std::unique_ptr<ErrorTrackingConfiguration> configuration);
  ~ErrorTrackingBackend();
  IQubit* getQubit(const IQubitId* id) override;
  IQubit* getQubit(const IQubitId* id, std::unique_ptr<IConfiguration> configuration) override;
  std::unique_ptr<IConfiguration> getDefaultConfiguration() const override;
  const SimTime& getSimTime() override;
  void setSimTime(SimTime time) override;
  double dblrand();

 protected:
  std::unordered_map<const IQubitId*, std::unique_ptr<ErrorTrackingQubit>, IQubitId::Hash, IQubitId::Pred> qubits;
  SimTime current_time;
  const std::unique_ptr<IRandomNumberGenerator> rng;
  std::unique_ptr<ErrorTrackingConfiguration> config;
};

}  // namespace quisp::backends::error_tracking

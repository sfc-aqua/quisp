#pragma once
#include <modules/common_types.h>
#include <omnetpp.h>
#include <memory>
#include "RNG.h"
#include "backends/GraphState/Qubit.h"
#include "backends/QubitConfiguration.h"

namespace quisp::modules::backend {
using quisp::modules::common::GraphStateBackend;
using quisp::modules::common::IQuantumBackend;
using quisp::modules::common::StationaryQubitConfiguration;
using rng::RNG;

class BackendContainer : public omnetpp::cSimpleModule, GraphStateBackend::ICallback {
 public:
  BackendContainer();
  ~BackendContainer();

  void initialize() override;
  void finish() override;

  IQuantumBackend* getQuantumBackend();
  void willUpdate(GraphStateBackend& backend) override;

 protected:
  std::unique_ptr<StationaryQubitConfiguration> getDefaultQubitErrorModelConfiguration();
  std::unique_ptr<IQuantumBackend> backend = nullptr;
};

Define_Module(BackendContainer);
}  // namespace quisp::modules::backend

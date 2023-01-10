#pragma once
#include <modules/common_types.h>
#include <omnetpp.h>
#include <memory>
#include "RNG.h"
#include "backends/ErrorTracking/Qubit.h"
#include "backends/GraphStateStabilizer/Qubit.h"

namespace quisp::modules::backend {
using quisp::modules::common::ErrorTrackingBackend;
using quisp::modules::common::ErrorTrackingConfiguration;
using quisp::modules::common::GraphStateStabilizerBackend;
using quisp::modules::common::GraphStateStabilizerConfiguration;
using quisp::modules::common::IQuantumBackend;
using rng::RNG;

class BackendContainer : public omnetpp::cSimpleModule, ErrorTrackingBackend::ICallback, GraphStateStabilizerBackend::ICallback {
 public:
  BackendContainer();
  ~BackendContainer();

  void initialize() override;
  void finish() override;

  IQuantumBackend* getQuantumBackend();
  void willUpdate(ErrorTrackingBackend& backend) override;
  void willUpdate(GraphStateStabilizerBackend& backend) override;

 protected:
  void configureErrorTrackingBackend();
  void configureGraphStateStabilizerBackend();
  std::unique_ptr<IQuantumBackend> backend = nullptr;
};

Define_Module(BackendContainer);
}  // namespace quisp::modules::backend

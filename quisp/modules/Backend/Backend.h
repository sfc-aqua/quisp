#pragma once
#include <modules/common_types.h>
#include <omnetpp.h>
#include <memory>
#include "RNG.h"
#include "backends/ErrorTracking/Qubit.h"
#include "backends/GraphState/Qubit.h"

namespace quisp::modules::backend {
using quisp::modules::common::ErrorTrackingBackend;
using quisp::modules::common::ErrorTrackingConfiguration;
using quisp::modules::common::GraphStateBackend;
using quisp::modules::common::GraphStateConfiguration;
using quisp::modules::common::IQuantumBackend;
using rng::RNG;

class BackendContainer : public omnetpp::cSimpleModule, ErrorTrackingBackend::ICallback, GraphStateBackend::ICallback {
 public:
  BackendContainer();
  ~BackendContainer();

  void initialize() override;
  void finish() override;

  IQuantumBackend* getQuantumBackend();
  void willUpdate(ErrorTrackingBackend& backend) override;
  void willUpdate(GraphStateBackend& backend) override;

 protected:
  void configureErrorTrackingBackend();
  void configureGraphStateBackend();
  std::unique_ptr<IQuantumBackend> backend = nullptr;
};

Define_Module(BackendContainer);
}  // namespace quisp::modules::backend

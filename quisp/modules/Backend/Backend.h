#pragma once
#include <modules/common_types.h>
#include <omnetpp.h>
#include <memory>
#include "RNG.h"

namespace quisp::modules::backend {
using quisp::modules::common::ErrorTrackingBackend;
using quisp::modules::common::ErrorTrackingConfiguration;
using quisp::modules::common::IQuantumBackend;
using rng::RNG;

class BackendContainer : public omnetpp::cSimpleModule {
 public:
  BackendContainer();
  ~BackendContainer();

  void initialize() override;
  void finish() override;

  IQuantumBackend* getQuantumBackend();

 protected:
  void configureErrorTrackingBackend();
  std::unique_ptr<IQuantumBackend> backend;
};

Define_Module(BackendContainer);
}  // namespace quisp::modules::backend

#pragma once
#include <modules/common_types.h>
#include <omnetpp.h>
#include <memory>
#include "RNG.h"

namespace quisp::modules::backend {
using quisp::modules::common::ErrorTrackingBackend;
using quisp::modules::common::IQuantumBackend;
using rng::RNG;

class BackendContainer : public omnetpp::cSimpleModule {
 public:
  BackendContainer();
  ~BackendContainer();

  void initialize() override {
    auto backend_type = std::string(par("backendType").stringValue());
    rng = std::make_unique<RNG>(this);
    if (backend_type == "ErrorTrackingBackend") {
      backend = std::make_unique<ErrorTrackingBackend>(rng.get());
    } else {
      throw omnetpp::cRuntimeError("Unknown backend type: %s", backend_type.c_str());
    }
  }

  void finish() override {}

  IQuantumBackend* getQuantumBackend() {
    if (backend == nullptr) {
      throw omnetpp::cRuntimeError("Backend is not initialized");
    }
    return backend.get();
  }

 protected:
  std::unique_ptr<IQuantumBackend> backend;
  std::unique_ptr<RNG> rng;
};

Define_Module(BackendContainer);
}  // namespace quisp::modules::backend

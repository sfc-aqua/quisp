#pragma once
#include <backends/Backends.h>
#include <omnetpp.h>
#include "omnetpp/regmacros.h"

namespace quisp::modules::backend {
using quisp::backends::ErrorTrackingBackend;
using quisp::backends::IQuantumBackend;

class BackendContainer : public omnetpp::cSimpleModule {
 public:
  BackendContainer();
  ~BackendContainer();

  void initialize() override {
    auto backend_type = std::string(par("backendType").stringValue());
    if (backend_type == "ErrorTrackingBackend") {
      backend = new ErrorTrackingBackend();
    } else {
      throw omnetpp::cRuntimeError("Unknown backend type: %s", backend_type.c_str());
    }
  }

  void finish() override {}

  IQuantumBackend* getQuantumBackend() {
    if (backend == nullptr) {
      throw omnetpp::cRuntimeError("Backend is not initialized");
    }
    return backend;
  }

 protected:
  IQuantumBackend* backend;
};

Define_Module(BackendContainer);
}  // namespace quisp::modules::backend

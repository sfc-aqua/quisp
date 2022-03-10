#include "Backend.h"

namespace quisp::modules::backend {
BackendContainer::BackendContainer() {}
BackendContainer::~BackendContainer() {}
void BackendContainer::initialize() {
  auto backend_type = std::string(par("backendType").stringValue());
  if (backend_type == "ErrorTrackingBackend") {
    backend = std::make_unique<ErrorTrackingBackend>(std::make_unique<RNG>(this));
  } else {
    throw omnetpp::cRuntimeError("Unknown backend type: %s", backend_type.c_str());
  }
}

void BackendContainer::finish() {}

IQuantumBackend* BackendContainer::getQuantumBackend() {
  if (backend == nullptr) {
    throw omnetpp::cRuntimeError("Backend is not initialized");
  }
  return backend.get();
}

}  // namespace quisp::modules::backend

#include "Backend.h"

namespace quisp::modules::backend {

BackendContainer::BackendContainer() {}

BackendContainer::~BackendContainer() {}

void BackendContainer::initialize() {
  auto backend_type = std::string(par("backendType").stringValue());
  if (backend_type == "ErrorTrackingBackend") {
    configureErrorTrackingBackend();
  } else {
    throw omnetpp::cRuntimeError("Unknown backend type: %s", backend_type.c_str());
  }
}

void BackendContainer::configureErrorTrackingBackend() {
  auto conf = std::make_unique<ErrorTrackingConfiguration>();
  conf->measurement_x_err_rate = par("Measurement_X_error_ratio").doubleValue();
  conf->measurement_y_err_rate = par("Measurement_Y_error_ratio").doubleValue();
  conf->measurement_z_err_rate = par("Measurement_Z_error_ratio").doubleValue();

  conf->h_gate_err_rate = par("Hgate_error_rate").doubleValue();
  conf->h_gate_x_err_ratio = par("Hgate_X_error_ratio").doubleValue();
  conf->h_gate_y_err_ratio = par("Hgate_Y_error_ratio").doubleValue();
  conf->h_gate_z_err_ratio = par("Hgate_Z_error_ratio").doubleValue();

  conf->x_gate_err_rate = par("Xgate_error_rate").doubleValue();
  conf->x_gate_x_err_ratio = par("Xgate_X_error_ratio").doubleValue();
  conf->x_gate_y_err_ratio = par("Xgate_Y_error_ratio").doubleValue();
  conf->x_gate_z_err_ratio = par("Xgate_Z_error_ratio").doubleValue();

  conf->z_gate_err_rate = par("Zgate_error_rate").doubleValue();
  conf->z_gate_x_err_ratio = par("Zgate_X_error_ratio").doubleValue();
  conf->z_gate_y_err_ratio = par("Zgate_Y_error_ratio").doubleValue();
  conf->z_gate_z_err_ratio = par("Zgate_Z_error_ratio").doubleValue();

  conf->cnot_gate_err_rate = par("CNOTgate_error_rate").doubleValue();
  conf->cnot_gate_iz_err_ratio = par("CNOTgate_IZ_error_ratio").doubleValue();
  conf->cnot_gate_zi_err_ratio = par("CNOTgate_ZI_error_ratio").doubleValue();
  conf->cnot_gate_zz_err_ratio = par("CNOTgate_ZZ_error_ratio").doubleValue();
  conf->cnot_gate_ix_err_ratio = par("CNOTgate_IX_error_ratio").doubleValue();
  conf->cnot_gate_xi_err_ratio = par("CNOTgate_XI_error_ratio").doubleValue();
  conf->cnot_gate_xx_err_ratio = par("CNOTgate_XX_error_ratio").doubleValue();
  conf->cnot_gate_iy_err_ratio = par("CNOTgate_IY_error_ratio").doubleValue();
  conf->cnot_gate_yi_err_ratio = par("CNOTgate_YI_error_ratio").doubleValue();
  conf->cnot_gate_yy_err_ratio = par("CNOTgate_YY_error_ratio").doubleValue();

  conf->memory_x_err_rate = par("memory_X_error_rate").doubleValue();
  conf->memory_y_err_rate = par("memory_Y_error_rate").doubleValue();
  conf->memory_z_err_rate = par("memory_Z_error_rate").doubleValue();
  conf->memory_excitation_rate = par("memory_energy_excitation_rate").doubleValue();
  conf->memory_relaxation_rate = par("memory_energy_relaxation_rate").doubleValue();
  conf->memory_completely_mixed_rate = par("memory_completely_mixed_rate").doubleValue();

  backend = std::make_unique<ErrorTrackingBackend>(std::make_unique<RNG>(this), std::move(conf));
}

void BackendContainer::finish() {}

IQuantumBackend* BackendContainer::getQuantumBackend() {
  if (backend == nullptr) {
    throw omnetpp::cRuntimeError("Backend is not initialized");
  }
  return backend.get();
}

}  // namespace quisp::modules::backend

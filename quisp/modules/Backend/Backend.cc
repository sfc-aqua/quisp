#include "Backend.h"
#include "backends/ErrorTracking/Qubit.h"

namespace quisp::modules::backend {

BackendContainer::BackendContainer() {}

BackendContainer::~BackendContainer() {}

void BackendContainer::initialize() {
  auto backend_type = std::string(par("backend_type").stringValue());
  if (backend_type == "ErrorTrackingBackend") {
    configureErrorTrackingBackend();
  } else if (backend_type == "GraphStateStabilizerBackend") {
    configureGraphStateStabilizerBackend();
  } else {
    throw omnetpp::cRuntimeError("Unknown backend type: %s", backend_type.c_str());
  }
}

void BackendContainer::configureErrorTrackingBackend() {
  auto conf = std::make_unique<ErrorTrackingConfiguration>();
  conf->measurement_x_err_rate = par("x_measurement_error_rate").doubleValue();
  conf->measurement_y_err_rate = par("y_measurement_error_rate").doubleValue();
  conf->measurement_z_err_rate = par("z_measurement_error_rate").doubleValue();

  conf->h_gate_err_rate = par("h_gate_error_rate").doubleValue();
  conf->h_gate_x_err_ratio = par("h_gate_x_error_ratio").doubleValue();
  conf->h_gate_y_err_ratio = par("h_gate_y_error_ratio").doubleValue();
  conf->h_gate_z_err_ratio = par("h_gate_z_error_ratio").doubleValue();

  conf->x_gate_err_rate = par("x_gate_error_rate").doubleValue();
  conf->x_gate_x_err_ratio = par("x_gate_x_error_ratio").doubleValue();
  conf->x_gate_y_err_ratio = par("x_gate_y_error_ratio").doubleValue();
  conf->x_gate_z_err_ratio = par("x_gate_z_error_ratio").doubleValue();

  conf->z_gate_err_rate = par("z_gate_error_rate").doubleValue();
  conf->z_gate_x_err_ratio = par("z_gate_x_error_ratio").doubleValue();
  conf->z_gate_y_err_ratio = par("z_gate_y_error_ratio").doubleValue();
  conf->z_gate_z_err_ratio = par("z_gate_z_error_ratio").doubleValue();

  conf->cnot_gate_err_rate = par("cnot_gate_error_rate").doubleValue();
  conf->cnot_gate_iz_err_ratio = par("cnot_gate_iz_error_ratio").doubleValue();
  conf->cnot_gate_zi_err_ratio = par("cnot_gate_zi_error_ratio").doubleValue();
  conf->cnot_gate_zz_err_ratio = par("cnot_gate_zz_error_ratio").doubleValue();
  conf->cnot_gate_ix_err_ratio = par("cnot_gate_ix_error_ratio").doubleValue();
  conf->cnot_gate_xi_err_ratio = par("cnot_gate_xi_error_ratio").doubleValue();
  conf->cnot_gate_xx_err_ratio = par("cnot_gate_xx_error_ratio").doubleValue();
  conf->cnot_gate_iy_err_ratio = par("cnot_gate_iy_error_ratio").doubleValue();
  conf->cnot_gate_yi_err_ratio = par("cnot_gate_yi_error_ratio").doubleValue();
  conf->cnot_gate_yy_err_ratio = par("cnot_gate_yy_error_ratio").doubleValue();

  conf->memory_x_err_rate = par("memory_x_error_rate").doubleValue();
  conf->memory_y_err_rate = par("memory_y_error_rate").doubleValue();
  conf->memory_z_err_rate = par("memory_z_error_rate").doubleValue();
  conf->memory_excitation_rate = par("memory_energy_excitation_rate").doubleValue();
  conf->memory_relaxation_rate = par("memory_energy_relaxation_rate").doubleValue();
  conf->memory_completely_mixed_rate = par("memory_completely_mixed_rate").doubleValue();

  backend = std::make_unique<ErrorTrackingBackend>(std::make_unique<RNG>(this), std::move(conf), static_cast<ErrorTrackingBackend::ICallback*>(this));
}

void BackendContainer::configureGraphStateStabilizerBackend() {
  auto conf = std::make_unique<GraphStateStabilizerConfiguration>();
  conf->measurement_x_err_rate = par("x_measurement_error_rate").doubleValue();
  conf->measurement_y_err_rate = par("y_measurement_error_rate").doubleValue();
  conf->measurement_z_err_rate = par("z_measurement_error_rate").doubleValue();

  conf->h_gate_err_rate = par("h_gate_error_rate").doubleValue();
  conf->h_gate_x_err_ratio = par("h_gate_x_error_ratio").doubleValue();
  conf->h_gate_y_err_ratio = par("h_gate_y_error_ratio").doubleValue();
  conf->h_gate_z_err_ratio = par("h_gate_z_error_ratio").doubleValue();

  conf->x_gate_err_rate = par("x_gate_error_rate").doubleValue();
  conf->x_gate_x_err_ratio = par("x_gate_x_error_ratio").doubleValue();
  conf->x_gate_y_err_ratio = par("x_gate_y_error_ratio").doubleValue();
  conf->x_gate_z_err_ratio = par("x_gate_z_error_ratio").doubleValue();

  conf->z_gate_err_rate = par("z_gate_error_rate").doubleValue();
  conf->z_gate_x_err_ratio = par("z_gate_x_error_ratio").doubleValue();
  conf->z_gate_y_err_ratio = par("z_gate_y_error_ratio").doubleValue();
  conf->z_gate_z_err_ratio = par("z_gate_z_error_ratio").doubleValue();

  conf->cnot_gate_err_rate = par("cnot_gate_error_rate").doubleValue();
  conf->cnot_gate_iz_err_ratio = par("cnot_gate_iz_error_ratio").doubleValue();
  conf->cnot_gate_zi_err_ratio = par("cnot_gate_zi_error_ratio").doubleValue();
  conf->cnot_gate_zz_err_ratio = par("cnot_gate_zz_error_ratio").doubleValue();
  conf->cnot_gate_ix_err_ratio = par("cnot_gate_ix_error_ratio").doubleValue();
  conf->cnot_gate_xi_err_ratio = par("cnot_gate_xi_error_ratio").doubleValue();
  conf->cnot_gate_xx_err_ratio = par("cnot_gate_xx_error_ratio").doubleValue();
  conf->cnot_gate_iy_err_ratio = par("cnot_gate_iy_error_ratio").doubleValue();
  conf->cnot_gate_yi_err_ratio = par("cnot_gate_yi_error_ratio").doubleValue();
  conf->cnot_gate_yy_err_ratio = par("cnot_gate_yy_error_ratio").doubleValue();

  conf->memory_x_err_rate = par("memory_x_error_rate").doubleValue();
  conf->memory_y_err_rate = par("memory_y_error_rate").doubleValue();
  conf->memory_z_err_rate = par("memory_z_error_rate").doubleValue();
  conf->memory_excitation_rate = par("memory_energy_excitation_rate").doubleValue();
  conf->memory_relaxation_rate = par("memory_energy_relaxation_rate").doubleValue();
  conf->memory_completely_mixed_rate = par("memory_completely_mixed_rate").doubleValue();

  backend = std::make_unique<GraphStateStabilizerBackend>(std::make_unique<RNG>(this), std::move(conf), static_cast<GraphStateStabilizerBackend::ICallback*>(this));
}
void BackendContainer::willUpdate(ErrorTrackingBackend& backend) { backend.setSimTime(omnetpp::simTime()); }
void BackendContainer::willUpdate(GraphStateStabilizerBackend& backend) { backend.setSimTime(omnetpp::simTime()); }
void BackendContainer::finish() {}

IQuantumBackend* BackendContainer::getQuantumBackend() {
  if (backend == nullptr) {
    throw omnetpp::cRuntimeError("Backend is not initialized");
  }
  return backend.get();
}

}  // namespace quisp::modules::backend

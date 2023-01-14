#pragma once

#include "../interfaces/IConfiguration.h"
namespace quisp::backends::graph_state {
/**
@brief Configuration class contains all parameters and provides the way to retrieve it
*/
class GraphStateConfiguration : public abstract::IConfiguration {
 public:
  GraphStateConfiguration() {}
  ~GraphStateConfiguration() {}
  // GraphStateConfiguration(const GraphStateConfiguration&c) = default;

  // list up all params
  double memory_x_err_rate;
  double memory_y_err_rate;
  double memory_z_err_rate;
  double memory_excitation_rate;
  double memory_relaxation_rate;
  double memory_completely_mixed_rate;

  double measurement_x_err_rate;
  double measurement_y_err_rate;
  double measurement_z_err_rate;

  double x_gate_x_err_ratio;
  double x_gate_y_err_ratio;
  double x_gate_z_err_ratio;
  double x_gate_err_rate;

  double z_gate_x_err_ratio;
  double z_gate_y_err_ratio;
  double z_gate_z_err_ratio;
  double z_gate_err_rate;

  double h_gate_x_err_ratio;
  double h_gate_y_err_ratio;
  double h_gate_z_err_ratio;
  double h_gate_err_rate;

  double cnot_gate_iz_err_ratio;
  double cnot_gate_zi_err_ratio;
  double cnot_gate_zz_err_ratio;
  double cnot_gate_ix_err_ratio;
  double cnot_gate_xi_err_ratio;
  double cnot_gate_xx_err_ratio;
  double cnot_gate_iy_err_ratio;
  double cnot_gate_yi_err_ratio;
  double cnot_gate_yy_err_ratio;
  double cnot_gate_err_rate;

 protected:
};
}  // namespace quisp::backends::graph_state

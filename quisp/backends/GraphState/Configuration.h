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

  // list up all params
  double memory_x_err_rate = 0;
  double memory_y_err_rate = 0;
  double memory_z_err_rate = 0;
  double memory_excitation_rate = 0;
  double memory_relaxation_rate = 0;
  double memory_completely_mixed_rate = 0;

  double measurement_x_err_rate = 0;
  double measurement_y_err_rate = 0;
  double measurement_z_err_rate = 0;

  double x_gate_x_err_ratio = 0;
  double x_gate_y_err_ratio = 0;
  double x_gate_z_err_ratio = 0;
  double x_gate_err_rate = 0;

  double z_gate_x_err_ratio = 0;
  double z_gate_y_err_ratio = 0;
  double z_gate_z_err_ratio = 0;
  double z_gate_err_rate = 0;

  double h_gate_x_err_ratio = 0;
  double h_gate_y_err_ratio = 0;
  double h_gate_z_err_ratio = 0;
  double h_gate_err_rate = 0;

  double cnot_gate_iz_err_ratio = 0;
  double cnot_gate_zi_err_ratio = 0;
  double cnot_gate_zz_err_ratio = 0;
  double cnot_gate_ix_err_ratio = 0;
  double cnot_gate_xi_err_ratio = 0;
  double cnot_gate_xx_err_ratio = 0;
  double cnot_gate_iy_err_ratio = 0;
  double cnot_gate_yi_err_ratio = 0;
  double cnot_gate_yy_err_ratio = 0;
  double cnot_gate_err_rate = 0;

 protected:
};
}  // namespace quisp::backends::graph_state

#pragma once
#include <Eigen/Eigen>
namespace quisp::backends::graph_state::types {
enum class CliffordOperator : int {
  Id = 0,
  X,
  Y,
  Z,
  RX_INV,
  RX,
  Z_RX_INV,
  Z_RX,
  RY_INV,
  RY,
  H,
  Z_RY,
  S_INV,
  S,
  X_S_INV,
  X_S,
  S_INV_RX_INV,
  S_INV_RX,
  S_RX_INV,
  S_RX,
  S_INV_RY_INV,
  S_INV_RY,
  S_RY_INV,
  S_RY,
};

struct SingleGateErrorModel {
  double pauli_error_rate;  // Overall error rate
  double z_error_rate;
  double x_error_rate;
  double y_error_rate;

  void setParams(double x_ratio, double y_ratio, double z_ratio, double error_rate) {
    double sum = x_ratio + z_ratio + y_ratio;
    pauli_error_rate = error_rate;
    if (sum == 0) {
      x_ratio = 1.;
      z_ratio = 1.;
      y_ratio = 1.;
      sum = 3.;
    }

    x_error_rate = pauli_error_rate * (x_ratio / sum);
    y_error_rate = pauli_error_rate * (y_ratio / sum);
    z_error_rate = pauli_error_rate * (z_ratio / sum);
  }
};

struct TwoQubitGateErrorModel {
  double pauli_error_rate;  // Overall error rate
  double ix_error_rate;
  double iy_error_rate;
  double iz_error_rate;
  double xi_error_rate;
  double xx_error_rate;
  double xy_error_rate;
  double xz_error_rate;
  double yi_error_rate;
  double yx_error_rate;
  double yy_error_rate;
  double yz_error_rate;
  double zi_error_rate;
  double zx_error_rate;
  double zy_error_rate;
  double zz_error_rate;

  void setParams(double error_rate,

                 double ix_ratio, double iy_ratio, double iz_ratio, double xi_ratio, double xx_ratio, double xy_ratio, double xz_ratio, double yi_ratio, double yx_ratio,
                 double yy_ratio, double yz_ratio, double zi_ratio, double zx_ratio, double zy_ratio, double zz_ratio) {
    pauli_error_rate = error_rate;
    double ratio_sum =
        ix_ratio + iy_ratio + iz_ratio + xi_ratio + xx_ratio + xy_ratio + xz_ratio + yi_ratio + yx_ratio + yy_ratio + yz_ratio + zi_ratio + zx_ratio + zy_ratio + zz_ratio;

    if (ratio_sum == 0) {
      ix_ratio = 1.;
      iy_ratio = 1.;
      iz_ratio = 1.;
      xi_ratio = 1.;
      xx_ratio = 1.;
      xy_ratio = 1.;
      xz_ratio = 1.;
      yi_ratio = 1.;
      yx_ratio = 1.;
      yy_ratio = 1.;
      yz_ratio = 1.;
      zi_ratio = 1.;
      zx_ratio = 1.;
      zy_ratio = 1.;
      zz_ratio = 1.;
      ratio_sum = 15.;
    }

    ix_error_rate = pauli_error_rate * (ix_ratio / ratio_sum);
    iy_error_rate = pauli_error_rate * (iy_ratio / ratio_sum);
    iz_error_rate = pauli_error_rate * (iz_ratio / ratio_sum);
    xi_error_rate = pauli_error_rate * (xi_ratio / ratio_sum);
    xx_error_rate = pauli_error_rate * (xx_ratio / ratio_sum);
    xy_error_rate = pauli_error_rate * (xy_ratio / ratio_sum);
    xz_error_rate = pauli_error_rate * (xz_ratio / ratio_sum);
    yi_error_rate = pauli_error_rate * (yi_ratio / ratio_sum);
    yx_error_rate = pauli_error_rate * (yx_ratio / ratio_sum);
    yy_error_rate = pauli_error_rate * (yy_ratio / ratio_sum);
    yz_error_rate = pauli_error_rate * (yz_ratio / ratio_sum);
    zi_error_rate = pauli_error_rate * (zi_ratio / ratio_sum);
    zx_error_rate = pauli_error_rate * (zx_ratio / ratio_sum);
    zy_error_rate = pauli_error_rate * (zy_ratio / ratio_sum);
    zz_error_rate = pauli_error_rate * (zz_ratio / ratio_sum);
  }
};

struct MemoryErrorModel {
  double error_rate;  // Overall error rate
  double z_error_rate;
  double x_error_rate;
  double y_error_rate;
  double excitation_error_rate;
  double relaxation_error_rate;
  double completely_mixed_rate;
};

struct MeasurementErrorModel {
  double x_error_rate;
  double y_error_rate;
  double z_error_rate;
  void setParams(double x, double y, double z) {
    x_error_rate = x;
    y_error_rate = y;
    z_error_rate = z;
  }
};
}  // namespace quisp::backends::graph_state::types

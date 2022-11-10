#include <modules/QNIC/StationaryQubit/IStationaryQubit.h>
#include <Eigen/Eigen>
#include <complex>

namespace quisp::backends::error_tracking {

using Complex = std::complex<double>;

struct emission_error_model {
  double pauli_error_rate;  // Overall error rate
  double Z_error_rate;
  double X_error_rate;
  double Y_error_rate;
  double Loss_error_rate;

  double No_error_ceil;
  double X_error_ceil;
  double Y_error_ceil;
  double Z_error_ceil;
  double Loss_error_ceil;
};

struct SingleGateErrorModel {
  double pauli_error_rate;  // Overall error rate
  double z_error_rate;
  double x_error_rate;
  double y_error_rate;

  double no_error_ceil;
  double z_error_ceil;
  double x_error_ceil;
  double y_error_ceil;

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
    no_error_ceil = 1 - pauli_error_rate;
    x_error_ceil = no_error_ceil + x_error_rate;
    z_error_ceil = x_error_ceil + z_error_rate;
    y_error_ceil = z_error_ceil + y_error_rate;
  }
};

struct TwoQubitGateErrorModel {
  double pauli_error_rate;  // Overall error rate
  double iz_error_rate;
  double zi_error_rate;
  double zz_error_rate;
  double iy_error_rate;
  double yi_error_rate;
  double yy_error_rate;
  double ix_error_rate;
  double xi_error_rate;
  double xx_error_rate;

  double no_error_ceil;
  double iz_error_ceil;
  double zi_error_ceil;
  double zz_error_ceil;
  double iy_error_ceil;
  double yi_error_ceil;
  double yy_error_ceil;
  double ix_error_ceil;
  double xi_error_ceil;
  double xx_error_ceil;

  void setParams(double error_rate, double ix_ratio, double xi_ratio, double xx_ratio, double iz_ratio, double zi_ratio, double zz_ratio, double iy_ratio, double yi_ratio,
                 double yy_ratio) {
    pauli_error_rate = error_rate;
    double ratio_sum = ix_ratio + xi_ratio + xx_ratio + iz_ratio + zi_ratio + zz_ratio + iy_ratio + yi_ratio + yy_ratio;

    if (ratio_sum == 0) {
      ix_ratio = 1.;
      xi_ratio = 1.;
      xx_ratio = 1.;
      iz_ratio = 1.;
      zi_ratio = 1.;
      zz_ratio = 1.;
      iy_ratio = 1.;
      yi_ratio = 1.;
      yy_ratio = 1.;
      ratio_sum = 9.;
    }

    ix_error_rate = pauli_error_rate * (ix_ratio / ratio_sum);
    xi_error_rate = pauli_error_rate * (xi_ratio / ratio_sum);
    xx_error_rate = pauli_error_rate * (xx_ratio / ratio_sum);

    iz_error_rate = pauli_error_rate * (iz_ratio / ratio_sum);
    zi_error_rate = pauli_error_rate * (zi_ratio / ratio_sum);
    zz_error_rate = pauli_error_rate * (zz_ratio / ratio_sum);

    iy_error_rate = pauli_error_rate * (iy_ratio / ratio_sum);
    yi_error_rate = pauli_error_rate * (yi_ratio / ratio_sum);
    yy_error_rate = pauli_error_rate * (yy_ratio / ratio_sum);

    no_error_ceil = 1 - pauli_error_rate;
    ix_error_ceil = no_error_ceil + ix_error_rate;
    xi_error_ceil = ix_error_ceil + xi_error_rate;
    xx_error_ceil = xi_error_ceil + xx_error_rate;

    iz_error_ceil = xx_error_ceil + iz_error_rate;
    zi_error_ceil = iz_error_ceil + zi_error_rate;
    zz_error_ceil = zi_error_ceil + zz_error_rate;

    iy_error_ceil = zz_error_ceil + iy_error_rate;
    yi_error_ceil = iy_error_ceil + yi_error_rate;
    yy_error_ceil = yi_error_ceil + yy_error_rate;
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

struct GOD_error_model {
  bool has_X_error;
  bool has_Z_error;
  bool has_EX_error;
  bool has_RE_error;
  bool has_CM_error;
};

// Matrices of single qubit errors. Used when conducting tomography.
struct SingleQubitErrorModel {
  Eigen::Matrix2cd X;  // double 2*2 matrix
  Eigen::Matrix2cd Y;  // complex double 2*2 matrix
  Eigen::Matrix2cd Z;
  Eigen::Matrix2cd I;
};

struct MeasurementOperator {
  Eigen::Matrix2cd plus;
  Eigen::Matrix2cd minus;
  Eigen::Vector2cd plus_ket;
  Eigen::Vector2cd minus_ket;
  char basis;
};

// Single qubit
struct MeasurementOperators {
  MeasurementOperator x_basis;
  MeasurementOperator z_basis;
  MeasurementOperator y_basis;
  Eigen::Matrix2cd identity;
};

}  // namespace quisp::backends::error_tracking

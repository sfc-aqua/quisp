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
  double Z_error_rate;
  double X_error_rate;
  double Y_error_rate;

  double No_error_ceil;
  double Z_error_ceil;
  double X_error_ceil;
  double Y_error_ceil;

  void setParams(double x_ratio, double y_ratio, double z_ratio) {
    double sum = x_ratio + z_ratio + y_ratio;
    if (sum == 0) {
      x_ratio = 1.;
      z_ratio = 1.;
      y_ratio = 1.;
      sum = 3.;
    }

    X_error_rate = pauli_error_rate * (x_ratio / sum);
    Y_error_rate = pauli_error_rate * (y_ratio / sum);
    Z_error_rate = pauli_error_rate * (z_ratio / sum);
    No_error_ceil = 1 - pauli_error_rate;
    X_error_ceil = No_error_ceil + X_error_rate;
    Z_error_ceil = X_error_ceil + Z_error_rate;
    Y_error_ceil = Z_error_ceil + Y_error_rate;
  }
};

struct TwoQubitGateErrorModel {
  double pauli_error_rate;  // Overall error rate
  double IZ_error_rate;
  double ZI_error_rate;
  double ZZ_error_rate;
  double IY_error_rate;
  double YI_error_rate;
  double YY_error_rate;
  double IX_error_rate;
  double XI_error_rate;
  double XX_error_rate;

  double No_error_ceil;
  double IZ_error_ceil;
  double ZI_error_ceil;
  double ZZ_error_ceil;
  double IY_error_ceil;
  double YI_error_ceil;
  double YY_error_ceil;
  double IX_error_ceil;
  double XI_error_ceil;
  double XX_error_ceil;

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

    IX_error_rate = pauli_error_rate * (ix_ratio / ratio_sum);
    XI_error_rate = pauli_error_rate * (xi_ratio / ratio_sum);
    XX_error_rate = pauli_error_rate * (xx_ratio / ratio_sum);

    IZ_error_rate = pauli_error_rate * (iz_ratio / ratio_sum);
    ZI_error_rate = pauli_error_rate * (zi_ratio / ratio_sum);
    ZZ_error_rate = pauli_error_rate * (zz_ratio / ratio_sum);

    IY_error_rate = pauli_error_rate * (iy_ratio / ratio_sum);
    YI_error_rate = pauli_error_rate * (yi_ratio / ratio_sum);
    YY_error_rate = pauli_error_rate * (yy_ratio / ratio_sum);

    No_error_ceil = 1 - pauli_error_rate;
    IX_error_ceil = No_error_ceil + IX_error_rate;
    XI_error_ceil = IX_error_ceil + XI_error_rate;
    XX_error_ceil = XI_error_ceil + XX_error_rate;

    IZ_error_ceil = XX_error_ceil + IZ_error_rate;
    ZI_error_ceil = IZ_error_ceil + ZI_error_rate;
    ZZ_error_ceil = ZI_error_ceil + ZZ_error_rate;

    IY_error_ceil = ZZ_error_ceil + IY_error_rate;
    YI_error_ceil = IY_error_ceil + YI_error_rate;
    YY_error_ceil = YI_error_ceil + YY_error_rate;
  }
};

struct memory_error_model {
  double error_rate;  // Overall error rate
  double Z_error_rate;
  double X_error_rate;
  double Y_error_rate;
  double excitation_error_rate;
  double relaxation_error_rate;
  double completely_mixed_rate;
};

struct MeasurementErrorModel {
  double x_error_rate;
  double y_error_rate;
  double z_error_rate;
};

// Matrices of single qubit errors. Used when conducting tomography.
struct single_qubit_error {
  Eigen::Matrix2cd X;  // double 2*2 matrix
  Eigen::Matrix2cd Y;  // complex double 2*2 matrix
  Eigen::Matrix2cd Z;
  Eigen::Matrix2cd I;
};

struct measurement_operator {
  Eigen::Matrix2cd plus;
  Eigen::Matrix2cd minus;
  Eigen::Vector2cd plus_ket;
  Eigen::Vector2cd minus_ket;
  char basis;
};

// Single qubit
struct measurement_operators {
  measurement_operator X_basis;
  measurement_operator Z_basis;
  measurement_operator Y_basis;
  Eigen::Matrix2cd identity;
};

}  // namespace quisp::backends::error_tracking

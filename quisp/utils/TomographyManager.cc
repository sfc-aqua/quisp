#include "TomographyManager.h"
#include "omnetpp/cexception.h"

using omnetpp::cRuntimeError;
namespace quisp::utils {

TomographyManager::TomographyManager() {
  Pauli.X << 0, 1, 1, 0;
  Pauli.Y << 0, std::complex<double>(0, -1), std::complex<double>(0, 1), 0;
  Pauli.Z << 1, 0, 0, -1;
  Pauli.I << 1, 0, 0, 1;
}

TomographyManager::~TomographyManager() {}

/// Reconstruct density matrix from tomogrpahy records
/// Data is recorded with qnic_id since there are multiple paths from this node to partner node
/// @param qnic_id
/// @param partner
/// @return density_matrix in Eigen::Matrix4cd
Matrix4cd TomographyManager::reconstructDensityMatrix(int qnic_id, int partner) {
  auto data = tomography_records[std::make_tuple(qnic_id, partner)];

  // II
  double S00 = 1.0;
  double S01 = get_stokes_parameter(data, "XX");
  double S02 = get_stokes_parameter(data, "YY");
  double S03 = get_stokes_parameter(data, "ZZ");

  // XX
  double S10 = get_stokes_parameter(data, "XX");
  double S11 = get_stokes_parameter(data, "XX");
  double S12 = get_stokes_parameter(data, "XY");
  double S13 = get_stokes_parameter(data, "XZ");

  // YY
  double S20 = get_stokes_parameter(data, "YY");
  double S21 = get_stokes_parameter(data, "YX");
  double S22 = get_stokes_parameter(data, "YY");
  double S23 = get_stokes_parameter(data, "YZ");

  // ZZ
  double S30 = get_stokes_parameter(data, "ZZ");
  double S31 = get_stokes_parameter(data, "ZX");
  double S32 = get_stokes_parameter(data, "ZY");
  double S33 = get_stokes_parameter(data, "ZZ");

  double S = get_stokes_parameter(data, "XX");

  Matrix4cd extended_density_matrix_reconstructed =
      (double)1 / (double)4 *
      (S01 * kroneckerProduct(Pauli.I, Pauli.X).eval() + S02 * kroneckerProduct(Pauli.I, Pauli.Y).eval() + S03 * kroneckerProduct(Pauli.I, Pauli.Z).eval() +
       S10 * kroneckerProduct(Pauli.X, Pauli.I).eval() + S11 * kroneckerProduct(Pauli.X, Pauli.X).eval() + S12 * kroneckerProduct(Pauli.X, Pauli.Y).eval() +
       S13 * kroneckerProduct(Pauli.X, Pauli.Z).eval() + S20 * kroneckerProduct(Pauli.Y, Pauli.I).eval() + S21 * kroneckerProduct(Pauli.Y, Pauli.X).eval() +
       S22 * kroneckerProduct(Pauli.Y, Pauli.Y).eval() + S23 * kroneckerProduct(Pauli.Y, Pauli.Z).eval() + S30 * kroneckerProduct(Pauli.Z, Pauli.I).eval() +
       S31 * kroneckerProduct(Pauli.Z, Pauli.X).eval() + S32 * kroneckerProduct(Pauli.Z, Pauli.Y).eval() + S33 * kroneckerProduct(Pauli.Z, Pauli.Z).eval() +
       S * kroneckerProduct(Pauli.I, Pauli.I).eval());
  return extended_density_matrix_reconstructed;
}

// Altepeter, Joseph B., Evan R. Jeffrey, and Paul G. Kwiat. "Photonic state tomography." Advances in atomic, molecular, and optical physics 52 (2005): 105-159.
double TomographyManager::get_stokes_parameter(const std::map<int, TomographyRecord> tomography_records, const std::string basis_combination) {
  int total_count = 0;
  int plus_plus = 0;
  int plus_minus = 0;
  int minus_plus = 0;
  int minus_minus = 0;
  for (const auto& record : tomography_records) {
    if (record.second.get_basis_combination() == basis_combination) {
      auto self_output = record.second.get_self_outcome();
      auto partner_output = record.second.get_partner_outcome();
      if (self_output && partner_output) {
        plus_plus += 1;
      } else if (self_output && !partner_output) {
        plus_minus += 1;
      } else if (!self_output && partner_output) {
        minus_plus += 1;
      } else if (!self_output && partner_output) {
        minus_minus += 1;
      } else {
        throw cRuntimeError("Tomography result unreachable!");
      }
      total_count += 1;
    } else {
      continue;
    }
  }
  auto v = (double)plus_plus / (double)total_count - (double)plus_minus / (double)total_count - (double)minus_plus / (double)total_count + (double)minus_minus / (double)total_count;
  if (std::isnan(v)) {
    throw cRuntimeError("Stokes parameter is NaN. The number of tomography might not be enough.");
  }
};

}  // namespace quisp::utils

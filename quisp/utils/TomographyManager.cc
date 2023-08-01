#include "TomographyManager.h"
#include <map>
#include <memory>
#include <tuple>
#include <utility>
#include "omnetpp/cexception.h"

using omnetpp::cRuntimeError;
using quisp::utils::TomographyManager;

namespace quisp::utils {

TomographyManager::TomographyManager() {
  Pauli.X << 0, 1, 1, 0;
  Pauli.Y << 0, std::complex<double>(0, -1), std::complex<double>(0, 1), 0;
  Pauli.Z << 1, 0, 0, -1;
  Pauli.I << 1, 0, 0, 1;
}

TomographyManager::~TomographyManager() {}

void TomographyManager::addLocalResult(int qnic_id, int partner, unsigned int tomography_round, char measurement_basis, bool is_plus, char my_GOD_clean) {
  TomographyRecord record;
  record.self_record.basis = measurement_basis;
  record.self_record.output_is_plus = is_plus;
  record.self_record.my_GOD_clean = my_GOD_clean;

  // tomography start with partner at qnic_id
  std::map<int, TomographyRecord> ith_record;
  ith_record.insert(std::make_pair(tomography_round, record));

  // Key to get the i th record
  auto partner_key = std::make_tuple(qnic_id, partner);

  // Every time result is inserted, check if the partner record is existing or not
  if (!tomography_records.count(partner_key)) {
    // No partner record found
    auto tomography_record = tomography_records[partner_key];

    // Find i th tomography record
    if (!tomography_record.count(tomography_round)) {
      // No i th tomography record found
      // tomography_records.insert(std::make_pair(partner_key, ith_record));

    } else {
      // i th tomography record found
    }

    // tomography_records.insert(std::make_pair(partner_key, ith_record));
    // existing_record.insert(std::make_pair(tomography_round, record));
  }

  void TomographyManager::addPartnerResult(int self_qnic_id, int partner, unsigned int tomography_round) {}

  /// Reconstruct density matrix from tomogrpahy records
  /// Data is recorded with qnic_id since there are multiple paths from this node to partner node
  /// @param qnic_id
  /// @param partner
  /// @return density_matrix in Eigen::Matrix4cd
  Matrix4cd TomographyManager::reconstructDensityMatrix(int qnic_id, int partner) {
    auto data = tomography_records[std::make_tuple(qnic_id, partner)];

    // II
    double S00 = 1.0;
    double S01 = get_stokes_parameter(data, "XX", std::make_tuple('m', 'p', 'm'));
    double S02 = get_stokes_parameter(data, "YY", std::make_tuple('m', 'p', 'm'));
    double S03 = get_stokes_parameter(data, "ZZ", std::make_tuple('m', 'p', 'm'));

    // XX
    double S10 = get_stokes_parameter(data, "XX", std::make_tuple('p', 'm', 'm'));
    double S11 = get_stokes_parameter(data, "XX", std::make_tuple('m', 'm', 'p'));
    double S12 = get_stokes_parameter(data, "XY", std::make_tuple('m', 'm', 'p'));
    double S13 = get_stokes_parameter(data, "XZ", std::make_tuple('m', 'm', 'p'));

    // YY
    double S20 = get_stokes_parameter(data, "YY", std::make_tuple('p', 'm', 'm'));
    double S21 = get_stokes_parameter(data, "YX", std::make_tuple('m', 'm', 'p'));
    double S22 = get_stokes_parameter(data, "YY", std::make_tuple('m', 'm', 'p'));
    double S23 = get_stokes_parameter(data, "YZ", std::make_tuple('m', 'm', 'p'));

    // ZZ
    double S30 = get_stokes_parameter(data, "ZZ", std::make_tuple('p', 'm', 'm'));
    double S31 = get_stokes_parameter(data, "ZX", std::make_tuple('m', 'm', 'p'));
    double S32 = get_stokes_parameter(data, "ZY", std::make_tuple('m', 'm', 'p'));
    double S33 = get_stokes_parameter(data, "ZZ", std::make_tuple('m', 'm', 'p'));

    double S = get_stokes_parameter(data, "XX", std::make_tuple('p', 'p', 'p'));

    Matrix4cd reconstructed_density_matrix = (double)1 / (double)4 *
                                             (S01 * kroneckerProduct(Pauli.I, Pauli.X).eval() +  // IX
                                              S02 * kroneckerProduct(Pauli.I, Pauli.Y).eval() +  // IY
                                              S03 * kroneckerProduct(Pauli.I, Pauli.Z).eval() +  // IZ
                                              S10 * kroneckerProduct(Pauli.X, Pauli.I).eval() +  // XI
                                              S11 * kroneckerProduct(Pauli.X, Pauli.X).eval() +  // XX
                                              S12 * kroneckerProduct(Pauli.X, Pauli.Y).eval() +  // XY
                                              S13 * kroneckerProduct(Pauli.X, Pauli.Z).eval() +  // XZ
                                              S20 * kroneckerProduct(Pauli.Y, Pauli.I).eval() +  // YI
                                              S21 * kroneckerProduct(Pauli.Y, Pauli.X).eval() +  // YX
                                              S22 * kroneckerProduct(Pauli.Y, Pauli.Y).eval() +  // YY
                                              S23 * kroneckerProduct(Pauli.Y, Pauli.Z).eval() +  // YZ
                                              S30 * kroneckerProduct(Pauli.Z, Pauli.I).eval() +  // ZI
                                              S31 * kroneckerProduct(Pauli.Z, Pauli.X).eval() +  // ZX
                                              S32 * kroneckerProduct(Pauli.Z, Pauli.Y).eval() +  // ZY
                                              S33 * kroneckerProduct(Pauli.Z, Pauli.Z).eval() +  // ZZ
                                              S * kroneckerProduct(Pauli.I, Pauli.I).eval());  // II
    return reconstructed_density_matrix;
  }

  // Altepeter, Joseph B., Evan R. Jeffrey, and Paul G. Kwiat. "Photonic state tomography." Advances in atomic, molecular, and optical physics 52 (2005): 105-159.
  double TomographyManager::get_stokes_parameter(const std::map<int, TomographyRecord> tomography_records, const std::string basis_combination,
                                                 const std::tuple<char, char, char> operators) {
    if (tomography_records.size() == 0) {
      throw cRuntimeError("No tomography result found.");
    }
    int total_count = 0;
    int plus_plus = 0;
    int plus_minus = 0;
    int minus_plus = 0;
    int minus_minus = 0;
    // Go through all the records and count the number of each outcome
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
    if (total_count == 0) {
      throw cRuntimeError("No tomography result found basis for %s. The number of tomography performed for this basis might not be good enough. ", basis_combination.c_str());
    }
    // plus plus
    auto stokes_param = (double)plus_plus / (double)total_count;

    // Currently, the size of operator is limited so that using tuple should be fine.
    // If we have more parameters, we should consider using other ways.
    // plus minus
    if (std::get<0>(operators) == 'p') {
      stokes_param += (double)plus_minus / (double)total_count;
    } else {
      stokes_param -= (double)plus_minus / (double)total_count;
    };

    // minus plus
    if (std::get<1>(operators) == 'p') {
      stokes_param += (double)minus_plus / (double)total_count;
    } else {
      stokes_param -= (double)minus_plus / (double)total_count;
    };

    // minus minus
    if (std::get<2>(operators) == 'p') {
      stokes_param += (double)minus_minus / (double)total_count;
    } else {
      stokes_param -= (double)minus_minus / (double)total_count;
    };
    return stokes_param;
  };

}  // namespace quisp::utils

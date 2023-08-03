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

void TomographyManager::addLocalResult(int qnic_id, int partner, int tomography_round, char measurement_basis, bool is_plus, char my_GOD_clean) {
  // Local measurement result
  TomographyOutput self_record;
  self_record.basis = measurement_basis;
  self_record.output_is_plus = is_plus;
  self_record.my_GOD_clean = my_GOD_clean;

  appendTomographyRecord(std::make_tuple(qnic_id, partner), tomography_round, self_record, true);
}

void TomographyManager::addPartnerResult(int self_qnic_id, int partner, int tomography_round, char measurement_basis, bool is_plus, char my_GOD_clean) {
  TomographyOutput partner_record;
  partner_record.basis = measurement_basis;
  partner_record.output_is_plus = is_plus;
  partner_record.my_GOD_clean = my_GOD_clean;

  appendTomographyRecord(std::make_tuple(self_qnic_id, partner), tomography_round, partner_record, false);
}

void TomographyManager::appendTomographyRecord(std::tuple<int, int> partner_key, int tomography_round, TomographyOutput tomography_output, bool is_self_record) {
  // Check if the partner record has already been prepared

  if (!tomography_records.count(partner_key)) {
    // Tomography record for this partner cannot be found.
    // Even if the tomography round is 0, there might be existing partner key
    // since there is a possibility that the partner node perform measurement
    // earlier than this node.

    if (tomography_round != 0) {
      // Tomography round must be 0 since this must be the first record for this partner.
      throw cRuntimeError("Previous tomography round is not properly recorded.");
    }

    // Prepare the first record for this partner.
    // auto tomography_record = std::make_unique<TomographyRecord>();
    TomographyRecord tomography_record;
    if (is_self_record) {
      // Self record is added, leave partner_record empty here
      tomography_record.self_output = tomography_output;
    } else {
      // Partner record is added, leave self_record empty here
      tomography_record.partner_output = tomography_output;
    }

    // round -> record
    // std::map<int, std::unique_ptr<TomographyRecord>> tomography_round_record;
    std::map<int, TomographyRecord> tomography_round_record;
    tomography_round_record.insert(std::make_pair(tomography_round, tomography_record));
    tomography_records.insert(std::make_pair(partner_key, tomography_round_record));
  } else {
    // Partner key found in the map, add this round of record to the existing parter record.
    // Find i th tomography record
    if (!tomography_records.at(partner_key).count(tomography_round)) {
      // No i th tomography record found
      // Add new tomography record as i th record
      // auto new_tomography_record = std::make_unique<TomographyRecord>();
      TomographyRecord new_tomography_record;
      if (is_self_record) {
        // Self record is added, leave partner_record empty here
        new_tomography_record.self_output = tomography_output;
      } else {
        // Partner record is added, leave self_record empty here
        new_tomography_record.partner_output = tomography_output;
      }
      // Leave partner_record empty here
      tomography_records.at(partner_key).insert(std::make_pair(tomography_round, new_tomography_record));

    } else {
      // i th tomography record found, get reference and update it.
      auto& ith_tomography_record = tomography_records.at(partner_key).at(tomography_round);
      if (is_self_record) {
        // Partner record already exists. Add self record to the existing record.
        ith_tomography_record.self_output = tomography_output;
        // existing_record.setSelfOutput(tomography_output);
      } else {
        // Self record already exists. Add partner record to the existing record.
        ith_tomography_record.partner_output = tomography_output;
      }
    }
  }
};

/// Reconstruct density matrix from tomogrpahy records
/// Data is recorded with qnic_id since there are multiple paths from this node to partner node
/// @param qnic_id
/// @param partner
/// @return density_matrix in Eigen::Matrix4cd
Matrix4cd TomographyManager::reconstructDensityMatrix(int qnic_id, int partner) {
  // Get tomography records for this partner
  if (!tomography_records.count(std::make_tuple(qnic_id, partner))) {
    throw cRuntimeError("Tomography record for this partner is not found.");
  }

  auto partner_key = std::make_tuple(qnic_id, partner);
  // II
  double S00 = 1.0;
  double S01 = getStokesParameter(partner_key, "XX", std::make_tuple('m', 'p', 'm'));
  double S02 = getStokesParameter(partner_key, "YY", std::make_tuple('m', 'p', 'm'));
  double S03 = getStokesParameter(partner_key, "ZZ", std::make_tuple('m', 'p', 'm'));

  // XX
  double S10 = getStokesParameter(partner_key, "XX", std::make_tuple('p', 'm', 'm'));
  double S11 = getStokesParameter(partner_key, "XX", std::make_tuple('m', 'm', 'p'));
  double S12 = getStokesParameter(partner_key, "XY", std::make_tuple('m', 'm', 'p'));
  double S13 = getStokesParameter(partner_key, "XZ", std::make_tuple('m', 'm', 'p'));

  // YY
  double S20 = getStokesParameter(partner_key, "YY", std::make_tuple('p', 'm', 'm'));
  double S21 = getStokesParameter(partner_key, "YX", std::make_tuple('m', 'm', 'p'));
  double S22 = getStokesParameter(partner_key, "YY", std::make_tuple('m', 'm', 'p'));
  double S23 = getStokesParameter(partner_key, "YZ", std::make_tuple('m', 'm', 'p'));

  // ZZ
  double S30 = getStokesParameter(partner_key, "ZZ", std::make_tuple('p', 'm', 'm'));
  double S31 = getStokesParameter(partner_key, "ZX", std::make_tuple('m', 'm', 'p'));
  double S32 = getStokesParameter(partner_key, "ZY", std::make_tuple('m', 'm', 'p'));
  double S33 = getStokesParameter(partner_key, "ZZ", std::make_tuple('m', 'm', 'p'));

  double S = getStokesParameter(partner_key, "XX", std::make_tuple('p', 'p', 'p'));

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
double TomographyManager::getStokesParameter(const std::tuple<int, int> partner_key, const std::string basis_combination, const std::tuple<char, char, char> operators) {
  auto tomography_record = tomography_records.at(partner_key);
  if (tomography_record.size() == 0) {
    throw cRuntimeError("No tomography result found.");
  }
  int total_count = 0;
  int plus_plus = 0;
  int plus_minus = 0;
  int minus_plus = 0;
  int minus_minus = 0;
  // Go through all the records and count the number of each outcome
  for (const auto& record : tomography_record) {
    if (record.second.getBasisCombination() == basis_combination) {
      auto self_output = record.second.getSelfOutcome();
      auto partner_output = record.second.getPartnerOutcome();
      // If there is missing record, ignore it and go next record

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

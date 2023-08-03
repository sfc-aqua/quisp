#pragma once
#include <map>
#include <memory>
#include <tuple>
#include <unsupported/Eigen/KroneckerProduct>
#include "Eigen/src/Core/Matrix.h"
#include "omnetpp/cexception.h"

using Eigen::Matrix2cd;
using Eigen::Matrix4cd;

namespace quisp::utils {

class TomographyManager {
 public:
  TomographyManager();
  ~TomographyManager();

  // Link Tomography RuleSet Generator (deprecated)

  // Tomography Calculation
  void addLocalResult(int qnic_id, int partner, int tomography_round, char measurement_basis, bool is_plus, char my_GOD_clean);
  void addPartnerResult(int self_qnic_id, int partner, int tomography_round, char measurement_basis, bool is_plus, char my_GOD_clean);
  Matrix4cd reconstructDensityMatrix(int qnic_id, int partner);

 protected:
  struct TomographyOutput {
    char basis;
    bool output_is_plus;
    char my_GOD_clean;
  };
  // Store one round result of tomography
  struct TomographyRecord {
    TomographyOutput self_output;
    TomographyOutput partner_output;
    // return basis combination
    std::string getBasisCombination() const {
      if (!self_output.basis || !partner_output.basis) {
        throw omnetpp::cRuntimeError("TomographyRecord is not complete.");
      }
      std::string basis_combination;
      basis_combination.push_back(self_output.basis);
      basis_combination.push_back(partner_output.basis);
      return basis_combination;
    };
    bool getSelfOutcome() const { return self_output.output_is_plus; }
    bool getPartnerOutcome() const { return partner_output.output_is_plus; }
  };
  // <qnic_id, partner> -> <tomography_round, TomographyRecord> -> TomographyRecord
  std::map<std::tuple<int, int>, std::map<int, TomographyRecord>> tomography_records;
  // <tomography_round, TomographyRecord>
  double getStokesParameter(std::tuple<int, int> partner_key, const std::string basis_combination, const std::tuple<char, char, char> operators);

  void appendTomographyRecord(std::tuple<int, int> partner_key, int tomography_round, TomographyOutput tomography_output, bool is_self_record);

 private:
  struct SingleQubitError {
    Matrix2cd X;
    Matrix2cd Y;
    Matrix2cd Z;
    Matrix2cd I;
  };
  SingleQubitError Pauli;
};

}  // namespace quisp::utils

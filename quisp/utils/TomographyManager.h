#pragma once
#include <map>
#include <unsupported/Eigen/KroneckerProduct>
#include "Eigen/src/Core/Matrix.h"

using Eigen::Matrix2cd;
using Eigen::Matrix4cd;

namespace quisp::utils {

class TomographyManager {
 public:
  TomographyManager();
  ~TomographyManager();

  // Link Tomography RuleSet Generator (deprecated)

  // Tomography Calculation
  void addLocalResult();
  void addPartnerResult();
  Matrix4cd reconstructDensityMatrix(int qnic_id, int partner);

 private:
  struct TomographyOutput {
    char basis;
    bool output_is_plus;
    char my_GOD_clean;
  };
  // Store one round result of tomography
  struct TomographyRecord {
    TomographyOutput self_record;
    TomographyOutput partner_record;
    // return basis combination
    std::string get_basis_combination() const {
      std::string basis_combination;
      basis_combination.push_back(self_record.basis);
      basis_combination.push_back(partner_record.basis);
      return basis_combination;
    };
    bool get_self_outcome() const { return self_record.output_is_plus; }
    bool get_partner_outcome() const { return partner_record.output_is_plus; }
  };
  // <qnic_id, partner> -> <tomography_round, TomographyRecord> -> TomographyRecord
  std::map<std::tuple<int, int>, std::map<int, TomographyRecord>> tomography_records;
  // <tomography_round, TomographyRecord>
  double get_stokes_parameter(const std::map<int, TomographyRecord> tomography_records, const std::string basis_combination);

  struct SingleQubitError {
    Matrix2cd X;
    Matrix2cd Y;
    Matrix2cd Z;
    Matrix2cd I;
  };
  SingleQubitError Pauli;
};

}  // namespace quisp::utils

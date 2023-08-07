#pragma once

#include <map>
#include <memory>
#include <tuple>
#include <unsupported/Eigen/KroneckerProduct>
#include "modules/QNIC.h"
#include "omnetpp/cexception.h"

#include "omnetpp/simtime_t.h"
#include "rules/RuleSet.h"

using namespace quisp::rules;
using Eigen::Matrix2cd;
using Eigen::Matrix4cd;

namespace quisp::utils {

class TomographyManager {
 public:
  TomographyManager();
  ~TomographyManager();

  // Performance result of tomography
  struct TomographyStats {
    simtime_t tomography_time;
    double bell_pair_per_sec;
    int total_measurement_count;
  };
  // Link Tomography RuleSet Generator (deprecated)
  [[deprecated("Link Tomography RuleSet creation will be integrated to RuleSet Factory.")]] RuleSet *createLinkTomographyRuleSet(int my_address, int partner_address,
                                                                                                                                 QNIC_type qnic_type, int qnic_index,
                                                                                                                                 unsigned long ruleset_id, int num_purification,
                                                                                                                                 int purification_type, bool x_purification,
                                                                                                                                 bool z_purification, int num_measure);

  // Tomography Calculation
  void addLocalResult(int qnic_id, int partner, int tomography_round, char measurement_basis, bool is_plus, char my_GOD_clean);
  void addPartnerResult(int self_qnic_id, int partner, int tomography_round, char measurement_basis, bool is_plus, char my_GOD_clean);
  void setStats(int qnic_id, int partner, simtime_t tomography_time, double bell_pair_per_sec, int total_measurement_count);
  TomographyStats getStats(int qnic_id, int partner) { return tomography_stats[std::make_tuple(qnic_id, partner)]; };
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

  // <qnic_id, partner> -> TomographyStats
  std::map<std::tuple<int, int>, TomographyStats> tomography_stats;

  // <tomography_round, TomographyRecord>
  double getStokesParameter(std::tuple<int, int> partner_key, const std::string basis_combination, const std::tuple<char, char, char> operators);

  void appendTomographyRecord(std::tuple<int, int> partner_key, int tomography_round, TomographyOutput tomography_output, bool is_self_record);

  [[deprecated]] std::unique_ptr<Rule> constructPurifyRule(int my_address, const std::string &rule_name, const rules::PurType pur_type, const int partner_address,
                                                           const QNIC_type qnic_type, const int qnic_index, const int send_tag) const;

  [[deprecated]] std::unique_ptr<Rule> constructCorrelationCheckRule(const std::string &rule_name, const rules::PurType pur_type, const int partner_address,
                                                                     const QNIC_type qnic_type, const int qnic_index, const int receive_tag) const;

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

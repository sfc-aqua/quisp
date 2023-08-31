#pragma once

#include <modules/QNIC.h>
#include <omnetpp/simtime_t.h>
#include <rules/RuleSet.h>
#include <unsupported/Eigen/KroneckerProduct>

using Eigen::Matrix4cd;
using omnetpp::simtime_t;
using namespace quisp::rules;

namespace quisp::utils {

// Performance result of tomography
struct TomographyStats {
  simtime_t tomography_time;
  double bell_pair_per_sec;
  int total_measurement_count;
};

/**
 * @brief The TomographyManager interface
 *
 * This interface is used to store tomography results and calcualte fidelity
 * The subclass of this interface provides a general way to access the tomography results.
 */
class ITomographyManager {
 public:
  virtual ~ITomographyManager(){};
  virtual void addLocalResult(int qnic_id, int partner, int tomography_round, char measurement_basis, bool is_plus, char my_GOD_clean) = 0;
  virtual void addPartnerResult(int self_qnic_id, int partner, int tomography_round, char measurement_basis, bool is_plus, char my_GOD_clean) = 0;
  virtual void setStats(int qnic_id, int partner, simtime_t tomography_time, double bell_pair_per_sec, int total_measurement_count) = 0;
  virtual double calcFidelity(int qnic_id, int partner) = 0;
  virtual std::tuple<double, double, double> calcErrorRate(int qnic_id, int partner) = 0;
  virtual Matrix4cd reconstructDensityMatrix(int qnic_id, int partner) = 0;
  virtual TomographyStats getStats(int qnic_id, int partner) = 0;
  virtual std::tuple<int, int, int, int> calcGodPairCount(int qnic_id, int partner) = 0;
  virtual RuleSet *createLinkTomographyRuleSet(int my_address, int partner_address, QNIC_type qnic_type, int qnic_index, unsigned long ruleset_id, int num_purification,
                                               int purification_type, bool x_purification, bool z_purification, int num_measure) = 0;
};
}  // namespace quisp::utils

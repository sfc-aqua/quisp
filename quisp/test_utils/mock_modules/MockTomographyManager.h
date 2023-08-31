#pragma once

#include <gmock/gmock.h>
#include <test_utils/TestUtilFunctions.h>
#include <unsupported/Eigen/KroneckerProduct>
#include "utils/ITomographyManager.h"

namespace quisp_test::mock_modules::tomography_manager {

using Eigen::Matrix4cd;
using quisp::utils::ITomographyManager;

class MockTomographyManager : public ITomographyManager {
 public:
  MOCK_METHOD(void, addLocalResult, (int qnic_id, int partner, int tomography_round, char measurement_basis, bool is_plus, char my_GOD_clean), (override));
  MOCK_METHOD(void, addPartnerResult, (int self_qnic_id, int partner, int tomography_round, char measurement_basis, bool is_plus, char my_GOD_clean), (override));
  MOCK_METHOD(void, setStats, (int qnic_id, int partner, omnetpp::simtime_t tomography_time, double bell_pair_per_sec, int total_measurement_count), (override));
  MOCK_METHOD(double, calcFidelity, (int qnic_id, int partner), (override));
  MOCK_METHOD((std::tuple<double, double, double>), calcErrorRate, (int qnic_id, int partner), (override));
  MOCK_METHOD(Matrix4cd, reconstructDensityMatrix, (int qnic_id, int partner), (override));
  MOCK_METHOD(quisp::utils::TomographyStats, getStats, (int qnic_id, int partner), (override));
  MOCK_METHOD((std::tuple<int, int, int, int>), calcGodPairCount, (int qnic_id, int partner), (override));
  MOCK_METHOD(RuleSet *, createLinkTomographyRuleSet,
              (int my_address, int partner_address, QNIC_type qnic_type, int qnic_index, unsigned long ruleset_id, int num_purification, int purification_type, bool x_purification,
               bool z_purification, int num_measure),
              (override));
};
}  // namespace quisp_test::mock_modules::tomography_manager

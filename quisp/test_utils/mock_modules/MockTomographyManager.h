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
};
}  // namespace quisp_test::mock_modules::tomography_manager

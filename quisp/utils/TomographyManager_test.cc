#include "utils/TomographyManager.h"
#include <gtest/gtest.h>
#include "test_utils/TestUtilFunctions.h"
#include "test_utils/TestUtils.h"

namespace {
using namespace quisp_test::utils;
using namespace quisp::utils;

class TomographyManager : public quisp::utils::TomographyManager {
 public:
  using quisp::utils::TomographyManager::addLocalResult;
  using quisp::utils::TomographyManager::tomography_records;
};

class TomographyManagerTest : public testing::Test {
 protected:
  void SetUp() {
    prepareSimulation();
    tomography_manager = new TomographyManager();
  }
  void TearDown() { delete tomography_manager; }
  TomographyManager *tomography_manager;
};

TEST_F(TomographyManagerTest, addLocalResult) {
  // First tomography result arrived
  int qnic_id = 0;
  int partner_addr = 0;

  // tomography results
  int tomography_round = 0;  // first round
  char measurement_basis = 'X';
  bool is_plus = true;
  char my_GOD_clean = 'I';

  tomography_manager->addLocalResult(qnic_id, partner_addr, tomography_round, measurement_basis, is_plus, my_GOD_clean);
  EXPECT_EQ(tomography_manager->tomography_records.size(), 1);
}
}  // namespace

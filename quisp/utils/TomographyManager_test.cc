#include "utils/TomographyManager.h"
#include <gtest/gtest.h>
#include <tuple>
#include "test_utils/TestUtilFunctions.h"
#include "test_utils/TestUtils.h"

namespace {
using namespace quisp_test::utils;
using namespace quisp::utils;

class TomographyManager : public quisp::utils::TomographyManager {
 public:
  using quisp::utils::TomographyManager::addLocalResult;
  using quisp::utils::TomographyManager::tomography_records;
  using quisp::utils::TomographyManager::tomography_stats;
  using quisp::utils::TomographyManager::TomographyOutput;
  using quisp::utils::TomographyManager::TomographyRecord;;
};

class TomographyManagerTest : public testing::Test {
 protected:
  void SetUp() {
    prepareSimulation();
    tomography_manager = new TomographyManager();
  }
  void TearDown() { delete tomography_manager; }
  TomographyManager *tomography_manager;

  // tomography results
  char measurement_basis = 'X';
  bool is_plus = true;
  char my_god_clean = 'I';
};

TEST_F(TomographyManagerTest, addLocalResult) {
  // First tomography result arrived
  int qnic_id = 0;
  int partner_addr = 0;

  int tomography_round = 0;  // first round

  tomography_manager->addLocalResult(qnic_id, partner_addr, tomography_round, measurement_basis, is_plus, my_god_clean);
  EXPECT_EQ(tomography_manager->tomography_records.size(), 1);
  auto stored_record = tomography_manager->tomography_records.at(std::make_tuple(qnic_id, partner_addr));
  EXPECT_EQ(stored_record.at(tomography_round).self_output.basis, measurement_basis);
  EXPECT_EQ(stored_record.at(tomography_round).self_output.output_is_plus, is_plus);
  EXPECT_EQ(stored_record.at(tomography_round).self_output.my_god_clean, my_god_clean);
}

TEST_F(TomographyManagerTest, addPartnerResult) {
  // Accept incoming tomography result
  int self_qnic_id = 0;
  int partner_addr = 1;

  int tomography_round = 0;  // first round

  tomography_manager->addPartnerResult(self_qnic_id, partner_addr, tomography_round, measurement_basis, is_plus, my_god_clean);
  EXPECT_EQ(tomography_manager->tomography_records.size(), 1);
  auto stored_record = tomography_manager->tomography_records.at(std::make_tuple(self_qnic_id, partner_addr));
  EXPECT_EQ(stored_record.at(tomography_round).partner_output.basis, measurement_basis);
  EXPECT_EQ(stored_record.at(tomography_round).partner_output.output_is_plus, is_plus);
  EXPECT_EQ(stored_record.at(tomography_round).partner_output.my_god_clean, my_god_clean);
}

TEST_F(TomographyManagerTest, addPartnerResultToExistingSelfRecord) {
  // Tomography between node 0 <--> node 2
  // Prepare self record
  int qnic_id = 0;
  int partner_addr = 2;

  int tomography_round = 0;

  tomography_manager->addLocalResult(qnic_id, partner_addr, tomography_round, measurement_basis, is_plus, my_god_clean);
  EXPECT_EQ(tomography_manager->tomography_records.size(), 1);

  // add partner record
  int self_qnic_id = 0;  // qnic used to communicate with node 2

  tomography_manager->addPartnerResult(self_qnic_id, partner_addr, tomography_round, measurement_basis, is_plus, my_god_clean);
  // Since local result is already stored, this should not create new record
  EXPECT_EQ(tomography_manager->tomography_records.size(), 1);
  auto stored_record = tomography_manager->tomography_records.at(std::make_tuple(qnic_id, partner_addr));
  // // Check self output
  EXPECT_EQ(stored_record.at(tomography_round).self_output.basis, measurement_basis);
  EXPECT_EQ(stored_record.at(tomography_round).self_output.output_is_plus, is_plus);
  EXPECT_EQ(stored_record.at(tomography_round).self_output.my_god_clean, my_god_clean);
  // // Check partner output
  EXPECT_EQ(stored_record.at(tomography_round).partner_output.basis, measurement_basis);
  EXPECT_EQ(stored_record.at(tomography_round).partner_output.output_is_plus, is_plus);
  EXPECT_EQ(stored_record.at(tomography_round).partner_output.my_god_clean, my_god_clean);
}

TEST_F(TomographyManagerTest, initializeTomographyStats){
  // When the first tomography record is added, initialize a tomography stats record with this partner
  int qnic_id = 0;
  int partner_addr = 1;
  int tomography_round = 0;

  tomography_manager->addLocalResult(qnic_id, partner_addr, tomography_round, measurement_basis, is_plus, my_god_clean);
  EXPECT_EQ(tomography_manager->tomography_stats.size(), 1);
  auto stored_stats = tomography_manager->tomography_stats.at(std::make_tuple(qnic_id, partner_addr));
  // Check initial values
  EXPECT_EQ(stored_stats.tomography_time, 0);
  EXPECT_EQ(stored_stats.bell_pair_per_sec, 0);
  EXPECT_EQ(stored_stats.total_measurement_count, 0);
}
}  // namespace

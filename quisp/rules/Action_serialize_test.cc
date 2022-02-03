#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <memory>
#include "Action.h"

namespace {
using namespace quisp_test;
using namespace quisp::rules;
using quisp::modules::QNIC_type;

TEST(ActionTest, Purification_serialize_json) {
  prepareSimulation();
  // purification_type, partner_addr, qnic_type, qnic_id
  auto purification = std::make_unique<Purification>(PurType::DSDA, 3, QNIC_E, 123);
  json purification_json = purification->serialize_json();
  EXPECT_EQ(purification_json["type"], "purification");
  EXPECT_EQ(purification_json["options"]["purification_type"], 8);
  EXPECT_EQ(purification_json["options"]["partner_address"][0], 3);
  EXPECT_EQ(purification_json["options"]["qnic_type"][0], 0);
  EXPECT_EQ(purification_json["options"]["qnic_id"][0], 123);
}

TEST(ActionTest, EntanglementSwapping_serialize_json) {
  prepareSimulation();
  // num measure
  std::vector<int> partners = {1, 3};
  std::vector<QNIC_type> qnic_types = {QNIC_E, QNIC_RP};
  std::vector<int> qnic_ids = {13, 15};
  auto swapping = std::make_unique<EntanglementSwapping>(partners, qnic_types, qnic_ids);
  json swapping_json = swapping->serialize_json();
  EXPECT_EQ(swapping_json["type"], "swapping");
  EXPECT_EQ(swapping_json["options"]["partner_address"][0], 1);
  EXPECT_EQ(swapping_json["options"]["partner_address"][1], 3);
  EXPECT_EQ(swapping_json["options"]["qnic_type"][0], 0);
  EXPECT_EQ(swapping_json["options"]["qnic_type"][1], 2);
  EXPECT_EQ(swapping_json["options"]["qnic_id"][0], 13);
  EXPECT_EQ(swapping_json["options"]["qnic_id"][1], 15);
}

TEST(ActionTest, Wait_serialize_json) {
  prepareSimulation();
  // num measure
  auto wait = std::make_unique<Wait>(1, QNIC_R, 13);
  json wait_json = wait->serialize_json();
  EXPECT_EQ(wait_json["type"], "wait");
  EXPECT_EQ(wait_json["options"]["partner_address"][0], 1);
  EXPECT_EQ(wait_json["options"]["qnic_type"][0], 1);
  EXPECT_EQ(wait_json["options"]["qnic_id"][0], 13);
}

TEST(ActionTest, Tomography_serialize_json) {
  prepareSimulation();
  // num measure
  auto tomography = std::make_unique<Tomography>(1000, 3, QNIC_E, 15);
  json tomography_json = tomography->serialize_json();
  EXPECT_EQ(tomography_json["type"], "tomography");
  EXPECT_EQ(tomography_json["options"]["num_measure"], 1000);
  EXPECT_EQ(tomography_json["options"]["partner_address"][0], 3);
  EXPECT_EQ(tomography_json["options"]["qnic_type"][0], 0);
  EXPECT_EQ(tomography_json["options"]["qnic_id"][0], 15);
}

}  // namespace
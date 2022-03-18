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
  EXPECT_EQ(purification_json["options"]["purification_type"], "DSDA");
  EXPECT_EQ(purification_json["options"]["partner_address"][0], 3);
  EXPECT_EQ(purification_json["options"]["qnic_type"][0], "QNIC_E");
  EXPECT_EQ(purification_json["options"]["qnic_id"][0], 123);
}

TEST(ActionTest, Purification_deserialize_json) {
  prepareSimulation();
  auto serialized = json::parse(R"({
    "type": "purification",
    "options": {
      "purification_type": "DOUBLE_INV",
      "partner_address": [1],
      "qnic_type": ["QNIC_R"],
      "qnic_id": [30]
      }
    })");
  auto empty_purification = std::make_unique<Purification>(serialized);
  EXPECT_EQ(empty_purification->purification_type, PurType::DOUBLE_INV);
  EXPECT_EQ(empty_purification->partner_address.at(0), 1);
  EXPECT_EQ(empty_purification->qnic_types.at(0), QNIC_R);
  EXPECT_EQ(empty_purification->qnic_ids.at(0), 30);
}

TEST(ActionTest, EntanglementSwapping_serialize_json) {
  prepareSimulation();
  // num measure
  std::vector<int> partners = {1, 3};
  std::vector<QNIC_type> qnic_types = {QNIC_E, QNIC_RP};
  std::vector<int> qnic_ids = {13, 15};
  std::vector<QNIC_type> remote_qnic_types = {QNIC_R, QNIC_E};
  std::vector<int> remote_qnic_ids = {12, 16};
  std::vector<int> remote_qnic_address = {21, 22};
  auto swapping = std::make_unique<EntanglementSwapping>(partners, qnic_types, qnic_ids, remote_qnic_types, remote_qnic_ids, remote_qnic_address);
  json swapping_json = swapping->serialize_json();
  EXPECT_EQ(swapping_json["type"], "swapping");
  EXPECT_EQ(swapping_json["options"]["partner_address"][0], 1);
  EXPECT_EQ(swapping_json["options"]["partner_address"][1], 3);
  EXPECT_EQ(swapping_json["options"]["qnic_type"][0], "QNIC_E");
  EXPECT_EQ(swapping_json["options"]["qnic_type"][1], "QNIC_RP");
  EXPECT_EQ(swapping_json["options"]["qnic_id"][0], 13);
  EXPECT_EQ(swapping_json["options"]["qnic_id"][1], 15);
  EXPECT_EQ(swapping_json["options"]["remote_qnic_type"][0], "QNIC_R");
  EXPECT_EQ(swapping_json["options"]["remote_qnic_type"][1], "QNIC_E");
  EXPECT_EQ(swapping_json["options"]["remote_qnic_id"][0], 12);
  EXPECT_EQ(swapping_json["options"]["remote_qnic_id"][1], 16);
  EXPECT_EQ(swapping_json["options"]["remote_qnic_address"][0], 21);
  EXPECT_EQ(swapping_json["options"]["remote_qnic_address"][1], 22);
}

TEST(ActionTest, EntanglementSwapping_deserialize_json) {
  prepareSimulation();
  auto serialized = json::parse(R"({
    "type": "swapping",
    "options": {
      "partner_address": [1, 3],
      "qnic_type": ["QNIC_R", "QNIC_RP"],
      "qnic_id": [30, 32],
      "remote_qnic_type": ["QNIC_E", "QNIC_E"],
      "remote_qnic_id": [29, 33],
      "remote_qnic_address": [13, 14]
      }
    })");
  auto empty_swapping = std::make_unique<EntanglementSwapping>(serialized);
  EXPECT_EQ(empty_swapping->partner_address.at(0), 1);
  EXPECT_EQ(empty_swapping->partner_address.at(1), 3);
  EXPECT_EQ(empty_swapping->qnic_types.at(0), QNIC_R);
  EXPECT_EQ(empty_swapping->qnic_types.at(1), QNIC_RP);
  EXPECT_EQ(empty_swapping->qnic_ids.at(0), 30);
  EXPECT_EQ(empty_swapping->qnic_ids.at(1), 32);
  EXPECT_EQ(empty_swapping->remote_qnic_types.at(0), QNIC_E);
  EXPECT_EQ(empty_swapping->remote_qnic_types.at(1), QNIC_E);
  EXPECT_EQ(empty_swapping->remote_qnic_ids.at(0), 29);
  EXPECT_EQ(empty_swapping->remote_qnic_ids.at(1), 33);
  EXPECT_EQ(empty_swapping->remote_qnic_address.at(0), 13);
  EXPECT_EQ(empty_swapping->remote_qnic_address.at(1), 14);
}

TEST(ActionTest, Wait_serialize_json) {
  prepareSimulation();
  // num measure
  auto wait = std::make_unique<Wait>(1, QNIC_R, 13);
  json wait_json = wait->serialize_json();
  EXPECT_EQ(wait_json["type"], "wait");
  EXPECT_EQ(wait_json["options"]["partner_address"][0], 1);
  EXPECT_EQ(wait_json["options"]["qnic_type"][0], "QNIC_R");
  EXPECT_EQ(wait_json["options"]["qnic_id"][0], 13);
}

TEST(ActionTest, Wait_deserialize_json) {
  prepareSimulation();
  auto serialized = json::parse(R"({
    "type": "wait",
    "options": {
      "partner_address": [1],
      "qnic_type": ["QNIC_R"],
      "qnic_id": [30]
      }
    })");
  auto empty_wait = std::make_unique<Wait>(serialized);
  EXPECT_EQ(empty_wait->partner_address.at(0), 1);
  EXPECT_EQ(empty_wait->qnic_types.at(0), QNIC_R);
  EXPECT_EQ(empty_wait->qnic_ids.at(0), 30);
}

TEST(ActionTest, Tomography_serialize_json) {
  prepareSimulation();
  // num measure
  auto tomography = std::make_unique<Tomography>(1000, 2, 3, QNIC_E, 15);
  json tomography_json = tomography->serialize_json();
  EXPECT_EQ(tomography_json["type"], "tomography");
  EXPECT_EQ(tomography_json["options"]["num_measure"], 1000);
  EXPECT_EQ(tomography_json["options"]["owner_address"], 2);
  EXPECT_EQ(tomography_json["options"]["partner_address"][0], 3);
  EXPECT_EQ(tomography_json["options"]["qnic_type"][0], "QNIC_E");
  EXPECT_EQ(tomography_json["options"]["qnic_id"][0], 15);
}

TEST(ActionTest, Tomography_deserialize_json) {
  prepareSimulation();
  auto serialized = json::parse(R"({
    "type": "tomography",
    "options": {
      "num_measure": 1000,
      "owner_address": 2,
      "partner_address": [1],
      "qnic_type": ["QNIC_R"],
      "qnic_id": [30]
      }
    })");
  auto empty_tomography = std::make_unique<Tomography>(serialized);
  EXPECT_EQ(empty_tomography->num_measurement, 1000);
  EXPECT_EQ(empty_tomography->owner_address, 2);
  EXPECT_EQ(empty_tomography->partner_address.at(0), 1);
  EXPECT_EQ(empty_tomography->qnic_types.at(0), QNIC_R);
  EXPECT_EQ(empty_tomography->qnic_ids.at(0), 30);
}
}  // namespace

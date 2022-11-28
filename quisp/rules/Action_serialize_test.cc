#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <memory>
#include "Action.h"

namespace {
using namespace quisp_test;
using namespace quisp::rules;
using quisp::modules::QNIC_E;
using quisp::modules::QNIC_N;
using quisp::modules::QNIC_R;
using quisp::modules::QNIC_RP;
using quisp::modules::QNIC_type;

TEST(ActionTest, Purification_serialize_json) {
  prepareSimulation();
  // purification_type, partner_addr, qnic_type, qnic_id
  auto purification = std::make_unique<Purification>(PurType::DSDA, 3, QNIC_E, 123);
  json purification_json = purification->serialize_json();
  EXPECT_EQ(purification_json["type"], "purification");
  EXPECT_EQ(purification_json["options"]["purification_type"], "DSDA");
  EXPECT_EQ(purification_json["options"]["interface"][0]["partner_address"], 3);
  EXPECT_EQ(purification_json["options"]["interface"][0]["qnic_type"], "QNIC_E");
  EXPECT_EQ(purification_json["options"]["interface"][0]["qnic_id"], 123);
}

TEST(ActionTest, Purification_deserialize_json) {
  prepareSimulation();
  auto serialized = json::parse(R"({
    "type": "purification",
    "options": {
      "purification_type": "DOUBLE_INV",
      "interface": [
        {"partner_address": 1, "qnic_type": "QNIC_R", "qnic_id": 30}
        ]
      }
    })");
  auto empty_purification = std::make_unique<Purification>(serialized);
  auto qnic_interface = empty_purification->qnic_interfaces.at(0);
  EXPECT_EQ(empty_purification->purification_type, PurType::DOUBLE_INV);
  EXPECT_EQ(qnic_interface.partner_addr, 1);
  EXPECT_EQ(qnic_interface.qnic_type, QNIC_R);
  EXPECT_EQ(qnic_interface.qnic_id, 30);
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
  EXPECT_EQ(swapping_json["options"]["interface"][0]["partner_address"], 1);
  EXPECT_EQ(swapping_json["options"]["interface"][0]["qnic_type"], "QNIC_E");
  EXPECT_EQ(swapping_json["options"]["interface"][0]["qnic_id"], 13);
  EXPECT_EQ(swapping_json["options"]["interface"][1]["partner_address"], 3);
  EXPECT_EQ(swapping_json["options"]["interface"][1]["qnic_type"], "QNIC_RP");
  EXPECT_EQ(swapping_json["options"]["interface"][1]["qnic_id"], 15);
  EXPECT_EQ(swapping_json["options"]["remote_interface"][0]["qnic_type"], "QNIC_R");
  EXPECT_EQ(swapping_json["options"]["remote_interface"][0]["qnic_id"], 12);
  EXPECT_EQ(swapping_json["options"]["remote_interface"][0]["qnic_address"], 21);
  EXPECT_EQ(swapping_json["options"]["remote_interface"][1]["qnic_type"], "QNIC_E");
  EXPECT_EQ(swapping_json["options"]["remote_interface"][1]["qnic_id"], 16);
  EXPECT_EQ(swapping_json["options"]["remote_interface"][1]["qnic_address"], 22);
}

TEST(ActionTest, EntanglementSwapping_deserialize_json) {
  prepareSimulation();
  auto serialized = json::parse(R"({
    "type": "swapping",
    "options": {
      "interface": [
        {"partner_address":1,  "qnic_type":"QNIC_R", "qnic_id":30},
        {"partner_address":3,  "qnic_type":"QNIC_RP", "qnic_id":32}
      ],
      "remote_interface":[
        {"partner_address": 1, "qnic_type": "QNIC_E", "qnic_id": 29, "qnic_address": 13},
        {"partner_address": 3, "qnic_type": "QNIC_E", "qnic_id": 33, "qnic_address": 14}
      ]
      }
    })");
  auto empty_swapping = std::make_unique<EntanglementSwapping>(serialized);
  auto qnic_interface_left = empty_swapping->qnic_interfaces.at(0);
  EXPECT_EQ(qnic_interface_left.partner_addr, 1);
  EXPECT_EQ(qnic_interface_left.qnic_type, QNIC_R);
  EXPECT_EQ(qnic_interface_left.qnic_id, 30);
  auto qnic_interface_right = empty_swapping->qnic_interfaces.at(1);
  EXPECT_EQ(qnic_interface_right.partner_addr, 3);
  EXPECT_EQ(qnic_interface_right.qnic_type, QNIC_RP);
  EXPECT_EQ(qnic_interface_right.qnic_id, 32);
  auto left_partner_qnic_interface = empty_swapping->remote_qnic_interfaces.at(0);
  EXPECT_EQ(left_partner_qnic_interface.qnic_type, QNIC_E);
  EXPECT_EQ(left_partner_qnic_interface.qnic_id, 29);
  EXPECT_EQ(left_partner_qnic_interface.qnic_address, 13);
  auto right_partner_qnic_interface = empty_swapping->remote_qnic_interfaces.at(1);
  EXPECT_EQ(right_partner_qnic_interface.qnic_type, QNIC_E);
  EXPECT_EQ(right_partner_qnic_interface.qnic_id, 33);
  EXPECT_EQ(right_partner_qnic_interface.qnic_address, 14);
}

TEST(ActionTest, Wait_serialize_json) {
  prepareSimulation();
  // num measure
  auto wait = std::make_unique<Wait>(1, QNIC_R, 13);
  json wait_json = wait->serialize_json();
  EXPECT_EQ(wait_json["type"], "wait");
  EXPECT_EQ(wait_json["options"]["interface"][0]["partner_address"], 1);
  EXPECT_EQ(wait_json["options"]["interface"][0]["qnic_type"], "QNIC_R");
  EXPECT_EQ(wait_json["options"]["interface"][0]["qnic_id"], 13);
}

TEST(ActionTest, Wait_deserialize_json) {
  prepareSimulation();
  auto serialized = json::parse(R"({
    "type": "wait",
    "options": {
      "interface":[
        {"partner_address": 1, "qnic_type": "QNIC_R", "qnic_id": 30}
      ]
      }
    })");
  auto empty_wait = std::make_unique<Wait>(serialized);
  auto qnic_interface = empty_wait->qnic_interfaces.at(0);
  EXPECT_EQ(qnic_interface.partner_addr, 1);
  EXPECT_EQ(qnic_interface.qnic_type, QNIC_R);
  EXPECT_EQ(qnic_interface.qnic_id, 30);
}

TEST(ActionTest, Tomography_serialize_json) {
  prepareSimulation();
  // num measure
  auto tomography = std::make_unique<Tomography>(1000, 2, 3, QNIC_E, 15);
  json tomography_json = tomography->serialize_json();
  EXPECT_EQ(tomography_json["type"], "tomography");
  EXPECT_EQ(tomography_json["options"]["num_measure"], 1000);
  EXPECT_EQ(tomography_json["options"]["owner_address"], 2);
  EXPECT_EQ(tomography_json["options"]["interface"][0]["partner_address"], 3);
  EXPECT_EQ(tomography_json["options"]["interface"][0]["qnic_type"], "QNIC_E");
  EXPECT_EQ(tomography_json["options"]["interface"][0]["qnic_id"], 15);
}

TEST(ActionTest, Tomography_deserialize_json) {
  prepareSimulation();
  auto serialized = json::parse(R"({
    "type": "tomography",
    "options": {
      "num_measure": 1000,
      "owner_address": 2,
      "interface": [
        {"partner_address": 1, "qnic_type": "QNIC_R","qnic_id": 30}
      ]
      }
    })");
  auto empty_tomography = std::make_unique<Tomography>(serialized);
  auto qnic_interface = empty_tomography->qnic_interfaces.at(0);
  EXPECT_EQ(empty_tomography->num_measurement, 1000);
  EXPECT_EQ(empty_tomography->owner_address, 2);
  EXPECT_EQ(qnic_interface.partner_addr, 1);
  EXPECT_EQ(qnic_interface.qnic_type, QNIC_R);
  EXPECT_EQ(qnic_interface.qnic_id, 30);
}
}  // namespace

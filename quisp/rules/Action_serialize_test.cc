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
  auto purification = std::make_unique<Purification>(PurType::DOUBLE_SELECTION_XZ_PURIFICATION, 3, 11);
  json purification_json = purification->serialize_json();
  EXPECT_EQ(purification_json["type"], "purification");
  EXPECT_EQ(purification_json["options"]["purification_type"], "DOUBLE_SELECTION_XZ_PURIFICATION");
  EXPECT_EQ(purification_json["options"]["interface"][0]["partner_address"], 3);
  EXPECT_EQ(purification_json["options"]["shared_rule_tag"], 11);
}

TEST(ActionTest, Purification_deserialize_json) {
  prepareSimulation();
  auto serialized = json::parse(R"({
    "type": "purification",
    "options": {
      "purification_type": "SINGLE_SELECTION_ZX_PURIFICATION",
      "interface": [
        {"partner_address": 1}
        ],
      "shared_rule_tag": 11
      }
    })");
  auto empty_purification = std::make_unique<Purification>(serialized);
  auto qnic_interface = empty_purification->qnic_interfaces.at(0);
  EXPECT_EQ(empty_purification->purification_type, PurType::SINGLE_SELECTION_ZX_PURIFICATION);
  EXPECT_EQ(empty_purification->shared_rule_tag, 11);
  EXPECT_EQ(qnic_interface.partner_addr, 1);
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
  auto swapping = std::make_unique<EntanglementSwapping>(partners, 12);
  json swapping_json = swapping->serialize_json();
  EXPECT_EQ(swapping_json["type"], "swapping");
  EXPECT_EQ(swapping_json["options"]["interface"][0]["partner_address"], 1);
  EXPECT_EQ(swapping_json["options"]["interface"][1]["partner_address"], 3);
  EXPECT_EQ(swapping_json["options"]["shared_rule_tag"], 12);
}

TEST(ActionTest, EntanglementSwapping_deserialize_json) {
  prepareSimulation();
  auto serialized = json::parse(R"({
    "type": "swapping",
    "options": {
      "interface": [
        {"partner_address":1},
        {"partner_address":3}
      ],
      "remote_interface":[
        {"partner_address": 1},
        {"partner_address": 3}
      ],
      "shared_rule_tag": 12
      }
    })");
  auto empty_swapping = std::make_unique<EntanglementSwapping>(serialized);
  auto qnic_interface_left = empty_swapping->qnic_interfaces.at(0);
  EXPECT_EQ(qnic_interface_left.partner_addr, 1);
  auto qnic_interface_right = empty_swapping->qnic_interfaces.at(1);
  EXPECT_EQ(qnic_interface_right.partner_addr, 3);
  auto shared_rule_tag = empty_swapping->shared_rule_tag;
  EXPECT_EQ(shared_rule_tag, 12);
}

TEST(ActionTest, Purification_Correlation_Action_Serialization) {}
TEST(ActionTest, Purification_Correlation_Action_Deserialization) {}
TEST(ActionTest, Swapping_Correction_Action_Serialization) {}
TEST(ActionTest, Swapping_Correction_Action_Deserialization) {}

TEST(ActionTest, Tomography_serialize_json) {
  prepareSimulation();
  // num measure
  auto tomography = std::make_unique<Tomography>(1000, 2, 3);
  json tomography_json = tomography->serialize_json();
  EXPECT_EQ(tomography_json["type"], "tomography");
  EXPECT_EQ(tomography_json["options"]["num_measure"], 1000);
  EXPECT_EQ(tomography_json["options"]["owner_address"], 2);
}

TEST(ActionTest, Tomography_deserialize_json) {
  prepareSimulation();
  auto serialized = json::parse(R"({
    "type": "tomography",
    "options": {
      "num_measure": 1000,
      "owner_address": 2,
      "interface": [
        {"partner_address": 1}
      ]
      }
    })");
  auto empty_tomography = std::make_unique<Tomography>(serialized);
  auto qnic_interface = empty_tomography->qnic_interfaces.at(0);
  EXPECT_EQ(empty_tomography->num_measurement, 1000);
  EXPECT_EQ(empty_tomography->owner_address, 2);
  EXPECT_EQ(qnic_interface.partner_addr, 1);
}
}  // namespace

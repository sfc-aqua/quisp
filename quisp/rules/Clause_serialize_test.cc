#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <test_utils/TestUtils.h>
#include <memory>
#include "Clause.h"

namespace {
using namespace quisp_test;
using namespace quisp::rules;
using quisp::modules::QNIC_type;

TEST(ClauseTest, EnoughResourceConditionClause_serialize_json) {
  prepareSimulation();
  // num_resource, required_fidelity, partner_addr, qnic_type, qnic_id
  auto enough_resource = std::make_unique<EnoughResourceConditionClause>(3, 0.85, 1, QNIC_R, 13);
  json enough_resource_json = enough_resource->serialize_json();
  EXPECT_EQ(enough_resource_json["type"], "enough_resource");
  EXPECT_EQ(enough_resource_json["options"]["num_resource"], 3);
  EXPECT_EQ(enough_resource_json["options"]["required_fidelity"], 0.85);
  EXPECT_EQ(enough_resource_json["options"]["interface"]["partner_address"], 1);
  EXPECT_EQ(enough_resource_json["options"]["interface"]["qnic_type"], "QNIC_R");
  EXPECT_EQ(enough_resource_json["options"]["interface"]["qnic_id"], 13);
}

TEST(ClauseTest, EnoughResourceConditionClause_deserialize_json) {
  prepareSimulation();
  auto serialized = json::parse(R"({
    "type": "enough_resource",
    "options": {
      "num_resource": 3,
      "required_fidelity": 0.95,
      "interface":{
        "partner_address": 1,
        "qnic_type": "QNIC_R",
        "qnic_id": 30
      }
      }
    })");
  auto enough_resource = std::make_unique<EnoughResourceConditionClause>(serialized);
  EXPECT_EQ(enough_resource->name, "enough_resource");
  EXPECT_EQ(enough_resource->num_resource, 3);
  EXPECT_EQ(enough_resource->required_fidelity, 0.95);
  EXPECT_EQ(enough_resource->partner_address, 1);
  EXPECT_EQ(enough_resource->qnic_type, QNIC_R);
  EXPECT_EQ(enough_resource->qnic_id, 30);
}

TEST(ClauseTest, MeasureCountConditionClause_serialize_json) {
  prepareSimulation();
  // num measure
  auto measure_count = std::make_unique<MeasureCountConditionClause>(1000, 1, QNIC_E, 15);
  json measure_count_json = measure_count->serialize_json();
  EXPECT_EQ(measure_count_json["type"], "measure_count");
  EXPECT_EQ(measure_count_json["options"]["num_measure"], 1000);
  EXPECT_EQ(measure_count_json["options"]["interface"]["partner_address"], 1);
  EXPECT_EQ(measure_count_json["options"]["interface"]["qnic_type"], "QNIC_E");
  EXPECT_EQ(measure_count_json["options"]["interface"]["qnic_id"], 15);
}

TEST(ClauseTest, MeasureCountConditionClause_deserialize_json) {
  prepareSimulation();
  auto serialized = json::parse(R"({
    "type": "measure_count",
    "options": {
      "num_measure": 500,
      "interface": {
        "partner_address": 1,
        "qnic_type": "QNIC_R",
        "qnic_id": 30
      }
      }
    })");
  auto empty_measure_count = std::make_unique<MeasureCountConditionClause>(serialized);
  EXPECT_EQ(empty_measure_count->name, "measure_count");
  EXPECT_EQ(empty_measure_count->num_measure, 500);
  EXPECT_EQ(empty_measure_count->partner_address, 1);
  EXPECT_EQ(empty_measure_count->qnic_type, QNIC_R);
  EXPECT_EQ(empty_measure_count->qnic_id, 30);
}

TEST(ClauseTest, FidelityConditionClause_serialize_json) {
  prepareSimulation();
  // num measure
  auto fidelity = std::make_unique<FidelityConditionClause>(0.8, 3, QNIC_RP, 103);
  json fidelity_json = fidelity->serialize_json();
  EXPECT_EQ(fidelity_json["type"], "fidelity");
  EXPECT_EQ(fidelity_json["options"]["required_fidelity"], 0.8);
  EXPECT_EQ(fidelity_json["options"]["interface"]["partner_address"], 3);
  EXPECT_EQ(fidelity_json["options"]["interface"]["qnic_type"], "QNIC_RP");
  EXPECT_EQ(fidelity_json["options"]["interface"]["qnic_id"], 103);
}

TEST(ClauseTest, FidelityConditionClause_deserialize_json) {
  prepareSimulation();
  auto serialized = json::parse(R"({
    "type": "fidelity",
    "options": {
      "required_fidelity": 0.9,
      "interface": {
        "partner_address": 1,
        "qnic_type": "QNIC_R",
        "qnic_id": 30
      }
      }
    })");
  auto empty_fidelity = std::make_unique<FidelityConditionClause>(serialized);
  EXPECT_EQ(empty_fidelity->name, "fidelity");
  EXPECT_EQ(empty_fidelity->required_fidelity, 0.9);
  EXPECT_EQ(empty_fidelity->partner_address, 1);
  EXPECT_EQ(empty_fidelity->qnic_type, QNIC_R);
  EXPECT_EQ(empty_fidelity->qnic_id, 30);
}

}  // namespace

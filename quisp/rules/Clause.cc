#include "Clause.h"

namespace quisp::rules {

EnoughResourceConditionClause::EnoughResourceConditionClause(int num_resource, int partner_addr) : Clause(partner_addr), num_resource(num_resource) {}

json EnoughResourceConditionClause::serialize_json() {
  json enough_resource_json;
  enough_resource_json["type"] = "enough_resource";
  enough_resource_json["options"]["num_resource"] = num_resource;
  enough_resource_json["options"]["interface"]["partner_address"] = partner_address;
  return enough_resource_json;
}

void EnoughResourceConditionClause::deserialize_json(json serialized) {
  auto options = serialized["options"];
  if (options != nullptr) {
    // get options one by one
    options["num_resource"].get_to(num_resource);
    options["interface"]["partner_address"].get_to(partner_address);
  }
}

MeasureCountConditionClause::MeasureCountConditionClause(int num_measurement, int partner_addr) : Clause(partner_addr), num_measure(num_measurement) {}

json MeasureCountConditionClause::serialize_json() {
  json measure_count_json;
  measure_count_json["type"] = "measure_count";
  measure_count_json["options"]["num_measure"] = num_measure;
  measure_count_json["options"]["interface"]["partner_address"] = partner_address;
  return measure_count_json;
}

void MeasureCountConditionClause::deserialize_json(json serialized) {
  auto options = serialized["options"];
  if (options != nullptr) {
    // get options one by one
    options["num_measure"].get_to(num_measure);
    options["interface"]["partner_address"].get_to(partner_address);
  }
}

FidelityConditionClause::FidelityConditionClause(double required_fidelity, int partner_addr) : Clause(partner_addr), required_fidelity(required_fidelity) {}

json FidelityConditionClause::serialize_json() {
  json fidelity_json;
  fidelity_json["type"] = "fidelity";
  fidelity_json["options"]["required_fidelity"] = required_fidelity;
  fidelity_json["options"]["interface"]["partner_address"] = partner_address;
  return fidelity_json;
}

void FidelityConditionClause::deserialize_json(json serialized) {
  auto options = serialized["options"];
  if (options != nullptr) {
    // get options one by one
    options["required_fidelity"].get_to(required_fidelity);
    options["interface"]["partner_address"].get_to(partner_address);
  }
}

PurificationCorrelationClause::PurificationCorrelationClause(int partner_address, int shared_rule_tag) : Clause(partner_address), shared_rule_tag(shared_rule_tag) {}

json PurificationCorrelationClause::serialize_json() {
  json wait_json;
  wait_json["type"] = "purification_correlation";
  wait_json["options"]["interface"]["partner_address"] = partner_address;
  wait_json["options"]["shared_rule_tag"] = shared_rule_tag;
  return wait_json;
}

void PurificationCorrelationClause::deserialize_json(json serialized) {
  auto options = serialized["options"];
  if (options != nullptr) {
    options["interface"]["partner_address"].get_to(partner_address);
    options["shared_rule_tag"].get_to(shared_rule_tag);
  }
}

SwappingCorrectionClause::SwappingCorrectionClause(int swapper_address, int shared_rule_tag) : Clause(swapper_address), shared_rule_tag(shared_rule_tag) {}

json SwappingCorrectionClause::serialize_json() {
  json wait_json;
  wait_json["type"] = "swapping_correction";
  wait_json["options"]["interface"]["partner_address"] = partner_address;
  wait_json["options"]["shared_rule_tag"] = shared_rule_tag;
  return wait_json;
}

void SwappingCorrectionClause::deserialize_json(json serialized) {
  auto options = serialized["options"];
  if (options != nullptr) {
    options["interface"]["partner_address"].get_to(partner_address);
    options["shared_rule_tag"].get_to(shared_rule_tag);
  }
}

}  // namespace quisp::rules

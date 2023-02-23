#include "Clause.h"

namespace quisp::rules {
using types::QNodeAddr;

EnoughResourceConditionClause::EnoughResourceConditionClause(int num_resource, QNodeAddr partner_addr) : Clause(partner_addr), num_resource(num_resource) {}

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

MeasureCountConditionClause::MeasureCountConditionClause(int num_measurement, QNodeAddr partner_addr) : Clause(partner_addr), num_measure(num_measurement) {}

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

FidelityConditionClause::FidelityConditionClause(double required_fidelity, QNodeAddr partner_addr) : Clause(partner_addr), required_fidelity(required_fidelity) {}

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

WaitConditionClause::WaitConditionClause(QNodeAddr swapper_addr) : Clause(swapper_addr) {}

json WaitConditionClause::serialize_json() {
  json wait_json;
  wait_json["type"] = "wait";
  wait_json["options"]["interface"]["partner_address"] = partner_address;
  return wait_json;
}

void WaitConditionClause::deserialize_json(json serialized) {
  auto options = serialized["options"];
  if (options != nullptr) {
    options["interface"]["partner_address"].get_to(partner_address);
  }
}
}  // namespace quisp::rules

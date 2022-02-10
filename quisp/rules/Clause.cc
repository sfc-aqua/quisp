#include "Clause.h"

namespace quisp::rules {

EnoughResourceConditionClause::EnoughResourceConditionClause(int num_resource, double required_fidelity, int partner_addr, QNIC_type qnic_type, int qnic_id)
    : Clause(partner_addr, qnic_type, qnic_id), num_resource(num_resource), required_fidelity(required_fidelity) {}

json EnoughResourceConditionClause::serialize_json() {
  json enough_resource_json;
  enough_resource_json["type"] = "enough_resource";
  enough_resource_json["options"]["num_resource"] = num_resource;
  enough_resource_json["options"]["required_fidelity"] = required_fidelity;
  enough_resource_json["options"]["partner_address"] = partner_address;
  enough_resource_json["options"]["qnic_type"] = qnic_type;
  enough_resource_json["options"]["qnic_id"] = qnic_id;
  return enough_resource_json;
}

void EnoughResourceConditionClause::deserialize_json(json serialized) {
  auto options = serialized["options"];
  if (options != nullptr) {
    // get options one by one
    options["num_resource"].get_to(num_resource);
    options["required_fidelity"].get_to(required_fidelity);
    options["partner_address"].get_to(partner_address);
    options["qnic_type"].get_to(qnic_type);
    options["qnic_id"].get_to(qnic_id);
  }
}

MeasureCountConditionClause::MeasureCountConditionClause(int num_measurement, int partner_addr, QNIC_type qnic_type, int qnic_id)
    : num_measure(num_measurement), Clause(partner_addr, qnic_type, qnic_id) {}

json MeasureCountConditionClause::serialize_json() {
  json measure_count_json;
  measure_count_json["type"] = "measure_count";
  measure_count_json["options"]["num_measure"] = num_measure;
  measure_count_json["options"]["partner_address"] = partner_address;
  measure_count_json["options"]["qnic_type"] = qnic_type;
  measure_count_json["options"]["qnic_id"] = qnic_id;
  return measure_count_json;
}

void MeasureCountConditionClause::deserialize_json(json serialized) {
  auto options = serialized["options"];
  if (options != nullptr) {
    // get options one by one
    options["num_measure"].get_to(num_measure);
    options["partner_address"].get_to(partner_address);
    options["qnic_type"].get_to(qnic_type);
    options["qnic_id"].get_to(qnic_id);
  }
}

FidelityConditionClause::FidelityConditionClause(double required_fidelity, int partner_addr, QNIC_type qnic_type, int qnic_id)
    : required_fidelity(required_fidelity), Clause(partner_addr, qnic_type, qnic_id) {}

json FidelityConditionClause::serialize_json() {
  json fidelity_json;
  fidelity_json["type"] = "fidelity";
  fidelity_json["options"]["required_fidelity"] = required_fidelity;
  fidelity_json["options"]["partner_address"] = partner_address;
  fidelity_json["options"]["qnic_type"] = qnic_type;
  fidelity_json["options"]["qnic_id"] = qnic_id;
  return fidelity_json;
}

void FidelityConditionClause::deserialize_json(json serialized) {
  auto options = serialized["options"];
  if (options != nullptr) {
    // get options one by one
    options["required_fidelity"].get_to(required_fidelity);
    options["partner_address"].get_to(partner_address);
    options["qnic_type"].get_to(qnic_type);
    options["qnic_id"].get_to(qnic_id);
  }
}

WaitConditionClause::WaitConditionClause(int partner_addr, QNIC_type qnic_type, int qnic_id) : Clause(partner_addr, qnic_type, qnic_id) {}

json WaitConditionClause::serialize_json() {
  json wait_json;
  wait_json["type"] = "wait";
  wait_json["options"]["partner_address"] = partner_address;
  wait_json["options"]["qnic_type"] = qnic_type;
  wait_json["options"]["qnic_id"] = qnic_id;
  return wait_json;
}

void WaitConditionClause::deserialize_json(json serialized) {
  auto options = serialized["options"];
  if (options != nullptr) {
    options["partner_address"].get_to(partner_address);
    options["qnic_type"].get_to(qnic_type);
    options["qnic_id"].get_to(qnic_id);
  }
}
}  // namespace quisp::rules
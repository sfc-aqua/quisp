#include "Clause.h"

namespace quisp::rules {

EnoughResourceConditionClause::EnoughResourceConditionClause(int num_resource, double required_fidelity, int partner_addr, QNIC_type qnic_type, int qnic_id)
    : Clause(partner_addr, qnic_type, qnic_id), num_resource(num_resource), required_fidelity(required_fidelity) {}

json EnoughResourceConditionClause::serialize() {
  json enough_resource_json;
  enough_resource_json["num_resources"] = num_resource;
  enough_resource_json["required_fidelity"] = required_fidelity;
  enough_resource_json["partner_address"] = partner_address;
  enough_resource_json["qnic_type"] = qnic_type;
  enough_resource_json["qnic_id"] = qnic_id;
  return enough_resource_json;
}

MeasureCountConditionClause::MeasureCountConditionClause(int num_measurement, int partner_addr, QNIC_type qnic_type, int qnic_id)
    : num_measure(num_measurement), Clause(partner_addr, qnic_type, qnic_id) {}

json MeasureCountConditionClause::serialize() {
  json measure_count_json;
  measure_count_json["num_measure"] = num_measure;
  measure_count_json["partner_address"] = partner_address;
  measure_count_json["qnic_type"] = qnic_type;
  measure_count_json["qnic_id"] = qnic_id;
  return measure_count_json;
}

FidelityConditionClause::FidelityConditionClause(double required_fidelity, int partner_addr, QNIC_type qnic_type, int qnic_id)
    : required_fidelity(required_fidelity), Clause(partner_addr, qnic_type, qnic_id) {}

json FidelityConditionClause::serialize() {
  json fidelity_json;
  fidelity_json["required_fidelity"] = required_fidelity;
  fidelity_json["partner_address"] = partner_address;
  fidelity_json["qnic_type"] = qnic_type;
  fidelity_json["qnic_id"] = qnic_id;
  return fidelity_json;
}

WaitConditionClause::WaitConditionClause(int partner_addr, QNIC_type qnic_type, int qnic_id) : Clause(partner_addr, qnic_type, qnic_id) {}

json WaitConditionClause::serialize() {
  json wait_json;
  return wait_json;
}

}  // namespace quisp::rules
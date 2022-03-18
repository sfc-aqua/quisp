#include "Action.h"

namespace quisp::rules {

Action::Action(int partner_addr, QNIC_type qnic_type, int qnic_id) {
  partner_address.push_back(partner_addr);
  qnic_types.push_back(qnic_type);
  qnic_ids.push_back(qnic_id);
};

Purification::Purification(PurType purification_type, int partner_addr, QNIC_type qnic_type, int qnic_id)
    : Action(partner_addr, qnic_type, qnic_id), purification_type(purification_type) {}

json Purification::serialize_json() {
  json purification_json;
  purification_json["type"] = "purification";
  purification_json["options"]["purification_type"] = purification_type;
  purification_json["options"]["partner_address"] = partner_address;
  purification_json["options"]["qnic_type"] = qnic_types;
  purification_json["options"]["qnic_id"] = qnic_ids;
  return purification_json;
}

void Purification::deserialize_json(json serialized) {
  auto options = serialized["options"];
  if (options != nullptr) {
    // get options one by one
    options["purification_type"].get_to(purification_type);
    options["partner_address"].get_to(partner_address);
    options["qnic_type"].get_to(qnic_types);
    options["qnic_id"].get_to(qnic_ids);
  }
}

EntanglementSwapping::EntanglementSwapping(std::vector<int> partner_addr, std::vector<QNIC_type> qnic_type, std::vector<int> qnic_id, std::vector<QNIC_type> remote_qnic_type,
                                           std::vector<int> remote_qnic_id, std::vector<int> remote_qnic_address)
    : Action(partner_addr, qnic_type, qnic_id), remote_qnic_types(remote_qnic_type), remote_qnic_ids(remote_qnic_id), remote_qnic_address(remote_qnic_address) {}

json EntanglementSwapping::serialize_json() {
  json swapping_json;
  swapping_json["type"] = "swapping";
  swapping_json["options"]["partner_address"] = partner_address;  // should be two
  swapping_json["options"]["qnic_type"] = qnic_types;
  swapping_json["options"]["qnic_id"] = qnic_ids;
  swapping_json["options"]["remote_qnic_type"] = remote_qnic_types;
  swapping_json["options"]["remote_qnic_id"] = remote_qnic_ids;
  swapping_json["options"]["remote_qnic_address"] = remote_qnic_address;
  return swapping_json;
}

void EntanglementSwapping::deserialize_json(json serialized) {
  auto options = serialized["options"];
  if (options != nullptr) {
    // get options one by one
    options["partner_address"].get_to(partner_address);
    options["qnic_type"].get_to(qnic_types);
    options["qnic_id"].get_to(qnic_ids);
    options["remote_qnic_type"].get_to(remote_qnic_types);
    options["remote_qnic_id"].get_to(remote_qnic_ids);
    options["remote_qnic_address"].get_to(remote_qnic_address);
  }
}

Wait::Wait(int partner_addr, QNIC_type qnic_type, int qnic_id) : Action(partner_addr, qnic_type, qnic_id) {}

json Wait::serialize_json() {
  json wait_json;
  wait_json["type"] = "wait";
  wait_json["options"]["partner_address"] = partner_address;  // should be two
  wait_json["options"]["qnic_type"] = qnic_types;
  wait_json["options"]["qnic_id"] = qnic_ids;
  return wait_json;
}

void Wait::deserialize_json(json serialized) {
  auto options = serialized["options"];
  if (options != nullptr) {
    // get options one by one
    options["partner_address"].get_to(partner_address);
    options["qnic_type"].get_to(qnic_types);
    options["qnic_id"].get_to(qnic_ids);
  }
}

Tomography::Tomography(int num_measurement, int owner_addr, int partner_addr, QNIC_type qnic_type, int qnic_id) : Action(partner_addr, qnic_type, qnic_id), owner_address(owner_addr), num_measurement(num_measurement) {}

json Tomography::serialize_json() {
  json tomography_json;
  tomography_json["type"] = "tomography";
  tomography_json["options"]["num_measure"] = num_measurement;
  tomography_json["options"]["owner_address"] = owner_address;
  tomography_json["options"]["partner_address"] = partner_address;
  tomography_json["options"]["qnic_type"] = qnic_types;
  tomography_json["options"]["qnic_id"] = qnic_ids;
  return tomography_json;
}

void Tomography::deserialize_json(json serialized) {
  auto options = serialized["options"];
  if (options != nullptr) {
    // get options one by one
    options["num_measure"].get_to(num_measurement);
    options["owner_address"].get_to(owner_address);
    options["partner_address"].get_to(partner_address);
    options["qnic_type"].get_to(qnic_types);
    options["qnic_id"].get_to(qnic_ids);
  }
}
}  // namespace quisp::rules

#include "Action.h"

namespace quisp::rules {

Action::Action(int partner_addr, QNIC_type qnic_type, int qnic_id) {
  QnicInterface qnic_interface{partner_addr, qnic_type, qnic_id};
  qnic_interfaces.push_back(qnic_interface);
};

Action::Action(std::vector<int> partner_addr, std::vector<QNIC_type> qnic_type, std::vector<int> qnic_id) {
  for (int i = 0; i < partner_addr.size(); i++) {
    QnicInterface qnic_interface{partner_addr.at(i), qnic_type.at(i), qnic_id.at(i)};
    qnic_interfaces.push_back(qnic_interface);
  }
}

Purification::Purification(PurType purification_type, int partner_addr, QNIC_type qnic_type, int qnic_id)
    : Action(partner_addr, qnic_type, qnic_id), purification_type(purification_type) {}

json Purification::serialize_json() {
  json purification_json;
  purification_json["type"] = "purification";
  purification_json["options"]["purification_type"] = purification_type;
  purification_json["options"]["interface"] = qnic_interfaces;
  return purification_json;
}

void Purification::deserialize_json(json serialized) {
  auto options = serialized["options"];
  if (options != nullptr) {
    // get options one by one
    options["purification_type"].get_to(purification_type);
    options["interface"].get_to(qnic_interfaces);
  }
}

EntanglementSwapping::EntanglementSwapping(std::vector<int> partner_addr, std::vector<QNIC_type> qnic_type, std::vector<int> qnic_id, std::vector<QNIC_type> remote_qnic_type,
                                           std::vector<int> remote_qnic_id, std::vector<int> remote_qnic_address)
    : Action(partner_addr, qnic_type, qnic_id) {
  for (int i = 0; i < partner_addr.size(); i++) {
    QnicInterface remote_qnic_interface{partner_addr.at(i), remote_qnic_type.at(i), remote_qnic_id.at(i), remote_qnic_address.at(i)};
    remote_qnic_interfaces.push_back(remote_qnic_interface);
  }
}

json EntanglementSwapping::serialize_json() {
  json swapping_json;
  swapping_json["type"] = "swapping";
  swapping_json["options"]["interface"] = qnic_interfaces;
  swapping_json["options"]["remote_interface"] = remote_qnic_interfaces;
  return swapping_json;
}

void EntanglementSwapping::deserialize_json(json serialized) {
  auto options = serialized["options"];
  if (options != nullptr) {
    // get options one by one
    options["interface"].get_to(qnic_interfaces);
    options["remote_interface"].get_to(remote_qnic_interfaces);
  }
}

Wait::Wait(int partner_addr, QNIC_type qnic_type, int qnic_id) : Action(partner_addr, qnic_type, qnic_id) {}

json Wait::serialize_json() {
  json wait_json;
  wait_json["type"] = "wait";
  wait_json["options"]["interface"] = qnic_interfaces;
  return wait_json;
}

void Wait::deserialize_json(json serialized) {
  auto options = serialized["options"];
  if (options != nullptr) {
    // get options one by one
    options["interface"].get_to(qnic_interfaces);
  }
}

Tomography::Tomography(int num_measurement, int owner_addr, int partner_addr, QNIC_type qnic_type, int qnic_id)
    : Action(partner_addr, qnic_type, qnic_id), owner_address(owner_addr), num_measurement(num_measurement) {}

json Tomography::serialize_json() {
  json tomography_json;
  tomography_json["type"] = "tomography";
  tomography_json["options"]["num_measure"] = num_measurement;
  tomography_json["options"]["owner_address"] = owner_address;
  tomography_json["options"]["interface"] = qnic_interfaces;
  return tomography_json;
}

void Tomography::deserialize_json(json serialized) {
  auto options = serialized["options"];
  if (options != nullptr) {
    // get options one by one
    options["num_measure"].get_to(num_measurement);
    options["owner_address"].get_to(owner_address);
    options["interface"].get_to(qnic_interfaces);
  }
}
}  // namespace quisp::rules

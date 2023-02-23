#include "Action.h"

namespace quisp::rules {
using types::QNodeAddr;

Action::Action(QNodeAddr partner_addr) : partner_address(partner_addr) {
  QnicInterface qnic_interface{partner_addr};
  qnic_interfaces.emplace_back(qnic_interface);
};

Action::Action(std::vector<QNodeAddr> partner_addr) {
  for (int i = 0; i < partner_addr.size(); i++) {
    QnicInterface qnic_interface{partner_addr.at(i)};
    qnic_interfaces.emplace_back(qnic_interface);
  }
}

Purification::Purification(PurType purification_type, QNodeAddr partner_addr, int shared_rule_tag)
    : Action(partner_addr), purification_type(purification_type), shared_rule_tag(shared_rule_tag) {}

json Purification::serialize_json() {
  json purification_json;
  purification_json["type"] = "purification";
  purification_json["options"]["purification_type"] = purification_type;
  purification_json["options"]["interface"] = qnic_interfaces;
  purification_json["options"]["shared_rule_tag"] = shared_rule_tag;
  return purification_json;
}

void Purification::deserialize_json(json serialized) {
  auto options = serialized["options"];
  if (options != nullptr) {
    // get options one by one
    options["purification_type"].get_to(purification_type);
    options["interface"].get_to(qnic_interfaces);
    options["shared_rule_tag"].get_to(shared_rule_tag);
  }
}

EntanglementSwapping::EntanglementSwapping(std::vector<QNodeAddr> partner_addr, int shared_rule_tag) : Action(partner_addr), shared_rule_tag(shared_rule_tag) {
  for (int i = 0; i < partner_addr.size(); i++) {
    QnicInterface remote_qnic_interface{partner_addr.at(i)};
    remote_qnic_interfaces.push_back(remote_qnic_interface);
  }
}

json EntanglementSwapping::serialize_json() {
  json swapping_json;
  swapping_json["type"] = "swapping";
  swapping_json["options"]["interface"] = qnic_interfaces;
  swapping_json["options"]["remote_interface"] = remote_qnic_interfaces;
  swapping_json["options"]["shared_rule_tag"] = shared_rule_tag;
  return swapping_json;
}

void EntanglementSwapping::deserialize_json(json serialized) {
  auto options = serialized["options"];
  if (options != nullptr) {
    // get options one by one
    options["interface"].get_to(qnic_interfaces);
    options["remote_interface"].get_to(remote_qnic_interfaces);
    options["shared_rule_tag"].get_to(shared_rule_tag);
  }
}

PurificationCorrelation::PurificationCorrelation(QNodeAddr partner_addr, int shared_rule_tag) : Action(partner_addr), shared_rule_tag(shared_rule_tag) {}

json PurificationCorrelation::serialize_json() {
  json wait_json;
  wait_json["type"] = "purification_correlation";
  wait_json["options"]["interface"] = qnic_interfaces;
  wait_json["options"]["shared_rule_tag"] = shared_rule_tag;
  return wait_json;
}

void PurificationCorrelation::deserialize_json(json serialized) {
  auto options = serialized["options"];
  if (options != nullptr) {
    options["interface"].get_to(qnic_interfaces);
    options["shared_rule_tag"].get_to(shared_rule_tag);
  }
}

SwappingCorrection::SwappingCorrection(QNodeAddr swapper_addr, int shared_rule_tag) : Action(swapper_addr), shared_rule_tag(shared_rule_tag) {}

json SwappingCorrection::serialize_json() {
  json wait_json;
  wait_json["type"] = "swapping_correction";
  wait_json["options"]["interface"] = qnic_interfaces;
  wait_json["options"]["shared_rule_tag"] = shared_rule_tag;
  return wait_json;
}

void SwappingCorrection::deserialize_json(json serialized) {
  auto options = serialized["options"];
  if (options != nullptr) {
    options["interface"].get_to(qnic_interfaces);
    options["shared_rule_tag"].get_to(shared_rule_tag);
  }
}

Tomography::Tomography(int num_measurement, QNodeAddr owner_addr, QNodeAddr partner_addr) : Action(partner_addr), num_measurement(num_measurement), owner_address(owner_addr) {}

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

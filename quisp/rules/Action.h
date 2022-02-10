#pragma once
#include <modules/QNIC.h>
#include <modules/QUBIT.h>
#include <nlohmann/json.hpp>

using nlohmann::json;
using quisp::modules::QNIC_type;
namespace quisp::rules {

enum PurType : int {
  SINGLE_X,  ///< Single purification for X error
  SINGLE_Z,  ///< Single purification for Z error
  DOUBLE,  ///< Double purification both for X and Z errors
  DOUBLE_INV,  ///< Double inverse purification both for X and Z errors
  SSDP_X,  ///< Single Selection and Double Purification (DoubleSelectionAction) for X error
  SSDP_Z,  ///< Single Selection and Double Purification (DoubleSelectionAction) for Z error
  SSDP_X_INV,  ///< Single Selection and Double Purification Inverse (DoubleSelectionAction) for X error
  SSDP_Z_INV,  ///< Single Selection and Double Purification Inverse (DoubleSelectionAction) for Z error
  DSDA,  ///< Double Selection and Dual Action for both X and Z errors
  DSDA_INV,  ///< Inverse Double Selection and Dual Action for both X and Z errors
  DSDA_SECOND,  ///< Different type of Double Selection and Dual Action for both X and Z errors
  DSDA_SECOND_INV  ///< Different type of Inverse Double Selection and Dual Action for both X and Z errors
};

NLOHMANN_JSON_SERIALIZE_ENUM(PurType, {
                                          {SINGLE_X, "SINGLE_X"},
                                          {SINGLE_Z, "SINGLE_Z"},
                                          {DOUBLE, "DOUBLE"},
                                          {DOUBLE_INV, "DOUBLE_INV"},
                                          {SSDP_X, "SSDP_X"},
                                          {SSDP_Z, "SSDP_Z"},
                                          {SSDP_X_INV, "SSDP_X_INV"},
                                          {SSDP_Z_INV, "SSDP_Z_INV"},
                                          {DSDA, "DSDA"},
                                          {DSDA_INV, "DSDA_INV"},
                                          {DSDA_SECOND, "DSDA_SECOND"},
                                          {DSDA_SECOND_INV, "DSDA_SECOND_INV"},
                                      })
class Action {
 public:
  Action() {}  // for deserialization
  Action(int partner_addr, QNIC_type qnic_type, int qnic_id);
  Action(std::vector<int> partner_addr, std::vector<QNIC_type> qnic_type, std::vector<int> qnic_id) : partner_address(partner_addr), qnic_types(qnic_type), qnic_ids(qnic_id){};
  virtual ~Action() {}
  std::vector<int> partner_address;
  std::vector<QNIC_type> qnic_types;
  std::vector<int> qnic_ids;

  virtual json serialize_json() = 0;
  virtual void deserialize_json(json serialized) = 0;
};

class Purification : public Action {
 public:
  Purification(json serialized) { deserialize_json(serialized); }  // for deserialization
  Purification(PurType purification_type, int partner_addr, QNIC_type qnic_type, int qnic_id);
  PurType purification_type;
  json serialize_json() override;
  void deserialize_json(json serialized) override;
};

class EntanglementSwapping : public Action {
 public:
  EntanglementSwapping(json serialized) { deserialize_json(serialized); }  // for deserialization
  EntanglementSwapping(std::vector<int> partner_addr, std::vector<QNIC_type> qnic_type, std::vector<int> qnic_id);
  json serialize_json() override;
  void deserialize_json(json serialized) override;
};

class Wait : public Action {
 public:
  Wait(json serialized) { deserialize_json(serialized); }  // for deserialization
  Wait(int partner_addr, QNIC_type qnic_type, int qnic_id);
  json serialize_json() override;
  void deserialize_json(json serialized) override;
};

class Tomography : public Action {
 public:
  Tomography(json serialized) { deserialize_json(serialized); }  // for deserialization
  Tomography(int num_measurement, int partner_addr, QNIC_type qnic_type, int qnic_id);
  int num_measurement;
  json serialize_json() override;
  void deserialize_json(json serialized) override;
};

}  // namespace quisp::rules

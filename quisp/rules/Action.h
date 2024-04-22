#pragma once
#include <nlohmann/json.hpp>

#include "modules/QNIC.h"
#include "modules/QUBIT.h"

using nlohmann::json;
using quisp::modules::QNIC_type;
namespace quisp::rules {

struct QnicInterface {
  int partner_addr;
};

enum PurType : int {
  INVALID,  ///< Invalid purification type
  SINGLE_SELECTION_X_PURIFICATION,  ///< Single purification for X error
  SINGLE_SELECTION_Z_PURIFICATION,  ///< Single purification for Z error
  SINGLE_SELECTION_Y_PURIFICATION,
  SINGLE_SELECTION_XZ_PURIFICATION,  ///< Double purification both for X and Z errors
  SINGLE_SELECTION_ZX_PURIFICATION,  ///< Double inverse purification both for X and Z errors
  DOUBLE_SELECTION_X_PURIFICATION,  ///< Double selection XZ and single action (DoubleSelectionAction) for X error
  DOUBLE_SELECTION_Z_PURIFICATION,  ///< Inverse Double selection XZ and single action(DoubleSelectionAction) for X error
  DOUBLE_SELECTION_XZ_PURIFICATION,  ///< Double Selection and Dual Action for both X and Z errors
  DOUBLE_SELECTION_ZX_PURIFICATION,  ///< Inverse Double Selection and Dual Action for both X and Z errors
  DOUBLE_SELECTION_X_PURIFICATION_SINGLE_SELECTION_Z_PURIFICATION,  ///< Different type of Double Selection and Dual Action for both X and Z errors
  DOUBLE_SELECTION_Z_PURIFICATION_SINGLE_SELECTION_X_PURIFICATION,  ///< Different type of Inverse Double Selection and Dual Action for both X and Z errors
};

NLOHMANN_JSON_SERIALIZE_ENUM(PurType, {
                                          {INVALID, "INVALID"},
                                          {SINGLE_SELECTION_X_PURIFICATION, "SINGLE_SELECTION_X_PURIFICATION"},
                                          {SINGLE_SELECTION_Z_PURIFICATION, "SINGLE_SELECTION_Z_PURIFICATION"},
                                          {SINGLE_SELECTION_Y_PURIFICATION, "SINGLE_SELECTION_Y_PURIFICATION"},
                                          {SINGLE_SELECTION_XZ_PURIFICATION, "SINGLE_SELECTION_XZ_PURIFICATION"},
                                          {SINGLE_SELECTION_ZX_PURIFICATION, "SINGLE_SELECTION_ZX_PURIFICATION"},
                                          {DOUBLE_SELECTION_X_PURIFICATION, "DOUBLE_SELECTION_X_PURIFICATION"},
                                          {DOUBLE_SELECTION_Z_PURIFICATION, "DOUBLE_SELECTION_Z_PURIFICATION"},
                                          {DOUBLE_SELECTION_XZ_PURIFICATION, "DOUBLE_SELECTION_XZ_PURIFICATION"},
                                          {DOUBLE_SELECTION_ZX_PURIFICATION, "DOUBLE_SELECTION_ZX_PURIFICATION"},
                                          {DOUBLE_SELECTION_X_PURIFICATION_SINGLE_SELECTION_Z_PURIFICATION, "DOUBLE_SELECTION_X_PURIFICATION_SINGLE_SELECTION_Z_PURIFICATION"},
                                          {DOUBLE_SELECTION_Z_PURIFICATION_SINGLE_SELECTION_X_PURIFICATION, "DOUBLE_SELECTION_Z_PURIFICATION_SINGLE_SELECTION_X_PURIFICATION"},
                                      })

inline void to_json(json& j, const QnicInterface& qi) { j = json{{"partner_address", qi.partner_addr}}; }

inline void from_json(const json& j, QnicInterface& qi) { j.at("partner_address").get_to(qi.partner_addr); }
class Action {
 public:
  Action() {}  // for deserialization
  Action(int partner_addr);
  Action(std::vector<int> partner_addr);
  virtual ~Action() {}
  std::vector<QnicInterface> qnic_interfaces;
  int partner_address;
  virtual json serialize_json() = 0;
  virtual void deserialize_json(json serialized) = 0;
};

class Purification : public Action {
 public:
  Purification(json serialized) { deserialize_json(serialized); }  // for deserialization
  Purification(PurType purification_type, int partner_addr, int shared_rule_tag);
  PurType purification_type;
  int shared_rule_tag;
  json serialize_json() override;
  void deserialize_json(json serialized) override;
};

class EntanglementSwapping : public Action {
 public:
  EntanglementSwapping(json serialized) { deserialize_json(serialized); }  // for deserialization
  EntanglementSwapping(std::vector<int> partner_addr, int shared_rule_tag);
  std::vector<QnicInterface> remote_qnic_interfaces;
  int shared_rule_tag;
  json serialize_json() override;
  void deserialize_json(json serialized) override;
};

class PurificationCorrelation : public Action {
 public:
  PurificationCorrelation(json serialized) { deserialize_json(serialized); }  // for deserialization
  PurificationCorrelation(int partner_addr, int shared_rule_tag);
  int shared_rule_tag;
  json serialize_json() override;
  void deserialize_json(json serialized) override;
};

class SwappingCorrection : public Action {
 public:
  SwappingCorrection(json serialized) { deserialize_json(serialized); }  // for deserialization
  SwappingCorrection(int swapper_addr, int shared_rule_tag);
  int shared_rule_tag;
  json serialize_json() override;
  void deserialize_json(json serialized) override;
};

class Tomography : public Action {
 public:
  Tomography(json serialized) { deserialize_json(serialized); }  // for deserialization
  Tomography(int num_measurement, int owner_addr, int partner_addr);
  simtime_t start_time = -1;
  int num_measurement;
  int owner_address;
  json serialize_json() override;
  void deserialize_json(json serialized) override;
};

}  // namespace quisp::rules

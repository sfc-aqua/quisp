#pragma once
#include <nlohmann/json.hpp>
#include <optional>

#include "modules/QNIC.h"
#include "modules/QUBIT.h"
#include "types/QNodeAddr.h"

namespace quisp::rules {

using nlohmann::json;
using quisp::modules::QNIC_type;
using quisp::types::QNodeAddr;

struct QnicInterface {
  types::QNodeAddr partner_addr;
};

enum PurType : int {
  INVALID,  ///< Invalid purification type
  SINGLE_X,  ///< Single purification for X error
  SINGLE_Z,  ///< Single purification for Z error
  SINGLE_Y,
  DOUBLE,  ///< Double purification both for X and Z errors
  DOUBLE_INV,  ///< Double inverse purification both for X and Z errors
  DSSA,  ///< Double selection XZ and single action (DoubleSelectionAction) for X error
  DSSA_INV,  ///< Inverse Double selection XZ and single action(DoubleSelectionAction) for X error
  DSDA,  ///< Double Selection and Dual Action for both X and Z errors
  DSDA_INV,  ///< Inverse Double Selection and Dual Action for both X and Z errors
  DSDA_SECOND,  ///< Different type of Double Selection and Dual Action for both X and Z errors
  DSDA_SECOND_INV,  ///< Different type of Inverse Double Selection and Dual Action for both X and Z errors
};

NLOHMANN_JSON_SERIALIZE_ENUM(PurType, {
                                          {INVALID, "INVALID"},
                                          {SINGLE_X, "SINGLE_X"},
                                          {SINGLE_Z, "SINGLE_Z"},
                                          {SINGLE_Y, "SINGLE_Y"},
                                          {DOUBLE, "DOUBLE"},
                                          {DOUBLE_INV, "DOUBLE_INV"},
                                          {DSSA, "DSSA"},
                                          {DSSA_INV, "DSSA_INV"},
                                          {DSDA, "DSDA"},
                                          {DSDA_INV, "DSDA_INV"},
                                          {DSDA_SECOND, "DSDA_SECOND"},
                                          {DSDA_SECOND_INV, "DSDA_SECOND_INV"},
                                      })

inline void to_json(json& j, const QnicInterface& qi) { j = json{{"partner_address", qi.partner_addr}}; }

inline void from_json(const json& j, QnicInterface& qi) { j.at("partner_address").get_to(qi.partner_addr); }
class Action {
 public:
  Action() {}  // for deserialization
  Action(QNodeAddr partner_addr);
  Action(std::vector<QNodeAddr> partner_addr);
  virtual ~Action() {}
  std::vector<QnicInterface> qnic_interfaces;
  QNodeAddr partner_address;
  virtual json serialize_json() = 0;
  virtual void deserialize_json(json serialized) = 0;
};

class Purification : public Action {
 public:
  Purification(json serialized) { deserialize_json(serialized); }  // for deserialization
  Purification(PurType purification_type, QNodeAddr partner_addr, int shared_rule_tag);
  PurType purification_type;
  int shared_rule_tag;
  json serialize_json() override;
  void deserialize_json(json serialized) override;
};

class EntanglementSwapping : public Action {
 public:
  EntanglementSwapping(json serialized) { deserialize_json(serialized); }  // for deserialization
  EntanglementSwapping(std::vector<QNodeAddr> partner_addr, int shared_rule_tag);
  std::vector<QnicInterface> remote_qnic_interfaces;
  int shared_rule_tag;
  json serialize_json() override;
  void deserialize_json(json serialized) override;
};

class PurificationCorrelation : public Action {
 public:
  PurificationCorrelation(json serialized) { deserialize_json(serialized); }  // for deserialization
  PurificationCorrelation(QNodeAddr partner_addr, int shared_rule_tag);
  int shared_rule_tag;
  json serialize_json() override;
  void deserialize_json(json serialized) override;
};

class SwappingCorrection : public Action {
 public:
  SwappingCorrection(json serialized) { deserialize_json(serialized); }  // for deserialization
  SwappingCorrection(QNodeAddr swapper_addr, int shared_rule_tag);
  SwappingCorrection(QNodeAddr swapper_addr, int shared_rule_tag, std::optional<unsigned long> upper_layer_ruleset_id);
  int shared_rule_tag;
  std::optional<unsigned long> upper_layer_ruleset_id;
  json serialize_json() override;
  void deserialize_json(json serialized) override;
};

class Tomography : public Action {
 public:
  Tomography(json serialized) { deserialize_json(serialized); }  // for deserialization
  Tomography(int num_measurement, types::QNodeAddr owner_addr, types::QNodeAddr partner_addr);
  simtime_t start_time = -1;
  int num_measurement;
  types::QNodeAddr owner_address;
  json serialize_json() override;
  void deserialize_json(json serialized) override;
};

}  // namespace quisp::rules

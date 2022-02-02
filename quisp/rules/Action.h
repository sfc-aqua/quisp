#pragma once
#include <modules/QNIC.h>
#include <modules/QUBIT.h>
#include <nlohmann/json.hpp>

using nlohmann::json;
using quisp::modules::QNIC_type;
namespace quisp::rules {

enum class PurType : int {
  SINGLE_X,  ///< Single purification for X error
  SSIGLE_Z,  ///< Single purification for Z error
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
class Action {
 public:
  Action(int partner_addr, QNIC_type qnic_type, int qnic_id);
  Action(std::vector<int> partner_addr, std::vector<QNIC_type> qnic_type, std::vector<int> qnic_id) : partner_address(partner_addr), qnic_types(qnic_type), qnic_ids(qnic_id){};
  virtual ~Action() {}
  std::vector<int> partner_address;
  std::vector<QNIC_type> qnic_types;
  std::vector<int> qnic_ids;

  virtual json serialize() = 0;
};

class Purification : public Action {
 public:
  Purification(PurType purification_type, int partner_addr, QNIC_type qnic_type, int qnic_id);
  PurType purification_type;
  json serialize() override;
};

class EntanglementSwapping : public Action {
 public:
  EntanglementSwapping(std::vector<int> partner_addr, std::vector<QNIC_type> qnic_type, std::vector<int> qnic_id);
  json serialize() override;
};

class Wait : public Action {
 public:
  Wait(int partner_addr, QNIC_type qnic_type, int qnic_id);
  json serialize() override;
};

class Tomography : public Action {
 public:
  Tomography(int num_measurement, int partner_addr, QNIC_type qnic_type, int qnic_id);
  int num_measurement;
  json serialize() override;
};

}  // namespace quisp::rules

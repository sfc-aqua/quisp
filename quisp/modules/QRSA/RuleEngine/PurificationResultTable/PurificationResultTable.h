// #pragma once
// #include <stdexcept>
// #include <unordered_map>

// #include <messages/classical_messages.h>
// #include <rules/Action.h>

// namespace quisp::modules::pur_result_table {
// using quisp::rules::PurType;

// struct PurificationResultKey {
//   unsigned long rs_id = -1;
//   int rule_id = -1;
//   int action_index = -1;
//   int shared_tag = -1;
//   rules::PurType type;
//   PurificationResultKey() {}

//   PurificationResultKey(const messages::PurificationResult& result) {
//     rs_id = result.getRuleset_id();
//     rule_id = result.getRule_id();
//     action_index = result.getAction_index();
//     shared_tag = result.getShared_tag();
//     type = (rules::PurType)result.getPurType();
//   }

//   PurificationResultKey(const messages::DoublePurificationResult& result) {
//     rs_id = result.getRuleset_id();
//     rule_id = result.getRule_id();
//     action_index = result.getAction_index();
//     shared_tag = result.getShared_tag();
//     type = (rules::PurType)result.getPurType();
//   }

//   PurificationResultKey(const messages::DS_DoublePurificationResult& result) {
//     rs_id = result.getRuleset_id();
//     rule_id = result.getRule_id();
//     action_index = result.getAction_index();
//     shared_tag = result.getShared_tag();
//     type = (rules::PurType)result.getPurType();
//   }

//   PurificationResultKey(const messages::DS_DoublePurificationSecondResult& result) {
//     rs_id = result.getRuleset_id();
//     rule_id = result.getRule_id();
//     action_index = result.getAction_index();
//     shared_tag = result.getShared_tag();
//     type = (rules::PurType)result.getPurType();
//   }

//   // intentionally ignore rule_id because the rule_id might be different in each node
//   bool operator==(const PurificationResultKey& key) const { return rs_id == key.rs_id && action_index == key.action_index && shared_tag == key.shared_tag; }
// };

// struct PurificationResultData {
//   bool is_x_plus = false;
//   bool is_z_plus = false;
//   bool is_ds_x_plus = false;
//   bool is_ds_z_plus = false;
//   bool is_ds_plus = false;
//   PurType pur_type = PurType::INVALID;

//   PurificationResultData() {}

//   bool isResultMatched(const PurificationResultData& result, PurType type) const {
//     switch (type) {
//       case PurType::SINGLE_X:
//         return result.is_z_plus == is_z_plus;
//       case PurType::SINGLE_Z:
//         return result.is_x_plus == is_x_plus;
//       case PurType::SINGLE_Y:
//         return result.is_z_plus == is_z_plus;
//       case PurType::DOUBLE:
//       case PurType::DOUBLE_INV:
//       case PurType::DSSA:
//       case PurType::DSSA_INV:
//         return result.is_x_plus == is_x_plus && result.is_z_plus == is_z_plus;
//       case PurType::DSDA:
//       case PurType::DSDA_INV:
//         return result.is_x_plus == is_x_plus && result.is_z_plus == is_z_plus && result.is_ds_x_plus == is_ds_x_plus && result.is_ds_z_plus == is_ds_z_plus;
//       case PurType::DSDA_SECOND:
//       case PurType::DSDA_SECOND_INV:
//         return result.is_x_plus == is_x_plus && result.is_z_plus == is_z_plus && result.is_ds_plus == is_ds_plus;
//       default:
//         throw std::runtime_error("the pur type not implemented yet");
//     }
//   }

//   PurificationResultData(const messages::PurificationResult& result) {
//     pur_type = (PurType)result.getPurType();
//     if (pur_type == PurType::SINGLE_X) {
//       is_z_plus = result.getOutput_is_plus();
//       return;
//     }
//     if (pur_type == PurType::SINGLE_Z) {
//       is_x_plus = result.getOutput_is_plus();
//       return;
//     }
//     if (pur_type == PurType::SINGLE_Y) {
//       is_z_plus = result.getOutput_is_plus();
//       return;
//     }
//     if (pur_type == PurType::DOUBLE || pur_type == PurType::DOUBLE_INV || pur_type == PurType::DSSA || pur_type == PurType::DSSA_INV) {
//       const auto& r = dynamic_cast<const messages::DoublePurificationResult&>(result);
//       is_z_plus = r.getZOutput_is_plus();
//       is_x_plus = r.getXOutput_is_plus();
//       return;
//     }
//     if (pur_type == PurType::DSDA_SECOND || pur_type == PurType::DSDA_SECOND_INV) {
//       const auto& r = dynamic_cast<const messages::DS_DoublePurificationSecondResult&>(result);
//       is_z_plus = r.getZOutput_is_plus();
//       is_x_plus = r.getXOutput_is_plus();
//       is_ds_plus = r.getDS_Output_is_plus();
//       return;
//     }
//     if (pur_type == PurType::DSDA || pur_type == PurType::DSDA_INV) {
//       const auto& r = dynamic_cast<const messages::DS_DoublePurificationResult&>(result);
//       is_z_plus = r.getZOutput_is_plus();
//       is_x_plus = r.getXOutput_is_plus();
//       is_ds_x_plus = r.getDS_XOutput_is_plus();
//       is_ds_z_plus = r.getDS_ZOutput_is_plus();
//       return;
//     }
//   }
// };

// using PurificationResultTable = std::unordered_map<PurificationResultKey, PurificationResultData>;
// std::ostream& operator<<(std::ostream& os, const quisp::modules::pur_result_table::PurificationResultTable& table);

// }  // namespace quisp::modules::pur_result_table

// namespace std {
// template <>
// struct ::std::hash<quisp::modules::pur_result_table::PurificationResultKey> {
//  public:
//   size_t operator()(const quisp::modules::pur_result_table::PurificationResultKey& k) const {
//     auto seed = std::hash<unsigned long>()(k.rs_id);
//     // https://stackoverflow.com/questions/4948780/magic-number-in-boosthash-combine
//     // intentionally ignore rule_id because the rule_id might be different in each node
//     seed ^= std::hash<int>()(k.action_index) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
//     seed ^= std::hash<int>()(k.shared_tag) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
//     seed ^= std::hash<int>()(k.type) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
//     return seed;
//   }
// };
// }  // namespace std

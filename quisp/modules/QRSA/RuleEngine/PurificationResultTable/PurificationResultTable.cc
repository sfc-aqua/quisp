#include "PurificationResultTable.h"

namespace std {

std::ostream &operator<<(std::ostream &os, const quisp::modules::pur_result_table::PurificationResultTable &table) {
  for (auto &[key, data] : table) {
    os << "(rule_id: " << key.rule_id << ", tag:" << key.shared_tag << ", act" << key.action_index << "): is_x_plus:" << data.is_x_plus << ", ";
  }
  return os;
}
}  // namespace std

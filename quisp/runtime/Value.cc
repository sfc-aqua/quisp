#include "Value.h"

namespace quisp::runtime {
std::ostream& operator<<(std::ostream& stream, const MemoryValue& value) {
  switch (value.type) {
    case ValueType::INT:
      stream << std::to_string(value.intValue());
      break;
    case ValueType::MEASUREMENT_OUTCOME:
      auto o = value.outcome();
      stream << "basis: " << std::to_string(o.basis) << ", GOD_clean: " << std::to_string(o.GOD_clean) << ", is_plus: " << o.outcome_is_plus;
      break;
  }
  return stream;
}

}  // namespace quisp::runtime

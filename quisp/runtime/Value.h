#pragma once
#include "types.h"

namespace quisp::runtime {

/// @brief actual memory value that can hold multiple types of values.
union ValueUnion {
  int int_value;
  MeasurementOutcome outcome;
  ValueUnion(int val) : int_value(val) {}
  ValueUnion(MeasurementOutcome val) : outcome(val) {}
};

/// @brief enum for memory value types
enum class ValueType {
  INT,
  MEASUREMENT_OUTCOME,
};

/// @brief memory value
class MemoryValue {
 public:
  MemoryValue(int val) : type(ValueType::INT), val(val) {}
  MemoryValue(MeasurementOutcome val) : type(ValueType::MEASUREMENT_OUTCOME), val(val) {}

  /// @brief return integer value if the type check passed.
  int intValue() const {
    if (type != ValueType::INT) throw std::runtime_error("the value is not an integer");
    return val.int_value;
  }

  /// @brief returns measurement outcome if the type check passed.
  MeasurementOutcome outcome() const {
    if (type != ValueType::MEASUREMENT_OUTCOME) throw std::runtime_error("the value is not a MeasurementOutcome");
    return val.outcome;
  }

  ValueType type;

 private:
  ValueUnion val;
};

std::ostream& operator<<(std::ostream& stream, const MemoryValue& value);

}  // namespace quisp::runtime

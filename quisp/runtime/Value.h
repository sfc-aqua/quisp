#pragma once
#include "types.h"

namespace quisp::runtime {
union ValueUnion {
  int intValue;
  MeasurementOutcome outcome;
  ValueUnion(int val) : intValue(val) {}
  ValueUnion(MeasurementOutcome val) : outcome(val) {}
};

enum class ValueType {
  INT,
  MEASUREMENT_OUTCOME,
};

class MemoryValue {
 public:
  MemoryValue(int val) : type(ValueType::INT), _val(val) {}
  MemoryValue(MeasurementOutcome val) : type(ValueType::MEASUREMENT_OUTCOME), _val(val) {}

  int intValue() const {
    if (type != ValueType::INT) throw std::runtime_error("the value is not an integer");
    return _val.intValue;
  }
  MeasurementOutcome outcome() const {
    if (type != ValueType::MEASUREMENT_OUTCOME) throw std::runtime_error("the value is not a MeasurementOutcome");
    return _val.outcome;
  }

  ValueType type;

 private:
  ValueUnion _val;
};

std::ostream& operator<<(std::ostream& stream, const MemoryValue& value);

}  // namespace quisp::runtime

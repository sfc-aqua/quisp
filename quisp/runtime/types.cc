#include "types.h"

#include <functional>
#include <iostream>
#include <string>

namespace quisp::runtime {

QubitId::QubitId(int val) : val(val) {}
size_t QubitId::operator()(const QubitId& id) const { return std::hash<int>()(id.val); }
std::ostream& operator<<(std::ostream& stream, const QubitId& value) {
  stream << "QubitId(" << std::to_string(value.val) << ")";
  return stream;
}
bool operator<(const QubitId& a, const QubitId& b) { return a.val < b.val; }
bool operator==(const QubitId& a, const QubitId& b) { return a.val == b.val; }

Label::Label(std::string val) : val(val) {}
std::ostream& operator<<(std::ostream& stream, const Label& label) {
  stream << "Label(" << label.val << ")";
  return stream;
}
bool operator==(const Label& a, const Label& b) { return a.val == b.val; }

MemoryKey::MemoryKey(std::string key) : val(key) {}
std::ostream& operator<<(std::ostream& stream, const MemoryKey& key) {
  stream << "MemoryKey(" << key.val << ")";
  return stream;
}
bool operator==(const MemoryKey& a, const MemoryKey& b) { return a.val == b.val; }

std::ostream& operator<<(std::ostream& stream, const RegId& value) {
  switch (value) {
    case RegId::REG0:
      stream << std::string("REG0");
      break;
    case RegId::REG1:
      stream << std::string("REG1");
      break;
    case RegId::REG2:
      stream << std::string("REG2");
      break;
    case RegId::REG3:
      stream << std::string("REG3");
      break;
    case RegId::REG4:
      stream << std::string("REG4");
      break;
  }
  return stream;
};

std::ostream& operator<<(std::ostream& stream, const ReturnCode& value) {
  switch (value) {
    case ReturnCode::COND_FAILED:
      stream << std::string("COND_FAILED");
      break;
    case ReturnCode::COND_PASSED:
      stream << std::string("COND_PASSED");
      break;
    case ReturnCode::NONE:
      stream << std::string("NONE");
      break;
    case ReturnCode::RS_TERMINATED:
      stream << std::string("RS_TERMINATED");
      break;
    case ReturnCode::ERROR:
      stream << std::string("ERROR");
      break;
  }
  return stream;
};

std::ostream& operator<<(std::ostream& stream, const Basis& value) {
  switch (value) {
    case Basis::X:
      stream << std::string("X");
      break;
    case Basis::Z:
      stream << std::string("Z");
      break;
    case Basis::Y:
      stream << std::string("Y");
      break;
    case Basis::RANDOM:
      stream << std::string("RANDOM");
      break;
  }
  return stream;
};
}  // namespace quisp::runtime

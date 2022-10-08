#include "types.h"
#include <functional>
#include <iostream>
#include <string>

namespace quisp::runtime {

QNodeAddr::QNodeAddr(int val) : val(val) {}
std::ostream& operator<<(std::ostream& stream, const QNodeAddr& value) {
  stream << "QNodeAddr(" << std::to_string(value.val) << ")";
  return stream;
}
bool operator<(const QNodeAddr& a, const QNodeAddr& b) { return a.val < b.val; }
bool operator==(const QNodeAddr& a, const QNodeAddr& b) { return a.val == b.val; }

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
    case Basis::RANDOM:
      stream << std::string("RANDOM");
      break;
  }
  return stream;
};
}  // namespace quisp::runtime

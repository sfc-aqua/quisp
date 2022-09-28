#include "types.h"
namespace quisp::runtime {
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

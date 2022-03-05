#pragma once
#include <cstddef>

namespace quisp::backends::abstract {
class IQubitId {
 public:
  virtual ~IQubitId(){};
  virtual std::size_t operator()() const = 0;
};
}  // namespace quisp::backends::abstract

#pragma once
#include <string>

namespace quisp::backends::abstract {

/**
 * @brief just an interface for the configuration to the backend
 */
class IConfiguration {
 public:
  IConfiguration(){};
  virtual ~IConfiguration(){};
};

}  // namespace quisp::backends::abstract

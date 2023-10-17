#pragma once

#include <omnetpp.h>

namespace quisp::modules {

class IConnectionManager : public omnetpp::cSimpleModule {
 public:
  virtual ~IConnectionManager(){};
};

}  // namespace quisp::modules

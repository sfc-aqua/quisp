#pragma once

#include <omnetpp.h>

namespace quisp::modules {

class IConnectionManager : public omnetpp::cSimpleModule {
 public:
  virtual ~IConnectionManager(){};
  virtual unsigned long createUniqueId() = 0;
};

}  // namespace quisp::modules

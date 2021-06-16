#pragma once

#include <omnetpp.h>
#include "omnetpp/cconfigoption.h"
using namespace omnetpp;
namespace quisp_test {

class TestKeyValue : public omnetpp::cConfiguration::KeyValue {
 public:
  TestKeyValue() {}
  const char *getKey() const override { return ""; };
  const char *getValue() const override { return ""; };
  const char *getBaseDirectory() const override { return ""; };
};

}  // namespace quisp_test
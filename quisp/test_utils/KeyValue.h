#pragma once

#include <omnetpp.h>

namespace quisp_test {
namespace key_value {

class TestKeyValue : public omnetpp::cConfiguration::KeyValue {
 public:
  TestKeyValue() {}
  const char *getKey() const override { return ""; };
  const char *getValue() const override { return ""; };
  const char *getBaseDirectory() const override { return ""; };
};

}  // namespace key_value
}  // namespace quisp_test
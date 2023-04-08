#pragma once

#include <omnetpp.h>

namespace quisp_test::key_value {

class TestKeyValue : public omnetpp::cConfiguration::KeyValue {
 public:
  TestKeyValue(const char *key, const char *value) : key(key), value(value) {}
  TestKeyValue() {}
  const char *key = "";
  const char *value = "";
  const char *getKey() const override { return key; };
  const char *getValue() const override { return value; };
  const char *getBaseDirectory() const override { return ""; };
};

}  // namespace quisp_test::key_value
#pragma once

#include <omnetpp.h>
#include "KeyValue.h"

namespace quisp_test {
namespace configuration {

using key_value::TestKeyValue;

class Configuration : public omnetpp::cConfiguration {
 private:
  std::vector<TestKeyValue> kvs;

 public:
  Configuration() {
    kvs = std::vector<TestKeyValue>();
    auto kv = TestKeyValue{};
    kvs.push_back(kv);
  }
  virtual const char *getConfigValue(const char *key) const override { return nullptr; };
  virtual const KeyValue &getConfigEntry(const char *key) const override { return kvs.at(0); };
  virtual const char *getPerObjectConfigValue(const char *objectFullPath, const char *keySuffix) const override { return nullptr; };
  virtual const KeyValue &getPerObjectConfigEntry(const char *objectFullPath, const char *keySuffix) const override { return kvs.at(0); };
  virtual const char *substituteVariables(const char *value) const override { return nullptr; };
};

}  // namespace configuration
}  // namespace quisp_test
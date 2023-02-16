#pragma once

#include <omnetpp.h>
#include "KeyValue.h"

namespace quisp_test::configuration {

using key_value::TestKeyValue;

class Configuration : public omnetpp::cConfiguration {
 public:
  Configuration();
  virtual const char *getConfigValue(const char *key) const override;
  virtual const KeyValue &getConfigEntry(const char *key) const override;
  virtual const char *getPerObjectConfigValue(const char *objectFullPath, const char *keySuffix) const override;
  virtual const KeyValue &getPerObjectConfigEntry(const char *objectFullPath, const char *keySuffix) const override { return kvs.at(0); };
  virtual const char *substituteVariables(const char *value) const override { return nullptr; };
  std::vector<TestKeyValue> kvs;
};

}  // namespace quisp_test::configuration
#pragma once

#include <omnetpp.h>
#include "KeyValue.h"
#include "omnetpp/cconfiguration.h"

namespace quisp_test {
namespace configuration {

using key_value::TestKeyValue;

class Configuration : public omnetpp::cConfigurationEx {
 private:
  std::vector<TestKeyValue> kvs;

 public:
  Configuration() : omnetpp::cConfigurationEx() {
    kvs = std::vector<TestKeyValue>();
    auto kv = TestKeyValue{};
    kvs.push_back(kv);
  }
  virtual const char *getConfigValue(const char *key) const override { return nullptr; };
  virtual const KeyValue &getConfigEntry(const char *key) const override { return kvs.at(0); };
  virtual const char *getPerObjectConfigValue(const char *objectFullPath, const char *keySuffix) const override { return nullptr; };
  virtual const KeyValue &getPerObjectConfigEntry(const char *objectFullPath, const char *keySuffix) const override { return kvs.at(0); };
  virtual const char *substituteVariables(const char *value) const override { return nullptr; };
  virtual void initializeFrom(cConfiguration *bootConfig) override{};
  virtual const char *getFileName() const override { return "test-file-name"; };
  virtual void validate(const char *ignorableConfigKeys = nullptr) const override{};
  virtual std::vector<std::string> getConfigNames() override { return {}; };
  virtual void activateConfig(const char *configName, int runNumber = 0) override{};
  virtual std::string getConfigDescription(const char *configName) const override {}
  virtual std::vector<std::string> getBaseConfigs(const char *configName) const override {}
  virtual std::vector<std::string> getConfigChain(const char *configName) const override {}
  virtual int getNumRunsInConfig(const char *configName) const override {}
  virtual std::vector<RunInfo> unrollConfig(const char *configName) const override {}
  virtual const char *getActiveConfigName() const override {}
  virtual int getActiveRunNumber() const override {}
  virtual const char *getVariable(const char *varname) const override {}
  virtual std::vector<const char *> getIterationVariableNames() const override {}
  virtual std::vector<const char *> getPredefinedVariableNames() const override {}
  virtual const char *getVariableDescription(const char *varname) const override {}
  virtual void dump() const override {}
  virtual std::vector<const char *> getMatchingConfigKeys(const char *pattern) const override {}
  virtual const char *getParameterValue(const char *moduleFullPath, const char *paramName, bool hasDefaultValue) const override {}
  virtual const KeyValue &getParameterEntry(const char *moduleFullPath, const char *paramName, bool hasDefaultValue) const override {}
  virtual std::vector<const char *> getKeyValuePairs(int flags = FILT_ALL) const override {}
  virtual std::vector<const char *> getMatchingPerObjectConfigKeySuffixes(const char *objectFullPath, const char *keySuffixPattern) const override {}
};

}  // namespace configuration
}  // namespace quisp_test

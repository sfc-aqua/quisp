#include "Configuration.h"

namespace quisp_test::configuration {

Configuration::Configuration() {
  kvs = std::vector<TestKeyValue>();
  auto kv = TestKeyValue{"sim-time-limit", "10.0s"};
  kvs.push_back(kv);
}
const char *Configuration::getConfigValue(const char *key) const {
  for (auto &kv : kvs) {
    if (strcmp(kv.getKey(), key) == 0) {
      return kv.getValue();
    }
  }
  return nullptr;
};
const Configuration::KeyValue &Configuration::getConfigEntry(const char *key) const { return kvs.at(0); };

const char *Configuration::getPerObjectConfigValue(const char *objectFullPath, const char *keySuffix) const { return nullptr; };
}  // namespace quisp_test::configuration
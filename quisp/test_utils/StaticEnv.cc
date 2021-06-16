
#include "StaticEnv.h"
#include "omnetpp/cconfiguration.h"

namespace quisp_test {

StaticEnv::StaticEnv() {}

cConfiguration *StaticEnv::getConfig() { return new Configuration(); }
std::string StaticEnv::gets(const char *prompt, const char *defaultreply) {
  unsupported();
  return "";
}
void StaticEnv::undisposedObject(cObject *obj) {}
}  // namespace quisp_test
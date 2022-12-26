#include "RuntimeManager.h"
#include "omnetpp/cexception.h"

namespace quisp::runtime {

RuntimeManager::RuntimeManager(std::unique_ptr<Runtime::ICallBack> &&callback) : callback(std::move(callback)) {}

void RuntimeManager::acceptRuleSet(const RuleSet &ruleset) { runtimes.emplace_back(runtime::Runtime(ruleset, callback.get())); }

Runtime &RuntimeManager::findById(unsigned long long ruleset_id) {
  for (auto &rt : runtimes) {
    if (rt.ruleset.id == ruleset_id) {
      return rt;
    }
  }
  throw cRuntimeError("Runtime for the ruleset: %llu not found", ruleset_id);
}

void RuntimeManager::exec() {
  for (auto &runtime : runtimes) {
    // how should we delete the runtime and its ruleset?
    runtime.exec();
  }
}

std::vector<Runtime>::iterator RuntimeManager::begin() { return runtimes.begin(); }
std::vector<Runtime>::iterator RuntimeManager::end() { return runtimes.end(); }
std::vector<Runtime>::reference RuntimeManager::at(size_t index) { return runtimes.at(index); }
size_t RuntimeManager::size() const { return runtimes.size(); }

}  // namespace quisp::runtime

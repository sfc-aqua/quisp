#include "RuntimeManager.h"
#include "omnetpp/cexception.h"

namespace quisp::runtime {

RuntimeManager::RuntimeManager(std::unique_ptr<Runtime::ICallBack> &&callback) : callback(std::move(callback)) {}

void RuntimeManager::acceptRuleSet(const RuleSet &ruleset) { runtimes.emplace_back(runtime::Runtime(ruleset, callback.get())); }

Runtime *RuntimeManager::findById(unsigned long long ruleset_id) {
  for (auto &rt : runtimes) {
    if (rt.ruleset.id == ruleset_id) {
      return &rt;
    }
  }
  return nullptr;
}

void RuntimeManager::exec() {
  for (auto it = runtimes.begin(); it != runtimes.end();) {
    it->exec();
    if (it->terminated and !it->stopped) {
      it->stopped = true;
      terminated_ruleset_ids.push_back(it->ruleset.id);
      //it = runtimes.erase(it);
      ++it;
    } else {
      ++it;
    }
  }
}

std::vector<unsigned long> RuntimeManager::getTerminatedRuleSetIds() {
    return terminated_ruleset_ids;
}

void RuntimeManager::killRuntime(unsigned long ruleset_id) {
    for (auto it = runtimes.begin(); it != runtimes.end();) {
        if (it->ruleset.id == ruleset_id) {
//      rt.terminated = true;
//      rt.stopped = true;
        it = runtimes.erase(it);
    } else ++it;
  }
}
void RuntimeManager::clearTerminatedRulesetIds() {terminated_ruleset_ids.clear();}

std::vector<Runtime>::iterator RuntimeManager::begin() { return runtimes.begin(); }
std::vector<Runtime>::iterator RuntimeManager::end() { return runtimes.end(); }
std::vector<Runtime>::reference RuntimeManager::at(size_t index) { return runtimes.at(index); }
size_t RuntimeManager::size() const { return runtimes.size(); }

}  // namespace quisp::runtime

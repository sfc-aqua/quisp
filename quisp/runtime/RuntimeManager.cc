#include "RuntimeManager.h"
#include <iostream>
#include <iterator>
#include <vector>
#include "RuleSet.h"
#include "omnetpp/cexception.h"
#include "runtime/RuleSet.h"
#include "runtime/types.h"

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

std::vector<RuleSet> RuntimeManager::exec() {
  std::vector<RuleSet> ruleset_list;
  std::vector<Runtime>::iterator it = runtimes.begin();
  for (; it != runtimes.end();) {
    it->exec();
    if (it->terminated) {
      ruleset_list.push_back(it->ruleset);
      it = runtimes.erase(it);
    } else {
      ++it;
    }
  }
  return ruleset_list;
}

void RuntimeManager::stopById(unsigned long long ruleset_id) {
  auto rt = findById(ruleset_id);
  rt->terminated = true;
}

std::vector<Runtime>::iterator RuntimeManager::begin() { return runtimes.begin(); }
std::vector<Runtime>::iterator RuntimeManager::end() { return runtimes.end(); }
std::vector<Runtime>::reference RuntimeManager::at(size_t index) { return runtimes.at(index); }
size_t RuntimeManager::size() const { return runtimes.size(); }

}  // namespace quisp::runtime

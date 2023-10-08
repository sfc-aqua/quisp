#include "RuntimeManager.h"
#include <__config>
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

std::vector<Runtime>::iterator RuntimeManager::findById(unsigned long long ruleset_id) {
  for (auto it = runtimes.begin(); it != runtimes.end(); ++it) {
    if (it->ruleset.id == ruleset_id) {
      return it;
    }
  }
}

std::vector<Runtime>::iterator RuntimeManager::findTerminatedRuntimeIteratorById(unsigned long long ruleset_id) {
  for (auto it = terminated_runtimes.begin(); it != terminated_runtimes.end(); ++it) {
    if (it->ruleset.id == ruleset_id) {
      return it;
    }
  }
}

std::vector<RuleSet> RuntimeManager::exec() {
  std::vector<RuleSet> terminated_ruleset_list_tmp;
  std::vector<QNodeAddr> partners_tmp;
  for (auto it = runtimes.begin(); it != runtimes.end();) {
    it->exec();
    if (it->terminated) {
      auto partners = it->partners;
      for (auto partner : partners) {
        partners_tmp.push_back(partner);
      }
      ruleset_id_partners_map[it->ruleset.id] = partners_tmp;

      terminated_ruleset_list_tmp.push_back(it->ruleset);
      it = runtimes.erase(it);
    } else {
      ++it;
    }
  }
  return terminated_ruleset_list_tmp;
}

void RuntimeManager::stopById(unsigned long long ruleset_id) {
  auto it = findById(ruleset_id);
  it->terminated = true;
}
std::vector<QNodeAddr> RuntimeManager::findPartnersById(unsigned long long ruleset_id) {
  for (auto &[k, v] : ruleset_id_partners_map) {
    if (k == ruleset_id) {
      return v;
    }
  }
  std::vector<QNodeAddr> partners;
  return partners;
}

std::vector<Runtime>::iterator RuntimeManager::begin() { return runtimes.begin(); }
std::vector<Runtime>::iterator RuntimeManager::end() { return runtimes.end(); }
std::vector<Runtime>::reference RuntimeManager::at(size_t index) { return runtimes.at(index); }
size_t RuntimeManager::size() const { return runtimes.size(); }

}  // namespace quisp::runtime

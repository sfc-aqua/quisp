#pragma once

#include <vector>
#include "Runtime.h"
#include "runtime/RuleSet.h"

namespace quisp::runtime {
class RuntimeManager {
 public:
  RuntimeManager(std::unique_ptr<Runtime::ICallBack>&& callback);
  void acceptRuleSet(const RuleSet&);
  std::vector<Runtime>::iterator findById(unsigned long long ruleset_id);
  std::vector<RuleSet> exec();
  void stopById(unsigned long long ruleset_id);
  std::vector<Runtime>::iterator begin();
  std::vector<Runtime>::iterator end();
  std::vector<Runtime>::reference at(size_t);
  size_t size() const;
  std::vector<Runtime>::iterator findTerminatedRuleSetById(unsigned long long ruleset_id);

 protected:
  std::vector<Runtime> runtimes;
  std::unique_ptr<Runtime::ICallBack> callback;
  std::vector<std::vector<Runtime>::iterator> terminated_ruleset_list;
};
}  // namespace quisp::runtime

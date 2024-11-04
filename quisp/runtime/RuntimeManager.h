#pragma once

#include "Runtime.h"

namespace quisp::runtime {
class RuntimeManager {
 public:
  RuntimeManager(std::unique_ptr<Runtime::ICallBack>&& callback);
  void acceptRuleSet(const RuleSet&);
  Runtime* findById(unsigned long long ruleset_id);
  void exec();
  std::vector<Runtime>::iterator begin();
  std::vector<Runtime>::iterator end();
  std::vector<Runtime>::reference at(size_t);
  size_t size() const;
  void terminateRuleset(const unsigned long ruleset_id);
  const std::vector<unsigned long>& getTerminatedRulesetIds() const;

 protected:
  std::vector<Runtime> runtimes = {};
  std::unique_ptr<Runtime::ICallBack> callback;
  std::vector<unsigned long> terminated_rulesets;
};
}  // namespace quisp::runtime

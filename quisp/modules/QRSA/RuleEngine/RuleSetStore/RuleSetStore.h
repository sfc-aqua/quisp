#pragma once

#include <memory>
#include <vector>
#include "rules/RuleSet.h"

namespace quisp::modules::ruleset_store {
using quisp::rules::RuleSet;
using RuleSetVector = std::vector<std::unique_ptr<RuleSet>>;
class RuleSetStore {
 public:
  RuleSetStore() {}
  ~RuleSetStore() {}
  int size();
  RuleSetVector::const_iterator cbegin();
  RuleSetVector::const_iterator cend();
  RuleSetVector::iterator begin();
  RuleSetVector::iterator end();
  void insert(std::unique_ptr<RuleSet>& ruleset);
  void insert(RuleSet* ruleset);
  RuleSetVector::iterator erase(const RuleSetVector::const_iterator& ruleset);
  std::unique_ptr<RuleSet>& operator[](int i);
  RuleSetVector::iterator findById(long ruleset_id);

 protected:
  RuleSetVector rulesets;
};
}  // namespace quisp::modules::ruleset_store

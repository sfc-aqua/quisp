#include "RuleSetStore.h"
namespace quisp::modules::ruleset_store {

int RuleSetStore::size() { return rulesets.size(); }

RuleSetVector::const_iterator RuleSetStore::cbegin() { return rulesets.cbegin(); }
RuleSetVector::const_iterator RuleSetStore::cend() { return rulesets.cend(); }
RuleSetVector::iterator RuleSetStore::begin() { return rulesets.begin(); }
RuleSetVector::iterator RuleSetStore::end() { return rulesets.end(); }

void RuleSetStore::insert(std::unique_ptr<ActiveRuleSet>& ruleset) { rulesets.emplace_back(std::move(ruleset)); }
void RuleSetStore::insert(ActiveRuleSet* ruleset) { rulesets.emplace_back(std::unique_ptr<ActiveRuleSet>(ruleset)); }
RuleSetVector::iterator RuleSetStore::erase(const RuleSetVector::const_iterator& ruleset) { return rulesets.erase(ruleset); }
std::unique_ptr<ActiveRuleSet>& RuleSetStore::operator[](int i) {
  if (i < 0 || i >= rulesets.size()) {
    throw std::out_of_range("RuleSetStore::operator[]");
  }
  return rulesets[i];
}

RuleSetVector::iterator RuleSetStore::findById(long ruleset_id) {
  for (auto &&rs = rulesets.begin(), end = rulesets.end(); rs != end; ++rs) {
    if ((*rs)->ruleset_id == ruleset_id) return rs;
  }
  return rulesets.end();
}

}  // namespace quisp::modules::ruleset_store

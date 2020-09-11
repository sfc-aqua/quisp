/** \file RuleSet.h
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief RuleSet
 */
#ifndef QUISP_RULES_RULESET_H_
#define QUISP_RULES_RULESET_H_

#include <omnetpp.h>
#include "Rule.h"

namespace quisp {
namespace rules {

/** \class RuleSet RuleSet.h
 *
 * \brief Set of rules for the RuleEngine.
 */

class RuleSet : public std::list<pRule> {
 public:
  int owner;
  std::vector<int> entangled_partner;
  std::vector<Rule*> entangled_partner_rule;
  // int entangled_partner_left;
  // int entangled_partner_right;
  simtime_t started_at;
  unsigned long ruleset_id;
  // AvailableResourceForEachStage rc;//Defined in tools.h
  RuleSet(long id, int o, std::vector<int> e) : std::list<pRule>() {
    ruleset_id = id;
    owner = o;
    entangled_partner = e;
    started_at = simTime();
  }

  RuleSet(long id, int o, int e) : std::list<pRule>() {
    ruleset_id = id;
    owner = o;
    entangled_partner.push_back(e);
    started_at = simTime();
  }

  // RuleSet(long id, int o, int l,int r) : std::list<pRule> () {
  //     ruleset_id = id; owner = o; entangled_partner_left = l; entangled_partner_right = r; started_at = simTime();
  // }

  // RuleSet(int o, int e) : std::list<pRule> () {
  //     ruleset_id = createUniqueId(owner); owner = o; entangled_partner = e; started_at = simTime();
  // }

  void addRule(Rule* r) { push_back(pRule(r)); };
  void addRule(pRule& r) { push_back(pRule(std::move(r))); };
  void setRule_ptr(Rule* r_ptr) { this->entangled_partner_rule.push_back(r_ptr); };
  std::vector<Rule*> getRule_ptr() { return this->entangled_partner_rule; };
  void finalize();
  int getSize() { return this->size(); };
  void destroyThis() {
    EV << "Destroying this RuleSet. \n ";
    delete this;
  };
  unsigned long createUniqueId(int myAddress) {
    std::string time = SimTime().str();
    std::string address = std::to_string(myAddress);
    std::string random = std::to_string(intuniform(0, 0, 10000000));
    std::string hash_seed = address + time + random;
    std::hash<std::string> hash_fn;
    size_t t = hash_fn(hash_seed);
    unsigned long RuleSet_id = t;
    std::cout << "Hash is " << hash_seed << ", = " << t << ", int = " << RuleSet_id << "\n";
    return RuleSet_id;
  }
};

}  // namespace rules
}  // namespace quisp

#endif  // QUISP_RULES_RULESET_H_

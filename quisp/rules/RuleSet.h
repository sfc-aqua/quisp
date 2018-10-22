/** \file RuleSet.h
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief RuleSet
 */
#ifndef QUISP_RULES_RULESET_H_
#define QUISP_RULES_RULESET_H_


#include "Rule.h"
#include <omnetpp.h>

namespace quisp {
namespace rules {

/** \class RuleSet RuleSet.h
 *
 * \brief Set of rules for the RuleEngine.
 */

class RuleSet : public std::list<pRule> {
    public:
        int owner;
        int entangled_partner;
        unsigned long ruleset_id;
        //AvailableResourceForEachStage rc;//Defined in tools.h
        RuleSet(long id, int o, int e) : std::list<pRule> () { ruleset_id = id; owner = o; entangled_partner = e;}
        RuleSet(int o, int e) : std::list<pRule> () { ruleset_id = createUniqueId(owner); owner = o; entangled_partner = e;}
        void addRule(Rule * r) { push_back(pRule(r)); };
        void addRule(pRule& r) { push_back(pRule(std::move(r))); };
        void finalize();
        int getSize() {return this->size();};
        void destroyThis() {EV<<"Destroying this RuleSet. \n "; delete this; };
        unsigned long createUniqueId(int myAddress){
            std::string time = SimTime().str();
            std::string address = std::to_string(myAddress);
            std::string random = std::to_string(intuniform(0,0,10000000));
            std::string hash_seed = address+time+random;
            std::hash<std::string> hash_fn;
            size_t  t = hash_fn(hash_seed);
            unsigned long RuleSet_id = t;
            std::cout<<"Hash is "<<hash_seed<<", = "<<t<<", int = "<<RuleSet_id<<"\n";
            return RuleSet_id;
        }

};

} // namespace rules
} // namespace quisp

#endif//QUISP_RULES_RULESET_H_

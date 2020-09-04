/** \file tools.h
 *
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/09/04
 *
 *  \brief tools
 */
#ifndef QUISP_RULES_TOOLS_H_
#define QUISP_RULES_TOOLS_H_
//#include <vector>

#include <modules/RuleEngine.h>
//#include <modules/stationaryQubit.h>

namespace quisp {
namespace rules {

/*For RuleSets*/
// typedef std::map<int,stationaryQubit*> resources;//index -> qubit. List of available resource for a particular stage/Rule in this RuleSet.
// typedef std::map<int, resources> AvailableResourceForEachStage;//Rule index -> resources. List of all resources for all stages/Rules in this RuleSet.
// AvailableResourceForEachStage rc;

/*
static stationaryQubit* getPurifiedQubit_fromTop(qnicResources* resources, QNIC_type qtype, int qid, int partner, int num_purified) {
    std::pair<EntangledPairs::iterator,EntangledPairs::iterator> ret = resources[qtype][qid].equal_range(partner);//Find all resource in qytpe/qid entangled with partner.
    int real_res_id = 0;
    for (EntangledPairs::iterator it=ret.first; it!=ret.second; ++it,++real_res_id) {
        //std::cout << real_res_id << '\n';
        if (!it->second->isLocked() && it->second->numpurified == num_purified){
            stationaryQubit *pt = it->second;
            return pt;
        }
    }
    return NULL;
}*/

static StationaryQubit* getUnLockedQubit_fromTop(qnicResources* resources, QNIC_type qtype, int qid, int partner, int res_id) {
  std::pair<EntangledPairs::iterator, EntangledPairs::iterator> ret = resources[qtype][qid].equal_range(partner);  // Find all resource in qytpe/qid entangled with partner.
  int real_res_id = 0;
  for (EntangledPairs::iterator it = ret.first; it != ret.second; ++it) {
    // std::cout << real_res_id << '\n';
    if (!it->second->isLocked()) {
      if (real_res_id == res_id) {
        StationaryQubit* pt = it->second;
        return pt;
      } else {
        real_res_id++;
      }
    }
  }
  return nullptr;
}

/** \func static stationaryQubit* getQubit(qnicResources* resources, QNIC_type qtype, int qid, int partner, int res_id)*/

static StationaryQubit* getQubit(qnicResources* resources, QNIC_type qtype, int qid, int partner, int res_id) {
  // assume that qnic type is ok
  std::pair<EntangledPairs::iterator, EntangledPairs::iterator> ret = resources[qtype][qid].equal_range(partner);  // Find all resource in qytpe/qid entangled with partner.
  // stationaryQubit *use_this_qubit;

  int real_res_id = 0;
  for (EntangledPairs::iterator it = ret.first; it != ret.second; ++it, ++real_res_id) {
    // std::cout << real_res_id << '\n';
    if (real_res_id == res_id) {
      StationaryQubit* pt = it->second;
      // RuleEngine re;
      // re.freeResource(qid, it->second->par("stationaryQubit_address"), qtype);
      // re.JustATest();
      return pt;

      // use_this_qubit = it->second;
      // resources[qtype][qid].erase(it);
      // break;//Returns the top qubit in that list, if res_id = 0
    }
  }
  // resources[qtype][qid].insert(std::make_pair(-1000/*QNode IP address*/,NULL));
  return nullptr;
}

static StationaryQubit* getQubitPurified(qnicResources* resources, QNIC_type qtype, int qid, int partner, int num_purified_must) {
  std::pair<EntangledPairs::iterator, EntangledPairs::iterator> ret = resources[qtype][qid].equal_range(partner);  // Find all resource in qytpe/qid entangled with partner.
  for (EntangledPairs::iterator it = ret.first; it != ret.second; ++it) {
    if (it->second->num_purified == num_purified_must && !it->second->isLocked()) {
      StationaryQubit* pt = it->second;
      return pt;
    }
  }
  return nullptr;
}

static StationaryQubit* getQubit(cModule* re, qnicResources* resources, QNIC_type qtype, int qid, int partner, int res_id) {
  // assume that qnic type is ok
  std::pair<EntangledPairs::iterator, EntangledPairs::iterator> ret = resources[qtype][qid].equal_range(partner);  // Find all resource in qytpe/qid entangled with partner.
  // stationaryQubit *use_this_qubit;

  int real_res_id = 0;
  for (EntangledPairs::iterator it = ret.first; it != ret.second; ++it, ++real_res_id) {
    // std::cout << real_res_id << '\n';
    if (real_res_id == res_id) {
      StationaryQubit* pt = it->second;
      // rule_engine->JustATest();
      return pt;

      // use_this_qubit = it->second;
      // resources[qtype][qid].erase(it);
      // break;//Returns the top qubit in that list, if res_id = 0
    }
  }
  // resources[qtype][qid].insert(std::make_pair(-1000/*QNode IP address*/,NULL));

  return nullptr;
}

/*
static void freeConsumedQubit(resources,qnic_type,qnic_id,partner,resource){

}*/

}  // namespace rules
}  // namespace quisp

#endif  // QUISP_RULES_TOOLS_H_

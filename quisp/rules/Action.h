/** \file Action.h
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief Action
 */
#ifndef QUISP_RULES_ACTION_H_
#define QUISP_RULES_ACTION_H_

#include <omnetpp.h>
#include <modules/QNIC.h>
#include <modules/QUBIT.h>
#include <memory>



using namespace quisp::modules;

namespace quisp {
namespace rules {


/** \class Action Action.h
 *
 *  \brief Action
 */
//typedef std::unique_ptr<class Rule> pRule;

class Action {
  public:
    std::map<int,stationaryQubit*> *rule_resources;
    unsigned long ruleset_id;
    int rule_id;//Used to make the lock_id unique, together with purification_count.
    virtual cPacket* run(cModule *re, qnicResources *resources) = 0;
    virtual cPacket* run(cModule *re) = 0;
    virtual stationaryQubit* getResource_fromTop(int required_index);
    virtual int checkNumResource();
    virtual void removeResource_fromRule(stationaryQubit *qubit);
    //virtual stationaryQubit* getQubit(qnicResources* resources, QNIC_type qtype, int qid, int partner, int res_id);
};
typedef std::unique_ptr<Action> pAction;

class SwappingAction : public Action {
    protected:
        // First partner
        int left_partner;
        QNIC_type left_qnic_type;
        int left_qnic_id;
        int left_resource;
        // Second partner
        int right_partner;
        QNIC_type right_qnic_type;
        int right_qnic_id;
        int right_resource;


    public:
        SwappingAction(
                int lp, QNIC_type lqt, int lqi, int lr,
                int rp, QNIC_type rqt, int rqi, int rr
                ) {
            left_partner = lp;
            left_qnic_type = lqt;
            left_qnic_id = lqi;
            left_resource = lr;
            right_partner = rp;
            right_qnic_type = rqt;
            right_qnic_id = rqi;
            right_resource = rr;
        };

        //cPacket* run(qnicResources *resources) override;
        cPacket* run(cModule *re, qnicResources *resources) override;
};

class PurifyAction : public Action {
    protected:
        int partner; /**< Identifies entanglement partner. */
        QNIC_type qnic_type;
        int qnic_id;
        int resource; /**< Identifies qubit */
        int trash_resource;
        int mutable purification_count;//Used for locked_id in stationaryQubit. You unlock the qubit when purification is successful.
        bool X;
        bool Z;
        int num_purify;
        int action_index = 0;//To track how many times this particular action has been invoked.
    public:
        PurifyAction(int part, QNIC_type qt, int qi, int res, int tres, int rs_id, int r_id) {
            partner = part;
            qnic_type = qt;
            qnic_id = qi;
            resource = res;/*The one to purify. Index from top to bottom.*/
            trash_resource = tres;/*The one to consume to purify*/
            purification_count = 0;
            rule_id = r_id;
            ruleset_id = rs_id;
            //action_index++;
        };
        PurifyAction(unsigned long RuleSet_id, int rule_index,bool X_purification, bool Z_purification, int num_purification, int part, QNIC_type qt, int qi, int res, int tres){
            partner =part;
            qnic_type = qt;
            qnic_id = qi;
            resource = res;
            trash_resource = tres;
            purification_count = num_purification;
            rule_id = rule_index;
            ruleset_id = RuleSet_id;
            num_purify = num_purification;
            X = X_purification;
            Z = Z_purification;
            //action_index++;
        };
        PurifyAction(){

        };
        //cPacket* run(qnicResources *resources) override;
        cPacket* run(cModule *re, qnicResources *resources) override;
        cPacket* run(cModule *re) override;
};


class RandomMeasureAction : public Action {
    protected:
        int partner; /**< Identifies entanglement partner. */
        QNIC_type qnic_type;
        int qnic_id;
        int resource; /**< Identifies qubit */
        int src;
        int dst;
        int mutable current_count;

    public:
        RandomMeasureAction(int part, QNIC_type qt, int qi, int res, int srcAddr){
            partner = part;
            dst = part;
            qnic_type = qt;
            qnic_id = qi;
            resource = res;
            src = srcAddr;
            current_count = 0;
        };
        //cPacket* run(qnicResources *resources) override;
        cPacket* run(cModule *re, qnicResources *resources) override;
        cPacket* run(cModule *re) override;
};



} // namespace rules
} // namespace quisp

#endif//QUISP_RULES_ACTION_H_

/** \file Action.h
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief Action
 */
#ifndef QUISP_RULES_ACTION_H_
#define QUISP_RULES_ACTION_H_

#include <modules/QNIC.h>
#include <modules/QUBIT.h>
#include <omnetpp.h>
#include <memory>

using namespace quisp::modules;

namespace quisp {
namespace rules {

/** \class Action Action.h
 *
 *  \brief Action
 */
// typedef std::unique_ptr<class Rule> pRule;

class Action {
 public:
  std::multimap<int, StationaryQubit*>* rule_resources;
  unsigned long ruleset_id;
  int rule_id;  // Used to make the lock_id unique, together with purification_count.
  // int resource_index = 0;// for check the index of resource.
  // virtual cPacket* run(cModule *re, qnicResources *resources) = 0;
  virtual cPacket* run(cModule* re) = 0;
  virtual StationaryQubit* getResource_fromTop(int required_index);
  virtual StationaryQubit* getResource_fromTop_with_partner(int required_index, int partner);
  virtual int checkNumResource();
  virtual void removeResource_fromRule(StationaryQubit* qubit);
  // virtual StationaryQubit* getQubit(qnicResources* resources, QNIC_type qtype, int qid, int partner, int res_id);
};
typedef std::unique_ptr<Action> pAction;

class SwappingAction : public Action {
 protected:
  // First partner
  int left_partner;
  QNIC_type left_qnic_type;
  int left_qnic_id;
  int left_qnic_address;
  int left_resource;
  // Second partner
  int right_partner;
  QNIC_type right_qnic_type;
  int right_qnic_id;
  int right_qnic_address;
  int right_resource;
  int action_index = 0;

  int self_left_qnic_id;
  int self_right_qnic_id;
  QNIC_type self_left_qnic_type;
  QNIC_type self_right_qnic_type;

 public:
  // constructor of entanglement swapping
  SwappingAction(unsigned long RuleSet_id, int rule_index, int lp, QNIC_type lqt, int lqi, int lqad, int lr, int rp, QNIC_type rqt, int rqi, int rqad, int rr, int slqi,
                 QNIC_type slqt, int srqi, QNIC_type srqt) {
    ruleset_id = RuleSet_id;
    rule_id = rule_index;

    left_partner = lp;
    left_qnic_type = lqt;
    left_qnic_id = lqi;
    left_qnic_address = lqad;
    left_resource = lr;
    right_partner = rp;
    right_qnic_type = rqt;
    right_qnic_id = rqi;
    right_qnic_address = rqad;
    right_resource = rr;

    self_left_qnic_id = slqi;
    self_right_qnic_id = srqi;
    self_left_qnic_type = slqt;
    self_right_qnic_type = srqt;
  };

  // cPacket* run(qnicResources *resources) override;
  // cPacket* run(cModule *re, qnicResources *resources) override;
  cPacket* run(cModule* re) override;
};

class PurifyAction : public Action {
 protected:
  int partner; /**< Identifies entanglement partner. */
  QNIC_type qnic_type;
  int qnic_id;
  int resource; /**< Identifies qubit */
  int trash_resource;
  int mutable purification_count;  // Used for locked_id in StationaryQubit. You unlock the qubit when purification is successful.
  bool X;
  bool Z;
  int num_purify;
  int action_index = 0;  // To track how many times this particular action has been invoked.
 public:
  PurifyAction(int part, QNIC_type qt, int qi, int res, int tres, int rs_id, int r_id) {
    partner = part;
    qnic_type = qt;
    qnic_id = qi;
    resource = res; /*The one to purify. Index from top to bottom.*/
    trash_resource = tres; /*The one to consume to purify*/
    purification_count = 0;
    rule_id = r_id;
    ruleset_id = rs_id;
    // action_index++;
  };
  PurifyAction(unsigned long RuleSet_id, int rule_index, bool X_purification, bool Z_purification, int num_purification, int part, QNIC_type qt, int qi, int res, int tres) {
    partner = part;
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
    // action_index++;
  };
  PurifyAction(){

  };
  // cPacket* run(qnicResources *resources) override;
  // cPacket* run(cModule *re, qnicResources *resources) override;
  cPacket* run(cModule* re) override;
};

class DoublePurifyAction : public Action {
 protected:
  int partner; /**< Identifies entanglement partner. */
  QNIC_type qnic_type;
  int qnic_id;
  int resource; /**< Identifies qubit */
  int trash_resource_Z;
  int trash_resource_X;
  int mutable purification_count;  // Used for locked_id in StationaryQubit. You unlock the qubit when purification is successful.
  bool X;
  bool Z;
  int num_purify;
  int action_index = 0;  // To track how many times this particular action has been invoked.
 public:
  DoublePurifyAction(unsigned long RuleSet_id, int rule_index, int part, QNIC_type qt, int qi, int res, int tres_X, int tres_Z) {
    partner = part;
    qnic_type = qt;
    qnic_id = qi;
    resource = res;
    trash_resource_X = tres_X;
    trash_resource_Z = tres_Z;
    rule_id = rule_index;
    ruleset_id = RuleSet_id;
    // action_index++;
  };
  DoublePurifyAction(){

  };
  cPacket* run(cModule* re) override;
};

class DoublePurifyActionInv : public Action {
 protected:
  int partner; /**< Identifies entanglement partner. */
  QNIC_type qnic_type;
  int qnic_id;
  int resource; /**< Identifies qubit */
  int trash_resource_Z;
  int trash_resource_X;
  int mutable purification_count;  // Used for locked_id in StationaryQubit. You unlock the qubit when purification is successful.
  bool X;
  bool Z;
  int num_purify;
  int action_index = 0;  // To track how many times this particular action has been invoked.
 public:
  DoublePurifyActionInv(unsigned long RuleSet_id, int rule_index, int part, QNIC_type qt, int qi, int res, int tres_X, int tres_Z) {
    partner = part;
    qnic_type = qt;
    qnic_id = qi;
    resource = res;
    trash_resource_X = tres_X;
    trash_resource_Z = tres_Z;
    rule_id = rule_index;
    ruleset_id = RuleSet_id;
    // action_index++;
  };
  DoublePurifyActionInv(){

  };
  cPacket* run(cModule* re) override;
};

// https://arxiv.org/abs/0811.2639
class DoubleSelectionAction : public Action {
 protected:
  int partner; /**< Identifies entanglement partner. */
  QNIC_type qnic_type;
  int qnic_id;
  int resource; /**< Identifies qubit */
  int trash_resource_Z;
  int trash_resource_X;
  int mutable purification_count;  // Used for locked_id in StationaryQubit. You unlock the qubit when purification is successful.
  bool X;
  bool Z;
  int num_purify;
  int action_index = 0;  // To track how many times this particular action has been invoked.
 public:
  DoubleSelectionAction(unsigned long RuleSet_id, int rule_index, int part, QNIC_type qt, int qi, int res, int tres_X, int tres_Z) {
    partner = part;
    qnic_type = qt;
    qnic_id = qi;
    resource = res;
    trash_resource_X = tres_X;
    trash_resource_Z = tres_Z;
    rule_id = rule_index;
    ruleset_id = RuleSet_id;
    // action_index++;
  };
  DoubleSelectionAction(){

  };
  cPacket* run(cModule* re) override;
};

// https://arxiv.org/abs/0811.2639
class DoubleSelectionActionInv : public Action {
 protected:
  int partner; /**< Identifies entanglement partner. */
  QNIC_type qnic_type;
  int qnic_id;
  int resource; /**< Identifies qubit */
  int trash_resource_Z;
  int trash_resource_X;
  int mutable purification_count;  // Used for locked_id in StationaryQubit. You unlock the qubit when purification is successful.
  bool X;
  bool Z;
  int num_purify;
  int action_index = 0;  // To track how many times this particular action has been invoked.
 public:
  DoubleSelectionActionInv(unsigned long RuleSet_id, int rule_index, int part, QNIC_type qt, int qi, int res, int tres_X, int tres_Z) {
    partner = part;
    qnic_type = qt;
    qnic_id = qi;
    resource = res;
    trash_resource_X = tres_X;
    trash_resource_Z = tres_Z;
    rule_id = rule_index;
    ruleset_id = RuleSet_id;
    // action_index++;
  };
  DoubleSelectionActionInv(){

  };
  cPacket* run(cModule* re) override;
};

// https://arxiv.org/abs/0811.2639
class DoubleSelectionDualAction : public Action {
 protected:
  int partner; /**< Identifies entanglement partner. */
  QNIC_type qnic_type;
  int qnic_id;
  int resource; /**< Identifies qubit */
  int trash_resource_Z;
  int trash_resource_X;
  int doubleselection_trash_resource_Z;
  int doubleselection_trash_resource_X;
  int mutable purification_count;  // Used for locked_id in StationaryQubit. You unlock the qubit when purification is successful.
  bool X;
  bool Z;
  int num_purify;
  int action_index = 0;  // To track how many times this particular action has been invoked.
 public:
  DoubleSelectionDualAction(unsigned long RuleSet_id, int rule_index, int part, QNIC_type qt, int qi, int res, int tres_X, int tres_Z, int ds_X, int ds_Z) {
    partner = part;
    qnic_type = qt;
    qnic_id = qi;
    resource = res;
    trash_resource_X = tres_X;
    trash_resource_Z = tres_Z;
    doubleselection_trash_resource_Z = ds_Z;
    doubleselection_trash_resource_X = ds_X;
    rule_id = rule_index;
    ruleset_id = RuleSet_id;
    // action_index++;
  };
  DoubleSelectionDualAction(){

  };
  cPacket* run(cModule* re) override;
};

// https://arxiv.org/abs/0811.2639
class DoubleSelectionDualActionInv : public Action {
 protected:
  int partner; /**< Identifies entanglement partner. */
  QNIC_type qnic_type;
  int qnic_id;
  int resource; /**< Identifies qubit */
  int trash_resource_Z;
  int trash_resource_X;
  int doubleselection_trash_resource_Z;
  int doubleselection_trash_resource_X;
  int mutable purification_count;  // Used for locked_id in StationaryQubit. You unlock the qubit when purification is successful.
  bool X;
  bool Z;
  int num_purify;
  int action_index = 0;  // To track how many times this particular action has been invoked.
 public:
  DoubleSelectionDualActionInv(unsigned long RuleSet_id, int rule_index, int part, QNIC_type qt, int qi, int res, int tres_X, int tres_Z, int ds_X, int ds_Z) {
    partner = part;
    qnic_type = qt;
    qnic_id = qi;
    resource = res;
    trash_resource_X = tres_X;
    trash_resource_Z = tres_Z;
    doubleselection_trash_resource_Z = ds_Z;
    doubleselection_trash_resource_X = ds_X;
    rule_id = rule_index;
    ruleset_id = RuleSet_id;
    // action_index++;
  };
  DoubleSelectionDualActionInv(){

  };
  cPacket* run(cModule* re) override;
};

// https://arxiv.org/abs/0811.2639
class DoubleSelectionDualActionSecondInv : public Action {
 protected:
  int partner; /**< Identifies entanglement partner. */
  QNIC_type qnic_type;
  int qnic_id;
  int resource; /**< Identifies qubit */
  int trash_resource_Z;
  int trash_resource_X;
  int doubleselection_trash_resource_Z;
  int mutable purification_count;  // Used for locked_id in StationaryQubit. You unlock the qubit when purification is successful.
  bool X;
  bool Z;
  int num_purify;
  int action_index = 0;  // To track how many times this particular action has been invoked.
 public:
  DoubleSelectionDualActionSecondInv(unsigned long RuleSet_id, int rule_index, int part, QNIC_type qt, int qi, int res, int tres_X, int tres_Z, int ds_Z) {
    partner = part;
    qnic_type = qt;
    qnic_id = qi;
    resource = res;
    trash_resource_X = tres_X;
    trash_resource_Z = tres_Z;
    doubleselection_trash_resource_Z = ds_Z;
    rule_id = rule_index;
    ruleset_id = RuleSet_id;
    // action_index++;
  };
  DoubleSelectionDualActionSecondInv(){

  };
  cPacket* run(cModule* re) override;
};

// https://arxiv.org/abs/0811.2639
class DoubleSelectionDualActionSecond : public Action {
 protected:
  int partner; /**< Identifies entanglement partner. */
  QNIC_type qnic_type;
  int qnic_id;
  int resource; /**< Identifies qubit */
  int trash_resource_Z;
  int trash_resource_X;
  int doubleselection_trash_resource_X;
  int mutable purification_count;  // Used for locked_id in StationaryQubit. You unlock the qubit when purification is successful.
  bool X;
  bool Z;
  int num_purify;
  int action_index = 0;  // To track how many times this particular action has been invoked.
 public:
  DoubleSelectionDualActionSecond(unsigned long RuleSet_id, int rule_index, int part, QNIC_type qt, int qi, int res, int tres_X, int tres_Z, int ds_X) {
    partner = part;
    qnic_type = qt;
    qnic_id = qi;
    resource = res;
    trash_resource_X = tres_X;
    trash_resource_Z = tres_Z;
    doubleselection_trash_resource_X = ds_X;
    rule_id = rule_index;
    ruleset_id = RuleSet_id;
    // action_index++;
  };
  DoubleSelectionDualActionSecond(){

  };
  cPacket* run(cModule* re) override;
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
  int mutable max_count;
  simtime_t start;

 public:
  RandomMeasureAction(int part, QNIC_type qt, int qi, int res, int srcAddr, int max) {
    partner = part;
    dst = part;
    qnic_type = qt;
    qnic_id = qi;
    resource = res;
    src = srcAddr;
    current_count = 0;
    max_count = max;
    start = simTime();
  };
  // cPacket* run(qnicResources *resources) override;
  // cPacket* run(cModule *re, qnicResources *resources) override;
  cPacket* run(cModule* re) override;
};

}  // namespace rules
}  // namespace quisp

#endif  // QUISP_RULES_ACTION_H_

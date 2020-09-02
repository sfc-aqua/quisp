#include "example.h"
using namespace quisp::rules;
using namespace quisp::modules;

/**
 * In a three node topology (0)======(42)======(1),
 * assume we use the following purify&swap scheme:
 *
 * (0) --------- F>.95 --------- (42) --------- F>.93 --------- (1)
 *   \                                                         /
 *    `------------------------ F>.98  -----------------------’
 *
 * Let's build the rule set for the swapping node (42):
 *   - Swapping rule:
 *      if you have a pair with (0) of fidelity >.95,
 *      and a pair with (1) of fidelity >.93,
 *      then do entanglement swapping.
 *   - Purification rule with (0):
 *      if you have two pairs with (0) of fidelity >.5,
 *      then do purification
 *   - Purification rule with (1):
 *      if you have two pairs with (1) of fidelity >.5,
 *      then do purification
 *
 * Here, we assume that we already know:
 *   - Every qnic is of type 0
 *   - (42) gets to (0) by qnic id 30
 *   - (42) gets to (1) by qnic id 31
 */

/*
RuleSet* build_ruleset_42 () {
  // 1. Create a Rule Set for node 42
  RuleSet* ruleset_42 = new RuleSet(42,1);

  // 2. Create a rule for swapping
  Rule* rule_swapping_0_1 = new Rule();

  //   2.1. Create the conditions (on fidelity)
  Condition* condition_swapping_0_1 = new Condition();

  Clause* fidelity_42_0_95 = new FidelityClause(
      0, QNIC_E, 30, // partner, qnic_type, qnic_id
      0,             // qubit index
      0.95           // fidelity threshold
    );
  condition_swapping_0_1->addClause(fidelity_42_0_95);

  Clause* fidelity_42_1_93 = new FidelityClause(1,QNIC_E,31,0,0.93);
  condition_swapping_0_1->addClause(fidelity_42_1_93);

  rule_swapping_0_1->setCondition(condition_swapping_0_1);

  //   2.2 Create the swapping action
  quisp::rules::Action* action_swapping_0_1 = new SwappingAction(
      0, QNIC_E, 30, // left partner, qnic_type, qnic_id
      0,             //      qubit index
      1, QNIC_E, 31, // right partner, qnic_type, qnic_id
      0              //       qubit index
    );

  rule_swapping_0_1->setAction(action_swapping_0_1);

  ruleset_42->addRule(rule_swapping_0_1);

  // 3. Create rules for purification
  Rule* rule_purification_42_0 = new Rule();
  Clause* fidelity_42_0_50_0 = new FidelityClause(0, QNIC_E, 30, 0, 0.50);
  Clause* fidelity_42_0_50_1 = new FidelityClause(0, QNIC_E, 30, 1, 0.50);
  Condition* condition_purification_42_0 = new Condition();
  condition_purification_42_0->addClause(fidelity_42_0_50_0);
  condition_purification_42_0->addClause(fidelity_42_0_50_1);
  rule_purification_42_0->setCondition(condition_purification_42_0);
  quisp::rules::Action* action_purification_42_0 = new PurifyAction(0, QNIC_E, 30, 0, 1);
  rule_purification_42_0->setAction(action_purification_42_0);

  ruleset_42->addRule(rule_purification_42_0);

  Rule* rule_purification_42_1 = new Rule();
  Condition* condition_purification_42_1 = new Condition();
  Clause* fidelity_42_1_50_0 = new FidelityClause(1, QNIC_E, 31, 0, 0.50);
  Clause* fidelity_42_1_50_1 = new FidelityClause(1, QNIC_E, 31, 1, 0.50);
  condition_purification_42_1->addClause(fidelity_42_1_50_0);
  condition_purification_42_1->addClause(fidelity_42_1_50_1);
  rule_purification_42_1->setCondition(condition_purification_42_1);
  rule_purification_42_1->setCondition(condition_purification_42_1);
  quisp::rules::Action* action_purification_42_1 = new PurifyAction(1, QNIC_E, 31, 0, 1);
  rule_purification_42_1->setAction(action_purification_42_1);

  ruleset_42->addRule(rule_purification_42_1);

  return ruleset_42;
}*/

/*
void run_ruleset(RuleSet * rs) {
    for (auto rule = rs->rules.cbegin(), end = rs->rules.cend(); rule!=end; rule++) {
        if ((*rule)->condition->check()) { (*rule)->action->run(); break; }
    }
}*/

/*
int main (int argc, char * argv[]) {
    qnicResources * resources = NULL; // Fictional resources for compilation

    // Get RuleSet 42
    RuleSet * rs = build_ruleset_42();

    // Run RuleSet
    for (auto rule=rs->cbegin(), end=rs->cend(); rule!=end; rule++)
        (*rule)->checkrun(resources);

    // Run RuleSet in reverse order and break at first matching rule
    for (auto rule = rs->crbegin(), end = rs->crend(); rule != end; rule++) {
        if ((*rule)->checkrun(resources)) break;
    }

    return 0;
}*/

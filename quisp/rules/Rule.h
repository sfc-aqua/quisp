/** \file Rule.h
 *  \authors cldurand, takaakimatsuo
 *  \date 2018/06/25
 *
 *  \brief Rule
 */
#pragma once
#include <omnetpp.h>
#include <stdio.h>
#include <memory>
#include "Action.h"
#include "Condition.h"

namespace quisp::rules {

enum class PurType : int {
  SINGLE_X,  ///< Single purification for X error
  SSIGLE_Z,  ///< Single purification for Z error
  DOUBLE,  ///< Double purification both for X and Z errors
  DOUBLE_INV,  ///< Double inverse purification both for X and Z errors
  SSDP_X,  ///< Single Selection and Double Purification (DoubleSelectionAction) for X error
  SSDP_Z,  ///< Single Selection and Double Purification (DoubleSelectionAction) for Z error
  SSDP_X_INV,  ///< Single Selection and Double Purification Inverse (DoubleSelectionAction) for X error
  SSDP_Z_INV,  ///< Single Selection and Double Purification Inverse (DoubleSelectionAction) for Z error
  DSDA,  ///< Double Selection and Dual Action for both X and Z errors
  DSDA_INV,  ///< Inverse Double Selection and Dual Action for both X and Z errors
  DSDA_SECOND,  ///< Different type of Double Selection and Dual Action for both X and Z errors
  DSDA_SECOND_INV  ///< Different type of Inverse Double Selection and Dual Action for both X and Z errors
};

class BaseRule {
 public:
  unsigned long rule_id;
  unsigned long to;
  // std::vector<Condition> conditions;
  // std::vector<Action> actions;

  void addCondition();
  void addAction();
  void setNextRule(unsigned long next_ruleid);
};

// class PurificationRule : public BaseRule {
//  public:
//   PurificationRule(PurType purification_type, int num_purification);
//   PurType purtype;
//   int num_purification;
// };

// class SwappingRule : public BaseRule {
//  public:
//   SwappingRule();
// };

// class WaitRule : public BaseRule {
//  public:
//   WaitRule();
// };

}  // namespace quisp::rules

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

struct BaseRule {
  unsigned long rule_id;
  unsigned long to;
};

}  // namespace quisp::rules

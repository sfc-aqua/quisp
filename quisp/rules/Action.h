#pragma once

#include "actions/BaseAction.h"
#include "actions/DoublePurifyAction.h"
#include "actions/DoubleSelectionAction.h"
#include "actions/DoubleSelectionDualAction.h"
#include "actions/DoubleSelectionDualActionSecond.h"
#include "actions/PurifyAction.h"
#include "actions/RandomMeasureAction.h"
#include "actions/SimultaneousSwappingAction.h"
#include "actions/SwappingAction.h"
#include "actions/GeneralizedSwappingAction.h" //CM

namespace quisp {
namespace rules {

using actions::Action;
using actions::DoublePurifyAction;
using actions::DoublePurifyActionInv;
using actions::DoubleSelectionAction;
using actions::DoubleSelectionActionInv;
using actions::DoubleSelectionDualAction;
using actions::DoubleSelectionDualActionInv;
using actions::DoubleSelectionDualActionSecond;
using actions::DoubleSelectionDualActionSecondInv;
using actions::PurifyAction;
using actions::RandomMeasureAction;
using actions::SimultaneousSwappingAction;
using actions::SwappingAction;

}  // namespace rules
}  // namespace quisp

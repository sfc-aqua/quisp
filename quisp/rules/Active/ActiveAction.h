#pragma once

#include "actions/ActiveAction.h"
#include "actions/DoublePurifyAction.h"
#include "actions/DoubleSelectionAction.h"
#include "actions/DoubleSelectionDualAction.h"
#include "actions/DoubleSelectionDualActionSecond.h"
#include "actions/PurifyAction.h"
#include "actions/RandomMeasureAction.h"
#include "actions/SimultaneousSwappingAction.h"
#include "actions/SwappingAction.h"
#include "actions/WaitAction.h"

namespace quisp::rules::active {

using actions::ActiveAction;
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
using actions::WaitAction;

}  // namespace quisp::rules::active

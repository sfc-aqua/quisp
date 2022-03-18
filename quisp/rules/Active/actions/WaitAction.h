#pragma once

#include "BaseAction.h"

namespace quisp::rules::active::actions {
  class WaitAction:public ActiveAction{
    public:
      WaitAction(unsigned long ruleset_id, int rule_id): ActiveAction(ruleset_id, rule_id){}
      cPacket* run(cModule* re) override;
  };
} // namespace quisp::rules::active::actions

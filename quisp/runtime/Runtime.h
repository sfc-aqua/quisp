#pragma once

#include <rules/Active/ActiveRuleSet.h>
#include "rules/Active/ActiveAction.h"
#include "rules/Active/ActiveCondition.h"

namespace quisp::runtime {
class Runtime {
 public:
  Runtime() {}
  ~Runtime() {}
  void exec(rules::active::ActiveRuleSet *ruleset) {
    for (auto &rule : *ruleset) {
      std::cout << "log: " << rule->name << std::endl;
      auto &condition = rule->condition;
      auto &action = rule->action;
      if (!checkCondition(condition)) {
        break;
      }
      execAction(action);
    }
  }

  bool checkCondition(std::unique_ptr<rules::active::ActiveCondition> &condition) { return false; }

  void execAction(std::unique_ptr<rules::active::ActiveAction> &action) {}
};
namespace op {
// Resource Preparations
void assign() {}
void validate() {}
// Quantum Operations
void gate() {}
void measure() {}

// Messaging
void send() {}

// Post processing
void freeQubit() {}
void setNameToResource() {}
void update() {}

};  // namespace op
}  // namespace quisp::runtime

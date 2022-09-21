#include "Runtime.h"
#include <variant>

namespace quisp::runtime {

Runtime::Runtime() : error(nullptr), visitor(InstructionVisitor{this}) {}
Runtime::~Runtime() {}

void Runtime::exec(RuleSet ruleset) {
  this->error = nullptr;
  for (auto& rule : ruleset.rules) {
    eval(rule.condition);
    if (error != nullptr) {
      break;
    }
    eval(rule.action);
  }
}

void Runtime::eval(Program& program) {
  pc = 0;
  auto len = program.opcodes.size();
  for (auto& op : program.opcodes) {
    evalOperation(op);
    pc++;
  }
}

void Runtime::evalOperation(InstructionTypes instruction) { std::visit(visitor, instruction); }
const Register& Runtime::getReg(RegId regId) const { return registers[(int)regId]; }
unsigned long long Runtime::getRegVal(RegId regId) const { return registers[(int)regId].value; }
void Runtime::setRegVal(RegId regId, unsigned long long val) { registers[(int)regId].value = val; }

};  // namespace quisp::runtime

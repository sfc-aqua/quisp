#include "Runtime.h"

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
  for (auto& op : program.opcodes) {
    evalOperation(op);
  }
}

void Runtime::evalOperation(InstructionTypes instruction) { std::visit(visitor, instruction); }

void InstructionVisitor::operator()(Inst_NONE_int_ instruction) {}
void InstructionVisitor::operator()(Inst_DEBUG_int_ instruction) {
  auto [arg] = instruction.args;
  std::cout << "Debug(int): " << arg << std::endl;
}
void InstructionVisitor::operator()(Inst_DEBUG_float_ instruction) {
  auto [arg] = instruction.args;
  std::cout << "Debug(float): " << arg << std::endl;
}
void InstructionVisitor::operator()(Inst_DEBUG_String_ instruction) {
  auto [arg] = instruction.args;
  std::cout << "Debug(string): " << arg << std::endl;
}
void InstructionVisitor::operator()(Inst_ADD_int_int_ instruction) {
  auto [arg1, arg2] = instruction.args;
  std::cout << "Add(int,int): " << arg1 + arg2 << std::endl;
}
void InstructionVisitor::operator()(Inst_SUB_int_int_ instruction) {
  auto [arg1, arg2] = instruction.args;
  std::cout << "Sub(int,int): " << arg1 + arg2 << std::endl;
}
};  // namespace quisp::runtime

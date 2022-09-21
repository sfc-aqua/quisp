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
  pc = 0;
  auto len = program.opcodes.size();
  for (auto& op : program.opcodes) {
    evalOperation(op);
    pc++;
  }
}

void Runtime::evalOperation(InstructionTypes instruction) { std::visit(visitor, instruction); }

void InstructionVisitor::operator()(Inst_NOP_int_ instruction) {}
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
void InstructionVisitor::operator()(Inst_DEBUG_RegisterId_ instruction) {
  auto [reg1] = instruction.args;
  auto value = runtime->registers[reg1].value;
  std::cout << "Debug(Reg): " << value << std::endl;
}
void InstructionVisitor::operator()(Inst_ADD_RegisterId_int_int_ instruction) {
  auto [reg1, arg1, arg2] = instruction.args;
  auto val = arg1 + arg2;
  runtime->registers[reg1].value = val;
  std::cout << "Add(Reg,int,int): " << val << std::endl;
}
void InstructionVisitor::operator()(Inst_ADD_RegisterId_RegisterId_int_ instruction) {
  auto [reg1, reg2, arg2] = instruction.args;
  auto arg1 = runtime->registers[reg2].value;
  auto val = arg1 + arg2;
  runtime->registers[reg1].value = val;
  std::cout << "Add(Reg,Reg,int): " << val << std::endl;
}
void InstructionVisitor::operator()(Inst_ADD_RegisterId_RegisterId_RegisterId_ instruction) {
  auto [reg1, reg2, reg3] = instruction.args;
  auto arg1 = runtime->registers[reg2].value;
  auto arg2 = runtime->registers[reg3].value;
  auto val = arg1 + arg2;
  runtime->registers[reg1].value = val;
  std::cout << "Add(Reg,Reg,Reg): " << val << std::endl;
}
void InstructionVisitor::operator()(Inst_SUB_RegisterId_int_int_ instruction) {
  auto [reg1, arg1, arg2] = instruction.args;
  auto val = arg1 - arg2;
  runtime->registers[reg1].value = val;
  std::cout << "Sub(Reg,int,int): " << val << std::endl;
}
void InstructionVisitor::operator()(Inst_SUB_RegisterId_RegisterId_int_ instruction) {
  auto [reg1, reg2, arg2] = instruction.args;
  auto arg1 = runtime->registers[reg2].value;
  auto val = arg1 - arg2;
  runtime->registers[reg1].value = val;
  std::cout << "Sub(Reg,Reg,int): " << val << std::endl;
}
void InstructionVisitor::operator()(Inst_SUB_RegisterId_RegisterId_RegisterId_ instruction) {
  auto [reg1, reg2, reg3] = instruction.args;
  auto arg1 = runtime->registers[reg2].value;
  auto arg2 = runtime->registers[reg3].value;
  auto val = arg1 - arg2;
  runtime->registers[reg1].value = val;
  std::cout << "Sub(Reg,Reg,Reg): " << val << std::endl;
}
};  // namespace quisp::runtime

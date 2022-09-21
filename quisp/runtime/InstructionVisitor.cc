#include <iostream>

#include "InstructionVisitor.h"
#include "Runtime.h"

namespace quisp::runtime {

void InstructionVisitor::operator()(INSTR_NOP_int_ instruction) {}
void InstructionVisitor::operator()(INSTR_DEBUG_int_ instruction) {
  auto [arg] = instruction.args;
  std::cout << "Debug(int): " << arg << std::endl;
}
void InstructionVisitor::operator()(INSTR_DEBUG_float_ instruction) {
  auto [arg] = instruction.args;
  std::cout << "Debug(float): " << arg << std::endl;
}
void InstructionVisitor::operator()(INSTR_DEBUG_String_ instruction) {
  auto [arg] = instruction.args;
  std::cout << "Debug(string): " << arg << std::endl;
}
void InstructionVisitor::operator()(INSTR_DEBUG_RegId_ instruction) {
  auto [reg1] = instruction.args;
  auto value = runtime->getRegVal(reg1);
  std::cout << "Debug(Reg): " << value << std::endl;
}
void InstructionVisitor::operator()(INSTR_ADD_RegId_RegId_int_ instruction) {
  auto [regId1, regId2, arg2] = instruction.args;
  auto arg1 = (int)runtime->getRegVal(regId2);
  auto val = arg1 + arg2;
  runtime->setRegVal(regId1, val);
  std::cout << "Add(Reg,Reg,int): " << val << std::endl;
}
void InstructionVisitor::operator()(INSTR_ADD_RegId_RegId_RegId_ instruction) {
  auto [regId1, regId2, regId3] = instruction.args;
  auto arg1 = runtime->getRegVal(regId2);
  auto arg2 = runtime->getRegVal(regId3);
  auto val = arg1 + arg2;
  runtime->setRegVal(regId1, val);
  std::cout << "Add(Reg,Reg,Reg): " << val << std::endl;
}
void InstructionVisitor::operator()(INSTR_SUB_RegId_RegId_int_ instruction) {
  auto [regId1, regId2, arg2] = instruction.args;
  auto arg1 = (int)runtime->getRegVal(regId2);
  auto val = arg1 - arg2;
  runtime->setRegVal(regId1, val);
  std::cout << "Sub(Reg,Reg,int): " << val << std::endl;
}
void InstructionVisitor::operator()(INSTR_SUB_RegId_RegId_RegId_ instruction) {
  auto [regId1, regId2, regId3] = instruction.args;
  auto arg1 = runtime->getRegVal(regId2);
  auto arg2 = runtime->getRegVal(regId3);
  auto val = arg1 - arg2;
  runtime->setRegVal(regId1, val);
  std::cout << "Sub(Reg,Reg,Reg): " << val << std::endl;
}
void InstructionVisitor::operator()(INSTR_SET_RegId_int_ instruction) {
  auto [regId1, arg1] = instruction.args;
  runtime->setRegVal(regId1, arg1);
}
}  // namespace quisp::runtime

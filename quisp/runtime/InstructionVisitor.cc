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
  auto [reg_id1, reg_id2, arg2] = instruction.args;
  int arg1 = runtime->getRegVal(reg_id2);
  auto val = arg1 + arg2;
  runtime->setRegVal(reg_id1, val);
  std::cout << "Add(Reg,Reg,int): " << val << std::endl;
}
void InstructionVisitor::operator()(INSTR_ADD_RegId_RegId_RegId_ instruction) {
  auto [reg_id1, reg_id2, reg_id3] = instruction.args;
  auto arg1 = runtime->getRegVal(reg_id2);
  auto arg2 = runtime->getRegVal(reg_id3);
  auto val = arg1 + arg2;
  runtime->setRegVal(reg_id1, val);
  std::cout << "Add(Reg,Reg,Reg): " << val << std::endl;
}
void InstructionVisitor::operator()(INSTR_SUB_RegId_RegId_int_ instruction) {
  auto [reg_id1, reg_id2, arg2] = instruction.args;
  auto arg1 = (int)runtime->getRegVal(reg_id2);
  auto val = arg1 - arg2;
  runtime->setRegVal(reg_id1, val);
  std::cout << "Sub(Reg,Reg,int): " << val << std::endl;
}
void InstructionVisitor::operator()(INSTR_SUB_RegId_RegId_RegId_ instruction) {
  auto [reg_id1, reg_id2, reg_id3] = instruction.args;
  auto arg1 = runtime->getRegVal(reg_id2);
  auto arg2 = runtime->getRegVal(reg_id3);
  auto val = arg1 - arg2;
  runtime->setRegVal(reg_id1, val);
  std::cout << "Sub(Reg,Reg,Reg): " << val << std::endl;
}
void InstructionVisitor::operator()(INSTR_SET_RegId_int_ instruction) {
  auto [reg_id1, arg1] = instruction.args;
  runtime->setRegVal(reg_id1, arg1);
}

void InstructionVisitor::operator()(INSTR_GET_QUBIT_QubitId_QNodeAddr_ instruction) {
  auto [qubit_id, partner_addr] = instruction.args;
  int qubit_index = 0;
  auto qubit_ref = runtime->getQubitByPartnerAddr(partner_addr, qubit_index);
  runtime->setQubit(qubit_ref, qubit_id);
}
}  // namespace quisp::runtime

#include <iostream>
#include <stdexcept>

#include "InstructionVisitor.h"
#include "Runtime.h"

namespace quisp::runtime {

void InstructionVisitor::operator()(INSTR_NOP_int_ instruction) {}

void InstructionVisitor::operator()(INSTR_SEND_LINK_TOMOGRAPHY_RESULT_QNodeAddr_RegId_MemoryKey_int_ instruction) {
  auto [partner_addr, counter_reg_id, outcome_key, max_count] = instruction.args;
  auto count = runtime->getRegVal(counter_reg_id);
  auto outcome = runtime->loadVal(outcome_key).outcome;
  runtime->rule_engine->sendLinkTomographyResult(partner_addr, count, outcome, max_count);
}

void InstructionVisitor::operator()(INSTR_MEASURE_RANDOM_MemoryKey_QubitId_ instruction) {
  auto [memory_key, qubit_id] = instruction.args;
  runtime->measureQubit(qubit_id, memory_key, Basis::RANDOM);
}
void InstructionVisitor::operator()(INSTR_MEASURE_MemoryKey_QubitId_Basis_ instruction) {
  auto [memory_key, qubit_id, basis] = instruction.args;
  runtime->measureQubit(qubit_id, memory_key, basis);
}

void InstructionVisitor::operator()(INSTR_FREE_QUBIT_QubitId_ instruction) {
  auto [qubit_id] = instruction.args;
  runtime->freeQubit(qubit_id);
}

void InstructionVisitor::operator()(INSTR_LOAD_RegId_MemoryKey_ instruction) {
  auto [reg_id, memory_key] = instruction.args;
  runtime->loadVal(memory_key, reg_id);
}

void InstructionVisitor::operator()(INSTR_STORE_MemoryKey_RegId_ instruction) {
  auto [memory_key, reg_id] = instruction.args;
  runtime->storeVal(memory_key, MemoryValue(runtime->getRegVal(reg_id)));
}

void InstructionVisitor::operator()(INSTR_STORE_MemoryKey_int_ instruction) {
  auto [memory_key, value] = instruction.args;
  runtime->storeVal(memory_key, MemoryValue(value));
}

void InstructionVisitor::operator()(INSTR_BNERR_Label_ instruction) {
  auto [label] = instruction.args;
  if (runtime->error == nullptr) {
    runtime->jumpTo(label);
  }
}

void InstructionVisitor::operator()(INSTR_BEQ_Label_RegId_RegId_ instruction) {
  auto [label, reg_id1, reg_id2] = instruction.args;
  if (runtime->getRegVal(reg_id1) == runtime->getRegVal(reg_id2)) runtime->jumpTo(label);
}

void InstructionVisitor::operator()(INSTR_BEQ_Label_RegId_int_ instruction) {
  auto [label, reg_id, value] = instruction.args;
  if ((int)runtime->getRegVal(reg_id) == value) runtime->jumpTo(label);
}

void InstructionVisitor::operator()(INSTR_BEZ_Label_RegId_ instruction) {
  auto [label, reg_id] = instruction.args;
  if (runtime->getRegVal(reg_id) == 0) runtime->jumpTo(label);
}

void InstructionVisitor::operator()(INSTR_BNZ_Label_RegId_ instruction) {
  auto [label, reg_id] = instruction.args;
  if (runtime->getRegVal(reg_id) != 0) runtime->jumpTo(label);
}

void InstructionVisitor::operator()(INSTR_JMP_Label_ instruction) {
  auto [label] = instruction.args;
  runtime->jumpTo(label);
}

void InstructionVisitor::operator()(INSTR_INC_RegId_ instruction) {
  auto [reg_id] = instruction.args;
  auto val = runtime->getRegVal(reg_id);
  runtime->setRegVal(reg_id, val + 1);
}

void InstructionVisitor::operator()(INSTR_ERROR_String_ instruction) {
  auto [message] = instruction.args;
  runtime->setError(message);
}

void InstructionVisitor::operator()(INSTR_DEBUG_RUNTIME_STATE_None_ _instruction) { runtime->debugRuntimeState(); }
void InstructionVisitor::operator()(INSTR_DEBUG_QubitId_ instruction) {
  auto [qubit_id] = instruction.args;
  auto qubit_ref = runtime->getQubitByQubitId(qubit_id);
  std::cout << "Debug(QubitId:" << qubit_id << "): "
            << "\n  qnic type: " << qubit_ref->getQNicType() << "\n  qnic index: " << qubit_ref->getQNicIndex() << "\n  qubit index: " << qubit_ref->getQubitIndex() << std::endl;
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
}

void InstructionVisitor::operator()(INSTR_ADD_RegId_RegId_RegId_ instruction) {
  auto [reg_id1, reg_id2, reg_id3] = instruction.args;
  auto arg1 = runtime->getRegVal(reg_id2);
  auto arg2 = runtime->getRegVal(reg_id3);
  auto val = arg1 + arg2;
  runtime->setRegVal(reg_id1, val);
}

void InstructionVisitor::operator()(INSTR_SUB_RegId_RegId_int_ instruction) {
  auto [reg_id1, reg_id2, arg2] = instruction.args;
  auto arg1 = (int)runtime->getRegVal(reg_id2);
  auto val = arg1 - arg2;
  runtime->setRegVal(reg_id1, val);
}

void InstructionVisitor::operator()(INSTR_SUB_RegId_RegId_RegId_ instruction) {
  auto [reg_id1, reg_id2, reg_id3] = instruction.args;
  auto arg1 = runtime->getRegVal(reg_id2);
  auto arg2 = runtime->getRegVal(reg_id3);
  auto val = arg1 - arg2;
  runtime->setRegVal(reg_id1, val);
}

void InstructionVisitor::operator()(INSTR_SET_RegId_int_ instruction) {
  auto [reg_id1, arg1] = instruction.args;
  runtime->setRegVal(reg_id1, arg1);
}

void InstructionVisitor::operator()(INSTR_GET_QUBIT_QubitId_QNodeAddr_int_ instruction) {
  auto [qubit_id, partner_addr, qubit_resource_index] = instruction.args;
  auto *qubit_ref = runtime->getQubitByPartnerAddr(partner_addr, qubit_resource_index);
  if (qubit_ref == nullptr) {
    runtime->setError("Qubit not found");
  }
  runtime->setQubit(qubit_ref, qubit_id);
}
}  // namespace quisp::runtime

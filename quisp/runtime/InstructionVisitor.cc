#include <iostream>
#include <stdexcept>

#include "InstructionVisitor.h"
#include "Runtime.h"

namespace quisp::runtime {

InstructionVisitor::InstructionVisitor(const InstructionVisitor& visitor) { runtime = visitor.runtime; }

InstructionVisitor& InstructionVisitor::operator=(const InstructionVisitor& visitor) {
  runtime = visitor.runtime;
  return *this;
}

void InstructionVisitor::operator()(const INSTR_NOP_None_& instruction) {}
void InstructionVisitor::operator()(const INSTR_RET_ReturnCode_& instruction) {
  auto [return_code] = instruction.args;
  runtime->should_exit = true;
  runtime->return_code = return_code;
}
void InstructionVisitor::operator()(const INSTR_BRANCH_IF_LOCKED_Label_RegId_& instruction) {
  auto [label, qubit_id_reg] = instruction.args;
  auto qubit_id = runtime->getRegVal(qubit_id_reg);
  auto* qubit = runtime->getQubitByQubitId(qubit_id);
  if (runtime->isQubitLocked(qubit)) {
    runtime->jumpTo(label);
  }
}
void InstructionVisitor::operator()(const INSTR_SEND_LINK_TOMOGRAPHY_RESULT_QNodeAddr_RegId_MemoryKey_int_Time_& instruction) {
  auto [partner_addr, counter_reg_id, outcome_key, max_count, start_time] = instruction.args;
  auto count = runtime->getRegVal(counter_reg_id);
  auto outcome = runtime->loadVal(outcome_key).outcome();
  auto& rs = runtime->ruleset;
  auto& rule = rs.rules.at(runtime->rule_id);
  auto action_index = 0;
  runtime->callback->sendLinkTomographyResult(rs.id, rule, action_index, partner_addr, count, outcome, max_count, start_time);
}

void InstructionVisitor::operator()(const INSTR_SEND_PURIFICATION_RESULT_QNodeAddr_RegId_RegId_& instruction) {
  auto [partner_addr, result_reg_id, action_index_reg_id] = instruction.args;
  bool result = runtime->getRegVal(result_reg_id);
  int action_index = runtime->getRegVal(action_index_reg_id);
  auto& rs = runtime->ruleset;
  auto& rule = rs.rules.at(runtime->rule_id);
  runtime->callback->sendPurificationResult(rs.id, rule, action_index, partner_addr, result);
}

void InstructionVisitor::operator()(const INSTR_SEND_SWAPPING_RESULT_QNodeAddr_RegId_QNodeAddr_RegId_& instruction) {
  auto [left_partner, left_op_id, right_partner, right_op_id] = instruction.args;
  auto& rs = runtime->ruleset;
  auto& rule = rs.rules.at(runtime->rule_id);
  runtime->callback->sendSwappingResults(rs.id, rule, left_partner, runtime->getRegVal(left_op_id), right_partner, runtime->getRegVal(right_op_id));
}

void InstructionVisitor::operator()(const INSTR_MEASURE_RANDOM_MemoryKey_QubitId_& instruction) {
  auto [memory_key, qubit_id] = instruction.args;
  runtime->measureQubit(qubit_id, memory_key, Basis::RANDOM);
}

void InstructionVisitor::operator()(const INSTR_MEASURE_MemoryKey_QubitId_Basis_& instruction) {
  auto [memory_key, qubit_id, basis] = instruction.args;
  runtime->measureQubit(qubit_id, memory_key, basis);
}

void InstructionVisitor::operator()(const INSTR_GATE_X_QubitId_& instruction) {
  auto [qubit_id] = instruction.args;
  runtime->gateX(qubit_id);
}

void InstructionVisitor::operator()(const INSTR_GATE_Z_QubitId_& instruction) {
  auto [qubit_id] = instruction.args;
  runtime->gateZ(qubit_id);
}

void InstructionVisitor::operator()(const INSTR_GATE_CNOT_QubitId_QubitId_& instruction) {
  auto [control_qubit_id, target_qubit_id] = instruction.args;
  runtime->gateCNOT(control_qubit_id, target_qubit_id);
}

void InstructionVisitor::operator()(const INSTR_PURIFY_X_RegId_QubitId_QubitId_& instruction) {
  auto [result_reg_id, qubit_id, trash_qubit_id] = instruction.args;
  runtime->purifyX(qubit_id, trash_qubit_id);
}

void InstructionVisitor::operator()(const INSTR_FREE_QUBIT_QubitId_& instruction) {
  auto [qubit_id] = instruction.args;
  runtime->freeQubit(qubit_id);
}

void InstructionVisitor::operator()(const INSTR_LOCK_QUBIT_QubitId_RegId_& instruction) {
  auto [qubit_id, reg_id] = instruction.args;
  // runtime->freeQubit(qubit_id);
  auto& rt = *runtime;
  int action_index = rt.getRegVal(reg_id);
  auto* qubit_rec = rt.getQubitByQubitId(qubit_id);
  rt.callback->lockQubit(qubit_rec, rt.ruleset.id, rt.rule_id, action_index);
}

void InstructionVisitor::operator()(const INSTR_LOAD_RegId_MemoryKey_& instruction) {
  auto [reg_id, memory_key] = instruction.args;
  runtime->loadVal(memory_key, reg_id);
}

void InstructionVisitor::operator()(const INSTR_LOAD_LEFT_OP_RegId_MemoryKey_& instruction) {
  auto [reg_id, outcome_key] = instruction.args;
  auto val = runtime->loadVal(outcome_key);
  auto outcome = val.outcome();
  // FIX: remove this assert and adapt to another basis and operation type
  // current implementation is sticked to the original implementation
  assert(outcome.basis == 'X');
  // operation_type: 0 = I, 1 = X, 2 = Z
  runtime->setRegVal(reg_id, outcome.outcome_is_plus ? 0 : 2);
}

void InstructionVisitor::operator()(const INSTR_LOAD_RIGHT_OP_RegId_MemoryKey_& instruction) {
  auto [reg_id, outcome_key] = instruction.args;
  auto val = runtime->loadVal(outcome_key);
  auto outcome = val.outcome();
  assert(outcome.basis == 'Z');
  // operation_type: 0 = I, 1 = X, 2 = Z
  runtime->setRegVal(reg_id, outcome.outcome_is_plus ? 0 : 1);
}

void InstructionVisitor::operator()(const INSTR_STORE_MemoryKey_RegId_& instruction) {
  auto [memory_key, reg_id] = instruction.args;
  runtime->storeVal(memory_key, MemoryValue(runtime->getRegVal(reg_id)));
}

void InstructionVisitor::operator()(const INSTR_STORE_MemoryKey_int_& instruction) {
  auto [memory_key, value] = instruction.args;
  runtime->storeVal(memory_key, MemoryValue(value));
}

void InstructionVisitor::operator()(const INSTR_BNERR_Label_& instruction) {
  auto [label] = instruction.args;
  if (runtime->error == nullptr) {
    runtime->jumpTo(label);
  }
}

void InstructionVisitor::operator()(const INSTR_BEQ_Label_RegId_RegId_& instruction) {
  auto [label, reg_id1, reg_id2] = instruction.args;
  if (runtime->getRegVal(reg_id1) == runtime->getRegVal(reg_id2)) runtime->jumpTo(label);
}

void InstructionVisitor::operator()(const INSTR_BEQ_Label_RegId_int_& instruction) {
  auto [label, reg_id, value] = instruction.args;
  if ((int)runtime->getRegVal(reg_id) == value) runtime->jumpTo(label);
}

void InstructionVisitor::operator()(const INSTR_BEZ_Label_RegId_& instruction) {
  auto [label, reg_id] = instruction.args;
  if (runtime->getRegVal(reg_id) == 0) runtime->jumpTo(label);
}

void InstructionVisitor::operator()(const INSTR_BNZ_Label_RegId_& instruction) {
  auto [label, reg_id] = instruction.args;
  if (runtime->getRegVal(reg_id) != 0) runtime->jumpTo(label);
}
void InstructionVisitor::operator()(const INSTR_BLT_Label_RegId_int_& instruction) {
  auto [label, reg_id, val] = instruction.args;
  if (runtime->getRegVal(reg_id) < val) runtime->jumpTo(label);
}

void InstructionVisitor::operator()(const INSTR_JMP_Label_& instruction) {
  auto [label] = instruction.args;
  runtime->jumpTo(label);
}

void InstructionVisitor::operator()(const INSTR_INC_RegId_& instruction) {
  auto [reg_id] = instruction.args;
  auto val = runtime->getRegVal(reg_id);
  runtime->setRegVal(reg_id, val + 1);
}

void InstructionVisitor::operator()(const INSTR_ERROR_String_& instruction) {
  auto [message] = instruction.args;
  runtime->setError(message);
  runtime->error->caught = true;
  runtime->should_exit = true;
}

void InstructionVisitor::operator()(const INSTR_DEBUG_RUNTIME_STATE_None_& _instruction) { runtime->debugRuntimeState(); }
void InstructionVisitor::operator()(const INSTR_DEBUG_QubitId_& instruction) {
  auto [qubit_id] = instruction.args;
  auto qubit_ref = runtime->getQubitByQubitId(qubit_id);
  std::cout << "Debug(QubitId:" << qubit_id << "): "
            << "\n  qnic type: " << qubit_ref->getQNicType() << "\n  qnic index: " << qubit_ref->getQNicIndex() << "\n  qubit index: " << qubit_ref->getQubitIndex() << std::endl;
}

void InstructionVisitor::operator()(const INSTR_DEBUG_String_& instruction) {
  auto [arg] = instruction.args;
  std::cout << "Debug(string): " << arg << std::endl;
}

void InstructionVisitor::operator()(const INSTR_DEBUG_RegId_& instruction) {
  auto [reg1] = instruction.args;
  auto value = runtime->getRegVal(reg1);
  std::cout << "Debug(Reg): " << value << std::endl;
}

void InstructionVisitor::operator()(const INSTR_ADD_RegId_RegId_int_& instruction) {
  auto [reg_id1, reg_id2, arg2] = instruction.args;
  int arg1 = runtime->getRegVal(reg_id2);
  auto val = arg1 + arg2;
  runtime->setRegVal(reg_id1, val);
}

void InstructionVisitor::operator()(const INSTR_ADD_RegId_RegId_RegId_& instruction) {
  auto [reg_id1, reg_id2, reg_id3] = instruction.args;
  auto arg1 = runtime->getRegVal(reg_id2);
  auto arg2 = runtime->getRegVal(reg_id3);
  auto val = arg1 + arg2;
  runtime->setRegVal(reg_id1, val);
}

void InstructionVisitor::operator()(const INSTR_SUB_RegId_RegId_int_& instruction) {
  auto [reg_id1, reg_id2, arg2] = instruction.args;
  auto arg1 = (int)runtime->getRegVal(reg_id2);
  auto val = arg1 - arg2;
  runtime->setRegVal(reg_id1, val);
}

void InstructionVisitor::operator()(const INSTR_SUB_RegId_RegId_RegId_& instruction) {
  auto [reg_id1, reg_id2, reg_id3] = instruction.args;
  auto arg1 = runtime->getRegVal(reg_id2);
  auto arg2 = runtime->getRegVal(reg_id3);
  auto val = arg1 - arg2;
  runtime->setRegVal(reg_id1, val);
}

void InstructionVisitor::operator()(const INSTR_SET_RegId_int_& instruction) {
  auto [reg_id1, arg1] = instruction.args;
  runtime->setRegVal(reg_id1, arg1);
}

void InstructionVisitor::operator()(const INSTR_GET_QUBIT_QubitId_QNodeAddr_int_& instruction) {
  auto [qubit_id, partner_addr, qubit_resource_index] = instruction.args;
  auto* qubit_ref = runtime->getQubitByPartnerAddr(partner_addr, qubit_resource_index);
  if (qubit_ref == nullptr) {
    runtime->setError("Qubit not found");
    return;
  }
  runtime->setQubit(qubit_ref, qubit_id);
}

void InstructionVisitor::operator()(const INSTR_GET_QUBIT_RegId_QNodeAddr_RegId_& instruction) {
  auto [qubit_id_reg, partner_addr, qubit_resource_index_reg] = instruction.args;
  int qubit_resource_index = runtime->getRegVal(qubit_resource_index_reg);
  int qubit_id = runtime->getRegVal(qubit_id_reg);
  auto* qubit_ref = runtime->getQubitByPartnerAddr(partner_addr, qubit_resource_index);
  if (qubit_ref == nullptr) {
    runtime->setError("Qubit not found");
    return;
  }
  runtime->setQubit(qubit_ref, qubit_id);
}

void InstructionVisitor::operator()(const INSTR_HACK_SWAPPING_PARTNERS_QubitId_QubitId_& instruction) {
  auto [qubit_id1, qubit_id2] = instruction.args;
  runtime->callback->hackSwappingPartners(runtime->getQubitByQubitId(qubit_id1), runtime->getQubitByQubitId(qubit_id2));
}

void InstructionVisitor::operator()(const INSTR_HACK_BREAK_ENTANGLEMENT_QubitId_& instruction) {
  auto [qubit_id] = instruction.args;
  runtime->callback->hackBreakEntanglement(runtime->getQubitByQubitId(qubit_id));
}
}  // namespace quisp::runtime

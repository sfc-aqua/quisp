#include <iostream>
#include <stdexcept>

#include "InstructionVisitor.h"
#include "Runtime.h"
#include "runtime/types.h"

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

void InstructionVisitor::operator()(const INSTR_SEND_PURIFICATION_RESULT_QNodeAddr_RegId_RegId_PurType_& instruction) {
  auto [partner_addr, result_reg, sequence_number_reg, protocol] = instruction.args;
  int measurement_result = runtime->getRegVal(result_reg);  // can only handle up to 32 qubits
  int sequence_number = runtime->getRegVal(sequence_number_reg);
  auto ruleset_id = runtime->ruleset.id;
  // TODO: get shared_rule_tag from action not from rules
  runtime->callback->sendPurificationResult(ruleset_id, partner_addr, runtime->send_tag, sequence_number, measurement_result, protocol);
}

void InstructionVisitor::operator()(const INSTR_SEND_SWAPPING_RESULT_QNodeAddr_RegId_QNodeAddr_RegId_& instruction) {
  // TODO: complete this
  auto [left_partner, left_op_id, right_partner, right_op_id] = instruction.args;
  auto& rs = runtime->ruleset;
  auto& rule = rs.rules.at(runtime->rule_id);
}

void InstructionVisitor::operator()(const INSTR_MEASURE_RANDOM_MemoryKey_QubitId_& instruction) {
  auto [memory_key, qubit_id] = instruction.args;
  runtime->measureQubit(qubit_id, memory_key, Basis::RANDOM);
}

void InstructionVisitor::operator()(const INSTR_MEASURE_MemoryKey_QubitId_Basis_& instruction) {
  auto [memory_key, qubit_id, basis] = instruction.args;
  runtime->measureQubit(qubit_id, memory_key, basis);
}

void InstructionVisitor::operator()(const INSTR_MEASURE_RegId_QubitId_Basis_& instruction) {
  auto [reg, qubit_id, basis] = instruction.args;
  runtime->measureQubit(qubit_id, reg, basis);
}

void InstructionVisitor::operator()(const INSTR_GATE_X_QubitId_& instruction) {
  auto [qubit_id] = instruction.args;
  runtime->gateX(qubit_id);
}

void InstructionVisitor::operator()(const INSTR_GATE_Z_QubitId_& instruction) {
  auto [qubit_id] = instruction.args;
  runtime->gateZ(qubit_id);
}

void InstructionVisitor::operator()(const INSTR_GATE_Y_QubitId_& instruction) {
  auto [qubit_id] = instruction.args;
  runtime->gateY(qubit_id);
}

void InstructionVisitor::operator()(const INSTR_GATE_CNOT_QubitId_QubitId_& instruction) {
  auto [control_qubit_id, target_qubit_id] = instruction.args;
  runtime->gateCNOT(control_qubit_id, target_qubit_id);
}

void InstructionVisitor::operator()(const INSTR_PURIFY_X_RegId_QubitId_QubitId_& instruction) {
  auto [result_reg_id, qubit_id, trash_qubit_id] = instruction.args;
  runtime->purifyX(result_reg_id, qubit_id, trash_qubit_id);
}

void InstructionVisitor::operator()(const INSTR_PURIFY_Z_RegId_QubitId_QubitId_& instruction) {
  auto [result_reg_id, qubit_id, trash_qubit_id] = instruction.args;
  runtime->purifyZ(result_reg_id, qubit_id, trash_qubit_id);
}

void InstructionVisitor::operator()(const INSTR_PURIFY_Y_RegId_QubitId_QubitId_& instruction) {
  auto [result_reg_id, qubit_id, trash_qubit_id] = instruction.args;
  runtime->purifyY(result_reg_id, qubit_id, trash_qubit_id);
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

void InstructionVisitor::operator()(const INSTR_BRANCH_IF_QUBIT_FOUND_Label_& instruction) {
  auto [label] = instruction.args;
  if (runtime->qubit_found) {
    runtime->jumpTo(label);
  }
}

void InstructionVisitor::operator()(const INSTR_BRANCH_IF_MESSAGE_FOUND_Label_& instruction) {
  auto [label] = instruction.args;
  if (runtime->message_found) {
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
  std::cerr << "RuntimeError : " << message << std::endl;
  runtime->debugRuntimeState();
  runtime->should_exit = true;
  runtime->return_code = ReturnCode::ERROR;
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

// bitwise operation with output reg
void InstructionVisitor::operator()(const INSTR_BITWISE_AND_RegId_RegId_RegId_& instruction) {
  auto [result_reg, reg_1, reg_2] = instruction.args;
  auto arg1 = (int)runtime->getRegVal(reg_1);
  auto arg2 = (int)runtime->getRegVal(reg_2);
  auto val = arg1 & arg2;
  runtime->setRegVal(result_reg, val);
}
void InstructionVisitor::operator()(const INSTR_BITWISE_AND_RegId_RegId_int_& instruction) {
  auto [result_reg, reg_1, arg2] = instruction.args;
  auto arg1 = (int)runtime->getRegVal(reg_1);
  auto val = arg1 & arg2;
  runtime->setRegVal(result_reg, val);
}
void InstructionVisitor::operator()(const INSTR_BITWISE_OR_RegId_RegId_RegId_& instruction) {
  auto [result_reg, reg_1, reg_2] = instruction.args;
  auto arg1 = (int)runtime->getRegVal(reg_1);
  auto arg2 = (int)runtime->getRegVal(reg_2);
  auto val = arg1 | arg2;
  runtime->setRegVal(result_reg, val);
}
void InstructionVisitor::operator()(const INSTR_BITWISE_OR_RegId_RegId_int_& instruction) {
  auto [result_reg, reg_1, arg2] = instruction.args;
  auto arg1 = (int)runtime->getRegVal(reg_1);
  auto val = arg1 | arg2;
  runtime->setRegVal(result_reg, val);
}
void InstructionVisitor::operator()(const INSTR_BITWISE_XOR_RegId_RegId_RegId_& instruction) {
  auto [result_reg, reg_1, reg_2] = instruction.args;
  auto arg1 = (int)runtime->getRegVal(reg_1);
  auto arg2 = (int)runtime->getRegVal(reg_2);
  auto val = arg1 ^ arg2;
  runtime->setRegVal(result_reg, val);
}
void InstructionVisitor::operator()(const INSTR_BITWISE_XOR_RegId_RegId_int_& instruction) {
  auto [result_reg, reg_1, arg2] = instruction.args;
  auto arg1 = (int)runtime->getRegVal(reg_1);
  auto val = arg1 ^ arg2;
  runtime->setRegVal(result_reg, val);
}

// bitwise operation in-place
void InstructionVisitor::operator()(const INSTR_BITWISE_AND_RegId_RegId_& instruction) {
  auto [reg_1, reg_2] = instruction.args;
  auto arg1 = (int)runtime->getRegVal(reg_1);
  auto arg2 = (int)runtime->getRegVal(reg_2);
  auto val = arg1 & arg2;
  runtime->setRegVal(reg_1, val);
}
void InstructionVisitor::operator()(const INSTR_BITWISE_AND_RegId_int_& instruction) {
  auto [reg_1, arg2] = instruction.args;
  auto arg1 = (int)runtime->getRegVal(reg_1);
  auto val = arg1 & arg2;
  runtime->setRegVal(reg_1, val);
}
void InstructionVisitor::operator()(const INSTR_BITWISE_OR_RegId_RegId_& instruction) {
  auto [reg_1, reg_2] = instruction.args;
  auto arg1 = (int)runtime->getRegVal(reg_1);
  auto arg2 = (int)runtime->getRegVal(reg_2);
  auto val = arg1 | arg2;
  runtime->setRegVal(reg_1, val);
}
void InstructionVisitor::operator()(const INSTR_BITWISE_OR_RegId_int_& instruction) {
  auto [reg_1, arg2] = instruction.args;
  auto arg1 = (int)runtime->getRegVal(reg_1);
  auto val = arg1 | arg2;
  runtime->setRegVal(reg_1, val);
}
void InstructionVisitor::operator()(const INSTR_BITWISE_XOR_RegId_RegId_& instruction) {
  auto [reg_1, reg_2] = instruction.args;
  auto arg1 = (int)runtime->getRegVal(reg_1);
  auto arg2 = (int)runtime->getRegVal(reg_2);
  auto val = arg1 ^ arg2;
  runtime->setRegVal(reg_1, val);
}

void InstructionVisitor::operator()(const INSTR_BITWISE_XOR_RegId_int_& instruction) {
  auto [reg_1, arg2] = instruction.args;
  auto arg1 = (int)runtime->getRegVal(reg_1);
  auto val = arg1 ^ arg2;
  runtime->setRegVal(reg_1, val);
}

void InstructionVisitor::operator()(const INSTR_SET_RegId_int_& instruction) {
  auto [reg_id1, arg1] = instruction.args;
  runtime->setRegVal(reg_id1, arg1);
}

void InstructionVisitor::operator()(const INSTR_GET_QUBIT_QubitId_QNodeAddr_RegId_& instruction) {
  auto [qubit_id, partner_addr, qubit_resource_index_reg_id] = instruction.args;
  int qubit_resource_index = runtime->getRegVal(qubit_resource_index_reg_id);
  auto* qubit_ref = runtime->getQubitByPartnerAddr(partner_addr, qubit_resource_index);
  if (qubit_ref == nullptr) {
    runtime->qubit_found = false;
    return;
  }
  runtime->qubit_found = true;
  runtime->setQubit(qubit_ref, qubit_id);
}

void InstructionVisitor::operator()(const INSTR_GET_QUBIT_QubitId_QNodeAddr_int_& instruction) {
  auto [qubit_id, partner_addr, qubit_resource_index] = instruction.args;
  auto* qubit_ref = runtime->getQubitByPartnerAddr(partner_addr, qubit_resource_index);
  if (qubit_ref == nullptr) {
    runtime->qubit_found = false;
    return;
  }
  runtime->qubit_found = true;
  runtime->setQubit(qubit_ref, qubit_id);
}

void InstructionVisitor::operator()(const INSTR_GET_QUBIT_RegId_QNodeAddr_RegId_& instruction) {
  auto [qubit_id_reg, partner_addr, qubit_resource_index_reg] = instruction.args;
  int qubit_resource_index = runtime->getRegVal(qubit_resource_index_reg);
  int qubit_id = runtime->getRegVal(qubit_id_reg);
  auto* qubit_ref = runtime->getQubitByPartnerAddr(partner_addr, qubit_resource_index);
  if (qubit_ref == nullptr) {
    runtime->qubit_found = false;
    return;
  }
  runtime->qubit_found = true;
  runtime->setQubit(qubit_ref, qubit_id);
}

void InstructionVisitor::operator()(const INSTR_GET_QUBIT_BY_SEQ_NO_RegId_QNodeAddr_RegId_& instruction) {
  auto [qubit_id_reg, partner_addr, sequence_number_reg] = instruction.args;
  auto qubit_id = runtime->getRegVal(qubit_id_reg);
  auto sequence_number = runtime->getRegVal(sequence_number_reg);
  auto* qubit_ref = runtime->getQubitBySequenceNumber(partner_addr, runtime->rule_id, sequence_number);
  if (qubit_ref == nullptr) {
    runtime->qubit_found = false;
    return;
  }
  runtime->qubit_found = true;
  runtime->setQubit(qubit_ref, qubit_id);
}

void InstructionVisitor::operator()(const INSTR_GET_QUBIT_BY_SEQ_NO_QubitId_QNodeAddr_RegId_& instruction) {
  auto [qubit_id, partner_addr, sequence_number_reg] = instruction.args;
  auto sequence_number = runtime->getRegVal(sequence_number_reg);
  auto* qubit_ref = runtime->getQubitBySequenceNumber(partner_addr, runtime->rule_id, sequence_number);
  if (qubit_ref == nullptr) {
    runtime->qubit_found = false;
    return;
  }
  runtime->qubit_found = true;
  runtime->setQubit(qubit_ref, qubit_id);
}

void InstructionVisitor::operator()(const INSTR_PROMOTE_QubitId_& instruction) {
  auto [qubit_id] = instruction.args;
  auto* qubit_rec = runtime->getQubitByQubitId(qubit_id);
  runtime->promoteQubit(qubit_rec);
}

void InstructionVisitor::operator()(const INSTR_PROMOTE_QubitId_RegId_& instruction) {
  auto [qubit_id, new_partner_addr_reg] = instruction.args;
  auto* qubit_rec = runtime->getQubitByQubitId(qubit_id);
  auto new_partner_addr = QNodeAddr(runtime->getRegVal(new_partner_addr_reg));
  runtime->promoteQubitWithNewPartner(qubit_rec, new_partner_addr);
}

void InstructionVisitor::operator()(const INSTR_GET_MESSAGE_SEQ_RegId_RegId_& instruction) {
  auto [message_index_reg_id, sequence_number_reg_id] = instruction.args;
  auto message_index = runtime->getRegVal(message_index_reg_id);
  auto& rule_messages = runtime->messages[{runtime->rule_id}];
  if (message_index >= rule_messages.size()) {
    runtime->message_found = false;
    return;
  }
  runtime->message_found = true;
  auto sequence_number = rule_messages[message_index][0];
  runtime->setRegVal(sequence_number_reg_id, sequence_number);
}

void InstructionVisitor::operator()(const INSTR_COUNT_MESSAGE_RegId_RegId_& instruction) {
  auto [sequence_number_reg_id, return_reg_id] = instruction.args;
  auto sequence_number = runtime->getRegVal(sequence_number_reg_id);
  auto& rule_messages = runtime->messages[{runtime->rule_id}];
  int count = 0;
  for (auto& message : rule_messages) {
    if (message[0] == sequence_number) {
      count++;
    }
  }
  runtime->setRegVal(return_reg_id, count);
}

void InstructionVisitor::operator()(const INSTR_GET_MESSAGE_RegId_int_RegId_& instruction) {
  auto [sequence_number_reg_id, message_index, content_reg_id_1] = instruction.args;
  auto sequence_number = runtime->getRegVal(sequence_number_reg_id);
  auto& rule_messages = runtime->messages[{runtime->rule_id}];

  int i = 0;
  bool message_found = false;
  for (auto& message : rule_messages) {
    if (message[0] != sequence_number) continue;
    if (i == message_index && message.size() >= 2) {
      runtime->message_found = true;
      runtime->setRegVal(content_reg_id_1, message[1]);
      return;
    }
    i++;
  }
}

void InstructionVisitor::operator()(const INSTR_GET_MESSAGE_RegId_int_RegId_RegId_& instruction) {
  auto [sequence_number_reg_id, message_index, content_reg_id_1, content_reg_id_2] = instruction.args;
  auto sequence_number = runtime->getRegVal(sequence_number_reg_id);
  auto& rule_messages = runtime->messages[{runtime->rule_id}];

  int i = 0;
  runtime->message_found = false;
  for (auto& message : rule_messages) {
    if (message[0] != sequence_number) continue;
    if (i == message_index && message.size() >= 3) {
      runtime->message_found = true;
      runtime->setRegVal(content_reg_id_1, message[1]);
      runtime->setRegVal(content_reg_id_2, message[2]);
      return;
    }
    i++;
  }
}

void InstructionVisitor::operator()(const INSTR_DELETE_MESSAGE_RegId_& instruction) {
  auto [seq_no_reg] = instruction.args;
  auto sequence_number = runtime->getRegVal(seq_no_reg);
  auto& rule_messages = runtime->messages[{runtime->rule_id}];

  for (auto it = rule_messages.begin(); it != rule_messages.end();) {
    if (it->at(0) == sequence_number) {
      it = rule_messages.erase(it);
    } else {
      it++;
    }
  }
}

}  // namespace quisp::runtime

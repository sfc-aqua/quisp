/**
 * @brief def_instructions.h
 * @brief this file contains list of macros defining
 * the Intermediate Representations (IR) used in a runtime::Program.
 *
 * If you want to add new instruction, add new opcode in def_opcodes.h,
 * and then define how it works in InstructionVisitor.cc.
 */

// X-macro pattern
// https://quuxplusone.github.io/blog/2021/02/01/x-macros/
#include <sys/_types/_u_int32_t.h>
#ifndef INSTR_LAST
#define INSTR_LAST INSTR
#endif

// debugging
INSTR(DEBUG_RUNTIME_STATE, None)
INSTR(DEBUG, String)
INSTR(DEBUG, RegId)
INSTR(DEBUG, QubitId)

// arithmetic
INSTR(ADD, RegId, RegId, int)
INSTR(ADD, RegId, RegId, RegId)
INSTR(SUB, RegId, RegId, int)
INSTR(SUB, RegId, RegId, RegId)
INSTR(INC, RegId)
INSTR(SET, RegId, int)
INSTR(BITWISE_AND, RegId /* write */, RegId /* read */, RegId /* read */)
INSTR(BITWISE_AND, RegId /* write */, RegId /* read */, int /* read */)
INSTR(BITWISE_OR, RegId /* write */, RegId /* read */, RegId /* read */)
INSTR(BITWISE_OR, RegId /* write */, RegId /* read */, int /* read */)
INSTR(BITWISE_XOR, RegId /* write */, RegId /* read */, RegId /* read */)
INSTR(BITWISE_XOR, RegId /* write */, RegId /* read */, int /* read */)
// in place operation
INSTR(BITWISE_AND, RegId /* write */, RegId /* read */)  // in-place operation: first_reg = first_reg | second_reg (bitwise and)
INSTR(BITWISE_AND, RegId /* write */, int /* read */)  //  in-place operation: first_reg = first_reg | int (bitwise and)
INSTR(BITWISE_OR, RegId /* write */, RegId /* read */)  //  in-place operation: first_reg = first_reg | second_reg (bitwise or)
INSTR(BITWISE_OR, RegId /* write */, int /* read */)  //  in-place operation: first_reg = first_reg | int (bitwise or)
INSTR(BITWISE_XOR, RegId /* write */, RegId /* read */)  //  in-place operation: first_reg = first_reg | second_reg (bitwise xor)
INSTR(BITWISE_XOR, RegId /* write */, int /* read */)  //  in-place operation: first_reg = first_reg | int (bitwise xor)
// // bitset operation
// INSTR(BITSET, RegId /* write */, int /* index to set */, RegId /*  */)

// control flow
INSTR(BEQ, Label, RegId, RegId)  // branch if the reg values are same
INSTR(BEQ, Label, RegId, int)  // branch if the reg value is equal to the int value
INSTR(BEZ, Label, RegId)  // branch if the reg value is zero
INSTR(BNZ, Label, RegId)  // branch if the reg value is not zero
INSTR(BLT, Label, RegId, int)  // branch if the reg value is less than the int value
INSTR(BRANCH_IF_LOCKED, Label, RegId)
INSTR(BRANCH_IF_QUBIT_FOUND, Label)
INSTR(BRANCH_IF_MESSAGE_FOUND, Label)
INSTR(JMP, Label)
INSTR(ERROR, String)  // stop execution and show error
INSTR(RET, ReturnCode)  // stop execution with the ReturnCode

// memory operations
INSTR(LOAD, RegId, MemoryKey)
INSTR(STORE, MemoryKey, RegId)
INSTR(STORE, MemoryKey, int)

INSTR(LOAD_LEFT_OP, RegId, MemoryKey)
INSTR(LOAD_RIGHT_OP, RegId, MemoryKey)

// qubit retrieval operations
INSTR(GET_QUBIT, QubitId, QNodeAddr, int)  // may throw "no qubit error"
INSTR(GET_QUBIT, QubitId, QNodeAddr, RegId)  // may throw "no qubit error"
INSTR(GET_QUBIT, RegId /* qubit id */, QNodeAddr /* partner addr */, RegId /* given qubit index */)
INSTR(GET_QUBIT_BY_SEQ_NO, RegId /* write: qubit */, QNodeAddr /* read */, RegId /* read: seq_no */)
INSTR(GET_QUBIT_BY_SEQ_NO, QubitId /* write: qubit */, QNodeAddr /* read */, RegId /* read: seq_no */)

// qubit quantum gate operations
INSTR(MEASURE_RANDOM, MemoryKey, QubitId)
INSTR(MEASURE, MemoryKey, QubitId, Basis)
INSTR(MEASURE, RegId, QubitId, Basis)
INSTR(GATE_X, QubitId)
INSTR(GATE_Z, QubitId)
INSTR(GATE_CNOT, QubitId, QubitId)
// circuit operations
INSTR(PURIFY_X, RegId /* measurement_result */, QubitId /* keep_qubit */, QubitId /* trash_qubit */)
INSTR(PURIFY_Z, RegId /* measurement_result */, QubitId /* keep_qubit */, QubitId /* trash_qubit */)
INSTR(PURIFY_Y, RegId /* measurement_result */, QubitId /* keep_qubit */, QubitId /* trash_qubit */)

// resource management operations
INSTR(SET_PARTNER, QubitId, QNodeAddr /* new partner address */)  // TODO: in the future we would like to use SET_NAME or SET_ID instead to allow multipartite purification
INSTR(FREE_QUBIT, QubitId)
INSTR(PROMOTE, QubitId)
INSTR(PROMOTE, RegId /* qubit */)
INSTR(LOCK_QUBIT, QubitId, RegId /* action index */)

// message operations
INSTR(GET_MESSAGE_SEQ, RegId /* read: message index */, RegId /* write: sequence number */)
INSTR(COUNT_MESSAGE, RegId /* read: sequence number */, RegId /* write: count */)
INSTR(GET_MESSAGE, RegId /* read: sequence number */, int /* read: message index */, RegId /* write: correction_frame */)  // for swapping
INSTR(GET_MESSAGE, RegId /* read: sequence number */, int /* read: message index */, RegId /* write: measurement_result */, RegId /* write: protocol */)  // for purification
INSTR(DELETE_MESSAGE, RegId /* read: sequence number */) // delete all messages with this sequence number

// send classical messages
INSTR(SEND_LINK_TOMOGRAPHY_RESULT, QNodeAddr, RegId, MemoryKey, int, Time)  // partner addr, current count reg_id, outcome key, max_count, start_time
INSTR(SEND_PURIFICATION_RESULT, QNodeAddr, RegId /* measurement_result encoded in int */, RegId /* shared_rule_tag */, PurType)
INSTR(SEND_SWAPPING_RESULT, QNodeAddr /* left partner*/, RegId /* left operation */, QNodeAddr /* right partner*/, RegId /* right operation */)

INSTR_LAST(NOP, None)
#undef INSTR
#undef INSTR_LAST

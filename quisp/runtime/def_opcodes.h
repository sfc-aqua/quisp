/**
 * @file def_opcodes.h
 * @brief this file contains a list of macros defining the opcodes used in
 * the IR. These opcodes are used in def_instructions.h and opcode.h.
 */

// X-macro pattern
// https://quuxplusone.github.io/blog/2021/02/01/x-macros/
#ifdef OP
#ifndef OP_LAST
#define OP_LAST OP
#endif
OP(DEBUG)
OP(DEBUG_RUNTIME_STATE)
OP(ADD)
OP(SUB)
OP(INC)
OP(ERROR)
OP(RET)

// branch
OP(JMP)  // jump
OP(BEQ)  // branch if eq
OP(BEZ)  // branch if zero
OP(BNZ)  // branch if not zero
OP(BNE)  // branch if not equal
OP(BLT)  // branch if less than
OP(BGE)  // branch if greater or equal
OP(BRANCH_IF_LOCKED)  // branch if the given qubit is locked
OP(BRANCH_IF_QUBIT_FOUND)  // branch if the qubit found after GET_QUBIT
OP(BRANCH_IF_MESSAGE_FOUND) // branch if GET_MESSAGE flag is set

// memory
OP(LOAD)
OP(STORE)

OP(LOAD_LEFT_OP)
OP(LOAD_RIGHT_OP)

// basic op
OP(GET_QUBIT)
OP(GET_QUBIT_BY_SEQ_NO)
OP(SET)
OP(MEASURE_RANDOM)
OP(MEASURE)
OP(FREE_QUBIT)
OP(LOCK_QUBIT)
OP(GATE_X)
OP(GATE_Z)
OP(GATE_Y)
OP(GATE_CNOT)
OP(PURIFY_X)
OP(PURIFY_Y)
OP(PURIFY_Z)

// resource management
OP(SET_PARTNER)
OP(PROMOTE)

// send classical messages
OP(SEND_LINK_TOMOGRAPHY_RESULT)
OP(SEND_PURIFICATION_RESULT)
OP(SEND_SWAPPING_RESULT)

// messages
OP(GET_MESSAGE)
OP(DELETE_MESSAGE)
OP(COUNT_MESSAGE)
OP(GET_MESSAGE_SEQ)

OP_LAST(NOP)
#endif
#undef OP
#undef OP_LAST

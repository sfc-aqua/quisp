// X-macro pattern
// https://quuxplusone.github.io/blog/2021/02/01/x-macros/
#ifndef INSTR_LAST
#define INSTR_LAST INSTR
#endif
INSTR(DEBUG_RUNTIME_STATE, None)
INSTR(DEBUG, String)
INSTR(DEBUG, RegId)
INSTR(DEBUG, QubitId)
INSTR(ADD, RegId, RegId, int)
INSTR(ADD, RegId, RegId, RegId)
INSTR(SUB, RegId, RegId, int)
INSTR(SUB, RegId, RegId, RegId)
INSTR(INC, RegId)
INSTR(SET, RegId, int)
INSTR(GET_QUBIT, QubitId, QNodeAddr, int)  // may throw an no qubit error
// INSTR(MEASURE_QUBIT, MemoryKey, QubitId)
// branch
INSTR(BEQ, Label, RegId, RegId)  // branch if the regs are same
INSTR(BEQ, Label, RegId, int)  // branch if the reg value is equal to the int value
INSTR(BEZ, Label, RegId)  // branch if the reg value is zero
INSTR(BNZ, Label, RegId)  // branch if the reg val is not zero
INSTR(BNERR, Label)  // branch if no error
INSTR(JMP, Label)
INSTR(ERROR, String)  // stop execution and show error

// memory operations
INSTR(LOAD, RegId, MemoryKey)
INSTR(STORE, MemoryKey, RegId)
INSTR(STORE, MemoryKey, int)

// qubit operations
INSTR(MEASURE_RANDOM, MemoryKey, QubitId)
INSTR(MEASURE, MemoryKey, QubitId, Basis)
INSTR(FREE_QUBIT, QubitId)

// send classical messages
INSTR(SEND_LINK_TOMOGRAPHY_RESULT, QNodeAddr, RegId, MemoryKey, int)  // partner addr, current count reg_id, outcome key, max_count
// OP(SEND_PURIFICATION_RESULT)
// OP(SEND_SWAPPING_RESULT)
// send packet
// INSTR(SEND_LINK_TOMOGRAPHY_RESULT)

INSTR_LAST(NOP, int)
#undef INSTR
#undef INSTR_LAST

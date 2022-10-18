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
INSTR(GET_QUBIT, RegId /* qubit id */, QNodeAddr /* partner addr */, RegId /* given qubit index */)  // may throw an no qubit error
INSTR(RET, ReturnCode)
// INSTR(MEASURE_QUBIT, MemoryKey, QubitId)
// branch
INSTR(BEQ, Label, RegId, RegId)  // branch if the regs are same
INSTR(BEQ, Label, RegId, int)  // branch if the reg value is equal to the int value
INSTR(BEZ, Label, RegId)  // branch if the reg value is zero
INSTR(BNZ, Label, RegId)  // branch if the reg val is not zero
INSTR(BLT, Label, RegId, int)  // branch if the reg val is less than the int value
INSTR(BNERR, Label)  // branch if no error
INSTR(BRANCH_IF_LOCKED, Label, RegId)
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
INSTR(LOCK_QUBIT, QubitId, RegId /* action index */)
INSTR(GATE_X, QubitId)
INSTR(GATE_Z, QubitId)
INSTR(GATE_CNOT, QubitId, QubitId)
INSTR(PURIFY_X, RegId, QubitId, QubitId)

// send classical messages
INSTR(SEND_LINK_TOMOGRAPHY_RESULT, QNodeAddr, RegId, MemoryKey, int)  // partner addr, current count reg_id, outcome key, max_count
INSTR(SEND_PURIFICATION_RESULT, QNodeAddr, RegId)
// send packet
// INSTR(SEND_LINK_TOMOGRAPHY_RESULT)

INSTR_LAST(NOP, None)
#undef INSTR
#undef INSTR_LAST

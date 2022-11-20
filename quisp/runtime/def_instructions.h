// X-macro pattern
// https://quuxplusone.github.io/blog/2021/02/01/x-macros/
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

// control flow
INSTR(BEQ, Label, RegId, RegId)  // branch if the regs are same
INSTR(BEQ, Label, RegId, int)  // branch if the reg value is equal to the int value
INSTR(BEZ, Label, RegId)  // branch if the reg value is zero
INSTR(BNZ, Label, RegId)  // branch if the reg val is not zero
INSTR(BLT, Label, RegId, int)  // branch if the reg val is less than the int value
INSTR(BNERR, Label)  // branch if no error
INSTR(BRANCH_IF_LOCKED, Label, RegId)
INSTR(JMP, Label)
INSTR(ERROR, String)  // stop execution and show error
INSTR(RET, ReturnCode)  // stop execution with the ReturnCode

// memory operations
INSTR(LOAD, RegId, MemoryKey)
INSTR(STORE, MemoryKey, RegId)
INSTR(STORE, MemoryKey, int)

INSTR(LOAD_LEFT_OP, RegId, MemoryKey)
INSTR(LOAD_RIGHT_OP, RegId, MemoryKey)

// qubit operations
INSTR(GET_QUBIT, QubitId, QNodeAddr, int)  // may throw no qubit error
INSTR(GET_QUBIT, QubitId, QNodeAddr, RegId)  // may throw no qubit error
INSTR(GET_QUBIT, RegId /* qubit id */, QNodeAddr /* partner addr */, RegId /* given qubit index */)  // may throw no qubit error
INSTR(MEASURE_RANDOM, MemoryKey, QubitId)
INSTR(MEASURE, MemoryKey, QubitId, Basis)
INSTR(FREE_QUBIT, QubitId)
INSTR(LOCK_QUBIT, QubitId, RegId /* action index */)
INSTR(GATE_X, QubitId)
INSTR(GATE_Z, QubitId)
INSTR(GATE_CNOT, QubitId, QubitId)
INSTR(PURIFY_X, RegId, QubitId, QubitId)
INSTR(PURIFY_Z, RegId, QubitId, QubitId)

// send classical messages
INSTR(SEND_LINK_TOMOGRAPHY_RESULT, QNodeAddr, RegId, MemoryKey, int, Time)  // partner addr, current count reg_id, outcome key, max_count, start_time
INSTR(SEND_PURIFICATION_RESULT, QNodeAddr, RegId /* result_z or result_x */, RegId /* action_index */, PurType)
INSTR(SEND_PURIFICATION_RESULT, QNodeAddr, RegId /* result_z */, RegId /* result_x */, RegId /* action_index */, PurType)
INSTR(SEND_PURIFICATION_RESULT, QNodeAddr, RegId /* result_z */, RegId /* result_x */, RegId /* ds_res_z */, RegId /* ds_res_x */, RegId /* action_index */, PurType)
INSTR(SEND_SWAPPING_RESULT, QNodeAddr /* left partner*/, RegId /* left operation */, QNodeAddr /* right partner*/, RegId /* right operation */)

// hacks. will be deleted
INSTR(HACK_SWAPPING_PARTNERS, QubitId, QubitId)
INSTR(HACK_BREAK_ENTANGLEMENT, QubitId)

INSTR_LAST(NOP, None)
#undef INSTR
#undef INSTR_LAST

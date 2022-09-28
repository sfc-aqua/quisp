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

// branch
OP(JMP)  // jump
OP(BEQ)  // branch if eq
OP(BEZ)  // branch if zero
OP(BNZ)  // branch if not zero
OP(BNE)  // branch if not equal
OP(BLT)  // branch if less than
OP(BGE)  // branch if greater or equal
OP(BNERR)  // branch if no error

// memory
OP(LOAD)
OP(STORE)

// basic op
OP(GET_QUBIT)
OP(SET)
OP(MEASURE_RANDOM)
OP(MEASURE)
OP(FREE_QUBIT)
OP(GATE_X)
OP(GATE_Z)

// send classical messages
OP(SEND_LINK_TOMOGRAPHY_RESULT)
OP(SEND_PURIFICATION_RESULT)
OP(SEND_SWAPPING_RESULT)

OP_LAST(NOP)
#endif
#undef OP
#undef OP_LAST

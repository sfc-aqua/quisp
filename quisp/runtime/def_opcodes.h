// X-macro pattern
// https://quuxplusone.github.io/blog/2021/02/01/x-macros/
#ifdef OP
#ifndef OP_LAST
#define OP_LAST OP
#endif
OP(DEBUG)
OP(ADD)
OP(SUB)

// branch
OP(JMP)  // jump
OP(BEQ)  // branch if eq
OP(BEZ)  // branch if zero
OP(BNZ)  // branch if not zero
OP(BNE)  // branch if not equal
OP(BLT)  // branch if less than
OP(BGE)  // branch if greater or equal
OP(BNERR)  // branch if no error

// basic op
OP(GET_QUBIT)
OP(SET)

OP_LAST(NOP)
#endif
#undef OP
#undef OP_LAST

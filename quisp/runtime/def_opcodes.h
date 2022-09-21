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
OP(JMP)
OP(BEQ)
OP(BEZ)
OP(BNZ)
OP(BNE)
OP(BLT)
OP(BGE)

// basic op
OP(GET_QUBIT)
OP(SET)

OP_LAST(NOP)
#endif
#undef OP
#undef OP_LAST

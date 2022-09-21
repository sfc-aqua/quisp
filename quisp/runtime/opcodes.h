// X-macro pattern
// https://quuxplusone.github.io/blog/2021/02/01/x-macros/
#ifdef OP
#ifndef OP_LAST
#define OP_LAST OP
#endif
OP(NOP)
OP(DEBUG)
OP(ADD)
OP(SUB)
OP_LAST(SET)
#endif
#undef OP
#undef OP_LAST

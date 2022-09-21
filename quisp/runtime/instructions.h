// X-macro pattern
// https://quuxplusone.github.io/blog/2021/02/01/x-macros/
#ifndef INST
#error define INST macro first
#endif
#ifndef INST_LAST
#define INST_LAST INST
#endif
INST(DEBUG, float)
INST(DEBUG, int)
INST(DEBUG, String)
INST(DEBUG, RegisterId)
INST(ADD, RegisterId, int, int)
INST(ADD, RegisterId, RegisterId, int)
INST(ADD, RegisterId, RegisterId, RegisterId)
INST(SUB, RegisterId, int, int)
INST(SUB, RegisterId, RegisterId, int)
INST(SUB, RegisterId, RegisterId, RegisterId)
INST_LAST(NOP, int)
#undef INST
#undef INST_LAST

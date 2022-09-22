// X-macro pattern
// https://quuxplusone.github.io/blog/2021/02/01/x-macros/
#ifndef INSTR_LAST
#define INSTR_LAST INSTR
#endif

INSTR(DEBUG, float)
INSTR(DEBUG, int)
INSTR(DEBUG, String)
INSTR(DEBUG, RegId)
INSTR(ADD, RegId, RegId, int)
INSTR(ADD, RegId, RegId, RegId)
INSTR(SUB, RegId, RegId, int)
INSTR(SUB, RegId, RegId, RegId)
INSTR(SET, RegId, int)
INSTR(GET_QUBIT, QubitId, QNodeAddr)
INSTR_LAST(NOP, int)
#undef INSTR
#undef INSTR_LAST

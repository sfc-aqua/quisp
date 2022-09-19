#ifdef OP
#ifndef OP_LAST
#define OP_LAST OP
#endif
OP(DEBUG)
OP(NONE)
OP(ADD)
OP(SUB)
OP_LAST(SET)
#endif
#undef OP
#undef OP_LAST

#ifdef INST
#ifndef INST_LAST
#define INST_LAST INST
#endif
INST(NONE, int)
INST(DEBUG, float)
INST(DEBUG, int)
INST(DEBUG, String)
INST(ADD, int, int)
INST_LAST(SUB, int, int)
#endif
#undef INST
#undef INST_LAST

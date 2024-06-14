#include "asm.h"
#include "asm/cpux8664.h"

void genpreamble() { cgpreamble(); }
void genpostamble() { cgpostamble(); }
void genfreeregs() { freeall_registers(); }
void genprintint(int reg) { cgprintint(reg); }

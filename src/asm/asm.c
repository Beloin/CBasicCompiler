#include "asm.h"
#include "asm/cpux8664.h"

void genpreamble() { cgpreamble(); }
void genpostamble() { cgpostamble(); }
void genfreeregs() { freeall_registers(); }
void genprintint(int reg) { cgprintint(reg); }
void genglobsym(char *s) { cgglobsym(s); }
void genstoreglob(int r, char *identifier) { cgstorglob(r, identifier); }
void genloadglob(char *identifier) { cgloadglob(identifier); }

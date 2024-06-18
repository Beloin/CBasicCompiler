#ifndef ASM_ASM_H
#define ASM_ASM_H

void genpreamble();
void genpostamble();
void genfreeregs();
void genprintint(int reg);
void genglobsym(char *s);
void genstoreglob(int r, char *identifier);
void genloadglob(char *identifier);

#endif // !ASM_ASM_H

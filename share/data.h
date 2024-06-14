#ifndef SHARE_DATA_H
#define SHARE_DATA_H

#include "lexical/scanner.h"
#include <stdio.h>

#define TEXTLEN 512

extern char Text[TEXTLEN + 1];

extern struct token Token;
extern int Line;
extern int Putback;
extern FILE *Infile;
extern FILE *Outfile;

#endif // !SHARE_DATA_H

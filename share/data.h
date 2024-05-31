#ifndef SHARE_DATA_H
#define SHARE_DATA_H

#include "lexical/scanner.h"
#include <stdio.h>

extern struct token Token;
extern int Line;
extern int Putback;
extern FILE *Infile;

#endif // !SHARE_DATA_H

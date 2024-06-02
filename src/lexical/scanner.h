#ifndef LEXICAL_SCANNER_H
#define LEXICAL_SCANNER_H

// Basic language Token
struct token {
  // Tokens defined in enum
  int token;
  int intvalue;
};

enum {
  T_PLUS = 0,
  T_MINUS = 1,
  T_STAR = 2,
  T_SLASH = 3,
  T_INTLIT = 4,
  T_EOF = 5
};

// Scan current line usingthe following externs:
// int Line;
// int Putback;
// FILE *Infile;
int scan(struct token *t);

#endif // !LEXICAL_SCANNER_H

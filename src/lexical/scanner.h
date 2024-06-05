#ifndef LEXICAL_SCANNER_H
#define LEXICAL_SCANNER_H

// Basic language Token
struct token {
  // Tokens defined in enum
  int token;
  int intvalue;
};

enum {
  T_EOF,
  T_PLUS,
  T_MINUS,
  T_STAR,
  T_SLASH,
  T_INTLIT,
};

// Scan current line usingthe following externs:
// int Line;
// int Putback;
// FILE *Infile;
int scan(struct token *t);

#endif // !LEXICAL_SCANNER_H

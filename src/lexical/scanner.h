#ifndef LEXICAL_SCANNER_H
#define LEXICAL_SCANNER_H

// Basic language Token
struct token {
  // Tokens defined in enum
  int token;
  int intvalue;
};

// TODO: Tokens could be elsewhere
// Low to high precedence
enum {
  T_EOF,
  T_PLUS, T_MINUS,
  T_STAR, T_SLASH,

  T_EQ, T_NE,
  T_LT, T_GT, T_LE, T_GE, 

  T_INTLIT, T_SEMI, T_ASSIGN, T_IDENTF,

  // Keywords -- Not accounted in OpPrec
  T_PRINT, T_INT
};

// Scan current line usingthe following externs:
// int Line;
// int Putback;
// FILE *Infile;
int scan(struct token *t);

// Scan an identifier from the input file and
// store it in buf[]. Return the identifier's length
static int scanident(int c, char *buf, int lim);

// Given a word from the input, return the matching
// keyword token number or 0 if it's not a keyword.
// Switch on the first letter so that we don't have
// to waste time strcmp()ing against all the keywords.
static int keyword(char *s);

#endif // !LEXICAL_SCANNER_H

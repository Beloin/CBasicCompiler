#ifndef SHARE_HELPER_H
#define SHARE_HELPER_H

// Ensure that the current token is t,
// and fetch the next token. Otherwise
// throw an error
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include "lexical/scanner.h"

void match(int t, char *what) {
  if (Token.token == t) {
    scan(&Token);
  } else {
    printf("%s expected on line %d\n", what, Line);
    exit(1);
  }
}

// Match a semicon and fetch the next token
void semi(void) { match(T_SEMI, ";"); }

#endif // !SHARE_HELPER_H

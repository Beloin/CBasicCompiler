#include "expr.h"
#include "lexical/ast.h"
#include "lexical/scanner.h"
#include <stdio.h>
#include <stdlib.h>
#include "data.h"

ASTNodeType arithop(int tok) {
  switch (tok) {
  case T_PLUS:
    return (A_ADD);
  case T_MINUS:
    return (A_SUBTRACT);
  case T_STAR:
    return (A_MULTIPLY);
  case T_SLASH:
    return (A_DIVIDE);
  default:
    fprintf(stderr, "unknown token in arithop() on line %d\n", Line);
    exit(1);
  }
}

static struct ASTnode *primary(void) {
  struct ASTnode *n;

  // For an INTLIT token, make a leaf AST node for it
  // and scan in the next token. Otherwise, a syntax error
  // for any other token type.
  switch (Token.token) {
  case T_INTLIT:
    n = mkastleaf(A_INTLIT, Token.intvalue);
    scan(&Token);
    return (n);
  default:
    fprintf(stderr, "syntax error on line %d\n", Line);
    exit(1);
  }
}

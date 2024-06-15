#include "expr.h"
#include "data.h"
#include "lexical/ast.h"
#include "lexical/scanner.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

struct ASTnode *binexpr(int ptp) {
  struct ASTnode *n, *left, *right;
  int nodetype;
  int tokentype;

  // Get the integer literal on the left.
  // Fetch the next token at the same time.
  left = primary();

  // If no tokens left, return just the left node
  tokentype = Token.token;
  if (tokentype == T_SEMI)
    return (left);

  while (op_precedence(tokentype) > ptp) {
    scan(&Token);
    right = binexpr(OpPrec[tokentype]);
    left = mkastnode(arithop(tokentype), left, right, 0);

    tokentype = Token.token;
    if (tokentype == T_SEMI) {
      return left;
    }
  }

  return left;
}

// Given an AST, interpret the
// a final value.
// operators in it and return
int interpretAST(struct ASTnode *n) {
  int leftval, rightval;

  // Get the left and right sub-tree values
  if (n->left)
    leftval = interpretAST(n->left);
  if (n->right)
    rightval = interpretAST(n->right);

#ifdef NDEBUG
  // Debug: Print what we are about to do
  if (n->op == A_INTLIT)
    printf("int %d\n", n->intvalue);
  else
    printf("%d %s %d\n", leftval, ASTop[n->op], rightval);
#endif /* ifdef NDEBUG */

  switch (n->op) {
  case A_ADD:
    return (leftval + rightval);
  case A_SUBTRACT:
    return (leftval - rightval);
  case A_MULTIPLY:
    return (leftval * rightval);
  case A_DIVIDE:
    return (leftval / rightval);
  case A_INTLIT:
    return (n->intvalue);
  default:
    fprintf(stderr, "Unknown AST operator %d\n", n->op);
    exit(1);
  }
}

struct ASTnode *additive_expr(void) {
  struct ASTnode *left, *right;
  int tokentype;

  // Get the left sub-tree at a higher precedence than us
  left = multiplicative_expr();

  // If no tokens left, return just the left node
  tokentype = Token.token;
  if (tokentype == T_EOF)
    return (left);

  // Loop working on token at our level of precedence
  while (1) {
    // Fetch in the next integer literal
    scan(&Token);

    // Get the right sub-tree at a higher precedence than us
    right = multiplicative_expr();

    // Join the two sub-trees with our low-precedence operator
    left = mkastnode(arithop(tokentype), left, right, 0);

    // And get the next token at our precedence
    tokentype = Token.token;
    if (tokentype == T_EOF)
      break;
  }

  // Return whatever tree we have created
  return (left);
}

struct ASTnode *multiplicative_expr(void) {
  struct ASTnode *left, *right;
  int tokentype;

  // Get the integer literal on the left.
  // Fetch the next token at the same time.
  left = primary();

  // If no tokens left, return just the left node
  tokentype = Token.token;
  if (tokentype == T_EOF)
    return (left);

  // While the token is a '*' or '/'
  while ((tokentype == T_STAR) || (tokentype == T_SLASH)) {
    // Fetch in the next integer literal
    scan(&Token);
    right = primary();

    // Join that with the left integer literal
    left = mkastnode(arithop(tokentype), left, right, 0);

    // Update the details of the current token.
    // If no tokens left, return just the left node
    tokentype = Token.token;
    if (tokentype == T_EOF)
      break;
  }

  // Return whatever tree we have created
  return (left);
}

static int op_precedence(int tokentype) {
  int prec = OpPrec[tokentype];
  if (prec == 0) {
    fprintf(stderr, "syntax error on line %d, token %d\n", Line, tokentype);
    exit(1);
  }
  return (prec);
}

#ifndef LEXICAL_EXPR_H
#define LEXICAL_EXPR_H

#include "lexical/ast.h"

// List of AST operators
static char *ASTop[] = {"+", "-", "*", "/"};

// Convert a token into an AST operation.
ASTNodeType arithop(int tok);

// Parse a primary factor and return an
// AST node representing it.
static struct ASTnode *primary(void);

// Return an AST tree whose root is a binary operator
// Parameter ptp is the previous token's precedence.
// Using this to add Pratt's Precedence parser using a table
// based on Token type
struct ASTnode *binexpr(int ptp);

// Given an AST, interpret the
// operators in it and return
// a final value.
int interpretAST(struct ASTnode *n);

// Return an AST tree whose root is a '+' or '-' binary operator
[[deprecated]] struct ASTnode *additive_expr(void);

// Return an AST tree whose root is a '*' or '/' binary operator
[[deprecated]] struct ASTnode *multiplicative_expr(void);

// Definitions of function following Pratt's parser

// Operator precedence for each token -> The higher the higher precedence
static int OpPrec[] = {0, 10, 10, 20, 20, 0};
//                     EOF  +   -   *   /  INTLIT

// Check that we have a binary operator and
// return its precedence.
static int op_precedence(int tokentype);

#endif // !LEXICAL_EXPR_H

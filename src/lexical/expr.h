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
struct ASTnode *binexpr(void);

// Given an AST, interpret the
// operators in it and return
// a final value.
int interpretAST(struct ASTnode *n);

#endif // !LEXICAL_EXPR_H

#ifndef LEXICAL_EXPR_H
#define LEXICAL_EXPR_H

#include "lexical/ast.h"

// Convert a token into an AST operation.
ASTNodeType arithop(int tok);

// Parse a primary factor and return an
// AST node representing it.
static struct ASTnode *primary(void);

#endif // !LEXICAL_EXPR_H

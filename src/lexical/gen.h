#ifndef LEXICAL_GEN_H
#define LEXICAL_GEN_H

#include "ast.h"

// Given an AST, generate
// assembly code recursively
int genAST(struct ASTnode *n);

// Generate code with preamble and postamble
void generatecode(struct ASTnode *n);

#endif // !LEXICAL_GEN_H

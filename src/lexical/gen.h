#ifndef LEXICAL_GEN_H
#define LEXICAL_GEN_H

#include "ast.h"

// Given an AST, generate
// assembly code recursively
static int genAST(struct ASTnode *n);

// Generate codes with preamble and postamble
void generatecode(struct ASTnode *n);

#endif // !LEXICAL_GEN_H

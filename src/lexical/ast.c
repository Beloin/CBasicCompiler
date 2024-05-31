#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

struct ASTnode *mkastnode(ASTNodeType op, struct ASTnode *left,
                          struct ASTnode *right, int intvalue) {
  struct ASTnode *n;

  // Malloc a new ASTnode -> Remember to free
  n = (struct ASTnode *)malloc(sizeof(struct ASTnode));
  if (n == NULL) {
    fprintf(stderr, "Unable to malloc in mkastnode()\n");
    exit(1);
  }
  // Copy in the field values and return it
  n->op = op;
  n->left = left;
  n->right = right;
  n->intvalue = intvalue;
  return (n);
}

struct ASTnode *mkastleaf(ASTNodeType op, int intvalue) {
  return (mkastnode(op, NULL, NULL, intvalue));
}

struct ASTnode *mkastunary(ASTNodeType op, struct ASTnode *left, int intvalue) {
  return (mkastnode(op, left, NULL, intvalue));
}

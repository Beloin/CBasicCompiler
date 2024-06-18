#include "gen.h"
#include "asm/cpux8664.h"
#include "lexical/ast.h"
#include "lexical/misc.h"
#include "lexical/symbols.h"

void generatecode(struct ASTnode *n) {
  int reg;

  cgpreamble();
  reg = genAST(n, -1);
  cgprintint(reg); // Print the register with the result as an int
  cgpostamble();
}

int genAST(struct ASTnode *n, int reg) {
  int leftreg, rightreg;

  // Get the left and right sub-tree values
  if (n->left)
    leftreg = genAST(n->left, -1);
  if (n->right)
    rightreg = genAST(n->right, leftreg);

  switch (n->op) {
  case A_ADD:
    return (cgadd(leftreg, rightreg));
  case A_SUBTRACT:
    return (cgsub(leftreg, rightreg));
  case A_MULTIPLY:
    return (cgmul(leftreg, rightreg));
  case A_DIVIDE:
    return (cgdiv(leftreg, rightreg));
  case A_INTLIT:
    return cgload(n->v.intvalue);
  case A_IDENTF:
    return cgloadglob(Gsym[n->v.id].name);
  case A_LVIDENTF:
    return cgstorglob(reg, Gsym[n->v.id].name);
  case A_ASSIGN:
    // The work has already been done, return the result
    return rightreg;
  default:
    fatald("Unknown AST operator", n->op);
  }
}

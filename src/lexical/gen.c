#include "gen.h"
#include "asm/asm.h"
#include "asm/cpux8664.h"
#include "lexical/ast.h"
#include "lexical/misc.h"
#include "lexical/symbols.h"

// Generate and return a new label number
static int label(void);

// Generate the code for an IF statement
// and an optional ELSE clause
static int genIFAST(struct ASTnode *n);

void generatecode(struct ASTnode *n) {
  // TODO: Not used
  // int reg;
  //
  // cgpreamble();
  // reg = genAST(n, -1);
  // cgprintint(reg); // Print the register with the result as an int
  // cgpostamble();
}

int genAST(struct ASTnode *n, int reg, int parentASTop) {
  int leftreg, rightreg;

  // We now have specific AST node handling at the top
  switch (n->op) {
  case A_IF:
    return (genIFAST(n));
  case A_GLUE:
    // Do each child statement, and free the
    // registers after each child
    genAST(n->left, NOREG, n->op);
    genfreeregs();
    genAST(n->right, NOREG, n->op);
    genfreeregs();
    return (NOREG);
  default:
    break;
  }

  // Get the left and right sub-tree values
  if (n->left)
    leftreg = genAST(n->left, -1, n->op);
  if (n->right)
    rightreg = genAST(n->right, leftreg, n->op);

  switch (n->op) {
  case A_ADD:
    return (cgadd(leftreg, rightreg));
  case A_SUBTRACT:
    return (cgsub(leftreg, rightreg));
  case A_MULTIPLY:
    return (cgmul(leftreg, rightreg));
  case A_DIVIDE:
    return (cgdiv(leftreg, rightreg));
  case A_EQ:
    // return (cgequal(leftreg, rightreg));
  case A_NE:
    // return (cgnotequal(leftreg, rightreg));
  case A_LT:
    // return (cglessthan(leftreg, rightreg));
  case A_GT:
    // return (cggreaterthan(leftreg, rightreg));
  case A_LE:
    // return (cglessequal(leftreg, rightreg));
  case A_GE:
    // return (cggreaterequal(leftreg, rightreg));
    if (parentASTop == A_IF)
      return cgcompare_and_jump(n->op, leftreg, rightreg, reg);
    else
      return cgcompare_and_set(n->op, leftreg, rightreg);
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

  return -1;
}

// Generate and return a new label number
static int label(void) {
  static int id = 1;
  return (id++);
}

// Generate the code for an IF statement
// and an optional ELSE clause
static int genIFAST(struct ASTnode *n) {
  int Lfalse, Lend;

  // Generate two labels: one for the
  // false compound statement, and one
  // for the end of the overall IF statement.
  // When there is no ELSE clause, Lfalse _is_
  // the ending label!
  Lfalse = label();
  if (n->right)
    Lend = label();

  // Generate the condition code followed
  // by a zero jump to the false label.
  // We cheat by sending the Lfalse label as a register.
  genAST(n->left, Lfalse, n->op);
  genfreeregs();

  // Generate the true compound statement
  genAST(n->mid, NOREG, n->op);
  genfreeregs();

  // If there is an optional ELSE clause,
  // generate the jump to skip to the end
  if (n->right)
    cgjump(Lend);

  // Now the false label
  cglabel(Lfalse);

  // Optional ELSE clause: generate the
  // false compound statement and the
  // end label
  if (n->right) {
    genAST(n->right, NOREG, n->op);
    genfreeregs();
    cglabel(Lend);
  }

  return (NOREG);
}

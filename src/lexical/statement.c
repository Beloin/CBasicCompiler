#include "statement.h"
#include "asm/asm.h"
#include "data.h"
#include "lexical/expr.h"
#include "lexical/gen.h"
#include "lexical/misc.h"

void statements(void) {

  while (1) {
    switch (Token.token) {
    case T_PRINT:
      print_statement();
      break;
    case T_INT:
      var_declaration();
      break;
    case T_IDENTF:
      assignment_statement();
      break;
    case T_EOF:
      return;
    default:
      fatald("Syntax error, token", Token.token);
    }
  }
}

void print_statement() {
  struct ASTnode *tree;
  int reg;
  // Match a 'print' as the first token
  match(T_PRINT, "print");

  // Parse the following expression and
  // generate the assembly code
  tree = binexpr(0);
  reg = genAST(tree);
  genprintint(reg);
  genfreeregs();

  // Match the following semicolon
  // and stop if we are at EOF
  semi();
  if (Token.token == T_EOF)
    return;
}

// Parse the declaration of a variable
void var_declaration() {

  // Ensure we have an 'int' token followed by an identifier
  // and a semicolon. Text now has the identifier's name.
  // Add it as a known identifier
  match(T_INT, "int");
  ident();
  addglob(Text);
  genglobsym(Text);
  semi();
}

void assignment_statement(void) {
  struct ASTnode *left, *right, *tree;
  int id;

  // Ensure we have an identifier
  ident();

  // Check it's been defined then make a leaf node for it
  if ((id = findglob(Text)) == -1) {
    fatals("Undeclared variable", Text);
  }
  right = mkastleaf(A_LVIDENT, id); // L VALUE IDENTIFIER

  // Ensure we have an equals sign
  match(T_EQUALS, "=");

  // Parse the following expression
  left = binexpr(0);

  // Make an assignment AST tree
  // This means the R value are evaluated before added to L VALUE
  tree = mkastnode(A_ASSIGN, left, right, 0);

  // Generate the assembly code for the assignment
  genAST(tree, -1);
  genfreeregs();

  // Match the following semicolon
  semi();
}

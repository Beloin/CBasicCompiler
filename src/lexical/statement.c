#include "statement.h"
#include "asm/asm.h"
#include "data.h"
#include "lexical/ast.h"
#include "lexical/expr.h"
#include "lexical/gen.h"
#include "lexical/misc.h"
#include "lexical/scanner.h"
#include "lexical/symbols.h"

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
  reg = genAST(tree, -1);
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

  right = mkastleaf(A_LVIDENTF, id); // L VALUE IDENTIFIER

  // Ensure we have an equals sign
  match(T_ASSIGN, "=");

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

struct ASTnode *compound_statement(void) {
  struct ASTnode *left = NULL;
  struct ASTnode *tree;

  // Requires a left curly brace -- As obligatory to dont need to change grammar
  lbrace();

  while (1) {
    switch (Token.token) {
    case T_PRINT:
      tree = print_statement();
      break;
    case T_INT:
      var_declaration();
      tree = NULL;
      break;
    case T_IDENTF:
      tree = assignment_statement();
      break;
    case T_IF:
      tree = if_statement();
      break;
    case T_RBRACE:
      // When we hit a right curly bracket,
      // skip past it and return the AST
      rbrace();
      return (left);
    default:
      fatald("Syntax error, token", Token.token);
    }
  }

  // For each new tree, either save it in left
  // if left is empty, or glue the left and the
  // new tree together
  if (tree) {
    if (left == NULL)
      left = tree;
    else
      left = mkastnode(A_GLUE, left, NULL, 0);
  }
}

struct ASTnode *if_statement(void) {
  struct ASTnode *condAST, *trueAST, *falseAST = NULL;

  // Ensure we have 'if' '('
  match(T_IF, "if");
  lparen();

  // Parse the following expression
  // and the ')' following. Ensure
  // the tree's operation is a comparison.
  condAST = binexpr(0);

  // This holds the comparitions
  if (condAST->op < A_EQ || condAST->op > A_GE)
    fatal("Bad comparison operator");
  rparen();

  // Get inside condition ast
  trueAST = compound_statement();

  // If we have an 'else', skip it
  // and get the AST for the compound statement
  if (Token.token == T_ELSE) {
    scan(&Token);
    falseAST = compound_statement();
  }

  // Build and return the AST for this statement
  return (mkastnode(A_IF, condAST, trueAST, falseAST, 0));
}

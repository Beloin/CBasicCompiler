#include "data.h"
#include "lexical/ast.h"
#include "lexical/expr.h"
#include <stdio.h>
#include <stdlib.h>

#include <lexical/scanner.h>

// TODO: Put this into a API on its own -- All this is referenced by extern in
// data.h
int Line = 0;
int Putback = 0;
FILE *Infile;
struct token Token;

// Loop scanning in all the tokens in the input file.
// Print out details of each token found.
static void scanfile();
char *tokstr[] = {"+", "-", "*", "/", "intlit"};

int main(int argc, char *argv[]) {
  struct ASTnode *node;
  Infile = fopen(argv[1], "r");

  // scanfile();
  scan(&Token);
  node = binexpr(0);
  printf("%d\n", interpretAST(node));

  return EXIT_SUCCESS;
}

static void scanfile() {
  while (scan(&Token)) {
    printf("Token %s", tokstr[Token.token]);
    if (Token.token == T_INTLIT)
      printf(", value %d", Token.intvalue);
    printf("\n");
  }
}

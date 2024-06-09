#include "data.h"
#include "lexical/ast.h"
#include "lexical/expr.h"
#include "lexical/gen.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <lexical/scanner.h>
#include <string.h>

// TODO: Put this into a API on its own -- All this is referenced by extern in
// data.h
int Line = 0;
int Putback = 0;
FILE *Infile;
FILE *Outfile;
struct token Token;

// Loop scanning in all the tokens in the input file.
// Print out details of each token found.
static void scanfile();
char *tokstr[] = {"+", "-", "*", "/", "intlit"};

static void init() {
  Line = 1;
  Putback = '\n';
}

int main(int argc, char *argv[]) {
  struct ASTnode *ast;
  Infile = fopen(argv[1], "r");
  if (argc != 2)
    exit(1);

  init();
  // Open up the input file
  if ((Infile = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
    exit(1);
  }

  // Create the output file
  if ((Outfile = fopen("out.s", "w")) == NULL) {
    fprintf(stderr, "Unable to create out.s: %s\n", strerror(errno));
    exit(1);
  }

  scan(&Token);
  ast = binexpr(0);
  printf("%d\n", interpretAST(ast));
  generatecode(ast);

  fclose(Outfile);

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

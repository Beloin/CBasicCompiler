#include "data.h"
#include <stdio.h>
#include <stdlib.h>

#include <lexical/scanner.h>

// TODO: Put this into a API on its own -- All this is referenced by extern in
// data.h
int Line;
int Putback;
FILE *Infile;
struct token Token;

// Loop scanning in all the tokens in the input file.
// Print out details of each token found.
static void scanfile();
char *tokstr[] = {"+", "-", "*", "/", "intlit"};

int main(int argc, char *argv[]) {
  Infile = fopen(argv[1], "r");

  scanfile();

  return EXIT_SUCCESS;
}

static void scanfile() {
  struct token T;

  while (scan(&T)) {
    printf("Token %s", tokstr[T.token]);
    if (T.token == T_INTLIT)
      printf(", value %d", T.intvalue);
    printf("\n");
  }
}

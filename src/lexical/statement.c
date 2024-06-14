#include "asm/asm.h"
#include "lexical/expr.h"
#include "lexical/gen.h"
#include "data.h"
#include "lexical/misc.h"

void statements(void) {
  struct ASTnode *tree;
  int reg;

  while (1) {
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
}

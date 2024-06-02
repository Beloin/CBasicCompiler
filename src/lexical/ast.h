#ifndef LEXICAL_AST_H
#define LEXICAL_AST_H

// AST node types
typedef enum { A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE, A_INTLIT } ASTNodeType;

// Abstract Syntax Tree structure
struct ASTnode {
  ASTNodeType op;       // "Operation" to be performed on this tree
  struct ASTnode *left; // Left and right child trees
  struct ASTnode *right;
  int intvalue; // For A_INTLIT, the integer value
};

// Build and return a generic AST node
struct ASTnode *mkastnode(ASTNodeType op, struct ASTnode *left,
                         struct ASTnode *right, int intvalue);

// Make an AST leaf node
struct ASTnode *mkastleaf(ASTNodeType op, int intvalue);

// Make a unary AST node: only one child
struct ASTnode *mkastunary(ASTNodeType op, struct ASTnode *left, int intvalue);

#endif // !LEXICAL_AST_H

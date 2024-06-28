#ifndef LEXICAL_STATEMENT_H
#define LEXICAL_STATEMENT_H

// statements: statement
//      | statement statements
//      ;
//
// statement: 'print' expression ';'
//      ;

// Parse one or more statements
void statements(void);

void print_statement();

// Parse the declaration of a variable
void var_declaration();

void semi();

void ident();

void assignment_statement(void);

// Parse a compound statement
// and return its AST
struct ASTnode *compound_statement(void);

// Parse an IF statement including
// any optional ELSE clause
// and return its AST
struct ASTnode *if_statement(void);

#endif // !LEXICAL_STATEMENT_H

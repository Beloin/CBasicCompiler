# Own C subset Compiler 

This is my own version of a compiler. Will be a self-compiling compiler.

# Asm to bin:

Command: `cc -o out out.s`

# Lexical
Code to read file and parse it into tokens.

The parser's job is to recognise the input
> Later on, you will see that this isn't actually true. It often makes sense to intertwine the syntax analysis and semantic analysis.  

We need to define a Grammar using Backus-Naur Form...

Example

```BNF
expression: number
          | expression '*' expression
          | expression '/' expression
          | expression '+' expression
          | expression '-' expression
          ;

number:  T_INTLIT # Terminal symbol
         ;
```

Create Abstract Syntax Trees, this is what the parses will allways result in.

Now to add precedence, we need the following grammar:

```BNF
expression: additive_expression
    ;

additive_expression:
      multiplicative_expression
    | additive_expression '+' multiplicative_expression
    | additive_expression '-' multiplicative_expression
    ;

multiplicative_expression:
      number
    | number '*' multiplicative_expression
    | number '/' multiplicative_expression
    ;

number:  T_INTLIT
         ;
```


Now we need to add statements, initially we can do this:

```BNF
statements: statement
    | statement statements
    ;

statement: 'print' expression ';'
```


Add variables:

```
 tatements: statement
      |      statement statements
      ;

 statement: 'print' expression ';'
      |     'int'   identifier ';'
      |     identifier '=' expression ';'
      ;

 identifier: T_IDENT
      ;
```


Conditional

```
  if (condition is true) 
    perform this first block of code
  else
    perform this other block of code
```
In assembly the code runs using jumps to labels, but we jump to the label if the opposite is true.

New Grammar:

```
 compound_statement: '{' '}'          // empty, i.e. no statement
      |      '{' statement '}'
      |      '{' statement statements '}'
      ;

 statement: print_statement
      |     declaration
      |     assignment_statement
      |     if_statement
      ;

 print_statement: 'print' expression ';'  ;

 declaration: 'int' identifier ';'  ;

 assignment_statement: identifier '=' expression ';'   ;

 if_statement: if_head
      |        if_head 'else' compound_statement
      ;

 if_head: 'if' '(' true_false_expression ')' compound_statement  ;

 identifier: T_IDENT ;
```

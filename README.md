# Own C subset Compiler 

This is my own version of a compiler.

# Asm to bin:

cc -o out out.s

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

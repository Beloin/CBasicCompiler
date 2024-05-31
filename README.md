# Own C subset Compiler 

This is my own version of a compiler.


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

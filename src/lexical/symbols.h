#ifndef LEXICAL_SYMBOLS_H
#define LEXICAL_SYMBOLS_H

#define NSYMBOLS 1024 // Number of symbol table entries

// Symbol table structure
struct symtable {
  char *name; // Name of a symbol
};

extern struct symtable Gsym[NSYMBOLS]; // Global symbol table
static int Globs = 0; // Position of next free global symbol slot

#endif // !LEXICAL_SYMBOLS_H

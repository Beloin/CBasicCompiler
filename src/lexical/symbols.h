#ifndef LEXICAL_SYMBOLS_H
#define LEXICAL_SYMBOLS_H

#define NSYMBOLS 1024 // Number of symbol table entries

// Symbol table structure
struct symtable {
  char *name; // Name of a symbol
};

extern struct symtable Gsym[NSYMBOLS]; // Global symbol table
static int Globs = 0; // Position of next free global symbol slot

// Determine if the symbol s is in the global symbol table.
// Return its slot position or -1 if not found.
int findglob(char *s);

// Add a global symbol to the symbol table.
// Return the slot number in the symbol table
int addglob(char *name);

#endif // !LEXICAL_SYMBOLS_H

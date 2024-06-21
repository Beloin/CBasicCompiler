#ifndef ASM_86X64_H
#define ASM_86X64_H

// TODO: Add this to a folder outside of ./src, since we can have multiple
// "target" asm. i.e (/asm/i358/*)
// also is necessary to "abstract" this part of the code

// -> Specific x86-64 functions

// Registers and current state
static int freereg[4];
static char *reglist[4] = {"%r8", "%r9", "%r10", "%r11"};
static char *breglist[4] = {"%r8b", "%r9b", "%r10b", "%r11b"};

// Set all registers as available
void freeall_registers(void);

// Allocate a free register. Return the number of
// the register. Die if no available registers.
static int alloc_register(void);

// Return a register to the list of available registers.
// Check to see if it's not already there.
static void free_register(int reg);

// -> Generic asm gen functions:

// Print out the assembly preamble
void cgpreamble();

// Print out the assembly postamble
void cgpostamble();

// Call printint() with the given register
void cgprintint(int r);

// Load an integer literal value into a register.
// Return the number of the register
int cgload(int value);

// Add two registers together and return
// the number of the register with the result
int cgadd(int r1, int r2);

// Multiply two registers together and return
// the number of the register with the result
int cgmul(int r1, int r2);

// Subtract the second register from the first and
// return the number of the register with the result
int cgsub(int r1, int r2);

// Divide the first register by the second and
// return the number of the register with the result
int cgdiv(int r1, int r2);

// Load a identifier returning the register
int cgloadglob(char *identifier);

// Store a register's value into a variable
int cgstorglob(int r, char *identifier);

// Generate a global symbol
void cgglobsym(char *sym);

// Compare registers using `how` as operator to retrieve result
static int cgcompare(int r1, int r2, char *how);

int cgequal(int r1, int r2);

int cgnotequal(int r1, int r2);
int cglessthan(int r1, int r2);

int cggreaterthan(int r1, int r2);

int cglessequal(int r1, int r2);

int cggreaterequal(int r1, int r2);

#endif // !ASM_86X64_H

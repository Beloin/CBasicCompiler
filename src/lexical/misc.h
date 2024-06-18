#ifndef SHARE_HELPER_H
#define SHARE_HELPER_H

// Ensure that the current token is t,
// and fetch the next token. Otherwise
// throw an error
void match(int t, char *what);

// Match a semicon and fetch the next token
void semi(void);
void ident(void);

// Print out fatal messages
void fatal(char *s);

void fatals(char *s1, char *s2);

void fatald(char *s, int d);
void fatalc(char *s, int c);

#endif // !SHARE_HELPER_H

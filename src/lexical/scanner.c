#include "scanner.h"
#include <ctype.h>
#include <data.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int next(void);
static void putback(int c);

// Skip past input that we don't need to deal with,
// i.e. whitespace, newlines. Return the first
// character we do need to deal with.
static int skip(void);

// Scan and return an integer literal
// value from the input file.
static int scanint(int c);

// Return the position of character c
// in string s, or -1 if c not found
static int chrpos(char *s, int c);

extern int Line;
extern int Putback;
extern FILE *Infile;

int scan(struct token *t) {
  int c, tokentype;

  c = skip();

  switch (c) {
  case EOF:
    t->token = T_EOF;
    break;
  case '+':
    t->token = T_PLUS;
    break;
  case '-':
    t->token = T_MINUS;
    break;
  case '*':
    t->token = T_STAR;
    break;
  case '/':
    t->token = T_SLASH;
    break;
  case ';':
    t->token = T_SEMI;
    break;
  default:
    if (isdigit(c)) {
      t->intvalue = scanint(c);
      t->token = T_INTLIT;

      break;
    } else if (isalpha(c) || '_' == c) {
      // Read in a keyword or identifier
      scanident(c, Text, TEXTLEN);

      // If it's a recognised keyword, return that token
      if ((tokentype = keyword(Text))) {
        t->token = tokentype;
        break;
      }

      // Not a recognised keyword, so an error for now
      printf("Unrecognised character '%c' on line %d\n", c, Line);
      exit(1);
    }
    // The character isn't part of any recognised token, error
    printf("Unrecognised character %c on line %d\n", c, Line);
    exit(1);
  }

  return 1;
}

// Skip past input that we don't need to deal with,
// i.e. whitespace, newlines. Return the first
// character we do need to deal with.
static int skip(void) {
  int c;

  c = next();
  while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c) {
    c = next();
  }

  return (c);
}

// Get the next character from the input file.
static int next(void) {
  int c;

  if (Putback) {
    c = Putback;
    Putback = 0;
    return c;
  }

  c = fgetc(Infile);
  if ('\n' == c)
    Line++;

  return c;
}

// Put back an unwanted character
static void putback(int c) { Putback = c; }

// TODO: Make it so we can scan integer, long and throw error if number is too
// big.
static int scanint(int c) {
  int k, val = 0;

  // Convert each character into an int value
  while ((k = chrpos("0123456789", c)) >= 0) {
    val = val * 10 + k;
    c = next();
  }

  // We hit a non-integer character, put it back.
  putback(c);
  return val;
}

static int chrpos(char *s, int c) {
  char *p;

  p = strchr(s, c);
  return (p ? p - s : -1);
}

static int scanident(int c, char *buf, int lim) {
  int i = 0;

  // Allow digits, alpha and underscores
  while (isalpha(c) || isdigit(c) || '_' == c) {
    // Error if we hit the identifier length limit,
    // else append to buf[] and get next character
    if (lim - 1 == i) {
      printf("identifier too long on line %d\n", Line);
      exit(1);
    } else if (i < lim - 1) {
      buf[i++] = c;
    }
    c = next();
  }
  // We hit a non-valid character, put it back.
  // NUL-terminate the buf[] and return the length
  putback(c);
  buf[i] = '\0';
  return (i);
}

static int keyword(char *s) {
  switch (*s) {
  case 'p':
    if (!strcmp(s, "print"))
      return (T_PRINT);
    break;
  }
  return (0);
}

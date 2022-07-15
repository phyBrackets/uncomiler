#include "defs.h"
#include "data.h"
#include "decl.h"

// Return pos of char c in string s, or -1 if c not found 
static int chrpos(const char *s, int c) {
    const char *p ;

    p = std::strchr(s,c);
    return p?p-s:-1;
}


// Get the next character from the input file 
static int next(void) {
    int c=0;

    if(Putback) {
        c = Putback ;
        Putback = 0;
        return c;
    }

    c = fgetc(Infile); // Read from input 
    if(c == '\n')
      Line++;   // Increment line count 
  
  return c;
}

// Put back unwanted character 
static void putback(int c) {
    Putback = c;
}


// Skip past input that we don't need to deal with, whitespace,
// newlines. Return the first char we do need to deal with .

static int skip(void) {
    int c;
    do {
  c = next();
    }while(c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f');

  return c;
}

static int scanint(int c) {
    int tmp, Fint = 0;

    // convert ech char into an int 
    while((tmp = chrpos("0123456789", c)) >= 0) {
        Fint = Fint* 10 + tmp;
        c = next() ;
    }

    // if we hit a non int char, put it back in stream
    putback(c);
    return Fint ;
}

// Scan and return next token found in input . 
// Return 1 if token valid , 0 if no tokens left 

int scan (token *t) {
  int c;

  // skip unwanted chars
  c = skip();

  // Determine the token based on input 
  switch (c)
  {
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
      t->token = T_SLASH ;
      break;
    
    case EOF: 
      t->token = T_EOF;
      break;
    
    default: 
      // if it is digit 

      if(isdigit(c)) {
          t->intvalue = scanint(c);
          t->token =T_INTLIT;
          break;
      }
      // will add more

      std::cout << "Unrecognised character" << c << " on line " << Line << "\n";
      exit(1); 
  }

  return 1; // we found a token 
}
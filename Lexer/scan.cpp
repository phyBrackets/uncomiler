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
static int nextToken(void) {
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
  c = nextToken();
    }while(c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f');

  return c;
}

static int scanint(int c) {
    int tmp, Fint = 0;

    // convert ech char into an int 
    while((tmp = chrpos("0123456789", c)) >= 0) {
        Fint = Fint* 10 + tmp;
        c = nextToken() ;
    }

    // if we hit a non int char, put it back in stream
    putback(c);
    return Fint ;
}

// scan an identifier from the input file and 
// store it in buf[]. Return the identifier's length
static int scanident(int c, char *buf, int lim) {
  int i = 0;

  // allow digits, alpha and underscores 
   while(isalpha(c) || isdigit(c) || '_' == c) {
     // error if we hit the identifier limit,
     // else append to buf[] and get next character
     if(lim-1 == i){
      std::cout << "identifier too long on line " << Line << "\n";
      exit(1);
     } 
     else if(i < lim-1)
       buf[i++] = c;
    
    c = nextToken();
   }

   // we hit a non valid character, put it back.
   putback(c);
   buf[i] = '\0';
   return i;
}

//scan keyword
static int keyword(char *s) {
   switch(*s) {
     case 'p': 
      if(!strcmp(s, "print"))
        return (T_PRINT);
      break;
   }
   return 0;
}
// Scan and return next token found in input . 
// Return 1 if token valid , 0 if no tokens left 

int scanToken (token *t) {
  int c,tokentype;

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

    case ';':
      t->token = T_SEMI;
      break;
    
    default: 
      // if it is digit 

      if(isdigit(c)) {
          t->intvalue = scanint(c);
          t->token =T_INTLIT;
          break;
      } else if (isalpha(c) || '_' == c) {
        scanident(c, Text, TEXTLEN);

        if((tokentype = keyword(Text))) {
          t->token =  tokentype;
          break;
        }

        std::cout << "Unrecognised symbol " << Text << "on line " << Line;
        exit(1);
      }
      // will add more

      std::cout << "Unrecognised character" << c << " on line " << Line << "\n";
      exit(1); 
  }

  return 1; // we found a token 
}
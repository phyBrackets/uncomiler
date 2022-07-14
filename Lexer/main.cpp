#include "defs.h"
#include "data.h"
#include "decl.h"
#include <cerrno> 

// Init the global var 
static void init() {
    Line = 1;
    Putback = '\n';
}

// print out a usage if started incorrectly 
static void usage(char *pr) {
    std::cerr << "Usage " << pr << "infile"<<"\n" ;
    exit(1);
}

// List of tokens
 char const *tokstr[] = {"+", "-", "*", "/", "intlit"} ;

 static void scanfile() {
     token T; 

     while(scan(&T)) {
         std::cout << "Token " << tokstr[T.token] ;
         if(T.token == T_INTLIT)
           std::cout << "value " << T.intvalue << "\n" ;
     }
 }

int main(int argc, char** argv) {
  if(argc != 2)
    usage(argv[0]);

    init();

    if((Infile = fopen(argv[1], "r")) == NULL) {
      std::cerr << "Unable to open " << argv[1] << errno ;
      exit(1);
    }

    scanfile();
    exit(0);
}
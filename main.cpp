#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
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

int main(int argc, char* argv[]) {
  ASTNode *newast;
  if(argc != 2)
    usage(argv[0]);

    init();

    if((Infile = fopen(argv[1], "r")) == NULL) {
      std::cerr << "Unable to open " << argv[1] << errno ;
      exit(1);
    }

    scan(&Token);  // get the first token from the input
    newast = binexpr(0);  // parse the expression
    std::cout << interpretAST(newast) << "\n"; // calculate the final result

    exit(0);
}
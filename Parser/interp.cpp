#include "defs.h"
#include "data.h"
#include "decl.h"

// given an ast, interpret the operators in it and return
// a final value 

// List of AST operators
static const char *ASTop[] = { "+", "-", "*", "/" };


int interpretAST(ASTNode *n) {
    int leftval, rightval;

    // get the left and right subtree  value 
    if(n->left) 
      leftval = interpretAST(n->left);
    if(n->right)
      rightval = interpretAST(n->right);

    if(n->op == A_INTLIT)
      std::cout<<n->intvalue<<"\n";
    else 
      std::cout << leftval << " " << ASTop[n->op] <<" " << rightval << "\n" ;
    
     switch(n->op) {
        case A_ADD:
         return (leftval + rightval);
        case A_SUBTRACT:
         return (leftval - rightval);
        case A_MULTIPLY:
         return (leftval * rightval);
        case A_DIVIDE:
         return (leftval / rightval);
        case A_INTLIT:
         return (n->intvalue);
        default:
         std::cerr<< "unknown ast operator\n" << n->op ;
        exit(1);
     }
}
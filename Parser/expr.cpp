#include "defs.h"
#include "data.h"
#include "decl.h" 

// parse a factor and return the corresponding ast node
static ASTNode *parsefactor(void) {
    ASTNode *newastnode;
   
   // for an integer literal token, make a leaf ast node for it 
   // and scan in the next token.
    switch(Token.token){
        case T_INTLIT:
        newastnode = buildastleaf(A_INTLIT, Token.intvalue);
        scan(&Token);
        return (newastnode);
        default:
         std::cerr<<"syntax error on line \n" << Line ;
         exit(1);
    }
}
// convert a token into corresponding ast operation 
int arithmeticop(int tok) {
    switch(tok) {
        case T_PLUS:
          return (A_ADD);
        case T_MINUS:
          return (A_SUBTRACT);
        case T_STAR:
          return (A_MULTIPLY);
        case T_SLASH:
           return(A_DIVIDE);
        default:
          std::cerr<< "unknown token on line \n" << Line << tok;
          exit(1);
    }
}

// Return an AST tree whose root is a binary op

ASTNode *binexpr(void) {
    ASTNode *n, *left, *right ;
    int nodetype;

    //get the integer literal on the left 
    // fetch the next token at same time
    left = parsefactor();

    // if no token left, return just the left node
    if (Token.token == T_EOF)
      return (left);

    //convert the token into a node type 
    nodetype = arithmeticop(Token.token);

    //Get the next token 
    scan(&Token);

    // Recursively get the right hand side 
    right = binexpr();

    // now build a tree with both sub tree 
    n = buildastnode(nodetype, left, right, 0);
    return (n);
}
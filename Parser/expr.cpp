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
          std::cerr<< "unknown token on line " << Line << "," << tok;
          exit(1);
    }
}


// operator precedence for each token 

static int OpPrec[] = {0,10,10,20,20,0} ;
// eof + - * / intlit

static int op_precedence(int tokentype) {
  int prec = OpPrec[tokentype] ;
  if(prec==0) {
    std::cerr << "syntax error on line" << Line << tokentype << "\n";
    exit(1);
  }

  return prec;
}
// Return an AST tree whose root is a binary op
// parameter previoustokenprec 
ASTNode *binexpr(int previoustokenprec) {
    ASTNode *n, *left, *right ;
    int tokentype;

    //get the integer literal on the left 
    // fetch the next token at same time
    left = parsefactor();
    
    // if no token left, return just the left node
    tokentype = Token.token;
    if (tokentype == T_EOF)
      return (left);
    
    // while the precedence of this token is
    // moore than that of the previous token precedence 
    while(op_precedence(tokentype) > previoustokenprec) {
      // fetch the next int literal 
      scan(&Token);

      right = binexpr(OpPrec[tokentype]);

      left = buildastnode(arithmeticop(tokentype), left, right, 0);
      
      tokentype = Token.token;
      if(Token.token == T_EOF)
        return left;
    }

    return left;
}
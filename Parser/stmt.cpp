#include "defs.h"
#include "decl.h"
#include "data.h" 

// parse one or more statements
void statements(void) {
    ASTNode *tree;
    int reg;

    while(1) {
    // match a 'print' as the first token 
    match(T_PRINT, "print");

    //parse the expression  and 
    // gen assembly code 
    tree = binexpr(0);
    reg = genAST(tree);
    genprintint(reg);
    genfreeregs();

    // match semicolon 
    semi();
    if(Token.token == T_EOF)
    return;
    }
}
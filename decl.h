int scanToken(token *t); 
ASTNode *buildastnode(int op, ASTNode *left, 
                      ASTNode *right, int intvalue); 
ASTNode *buildastleaf(int op, int intvalue);
ASTNode *buildastsinglechild(int op, ASTNode *left, int value);
ASTNode *binexpr(int rbp);
int interpretAST(ASTNode *n);
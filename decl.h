int scan(token *t); 
ASTNode *buildastnode(int op, ASTNode *left, 
                      ASTNode *right, int intvalue); 
ASTNode *buildastleaf(int op, int intvalue);
ASTNode *buildastsinglechild(int op, ASTNode *left, int value);
ASTNode *binexpr(void);
int interpretAST(ASTNode *n);
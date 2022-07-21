int scanToken(token *t); 
ASTNode *buildastnode(int op, ASTNode *left, 
                      ASTNode *right, int intvalue); 
ASTNode *buildastleaf(int op, int intvalue);
ASTNode *buildastsinglechild(int op, ASTNode *left, int value);

int genAST(ASTNode *n);
void genpreamble();
void genpostamble();
void genfreeregs();
void genprintint(int reg);


void freeall_registers(void);
void cgpreamble();
void cgpostamble();
int cgload(int value);
int cgadd(int r1, int r2);
int cgsub(int r1, int r2);
int cgmul(int r1, int r2);
int cgdiv(int r1, int r2);
void cgprintint(int r);

ASTNode *binexpr(int ptp);

void statements(void);

void match(int t, std::string what);
void semi(void);
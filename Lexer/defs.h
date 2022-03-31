#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cstdio>
#include <iostream>
int scan(struct token *t);
// Tokens 
enum {
    T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT
};

// Token structure
struct token {
 int token;
 int intvalue;
};

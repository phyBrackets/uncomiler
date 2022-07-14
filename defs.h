#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cstdio>
#include <iostream>
int scan(class token *t);
// Tokens 
enum {
    T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT
};

// Token class
class token {
public: 
 int token;
 int intvalue;
};

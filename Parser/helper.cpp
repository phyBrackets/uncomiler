#include "defs.h"
#include "data.h"
#include "decl.h"


void match(int t, std::string what) {
    if(Token.token == t) {
        scanToken(&Token);
    }else {
        std::cout << what << "expected on line " << Line ;
        exit(1); 
    }
}

void semi(void) {
    match(T_SEMI, ";");
}
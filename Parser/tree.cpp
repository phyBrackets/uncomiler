#include "defs.h"
#include "data.h"
#include "decl.h"

// build and return a ast node 
ASTNode *buildastnode(int op, ASTNode *left,
                      ASTNode *right, int intvalue) {
   
   ASTNode *newASTNode; 

   newASTNode = new ASTNode;
   if(newASTNode == NULL) {
       std::cerr << "Unable to malloc buildastnode()" << std::endl ;
       exit(1);
   }

   // Copy the fields and return 

   newASTNode->op = op;
   newASTNode->left = left;
   newASTNode->right = right;
   newASTNode->intvalue = intvalue ;
   return (newASTNode);
}

// Make AST leaf node
ASTNode *buildastleaf(int op, int intvalue) {
    return (buildastnode(op, NULL, NULL, intvalue));
}

// Make with one Child 
ASTNode *buildastsinglechild(int op, ASTNode *left, int intvalue) {
    return (buildastnode(op, left, NULL, intvalue));
}


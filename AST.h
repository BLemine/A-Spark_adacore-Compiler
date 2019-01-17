#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
    OP=0,IDF=1,NUM=2
}typeExp;
typedef enum{
  PLUS=0,MINUS=1,MULT=2,DIV=3  
}typeOP;
typedef enum{
    false=0,true=1
}boolean;

struct Exp;
typedef struct Exp *AST;

/* functions */
boolean aTree(AST a);
AST getLeftTree(AST a);
AST getRightTree(AST a);
void createLeavesNumber(AST a,double nbr);
void createLeavesIdf(AST a, char* idf);
AST createNodeOper(AST aRight,AST aLeft,typeOP oper);
void printTreePostOrder(AST a);
/********************************/
/*
struct node{
  int nodeInt;  
  char nodeChar;
  char* nodeIdf;
  typeOP root;
  AST left;
  AST right;
};*/
// to identify the type of values 
typedef union {
    double nodeInt;
    char * idf;
    struct {
        typeOP root;    // PLUS, MINUS, MULT, or DIV
        AST left;
        AST right;
    }op;
}typeNode;
///////////////////////////
// this structure below describe nodes 
struct Exp{
    typeExp type;   // to define the type of the actual node (OP, NUM or IDF)
    typeNode node; // for nodes, it means that a node has to be either an OP,or IDF or NUM or even another Tree in the case where the root is an OP
};
////////////////////////////
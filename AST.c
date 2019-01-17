#include "AST.h"

boolean aTree(AST a){
    if(a->type!=OP){    // the root should be an OP like PLUS,MINUS ..
        return true;
    }
    else return false;
}
AST getLeftTree(AST a){
    if(aTree(a)){
        return a->node.op.left;
    }
    else return NULL;
}
AST getRightTree(AST a){
    if(aTree(a)){
        return a->node.op.right;
    }
    else return NULL;
}
typeOP getFirstRoot(AST a){
    if(aTree(a)){
        return a->node.op.root;
    }
}
void createLeavesNumber(AST a,double nbr){
    if(aTree(a)){
        a->type=NUM;
        a->node.nodeInt=nbr;
    }
}
void createLeavesIdf(AST a,char *idf){
    if(aTree(a)){
        a->type=IDF;
        a->node.idf=malloc(strlen(idf)*sizeof(char));
        a->node.idf=idf;
    }
}
AST createNodeOper(AST aRight,AST aLeft,typeOP oper){
        AST a=malloc(sizeof(AST));
        a->type=OP;
        a->node.op.root=oper;
        a->node.op.left=aLeft;
        a->node.op.right=aRight;
        return a;
}
//postfixe : GDR -> (Left,Right,Root)
void printTreePostOrder(AST a){
    switch(a->type){
        case OP:
            printTreePostOrder(a->node.op.left);
            printTreePostOrder(a->node.op.left);
            switch(a->node.op.root){
                case PLUS:
                    printf("+");
                    break;
                case MINUS:
                    printf("-");
                    break;
                case MULT:
                    printf("*");
                    break;
                case DIV:
                    printf("/");
                    break;
            }
            break;
        case NUM:
            printf("%d",a->node.nodeInt);
            break;
        case IDF:
            printf("%s",a->node.idf);
            break;
    }
}
int main()
{
    printf("Hello, AST!\n");

    return 0;
}
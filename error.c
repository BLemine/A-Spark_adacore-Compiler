#include "error.h"

static warning *warnTb[lenghtWarn];

static error *errTb[lenghtErr];

void printError(error *er){
    switch(er->type){
        case  varNotDeclared:
            printf("%s %d de type : variable non declarée\n",er->name,*er->line);
            break;
        case varAlreadyDec:
            printf("%s %d de type : variable déjà declarée\n",er->name,*er->line);
            break;
        case varBadlyDeclared:
            printf("%s %d de type : variable mal declarée\n",er->name,*er->line);
            break;
        case IncompatibAssign:
            printf("%s %d de type : Incompatibilité de types\n",er->name,*er->line);
            break;
        case IncompatibOper:
            printf("%s %d de type : Incompatibilité dans l'opération\n",er->name,*er->line);
            break;
        case varOutIn:
            printf("%s %d de type : variable non declarée\n",er->name,*er->line);
            break;
    }
}

int getLastIndex(error *err[lenghtErr]){
    int i=0;
    int LastIndex = 0;
    while(i<lenghtErr){
        if(strlen(err[i]->name)==0){
            LastIndex=i;
            break;
        }
        i++;
    }
    return LastIndex;
}

void createErrTb(error *err[lenghtErr]){
    for(int i=0;i<lenghtErr;i++){
        err[i]=malloc(sizeof(error));
        err[i]->name=malloc(20*sizeof(char));
        err[i]->line=malloc(sizeof(int));
    }
}
void appendError(error *err[lenghtErr],char *name,int line, errorType type){
    strcpy(err[getLastIndex(err)]->name,name);
    err[getLastIndex(err)]->line=&line;
    err[getLastIndex(err)]->type=type;
}
int main()
{
    printf("Hello, here's Errors management !\n");

    return 0;
}
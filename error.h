#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define lenghtErr 20
#define lenghtWarn 20

typedef enum{
    varNotUsed=0,
    InstAfterInfLoop=1,
    varNotChanged=2 // it's better in this case to make it as constant in Spark
}warningType;

typedef struct {
    char *name;
    int *line;
    warningType type;
}warning;

typedef enum{
    varNotDeclared=0,
    varAlreadyDec=1,
    varBadlyDeclared=2,
    IncompatibAssign=3,
    IncompatibOper=4,
    varOutIn=5
}errorType;

typedef struct {
    char *name; // in general it's kinda : an error at the line "line number"
    int *line;
    errorType type;
}error;

/********** functions ********/
void printError(error *er);
int getLastIndex(error *err[lenghtErr]);
void createErrTb(error *err[lenghtErr]);
void appendError(error *err[lenghtErr],char *name,int line,errorType type);
///////////////////////////////
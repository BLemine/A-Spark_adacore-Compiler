#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tailleTS 100

typedef enum {
    false=0,
    true=1
}boolean;

typedef enum {
    BOOL=0,
    NATURAL=1,
    FLOAT=2,
    POSITIVE=3,
    INTEGER=4,
    STRING=5,
    CHAR=6
}Types;

typedef enum {
    LOCAL=0,
    GLOBAL=1
}scope;

struct varType;
typedef struct varType *varTypeTb;  // this is a table of the "varType" structure
typedef struct varType *varTypeVr;  // this is just a pointer on the structure
static varTypeTb TS;    // this one is the table of symboles
///
struct varType *newTab[10];
///
struct varType{
    Types type;
    char *name;
    int *line;
};

// this function is used to search for a variable in the TS
varTypeVr searchTS(char *var,int line){
    varTypeVr getVar=malloc(sizeof(varTypeVr));
    for(int i=0;i<tailleTS;i++){
        if((TS+i) !=NULL){
            if (strcmp( ((TS+i)->name),var )==0){
                getVar->type=(TS+i)->type;
                strcpy(getVar->name,var);
                getVar->line =&line;
            }
        }
    }
    return getVar;
}

// this function is used just to get if the var is in the TS or not
boolean inTS(char *var,int line){
    /*if(searchTS(var,line)!=NULL){
        printf("the variable is already declared at the line : %d\n",*searchTS(var,line)->line);
        return true;
    }
    else return false;*/
    return false;
}
///// an aux funtion to get the last index of the TS
int getLastIndex(varTypeTb TS){
    int i=0;
    int LastIndex = 0;
    while(i<tailleTS){
        if((TS+i)!=NULL){
            continue;
        }
        else if((TS+i)==NULL){
            LastIndex=i;
            break;
        }
        i++;
    }
    return LastIndex;
}
// this function is to append a variable structure to the TS
void appendTS(char *name,int line,Types type){
    if(inTS(name,line)==false){
        // code to append a variable structure to the TS
        /*strcpy((TS+getLastIndex(TS))->name,name);
        (TS+getLastIndex(TS))->line=&line;
        (TS+getLastIndex(TS))->type=type;*/
        //////////
        strcpy((newTab[0])->name,name);
        (newTab[0])->line=&line;
        (newTab[0])->type=type;
    }
}
// tp print the TS content in case we need that
void printTS(varTypeTb TS){
    for(int i=0;i<tailleTS;i++){
        if((TS+i)!=NULL){
            // code to print the content 
            printf("****** display of TS : ***********\n");
            printf("NAME : %s\n",(TS+i)->name);
            switch ((TS+i)->type)
            {
                case BOOL:
                    printf("TYPE : boolean\n");
                    break;
                case FLOAT:
                    printf("TYPE : float\n");
                    break;
                case NATURAL:
                    printf("TYPE : natural\n");
                    break;
                case POSITIVE:
                    printf("TYPE : positive\n");
                    break;
                case INTEGER:
                    printf("TYPE : integer\n");
                    break;
                case STRING:
                    printf("TYPE : String\n");
                    break;
                case CHAR:
                    printf("TYPE : char\n");
                    break;
                default:
                    printf("It was about displaying the TS\n");
                    break;
            }
        }
    }
}
// to create the TS sure
void createTS(varTypeTb ts){
    ts=malloc(tailleTS*sizeof(varTypeVr));
    ts->name=malloc(20*sizeof(char));
    ts->line=malloc(sizeof(int));
}
/************************************ NOTE : ****************************/
// with newTab it worked , till now 
/************************************************************************/
void main(){
    //TS=malloc(tailleTS*sizeof(varTypeVr));
    newTab[0]=malloc(sizeof(varTypeVr));
    newTab[0]->name=malloc(10*sizeof(char));
    newTab[0]->line=malloc(sizeof(int));
    //createTS(TS);
    Types t1=FLOAT;
    char *str=malloc(10*sizeof(char));
    //strcpy(str,"var1");
    appendTS("var1",1,t1);
    //printTS(TS);
    printf("here's the SymbTable \n");
}
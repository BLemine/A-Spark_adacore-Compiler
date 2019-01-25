#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tailleTS 10

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
typedef struct varType *tabTS[10];
struct varType *newTab[10];
///
struct varType{
    Types type;
    char *name;
    int *line;
};

// this function is used to search for a variable in the TS
varTypeVr searchTS(char *varname){
    varTypeVr getVar=malloc(sizeof(varTypeVr));
    getVar->name=malloc(10*sizeof(char));
    getVar->line=malloc(sizeof(int));
    /*for(int i=0;i<tailleTS;i++){
        if((TS+i) !=NULL){
            if (strcmp( ((TS+i)->name),varname )==0){
                getVar->type=(TS+i)->type;
                strcpy(getVar->name,varname);
                getVar->line =&line;
            }
        }
    }*/
    /// the second way :
    for(int i=0;i<10;i++){
        if(newTab[i]!=NULL){
            if(strcmp(newTab[i]->name,varname)==0 ){
                getVar->type=newTab[i]->type;
                strcpy(getVar->name,varname);
                getVar->line=newTab[i]->line;
            }

        }
    }
    if(strlen(newTab[1]->name)!=0)
    printf("%s\n",newTab[1]->name);
    ///////////////
    return getVar;
}

// this function is used just to get if the var is in the TS or not
boolean inTS(char *varname){
    // here comes the segmentation fault but solved hh but just got off by taking off '*' from *searchTS(varname)->line
    //printf("test %s\n",searchTS(varname)->name);
    boolean result=false;
    if(strlen(searchTS(varname)->name)!=0)
    /*if(searchTS(varname)->name!=NULL)*/{
        /************ NOTE : ************************/
        // the declaration of line  depends i mean we can get it either by getting the index of line in the tabTS
        // or by getting it as a parameter of the function , this last one if better when it comes to use it in analyzer.c
        /********************************************/
        printf("the variable %s is already declared at the line : %d\n",searchTS(varname)->name,*searchTS(varname)->line);
        result= true;
    }
    else result= false;
    return result;
}
///// an aux funtion to get the last index of the TS
int getLastIndex(tabTS TS){
    int i=0;
    int LastIndex = 0;
    while(i<10){
        if(strlen(TS[i]->name)==0 /*from here comes the prob and it's solved by fixing an index look at the apped func && TS[i]->line==0 && TS[i]->type!=?*/){
            LastIndex=i;
            break;
        }
        i++;
    }
    /*
    for(int j=0;j<10;j++){
        if(TS[j]==NULL){
            LastIndex=j;
            break;
        }
    }*/
    return LastIndex;
}
// this function is to append a variable structure to the TS
void appendTS(char *name,int *line,Types type){
    //if(newTab[getLastIndex(newTab)]!=NULL)
    if(inTS(name)==false){
        // code to append a variable structure to the TS
        /*strcpy((TS+getLastIndex(TS))->name,name);
        (TS+getLastIndex(TS))->line=&line;
        (TS+getLastIndex(TS))->type=type;*/
        //////////
        int index=getLastIndex(newTab);
        strcpy((newTab[index])->name,name);
        (newTab[index])->line=line;
        (newTab[index])->type=type;
        printf("The variable %s was inserted at %d\n",newTab[index]->name,*newTab[index]->line);
    }
    else{
        //printf("Variable already exist \n");
    }
    //printf("the LastIndex is :%d\n",getLastIndex(newTab));
}
// tp print the TS content in case we need that
void printTS(tabTS TS){
    printf("****** displaying TS : ***********\n");
    for(int i=0;i<tailleTS;i++){
        if(strlen(TS[i]->name)!=0){
            // code to print the content 
            printf("NAME : %s\n",TS[i]->name);
            printf("LINE : %d\n",*TS[i]->line);
            switch (TS[i]->type)
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
               printf("****** displaying TS : ***********\n");     break;
                case CHAR:
                    printf("TYPE : char\n");
                    break;
                default:
                    printf("It was about displaying the TS\n");
                    break;
            }
            printf("-----------------------\n");
        }
    }
}
// to create the TS sure
void createTS(tabTS ts){
    /*
    ts=malloc(tailleTS*sizeof(varTypeVr));
    ts->name=malloc(20*sizeof(char));
    ts->line=malloc(sizeof(int));
    */
    /// the second way :
    /*ts[0]=malloc(sizeof(varTypeVr));
    ts[0]->name=malloc(10*sizeof(char));
    ts[0]->line=malloc(sizeof(int));*/
    ///////
    for(int i=0;i<10;i++){
        ts[i]=malloc(sizeof(varTypeVr));
        ts[i]->name=malloc(10*sizeof(char));
        ts[i]->line=malloc(sizeof(int));
    }
    //
/*    strcpy((newTab[0])->name,"ccac");
    Types t=BOOL;
    int l=32;
    (newTab[0])->line=&l;
    (newTab[0])->type=t;
*/
}
/************************************ NOTE : ****************************/
// with newTab it worked , till now 
/************************************************************************/
void main(){
    //TS=malloc(tailleTS*sizeof(varTypeVr));
    /*newTab[0]=malloc(sizeof(varTypeVr));
    newTab[0]->name=malloc(10*sizeof(char));
    newTab[0]->line=malloc(sizeof(int));*/
    createTS(newTab);
    Types t1=FLOAT;
    //char *str=malloc(10*sizeof(char));
    //strcpy(str,"var1");
    //appendTS("var1",45,t1);
    int a=21;
    int b=32;
    appendTS("var1",&a,t1);
    appendTS("caca",&b,t1);
    //printf("%s at %d %s at %d\n",newTab[0]->name,*newTab[0]->line,newTab[1]->name,*newTab[1]->line);
    printTS(newTab);
    printf("here's the SymbTable \n");
}
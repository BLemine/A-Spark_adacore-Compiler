#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "error.h"

error * err;
static error * errors;
static int cpt=0;

void create_error(int lineErr,char *typeErr,char *tokenErr){
    strcpy(err->type,typeErr);
    strcpy(err->text,tokenErr);
    err->line=lineErr;
    *(errors+cpt)=*err;
    cpt++;
}
char * getError(){
    char * strErr=malloc(100*sizeof(char));
    char *auxLine=malloc(10*sizeof(char));
    strcat(strErr,err->type);strcat(strErr,"Error");
    strcat(strErr," : ");
    strcat(strErr,err->text);
    sprintf(auxLine,"%d",(err->line));
    strcat(strErr," at line number ");strcat(strErr,auxLine);
    return strErr;
}
int nbr_sm_errors(char * tab){
    return 0;
}
char * print_sm_error(int line,char * error){
    printf("%s %d",error,line);
}
void main(){
    errors=malloc(1024*sizeof(char));
    /*for(int j=0;j<1024;j++){
        (errors+j)->type=NULL;
        (errors+j)->text=NULL;
        (errors+j)->line=0;
    }*/
        
    err=malloc(sizeof(error));
    err->type=malloc(100*sizeof(char));
    err->text=malloc(100*sizeof(char));

    create_error(1,"semantic","la var blabla ..");
    printf("%s\n",getError());
    create_error(45,"syntaxic","coucou gregoire ..");
    printf("%s\n",getError());
    
    /*for(int i=0;i<10;i++)
        //if(((errors+i)->text)!=NULL)
            printf("%s\n",(errors+i)->text);*/
    //printf("%d",cpt);
}
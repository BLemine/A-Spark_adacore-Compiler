#include <stdio.h>
#include <stdlib.h>
#include <string.h>
////////// boolean enum
typedef enum {
	false=0, 
	true=1
	} boolean;
/////////////////////////
/// tokens enum
typedef enum {
    NUM =100,
    PLUS=101,
    MINUS=102,
    MULT=103,
    DIV=104,
    TYPE=105,
    PACK=106,
    SPARK_Mode=107,
    WITH=108,
    USE=109,
    IS=110,
    PROC=111,
    BEG_IN=112,
    END=113,
    LOOP=114,
    PUT=115,
    GET=116,
    PUT_LINE=117,
    GET_LINE=118,
    IF=119,
    ELSE=120,
    RECORD=121,
    WHILE=122,
    FOR=123,
    NATURAL=124,
    IN=125,
    OUT=126,
    NEW=127,
    RETURN=128,
    PRIVATE=129,
    STRING=130,
    CHAR=131,
    FLOAT=132,
    INTEGER=133,
    POINT=134,
//    DEF_TYPE_VAR=135,
    PT_ASSIGN=135,	
    PT_COMMA=136,
    COMMA=137,
    APPOST=138,
    AFFECT=139,
    TAB=140,
    POPEN=141,
    PCLOSE=142,
    SUP=143,
    INF=144,
    IDF=145,
    CONSTANT=146, // this key is used for another objective 
    FUNC=147,
    GUILL=148,
    COMMENT=149,
    /// 2401-19
    IDFPACK=150,
    BODY=151

} typetoken;

typedef struct {
    int *line;
    char *expectedIDF;
}syntaxErr;

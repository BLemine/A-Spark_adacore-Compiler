%{
#include "analyseur.h"
#define debug true

%}
%option noyywrap
%option yylineno

%%
[0-9]+  {return NUM;}
    
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MULT;}
"/" {return DIV;}
    
"type" {return TYPE;}
"package" {return PACK;}
"SPARK_Mode" {return SPARK_Mode;}
"with"|"WITH" {return WITH;}
"use" {return USE;}
"is" {return IS;}
"procedure" {return PROC;}
"function" {return FUNC;}
"begin" {return BEG_IN;}
"end" {return END;}
"loop" {return LOOP;}
"body" {return BODY;}
    
"put" {return PUT;}
"get" {return GET;}
"put_line" {return PUT_LINE;}
"get_line" {return GET_LINE;}
    
"if" {return IF;}
"else" {return ELSE;}
"record" {return RECORD;}
"while" {return WHILE;}
"for" {return FOR;}
"Natural" {return NATURAL;}
"in" {return IN;}
"out" {return OUT;}
"new" {return NEW;}
"return" {return RETURN;}
"private" {return PRIVATE;}
    
"constant" {return CONSTANT;}
    
"String" {return STRING;}
"Character" {return CHAR;}
"float" {return FLOAT;}
"Integer" {return INTEGER;}

"." {return POINT;}
":" {return PT_ASSIGN;}
";" {return PT_COMMA;}
"," {return COMMA;}
"'" {return APPOST;}
"\"" {return GUILL;}
":=" {return AFFECT;}
"_" {return TAB;}
"(" {return POPEN;}
")" {return PCLOSE;}
"<" {return SUP;}
">" {return INF;}
"--"(.)* {return COMMENT;}
(([a-zA-Z]+)"."([a-zA-Z]+)"_")+	{return IDFPACK;}

[a-zA-Z_][a-zA-Z0-9_]*  {return IDF;}

" "*|[\n\t]*  //will not treat it at all

.   {printf("%s is not defined as a token at line %d\n",yytext,yylineno);}
%%

%{
	#include <stdio.h>
    #include<string.h>
    #include<errno.h>
    #include "yacc.tab.hpp"    /* token codes from the parser */ 
    int yylex();
    void yyerror (const char* s);
    extern int errno;
    int yycolno  = 0;
    int prevleng = 0;
    #define YY_USER_ACTION {yylloc.first_line = yylloc.last_line = yylineno; yylloc.last_column = yycolno;}
%}

%option nounput yylineno

UNICODE_LETTER			[a-zA-Z]
LETTER				    [a-zA-Z_]
DIGIT				    [0-9]
UNICODE_CHAR			[^\n]
NEW_LINE			    [\n]
BOOL_CONST			    "true"|"false"
NIL_VAL				    "nil"
WHITESPACE              [\t\r\f\v]+
%%

"+"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_PLUS;}
"-"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_MINUS;}
"*"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_MULTIPLY;}
"/"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_DIVIDE;}
"%"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_MOD;}

"&"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_BIT_AND;}
"|"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_BIT_OR;}
"^"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_BIT_XOR;}
"<<"			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_SHIFT_LEFT;}
">>"			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_SHIFT_RIGHT;}
"&^"			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_AND_XOR;}

"+="			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_PLUS_EQ;}
"-="			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_MINUS_EQ;}
"*="			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_MULTIPLY_EQ;}
"/="			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_DIVIDE_EQ;}
"%="			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_MOD_EQ;}

"&="			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_BIT_AND_EQ;}
"|="			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_BIT_OR_EQ;}
"^="			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_XOR_EQ;}
"<<="			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_SHIFT_LEFT_EQ;}
">>="			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_SHIFT_RIGHT_EQ;}
"&^="			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_AND_XOR_EQ;}

"&&"			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_AND;}
"||"			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_OR;}
"<-"			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_ARROW;}
"++"			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_INCREMENT;}
"--"			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_DECREMENT;}

"=="			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_DOUBLE_EQ;}
">"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_GREATER;}
"<"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_LESSER;}
"="				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_EQ;}
"!"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_NOT;}
"~"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_TILDE;}

"!="			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_NOT_EQ;}
"<="			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_LESSER_EQ;}
">="			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_GREATER_EQ;}
":="			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_DECL_EQ;}
"..."			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_ELLIPSIS;}

"("				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_LEFT_PARANTHESES;}
"["				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_LEFT_BRACKET;}
"{"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_LEFT_BRACE;}
","				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_COMMA;}
"."				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_PERIOD;}

")"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_RIGHT_PARANTHESES;}
"]"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_RIGHT_BRACKET;}
"}"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_RIGHT_BRACE;}
";"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_SEMICOLON;}
":"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_COLON;}

"break"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_BREAK;} 
"case"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_CASE;} 
"chan"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_CHAN;} 
"const"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_CONST;} 
"continue"			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_CONTINUE;} 
"default"			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_DEFAULT;} 
"defer"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_DEFER;} 
"else"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_ELSE;} 
"fallthrough"		{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_FALLTHROUGH;} 
"for"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_FOR;} 
"func"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_FUNC;} 
"go"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_GO;} 
"goto"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_GOTO;} 
"if"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_IF;} 
"import"			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_IMPORT;} 
"interface"			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_INTERFACE;} 
"map"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_MAP;} 
"package"			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_PACKAGE;} 
"range"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_RANGE;} 
"return"			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_RETURN;} 
"select"			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_SELECT;} 
"struct"			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_STRUCT;} 
"switch"			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_SWITCH;} 
"type"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_TYPE;} 
"var"				{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_VAR;} 

{BOOL_CONST}		{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_BOOL_CONST;}
{NIL_VAL}			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_NIL_VAL;}


{LETTER}({LETTER}|{DIGIT})*	{    
    if(strlen(yytext)<=32)
        {yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_IDENTIFIER;}
    else
    {
        printf ("\033[0;31m Line:%d | Identifier too long,must be between 1 to 32 characters \n\033[0m\n",yylineno);
        char newid[32];
        strncpy(newid,yytext,32);
        printf ("\033[0;36m Error handled , Identifier name %s replaced by %s \n\033[0m\n",yytext,newid);
        yylval.sval= strdup(newid);yycolno+=prevleng; prevleng=strlen(newid);return T_IDENTIFIER;
    }
}
{DIGIT}+({LETTER}|_)+  {yycolno+=prevleng; prevleng=yyleng; yyerror("Lexical Error : Illegal identifier format\n");}

{DIGIT}+			{yylval.sval= strdup(yytext);yycolno+=prevleng; prevleng=yyleng;return T_INTEGER;}
{DIGIT}+"."{DIGIT}+		{ yylval.sval= strdup(yytext); yycolno+=prevleng; prevleng=yyleng;return T_FLOAT;}

\"([^\"\n\"]|(\\.))*$   { yycolno+=prevleng; prevleng=yyleng; yyerror("Lexical Error : Badly Terminated String\n");}
\"([^\\\n\"]|(\\.))*\"	{ yycolno+=prevleng; prevleng=yyleng; yylval.sval= strdup(yytext);return T_STRING;}

\'{UNICODE_CHAR}\' { yycolno+=prevleng; prevleng=yyleng; yylval.sval= strdup(yytext);return T_BYTE;}

\/\/{UNICODE_CHAR}*\n		{yycolno=0; prevleng=0;}

{NEW_LINE}          {yycolno=0;prevleng=0;}
"\t"				{yycolno+=prevleng; prevleng=4;};
" "                 {yycolno+=prevleng; prevleng=1;}
{WHITESPACE}		;
. {yyerror("Lexical error : Unidentified token");}

%%

int yywrap()
{
    printf("Input Exhausted!\n");
    return 1;
}

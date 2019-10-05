%{
    #include <stdio.h>
    #include <iostream>
    #include "Scanner.h"
    int _column = 0;
    #define YY_USER_ACTION { \
    _column += YYLeng(); \
    printf("[%i]", _column ); \
    } \
 
%}
%option noyywrap
%option c++
%option yyclass="MyScanner"


T_ANTI       "!"
T_LESS       "<"
T_EQ         "="
T_DIV        "/"
T_MUL        "*"
T_MINUS      "-"
T_PLUS       "+"
T_RPARENTH   ")"
T_LPARENTH   "("
T_RBRACKET   "]"
T_LBRACKET   "["
T_RBRACE     "}"
T_LBRACE     "{"
T_SEMI	     "."
T_COMMA	     ","
T_DOT	     "."
T_AND        "&&"
T_OR         "||"
T_CLASS      "class"
T_PUBLIC     "public"
T_PRIVATE    "private"
T_STATIC     "static"
T_VOID       "void"
T_MAIN       "main"
T_EXTENDS    "extends"
T_RETURN     "return"
T_IF         "if"
T_ELSE       "else"
T_WHILE      "while"
T_SOUT       "System.out.println"
T_LENGTH     "length"
T_NEW        "new"
T_THIS       "this"
T_TRUE       "true"
T_FALSE      "false"
T_STRING     "String"
T_BOOLEAN    "boolean"
T_INT        "int"

T_DIGIT [0-9]
T_LETTER [a-zA-Z_]
T_INTEGER_LITERAL [1-9]{T_DIGIT}*|0
T_LOGIC_LITERAL {T_TRUE}|{T_FALSE}
T_ID {T_LETTER}({T_DIGIT}|{T_LETTER})*
T_COMMENT \/\/(.)*\n
T_SPACE		(" "|"\v"|"\r")+

%%

{T_SPACE}    { printf("SPACE ");}
{T_LPARENTH}    { printf("LB "); }
{T_RPARENTH}    { printf("RB "); }
{T_OR}	{ printf("OR "); }

.     { printf("UNKNOWN ");}
%%

%{
    #include <stdio.h>
    #include <iostream>
    #include <string>     
    #include "Scanner.h"
    #include "common.h"

    location loc;
    #define YY_USER_ACTION { \
	loc._line_last = loc._line; \
        loc._column_last = loc._column; \
        for ( int i = 0; YYText()[i] != '\0'; i++ ) {\
            if ( YYText()[i] == '\n' ) { \
                loc._line++; \
                loc._column = 1; \
            } else if (YYText()[i] == '\t') { \
                loc._column += 4; \
            } else { \
                loc._column ++; \
            } \
        } \
    } \

    void print_data(bool flag, std::string name, std::string data, location loc) {
    	if (flag) {
	    if (data != "-1") {
 	        std::cout << name << "[" << data << "]" << " Line (" <<loc._line_last << ":" << loc._line << ")" << " Column (" << loc._column_last << ":" << loc._column << ")" << std::endl;
	    } else {
		std::cout << name << " Line (" <<loc._line_last << ":" << loc._line << ")" << " Column (" << loc._column_last << ":" << loc._column << ")" << std::endl;
	    }
	}
    }

 
%}
%option noyywrap
%option yylineno
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
T_SEMI	     ";"
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
T_NUM [1-9]{T_DIGIT}*|0
T_ID {T_LETTER}({T_DIGIT}|{T_LETTER})*
T_COMMENT 	\/\/(.)*\n
T_SPACE		(" "|"\v"|"\r")+
COMMENT		"//".*""

%%

{T_LBRACKET}    { std::string symbol = "LBRACKET"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_RBRACKET}    { std::string symbol = "RBRACKET"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_OR}		{ std::string symbol = "OR"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_DOT} 	{ std::string symbol = "DOT"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_COMMA}	{ std::string symbol = "COMMA"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_SEMI} 	{ std::string symbol = "SEMI"; std::string data = "-1"; print_data(1, symbol, data, loc); }

{T_LBRACE} 	{ std::string symbol = "LBRACE"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_RBRACE}  	{ std::string symbol = "RBRACE"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_LPARENTH}  	{ std::string symbol = "LPARENTH"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_RPARENTH} 	{ std::string symbol = "RPARENTH"; std::string data = "-1"; print_data(1, symbol, data, loc); }

{T_TRUE} 	{ std::string symbol = "LOGICAL_TRUE"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_FALSE} 	{ std::string symbol = "LOGICAL_FALSE"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_THIS} 	{ std::string symbol = "THIS"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_NEW} 	{ std::string symbol = "NEW"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_INT} 	{ std::string symbol = "INT"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_IF} 		{ std::string symbol = "IF"; std::string data = "-1"; print_data(1, symbol, data, loc);  }
{T_ELSE} 	{ std::string symbol = "ELSE"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_WHILE} 	{ std::string symbol = "WHILE"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_SOUT} 	{ std::string symbol = "SOUT"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_CLASS} 	{ std::string symbol = "CLASS"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_PUBLIC} 	{ std::string symbol = "PUBLIC"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_STATIC}  	{ std::string symbol = "STATIC"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_VOID} 	{ std::string symbol = "VOID"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_MAIN} 	{ std::string symbol = "MAIN"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_STRING} 	{ std::string symbol = "STRING"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_EXTENDS}  	{ std::string symbol = "EXTENDS"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_PRIVATE}  	{ std::string symbol = "PRIVATE"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_LENGTH}  	{ std::string symbol = "LENGTH"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_BOOLEAN}  	{ std::string symbol = "BOOL"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_RETURN}  	{ std::string symbol = "RETURN"; std::string data = "-1"; print_data(1, symbol, data, loc); }

{T_PLUS} 	{ std::string symbol = "PLUS"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_MINUS} 	{ std::string symbol = "MINUS"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_MUL} 	{ std::string symbol = "MUL"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_DIV} 	{ std::string symbol = "DIV"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_EQ} 		{ std::string symbol = "EQ"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_AND} 	{ std::string symbol = "AND"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_LESS} 	{ std::string symbol = "LESS"; std::string data = "-1"; print_data(1, symbol, data, loc); }
{T_ID}		{ std::string symbol = "ID"; std::string data = YYText(); print_data(1, symbol, data, loc); }
{T_NUM} 	{ std::string symbol = "CONST"; std::string data = YYText(); print_data(1, symbol, data, loc); }
{T_COMMENT}	{}
{T_SPACE}    	{}
"\n" 		{}
"\t" 		{}

. { printf("unknown"); }
%%
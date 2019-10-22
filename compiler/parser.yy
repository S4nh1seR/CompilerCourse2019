%language "c++"
%defines
%define parser_class_name {MC_Parser}
%parse-param { MyScanner *scanner }
%locations
%code requires {
class MyScanner;
#include <string>
}
%code {
#include "Scanner.h"
#undef yylex
#define yylex scanner->yylex
}
%define api.value.type variant
%define parse.assert

%token LBRACE
%token T_EOF 0
%token T_ANTI
%token T_LESS
%token T_EQ
%token T_DIV
%token T_MUL
%token T_MINUS
%token T_PLUS
%token T_RPARENTH
%token T_LPARENTH
%token T_RBRACKET
%token T_LBRACKET
%token T_RBRACE
%token T_LBRACE
%token T_SEMI
%token T_COMMA
%token T_DOT
%token T_AND
%token T_OR
%token T_CLASS
%token T_PUBLIC
%token T_PRIVATE
%token T_STATIC
%token T_VOID
%token T_MAIN
%token T_EXTENDS
%token T_RETURN
%token T_IF
%token T_ELSE
%token T_WHILE
%token T_SOUT
%token T_LENGTH
%token T_NEW
%token T_THIS
%token T_TRUE
%token T_FALSE
%token T_STRING
%token T_BOOLEAN
%token T_INT
%token T_NUM
%token T_ID
%token T_COMMENT
%token T_SPACE
%token T_N
%token T_T
%token T_Unknown

%type <std::string> item;

%token <std::string> TEXT;
%token <int> NUMBER;

%start program

%%

program:
  token_list T_EOF
;
token_list:
  token
  | token_list token
;
token:
  T_ID 
  | T_NUM
;

%%

void yy::MC_Parser::error (const location_type& loc, const std::string& msg)
 {
  std::cout << "error " << msg << std::endl;
} 


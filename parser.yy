%language "c++"
%defines
%define parser_class_name {MC_Parser}
%parse-param { MyScanner *scanner }
%parse-param { int& root }
%locations
%code requires {
class MyScanner;
#include <string>
/*#include "visitor/SerializeVisitor.h"
#include "visitor/Visitor.h"
#include "syntaxtree/Expressions.h"
#include "syntaxtree/Statements.h"
#include "syntaxtree/Goal.h"
#include "syntaxtree/MainClass.h"
#include "syntaxtree/SyntaxTreeNode.h"
#include "syntaxtree/Identifier.h"
#include "syntaxtree/Types.h"*/
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

%token <std::string> IDENTIFIER

%type <std::shared_ptr<Goal>> goal
%type <std::shared_ptr<MainClass>> main_class

%type <std::shared_ptr<ClassDeclarationPrefix>> class_declaration_prefix
%type <std::shared_ptr<ClassDeclaration>> class_declaration
%type <std::vector<std::shared_ptr<ClassDeclaration>>> class_declaration_sequence

%type <std::shared_ptr<Type>> type

%type <std::shared_ptr<VarDeclaration>> var_declaration
%type <std::vector<std::shared_ptr<VarDeclaration>>> var_declaration_sequence

%type <std::shared_ptr<MethodDeclaration>> method_declaration
%type <std::vector<std::pair<std::shared_ptr<Type>, std::string>>> method_args
%type <std::shared_ptr<MethodBody>> method_body
%type <std::vector<std::shared_ptr<MethodDeclaration>>> method_declaration_sequence

%type <std::shared_ptr<StatementBase>> statement
%type <std::vector<std::shared_ptr<StatementBase>>> statement_sequence

%type <std::shared_ptr<ExpressionBase>> expression
%type <std::vector<std::shared_ptr<ExpressionBase>>> few_expressions

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


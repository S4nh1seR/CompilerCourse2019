%language "c++"
%defines
%define api.value.type variant
%define parser_class_name {MC_Parser}
%parse-param { MyScanner* scanner }
%locations
%code requires {
#include <syntaxtree/Declarations.h>
#include <syntaxtree/Expressions.h>
#include <syntaxtree/Goal.h>
#include <syntaxtree/Identifier.h>
#include <syntaxtree/MainClass.h>
#include <syntaxtree/Statements.h>
#include <syntaxtree/Types.h>
using namespace SyntaxTree;

#include <string>

class MyScanner;
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

%type <Goal*> Goal
%type <MainClass*> MainClass
%type <ClassDeclaration*> ClassDeclaration
%type <std::vector<std::unique_ptr<const ClassDeclaration>>> ClassDeclarations
%type <MethodDeclaration*> MethodDeclaration
%type <VariableDeclaration*> VariableDeclaration
%type <std::vector<std::unique_ptr<const VariableDeclaration>>> VariableDeclarations
%type <IStatement*> Statement
%type <std::vector<std::unique_ptr<const IStatement>>*> Statements
%type <IExpression*> Expression
%type <std::vector<std::unique_ptr<const IExpression>>*> Expressions
%type <Identifier*> Identifier
%type <IType*> Type

%token <std::string> TEXT;
%token <int> NUMBER;

%%



%%

void yy::MC_Parser::error (const location_type& loc, const std::string& msg)
 {
  std::cout << "error " << msg << std::endl;
} 


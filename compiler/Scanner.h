#ifndef __MCSCANNER_HPP__
#define __MCSCANNER_HPP__ 1

#if !defined (yyFlexLexerOnce)
#include <FlexLexer.h>
#endif // _!defined (yyFlexLexerOnce)

#include "mc_parser.tab.hh"
#include "location.hh"

#include <Goal.h>

using Tokens = yy::MC_Parser::token_type;

class MyScanner : public yyFlexLexer {
public:
    int Process(Tokens token) {
	    std::cout << token << std::endl;
        return token;
    };

    void Space();

    using FlexLexer::yylex;
    virtual int yylex( yy::MC_Parser::semantic_type* const lval, 
 					   yy::MC_Parser::location_type *location1 );
   // YY_DECL defined in mc_lexer.l
   // Method body created by flex in mc_lexer.yy.cc

   void SetSyntaxTree(SyntaxTree::Goal* goal) {
       syntaxTree.reset(goal);
   }

private:
   /* yyval ptr */
   yy::MC_Parser::semantic_type *yylval = nullptr;

   std::unique_ptr<SyntaxTree::Goal> syntaxTree;
};

#endif /* END __MCSCANNER_HPP__ */

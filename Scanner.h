#ifndef __MCSCANNER_HPP__
#define __MCSCANNER_HPP__ 1

#if !defined (yyFlexLexerOnce)
#include <FlexLexer.h>
#endif // _!defined (yyFlexLexerOnce)

#include "mc_parser.tab.hh"
#include "location.hh"

using Tokens = yy::MC_Parser::token_type;

class MyScanner : public yyFlexLexer {
public:
    int Process(Tokens token) {
		if (loc != nullptr) {
			loc->begin.line = static_cast<unsigned int>(lineNumber);
			loc->begin.column = static_cast<unsigned int>(colNumber);
		}
		if (token == Tokens::T_N) {
			lineNumber += 1;
			colNumber = 1;
		} else {
			colNumber += YYLeng();
		}
		if (loc != nullptr) {
			loc->end.line = static_cast<unsigned int>(lineNumber);
			loc->end.column = static_cast<unsigned int>(colNumber);
		}
		std::cout << token << std::endl;
    	return token;
    };
    void Space() {
		colNumber += YYLeng();
	}
	
    using FlexLexer::yylex;
    virtual int yylex( yy::MC_Parser::semantic_type* const lval, 
 					   yy::MC_Parser::location_type *location1 );
   // YY_DECL defined in mc_lexer.l
   // Method body created by flex in mc_lexer.yy.cc


private:
   /* yyval ptr */
   yy::MC_Parser::semantic_type* yylval = nullptr;
   yy::MC_Parser::location_type* loc = nullptr;

   int lineNumber = 1;
   int colNumber = 1;
};

#endif /* END __MCSCANNER_HPP__ */

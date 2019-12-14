#pragma once

#if !defined (yyFlexLexerOnce)
#include <FlexLexer.h>
#endif // _!defined (yyFlexLexerOnce)

#include "parser.tab.hh"
#include "location.hh"

#include <Goal.h>

using Tokens = yy::Parser::token_type;

class Scanner : public yyFlexLexer {
public:
    Scanner() {
        loc = new yy::Parser::location_type();
    }
    Tokens Process(Tokens token) {
            //std::cout << "!" <<loc->begin << "!" << loc->end << std::endl;
	    //std::cout << token << std::endl;
        return token;
    };

    using FlexLexer::yylex;
    virtual int yylex( yy::Parser::semantic_type* const lval,
 					   yy::Parser::location_type* loc );
    int getRow() {
        return loc->begin.line;
    }
    yy::Parser::location_type* loc = nullptr;
private:
   /* yyval ptr */
   
   yy::Parser::semantic_type* yylval = nullptr;
};

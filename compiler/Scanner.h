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
        return token;
    };

    using FlexLexer::yylex;
    virtual int yylex( yy::Parser::semantic_type* const lval,
 					   yy::Parser::location_type* loc );
    ~Scanner() {
        delete loc;
    }
private:
   /* yyval ptr */
   yy::Parser::location_type* loc = nullptr;
   yy::Parser::semantic_type* yylval = nullptr;
};

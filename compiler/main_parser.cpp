#include <iostream>
#include "Scanner.h"
#include "mc_parser.tab.hh"

void parseStream(std::istream& input) {
    MyScanner *lexer = new MyScanner();
    lexer->switch_streams(input, std::cerr);    // По-умолчанию чтение из std::cin
    yy::MC_Parser parser(lexer);
    parser.parse();
    /*while (lexer.yylex() != Tokens::T_EOF) {
    }*/
}

int main() {
	parseStream(std::cin);
}


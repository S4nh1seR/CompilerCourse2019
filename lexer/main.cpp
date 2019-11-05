#include "Scanner.h"
#include <iostream>

void parseStream(std::istream& input) {
    MyScanner lexer;
    lexer.switch_streams(input, std::cerr);    // По-умолчанию чтение из std::cin
    while (lexer.yylex() != Tokens::T_EOF) {
    }
}

int main() {
	parseStream(std::cin);
}


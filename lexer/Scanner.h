#include "tokens.h"
#if !defined (yyFlexLexerOnce)
#include <FlexLexer.h>
#endif // _!defined (yyFlexLexerOnce)
class MyScanner : public yyFlexLexer {
public:
    virtual int yylex(); // Генерируется Flex
    int Process(Tokens token);
    void Space();
};

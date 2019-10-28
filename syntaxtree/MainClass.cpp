#include "MainClass.h"

namespace SyntaxTree {

    MainClass::MainClass(const Identifier* _mainClassIdentifier, const Identifier* _stringArgIdentifier,
        const IStatement* _internalStatement)
    :   mainClassIdentifier(_mainClassIdentifier),
        stringArgIdentifier(_stringArgIdentifier),
        internalStatement(_internalStatement)
        {}
}

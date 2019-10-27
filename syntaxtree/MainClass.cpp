#include "MainClass.h"

namespace SyntaxTree {

    MainClass::MainClass(const Identifier* _mainClassIdentifier, const Identifier* _stringArgIdentifier,
        const IStatement* _internalStatement)
    :   mainClassIdentifier(std::make_unique<Identifier>(_mainClassIdentifier)),
        stringArgIdentifier(std::make_unique<Identifier>(_stringArgIdentifier)),
        internalStatement(std::make_unique<IStatement>(_internalStatement))
        {}
}

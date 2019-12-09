#include "MainClass.h"

namespace SyntaxTree {

    MainClass::MainClass(std::unique_ptr<const Identifier>&& _mainClassIdentifier,
         std::unique_ptr<const Identifier>&& _stringArgIdentifier, std::unique_ptr<const IStatement>&& _internalStatement)

    :   mainClassIdentifier(std::move(_mainClassIdentifier)),
        mainFuncIdentifier(std::make_unique<Identifier>(L"main")),
        stringArgIdentifier(std::move(_stringArgIdentifier)),
        internalStatement(std::move(_internalStatement))
        {}
}

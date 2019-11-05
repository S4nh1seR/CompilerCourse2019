#include "MainClass.h"

namespace SyntaxTree {

    MainClass::MainClass(std::unique_ptr<const Identifier>&& _mainClassIdentifier,
         std::unique_ptr<const Identifier>&& _stringArgIdentifier, std::unique_ptr<const IStatement>&& _internalStatement)

    :   mainClassIdentifier(std::move(_mainClassIdentifier)),
        stringArgIdentifier(std::move(_stringArgIdentifier)),
        internalStatement(std::move(_internalStatement))
        {}
}

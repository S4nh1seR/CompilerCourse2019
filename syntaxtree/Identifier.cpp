#include "Identifier.h"

namespace SyntaxTree {

    void Identifier::AcceptVisitor(IVisitor* visitor, int _lineNumber) const {
        IIdentifierLogger* typeChecker = dynamic_cast<IIdentifierLogger*>(visitor);
        if (typeChecker != nullptr) {
            typeChecker->VisitNode(this, _lineNumber);
        }
    }
}
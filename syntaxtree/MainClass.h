#pragma once

#include "Statements.h"

#include <Visitor.h>

namespace SyntaxTree {

    class MainClass : public ISyntaxTreeNode {
    public:
        MainClass(const Identifier* _mainClassIdentifier, const Identifier* _stringArgIdentifier,
            const IStatement* _internalStatement);

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        const Identifier* GetMainClassIdentifier() const { return mainClassIdentifier.get(); }
        const Identifier* GetStringArgIdentifier() const { return stringArgIdentifier.get(); }
        const IStatement* GetInternalStatement() const { return internalStatement.get(); }
    private:
        std::unique_ptr<const Identifier> mainClassIdentifier;
        std::unique_ptr<const Identifier> stringArgIdentifier;
        std::unique_ptr<const IStatement> internalStatement;
    };

}
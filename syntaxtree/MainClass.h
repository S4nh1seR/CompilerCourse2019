#pragma once

#include "Statements.h"

namespace SyntaxTree {

    class MainClass : public ISyntaxTreeNode {
    public:
        MainClass(const Identifier* _mainClassIdentifier, const Identifier* _stringArgIdentifier,
            const IStatement* _internalStatement);

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

        const Identifier* GetMainClassIdentifier() const { return mainClassIdentifier.get(); }
        const Identifier* GetStringArgIdentifier() const { return stringArgIdentifier.get(); }
        const IStatement* GetInternalStatement() const { return internalStatement.get(); }
    private:
        std::unique_ptr<Identifier> mainClassIdentifier;
        std::unique_ptr<Identifier> stringArgIdentifier;
        std::unique_ptr<IStatement> internalStatement;
    };

}
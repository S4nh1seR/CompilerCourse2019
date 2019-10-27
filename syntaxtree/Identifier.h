#pragma once

#include "SyntaxTreeNode.h"

#include <string>

namespace SyntaxTree {

    class Identifier : public ISyntaxTreeNode {
    public:
        Identifier(const std::wstring& _identifier): identifier(_identifier) {}

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

        const std::wstring& GetIdentifier() const { return identifier; }

    private:
        const std::wstring identifier;
    };

}

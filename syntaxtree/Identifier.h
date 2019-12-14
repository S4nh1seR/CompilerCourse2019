#pragma once

#include "SyntaxTreeNode.h"

#include <Visitor.h>

#include <string>

namespace SyntaxTree {

    class Identifier : public ISyntaxTreeNode {
    public:
        explicit Identifier(const std::wstring& _identifier, int _line): identifier(_identifier) {line = _line;}

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        const std::wstring& GetIdentifier() const { return identifier; }

    private:
        const std::wstring identifier;
    };

}

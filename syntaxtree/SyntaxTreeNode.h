#pragma once

namespace SyntaxTree {

    class IVisitor;

    class ISyntaxTreeNode {
    public:
        virtual ~ISyntaxTreeNode() = default;
        virtual void AcceptVisitor(const IVisitor*) const = 0;
    };

}
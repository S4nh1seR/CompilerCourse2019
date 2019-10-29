#pragma once

#include <Visitor.h>

namespace SyntaxTree {

//    class IVisitor;

    class ISyntaxTreeNode {
    public:
        virtual ~ISyntaxTreeNode() = default;
        virtual void AcceptVisitor(IVisitor* visitor) const = 0;
    };

}
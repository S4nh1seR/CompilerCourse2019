#pragma once

#include <Visitor.h>

namespace SyntaxTree {

    const int InvalidLineNumber = -1;

    class ISyntaxTreeNode {
    public:
        virtual ~ISyntaxTreeNode() = default;
        virtual void AcceptVisitor(IVisitor* visitor) const = 0;

        int lineNumber{InvalidLineNumber};
    };

}

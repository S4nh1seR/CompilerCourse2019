#pragma once

#include <IrtVisitor.h>

namespace IrTree {

    class IIrTreeNode {
    public:
        virtual ~IIrTreeNode() = default;
        virtual void AcceptVisitor(IIrtVisitor* visitor) const = 0;
    };

    class IIrtExpression : public IIrTreeNode {
    };

    class IIrtStatement : public IIrTreeNode {
    };
}

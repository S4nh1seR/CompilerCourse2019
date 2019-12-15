#pragma once

#include <IrtExpressions.h>

#include <cassert>

namespace IrTree {
    class ISubtreeWrapper {
    public:
        virtual std::shared_ptr<const IIrtExpression> ToConditional(...) const {return nullptr;}
        virtual std::shared_ptr<const IIrtStatement> ToExpression(...) const {return nullptr;}
        virtual std::shared_ptr<const IIrtStatement> ToStatement(...) const {return nullptr;}
    };
    class ExpressionWrapper : public ISubtreeWrapper {};
    class StatementWrapper : public ISubtreeWrapper {};
}

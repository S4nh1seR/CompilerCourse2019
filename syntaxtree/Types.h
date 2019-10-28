#pragma once

#include "Identifier.h"

#include <memory>

namespace SyntaxTree {

    class IType : public ISyntaxTreeNode {
    };

    class IntType : public IType {
    public:
        IntType() = default;

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }
    };

    class  BooleanType : public IType {
    public:
        BooleanType() = default;

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }
    };

    class IntArrayType: public  IType {
    public:
        IntArrayType() = default;

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }
    };

    class IdentifierType : public IType {
    public:
        IdentifierType(const Identifier* _identifier): identifier(_identifier) {}

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

        const Identifier* GetIdentifier() const { return identifier.get(); }
    private:
        std::unique_ptr<const Identifier> identifier;
    };

}





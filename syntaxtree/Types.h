#pragma once

#include "Identifier.h"

#include <Visitor.h>

#include <cassert>
#include <memory>

namespace SyntaxTree {

    enum TType {
        T_Boolean,
        T_Int,
        T_IntArray,
        T_ClassType
    };

    class Type : public ISyntaxTreeNode {
    public:
        Type(TType _type): type(_type) { assert(IsSimpleType()); }
        Type(std::unique_ptr<const Identifier>&& _identifier): type(T_ClassType), identifier(std::move(_identifier)) { assert(identifier != 0); }

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }


        TType GetType() const { return type; }
        const Identifier* GetIdentifier() const { return identifier.get(); }
        bool IsSimpleType() const { return type != T_ClassType; }
    private:
        TType type;
        std::unique_ptr<const Identifier> identifier;
    };

}





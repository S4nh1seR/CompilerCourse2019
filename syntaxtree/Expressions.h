#pragma once

#include "Identifier.h"

#include <Visitor.h>

#include <cassert>
#include <memory>
#include <vector>

namespace SyntaxTree {

    class IExpression : public ISyntaxTreeNode {
    };

    enum TBinaryOperationType {
        BOT_Add,
        BOT_Sub,
        BOT_Mul,
        BOT_Mod,

        BOT_Or,
        BOT_And,

        BOT_Less
    };

    class IdentifierExpression : public IExpression {
    public:
        explicit IdentifierExpression(std::unique_ptr<const Identifier>&& _identifier): identifier(std::move(_identifier)) {}

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        const Identifier* GetIdentifier() const { return identifier.get(); }

    private:
        std::unique_ptr<const Identifier> identifier;
    };

    class BinaryOperationExpression : public IExpression {
    public:
        BinaryOperationExpression(TBinaryOperationType _boType, std::unique_ptr<const IExpression>&& _leftOperand,
            std::unique_ptr<const IExpression>&& _rightOperand);

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        TBinaryOperationType GetOperationType() const { return boType; }
        const IExpression* GetLeftOperand() const { return leftOperand.get(); }
        const IExpression* GetRightOperand() const { return rightOperand.get(); }

    private:
        TBinaryOperationType boType;

        std::unique_ptr<const IExpression> leftOperand;
        std::unique_ptr<const IExpression> rightOperand;
    };

    class SquareBracketExpression : public IExpression {
    public:
        SquareBracketExpression(std::unique_ptr<const IExpression>&& _arrayOperator, std::unique_ptr<const IExpression>&& _indexOperand);

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IExpression* GetArrayOperand() const { return arrayOperand.get(); }
        const IExpression* GetIndexOperand() const { return indexOperand.get(); }

    private:
        std::unique_ptr<const IExpression> arrayOperand;
        std::unique_ptr<const IExpression> indexOperand;
    };

    class LengthExpression : public IExpression {
    public:
        explicit LengthExpression(std::unique_ptr<const IExpression>&& _lengthOperand): lengthOperand(std::move(_lengthOperand)) {}

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IExpression* GetLengthOperand() const { return lengthOperand.get(); }
    private:
        std::unique_ptr<const IExpression> lengthOperand;
    };

    class MethodCallExpression : public IExpression {
    public:
        MethodCallExpression(std::unique_ptr<const IExpression>&& _objectOperand,
            std::unique_ptr<const Identifier>&& _methodIdentifier);

        MethodCallExpression(std::unique_ptr<const IExpression>&& _objectOperand,
            std::unique_ptr<const Identifier>&& _methodIdentifier,
            std::vector<std::unique_ptr<const IExpression>>&& _methodArguments);

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IExpression* GetObjectOperand() const { return objectOperand.get(); }
        const Identifier* GetMethodIdentifier() const { return methodIdentifier.get(); }
        const IExpression* GetArgument(int index) const;
        void GetAllArguments(std::vector<const IExpression*>& _methodArguments) const;

    private:
        std::unique_ptr<const IExpression> objectOperand;
        std::unique_ptr<const Identifier> methodIdentifier;
        const std::vector<std::unique_ptr<const IExpression>> methodArguments;
    };

    class BooleanLiteralExpression : public IExpression {
    public:
        explicit BooleanLiteralExpression(const bool _literalValue): literalValue(_literalValue) {}

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        bool GetLiteralValue() const { return literalValue; }
    private:
        const bool literalValue;
    };

    class IntegerLiteralExpression : public IExpression {
    public:
        explicit IntegerLiteralExpression(const int _literalValue): literalValue(_literalValue) {}

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        int GetLiteralValue() const { return literalValue; }
    private:
        const int literalValue;
    };


    class ThisExpression : public IExpression {
    public:
        ThisExpression() = default;

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }
    };

    class NewExpression : public IExpression {
    public:
        explicit NewExpression(std::unique_ptr<const Identifier>&& _identifierOperand): identifierOperand(std::move(_identifierOperand)) {}

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        const Identifier* GetIdentifierOperand() const { return identifierOperand.get(); }

    private:
        std::unique_ptr<const Identifier> identifierOperand;
    };

    class NewArrayExpression : public IExpression {
    public:
        explicit NewArrayExpression(std::unique_ptr<const IExpression>&& _sizeOperand): sizeOperand(std::move(_sizeOperand)) {}

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IExpression* GetSizeOperand() const { return sizeOperand.get(); }

    private:
        std::unique_ptr<const IExpression> sizeOperand;
    };

    class OppositeExpression : public IExpression {
    public:
        explicit OppositeExpression(std::unique_ptr<const IExpression>&& _sourceExpression): sourceExpression(std::move(_sourceExpression)) {}

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IExpression* GetSourceExpression() const { return sourceExpression.get(); }
    private:
        std::unique_ptr<const IExpression> sourceExpression;
    };

    class ParenthesesExpression : public IExpression {
    public:
        explicit ParenthesesExpression(std::unique_ptr<const IExpression>&& _internalExpression): internalExpression(std::move(_internalExpression)) {}

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IExpression* GetInternalExpression() const { return internalExpression.get(); }
    private:
        std::unique_ptr<const IExpression> internalExpression;
    };
}
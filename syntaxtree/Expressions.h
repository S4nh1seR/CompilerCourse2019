#pragma once

#include <memory>
#include <string>

#include "SyntaxTreeNode.h"

namespace SyntaxTree {

    class IExpression : public ISyntaxTreeNode {
    };

    enum TBinaryOperationType {
        BOT_Add,
        BOT_Sub,
        BOT_Mul,
        BOT_Div,
        BOT_Mod,

        BOT_Or,
        BOT_And,

        BOT_Less
    };

    class BinaryOperationExpression : public IExpression {
    public:
        BinaryOperationExpression(TBinaryOperationType _boType, const IExpression* _leftOperand, const IExpression* _rightOperand);

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

        TBinaryOperationType GetOperationType() const { return boType; }
        const IExpression* GetLeftOperand() const { return leftOperand.get(); }
        const IExpression* GetRightOperand() const { return rightOperand.get(); }

    private:
        TBinaryOperationType boType;

        std::unique_ptr<IExpression> leftOperand;
        std::unique_ptr<IExpression> rightOperand;
    };

    class SquareBracketExpression : public IExpression {
    public:
        SquareBracketExpression(const IExpression* _arrayOperator, const IExpression* _indexOperand);

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IExpression* GetArrayOperand() const { return arrayOperand.get(); }
        const IExpression* GetIndexOperand() const { return indexOperand.get(); }

    private:
        std::unique_ptr<IExpression> arrayOperand;
        std::unique_ptr<IExpression> indexOperand;
    };

    class LengthExpression : public IExpression {
    public:
        LengthExpression(const IExpression* _lengthOperand): lengthOperand(std::make_unique<IExpression>(_lengthOperand)) {};

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IExpression* GetLengthOperand() const { return lengthOperand.get(); }
    private:
        std::unique_ptr<IExpression> lengthOperand;
    };

    class MethodCallExpression : public IExpression {
        // TODO
    };

    class BooleanLiteralExpression : public IExpression {
    public:
        BooleanLiteralExpression(const bool _literalValue): literalValue(_literalValue) {}

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

        bool GetLiteralValue() const { return literalValue; }
    private:
        const bool literalValue;
    };

    class IntegerLiteralExpression : public IExpression {
    public:
        IntegerLiteralExpression(const int _literalValue): literalValue(_literalValue) {}

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

        int GetLiteralValue() const { return literalValue; }
    private:
        const int literalValue;
    };

    class IdentifierExpression : public IExpression {
    public:
        IdentifierExpression(const std::wstring& _identifier): identifier(_identifier) {}

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

        const std::wstring& GetIdentifier() const { return identifier; }

    private:
        const std::wstring identifier;
    };

    class ThisExpression : public IExpression {
    public:
        ThisExpression() = default;

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }
    };

    class NewExpression : public IExpression {
    public:
        NewExpression(const IExpression* _identifierOperand): identifierOperand(std::make_unique<IdentifierExpression>(_identifierOperand)) {}

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IExpression* GetIdentifierOperand() const { return identifierOperand.get(); }

    private:
        std::unique_ptr<IdentifierExpression> identifierOperand;
    };

    class NewArrayExpression : public IExpression {
    public:
        NewArrayExpression(const IExpression* _sizeOperand): sizeOperand(std::make_unique<IExpression>(_sizeOperand)) {}

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IExpression* GetSizeOperand() const { return sizeOperand.get(); }

    private:
        std::unique_ptr<IExpression> sizeOperand;
    };

    class OppositeExpression : public IExpression {
    public:
        OppositeExpression(const IExpression* _sourceExpression): sourceExpression(std::make_unique<IExpression>(_sourceExpression)) {}

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IExpression* GetSourceExpression() const { return sourceExpression.get(); }
    private:
        std::unique_ptr<IExpression> sourceExpression;
    };

    class ParenthesesExpression : public IExpression {
    public:
        ParenthesesExpression(const IExpression* _internalExpression): internalExpression(std::make_unique<IExpression>(_internalExpression)) {}

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IExpression* GetInternalExpression() const { return internalExpression.get(); }
    private:
        std::unique_ptr<IExpression> internalExpression;
    };
}
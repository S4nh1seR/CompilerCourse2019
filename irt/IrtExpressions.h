#pragma once

#include "Label.h"
#include "IrTreeNode.h"
#include <Expressions.h>

#include <memory>
#include <vector>

namespace IrTree {

    class IIrtExpression : public IIrTreeNode {
    };


    typedef SyntaxTree::TBinaryOperationType TBinaryOperationType;

    class IrtBinaryOperationExpression : public IIrtExpression {
    public:
        IrtBinaryOperationExpression(TBinaryOperationType _operationType,
                std::unique_ptr<const IIrtExpression>&& _leftOperand,
                std::unique_ptr<const IIrtExpression>&& _rightOperand);

        TBinaryOperationType GetOperationType() const { return operationType; }
        const IIrtExpression* GetLeftOperand() const { return leftOperand.get(); }
        const IIrtExpression* GetRightOperand() const { return rightOperand.get(); }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }

    private:

        TBinaryOperationType operationType;
        std::unique_ptr<const IIrtExpression> leftOperand;
        std::unique_ptr<const IIrtExpression> rightOperand;
    };

    class IrtConstExpression : public IIrtExpression {
    public:
        explicit IrtConstExpression(int _constValue): constValue(_constValue) {}

        int GetConstValue() const { return constValue; }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }

    private:
        const int constValue;
    };

    class IrtNameExpression : public IIrtExpression {
    public:
        explicit IrtNameExpression(std::unique_ptr<const IrtLabel>&& _label ) : label(std::move(_label)) {}

        const IrtLabel* GetLabel() const { return label.get(); }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }
    private:
        std::unique_ptr<const IrtLabel> label;
    };

    class IrtTempExpression : public IIrtExpression {
    public:
        explicit IrtTempExpression(std::unique_ptr<const IrtTemp>&& tempValue): tempValue(std::move(tempValue)) {}

        const IrtTemp* GetTempValue() const { return tempValue.get(); }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }
    private:
        std::unique_ptr<const IrtTemp> tempValue;
    };


    class IIrtStatement;

    class IrtESeqExpression : public IIrtExpression {
    public:
        IrtESeqExpression(std::unique_ptr<const IIrtStatement>&& _statement, std::unique_ptr<const IIrtExpression>&& _expression);

        const IIrtStatement* GetStatement() const { return statement.get(); }
        const IIrtExpression* GetExpression() const { return expression.get(); }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }

    private:
        std::unique_ptr<const IIrtStatement> statement;
        std::unique_ptr<const IIrtExpression> expression;
    };

    class IrtMemoryExpression : public IIrtExpression {
    public:
        explicit IrtMemoryExpression(std::unique_ptr<const IIrtExpression>&& _expression): expression(std::move(_expression)) {}

        const IIrtExpression* GetMemoryExpression() const { return expression.get(); }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }

    private:
        std::unique_ptr<const IIrtExpression> expression;
    };

    class IrtExpressionList : public IIrtExpression {
    public:
        explicit IrtExpressionList(std::vector<std::unique_ptr<const IIrtExpression>>&& _expressions): expressions(std::move(_expressions)) {}
        IrtExpressionList() {}

        void AddExpression(std::unique_ptr<const IIrtExpression>&& expression) { expressions.emplace_back(std::move(expression)); }
        void GetExpressions(std::vector<const IIrtExpression*>& _expressions) const;
        const IIrtExpression* GetExpression(int index) const;

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }

    private:
        std::vector<std::unique_ptr<const IIrtExpression>> expressions;
    };

    class IrtCallExpression : public IIrtExpression {
    public:
        IrtCallExpression(std::unique_ptr<const IIrtExpression>&& _methodExpression,
            std::unique_ptr<const IrtExpressionList>&& _argumentExpressionList);

        const IIrtExpression* GetMethodExpression() const { return methodExpression.get(); }
        const IrtExpressionList*  GetArgumentExpressionList() const { return argumentExpressionList.get(); }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }

    private:
        std::unique_ptr<const IIrtExpression> methodExpression;
        std::unique_ptr<const IrtExpressionList> argumentExpressionList;
    };


}
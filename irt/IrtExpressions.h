#pragma once

#include "Label.h"
#include "IrTreeNode.h"
#include <Expressions.h>

#include <memory>
#include <vector>

namespace IrTree {

    typedef SyntaxTree::TBinaryOperationType TBinaryOperationType;

    class IrtBinaryOperationExpression : public IIrtExpression {
    public:
        IrtBinaryOperationExpression(TBinaryOperationType _operationType,
            const std::shared_ptr<const IIrtExpression>& _leftOperand,
            const std::shared_ptr<const IIrtExpression>& _rightOperand);

        TBinaryOperationType GetOperationType() const { return operationType; }
        std::shared_ptr<const IIrtExpression> GetLeftOperand() const { return leftOperand; }
        std::shared_ptr<const IIrtExpression> GetRightOperand() const { return rightOperand; }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }

    private:

        TBinaryOperationType operationType;
        std::shared_ptr<const IIrtExpression> leftOperand;
        std::shared_ptr<const IIrtExpression> rightOperand;
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
        explicit IrtNameExpression(const std::shared_ptr<const IrtLabel>& _label ) : label(_label) {}

        std::shared_ptr<const IrtLabel> GetLabel() const { return label; }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }
    private:
        std::shared_ptr<const IrtLabel> label;
    };

    class IrtTempExpression : public IIrtExpression {
    public:
        explicit IrtTempExpression(const std::shared_ptr<const IrtTemp>& tempValue): tempValue(tempValue) {}

        std::shared_ptr<const IrtTemp> GetTempValue() const { return tempValue; }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }
    private:
        std::shared_ptr<const IrtTemp> tempValue;
    };


    class IIrtStatement;

    class IrtESeqExpression : public IIrtExpression {
    public:
        IrtESeqExpression(const std::shared_ptr<const IIrtStatement>& _statement, const std::shared_ptr<const IIrtExpression>& _expression);

        std::shared_ptr<const IIrtStatement> GetStatement() const { return statement; }
        std::shared_ptr<const IIrtExpression> GetExpression() const { return expression; }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }

    private:
        std::shared_ptr<const IIrtStatement> statement;
        std::shared_ptr<const IIrtExpression> expression;
    };

    class IrtMemoryExpression : public IIrtExpression {
    public:
        explicit IrtMemoryExpression(const std::shared_ptr<const IIrtExpression>& _expression): expression(_expression) {}

        std::shared_ptr<const IIrtExpression> GetMemoryExpression() const { return expression; }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }

    private:
        std::shared_ptr<const IIrtExpression> expression;
    };

    class IrtExpressionList : public IIrtExpression {
    public:
        explicit IrtExpressionList(std::vector<std::shared_ptr<const IIrtExpression>>&& _expressions): expressions(std::move(_expressions)) {}
        IrtExpressionList() {}

        void AddExpression(const std::shared_ptr<const IIrtExpression>& expression) { expressions.push_back(expression); }
        void GetExpressions(std::vector<std::shared_ptr<const IIrtExpression>>& _expressions) const;
        std::shared_ptr<const IIrtExpression> GetExpression(int index) const;

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }

    private:
        std::vector<std::shared_ptr<const IIrtExpression>> expressions;
    };

    class IrtCallExpression : public IIrtExpression {
    public:
        IrtCallExpression(const std::shared_ptr<const IIrtExpression>& _methodExpression,
            const std::shared_ptr<const IrtExpressionList>& _argumentExpressionList);

        std::shared_ptr<const IIrtExpression> GetMethodExpression() const { return methodExpression; }
        std::shared_ptr<const IrtExpressionList>  GetArgumentExpressionList() const { return argumentExpressionList; }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }

    private:
        std::shared_ptr<const IIrtExpression> methodExpression;
        std::shared_ptr<const IrtExpressionList> argumentExpressionList;
    };


}
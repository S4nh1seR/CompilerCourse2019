#pragma once

#include "Expressions.h"

#include <Visitor.h>

namespace SyntaxTree {


    class IStatement : public ISyntaxTreeNode {
    };

    class CompoundStatement : public IStatement {
    public:
        explicit CompoundStatement(std::unique_ptr<std::vector<std::unique_ptr<const IStatement>>>&& _internalStatements);

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IStatement* GetStatement(int index) const;
        void GetAllStatements(std::vector<const IStatement*>& _internalStatements) const;
    private:
        std::unique_ptr<const std::vector<std::unique_ptr<const IStatement>>> internalStatements;
    };

    class ConditionalStatement : public IStatement {
    public:
        ConditionalStatement(std::unique_ptr<const IExpression>&& _conditionExpression,
            std::unique_ptr<const IStatement>&& _positiveStatement, std::unique_ptr<const IStatement>&& _negativeStatement);

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IExpression* GetConditionalExpression() const { return conditionExpression.get(); }
        const IStatement* GetPositiveStatement() const { return positiveStatement.get(); }
        const IStatement* GetNegativeStatement() const { return negativeStatement.get(); }

    private:
        std::unique_ptr<const IExpression> conditionExpression;
        std::unique_ptr<const IStatement> positiveStatement;
        std::unique_ptr<const IStatement> negativeStatement;
    };

    class LoopStatement : public IStatement {
    public:
        LoopStatement(std::unique_ptr<const IExpression>&& _conditionExpression,
            std::unique_ptr<const IStatement>&& _internalStatement);

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IExpression* GetConditionalExpression() const { return conditionExpression.get(); }
        const IStatement* GetInternalStatement() const { return internalStatement.get(); }

    private:
        std::unique_ptr<const IExpression> conditionExpression;
        std::unique_ptr<const IStatement> internalStatement;
    };

    class PrintStatement : public IStatement {
    public:
        explicit PrintStatement(std::unique_ptr<const IExpression>&& _printOperand): printOperand(std::move(_printOperand)) {}

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IExpression* GetPrintOperand() const { return printOperand.get(); }
    private:
        std::unique_ptr<const IExpression> printOperand;
    };

    class AssignmentStatement : public IStatement {
    public:
        AssignmentStatement(std::unique_ptr<const Identifier>&& _leftOperand, std::unique_ptr<const IExpression>&& _rightOperand);

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        const Identifier* GetLeftOperand() const { return leftOperand.get(); }
        const IExpression* GetRightOperand() const { return rightOperand.get(); }

    private:
        std::unique_ptr<const Identifier> leftOperand;
        std::unique_ptr<const IExpression> rightOperand;
    };

    class ArrayAssignmentStatement : public IStatement {
    public:
        ArrayAssignmentStatement(std::unique_ptr<const Identifier>&& _arrayIdentifier, std::unique_ptr<const IExpression>&& _arrayIndex,
            std::unique_ptr<const IExpression>&& _rightOperand);

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        const Identifier* GetArrayIdentifier() const { return arrayIdentifier.get(); }
        const IExpression* GetArrayIndex() const { return arrayIndex.get(); }
        const IExpression* GetRightOperand() const { return rightOperand.get(); }
    private:
        std::unique_ptr<const Identifier> arrayIdentifier;
        std::unique_ptr<const IExpression> arrayIndex;
        std::unique_ptr<const IExpression> rightOperand;
    };
}
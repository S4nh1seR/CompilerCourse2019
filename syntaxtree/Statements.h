#pragma once

#include "Expressions.h"

namespace SyntaxTree {


    class IStatement : public ISyntaxTreeNode {
    };

    class CompoundStatement : public IStatement {
    public:
        CompoundStatement(const std::vector<const IStatement*>& _internalStatements);

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IStatement* GetStatement(int index) const;
        void GetAllStatements(std::vector<const IStatement*>& _internalStatements) const;
    private:
        std::vector<std::unique_ptr<const IStatement>> internalStatements;
    };

    class ConditionalStatement : public IStatement {
    public:
        ConditionalStatement(const IExpression* _conditionExpression, const IStatement* _positiveStatement, const IStatement* _negativeStatement);

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

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
        LoopStatement(const IExpression* _conditionExpression, const IStatement* _internalStatement);

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IExpression* GetConditionalExpression() const { return conditionExpression.get(); }
        const IStatement* GetInternalStatement() const { return internalStatement.get(); }

    private:
        std::unique_ptr<const IExpression> conditionExpression;
        std::unique_ptr<const IStatement> internalStatement;
    };

    class PrintStatement : public IStatement {
    public:
        PrintStatement(const IExpression* _printOperand): printOperand(_printOperand) {}

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IExpression* GetPrintOperand() const { return printOperand.get(); }
    private:
        std::unique_ptr<const IExpression> printOperand;
    };

    class AssignmentStatement : public IStatement {
    public:
        AssignmentStatement(const Identifier* _leftOperand, const IExpression* _rightOperand);

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

        const Identifier* GetLeftOperand() const { return leftOperand.get(); }
        const IExpression* GetRightOperand() const { return rightOperand.get(); }

    private:
        std::unique_ptr<const Identifier> leftOperand;
        std::unique_ptr<const IExpression> rightOperand;
    };

    class ArrayAssignmentStatement : public IStatement {
    public:
        ArrayAssignmentStatement(const Identifier* _arrayIdentifier, const IExpression* _arrayIndex, const IExpression* _rightOperand);

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

        const Identifier* GetArrayIdentifier() const { return arrayIdentifier.get(); }
        const IExpression* GetArrayIndex() const { return arrayIndex.get(); }
        const IExpression* GetRightOperand() const { return rightOperand.get(); }
    private:
        std::unique_ptr<const Identifier> arrayIdentifier;
        std::unique_ptr<const IExpression> arrayIndex;
        std::unique_ptr<const IExpression> rightOperand;
    };
}
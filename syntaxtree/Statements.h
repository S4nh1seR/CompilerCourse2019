
#include "Expressions.h"

namespace SyntaxTree {


    class IStatement : public ISyntaxTreeNode {
    };

    class CompoundStatement : public IStatement {
        // TODO
    };

    class ConditionalStatement : public IStatement {
    public:
        ConditionalStatement(const IExpression* _conditionExpression, const IStatement* _positiveStatement, const IStatement* _negativeStatement);

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IExpression* GetConditionalExpression() const { return conditionExpression.get(); }
        const IStatement* GetPositiveStatement() const { return positiveStatement.get(); }
        const IStatement* GetNegativeStatement() const { return negativeStatement.get(); }

    private:
        std::unique_ptr<IExpression> conditionExpression;
        std::unique_ptr<IStatement> positiveStatement;
        std::unique_ptr<IStatement> negativeStatement;
    };

    class LoopStatement : public IStatement {
    public:
        LoopStatement(const IExpression* _conditionExpression, const IStatement* _internalStatement);

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IExpression* GetConditionalExpression() const { return conditionExpression.get(); }
        const IStatement* GetInternalStatement() const { return internalStatement.get(); }

    private:
        std::unique_ptr<IExpression> conditionExpression;
        std::unique_ptr<IStatement> internalStatement;
    };

    class PrintStatement : public IStatement {
    public:
        PrintStatement(const IExpression* _printOperand): printOperand(std::make_unique<IExpression>(_printOperand)) {}

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IExpression* GetPrintOperand() const { return printOperand.get(); }
    private:
        std::unique_ptr<IExpression> printOperand;
    };

    class AssignmentStatement : public IStatement {
        AssignmentStatement(const IdentifierExpression* _leftOperand, const IExpression* _rightOperand);

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IdentifierExpression* GetLeftOperand() const { return leftOperand.get(); }
        const IExpression* GetRightOperand() const { return rightOperand.get(); }

    private:
        std::unique_ptr<IdentifierExpression> leftOperand;
        std::unique_ptr<IExpression> rightOperand;
    };

    class ArrayAssignmentStatement : public IStatement {
        ArrayAssignmentStatement(const IdentifierExpression* _arrayIdentifier, const IExpression* _arrayIndex, const IExpression* _rightOperand);

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IdentifierExpression* GetArrayIdentifier() const { return arrayIdentifier.get(); }
        const IExpression* GetArrayIndex() const { return arrayIndex.get(); }
        const IExpression* GetRightOperand() const { return rightOperand.get(); }
    private:
        std::unique_ptr<IdentifierExpression> arrayIdentifier;
        std::unique_ptr<IExpression> arrayIndex;
        std::unique_ptr<IExpression> rightOperand;
    };
}
#pragma once

#include "IrTreeNode.h"
#include "Label.h"

#include <IrtVisitor.h>

#include <memory>

namespace IrTree {

    class IIrtStatement : public IIrTreeNode {
    };

    class IIrtExpression;

    class IrtExpressionStatement : public IIrtStatement {
    public:
        explicit IrtExpressionStatement(std::unique_ptr<const IIrtExpression>&& _expression) : expression(std::move(_expression)) {}

        const IIrtExpression* GetExpression() const { return expression.get(); }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }

    private:
        std::unique_ptr<const IIrtExpression> expression;
    };

    class IrtJumpStatement : public IIrtStatement {
    public:

        explicit IrtJumpStatement(std::unique_ptr<const IrtLabel>&& _targetLabel) : targetLabel(std::move(_targetLabel)) {}

        const IrtLabel* GetTargetLabel() const { return targetLabel.get(); }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }

    private:
        std::unique_ptr<const IrtLabel> targetLabel;
    };

    // пока рассматриваем только условие "меньше <"
    class IrtCJumpStatement : public IIrtStatement {
    public:
        IrtCJumpStatement(std::unique_ptr<const IIrtExpression>&& _leftExpression,
            std::unique_ptr<const IIrtExpression>&& _rightExpression,
            std::unique_ptr<const IrtLabel>&& _positiveLabel,
            std::unique_ptr<const IrtLabel>&& _negativeLabel);

        const IIrtExpression* GetLeftExpression() const { return leftExpression.get(); }
        const IIrtExpression* GetRightExpression() const { return rightExpression.get(); }

        const IrtLabel* GetPositiveLabel() const { return positiveLabel.get(); }
        const IrtLabel* GetnegativeLabel() const { return negativeLabel.get(); }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }

    private:
        std::unique_ptr<const IIrtExpression> leftExpression;
        std::unique_ptr<const IIrtExpression> rightExpression;
        std::unique_ptr<const IrtLabel> positiveLabel;
        std::unique_ptr<const IrtLabel> negativeLabel;
    };


    class IrtLabelStatement : public IIrtStatement {
    public:
        explicit IrtLabelStatement(std::unique_ptr<const IrtLabel>&& _label) : label(std::move(_label)) {}

        const IrtLabel* GetLabel() const { return label.get(); }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }

    private:
        std::unique_ptr<const IrtLabel> label;
    };

    class IrtMoveStatement : public IIrtStatement {
    public:
        IrtMoveStatement(std::unique_ptr<const IIrtExpression>&& _destinationExpression,
            std::unique_ptr<const IIrtExpression>&& _sourceExpression);

        const IIrtExpression* GetDestinationExpression() const { return destinationExpression.get(); }
        const IIrtExpression* GetSourceExpression() const { return sourceExpression.get(); }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }

    private:
        std::unique_ptr<const IIrtExpression> destinationExpression;
        std::unique_ptr<const IIrtExpression> sourceExpression;
    };

    class IrtSeqStatement : public IIrtStatement {
    public:
        IrtSeqStatement(std::unique_ptr<const IIrtStatement>&& _leftStatement,
            std::unique_ptr<const IIrtStatement>&& _rightStatement);

        const IIrtStatement* GetLeftStatement() const { leftStatement.get(); }
        const IIrtStatement* GetRightStatement() const { rightStatement.get(); }

        virtual void AcceptVisitor(IIrtVisitor* visitor) { visitor->VisitNode(this); }

    private:
        std::unique_ptr<const IIrtStatement> leftStatement;
        std::unique_ptr<const IIrtStatement> rightStatement;
    };

}
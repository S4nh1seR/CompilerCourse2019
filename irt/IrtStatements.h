#pragma once

#include "IrTreeNode.h"
#include "Label.h"

#include <IrtVisitor.h>

#include <memory>

namespace IrTree {

    class IrtExpressionStatement : public IIrtStatement {
    public:
        explicit IrtExpressionStatement(const std::shared_ptr<const IIrtExpression>& _expression) : expression(_expression) {}

        std::shared_ptr<const IIrtExpression> GetExpression() const { return expression; }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }

    private:
        std::shared_ptr<const IIrtExpression> expression;
    };

    class IrtJumpStatement : public IIrtStatement {
    public:

        explicit IrtJumpStatement(const std::shared_ptr<const IrtLabel>& _targetLabel) : targetLabel(_targetLabel) {}

        const IrtLabel* GetTargetLabel() const { return targetLabel.get(); }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }

    private:
        std::shared_ptr<const IrtLabel> targetLabel;
    };

    // пока рассматриваем только условие "меньше <"
    class IrtCJumpStatement : public IIrtStatement {
    public:
        IrtCJumpStatement(const std::shared_ptr<const IIrtExpression>& _leftExpression,
            const std::shared_ptr<const IIrtExpression>& _rightExpression,
            const std::shared_ptr<const IrtLabel>& _positiveLabel,
            const std::shared_ptr<const IrtLabel>& _negativeLabel);

        std::shared_ptr<const IIrtExpression> GetLeftExpression() const { return leftExpression; }
        std::shared_ptr<const IIrtExpression> GetRightExpression() const { return rightExpression; }
        std::shared_ptr<const IrtLabel> GetPositiveLabel() const { return positiveLabel; }
        std::shared_ptr<const IrtLabel> GetnegativeLabel() const { return negativeLabel; }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }

    private:
        std::shared_ptr<const IIrtExpression> leftExpression;
        std::shared_ptr<const IIrtExpression> rightExpression;
        std::shared_ptr<const IrtLabel> positiveLabel;
        std::shared_ptr<const IrtLabel> negativeLabel;
    };


    class IrtLabelStatement : public IIrtStatement {
    public:
        explicit IrtLabelStatement(const std::shared_ptr<const IrtLabel>& _label) : label(_label) {}

        std::shared_ptr<const IrtLabel> GetLabel() const { return label; }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }

    private:
        std::shared_ptr<const IrtLabel> label;
    };

    class IrtMoveStatement : public IIrtStatement {
    public:
        IrtMoveStatement(const std::shared_ptr<const IIrtExpression>& _destinationExpression,
            const std::shared_ptr<const IIrtExpression>& _sourceExpression);

        std::shared_ptr<const IIrtExpression> GetDestinationExpression() const { return destinationExpression; }
        std::shared_ptr<const IIrtExpression> GetSourceExpression() const { return sourceExpression; }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }

    private:
        std::shared_ptr<const IIrtExpression> destinationExpression;
        std::shared_ptr<const IIrtExpression> sourceExpression;
    };

    class IrtSeqStatement : public IIrtStatement {
    public:
        IrtSeqStatement(const std::shared_ptr<const IIrtStatement>& _leftStatement,
            const std::shared_ptr<const IIrtStatement>& _rightStatement);

        std::shared_ptr<const IIrtStatement> GetLeftStatement() const { return leftStatement; }
        std::shared_ptr<const IIrtStatement> GetRightStatement() const { return rightStatement; }

        virtual void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }

    private:
        std::shared_ptr<const IIrtStatement> leftStatement;
        std::shared_ptr<const IIrtStatement> rightStatement;
    };

}
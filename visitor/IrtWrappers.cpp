#include "IrtWrappers.h"
#include "Make.h"

namespace IrTree {

    RelativeConditionalWrapper::RelativeConditionalWrapper(const std::shared_ptr<const IIrtExpression>& _leftOperand,
        const std::shared_ptr<const IIrtExpression>& _rightOperand)

    :   leftOperand(_leftOperand),
        rightOperand(_rightOperand)
        {}

    AndConditionalWrapper::AndConditionalWrapper(std::unique_ptr<const ISubtreeWrapper>&& _leftOperand,
        std::unique_ptr<const ISubtreeWrapper>&& _rightOperand)

    :   leftOperand(std::move(_leftOperand)),
        rightOperand(std::move(_rightOperand))
        {}

    OrConditionalWrapper::OrConditionalWrapper(std::unique_ptr<const ISubtreeWrapper>&& _leftOperand,
        std::unique_ptr<const ISubtreeWrapper>&& _rightOperand)

    :   leftOperand(std::move(_leftOperand)),
        rightOperand(std::move(_rightOperand))
        {}

    std::shared_ptr<const IIrtStatement> ExpressionWrapper::ToStatement() const {
        return makeNode<IrtExpressionStatement>(expression);
    }

    std::shared_ptr<const IIrtStatement> ExpressionWrapper::ToConditional(const std::shared_ptr<const IrtLabel>& positiveLabel,
        const std::shared_ptr<const IrtLabel>& negativeLabel) const
    {
        // Подразумевается, что expression имеет тип bool, и тогда можно сравнивать с 1
        return makeNode<IrtCJumpStatement>(expression, makeNode<IrtConstExpression>(1), positiveLabel, negativeLabel);
    }

    std::shared_ptr<const IIrtExpression> ConditionalWrapper::ToExpression() const {
        std::shared_ptr<const IrtLabel> positiveLabel = makeNode<IrtLabel>(L"true");
        std::shared_ptr<const IrtLabel> negativeLabel = makeNode<IrtLabel>(L"false");
        std::shared_ptr<const IIrtExpression> tempExpression = makeNode<IrtTempExpression>(makeNode<IrtTemp>(L"temp"));
        return makeNode<IrtESeqExpression>(
            makeNode<IrtSeqStatement>(
                makeNode<IrtMoveStatement>(tempExpression, makeNode<IrtConstExpression>(1)),
                makeNode<IrtSeqStatement>(
                    ToConditional(positiveLabel, negativeLabel),
                    makeNode<IrtSeqStatement>(
                        makeNode<IrtLabelStatement>(negativeLabel),
                        makeNode<IrtSeqStatement>(
                            makeNode<IrtMoveStatement>(tempExpression, makeNode<IrtConstExpression>(0)),
                            makeNode<IrtLabelStatement>(positiveLabel)
                        )
                    )
                )
            ),
            tempExpression
        );
    }

    std::shared_ptr<const IIrtStatement> RelativeConditionalWrapper::ToConditional(const std::shared_ptr<const IrtLabel>& positiveLabel,
        const std::shared_ptr<const IrtLabel>& negativeLabel) const
    {
        return makeNode<IrtCJumpStatement>(leftOperand, rightOperand, positiveLabel, negativeLabel);
    }

    std::shared_ptr<const IIrtStatement> AndConditionalWrapper::ToConditional(const std::shared_ptr<const IrtLabel>& positiveLabel,
        const std::shared_ptr<const IrtLabel>& negativeLabel) const
    {
        std::shared_ptr<const IrtLabel> midLabel = makeNode<IrtLabel>(L"mid_L");
        return makeNode<IrtSeqStatement>(
            leftOperand->ToConditional(midLabel, negativeLabel),
            makeNode<IrtSeqStatement>(makeNode<IrtLabelStatement>(midLabel), rightOperand->ToConditional(positiveLabel, negativeLabel))
        );
    }

    std::shared_ptr<const IIrtStatement> OrConditionalWrapper::ToConditional(const std::shared_ptr<const IrtLabel>& positiveLabel,
        const std::shared_ptr<const IrtLabel>& negativeLabel) const
    {
        std::shared_ptr<const IrtLabel> midLabel = makeNode<IrtLabel>(L"mid_L");
        return makeNode<IrtSeqStatement>(
            leftOperand->ToConditional(positiveLabel, midLabel),
            makeNode<IrtSeqStatement>(makeNode<IrtLabelStatement>(midLabel), rightOperand->ToConditional(positiveLabel, negativeLabel))
        );
    }

    std::shared_ptr<const IIrtStatement> OppositeConditionalWrapper::ToConditional(const std::shared_ptr<const IrtLabel>& positiveLabel,
        const std::shared_ptr<const IrtLabel>& negativeLabel) const
    {
        return internalWrapper->ToConditional(negativeLabel, positiveLabel);
    }
}


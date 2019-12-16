#include "IrtWrappers.h"
#include "Make.h"

namespace IrTree {

    RelativeConditionalWrapper::RelativeConditionalWrapper(const std::shared_ptr<const IIrtExpression>& _leftOperand,
        const std::shared_ptr<const IIrtExpression>& _rightOperand)

    :   leftOperand(_leftOperand),
        rightOperand(_rightOperand)
        {}

    AndConditionalWrapper::AndConditionalWrapper(const std::shared_ptr<ISubtreeWrapper>& _leftOperand,
        const std::shared_ptr<ISubtreeWrapper>& _rightOperand)

    :   leftOperand(_leftOperand),
        rightOperand(_rightOperand)
        {}

    OrConditionalWrapper::OrConditionalWrapper(const std::shared_ptr<ISubtreeWrapper>& _leftOperand,
        const std::shared_ptr<ISubtreeWrapper>& _rightOperand)

    :   leftOperand(_leftOperand),
        rightOperand(_rightOperand)
        {}

    std::shared_ptr<const IIrtStatement> ExpressionWrapper::ToStatement() const {
        return make<IrtExpressionStatement>(expression);
    }

    std::shared_ptr<const IIrtStatement> ExpressionWrapper::ToConditional(const std::shared_ptr<const IrtLabel>& positiveLabel,
        const std::shared_ptr<const IrtLabel>& negativeLabel) const
    {
        return make<IrtCJumpStatement>(expression, make<IrtConstExpression>(0), positiveLabel, negativeLabel);
    }

    std::shared_ptr<const IIrtExpression> ConditionalWrapper::ToExpression() const {
        std::shared_ptr<const IrtLabel> positiveLabel = make<IrtLabel>(L"true");
        std::shared_ptr<const IrtLabel> negativeLabel = make<IrtLabel>(L"false");
        std::shared_ptr<const IIrtExpression> tempExpression = make<IrtTempExpression>(make<IrtTemp>(L"temp"));
        return make<IrtESeqExpression>(
            make<IrtSeqStatement>(
                make<IrtMoveStatement>(tempExpression, make<IrtConstExpression>(1)),
                make<IrtSeqStatement>(
                    ToConditional(positiveLabel, negativeLabel),
                    make<IrtSeqStatement>(
                        make<IrtLabelStatement>(negativeLabel),
                        make<IrtSeqStatement>(
                            make<IrtMoveStatement>(tempExpression, make<IrtConstExpression>(0)),
                            make<IrtLabelStatement>(positiveLabel)
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
        return make<IrtCJumpStatement>(leftOperand, rightOperand, positiveLabel, negativeLabel);
    }

    std::shared_ptr<const IIrtStatement> AndConditionalWrapper::ToConditional(const std::shared_ptr<const IrtLabel>& positiveLabel,
        const std::shared_ptr<const IrtLabel>& negativeLabel) const
    {
        std::shared_ptr<const IrtLabel> midLabel = make<IrtLabel>(L"mid_L");
        return make<IrtSeqStatement>(
            leftOperand->ToConditional(midLabel, negativeLabel),
            make<IrtSeqStatement>(make<IrtLabelStatement>(midLabel), rightOperand->ToConditional(positiveLabel, negativeLabel))
        );
    }

    std::shared_ptr<const IIrtStatement> OrConditionalWrapper::ToConditional(const std::shared_ptr<const IrtLabel>& positiveLabel,
        const std::shared_ptr<const IrtLabel>& negativeLabel) const
    {
        std::shared_ptr<const IrtLabel> midLabel = make<IrtLabel>(L"mid_L");
        return make<IrtSeqStatement>(
            leftOperand->ToConditional(positiveLabel, midLabel),
            make<IrtSeqStatement>(make<IrtLabelStatement>(midLabel), rightOperand->ToConditional(positiveLabel, negativeLabel))
        );
    }

    std::shared_ptr<const IIrtStatement> OppositeConditionalWrapper::ToConditional(const std::shared_ptr<const IrtLabel>& positiveLabel,
        const std::shared_ptr<const IrtLabel>& negativeLabel) const
    {
        return internalWrapper->ToConditional(negativeLabel, positiveLabel);
    }
}


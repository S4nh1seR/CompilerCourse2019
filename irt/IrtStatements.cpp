#include "IrtStatements.h"

namespace IrTree {

    IrtMoveStatement::IrtMoveStatement(std::unique_ptr<const IIrtExpression>&& _destinationExpression,
        std::unique_ptr<const IIrtExpression>&& _sourceExpression)

    :   destinationExpression(std::move(_destinationExpression)),
        sourceExpression(std::move(_sourceExpression))
        {}

    IrtSeqStatement::IrtSeqStatement(std::unique_ptr<const IIrtStatement>&& _leftStatement,
        std::unique_ptr<const IIrtStatement>&& _rightStatement)

    :   leftStatement(std::move(_leftStatement)),
        rightStatement(std::move(_rightStatement))
        {}

    IrtCJumpStatement::IrtCJumpStatement(std::unique_ptr<const IIrtExpression>&& _leftExpression,
        std::unique_ptr<const IIrtExpression>&& _rightExpression, std::unique_ptr<const IrtLabel>&& _positiveLabel,
        std::unique_ptr<const IrtLabel>&& _negativeLabel)

    :   leftExpression(std::move(_leftExpression)),
        rightExpression(std::move(_rightExpression)),
        positiveLabel(std::move(_positiveLabel)),
        negativeLabel(std::move(_negativeLabel))
        {}
}
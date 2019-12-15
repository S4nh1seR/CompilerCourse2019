#include "IrtStatements.h"

namespace IrTree {

    IrtMoveStatement::IrtMoveStatement(const std::shared_ptr<const IIrtExpression>& _destinationExpression,
        const std::shared_ptr<const IIrtExpression>& _sourceExpression)

    :   destinationExpression(_destinationExpression),
        sourceExpression(_sourceExpression)
        {}

    IrtSeqStatement::IrtSeqStatement(const std::shared_ptr<const IIrtStatement>& _leftStatement,
        const std::shared_ptr<const IIrtStatement>& _rightStatement)

    :   leftStatement(_leftStatement),
        rightStatement(_rightStatement)
        {}

    IrtCJumpStatement::IrtCJumpStatement(const std::shared_ptr<const IIrtExpression>& _leftExpression,
        const std::shared_ptr<const IIrtExpression>& _rightExpression,
        const std::shared_ptr<const IrtLabel>& _positiveLabel,
        const std::shared_ptr<const IrtLabel>& _negativeLabel)

    :   leftExpression(_leftExpression),
        rightExpression(_rightExpression),
        positiveLabel(_positiveLabel),
        negativeLabel(_negativeLabel)
        {}
}
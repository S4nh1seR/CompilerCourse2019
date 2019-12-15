#include "IrtExpressions.h"

#include <algorithm>
#include <cassert>

namespace IrTree {

    IrtBinaryOperationExpression::IrtBinaryOperationExpression(TBinaryOperationType _operationType,
        const std::shared_ptr<const IIrtExpression>& _leftOperand,
        const std::shared_ptr<const IIrtExpression>& _rightOperand)

    :   operationType(_operationType),
        leftOperand(_leftOperand),
        rightOperand(_rightOperand)
        {}

    IrtESeqExpression::IrtESeqExpression(const std::shared_ptr<const IIrtStatement>& _statement,
        const std::shared_ptr<const IIrtExpression>& _expression)

    :   statement(_statement),
        expression(_expression)
        {}

    void IrtExpressionList::GetExpressions(std::vector<std::shared_ptr<const IIrtExpression>>& _expressions) const {
        _expressions.resize(expressions.size());
        std::copy(expressions.begin(), expressions.end(), _expressions.begin());
    }

    std::shared_ptr<const IIrtExpression> IrtExpressionList::GetExpression(int index) const {
        assert(index >=0 && index < expressions.size());
        return expressions[index];
    }

    IrtCallExpression::IrtCallExpression(const std::shared_ptr<const IIrtExpression>& _methodExpression,
        const std::shared_ptr<const IrtExpressionList>& _argumentExpressionList)

    :   methodExpression(_methodExpression),
        argumentExpressionList(_argumentExpressionList)
        {}
}

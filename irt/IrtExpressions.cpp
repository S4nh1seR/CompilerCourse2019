#include "IrtExpressions.h"

#include <cassert>

namespace IrTree {

    IrtBinaryOperationExpression::IrtBinaryOperationExpression(TBinaryOperationType _operationType,
        std::unique_ptr<const IIrtExpression>&& _leftOperand, std::unique_ptr<const IIrtExpression>&& _rightOperand)

    :   operationType(_operationType),
        leftOperand(std::move(_leftOperand)),
        rightOperand(std::move(_rightOperand))
        {}

    IrtESeqExpression::IrtESeqExpression(std::unique_ptr<const IIrtStatement>&& _statement,
        std::unique_ptr<const IIrtExpression>&& _expression)

    :   statement(std::move(_statement)),
        expression(std::move(_expression))
        {}

    void IrtExpressionList::GetExpressions(std::vector<const IIrtExpression*>& _expressions) const {
        _expressions.clear();
        for (int i = 0; i < expressions.size(); ++i) {
            _expressions.push_back(expressions[i].get());
        }
    }

    const IIrtExpression* IrtExpressionList::GetExpression(int index) const {
        assert(index >=0 && index < expressions.size());
        return expressions[index].get();
    }

    IrtCallExpression::IrtCallExpression(std::unique_ptr<const IIrtExpression>&& _methodExpression,
        std::unique_ptr<const IrtExpressionList>&& _argumentExpressionList)

    :   methodExpression(std::move(_methodExpression)),
        argumentExpressionList(std::move(_argumentExpressionList))
        {}
}

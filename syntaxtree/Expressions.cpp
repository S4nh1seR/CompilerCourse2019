#include "Expressions.h"

namespace SyntaxTree {

    BinaryOperationExpression::BinaryOperationExpression(TBinaryOperationType _boType, std::unique_ptr<const IExpression>&& _leftOperand,
        std::unique_ptr<const IExpression>&& _rightOperand)

    :   boType(_boType),
        leftOperand(std::move(_leftOperand)),
        rightOperand(std::move(_rightOperand))
        {}

    SquareBracketExpression::SquareBracketExpression(std::unique_ptr<const IExpression>&& _arrayOperator,
        std::unique_ptr<const IExpression>&& _indexOperand)

    :   arrayOperand(std::move(_arrayOperator)),
        indexOperand(std::move(_indexOperand))
        {}

    MethodCallExpression::MethodCallExpression(std::unique_ptr<const IExpression>&& _objectOperand,
        std::unique_ptr<const Identifier>&& _methodIdentifier)

    :   objectOperand(std::move(_objectOperand)),
        methodIdentifier(std::move(_methodIdentifier))
        {}

    MethodCallExpression::MethodCallExpression(std::unique_ptr<const IExpression>&& _objectOperand,
        std::unique_ptr<const Identifier>&& _methodIdentifier,
        std::vector<std::unique_ptr<const IExpression>>&& _methodArguments)

    :   objectOperand(std::move(_objectOperand)),
        methodIdentifier(std::move(_methodIdentifier)),
        methodArguments(std::move(_methodArguments))
        {}

    const IExpression* MethodCallExpression::GetArgument(int index) const {
        assert(index >= 0 && index < methodArguments.size());
        return methodArguments[index].get();
    }

    void MethodCallExpression::GetAllArguments(std::vector<const IExpression*>& _methodArguments) const {
        _methodArguments.clear();
        for (int i = 0; i < methodArguments.size(); ++i) {
            _methodArguments.push_back(methodArguments[i].get());
        }
    }
}
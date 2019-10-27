#include "Expressions.h"

namespace SyntaxTree {

    BinaryOperationExpression::BinaryOperationExpression(TBinaryOperationType _boType, const IExpression* _leftOperand, const IExpression* _rightOperand)
    :   boType(_boType),
        leftOperand(std::make_unique<IExpression>(_leftOperand)),
        rightOperand(std::make_unique<IExpression>(_rightOperand))
        {}

    SquareBracketExpression::SquareBracketExpression(const IExpression* _arrayOperator, const IExpression* _indexOperand)
    :   arrayOperand(std::make_unique<IExpression>(_arrayOperator)),
        indexOperand(std::make_unique<IExpression>(_indexOperand))
        {}

    MethodCallExpression::MethodCallExpression(const IExpression* _objectOperand, const Identifier* _methodIdentifier)
    :   objectOperand(std::make_unique<IExpression>(_objectOperand)),
        methodIdentifier(std::make_unique<Identifier>(_methodIdentifier))
        {}

    MethodCallExpression::MethodCallExpression(const IExpression* _objectOperand, const Identifier* _methodIdentifier,
        std::vector<const IExpression*> _methodArguments)
    :   objectOperand(std::make_unique<IExpression>(_objectOperand)),
        methodIdentifier(std::make_unique<Identifier>(_methodIdentifier))
    {
        for (auto _methodArgument : _methodArguments) {
            methodArguments.emplace_back(_methodArgument);
        }
    }
}
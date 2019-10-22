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

}
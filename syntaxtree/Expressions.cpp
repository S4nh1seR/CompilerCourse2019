#include "Expressions.h"

namespace SyntaxTree {

    IdentifierExpression::IdentifierExpression(std::unique_ptr<const Identifier>&& _identifier, int _lineNumber)

    : identifier(std::move(_identifier))
    {
        lineNumber = _lineNumber;
    }

    BinaryOperationExpression::BinaryOperationExpression(TBinaryOperationType _boType, std::unique_ptr<const IExpression>&& _leftOperand,
        std::unique_ptr<const IExpression>&& _rightOperand, int _lineNumber)

    :   boType(_boType),
        leftOperand(std::move(_leftOperand)),
        rightOperand(std::move(_rightOperand))
    {
        lineNumber = _lineNumber;
    }

    SquareBracketExpression::SquareBracketExpression(std::unique_ptr<const IExpression>&& _arrayOperator,
        std::unique_ptr<const IExpression>&& _indexOperand, int _lineNumber)

    :   arrayOperand(std::move(_arrayOperator)),
        indexOperand(std::move(_indexOperand))
    {
        lineNumber = _lineNumber;
    }

    LengthExpression::LengthExpression(std::unique_ptr<const IExpression>&& _lengthOperand, int _lineNumber)

    : lengthOperand(std::move(_lengthOperand))
    {
        lineNumber = _lineNumber;
    }

    MethodCallExpression::MethodCallExpression(std::unique_ptr<const IExpression>&& _objectOperand,
        std::unique_ptr<const Identifier>&& _methodIdentifier, int _lineNumber)

    :   objectOperand(std::move(_objectOperand)),
        methodIdentifier(std::move(_methodIdentifier))
    {
        lineNumber = _lineNumber;
    }

    BooleanLiteralExpression::BooleanLiteralExpression(const bool _literalValue, int _lineNumber)

    : literalValue(_literalValue)
    {
        lineNumber = _lineNumber;
    }

    IntegerLiteralExpression::IntegerLiteralExpression(const int _literalValue, int _lineNumber)
    : literalValue(_literalValue)
    {
        lineNumber = _lineNumber;
    }

    MethodCallExpression::MethodCallExpression(std::unique_ptr<const IExpression>&& _objectOperand,
        std::unique_ptr<const Identifier>&& _methodIdentifier,
        std::vector<std::unique_ptr<const IExpression>>&& _methodArguments, int _lineNumber)

    :   objectOperand(std::move(_objectOperand)),
        methodIdentifier(std::move(_methodIdentifier)),
        methodArguments(std::move(_methodArguments))
    {
        lineNumber = _lineNumber;
    }

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

    NewExpression::NewExpression(std::unique_ptr<const Identifier>&& _identifierOperand, int _lineNumber)

    : identifierOperand(std::move(_identifierOperand))
    {
        lineNumber = _lineNumber;
    }

    NewArrayExpression::NewArrayExpression(std::unique_ptr<const IExpression>&& _sizeOperand, int _lineNumber)

    : sizeOperand(std::move(_sizeOperand))
    {
        lineNumber = _lineNumber;
    }

    OppositeExpression::OppositeExpression(std::unique_ptr<const IExpression>&& _sourceExpression, int _lineNumber)

    : sourceExpression(std::move(_sourceExpression))
    {
        lineNumber = _lineNumber;
    }

    ParenthesesExpression::ParenthesesExpression(std::unique_ptr<const IExpression>&& _internalExpression, int _lineNumber)

    : internalExpression(std::move(_internalExpression))
    {
        lineNumber = _lineNumber;
    }

}

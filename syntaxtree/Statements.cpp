
#include "Statements.h"

namespace SyntaxTree {

    ConditionalStatement::ConditionalStatement(const IExpression* _conditionExpression, const IStatement* _positiveStatement, const IStatement* _negativeStatemen)
    :   conditionExpression(std::make_unique<IExpression>(_conditionExpression)),
        positiveStatement(std::make_unique<IStatement>(_positiveStatement)),
        negativeStatement(std::make_unique<IStatement>(_negativeStatemen))
        {}

    LoopStatement::LoopStatement(const IExpression* _conditionExpression, const IStatement* _internalStatement)
    :   conditionExpression(std::make_unique<IExpression>(_conditionExpression)),
        internalStatement(std::make_unique<IStatement>(_internalStatement))
        {}

    AssignmentStatement::AssignmentStatement(const IdentifierExpression* _leftOperand, const IExpression* _rightOperand)
    :   leftOperand(std::make_unique<IdentifierExpression>(_leftOperand)),
        rightOperand(std::make_unique<IExpression>(_rightOperand))
        {}

    ArrayAssignmentStatement::ArrayAssignmentStatement(const IdentifierExpression* _arrayIdentifier, const IExpression* _arrayIndex, const IExpression* _rightOperand)
    :   arrayIdentifier(std::make_unique<IdentifierExpression>(_arrayIdentifier)),
        arrayIndex(std::make_unique<IExpression>(_arrayIndex)),
        rightOperand(std::make_unique<IExpression>(_rightOperand))
        {}
}
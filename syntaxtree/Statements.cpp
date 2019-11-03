
#include "Statements.h"

namespace SyntaxTree {

    ConditionalStatement::ConditionalStatement(std::unique_ptr<const IExpression>&& _conditionExpression,
        std::unique_ptr<const IStatement>&& _positiveStatement, std::unique_ptr<const IStatement>&& _negativeStatement)

    :   conditionExpression(std::move(_conditionExpression)),
        positiveStatement(std::move(_positiveStatement)),
        negativeStatement(std::move(_negativeStatement))
        {}

    LoopStatement::LoopStatement(std::unique_ptr<const IExpression>&& _conditionExpression,
        std::unique_ptr<const IStatement>&& _internalStatement)

    :   conditionExpression(std::move(_conditionExpression)),
        internalStatement(std::move(_internalStatement))
        {}

    AssignmentStatement::AssignmentStatement(std::unique_ptr<const Identifier>&& _leftOperand,
    std::unique_ptr<const IExpression>&& _rightOperand)

    :   leftOperand(std::move(_leftOperand)),
        rightOperand(std::move(_rightOperand))
        {}

    ArrayAssignmentStatement::ArrayAssignmentStatement(std::unique_ptr<const Identifier>&& _arrayIdentifier,
        std::unique_ptr<const IExpression>&& _arrayIndex, std::unique_ptr<const IExpression>&& _rightOperand)

    :   arrayIdentifier(std::move(_arrayIdentifier)),
        arrayIndex(std::move(_arrayIndex)),
        rightOperand(std::move(_rightOperand))
        {}

    CompoundStatement::CompoundStatement(std::unique_ptr<std::vector<std::unique_ptr<const IStatement>>>&& _internalStatements)
    :   internalStatements(std::move(_internalStatements))
        {}

    const IStatement* CompoundStatement::GetStatement(int index) const {
        assert(index >= 0 && index < internalStatements->size());
        return (*internalStatements)[index].get();
    }

    void CompoundStatement::GetAllStatements(std::vector<const IStatement*>& _internalStatements) const {
        _internalStatements.clear();
        for (int i = 0; i < internalStatements->size(); ++i) {
            _internalStatements.push_back((*internalStatements)[i].get());
        }
    }
}
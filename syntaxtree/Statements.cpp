
#include "Statements.h"

namespace SyntaxTree {

    ConditionalStatement::ConditionalStatement(std::unique_ptr<const IExpression>&& _conditionExpression,
        std::unique_ptr<const IStatement>&& _positiveStatement, std::unique_ptr<const IStatement>&& _negativeStatement, int _line)

    :   conditionExpression(std::move(_conditionExpression)),
        positiveStatement(std::move(_positiveStatement)),
        negativeStatement(std::move(_negativeStatement))
        {line = _line;}

    LoopStatement::LoopStatement(std::unique_ptr<const IExpression>&& _conditionExpression,
        std::unique_ptr<const IStatement>&& _internalStatement, int _line)

    :   conditionExpression(std::move(_conditionExpression)),
        internalStatement(std::move(_internalStatement))
        {line = _line;}

    AssignmentStatement::AssignmentStatement(std::unique_ptr<const Identifier>&& _leftOperand,
    std::unique_ptr<const IExpression>&& _rightOperand, int _line)

    :   leftOperand(std::move(_leftOperand)),
        rightOperand(std::move(_rightOperand))
        {line = _line;}

    ArrayAssignmentStatement::ArrayAssignmentStatement(std::unique_ptr<const Identifier>&& _arrayIdentifier,
        std::unique_ptr<const IExpression>&& _arrayIndex, std::unique_ptr<const IExpression>&& _rightOperand, int _line)

    :   arrayIdentifier(std::move(_arrayIdentifier)),
        arrayIndex(std::move(_arrayIndex)),
        rightOperand(std::move(_rightOperand))
        {line = _line;}

    CompoundStatement::CompoundStatement(std::vector<std::unique_ptr<const IStatement>>&& _internalStatements, int _line)
    :   internalStatements(std::move(_internalStatements))
        {line = _line;}

    const IStatement* CompoundStatement::GetStatement(int index) const {
        assert(index >= 0 && index < internalStatements.size());
        return internalStatements[index].get();
    }

    void CompoundStatement::GetAllStatements(std::vector<const IStatement*>& _internalStatements) const {
        _internalStatements.clear();
        for (int i = 0; i < internalStatements.size(); ++i) {
            _internalStatements.push_back(internalStatements[i].get());
        }
    }
}

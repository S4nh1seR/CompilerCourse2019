
#include "Statements.h"

namespace SyntaxTree {

    ConditionalStatement::ConditionalStatement(std::unique_ptr<const IExpression>&& _conditionExpression,
        std::unique_ptr<const IStatement>&& _positiveStatement, std::unique_ptr<const IStatement>&& _negativeStatement, int _lineNumber)

    :   conditionExpression(std::move(_conditionExpression)),
        positiveStatement(std::move(_positiveStatement)),
        negativeStatement(std::move(_negativeStatement))
    {
        lineNumber = _lineNumber;
    }

    LoopStatement::LoopStatement(std::unique_ptr<const IExpression>&& _conditionExpression,
        std::unique_ptr<const IStatement>&& _internalStatement, int _lineNumber)

    :   conditionExpression(std::move(_conditionExpression)),
        internalStatement(std::move(_internalStatement))
    {
        lineNumber = _lineNumber;
    }

    PrintStatement::PrintStatement(std::unique_ptr<const IExpression>&& _printOperand, int _lineNumber)

    : printOperand(std::move(_printOperand))
    {
        lineNumber = _lineNumber;
    }

    AssignmentStatement::AssignmentStatement(std::unique_ptr<const Identifier>&& _leftOperand,
        std::unique_ptr<const IExpression>&& _rightOperand, int _lineNumber)

    :   leftOperand(std::move(_leftOperand)),
        rightOperand(std::move(_rightOperand))
    {
        lineNumber = _lineNumber;
    }

    ArrayAssignmentStatement::ArrayAssignmentStatement(std::unique_ptr<const Identifier>&& _arrayIdentifier,
        std::unique_ptr<const IExpression>&& _arrayIndex, std::unique_ptr<const IExpression>&& _rightOperand, int _lineNumber)

    :   arrayIdentifier(std::move(_arrayIdentifier)),
        arrayIndex(std::move(_arrayIndex)),
        rightOperand(std::move(_rightOperand))
    {
        lineNumber = _lineNumber;
    }

    CompoundStatement::CompoundStatement(std::vector<std::unique_ptr<const IStatement>>&& _internalStatements, int _lineNumber)

    :   internalStatements(std::move(_internalStatements))
    {
        lineNumber = _lineNumber;
    }

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

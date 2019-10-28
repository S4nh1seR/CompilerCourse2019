
#include "Statements.h"

namespace SyntaxTree {

    ConditionalStatement::ConditionalStatement(const IExpression* _conditionExpression, const IStatement* _positiveStatement, const IStatement* _negativeStatement)
    :   conditionExpression(_conditionExpression),
        positiveStatement(_positiveStatement),
        negativeStatement(_negativeStatement)
        {}

    LoopStatement::LoopStatement(const IExpression* _conditionExpression, const IStatement* _internalStatement)
    :   conditionExpression(_conditionExpression),
        internalStatement(_internalStatement)
        {}

    AssignmentStatement::AssignmentStatement(const Identifier* _leftOperand, const IExpression* _rightOperand)
    :   leftOperand(_leftOperand),
        rightOperand(_rightOperand)
        {}

    ArrayAssignmentStatement::ArrayAssignmentStatement(const Identifier* _arrayIdentifier, const IExpression* _arrayIndex, const IExpression* _rightOperand)
    :   arrayIdentifier(_arrayIdentifier),
        arrayIndex(_arrayIndex),
        rightOperand(_rightOperand)
        {}

    CompoundStatement::CompoundStatement(const std::vector<const IStatement*>& _internalStatements) {
        for (auto _internalStatement : _internalStatements) {
            internalStatements.emplace_back(_internalStatement);
        }
    }

    const IStatement* CompoundStatement::GetStatement(int index) const {
        assert(index >= 0 && index < internalStatements.size());
        return internalStatements[index].get();
    }

    void CompoundStatement::GetAllStatements(std::vector<const IStatement*>& _internalStatements) {
        _internalStatements.clear();
        for (int i = 0; i < internalStatements.size(); ++i) {
            _internalStatements.push_back(internalStatements[i].get());
        }
    }
}
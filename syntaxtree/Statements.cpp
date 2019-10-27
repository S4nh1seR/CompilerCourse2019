
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

    AssignmentStatement::AssignmentStatement(const Identifier* _leftOperand, const IExpression* _rightOperand)
    :   leftOperand(std::make_unique<Identifier>(_leftOperand)),
        rightOperand(std::make_unique<IExpression>(_rightOperand))
        {}

    ArrayAssignmentStatement::ArrayAssignmentStatement(const Identifier* _arrayIdentifier, const IExpression* _arrayIndex, const IExpression* _rightOperand)
    :   arrayIdentifier(std::make_unique<Identifier>(_arrayIdentifier)),
        arrayIndex(std::make_unique<IExpression>(_arrayIndex)),
        rightOperand(std::make_unique<IExpression>(_rightOperand))
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
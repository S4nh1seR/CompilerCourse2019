
#include "Expressions.h"

namespace SyntaxTree {


    BinOpExpression::BinOpExpression(TBinOperationType _boType, const ISyntaxTreeNode* _leftOperand, const ISyntaxTreeNode* _rightOperand)
    :   boType(_boType),
        leftOperand(std::make_unique<ISyntaxTreeNode>(_leftOperand)),
        rightOperand(std::make_unique<ISyntaxTreeNode>(_rightOperand))
        {}

    SquareBracketExpression::SquareBracketExpression(const ISyntaxTreeNode* _arrayOperator, const ISyntaxTreeNode* _indexOperand)
    :   arrayOperand(std::make_unique<ISyntaxTreeNode>(_arrayOperator)),
        indexOperand(std::make_unique<ISyntaxTreeNode>(_indexOperand))
        {}

}

#include "Expressions.h"

namespace SyntaxTree {


    BinOpExpression::BinOpExpression(TBinOperationTyp _boType, const ISyntaxTreeNode* _leftOperand, const ISyntaxTreeNode* _rightOperand)
    :   boType(_boType),
        leftOperand(_leftOperand),
        rightOperand(_rightOperand)
        {}

    BinOpExpression::SquareBracketExpression(const ISyntaxTreeNode* _arrayOperator, const ISyntaxTreeNode* _indexOperand)
    :   arrayOperand(_arrayOperand),
        indexOperand(_indexOperand)
        {}

}
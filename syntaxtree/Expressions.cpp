
#include "Expressions.h"

namespace SyntaxTree {


    BinOpExpression::BinOpExpression(TBinOperationTyp _boType, const ISyntaxTreeNode* _leftOperand, const ISyntaxTreeNode* _rightOperand)
    :   boType(_boType),
        leftOperand(_leftOperand),
        rightOperand(_rightOperand)
        {}


}
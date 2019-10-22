#pragma once

#include <memory>

#include "SyntaxTreeNode.h"

namespace SyntaxTree {

    class IExpression : public ISyntaxTreeNode {
    };

    enum TBinOperationType {
        BOT_Add,
        BOT_Sub,
        BOT_Mul,
        BOT_Div,
        BOT_Mod,

        BOT_Or,
        BOT_And,

        BOT_Less
    };

    class BinOpExpression : public IExpression {
    public:
        BinOpExpression(TBinOperationType _boType, const ISyntaxTreeNode* _leftOperand, const ISyntaxTreeNode* _rightOperand);

        virtual void AcceptVisitor(const IVisitor& visitor) const override { visitor.VisitNode(this); }

        TBinOperationType GetOperationType() const { return boType; }
        const ISyntaxTreeNode* GetLeftOperand() const { return leftOperand; }
        const ISyntaxTreeNode* GetRightOperand() const { return rightOperand; }

    private:
        TBinOperationType boType;

        std::unique_ptr<ISyntaxTreeNode> leftOperand;
        std::unique_ptr<ISyntaxTreeNode> rightOperand;
    };

}
#pragma once

namespace IrTree {

    class IrtGoal;

    class IrtBinaryOperationExpression;
    class IrtConstExpression;
    class IrtESeqExpression;
    class IrtMemoryExpression;
    class IrtExpressionList;
    class IrtCallExpression;
    class IrtNameExpression;
    class IrtTempExpression;

    class IrtExpressionStatement;
    class IrtMoveStatement;
    class IrtSeqStatement;
    class IrtJumpStatement;
    class IrtCJumpStatement;
    class IrtLabelStatement;

    class IrtLabel;
    class IrtTemp;

    class IIrtVisitor {
    public:
        virtual ~IIrtVisitor() {}

        virtual void VisitNode(const IrtGoal* goal) = 0;

        virtual void VisitNode(const IrtBinaryOperationExpression* expression) = 0;
        virtual void VisitNode(const IrtConstExpression* expression) = 0;
        virtual void VisitNode(const IrtESeqExpression* expression) = 0;
        virtual void VisitNode(const IrtMemoryExpression* expression) = 0;
        virtual void VisitNode(const IrtExpressionList* expression) = 0;
        virtual void VisitNode(const IrtCallExpression* expression) = 0;
        virtual void VisitNode(const IrtNameExpression* expression) = 0;
        virtual void VisitNode(const IrtTempExpression* expression) = 0;

        virtual void VisitNode(const IrtExpressionStatement* statement) = 0;
        virtual void VisitNode(const IrtMoveStatement* statement) = 0;
        virtual void VisitNode(const IrtSeqStatement* statement) = 0;
        virtual void VisitNode(const IrtJumpStatement* statement) = 0;
        virtual void VisitNode(const IrtCJumpStatement* statement) = 0;
        virtual void VisitNode(const IrtLabelStatement* statement) = 0;

        virtual void VisitNode(const IrtLabel* label) = 0;
        virtual void VisitNode(const IrtTemp* temp) = 0;
    };
}
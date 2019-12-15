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

        virtual void VisitNode(const IrtGoal* identifier) = 0;

        virtual void VisitNode(const IrtBinaryOperationExpression* identifier) = 0;
        virtual void VisitNode(const IrtConstExpression* identifier) = 0;
        virtual void VisitNode(const IrtESeqExpression* identifier) = 0;
        virtual void VisitNode(const IrtMemoryExpression* identifier) = 0;
        virtual void VisitNode(const IrtExpressionList* identifier) = 0;
        virtual void VisitNode(const IrtCallExpression* identifier) = 0;
        virtual void VisitNode(const IrtNameExpression* identifier) = 0;
        virtual void VisitNode(const IrtTempExpression* identifier) = 0;

        virtual void VisitNode(const IrtExpressionStatement* identifier) = 0;
        virtual void VisitNode(const IrtMoveStatement* identifier) = 0;
        virtual void VisitNode(const IrtSeqStatement* identifier) = 0;
        virtual void VisitNode(const IrtJumpStatement* identifier) = 0;
        virtual void VisitNode(const IrtCJumpStatement* identifier) = 0;
        virtual void VisitNode(const IrtLabelStatement* identifier) = 0;

        virtual void VisitNode(const IrtLabel* identifier) = 0;
        virtual void VisitNode(const IrtTemp* identifier) = 0;
    };
}
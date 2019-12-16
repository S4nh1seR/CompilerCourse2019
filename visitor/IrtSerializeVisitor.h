#pragma once

#include "IrtVisitor.h"

#include <IrTreeNode.h>
#include <Graph.h>

#include <memory>
#include <unordered_map>

using SyntaxTree::DirectedGraph;

namespace IrTree {

    class IrtSerializeVisitor : public IIrtVisitor {
    public:

        void RoundLaunch(std::shared_ptr<DirectedGraph>& _graph_ptr, const std::shared_ptr<const IrtGoal>& _root);

        void VisitNode(const IrtGoal* goal) override;

        void VisitNode(const IrtBinaryOperationExpression* expression) override;
        void VisitNode(const IrtConstExpression* expression) override;
        void VisitNode(const IrtESeqExpression* expression) override;
        void VisitNode(const IrtMemoryExpression* expression) override;
        void VisitNode(const IrtExpressionList* expression) override;
        void VisitNode(const IrtCallExpression* expression) override;
        void VisitNode(const IrtNameExpression* expression) override;
        void VisitNode(const IrtTempExpression* expression) override;

        void VisitNode(const IrtExpressionStatement* statement) override;
        void VisitNode(const IrtMoveStatement* statement) override;
        void VisitNode(const IrtSeqStatement* statement) override;
        void VisitNode(const IrtJumpStatement* statement) override;
        void VisitNode(const IrtCJumpStatement* statement) override;
        void VisitNode(const IrtLabelStatement* statement) override;

        void VisitNode(const IrtLabel* label) override;
        void VisitNode(const IrtTemp* temp) override;

    private:


    };
}
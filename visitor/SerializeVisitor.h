#pragma once

#include <Graph.h>
#include "Visitor.h"
#include <string>
#include <memory>
#include <unordered_map>
#include <SyntaxTreeNode.h>
#include <exception>
#include <vector>

namespace SyntaxTree  {

    class NotImplementedException : public std::logic_error
    {
    public:
        NotImplementedException () : std::logic_error{"Function not yet implemented."} {}
    };

    class SerializeVisitor: public IVisitor {
    public:
        SerializeVisitor() = default;

        void RoundLaunch(std::shared_ptr<DirectedGraph>& _graph_ptr, const ISyntaxTreeNode* _root_syntax_tree_ptr);

        void VisitNode(const Identifier* identifier) override;

        void VisitNode(const IdentifierExpression* identifierExpression) override;
        void VisitNode(const BinaryOperationExpression* binaryOperationExpression) override;
        void VisitNode(const SquareBracketExpression* squareBracketExpression) override;
        void VisitNode(const LengthExpression* lengthExpression) override;
        void VisitNode(const MethodCallExpression* methodCallExpression) override;
        void VisitNode(const BooleanLiteralExpression* booleanLiteralExpression) override;
        void VisitNode(const IntegerLiteralExpression* integerLiteralExpression) override;
        void VisitNode(const ThisExpression* thisExpression) override;
        void VisitNode(const NewExpression* newExpression) override;
        void VisitNode(const NewArrayExpression* newArrayExpression) override;
        void VisitNode(const OppositeExpression* oppositeExpression) override;
        void VisitNode(const ParenthesesExpression* parenthesesExpression) override;

        void VisitNode(const CompoundStatement* compoundStatement) override;
        void VisitNode(const ConditionalStatement* conditionalStatement) override;
        void VisitNode(const LoopStatement* loopStatement) override;
        void VisitNode(const PrintStatement* printStatement) override;
        void VisitNode(const AssignmentStatement* assignmentStatement) override;
        void VisitNode(const ArrayAssignmentStatement* arrayAssignmentStatement) override;

        void VisitNode(const Type* type) override;

        void VisitNode(const ClassDeclaration* classDeclaration) override;
        void VisitNode(const VariableDeclaration* variableDeclaration) override;
        void VisitNode(const MethodDeclaration* methodDeclaration) override;

        void VisitNode(const Goal* goal) override;
        void VisitNode(const MainClass* mainClass) override;

    private:

        void addNoRootNodeToGraph(const ISyntaxTreeNode* node, const std::wstring& nodeGraphName);
        void bindChildrenNode(const ISyntaxTreeNode* childrenNode, const ISyntaxTreeNode* node, bool addToQueue);

    private:

        struct CNodePrefixNumber{
            std::wstring prefix;
            unsigned int number;

            CNodePrefixNumber(std::wstring _prefix, int _number) : prefix(std::move(_prefix)), number(_number) {}
            explicit CNodePrefixNumber(std::wstring _prefix) : prefix(std::move(_prefix)), number(0) {}
        };

        struct CNodesNameUniqueMaker{
            CNodePrefixNumber identifierNode {L"Id"};

            CNodePrefixNumber identifierExpressionNode {L"IdExp"};

            CNodePrefixNumber addOperationExpressionNode {L"AddOpExp"};
            CNodePrefixNumber subOperationExpressionNode {L"SubOpExp"};
            CNodePrefixNumber mulOperationExpressionNode {L"MulOpExp"};
            CNodePrefixNumber modOperationExpressionNode {L"ModOpExp"};
            CNodePrefixNumber orOperationExpressionNode {L"OrOpExp"};
            CNodePrefixNumber andOperationExpressionNode {L"AndOpExp"};
            CNodePrefixNumber lessOperationExpressionNode {L"LessOpExp"};

            CNodePrefixNumber squareBracketExpressionNode {L"SquareBracketExp"};
            CNodePrefixNumber lengthExpressionNode {L"LengthExp"};
            CNodePrefixNumber methodCallExpressionNode {L"MethodCallExp"};
            CNodePrefixNumber booleanLiteralExpressionNode {L"BooleanLiteralExp"};
            CNodePrefixNumber integerLiteralExpressionNode {L"IntegerLiteralExp"};
            CNodePrefixNumber thisExpressionNode {L"ThisExp"};
            CNodePrefixNumber newExpressionNode {L"NewExp"};
            CNodePrefixNumber newArrayExpressionNode {L"NewArrayExp"};
            CNodePrefixNumber oppositeExpressionNode {L"OppositeExp"};
            CNodePrefixNumber parenthesesExpressionNode {L"ParenthesesExp"};

            CNodePrefixNumber compoundStatementNode {L"CompoundStm"};
            CNodePrefixNumber conditionalStatementNode {L"ConditionalStm"};
            CNodePrefixNumber loopStatementNode {L"LoopStm"};
            CNodePrefixNumber printStatementNode {L"PrintStm"};
            CNodePrefixNumber assignmentStatementNode {L"AssignmentStm"};
            CNodePrefixNumber arrayAssignmentStatementNode {L"ArrayAssignmentStm"};

            CNodePrefixNumber intTypeNode {L"IntType"};
            CNodePrefixNumber booleanTypeNode {L"BooleanType"};
            CNodePrefixNumber intArrayTypeNode {L"IntArrayType"};
            CNodePrefixNumber identifierTypeNode {L"IdentifierType"};

            CNodePrefixNumber classDeclarationNode {L"ClassDecl"};
            CNodePrefixNumber variableDeclarationNode {L"VariableDecl"};
            CNodePrefixNumber methodDeclarationNode {L"MethodDecl"};

            CNodePrefixNumber goalNode {L"Goal"};
            CNodePrefixNumber mainClassNode {L"MainClass"};
        } nodesNameUniqueMaker;

        std::wstring makeUniqueNameAndUpdate(CNodePrefixNumber& nodePrefixNumber);

    private:

        std::shared_ptr<DirectedGraph> graph_ptr {nullptr};
        std::vector<const ISyntaxTreeNode*> ptrs_queue;
        std::unordered_map<const ISyntaxTreeNode*, const ISyntaxTreeNode*> parent_mapping;
        std::unordered_map<const ISyntaxTreeNode*, const std::wstring> name_mapping;

    };
}

#pragma once

#include <Graph.h>
#include "Visitor.h"
#include <string>
#include <memory>
#include <unordered_map>
#include <SyntaxTreeNode.h>
#include <exception>

namespace SyntaxTree  {

    class NotImplementedException : public std::logic_error
    {
    public:
        NotImplementedException () : std::logic_error{"Function not yet implemented."} {}
    };

    class SerializeVisitor: public IVisitor {
    public:
        explicit SerializeVisitor(std::shared_ptr<DirectedGraph>& _graph_ptr) : graph_ptr(_graph_ptr) {}

        void VisitNode(const Identifier* identifier) override;

        void VisitNode(const IdentifierExpression* identifierExpression) override ;
        void VisitNode(const SquareBracketExpression* squareBracketExpression) override ;
        void VisitNode(const LengthExpression* lengthExpression) override ;
        void VisitNode(const MethodCallExpression* methodCallExpression) override ;
        void VisitNode(const BooleanLiteralExpression* booleanLiteralExpression) override ;
        void VisitNode(const IntegerLiteralExpression* integerLiteralExpression) override ;
        void VisitNode(const ThisExpression* thisExpression) override ;
        void VisitNode(const NewExpression* newExpression) override ;
        void VisitNode(const NewArrayExpression* newArrayExpression) override ;
        void VisitNode(const OppositeExpression* oppositeExpression) override ;
        void VisitNode(const ParenthesesExpression* parenthesesExpression) override ;

        void VisitNode(const CompoundStatement* compoundStatement) override ;
        void VisitNode(const ConditionalStatement* conditionalStatement) override ;
        void VisitNode(const LoopStatement* loopStatement) override ;
        void VisitNode(const PrintStatement* printStatement) override ;
        void VisitNode(const AssignmentStatement* assignmentStatement) override ;
        void VisitNode(const ArrayAssignmentStatement* arrayAssignmentStatement) override ;

        void VisitNode(const IntType* intType) override ;
        void VisitNode(const BooleanType* booleanType) override ;
        void VisitNode(const IntArrayType* intArrayType) override ;
        void VisitNode(const IdentifierType* identifierType) override;

        void VisitNode(const ClassDeclaration* classDeclaration) override ;
        void VisitNode(const VariableDeclaration* variableDeclaration) override ;
        void VisitNode(const MethodDeclaration* methodDeclaration) override ;

        void VisitNode(const Goal* goal) override ;
        void VisitNode(const MainClass* mainClass) override ;

    private:

        struct CNodePrefixNumber{
            std::wstring prefix;
            unsigned int number;

            CNodePrefixNumber(std::wstring _prefix, int _number) : prefix(std::move(_prefix)), number(_number) {}
            explicit CNodePrefixNumber(std::wstring _prefix) : prefix(std::move(_prefix)), number(0) {}
        };

        struct CNodesNameUniqueMaker{
            CNodePrefixNumber identifierNode {L"Identifier"};

            CNodePrefixNumber identifierExpressionNode {L"IdentifierExpression"};
            CNodePrefixNumber squareBracketExpressionNode {L"SquareBracketExpression"};
            CNodePrefixNumber lengthExpressionNode {L"LengthExpression"};
            CNodePrefixNumber methodCallExpressionNode {L"MethodCallExpression"};
            CNodePrefixNumber booleanLiteralExpressionNode {L"BooleanLiteralExpression"};
            CNodePrefixNumber integerLiteralExpressionNode {L"IntegerLiteralExpression"};
            CNodePrefixNumber thisExpressionNode {L"ThisExpression"};
            CNodePrefixNumber newExpressionNode {L"NewExpression"};
            CNodePrefixNumber newArrayExpressionNode {L"NewArrayExpression"};
            CNodePrefixNumber oppositeExpressionNode {L"OppositeExpression"};
            CNodePrefixNumber parenthesesExpressionNode {L"ParenthesesExpression"};

            CNodePrefixNumber compoundStatementNode {L"CompoundStatement"};
            CNodePrefixNumber conditionalStatementNode {L"ConditionalStatement"};
            CNodePrefixNumber loopStatementNode {L"LoopStatement"};
            CNodePrefixNumber printStatementNode {L"PrintStatement"};
            CNodePrefixNumber assignmentStatementNode {L"AssignmentStatement"};
            CNodePrefixNumber arrayAssignmentStatementNode {L"ArrayAssignmentStatement"};

            CNodePrefixNumber intTypeNode {L"IntType"};
            CNodePrefixNumber booleanTypeNode {L"BooleanType"};
            CNodePrefixNumber intArrayTypeNode {L"IntArrayType"};
            CNodePrefixNumber identifierTypeNode {L"IdentifierType"};

            CNodePrefixNumber classDeclarationNode {L"ClassDeclaration"};
            CNodePrefixNumber variableDeclarationNode {L"VariableDeclaration"};
            CNodePrefixNumber methodDeclarationNode {L"MethodDeclaration"};

            CNodePrefixNumber goalNode {L"Goal"};
            CNodePrefixNumber mainClassNode {L"MainClass"};
        } nodesNameUniqueMaker;

        std::wstring makeUniqueNameAndUpdate(CNodePrefixNumber& nodePrefixNumber);

    private:
        std::shared_ptr<DirectedGraph> graph_ptr;
        std::unordered_map<ISyntaxTreeNode*, std::wstring> ptrs_mapping;

    };
}

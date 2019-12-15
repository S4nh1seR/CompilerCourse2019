#pragma once

#include "Visitor.h"

namespace SyntaxTree {

    class IrTreeBuilder : public IVisitor {
    public:
        IrTreeBuilder() = default;
        virtual ~IrTreeBuilder() {}

        virtual void VisitNode(const Identifier* identifier) override;

        virtual void VisitNode(const IdentifierExpression* identifierExpression) override;
        virtual void VisitNode(const BinaryOperationExpression* binaryOperationExpression) override;
        virtual void VisitNode(const SquareBracketExpression* squareBracketExpression) override;
        virtual void VisitNode(const LengthExpression* lengthExpression) override;
        virtual void VisitNode(const MethodCallExpression* methodCallExpression) override;
        virtual void VisitNode(const BooleanLiteralExpression* booleanLiteralExpression) override;
        virtual void VisitNode(const IntegerLiteralExpression* integerLiteralExpression) override;
        virtual void VisitNode(const ThisExpression* thisExpression) override;
        virtual void VisitNode(const NewExpression* newExpression) override;
        virtual void VisitNode(const NewArrayExpression* newArrayExpression) override;
        virtual void VisitNode(const OppositeExpression* oppositeExpression) override;
        virtual void VisitNode(const ParenthesesExpression* parenthesesExpression) override;

        virtual void VisitNode(const CompoundStatement* compoundStatement) override;
        virtual void VisitNode(const ConditionalStatement* conditionalStatement) override;
        virtual void VisitNode(const LoopStatement* loopStatement) override;
        virtual void VisitNode(const PrintStatement* printStatement) override;
        virtual void VisitNode(const AssignmentStatement* assignmentStatement) override;
        virtual void VisitNode(const ArrayAssignmentStatement* arrayAssignmentStatement) override;

        virtual void VisitNode(const Type* type) override;

        virtual void VisitNode(const ClassDeclaration* classDeclaration) override;
        virtual void VisitNode(const VariableDeclaration* variableDeclaration) override;
        virtual void VisitNode(const MethodDeclaration* methodDeclaration) override;

        virtual void VisitNode(const Goal* goal) override;
        virtual void VisitNode(const MainClass* mainClass) override;

    private:

    };
}
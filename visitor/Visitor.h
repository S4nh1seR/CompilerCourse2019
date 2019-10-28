#pragma once

#include <Identifier.h>

namespace SyntaxTree {
    // identifier
    class Identifier;
    // expressions
    class IdentifierExpression;
    class BinaryOperationExpression;
    class SquareBracketExpression;
    class LengthExpression;
    class MethodCallExpression;
    class BooleanLiteralExpression;
    class IntegerLiteralExpression;
    class ThisExpression;
    class NewExpression;
    class NewArrayExpression;
    class OppositeExpression;
    class ParenthesesExpression;
    // statements
    class CompoundStatement;
    class ConditionalStatement;
    class LoopStatement;
    class PrintStatement;
    class AssignmentStatement;
    class ArrayAssignmentStatement;
    // types
    class IntType;
    class BooleanType;
    class IntArrayType;
    class IdentifierType;
    // declarations
    class ClassDeclaration;
    class VariableDeclaration;
    class MethodDeclaration;
    // goal
    class Goal;
    // mainClass
    class MainClass;

    class IVisitor{
    public:
        IVisitor() = default;

        virtual void VisitNode(const Identifier* identifier) = 0;

        virtual void VisitNode(const IdentifierExpression* identifierExpression) = 0;
        virtual void VisitNode(const BinaryOperationExpression* binaryOperationExpression) = 0;
        virtual void VisitNode(const SquareBracketExpression* squareBracketExpression) = 0;
        virtual void VisitNode(const LengthExpression* lengthExpression) = 0;
        virtual void VisitNode(const MethodCallExpression* methodCallExpression) = 0;
        virtual void VisitNode(const BooleanLiteralExpression* booleanLiteralExpression) = 0;
        virtual void VisitNode(const IntegerLiteralExpression* integerLiteralExpression) = 0;
        virtual void VisitNode(const ThisExpression* thisExpression) = 0;
        virtual void VisitNode(const NewExpression* newExpression) = 0;
        virtual void VisitNode(const NewArrayExpression* newArrayExpression) = 0;
        virtual void VisitNode(const OppositeExpression* oppositeExpression) = 0;
        virtual void VisitNode(const ParenthesesExpression* parenthesesExpression) = 0;

        virtual void VisitNode(const CompoundStatement* compoundStatement) = 0;
        virtual void VisitNode(const ConditionalStatement* conditionalStatement) = 0;
        virtual void VisitNode(const LoopStatement* loopStatement) = 0;
        virtual void VisitNode(const PrintStatement* printStatement) = 0;
        virtual void VisitNode(const AssignmentStatement* assignmentStatement) = 0;
        virtual void VisitNode(const ArrayAssignmentStatement* arrayAssignmentStatement) = 0;

        virtual void VisitNode(const IntType* intType) = 0;
        virtual void VisitNode(const BooleanType* booleanType) = 0;
        virtual void VisitNode(const IntArrayType* intArrayType) = 0;
        virtual void VisitNode(const IdentifierType* identifierType) = 0;

        virtual void VisitNode(const ClassDeclaration* classDeclaration) = 0;
        virtual void VisitNode(const VariableDeclaration* variableDeclaration) = 0;
        virtual void VisitNode(const MethodDeclaration* methodDeclaration) = 0;

        virtual void VisitNode(const Goal* goal) = 0;
        virtual void VisitNode(const MainClass* mainClass) = 0;
    };
}

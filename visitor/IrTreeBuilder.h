#pragma once

#include "Visitor.h"
#include "IrtWrappers.h"
#include <SymbolTable.h>

namespace SyntaxTree {

    class IStatement;

    class IrTreeBuilder : public IVisitor {
    public:
        IrTreeBuilder(const std::shared_ptr<const SymbolTable>& _symbolTable) : symbolTable(_symbolTable) {}
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

        void RoundLaunch(const Goal* syntaxTreeRoot);
        std::shared_ptr<const IrTree::IrtGoal> GetGoal() const { return goal; }

    private:
        void buildCompoundStatement(const std::vector<const IStatement*>& statements);
        inline const ClassInfo* getClassByType(const Type* type);

        std::shared_ptr<IrTree::IrtGoal> goal{nullptr};

        std::shared_ptr<const SymbolTable> symbolTable;
        const ClassInfo* currentClass{nullptr};
        const MethodInfo* currentMethod{nullptr};
        const ClassInfo* currentObjectClass{nullptr};
        std::unique_ptr<const IrTree::ISubtreeWrapper> currentWrapper{nullptr};
    };
}
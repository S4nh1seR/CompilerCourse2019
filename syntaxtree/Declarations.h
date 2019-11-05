#pragma once

#include "Statements.h"
#include "Types.h"

#include <Visitor.h>

namespace SyntaxTree {

    class Arguments {
    public:
        Arguments() = default;
        Arguments(Arguments&&) = default;

        void AddArgument(std::unique_ptr<const IType>&& argumentType, std::unique_ptr<const Identifier>&& argumentIdentifier) {
            argumentsTypes->push_back(std::move(argumentType));
            argumentsIdentifiers->push_back(std::move(argumentIdentifier));
        }
        std::unique_ptr<std::vector<std::unique_ptr<const IType>>>&& MoveTypes() { return std::move(argumentsTypes); }
        std::unique_ptr<std::vector<std::unique_ptr<const Identifier>>>&& MoveIdentifiers() { return std::move(argumentsIdentifiers); }
    private:
        std::unique_ptr<std::vector<std::unique_ptr<const IType>>> argumentsTypes;
        std::unique_ptr<std::vector<std::unique_ptr<const Identifier>>> argumentsIdentifiers;
    };

    class Declaration : public ISyntaxTreeNode {

    };

    class VariableDeclaration : public Declaration {
    public:
        VariableDeclaration(std::unique_ptr<const IType>&& _declarationType, std::unique_ptr<const Identifier>&& _declarationIdentifier);

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IType* GetDeclarationType() const { return declarationType.get(); }
        const Identifier* GetDeclarationIdentifier() const { return declarationIdentifier.get(); }
    private:
        std::unique_ptr<const IType> declarationType;
        std::unique_ptr<const Identifier> declarationIdentifier;
    };

    class MethodDeclaration : public Declaration {
    public:
        MethodDeclaration(std::unique_ptr<const IType>&& _returnType, std::unique_ptr<const Identifier>&& _classIdentifier,
            std::unique_ptr<const IExpression>&& _returnExpression,
            std::unique_ptr<std::vector<std::unique_ptr<const IType>>>&& _argumentTypes,
            std::unique_ptr<std::vector<std::unique_ptr<const Identifier>>>&& _argumentIdentifiers,
            std::unique_ptr<std::vector<std::unique_ptr<const VariableDeclaration>>>&& _variableDeclarations,
            std::unique_ptr<std::vector<std::unique_ptr<const IStatement>>>&& _statements);

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        const IType* GetReturnType() const { return returnType.get(); }
        const Identifier* GetClassIdentifier() const { return classIdentifier.get(); }
        const IExpression* GetReturnExpression() const { return returnExpression.get(); }

        const IType* GetArgumentType(int index) const;
        const Identifier* GetArgumentIdentifier(int index) const;
        const VariableDeclaration* GetVariableDeclaration(int index) const;
        const IStatement* GetStatement(int index) const;

        void GetArgumentTypes(std::vector<const IType*>& _argumentTypes) const;
        void GetArgumentIdentifiers(std::vector<const Identifier*>& _argumentIdentifiers) const;
        void GetVariableDeclarations(std::vector<const VariableDeclaration*>& _variableDeclarations) const;
        void GetStatements(std::vector<const IStatement*>& _statements) const;

    private:
        std::unique_ptr<const IType> returnType;
        std::unique_ptr<const Identifier> classIdentifier;
        std::unique_ptr<const IExpression> returnExpression;

        std::unique_ptr<const std::vector<std::unique_ptr<const IType>>> argumentTypes;
        std::unique_ptr<const std::vector<std::unique_ptr<const Identifier>>> argumentIdentifiers;

        std::unique_ptr<const std::vector<std::unique_ptr<const VariableDeclaration>>> variableDeclarations;
        std::unique_ptr<const std::vector<std::unique_ptr<const IStatement>>> statements;
    };

    class ClassDeclaration : public Declaration {
    public:
        ClassDeclaration(std::unique_ptr<const Identifier>&& _classIdentifier,
            std::unique_ptr<const Identifier>&& _baseClassIdentifier,
            std::unique_ptr<std::vector<std::unique_ptr<const VariableDeclaration>>>&& _variableDeclarations,
            std::unique_ptr<std::vector<std::unique_ptr<const MethodDeclaration>>>&& _methodDeclarations);

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        const Identifier* GetClassIdentifier() const { return classIdentifier.get(); }
        const Identifier* GetBaseClassIdentifier() const { return baseClassIdentifier.get(); }

        const VariableDeclaration* GetVariableDeclaration(int index) const;
        const MethodDeclaration* GetMethodDeclaration(int index) const;

        void GetVariableDeclarations(std::vector<const VariableDeclaration*>& _variableDeclarations) const;
        void GetMethodDeclarations(std::vector<const MethodDeclaration*>& _methodDeclarations) const;

    private:
        std::unique_ptr<const Identifier> classIdentifier;
        std::unique_ptr<const Identifier> baseClassIdentifier;

        std::unique_ptr<const std::vector<std::unique_ptr<const VariableDeclaration>>> variableDeclarations;
        std::unique_ptr<const std::vector<std::unique_ptr<const MethodDeclaration>>> methodDeclarations;
    };
}

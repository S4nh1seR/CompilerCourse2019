#pragma once

#include "Statements.h"
#include "Types.h"

#include <Visitor.h>

namespace SyntaxTree {

    class Argument {
    public:
        Argument(std::unique_ptr<const Type>&& _argumentType, std::unique_ptr<const Identifier>&& _argumentIdentifier);

        const Type* GetArgumentType() const { return argumentType.get(); }
        const Identifier* GetArgumentIdentifier() const { return argumentIdentifier.get(); }
    private:
        std::unique_ptr<const Type> argumentType;
        std::unique_ptr<const Identifier> argumentIdentifier;
    };

    class Declaration : public ISyntaxTreeNode {

    };

    class VariableDeclaration : public Declaration {
    public:
        VariableDeclaration(std::unique_ptr<const Type>&& _declarationType, std::unique_ptr<const Identifier>&& _declarationIdentifier,
            int _lineNumber = InvalidLineNumber);

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        const Type* GetDeclarationType() const { return declarationType.get(); }
        const Identifier* GetDeclarationIdentifier() const { return declarationIdentifier.get(); }
    private:
        std::unique_ptr<const Type> declarationType;
        std::unique_ptr<const Identifier> declarationIdentifier;
    };

    class MethodDeclaration : public Declaration {
    public:
        MethodDeclaration(std::unique_ptr<const Type>&& _returnType, std::unique_ptr<const Identifier>&& _methodIdentifier,
            std::unique_ptr<const IExpression>&& _returnExpression, std::vector<std::unique_ptr<const Argument>>&& _arguments,
            std::vector<std::unique_ptr<const VariableDeclaration>>&& _variableDeclarations,
            std::vector<std::unique_ptr<const IStatement>>&& _statements, int _lineNumber = InvalidLineNumber);

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        const Type* GetReturnType() const { return returnType.get(); }
        const Identifier* GetMethodIdentifier() const { return methodIdentifier.get(); }
        const IExpression* GetReturnExpression() const { return returnExpression.get(); }

        const Type* GetArgumentType(int index) const;
        const Identifier* GetArgumentIdentifier(int index) const;
        const VariableDeclaration* GetVariableDeclaration(int index) const;
        const IStatement* GetStatement(int index) const;

        void GetArgumentTypes(std::vector<const Type*>& _argumentTypes) const;
        void GetArgumentIdentifiers(std::vector<const Identifier*>& _argumentIdentifiers) const;
        void GetVariableDeclarations(std::vector<const VariableDeclaration*>& _variableDeclarations) const;
        void GetStatements(std::vector<const IStatement*>& _statements) const;

    private:
        std::unique_ptr<const Type> returnType;
        std::unique_ptr<const Identifier> methodIdentifier;
        std::unique_ptr<const IExpression> returnExpression;

        const std::vector<std::unique_ptr<const Argument>> arguments;
        const std::vector<std::unique_ptr<const VariableDeclaration>> variableDeclarations;
        const std::vector<std::unique_ptr<const IStatement>> statements;
    };

    class ClassDeclaration : public Declaration {
    public:
        ClassDeclaration(std::unique_ptr<const Identifier>&& _classIdentifier,
            std::unique_ptr<const Identifier>&& _baseClassIdentifier,
            std::vector<std::unique_ptr<const VariableDeclaration>>&& _variableDeclarations,
            std::vector<std::unique_ptr<const MethodDeclaration>>&& _methodDeclarations, int _lineNumber = InvalidLineNumber);

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

        const std::vector<std::unique_ptr<const VariableDeclaration>> variableDeclarations;
        const std::vector<std::unique_ptr<const MethodDeclaration>> methodDeclarations;
    };
}

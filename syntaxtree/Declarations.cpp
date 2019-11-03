#include "Declarations.h"

namespace SyntaxTree {

    VariableDeclaration::VariableDeclaration(std::unique_ptr<const IType>&& _declarationType,
        std::unique_ptr<const Identifier>&& _declarationIdentifier)

    :   declarationType(std::move(_declarationType)),
        declarationIdentifier(std::move(_declarationIdentifier))
        {}

    MethodDeclaration::MethodDeclaration(std::unique_ptr<const IType>&& _returnType,
        std::unique_ptr<const Identifier>&& _classIdentifier, std::unique_ptr<const IExpression>&& _returnExpression,
        std::unique_ptr<std::vector<std::unique_ptr<const IType>>>&& _argumentTypes,
        std::unique_ptr<std::vector<std::unique_ptr<const Identifier>>>&& _argumentIdentifiers,
        std::unique_ptr<std::vector<std::unique_ptr<const VariableDeclaration>>>&& _variableDeclarations,
        std::unique_ptr<std::vector<std::unique_ptr<const IStatement>>>&& _statements)

    :   returnType(std::move(_returnType)),
        classIdentifier(std::move(_classIdentifier)),
        returnExpression(std::move(_returnExpression)),
        argumentTypes(std::move(_argumentTypes)),
        argumentIdentifiers(std::move(_argumentIdentifiers)),
        variableDeclarations(std::move(_variableDeclarations)),
        statements(std::move(_statements))
    {
        assert(argumentTypes->size() == argumentIdentifiers->size());
    }

    const IType* MethodDeclaration::GetArgumentType(int index) const {
        assert(index >= 0 && index < argumentTypes->size());
        return (*argumentTypes)[index].get();
    }

    const Identifier* MethodDeclaration::GetArgumentIdentifier(int index) const {
        assert(index >= 0 && index < argumentIdentifiers->size());
        return (*argumentIdentifiers)[index].get();
    }

    const VariableDeclaration* MethodDeclaration::GetVariableDeclaration(int index) const {
        assert(index >= 0 && index < variableDeclarations->size());
        return (*variableDeclarations)[index].get();
    }

    const IStatement* MethodDeclaration::GetStatement(int index) const {
        assert(index >= 0 && index < statements->size());
        return (*statements)[index].get();
    }

    void MethodDeclaration::GetArgumentTypes(std::vector<const IType*>& _argumentTypes) const {
        _argumentTypes.clear();
        for (int i = 0; i < argumentTypes->size(); ++i) {
            _argumentTypes.push_back((*argumentTypes)[i].get());
        }
    }

    void MethodDeclaration::GetArgumentIdentifiers(std::vector<const Identifier*>& _argumentIdentifiers) const {
        _argumentIdentifiers.clear();
        for (int i = 0; i < argumentIdentifiers->size(); ++i) {
            _argumentIdentifiers.push_back((*argumentIdentifiers)[i].get());
        }
    }

    void MethodDeclaration::GetVariableDeclarations(std::vector<const VariableDeclaration*>& _variableDeclarations) const {
        _variableDeclarations.clear();
        for (int i = 0; i < variableDeclarations->size(); ++i) {
            _variableDeclarations.push_back((*variableDeclarations)[i].get());
        }
    }

    void MethodDeclaration::GetStatements(std::vector<const IStatement*>& _statements) const {
        _statements.clear();
        for (int i = 0; i < statements->size(); ++i) {
            _statements.push_back((*statements)[i].get());
        }
    }

    ClassDeclaration::ClassDeclaration(std::unique_ptr<const Identifier>&& _classIdentifier,
        std::unique_ptr<const Identifier>&& _baseClassIdentifier,
        std::unique_ptr<std::vector<std::unique_ptr<const VariableDeclaration>>>&& _variableDeclarations,
        std::unique_ptr<std::vector<std::unique_ptr<const MethodDeclaration>>>&& _methodDeclarations)

    :   classIdentifier(std::move(_classIdentifier)),
        baseClassIdentifier(std::move(_baseClassIdentifier)),
        variableDeclarations(std::move(_variableDeclarations)),
        methodDeclarations(std::move(_methodDeclarations))
        {}

    const VariableDeclaration* ClassDeclaration::GetVariableDeclaration(int index) const {
        assert(index >= 0 && index < variableDeclarations->size());
        return (*variableDeclarations)[index].get();
    }

    const MethodDeclaration* ClassDeclaration::GetMethodDeclaration(int index) const {
        assert(index >= 0 && index < methodDeclarations->size());
        return (*methodDeclarations)[index].get();
    }

    void ClassDeclaration::GetVariableDeclarations(std::vector<const VariableDeclaration*>& _variableDeclarations) const {
        _variableDeclarations.clear();
        for (int i = 0; i < variableDeclarations->size(); ++i) {
            _variableDeclarations.push_back((*variableDeclarations)[i].get());
        }
    }

    void ClassDeclaration::GetMethodDeclarations(std::vector<const MethodDeclaration*>& _methodDeclarations) const {
        _methodDeclarations.clear();
        for (int i = 0; i < methodDeclarations->size(); ++i) {
            _methodDeclarations.push_back((*methodDeclarations)[i].get());
        }
    }

}
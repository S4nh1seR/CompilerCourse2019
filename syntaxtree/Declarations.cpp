#include "Declarations.h"

namespace SyntaxTree {

    Argument::Argument(std::unique_ptr<const Type>&& _argumentType, std::unique_ptr<const Identifier>&& _argumentIdentifier)
    :   argumentType(std::move(_argumentType)),
        argumentIdentifier(std::move(_argumentIdentifier), int _line)
        {line = _line;}

    VariableDeclaration::VariableDeclaration(std::unique_ptr<const Type>&& _declarationType,
        std::unique_ptr<const Identifier>&& _declarationIdentifier, int _line)

    :   declarationType(std::move(_declarationType)),
        declarationIdentifier(std::move(_declarationIdentifier))
        {line = _line;}

    MethodDeclaration::MethodDeclaration(std::unique_ptr<const Type>&& _returnType,
        std::unique_ptr<const Identifier>&& _methodIdentifier, std::unique_ptr<const IExpression>&& _returnExpression,
        std::vector<std::unique_ptr<const Argument>>&& _arguments,
        std::vector<std::unique_ptr<const VariableDeclaration>>&& _variableDeclarations,
        std::vector<std::unique_ptr<const IStatement>>&& _statements, int _line)

    :   returnType(std::move(_returnType)),
        methodIdentifier(std::move(_methodIdentifier)),
        returnExpression(std::move(_returnExpression)),
        arguments(std::move(_arguments)),
        variableDeclarations(std::move(_variableDeclarations)),
        statements(std::move(_statements))
        {line = _line;}


    const Type* MethodDeclaration::GetArgumentType(int index) const {
        assert(index >= 0 && index < arguments.size());
        return arguments[index]->GetArgumentType();
    }

    const Identifier* MethodDeclaration::GetArgumentIdentifier(int index) const {
        assert(index >= 0 && index < arguments.size());
        return arguments[index]->GetArgumentIdentifier();
    }

    const VariableDeclaration* MethodDeclaration::GetVariableDeclaration(int index) const {
        assert(index >= 0 && index < variableDeclarations.size());
        return variableDeclarations[index].get();
    }

    const IStatement* MethodDeclaration::GetStatement(int index) const {
        assert(index >= 0 && index < statements.size());
        return statements[index].get();
    }

    void MethodDeclaration::GetArgumentTypes(std::vector<const Type*>& _argumentTypes) const {
        _argumentTypes.clear();
        for (int i = 0; i < arguments.size(); ++i) {
            _argumentTypes.push_back(arguments[i]->GetArgumentType());
        }
    }

    void MethodDeclaration::GetArgumentIdentifiers(std::vector<const Identifier*>& _argumentIdentifiers) const {
        _argumentIdentifiers.clear();
        for (int i = 0; i < arguments.size(); ++i) {
            _argumentIdentifiers.push_back(arguments[i]->GetArgumentIdentifier());
        }
    }

    void MethodDeclaration::GetVariableDeclarations(std::vector<const VariableDeclaration*>& _variableDeclarations) const {
        _variableDeclarations.clear();
        for (int i = 0; i < variableDeclarations.size(); ++i) {
            _variableDeclarations.push_back(variableDeclarations[i].get());
        }
    }

    void MethodDeclaration::GetStatements(std::vector<const IStatement*>& _statements) const {
        _statements.clear();
        for (int i = 0; i < statements.size(); ++i) {
            _statements.push_back(statements[i].get());
        }
    }

    ClassDeclaration::ClassDeclaration(std::unique_ptr<const Identifier>&& _classIdentifier,
        std::unique_ptr<const Identifier>&& _baseClassIdentifier,
        std::vector<std::unique_ptr<const VariableDeclaration>>&& _variableDeclarations,
        std::vector<std::unique_ptr<const MethodDeclaration>>&& _methodDeclarations, int _line)
    :   classIdentifier(std::move(_classIdentifier)),
        baseClassIdentifier(std::move(_baseClassIdentifier)),
        variableDeclarations(std::move(_variableDeclarations)),
        methodDeclarations(std::move(_methodDeclarations))
        {line = _line;}


    const VariableDeclaration* ClassDeclaration::GetVariableDeclaration(int index) const {
        assert(index >= 0 && index < variableDeclarations.size());
        return variableDeclarations[index].get();
    }

    const MethodDeclaration* ClassDeclaration::GetMethodDeclaration(int index) const {
        assert(index >= 0 && index < methodDeclarations.size());
        return methodDeclarations[index].get();
    }

    void ClassDeclaration::GetVariableDeclarations(std::vector<const VariableDeclaration*>& _variableDeclarations) const {
        _variableDeclarations.clear();
        for (int i = 0; i < variableDeclarations.size(); ++i) {
            _variableDeclarations.push_back(variableDeclarations[i].get());
        }
    }

    void ClassDeclaration::GetMethodDeclarations(std::vector<const MethodDeclaration*>& _methodDeclarations) const {
        _methodDeclarations.clear();
        for (int i = 0; i < methodDeclarations.size(); ++i) {
            _methodDeclarations.push_back(methodDeclarations[i].get());
        }
    }

}

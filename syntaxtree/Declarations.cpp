#include "Declarations.h"

namespace SyntaxTree {

    VariableDeclaration::VariableDeclaration(const IType* _declarationType, const Identifier* _declarationIdentifier)
    :   declarationType(std::make_unique<IType>(_declarationType)),
        declarationIdentifier(std::make_unique<Identifier>(_declarationIdentifier))
        {}

    MethodDeclaration::MethodDeclaration(const IType* _returnType, const Identifier* _classIdentifier,
        const IExpression* _returnExpression, const std::vector<const IType*>& _argumentTypes,
        const std::vector<const Identifier*>& _argumentIdentifiers,
        const std::vector<const VariableDeclaration*>& _variableDeclarations,
        const std::vector<const IStatement*>& _statements)

    :   returnType(std::make_unique<IType>(_returnType)),
        classIdentifier(std::make_unique<Identifier>(_classIdentifier)),
        returnExpression(std::make_unique<IExpression>(_returnExpression))
    {
        assert(_argumentTypes.size() == _argumentIdentifiers.size());
        for (int i = 0; i < _argumentTypes.size(); ++i) {
            argumentTypes.emplace_back(_argumentTypes[i]);
            argumentIdentifiers.emplace_back(_argumentIdentifiers[i]);
        }

        for (auto _variableDeclaration : _variableDeclarations) {
            variableDeclarations.emplace_back(_variableDeclaration);
        }

        for (auto _statement : _statements) {
            statements.emplace_back(_statement);
        }
    }

    const IType* MethodDeclaration::GetArgumentType(int index) const {
        assert(index >= 0 && index < argumentTypes.size());
        return argumentTypes[index].get();
    }

    const Identifier* MethodDeclaration::GetArgumentIdentifier(int index) const {
        assert(index >= 0 && index < argumentIdentifiers.size());
        return argumentIdentifiers[index].get();
    }

    const VariableDeclaration* MethodDeclaration::GetVariableDeclaration(int index) const {
        assert(index >= 0 && index < variableDeclarations.size());
        return variableDeclarations[index].get();
    }

    const IStatement* MethodDeclaration::GetStatement(int index) const {
        assert(index >= 0 && index < statements.size());
        return statements[index].get();
    }

    void MethodDeclaration::GetArgumentTypes(std::vector<const IType*>& _argumentTypes) const {
        _argumentTypes.clear();
        for (int i = 0; i < argumentTypes.size(); ++i) {
            _argumentTypes.push_back(argumentTypes[i].get());
        }
    }

    void MethodDeclaration::GetArgumentIdentifiers(std::vector<const Identifier*>& _argumentIdentifiers) const {
        _argumentIdentifiers.clear();
        for (int i = 0; i < argumentIdentifiers.size(); ++i) {
            _argumentIdentifiers.push_back(argumentIdentifiers[i].get());
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

    ClassDeclaration::ClassDeclaration(const Identifier* _classIdentifier, const Identifier* _baseClassIdentifier,
        const std::vector<const VariableDeclaration*>& _variableDeclarations,
        const std::vector<const MethodDeclaration*>& _methodDeclarations)

    :   classIdentifier(std::make_unique<Identifier>(_classIdentifier)),
        baseClassIdentifier(std::make_unique<Identifier>(_baseClassIdentifier))
    {
        for (auto _variableDeclaration : _variableDeclarations) {
            variableDeclarations.emplace_back(_variableDeclaration);
        }

        for (auto _methodDeclaration : _methodDeclarations) {
            methodDeclarations.emplace_back(_methodDeclaration);
        }
    }


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
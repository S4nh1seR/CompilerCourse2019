#include "BuildSymbolTableVisitor.h"
#include <Types.h>
#include <Statements.h>
#include <Declarations.h>
#include <Expressions.h>
#include <Identifier.h>
#include <MainClass.h>
#include <Goal.h>

namespace SyntaxTree {


    void BuildSymbolTableVisitor::RoundLaunch(std::shared_ptr<SymbolTable>& _symbolTable, const ISyntaxTreeNode* syntaxTreeRoot) {
        symbolTable = _symbolTable;
        syntaxTreeRoot->AcceptVisitor(this);
    }

    void BuildSymbolTableVisitor::VisitNode(const Goal* goal) {
        // В условиях нашей грамматики main класс всегда идет первым, поэтому не может быть переобъявлен
        const MainClass* mainClass = goal->GetMainClass();
        mainClass->AcceptVisitor(this);

        std::vector<const ClassDeclaration*> classDeclarations;
        goal->GetClassDeclarations(classDeclarations);
        for(const ClassDeclaration* classDeclaration : classDeclarations) {
            classDeclaration->AcceptVisitor(this);
        }
    }

    void BuildSymbolTableVisitor::VisitNode(const ClassDeclaration* classDeclaration) {
        const std::wstring& className = classDeclaration->GetClassIdentifier()->GetIdentifier();
        if (!checkClassRedefinition(className)) {
            const std::wstring& baseClassName = classDeclaration->GetBaseClassIdentifier()->GetIdentifier();
            currentClass = std::make_unique<ClassInfo>(className, baseClassName);


            std::vector<const VariableDeclaration*> varDeclarations;
            classDeclaration->GetVariableDeclarations(varDeclarations);
            for (const VariableDeclaration* varDeclaration : varDeclarations) {
                varDeclaration->AcceptVisitor(this);
            }

            std::vector<const MethodDeclaration*> methodDeclarations;
            classDeclaration->GetMethodDeclarations(methodDeclarations);
            for (const MethodDeclaration* methodDeclaration : methodDeclarations) {
                methodDeclaration->AcceptVisitor(this);
            }

            symbolTable->AddClass(className, std::move(currentClass));
        }
    }

    void BuildSymbolTableVisitor::VisitNode(const VariableDeclaration* variableDeclaration) {
        const Type* variableType = variableDeclaration->GetDeclarationType();
        const std::wstring& variableName = variableDeclaration->GetDeclarationIdentifier()->GetIdentifier();
        std::unique_ptr<VariableInfo> variableInfo = std::make_unique<VariableInfo>(variableType, variableName);

        if (currentMethod != nullptr) {
            if (!checkMethodVariableRedefinition(variableName)) {
                currentMethod->AddLocalVariable(variableName, std::move(variableInfo));
            }
        } else {
            if (!checkFieldRedefinition(variableName)) {
                currentClass->AddClassField(variableName, std::move(variableInfo));
            }
        }
    }

    void BuildSymbolTableVisitor::VisitNode(const MethodDeclaration* methodDeclaration) {
        const std::wstring& methodName = methodDeclaration->GetMethodIdentifier()->GetIdentifier();
        if (!checkMethodRedefinition(methodName)) {
            const Type* returnType = methodDeclaration->GetReturnType();
            currentMethod = std::make_unique<MethodInfo>(methodName, returnType);

            std::vector<const VariableDeclaration*> variableDeclarations;
            methodDeclaration->GetVariableDeclarations(variableDeclarations);
            for (const VariableDeclaration* varDeclaration : variableDeclarations) {
                varDeclaration->AcceptVisitor(this);
            }

            std::vector<const Type*> argumentTypes;
            std::vector<const Identifier*> argumentIdentifiers;
            methodDeclaration->GetArgumentTypes(argumentTypes);
            methodDeclaration->GetArgumentIdentifiers(argumentIdentifiers);
            for (int i = 0; i < argumentTypes.size(); ++i) {
                const std::wstring& currArgumentName = argumentIdentifiers[i]->GetIdentifier();
                std::unique_ptr<VariableInfo> currArgumentInfo = std::make_unique<VariableInfo>(argumentTypes[i],
                                                                                                currArgumentName);
                currentMethod->AddArgument(currArgumentName, std::move(currArgumentInfo));
            }

            currentClass->AddClassMethod(methodName, std::move(currentMethod));
        }
    }

    void BuildSymbolTableVisitor::VisitNode(const MainClass* mainClass) {
        const std::wstring& mainClassName = mainClass->GetMainClassIdentifier()->GetIdentifier();
        currentClass = std::make_unique<ClassInfo>(mainClassName, L"");

        const std::wstring& mainFuncName = mainClass->GetMainFuncIdentifier()->GetIdentifier();
        std::unique_ptr<MethodInfo> main = std::make_unique<MethodInfo>(mainFuncName, nullptr); // пока заглушка, потом если надо будет, добавим тип void

        const std::wstring& stringArgName = mainClass->GetStringArgIdentifier()->GetIdentifier();
        std::unique_ptr<VariableInfo> mainArg = std::make_unique<VariableInfo>(nullptr, stringArgName); // то же самое здесь для String
        main->AddArgument(stringArgName, std::move(mainArg));
        currentClass->AddClassMethod(mainFuncName, std::move(main));
        symbolTable->AddClass(mainClassName, std::move(currentClass));
    }

    bool BuildSymbolTableVisitor::checkClassRedefinition(const std::wstring& className) {
        if (symbolTable->GetClassByName(className) != nullptr || (symbolTable->GetMainClass()->GetClassName() == className)) {
            redefinitionErrors.push_back(L"Class redefinition error: " + className);
            return true;
        }
        return false;
    }

    bool BuildSymbolTableVisitor::checkMethodRedefinition(const std::wstring& methodName) {
        if (currentClass->GetMethodByName(methodName) != nullptr) {
            redefinitionErrors.push_back(L"Method redefinition: " + methodName + L" in class " + currentClass->GetClassName());
            return true;
        }
        return false;
    }

    bool BuildSymbolTableVisitor::checkMethodVariableRedefinition(const std::wstring& localVariableName) {
        if (currentMethod->GetArgumentByName(localVariableName) != nullptr) {
            redefinitionErrors.push_back(L"Method local variable redefinition: " + localVariableName + L" in method " +
                                                 currentMethod->GetMethodName() + L" in class " + currentClass->GetClassName());
            return true;
        }
        if (currentMethod->GetLocalVariableByName(localVariableName) != nullptr) {
            redefinitionErrors.push_back(L"Method argument redefinition: " + localVariableName + L" in method " +
                                         currentMethod->GetMethodName() + L" in class " + currentClass->GetClassName());
            return true;
        }
        return false;
    }

    bool BuildSymbolTableVisitor::checkFieldRedefinition(const std::wstring& fieldName) {
        if (currentClass->GetFieldByName(fieldName) != nullptr) {
            redefinitionErrors.push_back(L"Field redefinition: " + fieldName + L" in class " + currentClass->GetClassName());
            return true;
        }
        return false;
    }
}

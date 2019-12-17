#include "BuildSymbolTableVisitor.h"
#include <Types.h>
#include <Statements.h>
#include <Declarations.h>
#include <Expressions.h>
#include <Identifier.h>
#include <MainClass.h>
#include <Goal.h>

#include <algorithm>

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
        if (!checkClassRedefinition(className, classDeclaration->lineNumber)) {
            const ClassInfo* parentInfo = nullptr;
            const Identifier* baseClassIdentifier = classDeclaration->GetBaseClassIdentifier();
            if (baseClassIdentifier != nullptr) {
                const std::wstring& baseClassName = baseClassIdentifier->GetIdentifier();
                parentInfo = symbolTable->GetClassByName(baseClassName);
                if (parentInfo == nullptr) {
                    errors.push_back(L"Base " + baseClassName + L" for class " + className + L" does not exist!" +
                                     L" Line: " + std::to_wstring(classDeclaration->lineNumber) + L".");
                }
            }
            if (parentInfo != nullptr || baseClassIdentifier == nullptr) {
                currentClass = std::make_unique<ClassInfo>(className, parentInfo);

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
    }

    void BuildSymbolTableVisitor::VisitNode(const VariableDeclaration* variableDeclaration) {
        const Type* variableType = variableDeclaration->GetDeclarationType();
        const std::wstring& variableName = variableDeclaration->GetDeclarationIdentifier()->GetIdentifier();
        int& idxCounterRef = currentScope == ST_Class ? currentClass->GetIdxCounterRef() : currentMethod->GetVarsIdxCounterRef();
        std::unique_ptr<VariableInfo> variableInfo = std::make_unique<VariableInfo>(variableType, variableName, idxCounterRef);

        if (currentMethod != nullptr) {
            if (!checkMethodVariableRedefinition(variableName, variableDeclaration->lineNumber)) {
                currentMethod->AddLocalVariable(variableName, std::move(variableInfo));
            }
        } else {
            if (!checkFieldRedefinition(variableName, variableDeclaration->lineNumber)) {
                currentClass->AddClassField(variableName, std::move(variableInfo));
            }
        }
    }

    void BuildSymbolTableVisitor::VisitNode(const MethodDeclaration* methodDeclaration) {
        const std::wstring& methodName = methodDeclaration->GetMethodIdentifier()->GetIdentifier();
        if (!checkMethodRedefinition(methodName, methodDeclaration->lineNumber)) {
            currentScope = ST_Method;
            const Type* returnType = methodDeclaration->GetReturnType();
            currentMethod = std::make_unique<MethodInfo>(methodName, returnType, methodDeclaration->GetAccessModifier());

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
                std::unique_ptr<VariableInfo> currArgumentInfo =
                    std::make_unique<VariableInfo>(argumentTypes[i], currArgumentName, currentMethod->GetArgsIdxCounterRef());
                if (!checkMethodVariableRedefinition(currArgumentName, argumentTypes[i]->lineNumber)) {
                    currentMethod->AddArgument(currArgumentName, std::move(currArgumentInfo));
                }
            }

            currentClass->AddClassMethod(methodName, std::move(currentMethod));
            currentScope = ST_Class;
        }
    }

    void BuildSymbolTableVisitor::VisitNode(const MainClass* mainClass) {
        const std::wstring& mainClassName = mainClass->GetMainClassIdentifier()->GetIdentifier();
        currentClass = std::make_unique<ClassInfo>(mainClassName, nullptr);

        const std::wstring& mainFuncName = mainClass->GetMainFuncIdentifier()->GetIdentifier();
        std::unique_ptr<MethodInfo> main = std::make_unique<MethodInfo>(mainFuncName, nullptr, AM_Public); // пока заглушка, потом если надо будет, добавим тип void

        const std::wstring& stringArgName = mainClass->GetStringArgIdentifier()->GetIdentifier();
        std::unique_ptr<VariableInfo> mainArg = std::make_unique<VariableInfo>(nullptr, stringArgName, main->GetArgsIdxCounterRef()); // то же самое здесь для String
        main->AddArgument(stringArgName, std::move(mainArg));
        currentClass->AddClassMethod(mainFuncName, std::move(main));
        symbolTable->AddMainClass(std::move(currentClass));
    }

    bool BuildSymbolTableVisitor::checkClassRedefinition(const std::wstring& className, int lineNumber) {
        if (symbolTable->GetClassByName(className) != nullptr || (symbolTable->GetMainClass()->GetClassName() == className)) {
            errors.push_back(L"Class redefinition error: " + className + L". Line: " + std::to_wstring(lineNumber) + L".");
            return true;
        }
        return false;
    }

    bool BuildSymbolTableVisitor::checkMethodRedefinition(const std::wstring& methodName, int lineNumber) {
        if (currentClass->GetMethodByName(methodName, false) != nullptr) {
            errors.push_back(L"Method redefinition: " + methodName + L" in class " + currentClass->GetClassName() +
                            L". Line: " + std::to_wstring(lineNumber) + L".");
            return true;
        }
        return false;
    }

    bool BuildSymbolTableVisitor::checkMethodVariableRedefinition(const std::wstring& variableName, int lineNumber) {
        if (currentMethod->GetArgumentByName(variableName) != nullptr) {
            errors.push_back(L"Method argument redefinition: " + variableName + L" in method " +
                             currentMethod->GetMethodName() + L" in class " + currentClass->GetClassName()
                             + L". Line: " + std::to_wstring(lineNumber) + L".");
            return true;
        }
        if (currentMethod->GetLocalVariableByName(variableName) != nullptr) {
            errors.push_back(L"Method local variable redefinition: " + variableName + L" in method " +
                             currentMethod->GetMethodName() + L" in class " + currentClass->GetClassName()
                             + L". Line: " + std::to_wstring(lineNumber) + L".");
            return true;
        }
        return false;
    }

    bool BuildSymbolTableVisitor::checkFieldRedefinition(const std::wstring& fieldName, int lineNumber) {
        if (currentClass->GetFieldByName(fieldName) != nullptr) {
            errors.push_back(L"Field redefinition: " + fieldName + L" in class " + currentClass->GetClassName()
                            + L". Line: " + std::to_wstring(lineNumber) + L".");
            return true;
        }
        return false;
    }

    void BuildSymbolTableVisitor::DumpErrors(std::wostream& os) const {
        for (const std::wstring& currentError : errors) {
            os << currentError << L"\n";
        }
    }

    void BuildSymbolTableVisitor::GetErrors(std::vector<std::wstring>& _errors) const {
        _errors.resize(errors.size());
        std::copy(errors.begin(), errors.end(), _errors.begin());
    }
}

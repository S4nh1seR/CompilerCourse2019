#include "TypeCheckerVisitor.h"
#include <Statements.h>
#include <Declarations.h>
#include <Expressions.h>
#include <Identifier.h>
#include <MainClass.h>
#include <Goal.h>

namespace SyntaxTree {

    void TypeCheckerVisitor::RoundLaunch(std::shared_ptr<SymbolTable>& _symbolTable, const ISyntaxTreeNode* syntaxTreeRoot) {
        symbolTable = _symbolTable;
        syntaxTreeRoot->AcceptVisitor(this);
    }

    void TypeCheckerVisitor::VisitNode(const Type* type) {
        assert( false );
    }

    void TypeCheckerVisitor::VisitNode(const Goal* goal) {
        const MainClass* mainClass = goal->GetMainClass();
        mainClass->AcceptVisitor(this);

        std::vector<const ClassDeclaration*> classDeclarations;
        goal->GetClassDeclarations(classDeclarations);
        for(const ClassDeclaration* classDeclaration : classDeclarations) {
            classDeclaration->AcceptVisitor(this);
        }
    }

    void TypeCheckerVisitor::VisitNode(const MainClass* mainClass) {
        currentClass = symbolTable->GetMainClass();

        const std::wstring& mainFuncName = mainClass->GetMainFuncIdentifier()->GetIdentifier();
        currentMethod = currentClass->GetMethodByName(mainFuncName);

        const IStatement* intStatement = mainClass->GetInternalStatement();
        intStatement->AcceptVisitor(this);
        currentClass = nullptr;
        currentMethod = nullptr;
    }

    bool TypeCheckerVisitor::checkClassExistence(const std::wstring& className, int lineNumber, const std::wstring& errorMessage) {
        if (symbolTable->GetClassByName(className) == nullptr) {
            typeErrors.push_back(errorMessage + L" Line: " + std::to_wstring(lineNumber) + L".");
            return true;
        }
        return false;
    }

    void TypeCheckerVisitor::VisitNode(const ClassDeclaration* classDeclaration) {
        const std::wstring& className = classDeclaration->GetClassIdentifier()->GetIdentifier();
        currentClass = symbolTable->GetClassByName(className);

        // в принципе можно убрать цикл по переменным
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

        currentClass = nullptr;
    }

    void TypeCheckerVisitor::VisitNode(const VariableDeclaration* variableDeclaration) {
        // нечего проверять
    }

    std::wstring TypeCheckerVisitor::GetStandardName(TType type) {
        std::wstring returnTypeName = L"";
        if (type == T_Int) {
            returnTypeName = L"int";
        } else if(type == T_Boolean) {
            returnTypeName = L"boolean";
        } else if(type == T_IntArray) {
            returnTypeName = L"int_array";
        } else {
            assert(false);
        }
        return returnTypeName;
    }

    void TypeCheckerVisitor::checkMethodReturnType(const Type* type) {
        TType returnType = type->GetType();
        std::wstring returnTypeName = (returnType == T_ClassType) ? type->GetIdentifier()->GetIdentifier() : GetStandardName(returnType);
        if(currentType != returnType || currentTypeName != returnTypeName) {
            typeErrors.push_back(L"Incompatible types! Return expression type: " + currentTypeName + L", method return type: " + returnTypeName +
                                 L" . Line: " + std::to_wstring(type->lineNumber) + L".");
        }
    }

    void TypeCheckerVisitor::VisitNode(const MethodDeclaration* methodDeclaration) {
        const std::wstring& methodName = methodDeclaration->GetMethodIdentifier()->GetIdentifier();
        currentMethod = currentClass->GetMethodByName(methodName);

        std::vector<const Type*> argumentTypes;
        std::vector<const Identifier*> argumentIdentifiers;
        methodDeclaration->GetArgumentTypes(argumentTypes);
        methodDeclaration->GetArgumentIdentifiers(argumentIdentifiers);
        for (size_t i = 0; i < argumentTypes.size(); ++i) {
            if (argumentTypes[i]->GetType() == T_ClassType) {
                const std::wstring& argClassName = argumentTypes[i]->GetIdentifier()->GetIdentifier();
                std::wstring wrongArgMessage(L"Custom class type " + argClassName + L" for provided argument does not exist!");
                checkClassExistence(argClassName, argumentTypes[i]->lineNumber, wrongArgMessage);
            }
        }

        std::vector<const IStatement*> statements;
        methodDeclaration->GetStatements(statements);
        for(const IStatement* statement : statements) {
            statement->AcceptVisitor(this);
        }

        const IExpression* returnExpression = methodDeclaration->GetReturnExpression();
        returnExpression->AcceptVisitor(this);

        const Type* returnType = methodDeclaration->GetReturnType();
        if (!returnType->IsSimpleType()) {
            const std::wstring& returnTypeName = returnType->GetIdentifier()->GetIdentifier();
            std::wstring wrongReturnTypeMessage(L"Custom return type class " + returnTypeName + L" does not exist!");
            checkClassExistence(returnTypeName, returnType->lineNumber, wrongReturnTypeMessage);
        }
        checkMethodReturnType(returnType);

        currentMethod = nullptr;
    }

    void TypeCheckerVisitor::VisitNode(const CompoundStatement* compoundStatement) {
        std::vector<const IStatement*> internalStatements;
        compoundStatement->GetAllStatements(internalStatements);
        for(const IStatement* statement : internalStatements) {
            statement->AcceptVisitor(this);
        }
    }

    void TypeCheckerVisitor::checkCurrentType(std::wstring expectedTypeName, int lineNumber, const std::wstring& errorMessageDescription) {
        if (currentTypeName != expectedTypeName) {
            typeErrors.push_back(errorMessageDescription + L" Expected type: " + expectedTypeName + L". Got type: " + currentTypeName
                                 + L". Line: " + std::to_wstring(lineNumber) + L".");
        }
    }

    void TypeCheckerVisitor::VisitNode(const ConditionalStatement* conditionalStatement) {
        const IExpression* condition = conditionalStatement->GetConditionalExpression();
        condition->AcceptVisitor(this);

        std::wstring errorMessageDescription(L"Invalid condition type!");
        checkCurrentType(GetStandardName(T_Boolean), condition->lineNumber, errorMessageDescription);

        const IStatement* positiveStatement = conditionalStatement->GetPositiveStatement();
        positiveStatement->AcceptVisitor(this);
        const IStatement* negativeStatement = conditionalStatement->GetNegativeStatement();
        negativeStatement->AcceptVisitor(this);
    }

    void TypeCheckerVisitor::VisitNode(const LoopStatement* loopStatement) {
        const IExpression* condition = loopStatement->GetConditionalExpression();
        condition->AcceptVisitor(this);

        std::wstring errorMessageDescription(L"Invalid loop condition type!");
        checkCurrentType(GetStandardName(T_Boolean), condition->lineNumber, errorMessageDescription);

        const IStatement* loopBodyStatement = loopStatement->GetInternalStatement();
        loopBodyStatement->AcceptVisitor(this);
    }

    void TypeCheckerVisitor::VisitNode(const PrintStatement* printStatement) {
        const IExpression* printOperand = printStatement->GetPrintOperand();
        printOperand->AcceptVisitor(this);

        std::wstring errorMessageDescription(L"Invalid print operand type!");
        checkCurrentType(GetStandardName(T_Int), printOperand->lineNumber, errorMessageDescription);
    }

    void TypeCheckerVisitor::VisitNode(const AssignmentStatement* assignmentStatement) {
        const Identifier* leftOperand = assignmentStatement->GetLeftOperand();
        leftOperand->AcceptVisitor(this, assignmentStatement->lineNumber);

        if (currentType != T_Invalid) {
            std::wstring leftTypeName = currentTypeName;
            const IExpression* rightOperand = assignmentStatement->GetRightOperand();
            rightOperand->AcceptVisitor(this);

            std::wstring errorMessageDescription(L"Incompatible types in assignment!");
            checkCurrentType(leftTypeName, rightOperand->lineNumber, errorMessageDescription);
        }
    }

    void TypeCheckerVisitor::VisitNode(const IdentifierExpression* identifierExpression) {
        const Identifier* identifier = identifierExpression->GetIdentifier();
        identifier->AcceptVisitor(this, identifierExpression->lineNumber);
    }

    const VariableInfo* TypeCheckerVisitor::getVariableInfo(const std::wstring& variableName) {
        if (currentMethod == nullptr) {
            return currentClass->GetFieldByName(variableName);
        }
        const VariableInfo* methodSearchVariable = currentMethod->GetVariableByName(variableName);

        return (methodSearchVariable == nullptr) ? currentClass->GetFieldByName(variableName) : methodSearchVariable;
    }

    void TypeCheckerVisitor::checkVariableExistence(const std::wstring& variableName, int _lineNumber) {
        const VariableInfo* variableInfo = getVariableInfo(variableName);
        if (variableInfo == nullptr) {
            typeErrors.push_back(L"Variable " + variableName + L" is unavailable! Line: " + std::to_wstring(_lineNumber) + L".");
            currentType = T_Invalid;
            currentTypeName = L"Invalid";
        } else {
            const Type* type = variableInfo->GetVariableType();
            currentType = type->GetType();
            if (type->IsSimpleType()) {
                currentTypeName = GetStandardName(currentType);
            } else {
                currentTypeName = type->GetIdentifier()->GetIdentifier();
            }
        }
    }


    void TypeCheckerVisitor::VisitNode(const Identifier* identifier, int _lineNumber) {
        const std::wstring& variableName = identifier->GetIdentifier();
        checkVariableExistence(variableName, _lineNumber);
    }

    void TypeCheckerVisitor::VisitNode(const ArrayAssignmentStatement* arrayAssignmentStatement) {
        const Identifier* arrayIdentifier = arrayAssignmentStatement->GetArrayIdentifier();
        arrayIdentifier->AcceptVisitor(this, arrayAssignmentStatement->lineNumber);

        if (currentType != T_Invalid) {
            const IExpression* rightOperand = arrayAssignmentStatement->GetRightOperand();

            std::wstring ArrayErrorMessageDescription(L"Not an int array type!");
            checkCurrentType(GetStandardName(T_IntArray), rightOperand->lineNumber, ArrayErrorMessageDescription);

            const IExpression* arrayIndex = arrayAssignmentStatement->GetArrayIndex();
            arrayIndex->AcceptVisitor(this);
            std::wstring IndexErrorMessageDescription(L"Invalid array index type!");
            checkCurrentType(GetStandardName(T_Int), rightOperand->lineNumber, IndexErrorMessageDescription);

            rightOperand->AcceptVisitor(this);
            std::wstring AssignmentErrorMessageDescription(L"Invalid type of assigned value!");
            checkCurrentType(GetStandardName(T_Int), rightOperand->lineNumber, AssignmentErrorMessageDescription);
        }
    }

    void TypeCheckerVisitor::checkBinaryOperationType(const BinaryOperationExpression* binaryOperationExpression, TType operandsType, const std::wstring& operationName) {
        const IExpression* leftOperand = binaryOperationExpression->GetLeftOperand();
        leftOperand->AcceptVisitor(this);
        std::wstring LeftOperandErrorMessage(L"Invalid left operand type for " + operationName + L"operation");
        checkCurrentType(GetStandardName(operandsType), leftOperand->lineNumber, LeftOperandErrorMessage);

        const IExpression* rightOperand = binaryOperationExpression->GetRightOperand();
        rightOperand->AcceptVisitor(this);
        std::wstring RightOperandErrorMessage(L"Invalid right operand type for " + operationName + L"operation");
        checkCurrentType(GetStandardName(operandsType), rightOperand->lineNumber, RightOperandErrorMessage);
    }

    std::wstring GetOperationName(TBinaryOperationType type) {
        switch(type) {
            case BOT_And:
                return L"And";
            case BOT_Or:
                return L"Or";
            case BOT_Less:
                return L"Less";
            case BOT_Add:
                return L"Add";
            case BOT_Sub:
                return L"Sub";
            case BOT_Mul:
                return L"Mul";
            case BOT_Mod:
                return L"Mod";
            default:
                assert(false);
        }
        return L"";
    }

    void TypeCheckerVisitor::VisitNode(const BinaryOperationExpression* binaryOperationExpression) {
        TBinaryOperationType operationType = binaryOperationExpression->GetOperationType();
        std::wstring operationName = GetOperationName(operationType);

        if (operationType == BOT_And || operationType == BOT_Or) {
            checkBinaryOperationType(binaryOperationExpression, T_Boolean, operationName);
            currentType = T_Boolean;
        } else if (operationType == BOT_Less) {
            checkBinaryOperationType(binaryOperationExpression, T_Int, operationName);
            currentType = T_Boolean;
        } else {
            checkBinaryOperationType(binaryOperationExpression, T_Int, operationName);
            currentType = T_Int;
        }
        currentTypeName = GetStandardName(currentType);
    }

    void TypeCheckerVisitor::VisitNode(const SquareBracketExpression* squareBracketExpression) {
        const IExpression* arrayExpression = squareBracketExpression->GetArrayOperand();
        arrayExpression->AcceptVisitor(this);
        std::wstring arrayErrorMessageDescription(L"Trying to index not array type!");
        checkCurrentType(GetStandardName(T_IntArray), arrayExpression->lineNumber, arrayErrorMessageDescription);

        const IExpression* indexExpression = squareBracketExpression->GetIndexOperand();
        indexExpression->AcceptVisitor(this);
        std::wstring indexErrorMessageDescription(L"Invalid array index type!");
        checkCurrentType(GetStandardName(T_Int), indexExpression->lineNumber, indexErrorMessageDescription);

        currentType = T_Int;
        currentTypeName = GetStandardName(T_Int);
    }

    void TypeCheckerVisitor::VisitNode(const LengthExpression* lengthExpression) {
        const IExpression* lengthOperand = lengthExpression->GetLengthOperand();
        lengthOperand->AcceptVisitor(this);
        std::wstring lengthErrorMessageDescription(L"Trying to get length of not array type!");
        checkCurrentType(GetStandardName(T_IntArray), lengthOperand->lineNumber, lengthErrorMessageDescription);

        currentType = T_Int;
        currentTypeName = GetStandardName(T_Int);
    }

    void TypeCheckerVisitor::checkCustomClassArgumentType(const std::wstring& argumentTypeName, int _lineNumber, const std::wstring errorMessage) {
        std::wstring classTypeName = currentTypeName;
        const ClassInfo* argumentClassInfo = symbolTable->GetClassByName(classTypeName);

        while (classTypeName != argumentTypeName) {
            argumentClassInfo = argumentClassInfo->GetParentInfo();
            if (argumentClassInfo == nullptr) {
                typeErrors.push_back(errorMessage + L" Expected type: " + argumentTypeName + L". Got type: " + currentTypeName
                                     + L". Line: " + std::to_wstring(_lineNumber) + L".");
                break;
            }
            classTypeName = argumentClassInfo->GetClassName();
        }
    }

    void TypeCheckerVisitor::VisitNode(const MethodCallExpression* methodCallExpression) {
        const IExpression* objectOperand = methodCallExpression->GetObjectOperand();
        objectOperand->AcceptVisitor(this);
        if (currentType == T_ClassType) {
            std::wstring callerErrorMessage(L"Custom caller class type " + currentTypeName + L" does not exist!");
            if(!checkClassExistence(currentTypeName, objectOperand->lineNumber, callerErrorMessage)) {
                const ClassInfo* callerClass = symbolTable->GetClassByName(currentTypeName);
                const std::wstring& methodName = methodCallExpression->GetMethodIdentifier()->GetIdentifier();
                const MethodInfo* methodInfo = callerClass->GetMethodByName(methodName);
                if (methodInfo != nullptr) {
                    std::vector<const IExpression*> methodArguments;
                    methodCallExpression->GetAllArguments(methodArguments);
                    if (methodInfo->GetArgumentsQuantity() == methodArguments.size()) {

                        for (size_t i = 0; i < methodArguments.size(); ++i) {
                            methodArguments[i]->AcceptVisitor(this);

                            const Type* currArgType = methodInfo->GetArgumentByIndex(i)->GetVariableType();
                            std::wstring argWrongTypeError(L"Wrong type of method argument " + std::to_wstring(i) + L"!");
                            if (currArgType->IsSimpleType()) {
                                std::wstring argTypeName = GetStandardName(currArgType->GetType());
                                checkCurrentType(argTypeName, methodCallExpression->lineNumber, argWrongTypeError);
                            } else {
                                std::wstring argTypeName = currArgType->GetIdentifier()->GetIdentifier();
                                checkCustomClassArgumentType(argTypeName, methodCallExpression->lineNumber, argWrongTypeError);
                            }
                        }

                        const Type* returnType = methodInfo->GetReturnType();
                        currentType = returnType->GetType();
                        if (returnType->IsSimpleType()) {
                            currentTypeName = GetStandardName(currentType);
                        } else {
                            currentTypeName = returnType->GetIdentifier()->GetIdentifier();
                        }
                        return;
                    } else {
                        std::wstring WrongArgNumberMessageError(L"Wrong number of method arguments! Expected: " +
                        std::to_wstring(methodInfo->GetArgumentsQuantity()) + L", Got: " + std::to_wstring(methodArguments.size())
                        + L". Line: " + std::to_wstring(methodCallExpression->lineNumber) + L".");
                        typeErrors.push_back(WrongArgNumberMessageError);
                    }
                } else {
                    std::wstring wrongMethodErrorMessage(L"Unavailable method " + methodName + L" in class " + currentTypeName
                                                         + L". Line: " + std::to_wstring(objectOperand->lineNumber) + L".");
                    typeErrors.push_back(wrongMethodErrorMessage);
                }
            }
        } else {
            std::wstring callerErrorMessage(L"Trying to call method from not class type! Got type: " + currentTypeName
                                            + L". Line: " + std::to_wstring(objectOperand->lineNumber) + L".");
            typeErrors.push_back(callerErrorMessage);
        }
        currentType = T_Invalid;
        currentTypeName = L"Invalid";
    }

    void TypeCheckerVisitor::VisitNode(const BooleanLiteralExpression* booleanLiteralExpression) {
        currentType = T_Boolean;
        currentTypeName = GetStandardName(T_Boolean);
    }

    void TypeCheckerVisitor::VisitNode(const IntegerLiteralExpression* integerLiteralExpression) {
        currentType = T_Int;
        currentTypeName = GetStandardName(T_Int);
    }

    void TypeCheckerVisitor::VisitNode(const ThisExpression* thisExpression) {
        currentType = T_ClassType;
        currentTypeName = currentClass->GetClassName();
    }

    void TypeCheckerVisitor::VisitNode(const NewExpression* newExpression) {
        const std::wstring& className = newExpression->GetIdentifierOperand()->GetIdentifier();
        std::wstring wrongNewTypeMessage(L"Custom class type created by new does not exist!");
        checkClassExistence(className, newExpression->lineNumber, wrongNewTypeMessage);
        currentType = T_ClassType;
        currentTypeName = className;
    }

    void TypeCheckerVisitor::VisitNode(const NewArrayExpression* newArrayExpression) {
        const IExpression* sizeExpression = newArrayExpression->GetSizeOperand();
        sizeExpression->AcceptVisitor(this);
        std::wstring arraySizeErrorMessage(L"Invalid type for array size!");
        checkCurrentType(GetStandardName(T_Int), sizeExpression->lineNumber, arraySizeErrorMessage);

        currentType = T_IntArray;
        currentTypeName = GetStandardName(T_IntArray);
    }

    void TypeCheckerVisitor::VisitNode(const OppositeExpression* oppositeExpression) {
        const IExpression* sourceExpression = oppositeExpression->GetSourceExpression();
        sourceExpression->AcceptVisitor(this);
        std::wstring sourceExpErrorMessage(L"Internal expression should be boolean too!");
        checkCurrentType(GetStandardName(T_Boolean), sourceExpression->lineNumber, sourceExpErrorMessage);
    }

    void TypeCheckerVisitor::VisitNode(const ParenthesesExpression* parenthesesExpression) {
        const IExpression* internalExpression = parenthesesExpression->GetInternalExpression();
        internalExpression->AcceptVisitor(this);
    }

    void TypeCheckerVisitor::DumpErrors(std::wostream& os) const {
        for (const std::wstring& currentError : typeErrors) {
            os << currentError << L"\n";
        }
    }

    void TypeCheckerVisitor::GetErrors(std::vector<std::wstring>& _errors) const {
        _errors.resize(typeErrors.size());
        std::copy(typeErrors.begin(), typeErrors.end(), _errors.begin());
    }
}
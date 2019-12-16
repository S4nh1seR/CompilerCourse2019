#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <unordered_set>

#include "Visitor.h"
#include "SymbolTable.h"
#include "Types.h"

namespace SyntaxTree {

    class TypeCheckerVisitor : public IVisitor, public IIdentifierLogger {
    public:
        ~TypeCheckerVisitor() {}

        void RoundLaunch(std::shared_ptr<SymbolTable>& _symbolTable, const ISyntaxTreeNode* syntaxTreeRoot);

        // Реализация IIdentifierLogger
        void VisitNode(const Identifier* identifier, int _lineNumber) override; // пользуемся этим методом

        // Реализация IVisitor
        void VisitNode(const Identifier* identifier) override { assert(false); }

        void VisitNode(const IdentifierExpression* identifierExpression) override;
        void VisitNode(const BinaryOperationExpression* binaryOperationExpression) override;
        void VisitNode(const SquareBracketExpression* squareBracketExpression) override;
        void VisitNode(const LengthExpression* lengthExpression) override;
        void VisitNode(const MethodCallExpression* methodCallExpression) override;
        void VisitNode(const BooleanLiteralExpression* booleanLiteralExpression) override;
        void VisitNode(const IntegerLiteralExpression* integerLiteralExpression) override;
        void VisitNode(const ThisExpression* thisExpression) override;
        void VisitNode(const NewExpression* newExpression) override;
        void VisitNode(const NewArrayExpression* newArrayExpression) override;
        void VisitNode(const OppositeExpression* oppositeExpression) override;
        void VisitNode(const ParenthesesExpression* parenthesesExpression) override;

        void VisitNode(const CompoundStatement* compoundStatement) override;
        void VisitNode(const ConditionalStatement* conditionalStatement) override;
        void VisitNode(const LoopStatement* loopStatement) override;
        void VisitNode(const PrintStatement* printStatement) override;
        void VisitNode(const AssignmentStatement* assignmentStatement) override;
        void VisitNode(const ArrayAssignmentStatement* arrayAssignmentStatement) override;

        void VisitNode(const Type* type) override;

        void VisitNode(const ClassDeclaration* classDeclaration) override;
        void VisitNode(const VariableDeclaration* variableDeclaration) override;
        void VisitNode(const MethodDeclaration* methodDeclaration) override;

        void VisitNode(const Goal* goal) override;
        void VisitNode(const MainClass* mainClass) override;

        void DumpErrors(std::wostream& os = std::wcerr) const;
        void GetErrors(std::vector<std::wstring>& _errors) const;
        int GetErrorsNumber() const { return typeErrors.size(); }

    private:

        std::shared_ptr<const SymbolTable> symbolTable;

        const ClassInfo* currentClass{nullptr};
        const MethodInfo* currentMethod{nullptr};

        TType currentType;
        std::wstring currentTypeName;

        std::vector<std::wstring> typeErrors;

        bool checkClassExistence(const std::wstring& className, int lineNumber, const std::wstring& errorMessage);
        void checkVariableExistence(const std::wstring& variableName, int _lineNumber);

        const VariableInfo* getVariableInfo(const std::wstring& variableName);
        void checkMethodReturnType(const Type* type);
        std::wstring GetStandardName(TType type);
        void checkCurrentType(std::wstring expectedTypeName, int lineNumber, const std::wstring& errorMessage);
        void checkBinaryOperationType(const BinaryOperationExpression* binaryOperationExpression, TType operandsType, const std::wstring& errorMessage);
        void checkCustomClassArgumentType(const std::wstring& argumentTypeName, int _lineNumber, const std::wstring errorMessage);
    };

}



#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <unordered_set>

#include "Visitor.h"
#include "SymbolTable.h"
#include "Types.h"

namespace SyntaxTree {

    class TypeCheckerVisitor : public IVisitor {
    public:
        ~TypeCheckerVisitor() {}

        void RoundLaunch(std::shared_ptr<SymbolTable>& _symbolTable, const ISyntaxTreeNode* syntaxTreeRoot);

        void VisitNode(const Identifier* identifier) override;

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
        std::unordered_set<std::wstring> undeclaredNames; // чтобы не дублировать имена, для которых уже выдали ошибку

        bool checkClassExistence(const std::wstring& className);
        void checkVariableExistence(const std::wstring& variableName);

        const VariableInfo* getVariableInfo(const std::wstring& variableName);
        void checkMethodReturnType(const Type* type);
        std::wstring GetStandardName(TType type);
        void checkCurrentType(std::wstring expectedTypeName, const std::wstring& errorMessage);
        void checkBinaryOperationType(const BinaryOperationExpression* binaryOperationExpression, TType operandsType, const std::wstring& errorMessage);
    };

}



#include "IrTreeBuilder.h"
#include "Make.h"

#include <Types.h>
#include <Statements.h>
#include <Declarations.h>
#include <Expressions.h>
#include <Identifier.h>
#include <MainClass.h>
#include <Goal.h>

namespace SyntaxTree {
    using namespace IrTree;

    namespace {

        inline std::shared_ptr<const IrtLabelStatement> makeMethodNameStm(const std::wstring& className, const std::wstring& methodName) {
            return make<IrtLabelStatement>(make<IrtLabel>(className + L"::" + methodName));
        }

        const std::wstring kReturnRegister = L"ReturnRegister";
        const std::wstring kThisRegister = L"ThisRegister";

        inline std::shared_ptr<const IrtMemoryExpression> makeMemoryExp(const std::wstring& prefix, const int idx) {
            // Адрес - строка с указанием места хранения (класс, регистр, метод) и индексом, если нужно
            std::wstring address = (prefix == kReturnRegister) || (prefix == kThisRegister) ? prefix : prefix + L"_" + std::to_wstring(idx);
            return make<IrtMemoryExpression>(
                make<IrtTempExpression>(
                    make<IrtTemp>(address)
                )
            );
        }

    }

    void IrTreeBuilder::VisitNode(const Identifier* identifier) {

    }

    void IrTreeBuilder::VisitNode(const IdentifierExpression* identifierExpression) {
    }

    void IrTreeBuilder::VisitNode(const BinaryOperationExpression* binaryOperationExpression) {

    }

    void IrTreeBuilder::VisitNode(const SquareBracketExpression* squareBracketExpression) {

    }

    void IrTreeBuilder::VisitNode(const LengthExpression* lengthExpression) {

    }

    void IrTreeBuilder::VisitNode(const MethodCallExpression* methodCallExpression) {

    }

    void IrTreeBuilder::VisitNode(const BooleanLiteralExpression* booleanLiteralExpression) {

    }

    void IrTreeBuilder::VisitNode(const IntegerLiteralExpression* integerLiteralExpression) {

    }

    void IrTreeBuilder::VisitNode(const ThisExpression* thisExpression) {

    }

    void IrTreeBuilder::VisitNode(const NewExpression* newExpression) {

    }
    void IrTreeBuilder::VisitNode(const NewArrayExpression* newArrayExpression) {

    }

    void IrTreeBuilder::VisitNode(const OppositeExpression* oppositeExpression) {

    }

    void IrTreeBuilder::VisitNode(const ParenthesesExpression* parenthesesExpression) {

    }

    void IrTreeBuilder::VisitNode(const CompoundStatement* compoundStatement) {

    }

    void IrTreeBuilder::VisitNode(const ConditionalStatement* conditionalStatement) {

    }

    void IrTreeBuilder::VisitNode(const LoopStatement* loopStatement) {

    }

    void IrTreeBuilder::VisitNode(const PrintStatement* printStatement) {

    }

    void IrTreeBuilder::VisitNode(const AssignmentStatement* assignmentStatement) {

    }

    void IrTreeBuilder::VisitNode(const ArrayAssignmentStatement* arrayAssignmentStatement) {

    }

    void IrTreeBuilder::VisitNode(const Type* type) {

    }

    void IrTreeBuilder::VisitNode(const ClassDeclaration* classDeclaration) {
        currentClass = symbolTable->GetClassByName(classDeclaration->GetClassIdentifier()->GetIdentifier());
        std::vector<const MethodDeclaration*> methodDeclarations;
        classDeclaration->GetMethodDeclarations(methodDeclarations);
        for (const auto method : methodDeclarations) {
            method->AcceptVisitor(this);
        }
    }

    void IrTreeBuilder::VisitNode(const VariableDeclaration* variableDeclaration) {

    }

    void IrTreeBuilder::VisitNode(const MethodDeclaration* methodDeclaration) {
        currentMethod = currentClass->GetMethodByName(methodDeclaration->GetMethodIdentifier()->GetIdentifier());

        std::vector<const IStatement*> statements;
        methodDeclaration->GetStatements(statements);
        buildCompoundStatement(statements);
        auto statementsWrapper = std::move(currentWrapper);
        methodDeclaration->GetReturnExpression()->AcceptVisitor(this);
        auto returnExpressionWrapper = std::move(currentWrapper);

        std::shared_ptr<const IIrtStatement> body = nullptr;
        if (statementsWrapper) {
            body = make<IrtSeqStatement>(
                statementsWrapper->ToStatement(),
                make<IrtMoveStatement>(
                    makeMemoryExp(kReturnRegister, 0),
                    returnExpressionWrapper->ToExpression()
                )
            );
        } else {
            body = make<IrtMoveStatement>(
                makeMemoryExp(kReturnRegister, 0),
                returnExpressionWrapper->ToExpression()
            );
        }

        currentWrapper = std::make_unique<const StatementWrapper>(
            make<IrtSeqStatement>(
                makeMethodNameStm(currentClass->GetClassName(), currentMethod->GetMethodName()),
                body
            )
        );
    }

    void IrTreeBuilder::VisitNode(const Goal* _goal) {
        _goal->GetMainClass()->AcceptVisitor(this);
        auto mainMethodWrapper = std::move(currentWrapper);

        goal = std::make_shared<const IrTree::IrtGoal>(mainMethodWrapper->ToStatement());

        std::vector<const ClassDeclaration*> classDeclarations;
        _goal->GetClassDeclarations(classDeclarations);
        for (const auto classDeclaration : classDeclarations) {
            classDeclaration->AcceptVisitor(this);
        }
    }

    void IrTreeBuilder::VisitNode(const MainClass* mainClass) {
        currentClass = symbolTable->GetMainClass();
        currentMethod = currentClass->GetFirstMethod();
        mainClass->GetInternalStatement()->AcceptVisitor(this);
        auto internalStatementWrapper = std::move(currentWrapper);

        currentWrapper = std::make_unique<const StatementWrapper>(
            make<IrtSeqStatement>(
                makeMethodNameStm(currentClass->GetClassName(), currentMethod->GetMethodName()),
                internalStatementWrapper->ToStatement()
            )
        );
    }

    void IrTreeBuilder::buildCompoundStatement(const std::vector<const IStatement*>& statements) {
        std::unique_ptr<const ISubtreeWrapper> resultWrapper = nullptr;
        for (const auto statement : statements) {
            statement->AcceptVisitor(this);
            if (resultWrapper) {
                resultWrapper = std::make_unique<StatementWrapper>(
                    make<IrtSeqStatement>(
                        resultWrapper->ToStatement(),
                        currentWrapper->ToStatement()
                    )
                );
            } else {
                resultWrapper = std::move(currentWrapper);
            }
        }
        currentWrapper = std::move(resultWrapper);
    }

}
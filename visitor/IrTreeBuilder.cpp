#include "IrTreeBuilder.h"
#include "Make.h"

#include <Types.h>
#include <Statements.h>
#include <Declarations.h>
#include <Expressions.h>
#include <Identifier.h>
#include <MainClass.h>
#include <Goal.h>

namespace {

    inline std::shared_ptr<const IrTree::IrtLabelStatement> makeMethodNameStm(const std::wstring& className, const std::wstring& methodName) {
        return make<IrTree::IrtLabelStatement>(make<IrTree::IrtLabel>(className + L"::" + methodName));
    }

}

namespace SyntaxTree {
    using namespace IrTree;

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

    }

    void IrTreeBuilder::VisitNode(const VariableDeclaration* variableDeclaration) {

    }

    void IrTreeBuilder::VisitNode(const MethodDeclaration* methodDeclaration) {

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
        mainClass->GetInternalStatement()->AcceptVisitor(this);
        auto internalStatementWrapper = std::move(currentWrapper);

        currentWrapper = std::make_unique<const StatementWrapper>(
            make<IrtSeqStatement>(
                makeMethodNameStm(currentClass->GetClassName(), currentClass->GetFirstMethodName()),
                internalStatementWrapper->ToStatement()
            )
        );
    }

}
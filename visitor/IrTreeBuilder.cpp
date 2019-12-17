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

        const int kSizeOfInt = 4;

        inline std::shared_ptr<const IrtLabel> makeMethodName(const std::wstring& className, const std::wstring& methodName) {
            return makeNode<IrtLabel>(className + L"::" + methodName);
        }

        const std::wstring kReturnRegister = L"ReturnRegister";
        const std::wstring kThisRegister = L"ThisRegister";

        inline std::shared_ptr<const IIrtExpression> makeMemoryUnit(const std::wstring& prefix, const int idx) {
            // Адрес - строка с указанием места хранения (класс, регистр, метод) и индексом, если нужно
            std::wstring address = (prefix == kReturnRegister) || (prefix == kThisRegister) ? prefix : prefix + L"_" + std::to_wstring(idx);
            return makeNode<IrtTempExpression>(
                makeNode<IrtTemp>(address)
            );
        }

    }

    void IrTreeBuilder::VisitNode(const Identifier* identifier) {
        // new Identifier() обрабатывается вместе с NewExpression

        const VariableInfo* variable = nullptr;
        if ((variable = currentMethod->GetArgumentByName(identifier->GetIdentifier()))) {
            currentWrapper = makeWrapper<ExpressionWrapper>(
                makeMemoryUnit(currentMethod->GetMethodName() + L"_Arg", variable->GetIdx())
            );
        } else if ((variable = currentMethod->GetLocalVariableByName(identifier->GetIdentifier()))) {
            currentWrapper = makeWrapper<ExpressionWrapper>(
                makeMemoryUnit(currentMethod->GetMethodName() + L"_Local", variable->GetIdx())
            );
        } else if ((variable = currentClass->GetFieldByName(identifier->GetIdentifier()))) {
            currentWrapper = makeWrapper<ExpressionWrapper>(
                makeMemoryUnit(currentClass->GetClassName() + L"_Field", variable->GetIdx())
            );
        } else {
            assert(false);
        }

        if (!variable->GetVariableType()->IsSimpleType()) {
            currentObjectClass = getClassByType(variable->GetVariableType());
        }
    }

    void IrTreeBuilder::VisitNode(const IdentifierExpression* identifierExpression) {
        identifierExpression->GetIdentifier()->AcceptVisitor(this);
    }

    void IrTreeBuilder::VisitNode(const BinaryOperationExpression* binaryOperationExpression) {
        binaryOperationExpression->GetLeftOperand()->AcceptVisitor(this);
        auto leftExpressionWrapper = std::move(currentWrapper);
        binaryOperationExpression->GetRightOperand()->AcceptVisitor(this);
        auto rightExpressionWrapper = std::move(currentWrapper);

        if (binaryOperationExpression->GetOperationType() == BOT_And) {
            currentWrapper = makeWrapper<AndConditionalWrapper>(
                std::move(leftExpressionWrapper),
                std::move(rightExpressionWrapper)
            );
        } else if (binaryOperationExpression->GetOperationType() == BOT_Or) {
            currentWrapper = makeWrapper<OrConditionalWrapper>(
                std::move(leftExpressionWrapper),
                std::move(rightExpressionWrapper)
            );
        } else if (binaryOperationExpression->GetOperationType() == BOT_Less) {
            currentWrapper = makeWrapper<RelativeConditionalWrapper>(
                leftExpressionWrapper->ToExpression(),
                rightExpressionWrapper->ToExpression()
            );
        } else {
            currentWrapper = makeWrapper<ExpressionWrapper>(
                makeNode<IrtBinaryOperationExpression>(
                    binaryOperationExpression->GetOperationType(),
                    leftExpressionWrapper->ToExpression(),
                    rightExpressionWrapper->ToExpression()
                )
            );
        }
    }

    void IrTreeBuilder::VisitNode(const SquareBracketExpression* squareBracketExpression) {
        squareBracketExpression->GetArrayOperand()->AcceptVisitor(this);
        const auto arrayOperandWrapper = std::move(currentWrapper);
        squareBracketExpression->GetIndexOperand()->AcceptVisitor(this);
        const auto indexOperandWrapper = std::move(currentWrapper);

        currentWrapper = makeWrapper<ExpressionWrapper>(
            makeNode<IrtMemoryExpression>(
                makeNode<IrtBinaryOperationExpression>(
                    BOT_Add,
                    arrayOperandWrapper->ToExpression(),
                    makeNode<IrtBinaryOperationExpression>(
                        BOT_Mul,
                        makeNode<IrtBinaryOperationExpression>(
                            BOT_Add,
                            indexOperandWrapper->ToExpression(),
                            makeNode<IrtConstExpression>(1)
                        ),
                        makeNode<IrtConstExpression>(kSizeOfInt)
                    )
                )
            )
        );
    }

    void IrTreeBuilder::VisitNode(const LengthExpression* lengthExpression) {
        lengthExpression->GetLengthOperand()->AcceptVisitor(this);
        // размер массива находится по адресу массива
        currentWrapper = makeWrapper<ExpressionWrapper>(
            currentWrapper->ToExpression()
        );
    }

    void IrTreeBuilder::VisitNode(const MethodCallExpression* methodCallExpression) {
        methodCallExpression->GetObjectOperand()->AcceptVisitor(this);
        const auto objectOperandWrapper = std::move(currentWrapper);

        const auto objectOperandClass = currentObjectClass;

        const auto methodInfo = objectOperandClass->GetMethodByName(methodCallExpression->GetMethodIdentifier()->GetIdentifier());
        if (!methodInfo->GetReturnType()->IsSimpleType()) {
            currentObjectClass = getClassByType(methodInfo->GetReturnType());
        }

        std::vector<std::shared_ptr<const IIrtExpression>> arguments;
        arguments.push_back(objectOperandWrapper->ToExpression());   // this
        std::vector<const IExpression*> syntaxTreeArgs;
        methodCallExpression->GetAllArguments(syntaxTreeArgs);
        for (const auto arg : syntaxTreeArgs) {
            arg->AcceptVisitor(this);
            arguments.push_back(currentWrapper->ToExpression());
        }

        currentWrapper = makeWrapper<ExpressionWrapper>(
            makeNode<IrtCallExpression>(
                makeNode<IrtNameExpression>(
                    makeMethodName(objectOperandClass->GetClassName(), methodInfo->GetMethodName())
                ),
                makeNode<IrtExpressionList>(std::move(arguments))
            )
        );
    }

    void IrTreeBuilder::VisitNode(const BooleanLiteralExpression* booleanLiteralExpression) {
        currentWrapper = makeWrapper<ExpressionWrapper>(
            makeNode<IrtConstExpression>(booleanLiteralExpression->GetLiteralValue())
        );
    }

    void IrTreeBuilder::VisitNode(const IntegerLiteralExpression* integerLiteralExpression) {
        currentWrapper = makeWrapper<ExpressionWrapper>(
            makeNode<IrtConstExpression>(integerLiteralExpression->GetLiteralValue())
        );
    }

    void IrTreeBuilder::VisitNode(const ThisExpression*) {
        currentWrapper = makeWrapper<ExpressionWrapper>(
            makeMemoryUnit(kThisRegister, 0)
        );
        currentObjectClass = currentClass;
    }

    void IrTreeBuilder::VisitNode(const NewExpression* newExpression) {
        const auto classInfo = symbolTable->GetClassByName(newExpression->GetIdentifierOperand()->GetIdentifier());
        std::vector<std::shared_ptr<const IIrtExpression>> arguments;
        arguments.push_back(
            makeNode<IrtConstExpression>(classInfo->GetFieldsCount())
        );

        currentWrapper = makeWrapper<ExpressionWrapper>(
            makeNode<IrtCallExpression>(
                makeNode<IrtNameExpression>(makeNode<IrtLabel>(L"malloc")),
                makeNode<IrtExpressionList>(std::move(arguments))
            )
        );
        currentObjectClass = classInfo;
    }
    void IrTreeBuilder::VisitNode(const NewArrayExpression* newArrayExpression) {
        newArrayExpression->GetSizeOperand()->AcceptVisitor(this);
        const auto sizeOperandWrapper = std::move(currentWrapper);

        std::vector<std::shared_ptr<const IIrtExpression>> arguments;
        arguments.push_back(
            makeNode<IrtBinaryOperationExpression>(
                BOT_Mul,
                makeNode<IrtBinaryOperationExpression>(
                    BOT_Add,
                    sizeOperandWrapper->ToExpression(),
                    makeNode<IrtConstExpression>(1)
                ),
                makeNode<IrtConstExpression>(kSizeOfInt)
            )
        );

        currentWrapper = makeWrapper<ExpressionWrapper>(
            makeNode<IrtCallExpression>(
                makeNode<IrtNameExpression>(makeNode<IrtLabel>(L"malloc")),
                makeNode<IrtExpressionList>(std::move(arguments))
            )
        );
    }

    void IrTreeBuilder::VisitNode(const OppositeExpression* oppositeExpression) {
        oppositeExpression->GetSourceExpression()->AcceptVisitor(this);
        currentWrapper = makeWrapper<OppositeConditionalWrapper>(
            std::move(currentWrapper)
        );
    }

    void IrTreeBuilder::VisitNode(const ParenthesesExpression* parenthesesExpression) {
        parenthesesExpression->GetInternalExpression()->AcceptVisitor(this);
    }

    void IrTreeBuilder::VisitNode(const CompoundStatement* compoundStatement) {
        std::vector<const IStatement*> statements;
        compoundStatement->GetAllStatements(statements);
        buildCompoundStatement(statements);
    }

    void IrTreeBuilder::VisitNode(const ConditionalStatement* conditionalStatement) {
        conditionalStatement->GetConditionalExpression()->AcceptVisitor(this);
        const auto conditionalExpressionWrapper = std::move(currentWrapper);
        conditionalStatement->GetPositiveStatement()->AcceptVisitor(this);
        const auto positiveStatementWrapper = std::move(currentWrapper);
        conditionalStatement->GetNegativeStatement()->AcceptVisitor(this);
        const auto negativeStatementWrapper = std::move(currentWrapper);

        const auto labelIfTrue = makeNode<IrtLabel>(L"if_true");
        const auto labelIfFalse = makeNode<IrtLabel>(L"if_false");
        const auto labelEndIf = makeNode<IrtLabel>(L"end_if");
        auto positiveLabel = labelEndIf;
        auto negativeLabel = labelEndIf;

        std::shared_ptr<const IIrtStatement> result = makeNode<IrtLabelStatement>(labelEndIf);
        if (negativeStatementWrapper) {
            negativeLabel = labelIfFalse;
            result = makeNode<IrtSeqStatement>(
                makeNode<IrtLabelStatement>(labelIfFalse),
                makeNode<IrtSeqStatement>(
                    negativeStatementWrapper->ToStatement(),
                    result
                )
            );
        }
        if (positiveStatementWrapper) {
            positiveLabel = labelIfTrue;
            if (negativeStatementWrapper) {
                result = makeNode<IrtSeqStatement>(
                    makeNode<IrtJumpStatement>(labelEndIf),
                    result
                );
            }
            result = makeNode<IrtSeqStatement>(
                makeNode<IrtLabelStatement>(labelIfTrue),
                makeNode<IrtSeqStatement>(
                    positiveStatementWrapper->ToStatement(),
                    result
                )
            );
        }

        currentWrapper = makeWrapper<StatementWrapper>(
            makeNode<IrtSeqStatement>(
                conditionalExpressionWrapper->ToConditional(positiveLabel, negativeLabel),
                result
            )
        );
    }

    void IrTreeBuilder::VisitNode(const LoopStatement* loopStatement) {
        loopStatement->GetConditionalExpression()->AcceptVisitor(this);
        const auto conditionalExpressionWrapper = std::move(currentWrapper);
        loopStatement->GetInternalStatement()->AcceptVisitor(this);
        const auto internalStatementWrapper = std::move(currentWrapper);

        const auto labelWhileBody = makeNode<IrtLabel>(L"while_body");
        const auto labelWhileLoop = makeNode<IrtLabel>(L"while_loop");
        const auto labelEndWhile = makeNode<IrtLabel>(L"end_while");

        std::shared_ptr<const IIrtStatement> result = makeNode<IrtSeqStatement>(
            makeNode<IrtJumpStatement>(labelWhileLoop),
            makeNode<IrtLabelStatement>(labelEndWhile)
        );
        if (internalStatementWrapper) {
            result = makeNode<IrtSeqStatement>(
                internalStatementWrapper->ToStatement(),
                result
            );
        }
        currentWrapper = makeWrapper<StatementWrapper>(
            makeNode<IrtSeqStatement>(
                makeNode<IrtLabelStatement>(labelWhileLoop),
                makeNode<IrtSeqStatement>(
                    conditionalExpressionWrapper->ToConditional(labelWhileBody, labelEndWhile),
                    makeNode<IrtSeqStatement>(
                        makeNode<IrtLabelStatement>(labelWhileBody),
                        result
                    )
                )
            )
        );
    }

    void IrTreeBuilder::VisitNode(const PrintStatement* printStatement) {
        printStatement->GetPrintOperand()->AcceptVisitor(this);
        const auto printOperandWrapper = std::move(currentWrapper);
        std::vector<std::shared_ptr<const IIrtExpression>> arguments;
        arguments.push_back(printOperandWrapper->ToExpression());

        currentWrapper = makeWrapper<StatementWrapper>(
            makeNode<IrtExpressionStatement>(
                makeNode<IrtCallExpression>(
                    makeNode<IrtNameExpression>(makeNode<IrtLabel>(L"print")),
                    makeNode<IrtExpressionList>(std::move(arguments))
                )
            )
        );
    }

    void IrTreeBuilder::VisitNode(const AssignmentStatement* assignmentStatement) {
        assignmentStatement->GetLeftOperand()->AcceptVisitor(this);
        const auto leftOperandWrapper = std::move(currentWrapper);
        assignmentStatement->GetRightOperand()->AcceptVisitor(this);
        const auto rightOperandWrapper = std::move(currentWrapper);

        currentWrapper = makeWrapper<StatementWrapper>(
            makeNode<IrtMoveStatement>(
                leftOperandWrapper->ToExpression(),
                rightOperandWrapper->ToExpression()
            )
        );
    }

    void IrTreeBuilder::VisitNode(const ArrayAssignmentStatement* arrayAssignmentStatement) {
        arrayAssignmentStatement->GetArrayIdentifier()->AcceptVisitor(this);
        const auto arrayOperandWrapper = std::move(currentWrapper);
        arrayAssignmentStatement->GetArrayIndex()->AcceptVisitor(this);
        const auto indexOperandWrapper = std::move(currentWrapper);
        arrayAssignmentStatement->GetRightOperand()->AcceptVisitor(this);
        const auto rightOperandWrapper = std::move(currentWrapper);

        currentWrapper = makeWrapper<StatementWrapper>(
            makeNode<IrtMoveStatement>(
                makeNode<IrtMemoryExpression>(
                    makeNode<IrtBinaryOperationExpression>(
                        BOT_Add,
                        arrayOperandWrapper->ToExpression(),
                        makeNode<IrtBinaryOperationExpression>(
                            BOT_Mul,
                            makeNode<IrtBinaryOperationExpression>(
                                BOT_Add,
                                indexOperandWrapper->ToExpression(),
                                makeNode<IrtConstExpression>(1)
                            ),
                            makeNode<IrtConstExpression>(kSizeOfInt)
                        )
                    )
                ),
                rightOperandWrapper->ToExpression()
            )
        );
    }

    void IrTreeBuilder::VisitNode(const Type*) {
        assert(false);
    }

    void IrTreeBuilder::VisitNode(const ClassDeclaration* classDeclaration) {
        currentClass = symbolTable->GetClassByName(classDeclaration->GetClassIdentifier()->GetIdentifier());
        std::vector<const MethodDeclaration*> methodDeclarations;
        classDeclaration->GetMethodDeclarations(methodDeclarations);
        for (const auto method : methodDeclarations) {
            method->AcceptVisitor(this);
            goal->AddMethod(currentWrapper->ToStatement());
        }
    }

    void IrTreeBuilder::VisitNode(const VariableDeclaration*) {
        assert(false);
    }

    void IrTreeBuilder::VisitNode(const MethodDeclaration* methodDeclaration) {
        currentMethod = currentClass->GetMethodByName(methodDeclaration->GetMethodIdentifier()->GetIdentifier());

        std::vector<const IStatement*> statements;
        methodDeclaration->GetStatements(statements);
        buildCompoundStatement(statements);
        const auto statementsWrapper = std::move(currentWrapper);
        methodDeclaration->GetReturnExpression()->AcceptVisitor(this);
        const auto returnExpressionWrapper = std::move(currentWrapper);

        std::shared_ptr<const IIrtStatement> body = nullptr;
        if (statementsWrapper) {
            body = makeNode<IrtSeqStatement>(
                statementsWrapper->ToStatement(),
                makeNode<IrtMoveStatement>(
                    makeMemoryUnit(kReturnRegister, 0),
                    returnExpressionWrapper->ToExpression()
                )
            );
        } else {
            body = makeNode<IrtMoveStatement>(
                makeMemoryUnit(kReturnRegister, 0),
                returnExpressionWrapper->ToExpression()
            );
        }

        currentWrapper = makeWrapper<StatementWrapper>(
            makeNode<IrtSeqStatement>(
                makeNode<IrtLabelStatement>(
                    makeMethodName(currentClass->GetClassName(), currentMethod->GetMethodName() + L"_Body")
                ),
                body
            )
        );
    }

    void IrTreeBuilder::VisitNode(const Goal* _goal) {
        _goal->GetMainClass()->AcceptVisitor(this);
        const auto mainMethodWrapper = std::move(currentWrapper);

        goal = std::make_shared<IrTree::IrtGoal>(mainMethodWrapper->ToStatement());

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
        const auto internalStatementWrapper = std::move(currentWrapper);

        currentWrapper = makeWrapper<StatementWrapper>(
            makeNode<IrtSeqStatement>(
                makeNode<IrtLabelStatement>(
                    makeMethodName(currentClass->GetClassName(), currentMethod->GetMethodName())
                ),
                internalStatementWrapper->ToStatement()
            )
        );
    }

    void IrTreeBuilder::buildCompoundStatement(const std::vector<const IStatement*>& statements) {
        std::unique_ptr<const ISubtreeWrapper> resultWrapper = nullptr;
        for (const auto statement : statements) {
            statement->AcceptVisitor(this);
            if (resultWrapper) {
                resultWrapper = makeWrapper<StatementWrapper>(
                    makeNode<IrtSeqStatement>(
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

    const ClassInfo* IrTreeBuilder::getClassByType(const Type* type)  {
        return symbolTable->GetClassByName(type->GetIdentifier()->GetIdentifier());
    }

    void IrTreeBuilder::RoundLaunch(const Goal* syntaxTreeRoot) {
        syntaxTreeRoot->AcceptVisitor(this);
    }

}
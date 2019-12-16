#include "IrtSerializeVisitor.h"

#include <Label.h>
#include <IrtExpressions.h>
#include <IrtStatements.h>

namespace {
    using IrTree::IIrTreeNode;
    using SyntaxTree::TBinaryOperationType;

    const std::wstring goalNodeName = L"Goal";

    const std::wstring binaryOperationExpressionNodeName = L"BinOpExp";
    const std::wstring constExpressionNodeName = L"ConstExp";
    const std::wstring eseqExpressionNodeName = L"EseqExp";
    const std::wstring memoryExpressionNodeName = L"MemExp";
    const std::wstring expressionListNodeName = L"ExpList";
    const std::wstring callExpressionNodeName = L"CallExp";
    const std::wstring nameExpressionNodeName = L"NameExp";
    const std::wstring tempExpressionNodeName = L"TempExp";

    const std::wstring expressionStatementNodeName = L"ExpStm";
    const std::wstring moveStatementNodeName = L"MoveStm";
    const std::wstring seqStatementNodeName = L"SeqStm";
    const std::wstring jumpStatementNodeName = L"JumpStm";
    const std::wstring cjumpStatementNodeName = L"CJumpStm";
    const std::wstring labelStatementNodeName = L"LabelStm";

    const std::wstring labelNodeName = L"Label";
    const std::wstring tempNodeName = L"Temp";

    struct ParentSwitcher {
        const IIrTreeNode*& currParent;
        const IIrTreeNode* prevParent{nullptr};

        ParentSwitcher(const IIrTreeNode*& parent, const IIrTreeNode* newParent): currParent(parent) {
            prevParent = currParent;
            currParent = newParent;
        }

        ~ParentSwitcher() {
            currParent = prevParent;
        }

    };

    std::wstring GetOperationName(TBinaryOperationType type) {
        switch(type) {
            case TBinaryOperationType::BOT_And:
                return L"And";
            case TBinaryOperationType::BOT_Or:
                return L"Or";
            case TBinaryOperationType::BOT_Less:
                return L"Less";
            case TBinaryOperationType::BOT_Add:
                return L"Add";
            case TBinaryOperationType::BOT_Sub:
                return L"Sub";
            case TBinaryOperationType::BOT_Mul:
                return L"Mul";
            case TBinaryOperationType::BOT_Mod:
                return L"Mod";
            default:
                assert(false);
        }
        return L"";
    }
}

namespace IrTree {
    using namespace SyntaxTree;

    void IrtSerializeVisitor::RoundLaunch(std::shared_ptr<DirectedGraph>& _irtGraph, const std::shared_ptr<const IrtGoal>& _root) {
        irtGraph = _irtGraph;
        nameMapping.clear();

        _root->AcceptVisitor(this);
    }

    void IrtSerializeVisitor::processSpecialNameCases(const IIrTreeNode* node, std::wstring& nodeName, const std::wstring& nodeType) {
        if (nodeType == binaryOperationExpressionNodeName) {
            nodeName += (L": " + GetOperationName(dynamic_cast<const IrtBinaryOperationExpression*>(node)->GetOperationType()));
        } else if (nodeType == constExpressionNodeName) {
            nodeName += (L": " + std::to_wstring(dynamic_cast<const IrtConstExpression*>(node)->GetConstValue()));
        } else if (nodeType == labelNodeName) {
            nodeName += (L": " + dynamic_cast<const IrtLabel*>(node)->GetLabel());
        } else if (nodeType == tempNodeName) {
            nodeName += (L": " + dynamic_cast<const IrtTemp*>(node)->GetLabel());
        }
    }

    void IrtSerializeVisitor::makeUniqueName(const IIrTreeNode* node, const std::wstring& nodeType, std::wstring& nodeName) {
        if (nameCounters.find(nodeType) == nameCounters.end()) {
            nameCounters[nodeType] = 0;
        }
        nodeName = nodeType + L"_" + std::to_wstring(nameCounters[nodeType]++);

        processSpecialNameCases(node, nodeName, nodeType);
    }


    void IrtSerializeVisitor::makeGraphEdge(const IIrTreeNode* node, const std::wstring& nodeType) {
        std::wstring nodeName;
        if (nameMapping.find(node) == nameMapping.end()) {
            makeUniqueName(node, nodeType, nodeName);
            nameMapping.insert(std::make_pair(node, nodeName));
            irtGraph->AddVertex(nodeName);
        } else {
            nodeName = nameMapping[node];
        }

        assert(nameMapping.find(currentParent) != nameMapping.end());
        std::wstring parentNodeName = nameMapping[currentParent];

        irtGraph->AddEdge(parentNodeName, nodeName);
    }

    void IrtSerializeVisitor::VisitNode(const IrtGoal* goal) {
        std::wstring goalName;
        makeUniqueName(goal, goalNodeName, goalName);
        irtGraph->AddVertex(goalName);
        nameMapping.insert(std::make_pair(goal, goalName));

        currentParent = goal;
        std::shared_ptr<const IIrtStatement> mainMethod = goal->GetMainMethod();
        mainMethod->AcceptVisitor(this);

        const std::vector<std::shared_ptr<const IIrtStatement>>& methods = goal->GetMethods();
        for (const std::shared_ptr<const IIrtStatement>& method : methods) {
            method->AcceptVisitor(this);
        }
        currentParent = nullptr;
    }

    void IrtSerializeVisitor::VisitNode(const IrtBinaryOperationExpression* binaryOperationExpression) {
        makeGraphEdge(binaryOperationExpression, binaryOperationExpressionNodeName);

        ParentSwitcher switcher(currentParent, binaryOperationExpression);

        std::shared_ptr<const IIrtExpression> left = binaryOperationExpression->GetLeftOperand();
        left->AcceptVisitor(this);
        std::shared_ptr<const IIrtExpression> right = binaryOperationExpression->GetRightOperand();
        right->AcceptVisitor(this);
    }

    void IrtSerializeVisitor::VisitNode(const IrtConstExpression* constExpression) {
        makeGraphEdge(constExpression, constExpressionNodeName);
    }

    void IrtSerializeVisitor::VisitNode(const IrtESeqExpression* eseqExpression) {
        makeGraphEdge(eseqExpression, eseqExpressionNodeName);

        ParentSwitcher switcher(currentParent, eseqExpression);

        std::shared_ptr<const IIrtStatement> statement = eseqExpression->GetStatement();
        statement->AcceptVisitor(this);
        std::shared_ptr<const IIrtExpression> expression = eseqExpression->GetExpression();
        expression->AcceptVisitor(this);
    }

    void IrtSerializeVisitor::VisitNode(const IrtMemoryExpression* memoryExpression) {
        makeGraphEdge(memoryExpression, memoryExpressionNodeName);

        ParentSwitcher switcher(currentParent, memoryExpression);

        std::shared_ptr<const IIrtExpression> expression = memoryExpression->GetMemoryExpression();
        expression->AcceptVisitor(this);
    }

    void IrtSerializeVisitor::VisitNode(const IrtExpressionList* expressionList) {
        makeGraphEdge(expressionList, expressionListNodeName);

        ParentSwitcher switcher(currentParent, expressionList);

        std::vector<std::shared_ptr<const IIrtExpression>> expressions;
        expressionList->GetExpressions(expressions);
        for (const std::shared_ptr<const IIrtExpression>& expression : expressions) {
            expression->AcceptVisitor(this);
        }
    }

    void IrtSerializeVisitor::VisitNode(const IrtCallExpression* callExpression) {
        makeGraphEdge(callExpression, callExpressionNodeName);

        ParentSwitcher switcher(currentParent, callExpression);

        std::shared_ptr<const IIrtExpression> methodExpression = callExpression->GetMethodExpression();
        methodExpression->AcceptVisitor(this);
        std::shared_ptr<const IrtExpressionList> argExpressionList = callExpression->GetArgumentExpressionList();
        argExpressionList->AcceptVisitor(this);
    }

    void IrtSerializeVisitor::VisitNode(const IrtNameExpression* nameExpression) {
        makeGraphEdge(nameExpression, nameExpressionNodeName);

        ParentSwitcher switcher(currentParent, nameExpression);

        std::shared_ptr<const IrtLabel> label = nameExpression->GetLabel();
        label->AcceptVisitor(this);
    }

    void IrtSerializeVisitor::VisitNode(const IrtTempExpression* tempExpression) {
        makeGraphEdge(tempExpression, tempExpressionNodeName);

        ParentSwitcher switcher(currentParent, tempExpression);

        std::shared_ptr<const IrtTemp> temp = tempExpression->GetTempValue();
        temp->AcceptVisitor(this);
    }

    void IrtSerializeVisitor::VisitNode(const IrtExpressionStatement* expressionStatement) {
        makeGraphEdge(expressionStatement, expressionStatementNodeName);

        ParentSwitcher switcher(currentParent, expressionStatement);

        std::shared_ptr<const IIrtExpression> expression = expressionStatement->GetExpression();
        expression->AcceptVisitor(this);
    }

    void IrtSerializeVisitor::VisitNode(const IrtMoveStatement* moveStatement) {
        makeGraphEdge(moveStatement, moveStatementNodeName);

        ParentSwitcher switcher(currentParent, moveStatement);

        std::shared_ptr<const IIrtExpression> destination = moveStatement->GetDestinationExpression();
        destination->AcceptVisitor(this);
        std::shared_ptr<const IIrtExpression> source = moveStatement->GetSourceExpression();
        source->AcceptVisitor(this);
    }

    void IrtSerializeVisitor::VisitNode(const IrtSeqStatement* seqStatement) {
        makeGraphEdge(seqStatement, seqStatementNodeName);

        ParentSwitcher switcher(currentParent, seqStatement);

        std::shared_ptr<const IIrtStatement> leftStatement = seqStatement->GetLeftStatement();
        leftStatement->AcceptVisitor(this);
        std::shared_ptr<const IIrtStatement> rightStatement = seqStatement->GetRightStatement();
        rightStatement->AcceptVisitor(this);
    }

    void IrtSerializeVisitor::VisitNode(const IrtJumpStatement* jumpStatement) {
        makeGraphEdge(jumpStatement, jumpStatementNodeName);

        ParentSwitcher switcher(currentParent, jumpStatement);

        std::shared_ptr<const IrtLabel> target = jumpStatement->GetTargetLabel();
        target->AcceptVisitor(this);
    }

    void IrtSerializeVisitor::VisitNode(const IrtCJumpStatement* cjumpStatement) {
        makeGraphEdge(cjumpStatement, cjumpStatementNodeName);

        ParentSwitcher switcher(currentParent, cjumpStatement);

        std::shared_ptr<const IIrtExpression> leftExpression = cjumpStatement->GetLeftExpression();
        leftExpression->AcceptVisitor(this);
        std::shared_ptr<const IIrtExpression> rightExpression = cjumpStatement->GetRightExpression();
        rightExpression->AcceptVisitor(this);
        std::shared_ptr<const IrtLabel> positiveLabel = cjumpStatement->GetPositiveLabel();
        positiveLabel->AcceptVisitor(this);
        std::shared_ptr<const IrtLabel> negativeLabel = cjumpStatement->GetnegativeLabel();
        negativeLabel->AcceptVisitor(this);
    }

    void IrtSerializeVisitor::VisitNode(const IrtLabelStatement* labelStatement) {
        makeGraphEdge(labelStatement, labelStatementNodeName);

        ParentSwitcher switcher(currentParent, labelStatement);

        std::shared_ptr<const IrtLabel> label = labelStatement->GetLabel();
        label->AcceptVisitor(this);
    }

    void IrtSerializeVisitor::VisitNode(const IrtLabel* label) {
        makeGraphEdge(label, labelNodeName);
    }

    void IrtSerializeVisitor::VisitNode(const IrtTemp* temp) {
        makeGraphEdge(temp, tempNodeName);
    }
}
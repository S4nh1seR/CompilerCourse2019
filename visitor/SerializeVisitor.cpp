#include "SerializeVisitor.h"
#include <Types.h>
#include <Statements.h>
#include <assert.h>
#include <exception>

namespace SyntaxTree {

    std::wstring SerializeVisitor::makeUniqueNameAndUpdate(
            SyntaxTree::SerializeVisitor::CNodePrefixNumber &nodePrefixNumber)
    {
        std::wstring toReturn = nodePrefixNumber.prefix + L"_replica" + std::to_wstring(nodePrefixNumber.number);
        ++nodePrefixNumber.number;
        return toReturn;
    }

    void SerializeVisitor::RoundLaunch(
            std::shared_ptr<SyntaxTree::DirectedGraph> &_graph_ptr,
            const SyntaxTree::ISyntaxTreeNode *_root_syntax_tree_ptr)
    {
        graph_ptr = _graph_ptr;
        ptrs_queue.clear();
        name_mapping.clear();
        parent_mapping.clear();

        ptrs_queue.push_back(_root_syntax_tree_ptr);
        while(!ptrs_queue.empty()) {
            std::vector<const ISyntaxTreeNode*> current_ptrs_queue;
            current_ptrs_queue.swap(ptrs_queue);

            for(auto syntaxTreeNode : current_ptrs_queue) {
                syntaxTreeNode->AcceptVisitor(this);
            }
        }
    }

    void SerializeVisitor::addNoRootNodeToGraph(
            const SyntaxTree::ISyntaxTreeNode *node,
            const std::wstring &nodeGraphName)
    {
        // extract the parent of the node
        auto parentItem = parent_mapping.find(node);
        assert(parentItem != parent_mapping.end());
        auto parent = parentItem->second;

        // extract the parent name
        auto parentNameItem = name_mapping.find(parent);
        assert(parentNameItem != name_mapping.end());
        std::wstring parentName = parentNameItem->second;

        // add the node to the hashtable
        name_mapping.insert(std::make_pair(node, nodeGraphName));

        // make iT vertex and edge connecting iT and it's parent
        graph_ptr->AddVertex(nodeGraphName);
        graph_ptr->AddEdge(parentName, nodeGraphName);
    }

    void SerializeVisitor::bindChildrenNode(
            const SyntaxTree::ISyntaxTreeNode *childrenNode,
            const SyntaxTree::ISyntaxTreeNode *node,
            bool addToQueue)
    {
        assert(parent_mapping.find(childrenNode) == parent_mapping.end());
        parent_mapping.insert(std::make_pair(childrenNode, node));
        if(addToQueue) {
            ptrs_queue.push_back(childrenNode);
        }
    }

    void SerializeVisitor::VisitNode(const IdentifierType* identifierType)
    {
        // make identifierType name and add it to the graph with this name
        std::wstring iT_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.identifierTypeNode);
        addNoRootNodeToGraph(identifierType, iT_Name);

        // bind identifierType children to it's parent and add them to in-process queue
        bindChildrenNode(identifierType->GetIdentifier(), identifierType, true);
    }

    void SerializeVisitor::VisitNode(const IntArrayType* intArrayType)
    {
        // make intArrayType name and add it to the graph with this name
        std::wstring iAT_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.intArrayTypeNode);
        addNoRootNodeToGraph(intArrayType, iAT_Name);
    }

    void SerializeVisitor::VisitNode(const BooleanType* booleanType)
    {
        // make booleanType name and add it to the graph with this name
        std::wstring bT_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.booleanTypeNode);
        addNoRootNodeToGraph(booleanType, bT_Name);
    }

    void SerializeVisitor::VisitNode(const IntType* intType)
    {
        // make intType name and add it to the graph with this name
        std::wstring iT_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.intTypeNode);
        addNoRootNodeToGraph(intType, iT_Name);
    }

    void SerializeVisitor::VisitNode(const ArrayAssignmentStatement* arrayAssignmentStatement)
    {
        // make arrayAssignmentStatement name and add it to the graph with this name
        std::wstring aAS_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.arrayAssignmentStatementNode);
        addNoRootNodeToGraph(arrayAssignmentStatement, aAS_Name);

        // bind aAS children to aAS and add them to in-process queue
        bindChildrenNode(arrayAssignmentStatement->GetArrayIdentifier(), arrayAssignmentStatement, true);
        bindChildrenNode(arrayAssignmentStatement->GetArrayIndex(), arrayAssignmentStatement, true);
        bindChildrenNode(arrayAssignmentStatement->GetRightOperand(), arrayAssignmentStatement, true);
    }

    void SerializeVisitor::VisitNode(const AssignmentStatement* assignmentStatement)
    {
        std::wstring aS_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.assignmentStatementNode);
        addNoRootNodeToGraph(assignmentStatement, aS_Name);
        bindChildrenNode(assignmentStatement->GetLeftOperand(), assignmentStatement, true);
        bindChildrenNode(assignmentStatement->GetRightOperand(), assignmentStatement, true);
    }

    void SerializeVisitor::VisitNode(const CompoundStatement* compoundStatement)
    {
        std::wstring cmpS_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.compoundStatementNode);
        addNoRootNodeToGraph(compoundStatement, cmpS_Name);
        throw NotImplementedException();
    }
    void SerializeVisitor::VisitNode(const ConditionalStatement* conditionalStatement)
    {
        std::wstring cdS_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.conditionalStatementNode);
        addNoRootNodeToGraph(conditionalStatement, cdS_Name);
    }
    void SerializeVisitor::VisitNode(const LoopStatement* loopStatement)
    {
        std::wstring lS_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.loopStatementNode);
        addNoRootNodeToGraph(loopStatement, lS_Name);
    }
    void SerializeVisitor::VisitNode(const PrintStatement* printStatement)
    {
        std::wstring pS_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.printStatementNode);
        addNoRootNodeToGraph(printStatement, pS_Name);
    }
}

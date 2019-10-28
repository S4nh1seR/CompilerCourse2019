#include "SerializeVisitor.h"
#include <Types.h>
#include <Statements.h>
#include <Declarations.h>
#include <Expressions.h>
#include <Identifier.h>
#include <MainClass.h>
#include <Goal.h>
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

        // make node vertex and edge connecting node and it's parent
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
        std::vector<const IStatement*> children_statements;
        compoundStatement->GetAllStatements(children_statements);
        for(auto child_statement : children_statements) {
            bindChildrenNode(child_statement, compoundStatement, true);
        }
    }
    void SerializeVisitor::VisitNode(const ConditionalStatement* conditionalStatement)
    {
        std::wstring cdS_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.conditionalStatementNode);
        addNoRootNodeToGraph(conditionalStatement, cdS_Name);
        bindChildrenNode(conditionalStatement->GetConditionalExpression(), conditionalStatement, true);
        bindChildrenNode(conditionalStatement->GetPositiveStatement(), conditionalStatement, true);
        bindChildrenNode(conditionalStatement->GetNegativeStatement(), conditionalStatement, true);
    }
    void SerializeVisitor::VisitNode(const LoopStatement* loopStatement)
    {
        std::wstring lS_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.loopStatementNode);
        addNoRootNodeToGraph(loopStatement, lS_Name);
        bindChildrenNode(loopStatement->GetConditionalExpression(), loopStatement, true);
        bindChildrenNode(loopStatement->GetInternalStatement(), loopStatement, true);
    }
    void SerializeVisitor::VisitNode(const PrintStatement* printStatement)
    {
        std::wstring pS_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.printStatementNode);
        addNoRootNodeToGraph(printStatement, pS_Name);
        bindChildrenNode(printStatement->GetPrintOperand(), printStatement, true);
    }

    void SerializeVisitor::VisitNode(const IdentifierExpression* identifierExpression)
    {
        std::wstring iE_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.identifierExpressionNode);
        addNoRootNodeToGraph(identifierExpression, iE_Name);
        bindChildrenNode(identifierExpression->GetIdentifier(), identifierExpression, true);
    }

    void SerializeVisitor::VisitNode(const SquareBracketExpression* squareBracketExpression)
    {
        std::wstring sBE_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.squareBracketExpressionNode);
        addNoRootNodeToGraph(squareBracketExpression, sBE_Name);
        bindChildrenNode(squareBracketExpression->GetArrayOperand(), squareBracketExpression, true);
        bindChildrenNode(squareBracketExpression->GetIndexOperand(), squareBracketExpression, true);
    }

    void SerializeVisitor::VisitNode(const LengthExpression* lengthExpression)
    {
        std::wstring lE_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.lengthExpressionNode);
        addNoRootNodeToGraph(lengthExpression, lE_Name);
        bindChildrenNode(lengthExpression->GetLengthOperand(), lengthExpression, true);
    }

    void SerializeVisitor::VisitNode(const MethodCallExpression* methodCallExpression)
    {
        std::wstring mCE_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.methodCallExpressionNode);
        addNoRootNodeToGraph(methodCallExpression, mCE_Name);
        bindChildrenNode(methodCallExpression->GetObjectOperand(), methodCallExpression, true);
        bindChildrenNode(methodCallExpression->GetMethodIdentifier(), methodCallExpression, true);
        std::vector<const IExpression*> children_arg_expressions;
        methodCallExpression->GetAllArguments(children_arg_expressions);
        for(auto child_arg_expr : children_arg_expressions) {
            bindChildrenNode(child_arg_expr, methodCallExpression, true);
        }
    }

    void SerializeVisitor::VisitNode(const BooleanLiteralExpression* booleanLiteralExpression)
    {
        std::wstring bLE_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.booleanLiteralExpressionNode);
        bool boolValue = booleanLiteralExpression->GetLiteralValue();
        if(boolValue) {
            bLE_Name += L"_true";
            addNoRootNodeToGraph(booleanLiteralExpression, bLE_Name);
        }
        else {
            bLE_Name += L"_false";
            addNoRootNodeToGraph(booleanLiteralExpression, bLE_Name);
        }
    }

    void SerializeVisitor::VisitNode(const IntegerLiteralExpression* integerLiteralExpression)
    {
        std::wstring iLE_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.integerLiteralExpressionNode);
        int integerValue = integerLiteralExpression->GetLiteralValue();
        iLE_Name += L"_" + std::to_wstring(integerValue);
        addNoRootNodeToGraph(integerLiteralExpression, iLE_Name);
    }

    void SerializeVisitor::VisitNode(const ThisExpression* thisExpression)
    {
        std::wstring tE_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.thisExpressionNode);
        addNoRootNodeToGraph(thisExpression, tE_Name);
    }

    void SerializeVisitor::VisitNode(const NewExpression* newExpression)
    {
        std::wstring nE_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.newExpressionNode);
        addNoRootNodeToGraph(newExpression, nE_Name);
        bindChildrenNode(newExpression->GetIdentifierOperand(), newExpression, true);
    }

    void SerializeVisitor::VisitNode(const NewArrayExpression* newArrayExpression)
    {
        std::wstring nAE_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.newArrayExpressionNode);
        addNoRootNodeToGraph(newArrayExpression, nAE_Name);
        bindChildrenNode(newArrayExpression->GetSizeOperand() ,newArrayExpression, true);
    }

    void SerializeVisitor::VisitNode(const OppositeExpression* oppositeExpression)
    {
        std::wstring oE_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.oppositeExpressionNode);
        addNoRootNodeToGraph(oppositeExpression, oE_Name);
        bindChildrenNode(oppositeExpression->GetSourceExpression(), oppositeExpression, true);
    }
    void SerializeVisitor::VisitNode(const ParenthesesExpression* parenthesesExpression)
    {
        std::wstring pE_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.parenthesesExpressionNode);
        addNoRootNodeToGraph(parenthesesExpression, pE_Name);
        bindChildrenNode(parenthesesExpression->GetInternalExpression(), parenthesesExpression, true);
    }

    void SerializeVisitor::VisitNode(const Identifier* identifier)
    {
        std::wstring i_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.identifierNode);
        std::wstring identifierValue = identifier->GetIdentifier();
        i_Name += L"_" + identifierValue;
        addNoRootNodeToGraph(identifier, i_Name);
    }

    void SerializeVisitor::VisitNode(const ClassDeclaration* classDeclaration)
    {
        std::wstring cD_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.classDeclarationNode);
        addNoRootNodeToGraph(classDeclaration, cD_Name);
        bindChildrenNode(classDeclaration->GetClassIdentifier(), classDeclaration, true);
        auto baseIdentifier = classDeclaration->GetBaseClassIdentifier();
        if(baseIdentifier) {
            bindChildrenNode(baseIdentifier, classDeclaration, true);
        }
        std::vector<const VariableDeclaration*> var_declarations;
        classDeclaration->GetVariableDeclarations(var_declarations);
        std::vector<const MethodDeclaration*> method_declarations;
        classDeclaration->GetMethodDeclarations(method_declarations);
        for(auto var_decl : var_declarations) {
            bindChildrenNode(var_decl, classDeclaration, true);
        }
        for(auto method_decl : method_declarations) {
            bindChildrenNode(method_decl, classDeclaration, true);
        }
    }

    void SerializeVisitor::VisitNode(const VariableDeclaration* variableDeclaration)
    {
        std::wstring vD_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.variableDeclarationNode);
        addNoRootNodeToGraph(variableDeclaration, vD_Name);
        bindChildrenNode(variableDeclaration->GetDeclarationType(), variableDeclaration, true);
        bindChildrenNode(variableDeclaration->GetDeclarationIdentifier(), variableDeclaration, true);
    }

    void SerializeVisitor::VisitNode(const MethodDeclaration* methodDeclaration)
    {
        std::wstring mD_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.methodDeclarationNode);
        addNoRootNodeToGraph(methodDeclaration, mD_Name);
        bindChildrenNode(methodDeclaration->GetReturnType(), methodDeclaration, true);
        bindChildrenNode(methodDeclaration->GetClassIdentifier(), methodDeclaration, true);
        std::vector<const IType*> argument_types;
        std::vector<const Identifier*> argument_identifiers;
        methodDeclaration->GetArgumentTypes(argument_types);
        methodDeclaration->GetArgumentIdentifiers(argument_identifiers);
        assert(argument_identifiers.size() == argument_types.size());
        int arguments_count = argument_identifiers.size();
        for(int i = 0 ; i < arguments_count; ++i) {
            auto argument_type = argument_types[i];
            auto argument_identifier = argument_identifiers[i];
            bindChildrenNode(argument_type, methodDeclaration, true);
            bindChildrenNode(argument_identifier, methodDeclaration, true);
        }
        std::vector<const VariableDeclaration*> variables_declarations;
        methodDeclaration->GetVariableDeclarations(variables_declarations);
        for(auto var_decl : variables_declarations) {
            bindChildrenNode(var_decl, methodDeclaration, true);
        }
        std::vector<const IStatement*> statements;
        methodDeclaration->GetStatements(statements);
        for(auto statement : statements) {
            bindChildrenNode(statement, methodDeclaration, true);
        }
        bindChildrenNode(methodDeclaration->GetReturnExpression(), methodDeclaration, true);
    }

    void SerializeVisitor::VisitNode(const Goal* goal)
    {
        // create goal name and add goal to the hashtable
        std::wstring g_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.goalNode);
        name_mapping.insert(std::make_pair(goal, g_Name));

        // make goal vertex in the graph
        graph_ptr->AddVertex(g_Name);

        assert(parent_mapping.find(goal) == parent_mapping.end());

        bindChildrenNode(goal->GetMainClass(), goal, true);
        std::vector<const ClassDeclaration *> class_declarations;
        goal->GetClassDeclarations(class_declarations);
        for(auto class_decl : class_declarations) {
            bindChildrenNode(class_decl, goal, true);
        }
    }
    void SerializeVisitor::VisitNode(const MainClass* mainClass)
    {
        std::wstring mC_Name = makeUniqueNameAndUpdate(nodesNameUniqueMaker.mainClassNode);
        addNoRootNodeToGraph(mainClass, mC_Name);
        bindChildrenNode(mainClass->GetMainClassIdentifier(), mainClass, true);
        bindChildrenNode(mainClass->GetStringArgIdentifier(), mainClass, true);
        bindChildrenNode(mainClass->GetInternalStatement(), mainClass, true);
    }
}

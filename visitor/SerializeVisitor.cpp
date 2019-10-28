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

    void SerializeVisitor::VisitNode(const IdentifierType* identifierType)
    {
        // extract the identifierType Node name
        auto noConstIdentifierType = const_cast<IdentifierType*>(identifierType);
        auto identifierTypeMapItem = ptrs_mapping.find(static_cast<ISyntaxTreeNode*>(noConstIdentifierType));
        assert(identifierTypeMapItem != ptrs_mapping.end());
        std::wstring identifierTypeName = identifierTypeMapItem->second;

        // get identifier sub Node and associate it with an IdentifierName
        std::wstring identifierName = makeUniqueNameAndUpdate(nodesNameUniqueMaker.identifierNode);
        auto identifier = const_cast<Identifier*>(identifierType->GetIdentifier());

        // insert the IdentifierName into the hash table
        auto resultInsert = ptrs_mapping.insert(std::make_pair(identifier, identifierName));
        assert(resultInsert.second);

        // make new vertex and new edge in the graph
        graph_ptr->AddVertex(identifierName);
        graph_ptr->AddEdge(identifierTypeName, identifierName);

        // recursion descent to the identifier
        identifier->AcceptVisitor(this);
    }

    void SerializeVisitor::VisitNode(const IntArrayType* intArrayType)
    {
        // just check that the intArrayType is presented in the hash table
        auto noConstIntArrayType = const_cast<IntArrayType*>(intArrayType);
        auto intArrayTypeMapItem = ptrs_mapping.find(static_cast<ISyntaxTreeNode*>(noConstIntArrayType));
        assert(intArrayTypeMapItem != ptrs_mapping.end());
    }

    void SerializeVisitor::VisitNode(const BooleanType* booleanType)
    {
        // just check that the booleanType is presented in the hash table
        auto noConstBooleanType = const_cast<BooleanType*>( booleanType);
        auto booleanTypeMapItem = ptrs_mapping.find(static_cast<ISyntaxTreeNode*>(noConstBooleanType));
        assert(booleanTypeMapItem != ptrs_mapping.end());
    }

    void SerializeVisitor::VisitNode(const IntType* intType)
    {
        // just check that the intType is presented in the hash table
        auto noConstIntType = const_cast<IntType*>( intType);
        auto intTypeMapItem = ptrs_mapping.find(static_cast<ISyntaxTreeNode*>(noConstIntType));
        assert(intTypeMapItem != ptrs_mapping.end());
    }

    void SerializeVisitor::VisitNode(const ArrayAssignmentStatement* arrayAssignmentStatement)
    {
        // extract the identifierType Node name
        auto noConstArrayAssignmentType = const_cast<ArrayAssignmentStatement*>(arrayAssignmentStatement);
        auto arrayAssignmentTypeMapItem = ptrs_mapping.find(static_cast<ISyntaxTreeNode*>(noConstArrayAssignmentType));
        assert(arrayAssignmentTypeMapItem != ptrs_mapping.end());
        std::wstring arrayAssignmentTypeName = arrayAssignmentTypeMapItem->second;

        throw NotImplementedException();
    }
}

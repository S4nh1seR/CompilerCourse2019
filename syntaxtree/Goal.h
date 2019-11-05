#pragma once

#include "Declarations.h"
#include "MainClass.h"

#include <Visitor.h>

namespace SyntaxTree {

    class Goal : public ISyntaxTreeNode {
    public:
        Goal(std::unique_ptr<MainClass const>&& _mainClass,
            std::unique_ptr<std::vector<std::unique_ptr<ClassDeclaration const>>>&& _classDeclarations);

        virtual void AcceptVisitor(IVisitor* visitor) const override { visitor->VisitNode(this); }

        const MainClass* GetMainClass() const { return mainClass.get(); }
        const ClassDeclaration* GetClassDeclaration(int index) const;
        void GetClassDeclarations(std::vector<const ClassDeclaration*>& _classDeclarations) const;
    private:
        std::unique_ptr<const MainClass> mainClass;
        std::unique_ptr<const std::vector<std::unique_ptr<const ClassDeclaration>>> classDeclarations;
    };
}
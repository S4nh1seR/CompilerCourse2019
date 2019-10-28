#include "Declarations.h"
#include "MainClass.h"

namespace SyntaxTree {

    class Goal : public ISyntaxTreeNode {
    public:
        Goal(const MainClass* _mainClass, const std::vector<const ClassDeclaration*>& _classDeclarations);

        virtual void AcceptVisitor(const IVisitor* visitor) const override { visitor->VisitNode(this); }

        const MainClass* GetMainClass() const { return mainClass.get(); }
        const ClassDeclaration* GetClassDeclaration(int index) const;
        void GetClassDeclarations(std::vector<const ClassDeclaration*>& _classDeclarations) const;
    private:
        std::unique_ptr<const MainClass> mainClass;
        std::vector<std::unique_ptr<const ClassDeclaration>> classDeclarations;
    };
}
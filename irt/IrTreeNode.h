#pragma once

#include <IrtVisitor.h>

#include <memory>
#include <vector>

namespace IrTree {

    class IIrTreeNode {
    public:
        virtual ~IIrTreeNode() = default;
        virtual void AcceptVisitor(IIrtVisitor* visitor) const = 0;
    };

    class IIrtExpression : public IIrTreeNode {
    };

    class IIrtStatement : public IIrTreeNode {
    };

    class IrtGoal : public IIrtStatement {
    public:
        IrtGoal(const std::shared_ptr<const IIrtStatement>& _mainMethod) : mainMethod(_mainMethod) {}

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }

        void AddMethod(const std::shared_ptr<const IIrtStatement>& method) { methods.push_back(method); }
        std::shared_ptr<const IIrtStatement> GetMainMethod() const { return mainMethod; }
        const std::vector<std::shared_ptr<const IIrtStatement>>& GetMethods() const { return methods; }

    private:
        std::shared_ptr<const IIrtStatement> mainMethod;
        std::vector<std::shared_ptr<const IIrtStatement>> methods;
    };
}

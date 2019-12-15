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
        IrtGoal(const std::shared_ptr<IIrtStatement>& _mainClass, std::vector<std::shared_ptr<IIrtStatement>>&& _classes)
            : mainClass(_mainClass), classes(std::move(_classes))
        {
        }

        std::shared_ptr<IIrtStatement> GetMainClass() const { return mainClass; }
        const std::vector<std::shared_ptr<IIrtStatement>>& GetClasses() const { return classes; }

    private:
        std::shared_ptr<IIrtStatement> mainClass;
        std::vector<std::shared_ptr<IIrtStatement>> classes;
    };
}

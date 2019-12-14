#pragma once

#include "IrTreeNode.h"

#include <IrtVisitor.h>

#include <string>

namespace IrTree {

    class IrtLabel : public IIrTreeNode {
    public:
        IrtLabel(const std::wstring& _label): label(_label) {}

        const std::wstring& GetLabel() const { return label; }

        virtual void AcceptVisitor(IIrtVisitor* visitor) { visitor->VisitNode(this); }

    private:
        std::wstring label;
    };

    class IrtTemp : public IIrTreeNode {
    public:
        IrtTemp(const std::wstring& _label): label(_label) {}

        const std::wstring& GetLabel() const { return label; }

        virtual void AcceptVisitor(IIrtVisitor* visitor) { visitor->VisitNode(this); }

    private:
        std::wstring label;
    };
}
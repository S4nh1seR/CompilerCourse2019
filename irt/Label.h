#pragma once

#include "IrTreeNode.h"

#include <IrtVisitor.h>

#include <string>
#include <unordered_map>

namespace IrTree {

    class IrtLabel : public IIrTreeNode {
    public:
        IrtLabel(const std::wstring& _label = L"");

        const std::wstring& GetLabel() const { return label; }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }
    private:
        std::wstring label;
        static std::unordered_map<std::wstring, int> labelCounters;
    };

    class IrtTemp : public IIrTreeNode {
    public:
        IrtTemp(const std::wstring& _label = L"");

        const std::wstring& GetLabel() const { return label; }

        void AcceptVisitor(IIrtVisitor* visitor) const override { visitor->VisitNode(this); }

    private:
        std::wstring label;
        static std::unordered_map<std::wstring, int> tempCounters;
    };
}
#pragma once

#include "ClassInfo.h"

namespace SyntaxTree {

    class SymbolTable {
    public:
        void AddClass(const std::wstring& _className, std::unique_ptr<const ClassInfo>&& _classInfo);
        void AddMainClass(std::unique_ptr<const ClassInfo>&& _mainClassInfo) { mainClass = std::move(_mainClassInfo); }
        const ClassInfo* GetClassByName(const std::wstring& _className) const;
        const ClassInfo* GetMainClass() const { return mainClass.get(); }

    private:
        std::unique_ptr<const ClassInfo> mainClass;
        std::unordered_map<std::wstring, std::unique_ptr<const ClassInfo>> classes;
    };
}
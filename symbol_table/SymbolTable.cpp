#include "SymbolTable.h"

namespace SyntaxTree {

    void SymbolTable::AddClass(const std::wstring& _className, std::unique_ptr<ClassInfo>&& _classInfo) {
        assert(classes.find(_className) == classes.end());
        classes.emplace(_className, std::move(_classInfo));
    }

    const ClassInfo* SymbolTable::GetClassByName(const std::wstring& _className) const {
        return (classes.find(_className) != classes.end()) ? classes.at(_className).get() : nullptr;
    }

}
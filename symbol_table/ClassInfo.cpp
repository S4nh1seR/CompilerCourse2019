#include "ClassInfo.h"

#include <cassert>

namespace SyntaxTree {

    void ClassInfo::AddClassMethod(const std::wstring& _methodName, std::unique_ptr<const MethodInfo>&& _methodInfo) {
        classMethods.emplace(_methodName, std::move(_methodInfo));
    }

    void ClassInfo::AddClassField(const std::wstring& _fieldName, std::unique_ptr<const VariableInfo>&& _fieldInfo) {
        classFields.emplace(_fieldName, std::move(_fieldInfo));
    }

    const VariableInfo* ClassInfo::GetFieldByName(const std::wstring& _fieldName) const {
        if (classFields.find(_fieldName) != classFields.end()) {
            return classFields.at(_fieldName).get();
        }
        if (parentInfo != nullptr) {
            return parentInfo->GetFieldByName(_fieldName);
        }
        return nullptr;
    }

    const MethodInfo* ClassInfo::GetMethodByName(const std::wstring& _methodName, bool searchParent) const {
        if (classMethods.find(_methodName) != classMethods.end()) {
            return classMethods.at(_methodName).get();
        }
        if (searchParent && parentInfo != nullptr) {
            return parentInfo->GetMethodByName(_methodName);
        }
        return nullptr;
    }

    const MethodInfo* ClassInfo::GetFirstMethod() const {
        if (!classMethods.empty()) {
            classMethods.cbegin()->second.get();
        }
        return nullptr;
    }
}
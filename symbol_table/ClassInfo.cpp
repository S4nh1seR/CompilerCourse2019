#include "ClassInfo.h"

#include <cassert>

namespace SyntaxTree {

    void ClassInfo::AddClassMethod(const std::wstring& _methodName, std::unique_ptr<const MethodInfo>&& _methodInfo) {
        assert(classMethods.find(_methodName) == classMethods.end());
        classMethods.emplace(_methodName, std::move(_methodInfo));
    }

    void ClassInfo::AddClassField(const std::wstring& _fieldName, std::unique_ptr<const VariableInfo>&& _fieldInfo) {
        assert(classFields.find(_fieldName) == classFields.end());
        classFields.emplace(_fieldName, std::move(_fieldInfo));
    }

    const VariableInfo* ClassInfo::GetFieldByName(const std::wstring& _fieldName) const {
        assert(classFields.find(_fieldName) != classFields.end());
        return classFields.at(_fieldName).get();
    }

    const MethodInfo* ClassInfo::GetMethodByName(const std::wstring& _methodName) const {
        assert(classMethods.find(_methodName) != classMethods.end());
        return classMethods.at(_methodName).get();
    }
}
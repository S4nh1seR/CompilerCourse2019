#pragma once

#include "MethodInfo.h"

#include <unordered_map>
#include <memory>

namespace SyntaxTree {

    class ClassInfo {
    public:

        ClassInfo(const std::wstring& _className, const std::wstring& _parentName):
            className(_className), parentName(_parentName) {}

        void AddClassField(const std::wstring& _fieldName, std::unique_ptr<const VariableInfo>&& _fieldInfo);
        void AddClassMethod(const std::wstring& _methodName, std::unique_ptr<const MethodInfo>&& _methodInfo);

        const std::wstring& GetClassName() const { return className; }
        const std::wstring& GetParentInfo() const { return parentName; }

        const VariableInfo* GetFieldByName(const std::wstring& _fieldName) const;
        const MethodInfo* GetMethodByName(const std::wstring& _methodName) const;
    private:
        const std::wstring& className;
        const std::wstring& parentName;

        std::unordered_map<std::wstring, std::unique_ptr<const VariableInfo>> classFields;
        std::unordered_map<std::wstring, std::unique_ptr<const MethodInfo>> classMethods;
    };

}
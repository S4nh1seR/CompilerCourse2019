#pragma once

#include "MethodInfo.h"

#include <unordered_map>
#include <memory>

namespace SyntaxTree {

    class ClassInfo {
    public:

        ClassInfo(const std::wstring& _className, const ClassInfo* _parentInfo):
            className(_className), parentInfo(_parentInfo), idxCounter(0) {}

        const ClassInfo* GetParentInfo() const { return parentInfo; }

        void AddClassField(const std::wstring& _fieldName, std::unique_ptr<const VariableInfo>&& _fieldInfo);
        void AddClassMethod(const std::wstring& _methodName, std::unique_ptr<const MethodInfo>&& _methodInfo);

        const std::wstring& GetClassName() const { return className; }
        const std::wstring& GetParentName() const { return parentInfo->GetClassName(); }

        const VariableInfo* GetFieldByName(const std::wstring& _fieldName) const;
        const MethodInfo* GetMethodByName(const std::wstring& _methodName) const;

        int& GetIdxCounterRef() { return idxCounter; }

    private:
        const std::wstring& className;
        const ClassInfo* parentInfo;

        std::unordered_map<std::wstring, std::unique_ptr<const VariableInfo>> classFields;
        std::unordered_map<std::wstring, std::unique_ptr<const MethodInfo>> classMethods;

        int idxCounter;
    };

}
#include "MethodInfo.h"

#include <cassert>
#include <memory>

namespace SyntaxTree {

    const VariableInfo* MethodInfo::GetArgumentByName(const std::wstring& _argumentName) const {
        return (arguments.find(_argumentName) != arguments.end()) ? arguments.at(_argumentName).get() : nullptr;
    }

    const VariableInfo* MethodInfo::GetArgumentByIndex(int index) const {
        assert(index >= 0 && index < arguments.size());
        const std::wstring& argumentName = sortedArgumentNames[index];
        return GetArgumentByName(argumentName);
    }

    const VariableInfo* const MethodInfo::GetLocalVariableByName(const std::wstring& _localVariableName) const {
        return (localVariables.find(_localVariableName) != localVariables.end()) ? localVariables.at(_localVariableName).get() : nullptr;
    }

    const VariableInfo* MethodInfo::GetVariableByName(const std::wstring& variableName) const {
        const VariableInfo* result = GetArgumentByName(variableName);
        return (result != nullptr) ? result : GetLocalVariableByName(variableName);
    }

    void MethodInfo::AddArgument(const std::wstring& _argumentName, std::unique_ptr<const VariableInfo>&& _argumentInfo) {
        arguments.emplace(_argumentName, std::move(_argumentInfo));
        sortedArgumentNames.push_back(_argumentName);
    }

    void MethodInfo::AddLocalVariable(const std::wstring& _localVariableName, std::unique_ptr<const VariableInfo>&& _localVariableInfo) {
        localVariables.emplace(_localVariableName, std::move(_localVariableInfo));
    }

}
#pragma once

#include "VariableInfo.h"
#include <unordered_map>
#include <vector>

namespace SyntaxTree {

    class MethodInfo {
    public:
        MethodInfo(const std::wstring& _methodName, const Type* _returnType)
            : methodName(_methodName), returnType(_returnType), argsIdxCounter(0), varsIdxCounter(0) {}

        void AddArgument(const std::wstring& _argumentName, std::unique_ptr<const VariableInfo>&& _argumentInfo);
        void AddLocalVariable(const std::wstring& _localVariableName, std::unique_ptr<const VariableInfo>&& _localVariableInfo);

        const std::wstring& GetMethodName() const { return methodName; }
        const Type* GetReturnType() const { return returnType; }

        const VariableInfo* GetArgumentByName(const std::wstring& _argumentName) const;
        const VariableInfo* GetArgumentByIndex(int index) const;

        int GetArgumentsQuantity() const { return arguments.size(); }
        const VariableInfo* const GetLocalVariableByName(const std::wstring& _localVariableName) const;
        const VariableInfo* GetVariableByName(const std::wstring& _variableName) const;

        int& GetArgsIdxCounterRef() { return argsIdxCounter; }
        int& GetVarsIdxCounterRef() { return varsIdxCounter; }

    private:
        const std::wstring& methodName;
        const Type* returnType;

        std::unordered_map<std::wstring, std::unique_ptr<const VariableInfo>> arguments;
        std::unordered_map<std::wstring, std::unique_ptr<const VariableInfo>> localVariables;

        std::vector<std::wstring> sortedArgumentNames;

        int argsIdxCounter;
        int varsIdxCounter;
    };


}
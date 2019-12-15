#pragma once

#include "Types.h"

#include <string>

namespace SyntaxTree {

    class VariableInfo {
    public:
        VariableInfo(const Type* _variableType, const std::wstring& _variableName, int& idxCounter)
        :   variableType(_variableType), variableName(_variableName), idx(idxCounter++) {}

        const Type* GetVariableType() const { return variableType; }
        const std::wstring& GetVariableName() const { return variableName; }
        const int GetIdx() const { return idx; }

    private:
        const Type* variableType;
        const std::wstring& variableName;
        const int idx;
    };
}

#pragma once

#include "Types.h"

#include <string>

namespace SyntaxTree {

    class VariableInfo {
    public:
        explicit VariableInfo(const Type* _variableType, const std::wstring& _variableName)
        :   variableType(_variableType), variableName(_variableName) {}

        const Type* GetVariableType() const { return variableType; }
        const std::wstring& GetVariableName() const { return variableName; }
    private:
        const Type* variableType;
        const std::wstring& variableName;
    };
}

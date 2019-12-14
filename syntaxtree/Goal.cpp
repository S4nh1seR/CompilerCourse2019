#include "Goal.h"

namespace SyntaxTree {

    Goal::Goal(std::unique_ptr<MainClass const>&& _mainClass,
        std::vector<std::unique_ptr<ClassDeclaration const>>&& _classDeclarations, int _line)

    :   mainClass(std::move(_mainClass)),
        classDeclarations(std::move(_classDeclarations))
        {line = _line;}

    const ClassDeclaration* Goal::GetClassDeclaration(int index) const {
        assert(index >= 0 && index < classDeclarations.size());
        return classDeclarations[index].get();
    }

    void Goal::GetClassDeclarations(std::vector<const ClassDeclaration*>& _classDeclarations) const {
        _classDeclarations.clear();
        for (int i = 0; i < classDeclarations.size(); ++i) {
            _classDeclarations.push_back(classDeclarations[i].get());
        }
    }
}

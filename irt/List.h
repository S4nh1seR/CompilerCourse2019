#pragma once

#include <vector>
#include <memory>
#include "IExp.h"
#include "IStm.h"

namespace IrtTree {

class ExpList
{
 public:
    ExpList() = default;

    explicit ExpList(const IExp* expression)
    {
        Add( expression );
    }

    void Add(const IExp* expression)
    {
        expressions.emplace_back(expression);
    }

    const std::vector<std::unique_ptr<const IExp>>& GetExpressions() const
    {
        return expressions;
    }

 private:
    std::vector<std::unique_ptr<const IExp>> expressions;
};

};

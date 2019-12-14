#pragma once

#include <memory>
#include <map>

#include "IExp.h"
#include "List.h"

class CallExp : public IExp
{

 public:

    CallExp(std::unique_ptr<IExp>& funcExp, std::unique_ptr<ExpList>& exp args ) : funcExp(funcExp), args(args)
    {
    }

    void AcceptVisitor(IVisitor* visitor) const override;
    const IExp* GetFuncExp() const;
    const ExpList* GetArgs() const;

 private:
    std::unique_ptr<const IExp> funcExp;
    std::unique_ptr<const ExpList> args;
};
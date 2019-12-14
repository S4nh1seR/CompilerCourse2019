#pragma once

#include "IStm.h"
#include "IExp.h"

class ExpStm : public IStm
{
 public:
    explicit ExpStm(std::unique_ptr<IExp>& exp) : exp(exp)
    {}
    void AcceptVisitor(IVisitor* visitor) const override;
    const IExp* GetExp() const;

 private:
    std::unique_ptr<const IExp> exp;
};


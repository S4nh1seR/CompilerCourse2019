#pragma once


#include "IExp.h"
#include "IStm.h"

class ESeqExp : public IExp
{

 public:

    CESeqExp(std::unique_ptr<IStm>& stm, std::unique_ptr<IExp>& exp) : stm(stm), exp(exp)
    {
    }

    void AcceptVisitor(IVisitor* visitor) const override;
    const IStm* GetStm() const;
    const IExp* GetExp() const;

 private:
    std::unique_ptr<const IStm> stm;
    std::unique_ptr<const IExp> exp;
};

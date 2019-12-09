#pragma once

#include <memory>
#include "IExp.h"


class MemoryExp : public IExp
{

 public:

    explicit CMemoryExp(std::unique_ptr<IExp>& exp);

    void AcceptVisitor(IVisitor* visitor) const override;
    const IExp* GetMem() const;

 private:
    std::unique_ptr<const IExp> exp;
};






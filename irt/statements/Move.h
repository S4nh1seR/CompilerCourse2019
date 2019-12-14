#pragma once

#include "IStm.h"
#include "IExp.h"
#include "Label.h"

class MoveStm : public IStm
{
 public:
    CMoveStm(std::unique_ptr<const IExp>&  dst, std::unique_ptr<const IExp>&  src) 
	: dst(dst), src(src)
    {}
    void AcceptVisitor(IVisitor* visitor) const override;
    const IExp* GetDst() const;
    const IExp* GetSrc() const;

 private:
    std::unique_ptr<const IExp> dst;
    std::unique_ptr<const IExp> src;
};



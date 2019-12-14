#pragma once

#include "IStm.h"

class Seq : public IStm {
public:
    Seq(std::unique_ptr<const IStm>& left, const std::unique_ptr<const IStm>& right)
        : right(right), left(left)
        {}
	virtual void AcceptVisitor(IVisitor* visitor);
    const IStm* GetLeft() const;
    const IStm* GetRight() const;

private:
    std::unique_ptr<IStm> left;
    std::unique_ptr<IStm> right;
};

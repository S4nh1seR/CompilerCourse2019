#pragma once

#include "IExp.h"

class ConstExp : public IExp
{

 public:

    explicit CConstExp(int value) : value(value)
    {
    }

    void AcceptVisitor(IVisitor* visitor) const override;
    int GetValue() const;

 private:
    const int value;
};



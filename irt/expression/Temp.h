#pragma once

#include "IExp.h"

class TempExp : public IExp
{

 public:
    explicit CTempExp(std::unique_ptr<const IExp>& value_) : value(value_)
    {
    }

    void AcceptVisitor(IVisitor* visitor) const override;
    const std::string GetValueLabel() const;

 private:
    Temp value;
};



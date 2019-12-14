#pragma once

#include "IStm.h"
#include "Label.h"

class JumpStm : public IStm
{

 public:

    explicit JumpStm(std::unique_ptr<Label>& target) : target(target)
    {}
    void AcceptVisitor(IVisitor* visitor) const override;
    const Label* GetLabel() const;

 private:
    td::unique_ptr<const Label> target;
};


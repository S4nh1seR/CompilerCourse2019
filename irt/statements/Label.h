#pragma once

#include "IStm.h"
#include "Label.h"

class LabelStm : public IStm
{
	public:
		explicit LabelStm(std::unique_ptr<Label>& label) : label(label)
	    {}
	    void AcceptVisitor(IVisitor* visitor) const override;
	    const Label* GetLabel() const;
	    
	private:
	    std::unique_ptr<Label> label;
};


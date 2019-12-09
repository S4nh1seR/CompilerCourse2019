#include "IStm.h"
#include "IVisitorIRT.h"

namespace IrtTree
{

void MoveStm::AcceptVisitor(IVisitor* visitor) const
{
    visitor->Visit( this );
}

const IExp* MoveStm::GetDst() const
{
    return dst.get();
}

const IExp* MoveStm::GetSrc() const
{
    return src.get();
}

void CExpStm::AcceptVisitor(IVisitor* visitor) const
{
    visitor->Visit( this );
}

const IExp* CExpStm::GetExp() const
{
    return exp.get();
}

void JumpStm::AcceptVisitor(IVisitor* visitor) const
{
    visitor->Visit( this );
}

const CLabel& CJumpStm::GetLabel() const
{
    return target;
}

const std::map<CJumpStm::ERelationType, const std::string> CJumpStm::TypeToStr
    = {{ERelationType::EQ, "EQ"},
       {ERelationType::NE, "NE"},
       {ERelationType::LT, "LT"}};

void CJumpStm::Accept( IVisitorIRT* v ) const
{
    visitor->Visit( this );
}

const IExp* CJumpStm::GetLeft() const
{
    return leftExp.get();
}

const IExp* CJumpStm::GetRight() const
{
    return rightExp.get();
}

const CLabel& CJumpStm::GetTrueLabel() const
{
    return ifTrueLabel;
}

const CLabel& CJumpStm::GetFalseLabel() const
{
    return ifFalseLabel;
}

const std::string& CJumpStm::GetTypeStr() const
{
    return TypeToStr.at( relationType );
}

void CSeqStm::AcceptVisitor(IVisitor* visitor) const
{
    visitor->Visit( this );
}

const IStm* SeqStm::GetLeft() const
{
    return leftStm.get();
}

const IStm* SeqStm::GetRight() const
{
    return rightStm.get();
}


void LabelStm::AcceptVisitor(IVisitor* visitor) const
{
    visitor->Visit( this );
}

const CLabel& LabelStm::GetLabel() const
{
    return label;
}

}

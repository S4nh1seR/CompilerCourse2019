#include "Exp.h"
#include "IVisitorIRT.h"

namespace IrtTree {

void ConstExp::AcceptVisitor(IVisitor* visitor) const
{
    visitor->Visit(this);
}

int ConstExp::GetValue() const
{
    return value;
}

void NameExp::AcceptVisitor(IVisitor* visitor) const
{
    visitor->Visit(this);
}

const CLabel& NameExp::GetLabel() const
{
    return label;
}

void TempExp::AcceptVisitor(IVisitor* visitor) const
{
    visitor->Visit(this);
}

const std::string TempExp::GetValueLabel() const
{
    return value.String();
}

const std::map<BinaryExp::EBinaryType, const std::string> BinaryExp::TypeToStr
    = {{EBinaryType::PLUS, "+"},
       {EBinaryType::MINUS, "-"},
       {EBinaryType::MULTIPLY, "*"},
       {EBinaryType::AND, "&&"}};

void BinaryExp::AcceptVisitor(IVisitor* visitor) const
{
    visitor->Visit( this );
}

const std::string& BinaryExp::GetTypeStr() const
{
    return TypeToStr.at(binType);
}

const IExp* BinaryExp::GetLeft() const
{
    return leftExp.get();
}

const IExp* BinaryExp::GetRight() const
{
    return rightExp.get();
}

MemoryExp::MemoryExp(const IExp* exp) :
    exp(exp)
{
}

void MemoryExp::AcceptVisitor(IVisitor* visitor) const
{
    visitor->Visit(this);
}

const IExp* MemoryExp::GetMem() const
{
    return exp.get();
}

void CallExp::AcceptVisitor(IVisitor* visitor) const
{
    visitor->Visit(this);
}

const IExp* CallExp::GetFuncExp() const
{
    return funcExp.get();
}

const ExpList* CallExp::GetArgs() const
{
    return args.get();
}

void ESeqExp::AcceptVisitor(IVisitor* visitor) const
{
    visitor->Visit(this);
}

const IStm* ESeqExp::GetStm() const
{
    return stm.get();
}

const IExp* ESeqExp::GetExp() const
{
    return exp.get();
}
};

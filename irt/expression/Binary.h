#pragma once

#include <map>
#include "IExp.h"


class BinaryExp : public IExp
{

 public:
    enum class EBinaryType
    {
        AND,
        PLUS,
        MINUS,
        MULTIPLY
    };

    BinaryExp(EBinaryType binType, std::unique_ptr<const IExp>& left, std::unique_ptr<const IExp>& right) :
        binType(binType), leftExp(left), rightExp(right)
    {
    }

    void AcceptVisitor(IVisitor* visitor) const override;
    const std::string& GetTypeStr() const;
    const IExp* GetLeft() const;
    const IExp* GetRight() const;

 private:
    const static std::map<EBinaryType, const std::string> TypeToStr;
    const EBinaryType binType;
    std::unique_ptr<const IExp> leftExp;
    std::unique_ptr<const IExp> rightExp;
};



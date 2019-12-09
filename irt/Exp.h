#pragma once

#include <memory>
#include <map>
#include "IExp.h"
#include "IStm.h"
#include "Label.h"
#include "List.h"

namespace IrtTree {

class ConstExp : public IExp
{

 public:

    explicit ConstExp(int value) : value(value)
    {
    }

    void AcceptVisitor(IVisitor* visitor) const override;
    int GetValue() const;

 private:
    const int value;
};

class NameExp : public IExp
{

 public:

    explicit NameExp( const CLabel& label ) : label(label)
    {
    }

    void AcceptVisitor(IVisitor* visitor) const override;
    const CLabel& GetLabel() const;

 private:
    CLabel label;
};

class TempExp : public IExp
{

 public:
    explicit TempExp( const CTemp& value_ ) : value( value_ )
    {
    }

    void AcceptVisitor(IVisitor* visitor) const override;
    const std::string GetValueLabel() const;

 private:
    CTemp value;
};

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

    BinaryExp( EBinaryType binType, const IExp* left, const IExp* right ) :
        binType( binType ), leftExp( left ), rightExp( right )
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

class MemoryExp : public IExp
{

 public:

    explicit MemoryExp(const IExp* exp);

    void AcceptVisitor(IVisitor* visitor) const override;
    const IExp* GetMem() const;

 private:
    std::unique_ptr<const IExp> exp;
};

class CallExp : public IExp
{

 public:

    CallExp( const IExp* funcExp, const ExpList* args ) : funcExp(funcExp), args(args)
    {
    }

    void AcceptVisitor(IVisitor* visitor) const override;
    const IExp* GetFuncExp() const;
    const ExpList* GetArgs() const;

 private:
    std::unique_ptr<const IExp> funcExp;
    std::unique_ptr<const ExpList> args;
};

class ESeqExp : public IExp
{

 public:

    ESeqExp( const IStm* stm, const IExp* exp ) : stm( stm ), exp( exp )
    {
    }

    void AcceptVisitor(IVisitor* visitor) const override;
    const IStm* GetStm() const;
    const IExp* GetExp() const;

 private:
    std::unique_ptr<const IStm> stm;
    std::unique_ptr<const IExp> exp;
};
}

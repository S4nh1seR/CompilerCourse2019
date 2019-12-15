#pragma once

#include <IrtExpressions.h>
#include <IrtStatements.h>

#include <cassert>

namespace IrTree {

    class ISubtreeWrapper {
    public:
        virtual ~ISubtreeWrapper() {};

        virtual std::shared_ptr<const IIrtExpression> ToExpression() = 0;
        virtual std::shared_ptr<const IIrtStatement> ToStatement() = 0;
        virtual std::shared_ptr<const IIrtStatement> ToConditional(const std::shared_ptr<const IrtLabel>& positiveLabel,
            const std::shared_ptr<const IrtLabel>& negativeLabel) = 0;
    };

    class ExpressionWrapper : public ISubtreeWrapper {
    public:
        explicit ExpressionWrapper(const std::shared_ptr<const IIrtExpression>& _expression): expression(_expression) {}

        std::shared_ptr<const IIrtExpression> ToExpression() override { return expression; }
        std::shared_ptr<const IIrtStatement> ToStatement() override;
        std::shared_ptr<const IIrtStatement> ToConditional(const std::shared_ptr<const IrtLabel>& positiveLabel,
            const std::shared_ptr<const IrtLabel>& negativeLabel) override;

    private:
        std::shared_ptr<const IIrtExpression> expression;
    };

    class StatementWrapper : public ISubtreeWrapper {
    public:
        explicit StatementWrapper(const std::shared_ptr<const IIrtStatement>& _statement): statement(_statement) {}

        std::shared_ptr<const IIrtExpression> ToExpression() override { assert(false); }
        std::shared_ptr<const IIrtStatement> ToStatement() override { return statement; }
        std::shared_ptr<const IIrtStatement> ToConditional(const std::shared_ptr<const IrtLabel>& positiveLabel,
            const std::shared_ptr<const IrtLabel>& negativeLabel) override { assert(false); }

    private:
        std::shared_ptr<const IIrtStatement> statement;
    };

    class ConditionalWrapper : public ISubtreeWrapper {
    public:
        virtual ~ConditionalWrapper() {};

        std::shared_ptr<const IIrtExpression> ToExpression() override;
        std::shared_ptr<const IIrtStatement> ToStatement() override { assert(false); }
        virtual std::shared_ptr<const IIrtStatement> ToConditional(const std::shared_ptr<const IrtLabel>& positiveLabel,
            const std::shared_ptr<const IrtLabel>& negativeLabel) override = 0;
    };


    // пока поддерживаем только "меньше <"
    class RelativeConditionalWrapper : public ConditionalWrapper {
    public:
        RelativeConditionalWrapper(const std::shared_ptr<const IIrtExpression>& _leftOperand,
            const std::shared_ptr<const IIrtExpression>& _rightOperand);

        std::shared_ptr<const IIrtStatement> ToConditional(const std::shared_ptr<const IrtLabel>& positiveLabel,
            const std::shared_ptr<const IrtLabel>& negativeLabel) override;

    private:
        std::shared_ptr<const IIrtExpression> leftOperand;
        std::shared_ptr<const IIrtExpression> rightOperand;
    };

    class AndConditionalWrapper : public ConditionalWrapper {
    public:
        AndConditionalWrapper(const std::shared_ptr<ISubtreeWrapper>& _leftOperand,
            const std::shared_ptr<ISubtreeWrapper>& _rightOperand);

        std::shared_ptr<const IIrtStatement> ToConditional(const std::shared_ptr<const IrtLabel>& positiveLabel,
            const std::shared_ptr<const IrtLabel>& negativeLabel) override;

    private:
        std::shared_ptr<ISubtreeWrapper> leftOperand;
        std::shared_ptr<ISubtreeWrapper> rightOperand;
    };

    class OrConditionalWrapper : public ConditionalWrapper {
    public:
        OrConditionalWrapper(const std::shared_ptr<ISubtreeWrapper>& _leftOperand,
            const std::shared_ptr<ISubtreeWrapper>& _rightOperand);

        std::shared_ptr<const IIrtStatement> ToConditional(const std::shared_ptr<const IrtLabel>& positiveLabel,
            const std::shared_ptr<const IrtLabel>& negativeLabel) override;

    private:
        std::shared_ptr<ISubtreeWrapper> leftOperand;
        std::shared_ptr<ISubtreeWrapper> rightOperand;
    };

    class OppositeConditionalWrapper : public ConditionalWrapper {
    public:
        explicit OppositeConditionalWrapper(const std::shared_ptr<ISubtreeWrapper>& _wrapper) : internalWrapper(_wrapper) {}

        std::shared_ptr<const IIrtStatement> ToConditional(const std::shared_ptr<const IrtLabel>& positiveLabel,
            const std::shared_ptr<const IrtLabel>& negativeLabel) override;

    private:
        std::shared_ptr<ISubtreeWrapper> internalWrapper;
    };



}

#pragma once

#include <IrtExpressions.h>
#include <IrtStatements.h>

#include <cassert>

namespace IrTree {

    class ISubtreeWrapper {
    public:
        virtual ~ISubtreeWrapper() {};

        virtual std::shared_ptr<const IIrtExpression> ToExpression() const { assert(false); };
        virtual std::shared_ptr<const IIrtStatement> ToStatement() const { assert(false); };
        virtual std::shared_ptr<const IIrtStatement> ToConditional(const std::shared_ptr<const IrtLabel>& positiveLabel,
            const std::shared_ptr<const IrtLabel>& negativeLabel) const { assert(false); };
    };

    class ExpressionWrapper : public ISubtreeWrapper {
    public:
        explicit ExpressionWrapper(const std::shared_ptr<const IIrtExpression>& _expression): expression(_expression) {}

        std::shared_ptr<const IIrtExpression> ToExpression() const override { return expression; }
        std::shared_ptr<const IIrtStatement> ToStatement() const override;
        std::shared_ptr<const IIrtStatement> ToConditional(const std::shared_ptr<const IrtLabel>& positiveLabel,
            const std::shared_ptr<const IrtLabel>& negativeLabel) const override;

    private:
        std::shared_ptr<const IIrtExpression> expression;
    };

    class StatementWrapper : public ISubtreeWrapper {
    public:
        explicit StatementWrapper(const std::shared_ptr<const IIrtStatement>& _statement): statement(_statement) {}

        std::shared_ptr<const IIrtStatement> ToStatement() const override { return statement; }

    private:
        std::shared_ptr<const IIrtStatement> statement;
    };

    class ConditionalWrapper : public ISubtreeWrapper {
    public:
        virtual ~ConditionalWrapper() {};

        std::shared_ptr<const IIrtExpression> ToExpression() const override;
        virtual std::shared_ptr<const IIrtStatement> ToConditional(const std::shared_ptr<const IrtLabel>& positiveLabel,
            const std::shared_ptr<const IrtLabel>& negativeLabel) const override = 0;
    };

    // пока поддерживаем только "меньше <"
    class RelativeConditionalWrapper : public ConditionalWrapper {
    public:
        RelativeConditionalWrapper(const std::shared_ptr<const IIrtExpression>& _leftOperand,
            const std::shared_ptr<const IIrtExpression>& _rightOperand);

        std::shared_ptr<const IIrtStatement> ToConditional(const std::shared_ptr<const IrtLabel>& positiveLabel,
            const std::shared_ptr<const IrtLabel>& negativeLabel) const override;

    private:
        std::shared_ptr<const IIrtExpression> leftOperand;
        std::shared_ptr<const IIrtExpression> rightOperand;
    };

    class AndConditionalWrapper : public ConditionalWrapper {
    public:
        AndConditionalWrapper(std::unique_ptr<const ISubtreeWrapper>&& _leftOperand,
            std::unique_ptr<const ISubtreeWrapper>&& _rightOperand);

        std::shared_ptr<const IIrtStatement> ToConditional(const std::shared_ptr<const IrtLabel>& positiveLabel,
            const std::shared_ptr<const IrtLabel>& negativeLabel) const override;

    private:
        std::shared_ptr<const ISubtreeWrapper> leftOperand;
        std::shared_ptr<const ISubtreeWrapper> rightOperand;
    };

    class OrConditionalWrapper : public ConditionalWrapper {
    public:
        OrConditionalWrapper(std::unique_ptr<const ISubtreeWrapper>&& _leftOperand,
            std::unique_ptr<const ISubtreeWrapper>&& _rightOperand);

        std::shared_ptr<const IIrtStatement> ToConditional(const std::shared_ptr<const IrtLabel>& positiveLabel,
            const std::shared_ptr<const IrtLabel>& negativeLabel) const override;

    private:
        std::shared_ptr<const ISubtreeWrapper> leftOperand;
        std::shared_ptr<const ISubtreeWrapper> rightOperand;
    };

    class OppositeConditionalWrapper : public ConditionalWrapper {
    public:
        explicit OppositeConditionalWrapper(std::unique_ptr<const ISubtreeWrapper>&& _wrapper) : internalWrapper(std::move(_wrapper)) {}

        std::shared_ptr<const IIrtStatement> ToConditional(const std::shared_ptr<const IrtLabel>& positiveLabel,
            const std::shared_ptr<const IrtLabel>& negativeLabel) const override;

    private:
        std::shared_ptr<const ISubtreeWrapper> internalWrapper;
    };
}

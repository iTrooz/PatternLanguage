#pragma once

#include <pl/patterns/pattern.hpp>

namespace pl::ptrn {

    class PatternSigned : public Pattern {
    public:
        PatternSigned(core::Evaluator *evaluator, u64 offset, size_t size, u32 color = 0)
            : Pattern(evaluator, offset, size, color) { }

        [[nodiscard]] std::unique_ptr<Pattern> clone() const override {
            return std::unique_ptr<Pattern>(new PatternSigned(*this));
        }

        [[nodiscard]] core::Token::Literal getValue() const override {
            i128 data = 0;
            this->getEvaluator()->readData(this->getOffset(), &data, this->getSize(), this->getSection());
            data = hlp::changeEndianess(data, this->getSize(), this->getEndian());

            return hlp::signExtend(this->getSize() * 8, data);
        }

        std::vector<u8> getBytesOf(const core::Token::Literal &value) const override {
            auto signedValue = core::Token::literalToSigned(value);
            std::vector<u8> result;

            result.resize(this->getSize());
            std::memcpy(result.data(), &signedValue, result.size());

            if (this->getEndian() != std::endian::native)
                std::reverse(result.begin(), result.end());

            return result;
        }

        [[nodiscard]] std::string getFormattedName() const override {
            return this->getTypeName();
        }

        [[nodiscard]] bool operator==(const Pattern &other) const override { return areCommonPropertiesEqual<decltype(*this)>(other); }

        void accept(PatternVisitor &v) override {
            v.visit(*this);
        }

        std::string getFormattedValue() override {
            auto data = core::Token::literalToSigned(this->getValue());
            return this->formatDisplayValue(fmt::format("{:d}", data), this->getValue());
        }

        [[nodiscard]] std::string toString() const override {
            auto value = this->getValue();
            auto result = fmt::format("{}", core::Token::literalToSigned(value));

            return this->formatDisplayValue(result, value);
        }
    };

}
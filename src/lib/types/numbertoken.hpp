#pragma once
#include <iomanip>
#include <ostream>
#include "token.hpp"

namespace json
{
    class NumberToken : public Token
    {
      public:
        explicit NumberToken(int skip, double number = 0.0) : Token(skip), value(number)
        {
        }

        NumberToken(const NumberToken&) = default;
        auto operator=(const NumberToken&) -> NumberToken& = default;
        NumberToken(NumberToken&&) = default;
        auto operator=(NumberToken&&) -> NumberToken& = default;

        ~NumberToken() override = default;

        double value;

        auto writeTo(std::ostream& os, int indent = 0, bool inl = false) const -> std::ostream& override
        {
            os << (inl ? "" : std::string(indent, ' ')) << "NumberToken { skip: " << skip << ", value: " << std::fixed
               << std::setprecision(4) << value << " }";
            return os;
        }
    };
} // namespace json

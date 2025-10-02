#pragma once
#include <ostream>
#include "token.hpp"

namespace json
{
    class TrueToken : public Token
    {
      public:
        explicit TrueToken(int skip) : Token(skip)
        {
        }

        TrueToken(const TrueToken&) = default;
        auto operator=(const TrueToken&) -> TrueToken& = default;
        TrueToken(TrueToken&&) = default;
        auto operator=(TrueToken&&) -> TrueToken& = default;

        ~TrueToken() override = default;

        bool value{true};

        auto writeTo(std::ostream& os, int indent = 0, bool inl = false) const -> std::ostream& override
        {
            os << (inl ? "" : std::string(indent, ' ')) << "TrueToken { skip: " << skip << ", value: " << std::boolalpha
               << value << " }";
            return os;
        }
    };
} // namespace json

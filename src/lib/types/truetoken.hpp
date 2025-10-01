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

        auto writeTo(std::ostream& os) const -> std::ostream& override
        {
            os << std::boolalpha << value;
            return os;
        }
    };
} // namespace json

#pragma once
#include <ostream>
#include "token.hpp"

namespace json
{
    class NullToken : public Token
    {
      public:
        explicit NullToken(int skip) : Token(skip)
        {
        }

        NullToken(const NullToken&) = default;
        auto operator=(const NullToken&) -> NullToken& = default;
        NullToken(NullToken&&) = default;
        auto operator=(NullToken&&) -> NullToken& = default;

        ~NullToken() override = default;

        auto writeTo(std::ostream& os) const -> std::ostream& override
        {
            os << "null";
            return os;
        }
    };
} // namespace json

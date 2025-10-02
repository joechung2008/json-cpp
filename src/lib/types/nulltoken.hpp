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

        auto writeTo(std::ostream& os, int indent = 0, bool inl = false) const -> std::ostream& override
        {
            os << (inl ? "" : std::string(indent, ' ')) << "NullToken { skip: " << skip << " }";
            return os;
        }
    };
} // namespace json

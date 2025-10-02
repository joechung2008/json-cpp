#pragma once
#include <ostream>
#include <string>
#include "token.hpp"

namespace json
{
    class StringToken : public Token
    {
      public:
        explicit StringToken(int skip, std::string string = "") : Token(skip), value(std::move(string))
        {
        }

        StringToken(const StringToken&) = default;
        auto operator=(const StringToken&) -> StringToken& = default;
        StringToken(StringToken&&) = default;
        auto operator=(StringToken&&) -> StringToken& = default;

        ~StringToken() override = default;

        std::string value;

        auto writeTo(std::ostream& os, int indent = 0, bool inl = false) const -> std::ostream& override
        {
            os << (inl ? "" : std::string(indent, ' ')) << "StringToken { skip: " << skip << ", value: \"" << value
               << "\" }";
            return os;
        }
    };
} // namespace json

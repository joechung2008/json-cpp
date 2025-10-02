#pragma once
#include <ostream>
#include "token.hpp"

namespace json
{
    class FalseToken : public Token
    {
      public:
        explicit FalseToken(int skip) : Token(skip)
        {
        }

        FalseToken(const FalseToken&) = default;
        auto operator=(const FalseToken&) -> FalseToken& = default;
        FalseToken(FalseToken&&) = default;
        auto operator=(FalseToken&&) -> FalseToken& = default;

        ~FalseToken() override = default;

        bool value{false};

        auto writeTo(std::ostream& os, int indent = 0, bool inl = false) const -> std::ostream& override
        {
            os << (inl ? "" : std::string(indent, ' ')) << "FalseToken { skip: " << skip
               << ", value: " << std::boolalpha << value << " }";
            return os;
        }
    };
} // namespace json

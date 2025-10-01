#pragma once
#include <ostream>

namespace json
{
    class Token
    {
      public:
        explicit Token(int skip) : skip(skip)
        {
        }

        Token(const Token&) = default;
        auto operator=(const Token&) -> Token& = default;
        Token(Token&&) = default;
        auto operator=(Token&&) -> Token& = default;

        int skip;

        virtual ~Token() = default;

        virtual auto writeTo(std::ostream& os) const -> std::ostream& = 0;
    };
} // namespace json

static auto operator<<(std::ostream& os, const json::Token& token) -> std::ostream&
{
    return token.writeTo(os);
}

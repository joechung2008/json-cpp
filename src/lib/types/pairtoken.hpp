#pragma once
#include <memory>
#include <ostream>
#include "stringtoken.hpp"
#include "token.hpp"

namespace json
{
    class PairToken : public Token
    {
      public:
        PairToken(int skip, std::shared_ptr<StringToken> key, std::shared_ptr<Token> value)
            : Token(skip), key(std::move(key)), value(std::move(value))
        {
        }

        std::shared_ptr<StringToken> key;
        std::shared_ptr<Token> value;

        auto writeTo(std::ostream& os) const -> std::ostream& override
        {
            os << *key << ":" << *value;
            return os;
        }
    };
} // namespace json

static auto operator<<(std::ostream& os, const json::PairToken& token) -> std::ostream&
{
    return token.writeTo(os);
}

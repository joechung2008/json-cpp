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

        auto writeTo(std::ostream& os, int indent = 0, bool inl = false) const -> std::ostream& override
        {
            os << std::string(indent, ' ') << "PairToken {\n";
            os << std::string(indent + 4, ' ') << "key: ";
            key->writeTo(os, 0, true);
            os << ",\n";
            os << std::string(indent + 4, ' ') << "value: ";
            value->writeTo(os, indent + 4, true);
            os << "\n" << std::string(indent, ' ') << "}";
            return os;
        }
    };
} // namespace json

static auto operator<<(std::ostream& os, const json::PairToken& token) -> std::ostream&
{
    return token.writeTo(os, 0, false);
}

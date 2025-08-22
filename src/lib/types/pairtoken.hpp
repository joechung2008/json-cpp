#pragma once
#include <iostream>
#include <string>
#include "stringtoken.hpp"
#include "token.hpp"

namespace json {
    class PairToken : public Token {
    public:
        PairToken(int skip, std::shared_ptr<StringToken> key, std::shared_ptr<Token> value)
            : Token(skip), key(key), value(value) {
        }
        
        std::shared_ptr<StringToken> key;
        std::shared_ptr<Token> value;

        std::ostream& writeTo(std::ostream &os) const {
            os << *key << ":" << *value;
            return os;
        }        
    };
}

inline std::ostream& operator<<(std::ostream& os, const json::PairToken& token) {
    return token.writeTo(os);
}

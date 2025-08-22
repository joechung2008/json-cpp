#pragma once
#include <iostream>
#include "token.hpp"

namespace json {
    class NullToken : public Token {
    public:
        NullToken(int skip)
            : Token(skip) {
        }
        
        virtual ~NullToken() {
        }

        std::ostream& writeTo(std::ostream& os) const {
            os << "null";
            return os;
        }
    };
}

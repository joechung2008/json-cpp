#pragma once
#include <iostream>
#include "token.hpp"

namespace json {
    class TrueToken : public Token {
    public:
        TrueToken(int skip)
            : Token(skip), value(true) {
        }
        
        virtual ~TrueToken() {
        }

        bool value;
        
        std::ostream& writeTo(std::ostream& os) const {
            os << std::boolalpha << value;
            return os;
        }
    };
}

#pragma once
#include <ostream>
#include "token.hpp"

namespace json {
    class NumberToken : public Token {
    public:
        NumberToken(int skip, double number = 0.0)
            : Token(skip), value(number) {
        }

        virtual ~NumberToken() {
        }

        double value;
        
        std::ostream& writeTo(std::ostream& os) const {
            os << value;
            return os;
        }
    };
}

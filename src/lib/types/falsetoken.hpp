#pragma once
#include <ostream>
#include "token.hpp"

namespace json {
    class FalseToken : public Token {
    public:
        FalseToken(int skip)
            : Token(skip), value(false) {
        }

        virtual ~FalseToken() {
        }

        bool value;
        
        std::ostream& writeTo(std::ostream& os) const {
            os << std::boolalpha << value;
            return os;
        }
    };
}

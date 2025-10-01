#pragma once
#include <ostream>
#include <string>
#include "token.hpp"

namespace json {
    class StringToken : public Token {
    public:
        StringToken(int skip, std::string string = "")
            : Token(skip), value(string) {
        }

        virtual ~StringToken() {
        }

        std::string value;
        
        std::ostream& writeTo(std::ostream& os) const {
            os << "\"" << value << "\"";
            return os;
        }
    };
}

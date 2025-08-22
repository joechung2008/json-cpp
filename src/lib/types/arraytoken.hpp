#pragma once
#include <iostream>
#include <vector>
#include "token.hpp"

namespace json {
    class ArrayToken : public Token {
    public:
        ArrayToken(int skip, std::vector<std::shared_ptr<Token>> elements)
            : Token(skip), elements(elements) {
        }
        
        virtual ~ArrayToken() {
        }

        std::vector<std::shared_ptr<Token>> elements;
        
        std::ostream& writeTo(std::ostream& os) const {
            os << "[";
            for (auto it = elements.begin(); it != elements.end(); ++it) {
                if (it != elements.begin()) {
                    os << ",";
                }

                os << **it;
            }
            os << "]";
            return os;
        }
    };
}

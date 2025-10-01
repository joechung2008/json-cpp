#pragma once
#include <memory>
#include <ostream>
#include <vector>
#include "pairtoken.hpp"
#include "token.hpp"

namespace json {
    class ObjectToken : public Token {
    public:
        ObjectToken(int skip, std::vector<std::shared_ptr<PairToken>> pairs)
            : Token(skip), members(pairs) {
        }

        virtual ~ObjectToken() {
        }

        std::vector<std::shared_ptr<PairToken>> members;
        
        std::ostream& writeTo(std::ostream& os) const {
            os << "{";
            for (auto it = members.begin(); it != members.end(); ++it) {
                if (it != members.begin()) {
                    os << ",";
                }
                os << **it;
            }
            os << "}";
            return os;
        }
    };
}

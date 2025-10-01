#pragma once
#include <memory>
#include <ostream>
#include <vector>
#include "pairtoken.hpp"
#include "token.hpp"

namespace json
{
    class ObjectToken : public Token
    {
      public:
        ObjectToken(int skip, std::vector<std::shared_ptr<PairToken>> pairs) : Token(skip), members(std::move(pairs))
        {
        }

        ObjectToken(const ObjectToken&) = default;
        auto operator=(const ObjectToken&) -> ObjectToken& = default;
        ObjectToken(ObjectToken&&) = default;
        auto operator=(ObjectToken&&) -> ObjectToken& = default;

        ~ObjectToken() override = default;

        std::vector<std::shared_ptr<PairToken>> members;

        auto writeTo(std::ostream& os) const -> std::ostream& override
        {
            os << "{";
            for (auto it = members.begin(); it != members.end(); ++it)
            {
                if (it != members.begin())
                {
                    os << ",";
                }
                os << **it;
            }
            os << "}";
            return os;
        }
    };
} // namespace json

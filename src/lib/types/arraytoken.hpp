#pragma once
#include <memory>
#include <ostream>
#include <vector>
#include "token.hpp"

namespace json
{
    class ArrayToken : public Token
    {
      public:
        ArrayToken(int skip, std::vector<std::shared_ptr<Token>> elements) : Token(skip), elements(std::move(elements))
        {
        }

        ArrayToken(const ArrayToken&) = default;
        auto operator=(const ArrayToken&) -> ArrayToken& = default;
        ArrayToken(ArrayToken&&) = default;
        auto operator=(ArrayToken&&) -> ArrayToken& = default;

        ~ArrayToken() override = default;

        std::vector<std::shared_ptr<Token>> elements;

        auto writeTo(std::ostream& os) const -> std::ostream& override
        {
            os << "[";
            for (auto it = elements.begin(); it != elements.end(); ++it)
            {
                if (it != elements.begin())
                {
                    os << ",";
                }

                os << **it;
            }
            os << "]";
            return os;
        }
    };
} // namespace json

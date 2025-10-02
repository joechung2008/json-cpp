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

        auto writeTo(std::ostream& os, int indent = 0, bool inl = false) const -> std::ostream& override
        {
            os << (inl ? "" : std::string(indent, ' ')) << "ArrayToken {\n";
            os << std::string(indent + 4, ' ') << "elements: [";
            if (!elements.empty())
            {
                os << "\n";
                for (size_t i = 0; i < elements.size(); ++i)
                {
                    elements[i]->writeTo(os, indent + 8, false);
                    if (i < elements.size() - 1)
                    {
                        os << ",";
                    }
                    os << "\n";
                }
                os << std::string(indent + 4, ' ');
            }
            os << "]\n" << std::string(indent, ' ') << "}";
            return os;
        }
    };
} // namespace json

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

        auto writeTo(std::ostream& os, int indent = 0, bool inl = false) const -> std::ostream& override
        {
            os << (inl ? "" : std::string(indent, ' ')) << "ObjectToken {\n";
            os << std::string(indent + 4, ' ') << "members: [";
            if (!members.empty())
            {
                os << "\n";
                for (size_t i = 0; i < members.size(); ++i)
                {
                    members[i]->writeTo(os, indent + 8, false);
                    if (i < members.size() - 1)
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

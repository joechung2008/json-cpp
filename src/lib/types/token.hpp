#pragma once
#include <ostream>

namespace json
{
    class Token
    {
      public:
        Token(int skip) : skip(skip)
        {
        }

        int skip;

        virtual ~Token()
        {
        }

        virtual std::ostream& writeTo(std::ostream& os) const = 0;
    };
} // namespace json

inline std::ostream& operator<<(std::ostream& os, const json::Token& token)
{
    return token.writeTo(os);
}

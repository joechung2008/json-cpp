#include <cstdint>
#include <memory>
#include <regex>
#include <stdexcept>
#include "../types/pairtoken.hpp"
#include "../types/stringtoken.hpp"
#include "../types/token.hpp"
#include "string.hpp"
#include "value.hpp"

namespace json
{
    auto parsePair(const std::string& s, const std::regex& delimiters) -> std::shared_ptr<PairToken>
    {
        enum class Mode : std::uint8_t
        {
            Scanning,
            Key,
            Colon,
            Value,
            End
        };

        auto mode = Mode::Scanning;
        auto pos = 0;
        const std::regex whitespace(R"([ \n\r\t])");
        std::shared_ptr<StringToken> key;
        std::shared_ptr<Token> value;

        while (pos < s.length() && mode != Mode::End)
        {
            std::string ch(1, s[pos]);
            std::string slice;

            switch (mode)
            {
            case Mode::Scanning:
                if (regex_search(ch, whitespace))
                {
                    pos++;
                }
                else
                {
                    mode = Mode::Key;
                }
                break;

            case Mode::Key:
                slice = s.substr(pos);
                key = parseString(slice);
                pos += key->skip;
                mode = Mode::Colon;
                break;

            case Mode::Colon:
                if (regex_search(ch, whitespace))
                {
                    pos++;
                }
                else if (ch == ":")
                {
                    pos++;
                    mode = Mode::Value;
                }
                else
                {
                    throw std::runtime_error("Expected ':'");
                }
                break;

            case Mode::Value:
                slice = s.substr(pos);
                value = parseValue(slice, delimiters);
                pos += value->skip;
                mode = Mode::End;
                break;

            case Mode::End:
                break;

            default:
                throw std::runtime_error("Unexpected mode");
            }
        }

        return std::make_shared<PairToken>(pos, key, value);
    }
} // namespace json

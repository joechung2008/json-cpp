#include <string>
#include <vector>
#include <memory>
#include <regex>
#include <stdexcept>
#include "../types.hpp"
#include "object.hpp"
#include "pair.hpp"

namespace json
{
    std::shared_ptr<ObjectToken> parseObject(const std::string &s)
    {
        enum class Mode
        {
            Scanning,
            LeftBrace,
            Pair,
            Delimiter,
            End
        };

        auto mode = Mode::Scanning;
        auto pos = 0;
        const std::regex delimiters(R"([ \n\r\t,\}])");
        const std::regex whitespace(R"([ \n\r\t])");
        auto pMembers = std::make_shared<std::vector<std::shared_ptr<PairToken>>>();

        while (pos < s.length() && mode != Mode::End)
        {
            std::string ch(1, s[pos]);

            switch (mode)
            {
            case Mode::Scanning:
                if (regex_search(ch, whitespace))
                {
                    pos++;
                }
                else if (ch == "{")
                {
                    pos++;
                    mode = Mode::Pair;
                }
                else
                {
                    throw std::runtime_error("Expected '{'");
                }
                break;

            case Mode::Pair:
                if (regex_search(ch, whitespace))
                {
                    pos++;
                }
                else if (ch == "}")
                {
                    if (!pMembers->empty())
                    {
                        throw std::runtime_error("Unexpected ','");
                    }

                    pos++;
                    mode = Mode::End;
                }
                else
                {
                    std::string slice = s.substr(pos);
                    std::shared_ptr<PairToken> member = parsePair(slice, delimiters);
                    pMembers->push_back(member);
                    pos += member->skip;
                    mode = Mode::Delimiter;
                }
                break;

            case Mode::Delimiter:
                if (regex_search(ch, whitespace))
                {
                    pos++;
                }
                else if (ch == ",")
                {
                    pos++;
                    mode = Mode::Pair;
                }
                else if (ch == "}")
                {
                    pos++;
                    mode = Mode::End;
                }
                else
                {
                    throw std::runtime_error("Expected ',' or '}'");
                }
                break;

            case Mode::End:
                break;

            default:
                throw std::runtime_error("Unexpected mode");
            }
        }

        return std::make_shared<ObjectToken>(pos, *pMembers);
    }
}
